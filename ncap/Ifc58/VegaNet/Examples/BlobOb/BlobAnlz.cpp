// BlobAnlz.cpp : Implementation of CBlobAnlz
#include "stdafx.h"
#include "BlobOb.h"
#include "BlobAnlz.h"

#include <VnBase.h>
#include <ProcThrd.h>
#include <VnVidSrc.h> 



/////////////////////////////////////////////////////////////////////////////
// CBlobAnlz

CBlobAnlz::CBlobAnlz()
{
	m_pUnkMarshaler = NULL;
	m_minBlobArea = 20;
	m_maxBlobArea = 4000;

}

CBlobAnlz::~CBlobAnlz()
{

}

void IVSAPI MyDerefHandler(CProcThread *threadObj, DWORD OutputId, HBYREFELE deRefHandle)
{
	threadObj->ReleaseImage((BYTE*)deRefHandle);
}


DWORD IVSAPI LutBinarize(DWORD arg, DWORD * constants)
{
	DWORD pivot=constants[0];
	if (arg > pivot)
		return 255;
	else
		return 0;
}

void DoLutBinarize(IVideoSrc *vidSrc,DWORD pivot ) 
{
	double dwPixelSize;
	vidSrc->GetAcqParam(VSP_PIXEL_SIZE,&dwPixelSize,0);
	DWORD numEntries= (dwPixelSize < 16) ? 1UL << (DWORD)dwPixelSize:0x100;		

	vidSrc->SetLutFunction(VS_INPUT_LUT1,LutBinarize,&pivot,VS_LUT_INTELLI_WIDTH );
}


#define MAX_NUM_RLE_FEATURES 80000
#define MAX_NUM_BLOBS 0x10000


STDMETHODIMP CBlobAnlz::ThreadFunction(HCProcThread thrdObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CProcThread *threadObj = (CProcThread *)thrdObj;

	VS_INODE_IMG_ATTR imgAttr;
	pBYTE frameAddr;
	IVideoSrc *vidSrc = threadObj->GetVideoSrc();
	LPVS_RLE_FEATURE_DESC rleEncode;
	DWORD numRleFeatures;
	int numFilteredBlobs;
	int numBlobs;
	int i;
	VS_BLOB_DESC_LIST *blobList;
	VS_BLOB_DESC *blobs,*srcBlob,*dstBlob;
	BOOL enQueued;

	threadObj->WaitInputConnected(5000);

	HVSEVENT shutdownEvent=threadObj->GetShutdownInputEvent();

	threadObj->SetDeRefHandler(MyDerefHandler);


	if (vidSrc)
		DoLutBinarize(vidSrc,128);

	rleEncode = new VS_RLE_FEATURE_DESC[MAX_NUM_RLE_FEATURES];
	blobList = (VS_BLOB_DESC_LIST*)malloc(sizeof(VS_BLOB_DESC_LIST) + sizeof(VS_BLOB_DESC) * MAX_NUM_BLOBS);
	blobs = blobList->blobs;

	while (!threadObj->m_shutdown) {
		if (threadObj->WaitNewImage(&imgAttr,&frameAddr,5000,shutdownEvent)) {

			enQueued=FALSE;
			if (VsRleEncode(frameAddr,imgAttr.dwWidth,imgAttr.dwHeight,rleEncode,MAX_NUM_RLE_FEATURES,&numRleFeatures)) {
				numBlobs = MAX_NUM_BLOBS;
				VsBuildBlobs(imgAttr.dwWidth,imgAttr.dwHeight,numRleFeatures,rleEncode,numBlobs,blobs,imgAttr.dwHeight/3,TRUE);
				numFilteredBlobs=0;
				for (i=0,srcBlob=blobs,dstBlob=blobs; i < numBlobs; i++,srcBlob++) {
					if (srcBlob->area >= m_minBlobArea && srcBlob->area <= m_maxBlobArea) {
						*dstBlob++ = *srcBlob;
						numFilteredBlobs++;
					}
				}
				blobList->numBlobs = numFilteredBlobs;

				// The installed image DeRefHandler "MyDerefHandler" will automatically be invoked
				// when the enqueued image is no longer referenced. 
				enQueued = threadObj->Enqueue(0,&imgAttr,frameAddr, VS_FRAME_JPEG_ENCODE,(HBYREFELE)frameAddr,
					(BYTE*)blobList,sizeof(VS_BLOB_DESC_LIST) + sizeof(VS_BLOB_DESC) * numFilteredBlobs);
			}
			if (!enQueued) {
				// If enqueue failed release image immediately
				threadObj->ReleaseImage(frameAddr);
			}
		}
	}

	free (blobList);
	delete [] rleEncode;

	return S_OK;
}

STDMETHODIMP CBlobAnlz::SetBlobAreas(DWORD minArea, DWORD maxArea)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_minBlobArea = minArea;
	m_maxBlobArea = maxArea;

//	FILE *fp=fopen("blob.dat","wb+");
//	fprintf(fp,"\nmin = %d, max %d",minArea,maxArea);
//	fclose(fp);
	return S_OK;
}
