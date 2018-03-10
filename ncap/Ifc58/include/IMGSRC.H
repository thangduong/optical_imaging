/******************************************************************************
 *
 * MODULE   
 *		imgsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IMGSRC.H $
 *		$Revision: 1.1 $
 *		$Modtime: 10/15/04 10:26a $
 *
 * ABSTRACT 
 *	Header file for image source.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#ifndef	_IMGSRC_H
#define _IMGSRC_H

#include <iobject.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <camera.h>
#include <ifcclass.h>
#include <ClrSpace.h>


/////////////////////////////////////////////////////////////////////
//CImgSrc
//////////////////////////////////////////////////////////////////////

#define IFC_IMGSRC_OPT_PIX_LEAST_SIG	1 // pixel bits are in the least significant position of a WORD
#define IFC_IMGSRC_OPT_BAYER_GB_RG		2
#define IFC_IMGSRC_OPT_BAYER_BG_GR		4
#define IFC_IMGSRC_OPT_BAYER_GB_RG_DEZIPPER		8
#define IFC_IMGSRC_OPT_BAYER_BG_GR_DEZIPPER		0x10
#define IFC_IMGSRC_OPT_BAYER_GB_RG_GOLD_EAGLE	0x20
#define IFC_IMGSRC_OPT_BAYER_BG_GR_GOLD_EAGLE	0x40



#define IFC_IMGSRC_GB_OPT_YCRCB_DESIRED	1
#define IFC_IMGSRC_GB_OPT_WAIT_NEWER	2



#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CImgSrc : public CIobject
{
friend class CImgConn;
friend class CCamImgSrc;
friend class CHBufImgSrc;
friend class CSwOverlay;

//member functions
public:
	CImgSrc(WORD wFrameWidth, WORD wFrameHeight, WORD wImgBitsPP = 8,IFC_COLOR color=IFC_MONO, WORD wxAoiStart=0, WORD wyAoiStart=0, WORD wAoiWidth=0, WORD wAoiHeight=0, DWORD dwOptions=0 );
	virtual ~CImgSrc();
	virtual BOOL Create();

	virtual const WORD FrameWidth() const ;
	virtual const WORD FrameHeight() const ;
	virtual void SetAoiPos(const WORD wxAoiStart, const WORD wyAoiStart);
	virtual void GetAoiPos(WORD *pwxAoiStart, WORD *pwyAoiStart) const ;
	virtual WORD GetAoiStartX() const ;
	virtual WORD GetAoiStartY() const ;
	WORD GetWidth() const;
	WORD GetHeight() const;
	virtual WORD GetLinePitch () const;
	WORD GetBitsPP() const;
	WORD GetRawBitsPP() const;
	IFC_COLOR GetColor() const;
	SRC_KIND GetKind() const;
	virtual CICamera *GetCamera() const;
	virtual BYTE *GetBufferAddr(DWORD options=0);

	virtual void SetBufferAddr(BYTE *pBuffer);
	virtual IFC_BAYER_FILTER_TYPE GetBayer() const;
	DWORD SetOptions(DWORD dwOptions);
	void SetBayerExtAttr(IFC_BAYER_EXT_ATTR *extAttr);
	void SetBayerExtAttr(CICamera *cam);
	IFC_BAYER_EXT_ATTR *GetBayerExtAttr(IFC_BAYER_EXT_ATTR *extAttr);
	DWORD SetTransform(IFC_TRANSFORM_TYPE eTransform);


	
private:
	void SetBitsPP(const WORD BitsPP);
	void SetAlignmentValues(const WORD wAOiStart, const WORD wAOIWidth, const WORD wFrameWidth);


//attributes
public:

	DWORD m_dwOptions;

private:
	SRC_KIND m_SrcKind;
	WORD m_wImgBitsPP;
	WORD m_wRawImgBitsPP;

	WORD m_wFrameWidth;
	WORD m_wFrameHeight;
	WORD m_wxAoiStart;
	WORD m_wyAoiStart;
	WORD m_wAoiWidth;
	WORD m_wAoiHeight;
	WORD m_wFrameLinePitchBytes;
	WORD m_wAOIAlignStartX;	
	WORD m_wAOIAlignWidth;	
	WORD m_wFrameAlignWidth;
	IFC_COLOR m_eColor;
	IFC_BAYER_FILTER_TYPE m_bayer;

	IFC_BAYER_EXT_ATTR m_bayerExtAttr;
	BOOL m_bayerAttrSet;
	IFC_TRANSFORM_TYPE m_eTransform;

};


IFC_EXT_API	CImgSrc * IfxCreateImgSrc(BYTE *pImgBuffer, CAM_ATTR * pCamAttr, DWORD dwOptions=0);
IFC_EXT_API	CImgSrc * IfxCreateImgSrc(BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP = 8,IFC_COLOR eColor=IFC_MONO,
									  WORD wxAoiStart=0, WORD wyAoiStart=0, WORD wAoiWidth=0, WORD wAoiHeight=0, DWORD dwOptions=0);
IFC_EXT_API	CImgSrc * IfxCreateImgSrc(CICamera *pCamera, WORD wxAoiStart=0, WORD wyAoiStart=0, WORD wAoiWidth=0, WORD wAoiHeight=0);
#endif

#endif // !defined(_IMGSRC_H)
