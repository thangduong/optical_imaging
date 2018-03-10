/******************************************************************************
 *
 * MODULE   
 *		ddawsink.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/DDawSink.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:39a $
 *
 * ABSTRACT 
 *	Header file for Direct Draw display sink.
 *
 * TECHNICAL NOTES  
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _DDRWSINK_H_
#define _DDRWSINK_H_

#include <iobject.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <imgsink.h>

//{secret}
//used by funciton coping data to VGA buffer
//describes each visible rectangular region of the sink window
typedef struct 
{
	 DWORD physdest;
	 short nRgnWidth;
	 short nRgnHeight;
	 short aoi_xadj;
	 short aoi_yadj;
     DWORD dwVgaAddress;
     DWORD dwHostOffset;
} DDRAW_INFO;
typedef DDRAW_INFO *pDDRAW_INFO;	                 
         
                
/////////////////////////////////////////////////////////////////////
//CImgDDrawSink
//////////////////////////////////////////////////////////////////////
#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CImgDDrawSink: public CImgSink  
{
//methods
public:
	CImgDDrawSink(CImgDDrawSink *pSink);
	CImgDDrawSink(IFC_HWND hWnd, WORD wxSinkStart=0, WORD wySinkStart=0, WORD wWidth=0, WORD wHeight=0);

	~CImgDDrawSink();
	virtual BOOL Create();
	virtual CImgSink *MakeCopy();

	IFC_DECLARE_DYN_IMGSINK(CImgSink)

private:
	BOOL SetupDispDevContext(CImgConn *pConn);
	virtual BOOL Display(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL DisplayFrameBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL DisplayHostBuffer(CImgSrc *pSrc, COverlay *pOverlay);
	BOOL CImgDDrawSink::DDrawClipRect(CImgSrc *pSrc, short *sNumClipRgn, short *sDestLineBytes, DDRAW_INFO ddraw_rect_info[]);
	BOOL DDrawClipRect(CImgConn *pConn, short *numcliprgn, short *destlinebytes, DDRAW_INFO ddraw_rect_info[], short bytesdxmul );
	WORD GetBitsPP() const ;


//attributes
public:

private:
	HPALETTE			m_hCurrentPalette;
	LPRGNDATA			m_DisplayRgnData;
	WORD				m_DDSinkSurfDepthBytes;
	WORD				m_DDSinkSurfLinePitch;
	WORD				m_wAlignment;
	BOOL				m_bError;

};
#endif

#endif // _DDRWSINK_H_
