/******************************************************************************
 *
 * MODULE   
 *		swovlsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/SWOVLSRC.H $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:39a $
 *
 * ABSTRACT 
 *	Header file for software overlay.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _SWOVLSRC_H
#define _SWOVLSRC_H

#include <ddraw.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <ovlsrc.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CSwOverlay : public COverlay
{
friend class CImgDibSink;
//methods
public:
	CSwOverlay(WORD dx, WORD dy);
	virtual  ~CSwOverlay();
	virtual BOOL Create();
	virtual IFC_HDC GetOverlayDC();
	virtual void ReleaseOverlayDC(IFC_HDC hDC);
	virtual DWORD GetMinStretch();
	virtual DWORD GetMaxStretch();
	
	IFC_DECLARE_DYN_OVERLAY(COverlay)
private:
	LPDIRECTDRAWSURFACE CreateDDSurface();
	BYTE *CreatePhysicalPal();
	DWORD DDColorMatch(COLORREF rgb);
	void ConvertSurfaceToIndexed();
	void ConvertSurface16ToIndexed();
	void ConvertSurface24ToIndexed();
	void ConvertSurface32ToIndexed();
	BYTE *Create16bitConversionTable();
	virtual BOOL MergeOverlay(CImgSink* pSink);
	virtual BOOL CopyMergeOverlay(CImgSrc* pSrc, CImgSink* pSink);


//attributes
public:

private:
	LPDIRECTDRAWSURFACE m_pDDSOverlay;
	BYTE *m_pbyPhysicalPalBuf;
	BYTE *m_pbyIndexedImgBuffer;
	RECT m_rcUpdateRect;
	RECT m_rcOverlayRect;
	BOOL m_bGetBoundsRectBugFixed;
	DWORD m_dwRBitMask;
	DWORD m_dwGBitMask;
	DWORD m_dwBBitMask;
	BYTE *m_pby16BitBadColorConvTable;

};
#endif
#endif // !defined(_SWOVLSRC_H)
