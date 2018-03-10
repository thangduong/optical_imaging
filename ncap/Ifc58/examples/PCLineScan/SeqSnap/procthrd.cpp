/******************************************************************************
 *
 * MODULE
 *    PROCTHRD.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/procthrd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/27/02 10:10a $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 * seqsnap.cpp : Defines the class behaviors for the application.
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


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

#define MAX_NUM_BLOBS 0x8000
#define CENTROID_WIDTH 3

static const COLORREF  syscolors[] = {
	RGB( 0x0 , 0x0 , 0x0 ),
	RGB( 0x0 , 0x0 , 0xff ),
	RGB( 0x0 , 0xff , 0x0 ),
	RGB( 0x0 , 0xff , 0xff ),
	RGB( 0xff , 0x0 , 0x0 ),
	RGB( 0xff , 0x0 , 0xff ),
	RGB( 0xff , 0xff , 0x0 ),
};

/////////////////////////////////////////////////////////////////////////////
// CProcessThread

// This is the image processing and display thread
DWORD WINAPI ProcessThread(LPVOID pOwner)
{
	CProcessThread *proc = (CProcessThread *)pOwner;
	return proc->ProcessThreadMember();
}


DWORD CProcessThread::ProcessThreadMember()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CImgConn *imgconn;
	BYTE *imgBuf;	// Memory space which is the destination of the ITX grab operation
	BYTE *rleBuf;	// Memory space which is the destination of the ITX grab operation
	DWORD areaDx;	// DX of the image area being processed
	DWORD areaDy;  // DY of the image area being processed
	float avgTime;
	DWORD start_time;
	DWORD frame_count;
	BYTE *DisplayBuf;
	int iSeqNum;
	CICamera *cam=theapp->m_cam;
	CAM_ATTR attr;
	HIFCGRAB grabID;
	DWORD numRleFeatures;
	DWORD i;
	CPCLFrame flexFrame;
	PCL_BLOB_DESC *blobs;
	int numBlobs=0;
    HDC hDC;
    CDC* cdc;
	PCL_BLOB_DESC *blob;
	int colorIndex;
	DWORD rleBufSize;
	
	blobs = new PCL_BLOB_DESC[MAX_NUM_BLOBS];
	// Get the current acquisition dimensions
	cam->GetAttr(&attr);
	areaDx = attr.dwWidth;
	areaDy = attr.dwHeight;
	imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,areaDx * areaDy * FRAMES_IN_HOSTBUFF);
	DisplayBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,areaDx * areaDy );

	rleBufSize = areaDx * areaDy * 2;

	rleBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,rleBufSize);
	imgconn = new CImgConn(DisplayBuf,(WORD)attr.dwWidth,(WORD)attr.dwHeight, 8, m_pView->m_hWnd,IFC_MONO,IFC_DIB_SINK|IFC_SW_OVERLAY);

	start_time = theapp->m_iCap->m_os->GetSystimeMillisecs();

	// Load RLE Tag LUTs so that only the Most Significant bit is used for Run encoding
	cam->LutPassMostSigBits(PCL_RLE_TAG_LUT0,LUT_INTELLI_WIDTH,1);
	cam->LutPassMostSigBits(PCL_RLE_TAG_LUT1,LUT_INTELLI_WIDTH,1);

	// set board in mode: grab into host circular buffer

	if (m_grabToFeatureRam)
		grabID=cam->Grab(PCL_GOPT_RLE_ENCODE,imgBuf, FRAMES_IN_HOSTBUFF);
	else
		grabID=cam->Grab(PCL_GOPT_RLE2FBUF_ENCODE,imgBuf, FRAMES_IN_HOSTBUFF);

	Sleep(20);


	for (frame_count=0;!m_bShutdown;) {

		// Wait for a new frame to become available, and lock it
		// some it can't be overwritten while we are processing and then displaying it
		if (((iSeqNum=theapp->m_iCap->GrabWaitRle(grabID,rleBuf,rleBufSize,IFC_WAIT_NEWER_FRAME,500,TRUE,&numRleFeatures)) >= 0)
			&& !m_bShutdown) {


	        hDC = imgconn->GetOverlayDC();
			if(hDC) {
				COLORREF color;
				DWORD blobWidth;
				cdc = CDC::FromHandle(hDC);
				for (i=0,blob=blobs; i < (DWORD)numBlobs; i++,blob++) { 
					blobWidth = 1+blob->x1-blob->x0;
					if (blob->area >= m_minBlobArea && blob->area <= m_maxBlobArea) {
						cdc->Draw3dRect(blob->x0,blob->y0,blobWidth,1+blob->y1-blob->y0,syscolors[0],syscolors[0]);
						cdc->Draw3dRect(blob->x_cent-CENTROID_WIDTH,blob->y_cent-CENTROID_WIDTH,2*CENTROID_WIDTH,2*CENTROID_WIDTH,syscolors[0],syscolors[0]);
					}
				}

				numBlobs = MAX_NUM_BLOBS;
				theapp->m_iCap->BuildBlobs(areaDx,areaDy,numRleFeatures,(LPPCL_RLE_FEATURE_DESC)rleBuf,numBlobs,blobs,areaDy/3,TRUE);

				DWORD totalBlobArea=0;
				DWORD numPassingBlobs=0;
				for (colorIndex=0,i=0,blob=blobs; i < (DWORD)numBlobs; i++,blob++) { 
					blobWidth = 1+blob->x1-blob->x0;
					if (blob->area >= m_minBlobArea && blob->area <= m_maxBlobArea) {
						totalBlobArea += blob->area;
						numPassingBlobs++;
						color = syscolors[3];
//						color = syscolors[colorIndex++%6 + 1];
						cdc->Draw3dRect(blob->x_cent-CENTROID_WIDTH,blob->y_cent-CENTROID_WIDTH,2*CENTROID_WIDTH,2*CENTROID_WIDTH,color,color);
						cdc->Draw3dRect(blob->x0,blob->y0,blobWidth,1+blob->y1-blob->y0,color,color);
					}					
				}
				if (numPassingBlobs > 0)
					m_avgBlobArea = totalBlobArea / numPassingBlobs;
				m_numDetectedBlobs = numPassingBlobs;
				cdc->DeleteTempMap();
				imgconn->ReleaseOverlayDC(hDC);
			}

			theapp->m_iCap->DecodeRle( (LPPCL_RLE_FEATURE_DESC)rleBuf,numRleFeatures,areaDx,areaDx*areaDy,DisplayBuf);

			if (m_saveTifFile) {
				char tifFile[80];				
				sprintf(tifFile,"img%d.tif",frame_count);
				IfxWriteImgFile(tifFile,DisplayBuf,areaDx,areaDy,8);
			}

			// Release the frame back into the active circular acquistion buffer
			cam->GrabRelease(grabID,iSeqNum);

			// Display the  frame in our client window
			imgconn->Display();
			Sleep(0);
			frame_count++;
		}
	}

	if (frame_count > 0) {
		avgTime = (float)(theapp->m_iCap->m_os->GetSystimeMillisecs() - start_time) / (float)frame_count;
//		theapp->m_iCap->m_os->WriteConsole("\nAverage acquire time was %f milliseconds",avgTime);
	}
	// Stop the grab operation
	cam->Freeze(grabID);


	delete imgconn;

	if (rleBuf)
		GlobalFreePtr(rleBuf);
	if (imgBuf)
		GlobalFreePtr(imgBuf);
	if (DisplayBuf)
		GlobalFreePtr(DisplayBuf);

	delete [] blobs;
	return 0;
}



CProcessThread::CProcessThread(CSeqsnapView *thread_view,BOOL saveTifFile)
{
	DWORD id;
	m_bShutdown = FALSE;
	m_pView = thread_view;
	m_saveTifFile = saveTifFile;
	m_minBlobArea = 10;
	m_maxBlobArea = 30;
	m_avgBlobArea = 1;
	m_numDetectedBlobs = 0;
	m_grabToFeatureRam=TRUE;

	m_hThread = CreateThread(
					NULL,					// address of thread security attributes
					(DWORD)0x80000,			// initial thread stack size, in bytes
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






