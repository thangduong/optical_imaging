/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/12/02 4:02p $
 *
 * ABSTRACT
 *    BanditII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "TrgThrd.h"
#include <windowsx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FRAMES_IN_HOSTBUFF 5

/// This is the display thread
DWORD WINAPI DisplayThread(LPVOID owner)
{

 	CTrgThrd *proc = (CTrgThrd *)owner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_parent->m_vParent;

	while(proc->m_bDisplay) {
		if(proc->m_imgConn)
			proc->m_imgConn->Display();
		Sleep(30);	// Yield
	}
	return 0;
}


// This is the image processing thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
 	CTrgThrd *proc = (CTrgThrd *)owner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_parent->m_vParent;


	BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD m_areaDx;	// DX of the image area being processed
	DWORD m_areaDy;  // DY of the image area being processed
	DWORD last_time,old_time, singl_img_time;
	DWORD frame_count;
	DWORD deltaTime;
	DWORD totalTime;
	BYTE *pHostBuffFrame;
	CInterrupt intr_eot(theapp->m_iCap, BDT_INTR_EOFRM);
	CICamera *cam=theapp->m_cam;
	int iSeqNum;
	CTrigGrabDlg* m_trigProp = proc->m_parent;
	CAM_ATTR attr;
	DWORD AcquiredDy;
	HIFCGRAB hGrabId;
	CVixnEOF *pVixnEOF =0;
	IFC_GRAB_STATS stats;
	int i, j;
	bool GoodImage = TRUE;
	
	
	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	j = m_areaDx / 2;

	proc->m_imgConn = IfxCreateImgConn(m_imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight,(WORD)attr.dwBitsPerPixel, view->m_hWnd,attr.color);

	// Set board in mode: grab into host circular buffer.
	hGrabId = cam->Grab(IFC_GOPT_SYSCOLOR_CLIP,m_imgBuf, FRAMES_IN_HOSTBUFF);
	Sleep(20);
	totalTime = 0;
	m_trigProp->m_maxTime = 0;
	m_trigProp->m_minTime = 1000;
	m_trigProp->m_avgTime = 0;
	m_trigProp->m_nTriggers = 0;
	last_time = 0;

	if (m_trigProp->m_iTrigSrc == BDT_SOFT_TRIG){
		pVixnEOF = new CVixnEOF(theapp->m_iCap);
		pVixnEOF->Create();
		// Kickoff the software trigger chain
		cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}
	singl_img_time = theapp->m_iCap->m_os->GetSystimeMillisecs();

	BOOL bDone = FALSE;

	DWORD id;
	proc->m_bDisplay = TRUE;
	proc->m_hDisplayThread =	CreateThread(
						NULL,				// address of thread security attributes
						(DWORD) 0x10000,	// initial thread stack size, in bytes
						DisplayThread,		// address of thread function
						(LPVOID) owner,		// argument for new thread
						0x0,				// creation flags
						&id);				// address of returned thread identifier

	::SetThreadPriority(GetCurrentThread() , THREAD_PRIORITY_TIME_CRITICAL);
	for (frame_count=0;!proc->m_shutdown;) {
		
		if(bDone)
		{
			Sleep(30);
			continue;
		}

		// Wait for a new frame to become available, and lock it
		// so it can't be overwritten while we are processing and then displaying it
		if (((iSeqNum=cam->GrabWaitFrameEx(hGrabId,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy)) >= 0)
			&& !proc->m_shutdown) {
			old_time = last_time;
			theapp->m_iCap->GetGrabStats(hGrabId,&stats);
			m_trigProp->m_nNumMissed = stats.NumberOfFramesMissed;
			m_trigProp->m_nNumLost = stats.NumberOfFramesLost;

			last_time = theapp->m_iCap->m_os->GetSystimeMillisecs();
			m_trigProp->m_nTriggers++;
			if (frame_count > 0) {
				deltaTime = last_time - old_time;
				totalTime += deltaTime;
				if (deltaTime > m_trigProp->m_maxTime)
					m_trigProp->m_maxTime = deltaTime;
				if (deltaTime < m_trigProp->m_minTime)
					m_trigProp->m_minTime = deltaTime;
				m_trigProp->m_avgTime = totalTime / frame_count;
				m_trigProp->m_dwLastInterval = deltaTime;
			}
			

			// Update the address associated with the image source to point to the frame
			// we just processed
			proc->m_imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);

				
			for (i = m_trigProp->m_nVerifyStart; i < m_trigProp->m_nVerifyEnd; i++)
			{
				if (pHostBuffFrame [i * m_areaDx + j ] < m_trigProp->m_nVerifyThreshold)
					GoodImage = FALSE;					
			}

			if (GoodImage)
				m_trigProp->m_nVerifyGood++;
			else
				m_trigProp->m_nVerifyBad++;
				
//			proc->m_imgConn->Display();



			frame_count++;
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(hGrabId, iSeqNum);
		}

		// check for the number of images acquired
		if (!(m_trigProp->m_bContinuous))
		{
			if (m_trigProp->m_iImagesNum == 1)
			{
				deltaTime = last_time - singl_img_time;
				m_trigProp->m_maxTime = deltaTime;
				m_trigProp->m_minTime = deltaTime;
				m_trigProp->m_dwLastInterval = deltaTime;
				m_trigProp->m_avgTime = deltaTime;
			}
				if (m_trigProp->m_nTriggers == m_trigProp->m_iImagesNum)
				{
					bDone = TRUE;
					::PostMessage(m_trigProp->m_hWnd, UM_KILLME, 0, 0);					
				}
		}
	}
	::SetThreadPriority(GetCurrentThread() , THREAD_PRIORITY_NORMAL);
	cam->Freeze(hGrabId);
	if (pVixnEOF) {
		pVixnEOF->m_iSoftTrig = 0;
		delete pVixnEOF;
	}
	proc->m_bDisplay = FALSE;
	WaitForSingleObject(proc->m_hDisplayThread, INFINITE);
	CloseHandle(proc->m_hDisplayThread);

	if(proc->m_imgConn)
		delete proc->m_imgConn;
	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);	
	

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CTrigGrabDlg *parent)
{
	DWORD id;
	m_parent	= parent;
	m_shutdown	= FALSE;
	m_bDisplay = FALSE;
	m_bNewFrame = FALSE;
	m_imgConn = 0;
	m_hthread	= CreateThread(
						NULL,				// address of thread security attributes
						(DWORD) 0x10000,	// initial thread stack size, in bytes
						TriggerThread,		// address of thread function
						(LPVOID) this,		// argument for new thread
						0x0,				// creation flags
						&id);				// address of returned thread identifier
}


CTrgThrd::~CTrgThrd()
{
	// Tell the trigger thread to shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject(m_hthread, INFINITE);
	CloseHandle(m_hthread);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Use End of Frame Interrupt
CVixnEOF::CVixnEOF(PCParentMod pMod) : CVixn(pMod,  BDT_INTR_EOFRM)
{
	m_intrCount = 0;
	m_deltaTime = 0;
	m_iSoftTrig = 1;
	
}

CVixnEOF::~CVixnEOF()
{

}

BOOL CVixnEOF::VixnMain()
{
	m_deltaTime = ReadTimeMicro();


	m_intrCount++;
	return TRUE;
}