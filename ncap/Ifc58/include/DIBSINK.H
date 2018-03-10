/******************************************************************************
 *
 * MODULE   
 *		dibsink.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/DIBSINK.H $
 *		$Revision: 1.1 $
 *		$Modtime: 8/27/04 2:15p $
 *
 * ABSTRACT 
 *	Header file for DIB display sink.
 *
 * TECHNICAL NOTES 
 * 
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
#ifndef _DIBSINK_H
#define _DIBSINK_H

#ifndef _WIN32_WCE
#include <vfw.h>
#endif
#include <iobject.h>
#include <imgsink.h>

                 
#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CImgDibSink: public CImgSink  
{
friend class CImgConn;

//methods
public:
	CImgDibSink(CImgDibSink *pSink);	
	CImgDibSink(IFC_HWND hWnd, WORD wxSinkStart=0, WORD wySinkStart=0, WORD wWidth=0, WORD wHeight=0);
	~CImgDibSink();
	virtual IFC_HWND GetSinkWindow(); 
	virtual BYTE* GetBufferAddr() const;
	virtual WORD GetBitsPP() const;
	virtual const WORD GetLinePitch() const;
	WORD	DIBWidth();
	WORD	DIBHeight();
	virtual BOOL Create();
	virtual CImgSink *MakeCopy();
	virtual BOOL SetRemapColor(int iFirstIndex, int iLastIndex, COLORREF RemapColor);

	IFC_DECLARE_DYN_IMGSINK(CImgSink)

private:
	BOOL Display(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL DisplayFrameBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL DisplayHostBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL CameraSrcToReverseBuffSink(CImgSrc *pSrc, BOOL bClip8BitImage);
	BOOL LinearBuffSrcToReverseBuffSink(CImgSrc *pSrc);
	BOOL CopyImgToScreen(CImgSrc *pSrc, BOOL RemapSystemColors);
	BOOL MergeOverlay(COverlay *pOverlay);
	BOOL CopySourceAndMergeOverlay(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL SetupDispDevContext(CImgConn *pConn);

//attributes
public:

private:
#ifndef _WIN32_WCE
	HDRAWDIB	m_hDrawDibDC;
#else
	HBITMAP		m_hDrawDibDC;
#endif
	HDC	 		m_hSinkWndDC;
	WORD		m_wPixelBitsPP;
	BYTE		*m_pbyDibImgBuffer;
	BITMAPINFO	m_BitmapInfoStruc;
	RGBQUAD		m_PaletteSpace[256];

	WORD		m_wDIBWidth;		
	WORD		m_wDIBHeight;		
	BYTE		*m_imgBuf;
	DWORD		m_imgSize;
	BYTE		*m_curDisplayAddr;
	HANDLE		m_dispMutex;

};
#endif
#endif // !defined(_DIBSINK_H)
