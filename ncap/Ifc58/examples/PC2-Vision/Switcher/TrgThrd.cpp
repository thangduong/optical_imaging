/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/05/03 2:59p $
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
#include "Switcher.h"
#include "TrgThrd.h"
#include <windowsx.h>
#include <pv2cam.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *)owner;
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();	
	CImgConn *imgConn;
	CP2VCam *cam;
	BYTE *imgBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD areaDx;	// DX of the image area being processed
	DWORD areaDy;  // DY of the image area being processed
	DWORD frameCount;
	BYTE *pHostBuffFrame;
	int iSeqNum;
	DWORD AcquiredDy;
	HIFCGRAB grabID; 
	DWORD childId=proc->m_parent->m_viewID%P2V_MAX_NUM_CAMERAS;
	BOOL singleRing=theapp->m_singleRing;
	GRAB_EXT_ATTR ExtendedAttr;

	cam = (CP2VCam*)theapp->m_pMod->GetCam(theapp->m_camIdx[childId]);
	
	CAM_ATTR attr;
	cam->GetAttr(&attr);

	attr.dwBytesPerPixel=1;
	attr.dwBitsPerPixel=8;

	areaDx = attr.dwWidth;
	areaDy = attr.dwHeight;

	imgBuf =  theapp->m_singleRing ? theapp->m_pHostBuffFrame[0] : theapp->m_pHostBuffFrame[childId];
	imgConn = IfxCreateImgConn(imgBuf,(WORD)areaDx,(WORD)areaDy,(WORD)attr.dwBitsPerPixel, proc->m_parent->m_hWnd);
	CImgSink *imgSink=imgConn->GetSink();
	imgSink->ResizeWindow();
	
	grabID = theapp->m_grabID[childId]; 
	
	if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG ) {
		Sleep(33);
		cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}

	for (frameCount=0;!proc->m_shutdown;) {
		
		if (((iSeqNum=cam->GrabWaitFrameEx(grabID,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,FALSE,&AcquiredDy,NULL,&ExtendedAttr)) >= 0)
			&& !proc->m_shutdown) {
			
			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
			
			if (!theapp->m_singleRing ||  (ExtendedAttr.camPortNum == theapp->m_camIdx[childId]) ) {
				// Update the address associated with the image source to point to the frame
				// we just processed
				imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);
				// Display the  frame in our client window
				imgConn->Display();
				frameCount++;
				
				// Release the frame back into the active circular acquistion buffer
				cam->GrabRelease(grabID,iSeqNum);
			}
		}
		else {
			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
			Sleep(20);
		}
		
	}
	cam->Freeze(grabID);
	delete imgConn;
	
	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CSwitcherView *parent)
{
	DWORD id;
	m_parent = parent;
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
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();	
	// Tell the trigger thread to m_shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject (hthread,INFINITE);
	CloseHandle(hthread);
}

