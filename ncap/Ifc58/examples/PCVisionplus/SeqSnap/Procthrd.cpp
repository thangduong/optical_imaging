
#include "stdafx.h"
#include "seqsnap.h"
#include "seqsnapv.h"
#include "ProcThrd.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FRAMES_IN_HOSTBUFF 5

/////////////////////////////////////////////////////////////////////////////
// CProcessThread

// This is the image processing and display thread
DWORD WINAPI ProcessThread(LPVOID pOwner)
{
	CProcessThread *proc = (CProcessThread *)pOwner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_pView;
	CImgConn *imgconn;
	BYTE *imgBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD areaDx;	// DX of the image area being processed
	DWORD areaDy;  // DY of the image area being processed
	float avgTime;
	DWORD start_time;
	DWORD frame_count;
	BYTE *pHostBuffFrame;
	int iSeqNum;
	CICamera *cam=theapp->m_cam;
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	areaDx = attr.dwWidth;
	areaDy = attr.dwHeight;
	imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,areaDx * areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	imgconn = new CImgConn(imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwWidth,(WORD)attr.dwBitsPerPixel, view->m_hWnd);

	// set board in mode: grab into host circular buffer
	cam->Grab(imgBuf, FRAMES_IN_HOSTBUFF);

	Sleep(20);

	start_time =  theapp->m_iCap->m_os->GetSystimeMillisecs();
	for (frame_count=0;!proc->m_bShutdown;) {

		// Wait for a new frame to become available, and lock it
		// some it can't be overwritten while we are processing and then displaying it
		if ((iSeqNum=cam->GrabWaitFrame(&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {


			// Update the address associated with the image source to point to the frame
			// we just processed
			imgconn->GetSrc()->SetBufferAddr(pHostBuffFrame);
			// Display the  frame in our client window
			imgconn->Display();
			frame_count++;
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(iSeqNum);
		}
	}

	if (frame_count > 0) {
		avgTime = (float)(theapp->m_iCap->m_os->GetSystimeMillisecs() - start_time) / (float)frame_count;
		theapp->m_iCap->m_os->WriteConsole("\nAverage acquire time was %f milliseconds",avgTime);
	}
	// Stop the grab operation
	cam->Freeze();
	delete imgconn;
	if (imgBuf)
		GlobalFreePtr(imgBuf);

	return 0;
}


CProcessThread::CProcessThread(CSeqsnapView *thread_view)
{
	DWORD id;
	m_bShutdown = FALSE;
	m_pView = thread_view;
	m_hThread = CreateThread(
					NULL,					// address of thread security attributes
					(DWORD)0x4000,			// initial thread stack size, in bytes
					ProcessThread,			// address of thread function
					(LPVOID)this,			// argument for new thread
					0x0,					// creation flags
					&id );					// address of returned thread identifier
}


CProcessThread::~CProcessThread()
{
	// Tell the image processing thread to shutdown
	m_bShutdown = TRUE;
	// Wait for the thread to terminate
	WaitForSingleObject (m_hThread,INFINITE);
	CloseHandle(m_hThread);
}





