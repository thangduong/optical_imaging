/******************************************************************************
 *
 * MODULE   
 *		imgsink.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IMGSINK.H $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:37a $
 *
 * ABSTRACT 
 *	Header file for image sink.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#ifndef _IMGSINK_H
#define _IMGSINK_H

#include <windows.h>
#include <iobject.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <ifcclass.h>

#define IFC_STRETCH_TO_FIT -1.0

typedef CImgSink *PCImgSink;

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CImgSink : public CIobject
{
friend class CImgConn;
friend class CImgDDrawSink;
friend class CImgDibSink;
friend class CImgYcrcbSink;


//methods
public:
	CImgSink(CImgSink* pSink);
	CImgSink(IFC_HWND hWnd, SINK_KIND Kind, WORD wSinkStartX=0, WORD wSinkStartY=0,	WORD Width=0,	WORD Height=0);
	virtual ~CImgSink();
	virtual const WORD GetAoiStartX() const;
	virtual const WORD GetAoiStartY() const;
	virtual const WORD GetWidth() const;
	virtual const WORD GetHeight() const;
	virtual const WORD GetLinePitch() const;
	virtual void SetAoiPos(const WORD wxAoiStart, const WORD wyAoiStart);
	virtual void GetAoiPos(WORD *pwxAoiStart, WORD *pwyAoiStart) const ;
	virtual void GetAoiPos(RECT *pRect) const ;
	virtual IFC_HWND GetSinkWindow();
	void GetZoom(double *ZoomX, double *ZoomY) const;
	virtual void SetZoom(double ZoomX, double ZoomY);
	double GetZoomX() const;
	double GetZoomY() const;
	virtual BOOL ResizeWindow();
	virtual BOOL Create();
	virtual CImgSink *MakeCopy();
	virtual BYTE * GetBufferAddr() const;
	virtual WORD GetBitsPP() const;
	virtual DWORD GetMinStretch();
	virtual DWORD GetMaxStretch();
	virtual BOOL SetDestColorKey(DWORD dwNewColorKey);
	virtual BOOL SetRemapColor(int iFirstIndex, int iLastIndex, COLORREF RemapColor);
	virtual DWORD GetDestColorKey();
	virtual DWORD GetColorKeyRep(COLORREF color) {return 0;};
	virtual void Remove(CImgConn* imgConn){};
	SINK_KIND GetKind() const ;
 
private:
	virtual BOOL Display(CImgSrc *pSrc, COverlay *pOverlay);
	virtual BOOL SetupDispDevContext(CImgConn *pConn);
	

public:
	virtual void SetWidth(WORD wWidth);
	virtual void SetHeight(WORD wHeight);
	virtual void AutoSizeToSrc(CImgSrc *pSrc);

//attributes
public:

private:
	IFC_HWND	m_hSinkWnd;	
	WORD		m_wxSinkStart;		
	WORD		m_wySinkStart;		
	WORD		m_wWidth;			
	WORD		m_wHeight;			
	LONG		m_lFrameWindowWidth;
	LONG		m_lFrameWindowHeight;

	double		m_xZoom;		
	double		m_yZoom;		
	SINK_KIND	m_SinkKind;	
	BOOL		m_bAutoSizeSink;	

};


IFC_EXT_API CImgSink *IfxCreateImgSink(IFC_HWND hWnd, SINK_KIND Kind, WORD wSinkStartX=0, WORD wSinkStartY=0,	WORD wWidth=0,	WORD wHeight=0);
#else
IFC_EXT_API CImgSink *IfxCreateImgSink(IFC_HWND hWnd, SINK_KIND Kind, WORD wSinkStartX, WORD wSinkStartY,	WORD wWidth,	WORD wHeight);
#endif

#define IFC_DECLARE_DYN_IMGSINK(baseClass) static baseClass *CreateObject(IFC_HWND hWnd, WORD wSinkStartX, WORD wSinkStartY,	WORD wWidth,	WORD wHeight);

#define IFC_IMPLEMENT_DYN_IMGSINK(deriveClass,baseClass) \
baseClass *deriveClass::CreateObject(IFC_HWND hWnd,  WORD wSinkStartX, WORD wSinkStartY,	WORD wWidth,	WORD wHeight) \
{ \
	return new deriveClass(hWnd,wSinkStartX,wSinkStartY,wWidth,wHeight); \
} 

typedef PCImgSink (*pfImgSinkCreate)(IFC_HWND hWnd,  WORD wSinkStartX, WORD wSinkStartY,	WORD wWidth, WORD wHeight);

BOOL IFCCALL IfxAddImgSinkClass(pfImgSinkCreate create,SINK_KIND eSinkKind);
void IFCCALL IfxCloseImageSinkFactory(void);

#define IFC_ADD_FACTORY_IMGSINK_CLASS(sinkClass,eSinkKind) \
int _var_##sinkClass = IfxAddImgSinkClass(sinkClass::CreateObject,(eSinkKind));


#endif // !defined(_IMGSINK_H)
