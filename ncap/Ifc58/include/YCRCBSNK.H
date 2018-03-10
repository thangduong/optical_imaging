/******************************************************************************
 *
 * MODULE   
 *		ycrcbsnk.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/YCRCBSNK.H $
 *		$Revision: 1.1 $
 *		$Modtime: 9/16/04 9:43a $
 *
 * ABSTRACT 
 *	Header file for YCrCb sink.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(_YCRCBSNK_H)
#define _YCRCBSNK_H

#include <windows.h>
#ifndef _WIN32_WCE
#include <vfw.h>
#endif
#include <ddraw.h>

#include <iobject.h>

/////////////////////////////////////////////////////////////////////
//CImgYcrcbSink
//////////////////////////////////////////////////////////////////////
#include <imgsink.h>
#include <ifcclass.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CImgYcrcbSink: public CImgSink  
{
//methods
public:
	CImgYcrcbSink(CImgYcrcbSink *pSink);
	CImgYcrcbSink(IFC_HWND hWind);
	CImgYcrcbSink(IFC_HWND hWind, WORD wxSinkStart, WORD wySinkStart, WORD wxSinkEnd, WORD wySinkEnd);
	~CImgYcrcbSink();
	BOOL SetupDispDevContext(CImgConn *pConn);
	virtual CImgSink *MakeCopy();
	virtual BOOL Create();
	virtual DWORD GetMinStretch();
	virtual DWORD GetMaxStretch();
	virtual BOOL SetDestColorKey(DWORD dwNewColorKey);
	virtual DWORD GetDestColorKey();
	virtual DWORD GetColorKeyRep(COLORREF color);
	virtual BOOL SetRemapColor(int iFirstIndex, int iLastIndex, COLORREF RemapColor);
	virtual void Remove(CImgConn* imgConn);

	IFC_DECLARE_DYN_IMGSINK(CImgSink)

private:
	virtual BOOL Display(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL MovFrameToYCrCbSurf(CImgSrc *pSrc);
	BOOL MovHostBuffToYCrCbSurf(CImgSrc *pSrc);
	BOOL UpdateSinkLocationIfNeeded(CImgSrc *pSrc);
	BOOL DisplayFrameBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL DisplayHostBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	WORD GetBitsPP() const ;
	DWORD DDColorMatch(LPDIRECTDRAWSURFACE pDDSurf,COLORREF rgb);
	void Mov8BitToYCrCb(BYTE *pby8BitSurf, WORD *pwYCrCbSurface,
									DWORD dwYCrCbSurfLinePitch,
									DWORD dw8BitSurfWidth,
									DWORD dwHeight);
	void CleanUp();


//attributes
public:

private:
	LPDIRECTDRAWSURFACE m_pDDYCrCbOverlaySurf;
	LPDIRECTDRAWSURFACE m_pDDSBackBuffer;
	BYTE				*m_p8BPPConvBuff;
	DDOVERLAYFX			m_ovfx;
	DWORD				m_dwColorKey;
	DWORD				m_dwAlignSizeMask;
	RECT				m_OldSinkRect;
	RECT				m_OldSrcRect;
	WORD				m_wYcrRemap[256];
	WORD				m_wYcbRemap[256];
	DWORD				m_dwPhysicalAddress;
	WORD				m_wSufaceWidth;		
	WORD				m_wSufaceHeight;	
	BOOL				m_bError;
	BOOL				m_bRemap;

	BOOL				m_acqToYcrcbSurface;
	DWORD               m_dwYcrcbRemap[0x10000];

	BYTE				*m_imgBuf;
	DWORD				m_imgSize;
	BOOL				m_isRGBSurface;

};
#endif
#endif // !defined(_YCRCBSNK_H)

