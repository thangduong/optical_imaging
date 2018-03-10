/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/seqsnap/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 10/25/03 9:20a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "TrgThrd.h"
#include <windowsx.h>
#include "TrigPro.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <Vixni.h>

class CVixnEOF : public CVixn  
{
public:

	int			m_iModId;
	int			m_iSoftTrig;
	CVixnEle	m_intrCount;
	CVixnEle	m_deltaTime;
	CVixnEle	m_modId;

	virtual BOOL VixnMain();

	CVixnEOF(PCParentMod pMod, int iSoftTrig=1);
	virtual ~CVixnEOF();
};

// Use End of Frame Interrupt
CVixnEOF::CVixnEOF(PCParentMod pMod, int iSoftTrig) : CVixn(pMod,  LNK_INTR_VB)
{
	m_intrCount = 0;
	m_deltaTime = 0;
	m_iSoftTrig = iSoftTrig;
	
}

CVixnEOF::~CVixnEOF()
{

}

BOOL CVixnEOF::VixnMain()
{
	m_deltaTime = ReadTimeMicro();

	// Generate software triggers as long as needed and immediately after the EOF interrupt
	// NB: m_iSoftTrig is a DWORD, not a CVixnEle variable, so the following statements which
	// test m_iSoftTrig are used to affect a runtime conditional compilation of the Vixn code.
	if(m_iSoftTrig == 1)
	{
		WriteReg(LNK_SWTRIG0_32, 1, VIXN_PARENT_MOD);
	}
	else if(m_iSoftTrig == 2)
	{
		WriteReg(LNK_SWTRIG1_32, 1, VIXN_PARENT_MOD);
	}

	m_intrCount++;
	return TRUE;
}


#define FRAMES_IN_HOSTBUFF 5

const char *PIPMessage = "End of Part-in-Place Image";

// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *)owner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_parent->m_vparent;
	CImgConn *imgconn;
	BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD m_areaDx;	// DX of the image area being processed
	DWORD m_areaDy;  // DY of the image area being processed
	DWORD last_time,old_time;
	DWORD frame_count;
	DWORD deltaTime;
	DWORD totalTime;
	BYTE *pHostBuffFrame;
	CICamera *cam=theapp->m_cam;
	int iSeqNum;
	CTrgGrab *m_trigProp = proc->m_parent->m_trigProp;
	CAM_ATTR attr;
	DWORD AcquiredDy;
	HIFCGRAB grabID;
	GRAB_EXT_ATTR ExtendedAttr;
	CVixnEOF *pVixnEOF = NULL;


	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	IFC_BAYER_FILTER_TYPE bayer = (IFC_BAYER_FILTER_TYPE)(DWORD)theapp->m_cam->GetAcqParam(P_BAYER_FILTER); 
	DWORD bayerFlagMap[] = {0,IFC_BAYER_GB_RG_FLAG, IFC_BAYER_GB_RG_DEZIPPER_FLAG, 0, 
		IFC_BAYER_BG_GR_DEZIPPER_FLAG, IFC_BAYER_BG_GR_FLAG, IFC_BAYER_GB_RG_GOLD_EAGLE_FLAG, 0, IFC_BAYER_BG_GR_GOLD_EAGLE_FLAG};
	DWORD imgConnFlags= bayerFlagMap[bayer];

	imgconn = new CImgConn(m_imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight,(WORD)attr.dwBitsPerPixel, view->m_hWnd, attr.color, imgConnFlags);
	imgconn->GetSrc()->SetBayerExtAttr(cam);

	// set board in mode: grab into host circular buffer

	grabID=cam->Grab(0,m_imgBuf, FRAMES_IN_HOSTBUFF);
	Sleep(20);

	if (m_trigProp->m_continuousSWTrig &&
		(  m_trigProp->m_startEvent == LNK_TMODE_SWTRIG0
		|| m_trigProp->m_startEvent == LNK_TMODE_SWTRIG1)) {
		pVixnEOF = new CVixnEOF(theapp->m_iCap, 1+m_trigProp->m_startEvent - LNK_TMODE_SWTRIG0);
		pVixnEOF->Create();
		// Kickoff the software trigger chain
		cam->SetAcqParam(P_GEN_SW_TRIGGER,0,0);
	}

	totalTime = 0;
	m_trigProp->m_maxTime = 0;
	m_trigProp->m_minTime = 1000;
	m_trigProp->m_avgTime = 0;
	last_time = 0;
	for (frame_count=0;!proc->m_shutdown;) {

		// Wait for a new frame to become available, and lock it
		// so it can't be overwritten while we are processing and then displaying it
		if (((iSeqNum=cam->GrabWaitFrameEx(grabID,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy,NULL,&ExtendedAttr)) >= 0)
			&& !proc->m_shutdown) {
			old_time = last_time;
			last_time = theapp->m_iCap->m_os->GetSystimeMillisecs();
			if (frame_count > 0) {
				deltaTime = last_time-old_time;
				totalTime += deltaTime;
				if (deltaTime > m_trigProp->m_maxTime)
					m_trigProp->m_maxTime = deltaTime;
				if (deltaTime < m_trigProp->m_minTime)
					m_trigProp->m_minTime = deltaTime;
			}
			// Update the address associated with the image source to point to the frame
			// we just processed
			imgconn->GetSrc()->SetBufferAddr(pHostBuffFrame);
			// Display the  frame in our client window
			if (AcquiredDy < m_areaDy) {
				memset(pHostBuffFrame + m_areaDx * AcquiredDy * attr.dwBytesPerPixel,0,
					m_areaDx * (m_areaDy-AcquiredDy) * attr.dwBytesPerPixel);
			}
			imgconn->Display();
			frame_count++;
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(grabID,iSeqNum);
			if (AcquiredDy < m_areaDy) {
				HDC hdc=::GetDC(view->m_hWnd);
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc,0x00ff0000);
				TextOut(hdc,20,AcquiredDy,PIPMessage,strlen(PIPMessage));
				::ReleaseDC(view->m_hWnd,hdc);
			}
		}
	}

	if (frame_count > 1)
		m_trigProp->m_avgTime = totalTime / (frame_count-1);
	cam->Freeze(grabID);
	delete imgconn;
	if (pVixnEOF) {
		pVixnEOF->m_iSoftTrig = 0;
		delete pVixnEOF;
	}

	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CTrgSheet *parent)
{
	DWORD id;
	m_parent = parent;
	m_shutdown = FALSE;
	m_hthread = CreateThread(
			NULL,                	// address of thread security attributes
			(DWORD)0x10000,       	// initial thread stack size, in bytes
			TriggerThread,            // address of thread function
			(LPVOID)this,     // argument for new thread
			0x0,                   	// creation flags
			&id );                  // address of returned thread identifier
}


CTrgThrd::~CTrgThrd()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	// Tell the trigger thread to shutdown
	m_shutdown = TRUE;


	// Wait for the thread to terminate
	WaitForSingleObject (m_hthread,INFINITE);
	CloseHandle(m_hthread);
}




