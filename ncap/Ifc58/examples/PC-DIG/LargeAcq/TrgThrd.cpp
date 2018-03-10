/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/LargeAcq/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 10/09/03 10:02a $
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
#include "LargeAcq.h"
#include "TrgThrd.h"
#include <windowsx.h>
#include <clrspace.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	return ((CTrgThrd *)owner)->TriggerLoop();
}

DWORD CTrgThrd::TriggerLoop(void)
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	CImgConn *imgConn;
	CICamera *cam=theapp->m_cam;
	DWORD frameCount;
	int iSeqNum;
	DWORD AcquiredDy;

	SetThreadPriority(GetCurrentThread() , THREAD_PRIORITY_BELOW_NORMAL);

	imgConn = m_parent->m_hImgConn;

	if (!cam->Grab(m_parent->m_pImgBuff, m_parent->m_numFramesInHostBuf)) {
		::MessageBox(NULL,"The attempt to grab to host memory failed.",
				"Grab Fail",MB_OK);

		return 0;
	}

	for (frameCount=0;1;) {

		if ((iSeqNum=cam->GrabWaitFrame(&m_parent->m_pHostBuffFrame,IFC_WAIT_NEWER_FRAME,1000,TRUE,&AcquiredDy)) >= 0) {

			m_parent->DisplayImage(m_parent->m_pHostBuffFrame);
			frameCount++;

			if (m_shutdown)
				break;
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(iSeqNum);
		}
		else if (m_shutdown)
			break;

	}
	iSeqNum=cam->Freeze();

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CLargeAcqView *parent)
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
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	// Tell the trigger thread to m_shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject (hthread,INFINITE);
	CloseHandle(hthread);
}


BOOL CTrgThrd::SetAoiPos(DWORD x, DWORD y)
{
	return TRUE;
}