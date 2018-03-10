// ImageDIff.cpp : Implementation of CImageDIff
#include "stdafx.h"
#include "ImgDifOb.h"
#include "ImageDIff.h"


#include <VnBase.h>
#include <ProcThrd.h>
#include <VnVidSrc.h> 

/////////////////////////////////////////////////////////////////////////////
// CImageDIff


BOOL ImgDifferenceFunc( BYTE *img1, BYTE *img2, VS_INODE_IMG_ATTR *imgAttr)
{
	DWORD x,y;
	DWORD numDiffPixels=0;	
	BYTE *i1=img1;
	BYTE *i2=img2;
	DWORD inc= 2*imgAttr->dwBytesPerPixel;
	DWORD stride=imgAttr->dwBytesPerPixel * imgAttr->dwWidth;
	
	if (imgAttr->dwBytesPerPixel==2) {
		i1++;
		i2++;
	}
	for(y=0; y < imgAttr->dwHeight/2; y++) {
		for(x=0; x < imgAttr->dwWidth/2; x++) {
			if ( abs((int)*i1 - (int)*i2) > 6  )
				numDiffPixels++;
			i1+=inc;
			i2+=inc;
		}	
		i1 += stride;
		i2 += stride;
	}	

	numDiffPixels *= 4; // compensate for sub-sampling
	// Deem images to be different if > 5% of pixels are significantly different
	return (numDiffPixels > (imgAttr->dwWidth*imgAttr->dwHeight/20));
}

void IVSAPI MyDerefHandler(CProcThread *threadObj, DWORD OutputId, HBYREFELE deRefHandle)
{
	threadObj->ReleaseImage((BYTE*)deRefHandle);
}




STDMETHODIMP CImageDIff::ThreadFunction(HCProcThread thrdObj)
{

	CProcThread *threadObj = (CProcThread *)thrdObj;

	VS_INODE_IMG_ATTR imgAttr;
	pBYTE frameAddr;
	pBYTE oldFrame;
	IVideoSrc *vidSrc = threadObj->GetVideoSrc();
	BOOL enQueued;
	threadObj->WaitInputConnected(5000);

	HVSEVENT shutdownEvent=threadObj->GetShutdownInputEvent();

	threadObj->SetDeRefHandler(MyDerefHandler);

	threadObj->WaitNewImage(&imgAttr,&oldFrame,5000,shutdownEvent);

	while (!threadObj->m_shutdown) {
		if (threadObj->WaitNewImage(&imgAttr,&frameAddr,5000,shutdownEvent)) {

			enQueued=FALSE;

			if (ImgDifferenceFunc(frameAddr,oldFrame,&imgAttr)) {
				enQueued = threadObj->Enqueue(0,&imgAttr,oldFrame, 
					VS_FRAME_JPEG_ENCODE,(HBYREFELE)oldFrame);
			}
			if (!enQueued) {
				// If enqueue failed release image immediately
				threadObj->ReleaseImage(oldFrame);
			}
			oldFrame = frameAddr;
		}
	}

	return S_OK;
}

main() {return 0;}
