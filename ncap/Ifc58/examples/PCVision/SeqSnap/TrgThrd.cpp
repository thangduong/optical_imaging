/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVision/Seqsnap/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 2/23/01 2:00p $
 *
 * ABSTRACT
 *    PCVision Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
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


// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *) owner;
	CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();	
	CSeqsnapView *view = proc->m_parent->m_vParent;
	CImgConn *imgconn;
	BYTE *imgBuf;				// Memory space which is the destination of the ITX grab operation
	DWORD m_areaDx;				// DX of the image area being processed
	DWORD m_areaDy;				// DY of the image area being processed
	DWORD last_time,old_time;
	DWORD frame_count;
	DWORD deltaTime;
	DWORD totalTime;
	
	CICamera *cam = theapp->m_cam;
	CPCVision* pMod = (CPCVision*) cam->m_parent;
	HTRIGOP hTrigOp = NULL;
	
	CTrigGrabDlg* m_trigProp = proc->m_parent;
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	
	imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel);
	imgconn = new CImgConn(imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight,(WORD)attr.dwBitsPerPixel, view->m_hWnd);
	
	
	totalTime = 0;
	last_time = 0;
	m_trigProp->m_maxTime = 0;
	m_trigProp->m_minTime = 1000;
	m_trigProp->m_avgTime = 0;
	
	if((hTrigOp = pMod->StartTrigOps(cam)) != NULL) {
		
		pMod->TrigSnap(hTrigOp);
		if(m_trigProp->m_iTrigSrc == IFC_SOFT_TRIG)
			cam->SetAcqParam(P_GEN_SW_TRIGGER, 1);

		for(frame_count=0; !proc->m_shutdown;)
		{
			// Wait for the triggered acqisition frame to finish
			pMod->WaitTrig(hTrigOp, 1000);
						
			// Enable an image snap to commence upon receiving a trigger
			// This is so we won't miss a trigger which happens while reading the frame just acquired
			pMod->TrigSnap(hTrigOp);
			
			
			if(m_trigProp->m_iTrigSrc == IFC_SOFT_TRIG)
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 1);
			
			old_time = last_time;
			last_time = theapp->m_iCap->m_os->GetSystimeMillisecs();
			
			if(frame_count > 0)
			{
				deltaTime = last_time - old_time;
				totalTime += deltaTime;
				
				if(deltaTime > m_trigProp->m_maxTime)
					m_trigProp->m_maxTime = deltaTime;
				
				if(deltaTime < m_trigProp->m_minTime)
					m_trigProp->m_minTime = deltaTime;
				
				m_trigProp->m_avgTime = totalTime / frame_count;
			}
			
			pMod->TrigRead(hTrigOp, 0, 0, (short) m_areaDx, (short) m_areaDy, imgBuf);
			imgconn->Display();
			frame_count++;
		}
	}
	
	pMod->WaitTrig(hTrigOp, 0);
	pMod->StopTrigOps(hTrigOp);
	
	delete imgconn;
	cam->Freeze();
	
	if(imgBuf)
	{
		GlobalFreePtr(imgBuf);
	}
	
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

