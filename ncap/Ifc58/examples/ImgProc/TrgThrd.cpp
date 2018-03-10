/******************************************************************************
 *
 * MODULE
 *    TrgThrd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/ImgProc/TrgThrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 12/23/99 8:51a $
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
#include "ImgProc.h"
#include "TrgThrd.h"
#include <windowsx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

template <class T> void LineReverse( T& pHostBuffFrame, int dwAreaDx, int dwAreaDy)
{
	int i,j;
	DWORD dwBytesPerLine = dwAreaDx * sizeof(T);
	
	for(j=0; j < dwAreaDy; j++)
	{
		T *pSrc;
		T *pTarget;
		T tVal;
		pSrc    = (T*)((DWORD)(&pHostBuffFrame) + j*(int)dwBytesPerLine);
		pTarget = (T*)((DWORD)pSrc + dwBytesPerLine - sizeof(T));
		
		for(i=0; i <  dwAreaDx/2 ; i++)
		{
			tVal = *pSrc;
			*pSrc++ = *pTarget;
			*pTarget-- = tVal;
		}
	}	
}



// This is the image processing and display thread
DWORD WINAPI TriggerThread(LPVOID owner)
{
	CTrgThrd *proc = (CTrgThrd *) owner;
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();	
	CImgConn *imgConn = NULL;
	CICamera *cam = theApp->m_cam;
	BYTE *imgBuf = NULL;	// Memory space which is the destination of the IFC grab operation
	DWORD dwAreaDx;			// DX of the image area being processed
	DWORD dwAreaDy;			// DY of the image area being processed
	DWORD dwFrameSize;
	DWORD dwBytesPerLine;
	BYTE *pHostBuffFrame;
	DWORD *pdwHostBuffFrame;
	DWORD *pdwBuf;
	int iSeqNum;
	int iInc;

	DWORD AcquiredDy;

	// TODO: Set your particular trigger parameters

	CAM_ATTR attr;
	cam->GetAttr(&attr);
	dwAreaDx = theApp->m_dwWidth[proc->m_ID];
	dwAreaDy = theApp->m_dwHeight[proc->m_ID];
	dwBytesPerLine = dwAreaDx * attr.dwBytesPerPixel;
	iInc = (int) attr.dwBytesPerPixel;
	dwFrameSize = dwAreaDy * dwBytesPerLine;

	SetThreadPriority(GetCurrentThread() , THREAD_PRIORITY_BELOW_NORMAL);


	imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED, dwFrameSize * FRAMES_IN_HOSTBUFF);

	if(!imgBuf)
	{
		::SendMessage(proc->m_parent->m_hWnd, ID_MSG_ALLOCERROR, 0, 0);
	}

	if(cam->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED)
	{
		imgConn = IfxCreateImgConn(imgBuf,(WORD)dwAreaDx,(WORD)dwAreaDy,(WORD)attr.dwBitsPerPixel,
									proc->m_parent->m_hWnd, attr.color, IFC_DIB_SINK, NULL,
									ICAP_INTR_EOF);
	}
	else
	{
		imgConn = IfxCreateImgConn(imgBuf,(WORD)dwAreaDx,(WORD)dwAreaDy,(WORD)attr.dwBitsPerPixel,
									proc->m_parent->m_hWnd, attr.color, IFC_DIB_SINK, NULL,
									ICAP_INTR_VB);
	}

	CDC* pDC = proc->m_parent->GetDC();
	if((DWORD)pDC->GetDeviceCaps(HORZRES) != theApp->m_dwWidth[proc->m_ID] || (DWORD)pDC->GetDeviceCaps(VERTRES) != theApp->m_dwHeight[proc->m_ID])
	{
		CImgSink *imgSink = imgConn->GetSink();
		imgSink->ResizeWindow();
	}
	proc->m_parent->ReleaseDC(pDC);


	HIFCGRAB GrabID = cam->Grab(0, imgBuf, FRAMES_IN_HOSTBUFF, IFC_INFINITE_FRAMES);

	BYTE* prevFrame = (BYTE*) GlobalAllocPtr(GMEM_FIXED, dwFrameSize);
	BYTE* pByte = NULL;

	if(!prevFrame)
	{
		::PostMessage(proc->m_parent->m_hWnd, ID_MSG_ALLOCERROR, 1, 0);
	}
	else
	{
		pByte = (BYTE*) GlobalAllocPtr(GMEM_FIXED, dwFrameSize);

		if(!pByte)
		{
			::PostMessage(proc->m_parent->m_hWnd, ID_MSG_ALLOCERROR, 1, 0);
			GlobalFreePtr(prevFrame);
		}
	}


	int i;

	memcpy(prevFrame, imgBuf, dwFrameSize);

	for(;!proc->m_shutdown;)
	{
		if(((iSeqNum=cam->GrabWaitFrameEx(GrabID, &pHostBuffFrame, IFC_WAIT_NEWER_FRAME,500,TRUE,&AcquiredDy)) >= 0)
			&& !proc->m_shutdown)
		{
			if(proc->m_parent->m_bInvert)
			{
				pdwHostBuffFrame = (DWORD*)pHostBuffFrame;
				pdwBuf = (DWORD*)((DWORD)pHostBuffFrame + dwFrameSize);
				while(pdwHostBuffFrame < pdwBuf)
				{
					*pdwHostBuffFrame++ ^= 0xffffffff;
				}
			}

			if(proc->m_parent->m_bDelta && prevFrame && pByte)
			{
				memcpy(pByte, pHostBuffFrame, dwFrameSize);

				for(i=0; i<(int) dwFrameSize; i+=iInc)
				{
					if(memcmp(&pHostBuffFrame[i], &prevFrame[i], iInc) == 0)
					{
						memset(&pHostBuffFrame[i], 0x00, iInc);
					}
				}

				memcpy(prevFrame, pByte, dwFrameSize);
			}

			if(proc->m_parent->m_bMirror)
			{
				switch (iInc) {
				case 1:
					LineReverse(pHostBuffFrame[0],dwAreaDx,dwAreaDy);
				break;

				case 2:
					LineReverse(((WORD*)pHostBuffFrame)[0],dwAreaDx,dwAreaDy);
				break;

				default:
					LineReverse(((DWORD*)pHostBuffFrame)[0],dwAreaDx,dwAreaDy);
				break;
				}
			}

			// Update the address associated with the image source to point to the frame
			// we just processed
			imgConn->GetSrc()->SetBufferAddr(pHostBuffFrame);

			// Display the  frame in our client window
			imgConn->Display();

			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(GrabID, iSeqNum);
		}
	}

	cam->Freeze(GrabID);

	if(imgConn)
	{
		delete imgConn;
	}
	
	if(imgBuf)
	{
		GlobalFreePtr(imgBuf);
	}

	if(prevFrame)
	{
		GlobalFreePtr(prevFrame);
	}

	if(pByte)
	{
		GlobalFreePtr(pByte);
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrgThrd::CTrgThrd(CImgProcView *parent, int ID)
{
	DWORD thread_id;

	m_ID = ID;
	m_parent    = parent;
	m_shutdown  = FALSE;

	m_hthread = CreateThread(
			NULL,                	// address of thread security attributes
			(DWORD)0x10000,       	// initial thread stack size, in bytes
			TriggerThread,            // address of thread function
			(LPVOID)this,     // argument for new thread
			0x0,                   	// creation flags
			&thread_id );                  // address of returned thread identifier
}


CTrgThrd::~CTrgThrd()
{
	CImgProcApp *theapp = (CImgProcApp*) AfxGetApp();	
	// Tell the trigger thread to m_shutdown
	m_shutdown = TRUE;

	// Wait for the thread to terminate
	WaitForSingleObject(m_hthread, INFINITE);
	CloseHandle(m_hthread);
}

