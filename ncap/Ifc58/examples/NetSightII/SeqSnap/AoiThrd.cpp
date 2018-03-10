/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/seqsnap/AoiThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 1/13/04 10:27a $
 *
 * ABSTRACT
 *    NetSight II Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "AoiThrd.h"
#include <windowsx.h>
#include <NSII.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FRAMES_IN_HOSTBUFF 12



// This is the image processing thread
DWORD WINAPI AioTriggerThread(LPVOID owner)
{
 	CAioThrd *proc = (CAioThrd *)owner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_parent;


	BYTE *m_imgBuf=NULL;	// Memory space which is the destination of the ITX grab operation
	DWORD m_areaDx;	// DX of the image area being processed
	DWORD m_areaDy;  // DY of the image area being processed
	DWORD last_time,old_time;
	DWORD frame_count;
	DWORD deltaTime;
	DWORD totalTime;
	BYTE *pHostBuffFrame;
	CICamera *cam=theapp->m_cam;
	int iSeqNum;
	CAM_ATTR attr;
	DWORD AcquiredDy;
	HIFCGRAB hGrabId;
	IFC_GRAB_STATS stats;
	GRAB_EXT_ATTR ExtendedAttr;
	CNetSightII *nsii=(CNetSightII*)theapp->m_iCap;
	int iTrigSrc			= (int) cam->GetAcqParam(P_TRIGGER_SRC);

	CIFCOS os;
//	os.WriteConsole("\nAIO Begin");
	
	
	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;

	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);

	proc->m_imgConn = IfxCreateImgConn(m_imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight,(WORD)attr.dwBitsPerPixel, view->m_hWnd,attr.color);

	// Set board in mode: grab into host circular buffer.
	hGrabId = cam->Grab(IFC_GOPT_AUTO_FRAME_LOCK,m_imgBuf, FRAMES_IN_HOSTBUFF);


	Sleep(20);
	totalTime = 0;
	last_time = 0;

	if (iTrigSrc == IFC_SOFT_TRIG){
		// Kickoff the software trigger chain
		cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}


	DWORD lastObjectIndex=255;
	for (frame_count=0;!proc->m_shutdown;) {
		

		// Wait for a new frame to become available, and lock it
		// so it can't be overwritten while we are processing and then displaying it
		if (((iSeqNum=cam->GrabWaitFrameEx(hGrabId,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy, NULL, &ExtendedAttr)) >= 0)
			&& !proc->m_shutdown) {

			if (iTrigSrc == IFC_SOFT_TRIG){
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}

			old_time = last_time;
			theapp->m_iCap->GetGrabStats(hGrabId,&stats);

			last_time = theapp->m_iCap->m_os->GetSystimeMillisecs();
			if (frame_count > 0) {
				deltaTime = last_time - old_time;
				totalTime += deltaTime;
			}

//			if (((lastObjectIndex+1)%256) != ExtendedAttr.objectIndex)
//				os.WriteConsole("\n Object ID gap got %d expected %d",ExtendedAttr.objectIndex,(lastObjectIndex+1)%256);

//			os.WriteConsole("\n Object ID %d  seq %d",ExtendedAttr.objectIndex, iSeqNum);

			lastObjectIndex = ExtendedAttr.objectIndex;
			
			nsii->AdvancedIOEnqueueDecision( NSP_REJECTOR_1, ExtendedAttr.objectIndex,
				(frame_count&1)? NSP_DECISION_REJECT:NSP_DECISION_ACCEPT);

			nsii->AdvancedIOEnqueueDecision( NSP_REJECTOR_2, ExtendedAttr.objectIndex,
				(frame_count&2)? NSP_DECISION_REJECT:NSP_DECISION_ACCEPT);


			// Update the address associated with the image source to point to the frame
			// we just processed
			proc->m_imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);
								
			proc->m_imgConn->Display();

			frame_count++;
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(hGrabId, iSeqNum);
		}
		else {
			// When timeout generate a SW trigger if necessary
			if (iTrigSrc == IFC_SOFT_TRIG){
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
		}

	}


	cam->Freeze(hGrabId);

	cam->SetAcqParam(NSP_AIO_ENABLE, IFC_DISABLE);

	if(proc->m_imgConn)
		delete proc->m_imgConn;
	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);	
	

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAioThrd::CAioThrd(CSeqsnapView *parent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	DWORD id;
	m_parent	= parent;
	m_shutdown	= FALSE;
	m_bNewFrame = FALSE;
	m_imgConn = 0;
	cam->SetAcqParam(NSP_AIO_ENABLE, IFC_ENABLE);

	m_hthread	= CreateThread(
						NULL,				// address of thread security attributes
						(DWORD) 0x10000,	// initial thread stack size, in bytes
						AioTriggerThread,		// address of thread function
						(LPVOID) this,		// argument for new thread
						0x0,				// creation flags
						&id);				// address of returned thread identifier
}


CAioThrd::~CAioThrd()
{
	// Tell the trigger thread to shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject(m_hthread, INFINITE);
	CloseHandle(m_hthread);
}


