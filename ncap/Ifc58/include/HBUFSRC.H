/******************************************************************************
 *
 * MODULE   
 *		hbufsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/HBUFSRC.H $
 *		$Revision: 1.1 $
 *		$Modtime: 10/15/04 10:29a $
 *
 * ABSTRACT 
 *	Header file for host buffer image source.
 *
 * TECHNICAL NOTES 
 * 
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _HBUFSRC_H
#define _HBUFSRC_H

#include <ifcstd.h>
#include <dsptype.h>
#include <camera.h>
#include <imgsrc.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CHBufImgSrc : public CImgSrc
{
//member functions
public:
	CHBufImgSrc(BYTE *pImgBuffer, CAM_ATTR * pCamAttr, DWORD dwOptions=0);
	CHBufImgSrc(BYTE *pImgBuffer, WORD wFrameWidth, WORD wFrameHeight, WORD wImgBitsPP = 8,IFC_COLOR eColor=IFC_MONO, WORD wxAoiStart=0, WORD wyAoiStart=0, WORD wAoiWidth=0, WORD wAoiHeight=0, DWORD dwOptions=0 );
	~CHBufImgSrc();
	virtual BOOL Create();
	virtual BYTE *GetBufferAddr(DWORD options=0);
	virtual void SetBufferAddr(BYTE *pBuffer);

private:

//attributes
public:

private:
	BYTE *m_pbyHostImageBuffer;
	BYTE *m_iBuffer;


};
#endif

#endif //ifndef _HBUFSRC_H
