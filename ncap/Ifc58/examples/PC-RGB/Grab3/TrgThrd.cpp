/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/Grab3/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 9/24/99 4:27p $
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
#include <pcrcam.h>

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
	CPCRCam *cam=(CPCRCam*)theapp->m_cam;
	BYTE *imgBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD areaDx;	// DX of the image area being processed
	DWORD areaDy;  // DY of the image area being processed
	DWORD frameCount;
	BYTE *pHostBuffFrame;
	int iSeqNum;
	DWORD AcquiredDy;
	HIFCGRAB grabID; 
	IFC_COLOR colorPlane;
		
	CAM_ATTR attr;
	cam->GetAttr(&attr);
	IFC_AOI_DESC aoiDesc;

	switch (proc->m_parent->m_viewID%3) {
	case 0:
		colorPlane = IFC_RED;
		break;
	case 1:
		colorPlane = IFC_GREEN;
		break;
	case 2:
		colorPlane = IFC_BLUE;
		break;
	}

	cam->GetPlanarAoi(colorPlane,&aoiDesc);
/*
	aoiDesc.x += 8;
	aoiDesc.dx -= 64;
	aoiDesc.dy -= 203;
	aoiDesc.y += 40;
*/ /*
	aoiDesc.x = 64;
	aoiDesc.dx = 1000;
	aoiDesc.dy -= 203;
	aoiDesc.y += 40;
*/

	areaDx = aoiDesc.dx;
	areaDy = aoiDesc.dy;
	imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,areaDx * areaDy * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
	imgConn = IfxCreateImgConn(imgBuf,(WORD)areaDx,(WORD)areaDy,(WORD)attr.dwBitsPerPixel, proc->m_parent->m_hWnd);
	CImgSink *imgSink=imgConn->GetSink();
	imgSink->ResizeWindow();
	
	grabID = cam->Grab(0,imgBuf, FRAMES_IN_HOSTBUFF,&aoiDesc);
	
	for (frameCount=0;!proc->m_shutdown;) {
		
		if (((iSeqNum=cam->GrabWaitFrameEx(grabID,&pHostBuffFrame,IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy)) >= 0)
			&& !proc->m_shutdown) {
			
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

