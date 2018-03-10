/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/6Cam2Grab/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/06/03 5:58p $
 *
 * ABSTRACT
 *    IFC Wizard Produced Program
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/

#include "stdafx.h"
#include "6Cam2Grab.h"
#include "TrgThrd.h"
#include <windowsx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *)owner;
	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	
	CImgConn *imgConn;
	CICamera *cam=theapp->m_cam;
	DWORD frameCount;
	BYTE *pHostBuffFrame;
	int iSeqNum;
	DWORD AcquiredDy;
	HIFCGRAB grabID;
	GRAB_EXT_ATTR ExtendedAttr;


	// TODO: Set your particular trigger parameters

	CAM_ATTR attr;
	cam->GetAttr(&attr);

	// Note: ringNumFrames parameter to Grab must be a multiple of 3 
	grabID = theapp->m_grabID[0];

	if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG) {
		Sleep(33);
		cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}

	for (frameCount=0;!proc->m_shutdown;) {

		if (((iSeqNum=cam->GrabWaitFrameEx(grabID, &pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy,NULL,&ExtendedAttr)) >= 0)
			&& !proc->m_shutdown) {

			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG ) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}

			// Update the address associated with the image source to point to the frame
			// we just processed
			WaitForSingleObject(theapp->m_connMutex,10000);

			imgConn = theapp->m_imgConn[ExtendedAttr.camPortNum];
			if (imgConn) {
				imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);
				// Display the  frame in our client window
				imgConn->Display();
			}

			::ReleaseMutex(theapp->m_connMutex);

			frameCount++;

			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(grabID, iSeqNum);
		}
		else {
			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
			Sleep(20);
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(DWORD groupID)
{
	DWORD id;
	m_groupID = groupID;

	m_shutdown = FALSE;
	hthread = CreateThread(
			NULL,                	// address of thread security attributes
			(DWORD)0x10000,       	// initial thread stack size, in bytes
			TriggerThread,            // address of thread function
			(LPVOID)this,     // argument for new thread
			0x0,                   	// creation flags
			&id );                  // address of returned thread identifier
}


CTrgThrd::~CTrgThrd()
{
	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	
	// Tell the trigger thread to m_shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject (hthread,INFINITE);
	CloseHandle(hthread);
}

