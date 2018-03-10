/******************************************************************************
 *
 * MODULE
 *      procthrd.cpp 
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/examples/overlay/PROCTHRD.CPP $
 *     $Revision: 1.1 $
 *     $Modtime: 5/23/00 10:22a $
 *
 * ABSTRACT
 *     This module is part of the PCDig Image Processing Example
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/


#include "stdafx.h"
#include "overlay.h"
#include "procthrd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PROCTHRD

// This is the image processing and display thread
DWORD WINAPI ProcessThread(LPVOID owner)
{
	PROCTHRD *proc = (PROCTHRD *)owner;
	COverlayView *view = proc->m_thread_view;
	COverlayApp *theapp=(COverlayApp*)AfxGetApp();	
	BYTE *frame_addr;
	int seqnum;
	while (!proc->shutdown) {
		// Wait for a new frame to become available, and lock it
		// some it can't be overwritten while we are processing and then displaying it
		if ((seqnum=view->m_cam->GrabWaitFrameEx(view->m_hGrabId, &frame_addr)) >= 0) {

			// TODO - insert any image processisng code here

			// Update the address associated with the image source to point to the frame
			// we just processed
			view->m_hImgsrc->SetBufferAddr(frame_addr);		

			// Display the processed frame in our client window
			view->m_hSrvconn->Display();

			// Release the frame back into the active circular acquistion buffer
			view->m_cam->GrabRelease(view->m_hGrabId, seqnum);
		}
	}
	return 0;
}


PROCTHRD::PROCTHRD(COverlayView *thread_view)
{
	DWORD id;
	shutdown = FALSE;
	m_thread_view = thread_view;
	hthread = CreateThread(
			NULL,                	// address of thread security attributes
			(DWORD)0x4000,       	// initial thread stack size, in bytes
			ProcessThread,            // address of thread function
			(LPVOID)this,     // argument for new thread
			0x0,                   	// creation flags
			&id );                  // address of returned thread identifier
}


PROCTHRD::~PROCTHRD()
{
	// Tell the image processing thread to shutdown
	shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject (hthread,INFINITE);
	CloseHandle(hthread);
}


