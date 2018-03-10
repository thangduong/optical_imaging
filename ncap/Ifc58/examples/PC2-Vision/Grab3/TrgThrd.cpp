/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/grab3/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/21/03 10:11a $
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
#include "Grab3.h"
#include "TrgThrd.h"
#include <windowsx.h>
#include <pv2cam.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define FRAMES_IN_HOSTBUFF 4


// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *)owner;
	CGrab3App *theapp=(CGrab3App*)AfxGetApp();	
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

	cam = (CP2VCam*)theapp->m_pMod->GetCam(proc->m_parent->m_viewID%3 + theapp->m_camBasePort);
	
	CAM_ATTR attr;
	cam->GetAttr(&attr);

	attr.dwBytesPerPixel=1;
	attr.dwBitsPerPixel=8;

	areaDx = attr.dwWidth;
	areaDy = attr.dwHeight;
	imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,areaDx * areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	imgConn = IfxCreateImgConn(imgBuf,(WORD)areaDx,(WORD)areaDy,(WORD)attr.dwBitsPerPixel, proc->m_parent->m_hWnd);
	CImgSink *imgSink=imgConn->GetSink();
	imgSink->ResizeWindow();

	
	// Note: When using grab option IFC_GOPT_PLANAR_INIT, CICamera::Grab must be called
	// to start 3 concurrent grabs on all 3 channels offered by one connector, the acquisition does not
	// actually start until the 3rd CICamera::Grab call is made.
	// Also note this option should only be used in conjunction with 
	// parameter P_PIXEL_COLOR set to IFC_RGB_PLANAR .
	grabID = cam->Grab(IFC_GOPT_PLANAR_INIT | IFC_GOPT_AUTO_FRAME_LOCK,imgBuf, FRAMES_IN_HOSTBUFF);
	
	if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG && proc->m_parent->m_viewID==2) {
		Sleep(33);
		cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}

	for (frameCount=0;!proc->m_shutdown;) {
		
		if (((iSeqNum=cam->GrabWaitFrameEx(grabID,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy)) >= 0)
			&& !proc->m_shutdown) {
			
			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG && proc->m_parent->m_viewID==2) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
			
			// Update the address associated with the image source to point to the frame
			// we just processed
			imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);
			// Display the  frame in our client window
			imgConn->Display();
			
			frameCount++;
			
			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(grabID,iSeqNum);
		}
		else {
			if (cam->GetAcqParam(P_TRIGGER_SRC)	== IFC_SOFT_TRIG && proc->m_parent->m_viewID==2) {
				cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
			}
			Sleep(20);
		}
		
	}
	cam->Freeze(grabID);
	delete imgConn;
	if (imgBuf)
		GlobalFreePtr(imgBuf);
	
	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CGrab3View *parent)
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
	CGrab3App *theapp=(CGrab3App*)AfxGetApp();	
	// Tell the trigger thread to m_shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject (hthread,INFINITE);
	CloseHandle(hthread);
}

