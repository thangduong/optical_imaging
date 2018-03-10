/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 10/10/03 11:38a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging, Inc.  All rights reserved.
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

const char *PIPMessage = "End of Part-in-Place Image";

// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *)owner;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapView *view = proc->m_parent->m_parent;
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
	CTrgGrab *m_trigProp = proc->m_parent;
	CAM_ATTR attr;
	DWORD AcquiredDy;
	HIFCGRAB grabID;
	GRAB_EXT_ATTR ExtendedAttr;
	BOOL genSWTrig=FALSE;

	if ( (DWORD)cam->GetAcqParam(P_FEN_ENABLE)==IFC_ENABLE)
		genSWTrig = (DWORD)cam->GetAcqParam(CL2_FRAME_TRIG_SRC) == CL2_SOFT_FRAME_TRIG;
	else
		genSWTrig = (DWORD)cam->GetAcqParam(CL2_VFRAME_TRIG_SOURCE) == CL2_SOFT_VFRAME_TRIG;

	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	IFC_BAYER_FILTER_TYPE bayer = (IFC_BAYER_FILTER_TYPE)(DWORD)theapp->m_cam->GetAcqParam(P_BAYER_FILTER); 
	DWORD bayerFlagMap[] = {0,IFC_BAYER_GB_RG_FLAG, IFC_BAYER_GB_RG_DEZIPPER_FLAG, 0, 
		IFC_BAYER_BG_GR_DEZIPPER_FLAG, IFC_BAYER_BG_GR_FLAG, IFC_BAYER_GB_RG_GOLD_EAGLE_FLAG, 0, IFC_BAYER_BG_GR_GOLD_EAGLE_FLAG};
	DWORD imgConnFlags = bayerFlagMap[bayer];

	imgconn = new CImgConn(m_imgBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight,(WORD)attr.dwBitsPerPixel, view->m_hWnd, attr.color, imgConnFlags);
	imgconn->GetSrc()->SetBayerExtAttr(cam);

	// For pixel sizes greater than 8 bits, the pixel bits are the least significant dwBitsPerPixel of a 16 bit WORD
	// So need to set option IFC_IMGSRC_OPT_PIX_LEAST_SIG
	if (attr.dwBitsPerPixel > 8 && attr.dwBitsPerPixel < 16)
		imgconn->GetSrc()->SetOptions(IFC_IMGSRC_OPT_PIX_LEAST_SIG);

	// set board in mode: grab into host circular buffer

	grabID=cam->Grab(0,m_imgBuf, FRAMES_IN_HOSTBUFF);
	Sleep(20);

	if (genSWTrig && m_trigProp->m_contiuouseSWTrig) {
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

			if (genSWTrig && m_trigProp->m_contiuouseSWTrig) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER,0,0);
			}

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
		else {
			if (genSWTrig && m_trigProp->m_contiuouseSWTrig) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER,0,0);
			}
		}
	}

	if (frame_count > 1)
		m_trigProp->m_avgTime = totalTime / (frame_count-1);
	cam->Freeze(grabID);
	delete imgconn;

	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CTrgGrab *parent)
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




