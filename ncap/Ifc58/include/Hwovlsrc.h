/******************************************************************************
 *
 * MODULE   
 *		hwovlsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/HWOVLSRC.H $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:39a $
 *
 * ABSTRACT 
 *	Header file for hardware overlay.
 *
 * TECHNICAL NOTES 
 * 
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _HWOVLSRC_H
#define _HWOVLSRC_H

#include <windows.h>
#include <ddraw.h>
#include <ovlsrc.h>
#include <ifcclass.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CHwOverlay : public COverlay
{
//methods
public:
	CHwOverlay(WORD dx, WORD dy);
	~CHwOverlay();
	virtual BOOL Create();
	virtual IFC_HDC GetOverlayDC();
	virtual void ReleaseOverlayDC(IFC_HDC hDC);
	BOOL PaintOverlay(CImgSink *pImgSink);

	IFC_DECLARE_DYN_OVERLAY(COverlay)
private:
	LPDIRECTDRAWSURFACE CreateDDSurface();

//attributes
public:
 
private:
	LPDIRECTDRAWSURFACE m_pDDSOverlay;
	LPRGNDATA			m_DisplayRgnData;
	LPDIRECTDRAWCLIPPER m_pDDrawClipper;
	RECT				m_OldSinkRect;
	DWORD				m_dwStretchFactor;
	DWORD				m_dwAlignSrcMask;
	DWORD				m_dwAlignDestMask;
	DWORD				m_dwMinStretch;
	DWORD				m_dwMaxStretch;



};
#endif

#endif // !defined(_HWOVLSRC_H)
