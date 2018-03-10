/******************************************************************************
 *
 * MODULE   
 *		imgconn.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/imgconn.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/15/04 7:07p $
 *
 * ABSTRACT 
 *	Header file for image connection.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef	_IMGCONN_H
#define _IMGCONN_H

#include <windows.h>

#include <iobject.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <intrupt.h>
#include <icapmod.h>
#include <ifcclass.h>


typedef void (*pVoidFunc)(void *);
typedef BOOL (*pBoolFunc)(void *);
//define structure that will be passed to process->display on the event
typedef struct{
		pBoolFunc pFunc;
		void *pArg;
		CImgConn *pConn;
	}PROCESSPARAM;

#if defined __cplusplus && !defined NOIFCLINK
//export wrappers around new... ->Create
IFC_EXT_API CImgConn *IfxCreateImgConn(	
				CICamera *pCamera, 
				IFC_HWND hWnd, 
				DWORD Flags = IFC_DIB_SINK,
				ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);

IFC_EXT_API CImgConn *IfxCreateImgConn(
				BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, 
				IFC_HWND hwnd, 
				IFC_COLOR eColor = IFC_MONO,
				DWORD Flags = IFC_DIB_SINK,
				CICamera *cam=NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1,
				pBoolFunc pFunc = NULL, void *pArg= NULL);

IFC_EXT_API CImgConn *IfxCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink,		
				DWORD Flags = IFC_DEFAULT_FLAG,
				CICamera *cam = NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);

IFC_EXT_API CImgConn *IfxCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink, 
				COverlay *pOverlay, 
				DWORD Flags = IFC_DEFAULT_FLAG,
				CICamera *cam=NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);



class IFC_EXT_API CImgConn : public CIobject  
{
public:
friend void DisplayConn(void* pArg);
friend void ProcessAndDisplayConn(void *pProcessArg);
//****************************************************************************
// Name: 
//	CImgConn
//
// Description: 
//	Creates CImgConn object. It will dynamicly create internal image source and image sink
//	if needed or use user supplied source, sink or overlay
//
// Parameters:
//	pCamera - pointer to camera
//  pImgBuffer - ponter to host image buffer
//	wWidth, wHeight, wImgBitsPP - width, height and bits per pixel of an image 
//	hwnd - pointer to window used as a sink device
//	pImgSrc - pointer image source object
//	pOverlay - pointer overlay image object
//	pImgSink - pointer image sink object
//	Flags - combination of flags indicating how to create connection
//
// Return Value:
//	CImgConn object (Create member of CImgConn has to be called before connection is
//	usable)
//
// Possible ways to create image connection:
//	CImgConn::CImgConn(CICamera *pCamera, IFC_HWND hwnd, DWORD Flags)	
//	 valid flags for this constructor:
//	 one of: IFC_DIB_SINK, IFC_DDRAW_SINK, IFC_YCRCB_SINK
//	 optional: IFC_SW_OVERLAY or IFC_HW_OVERLAY
//	 optional: IFC_LIVE_IMAGE
//	Flags parameter can be ommited. Default value in this case is: IFC_DIB_SINK
//
//	CImgConn::CImgConn(BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, IFC_HWND hwnd, DWORD Flags)
//	 valid flags for this constructor:
//	 one of: IFC_DIB_SINK, IFC_DDRAW_SINK, IFC_YCRCB_SINK
//	 optional: IFC_SW_OVERLAY or IFC_HW_OVERLAY
//	 optional: IFC_LIVE_IMAGE
//	Flags parameter can be ommited. Default value in this case is: IFC_DIB_SINK
//
//  CImgConn::CImgConn(CImgSrc *pImgSrc, CImgSink *pImgSink, DWORD Flags)
//	 optional: IFC_SW_OVERLAY or IFC_HW_OVERLAY
//	 optional: IFC_LIVE_IMAGE
//	Flags parameter can be ommited.
//
//	CImgConn::CImgConn(CImgSrc *pImgSrc, COverlay *pOverlay, CImgSink *pImgSink, DWORD Flags)
//	 optional: IFC_LIVE_IMAGE
//	Flags parameter can be ommited.
//
//
// Note:
//	When connection is supplied with a handle to window display method can
//	be indicated by specifying one of the sink flags. 
//	Possible choices are:
//	*IFC_DIB_SINK	- uses GDI DIB display method
//	*IFC_DDRAW_SINK	- uses DDRAW display method
//	*IFC_YCRCB_SINK - uses DDRAW YCrCb surface and desination keying (allows to create
//					  overlay images without creating separate overlay surface)
//	*IFC_IMG_SINK   - reserved
//
//	Default is: IFC_DIB_SINK
//
//  Overlay can be created over the sink window by specifying one of the following:
//	*IFC_SW_OVERLAY - software overlay (supported only with IFC_DIB_SINK display)
//	*IFC_HW_OVERLAY - hardware overlay (supported with IFC_DIB_SINK and IFC_DDRAW_SINK)
//	Please note that IFC_YCRCB_SINK without IFC_SW_OVERLAY or IFC_HW_OVERLAY can be used to 
//	created overlay images.
//	Default is: No overlay
//
//	With any of the connection constructors live image can be displayed by specifying
//	IFC_LIVE_IMAGE flag
//
//**************************************************************************** 




//#########################################################################################
// change the default for the interrupt invent when interrupts get implemented.....
	CImgConn(	CICamera *pCamera, 
				IFC_HWND hWnd, 
				DWORD Flags = IFC_DIB_SINK,
				ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);

	CImgConn(	BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, 
				IFC_HWND hwnd, 
				IFC_COLOR eColor = IFC_MONO,
				DWORD Flags = IFC_DIB_SINK,
				CICamera *cam = NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1,
				pBoolFunc pFunc = NULL, void *pArg= NULL);

	CImgConn(	CImgSrc *pImgSrc, 
				CImgSink *pImgSink,
				DWORD Flags = IFC_DEFAULT_FLAG,
				CICamera *cam = NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);

	CImgConn(	CImgSrc *pImgSrc, 
				CImgSink *pImgSink, 
				COverlay *pOverlay, 
				DWORD Flags = IFC_DEFAULT_FLAG,
				CICamera *cam = NULL, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB,
				int iScale = 1);
//#########################################################################################

	virtual ~CImgConn();
	void Display();
	BOOL Create();

///////////////////////////////////////////////////////////////////////////////
//basic connection operations
///////////////////////////////////////////////////////////////////////////////
	//live image
	BOOL StartLiveImage(CICamera *cam, ICAP_INTR_EVENT intrEvent = ICAP_INTR_EVEN_VB, WORD InterruptScale = 1);
	BOOL StopLiveImage();
	BOOL LiveImageSuspend();
	BOOL LiveImageResume();
	double GetLiveImageFPS();


	//overlay
	IFC_HDC GetOverlayDC();
	void ReleaseOverlayDC(IFC_HDC hDC);
	void EnableOverlay(BOOL bEnable);



///////////////////////////////////////////////////////////////////////////////
//advanced connection operations
///////////////////////////////////////////////////////////////////////////////
	//image server operations
	CCallBackServer *GetImgServer();

	//source operation
	CImgSrc *GetSrc();

	//sink operations
	CImgSink *GetSink();


	//overlay operations
	COverlay *GetOverlay();	
	WORD GetOverlayWidth();
	WORD GetOverlayHeight();
	DWORD GetOverlayMaxStretch();
	WORD GetOverlayBitsPP() const;
	DWORD GetOverlayMinStretch();
	OVERLAY_KIND GetOverlayKind() const ;

private:
	BOOL SetupConnection();
	void CreateRequestedSink(DWORD Flags, IFC_HWND hwnd );
	void CreateRequestedOverlay(DWORD Flags, WORD Width, WORD Heigh);

private:
	CImgSrc			*m_pImgSrc;
	COverlay		*m_pOverlay;
	CImgSink		*m_pImgSink;
	CCallBackServer	*m_pImgServer;
	CInterrupt		*m_pLiveImgIntr;
	BOOL			m_bError;
	BOOL			m_bConnCreatedSrc;
	BOOL			m_bConnCreatedOverlay;

	PROCESSPARAM	*m_pProcessingParams;
	CInterrupt		*m_pProcessingIntr;
	CCallBackServer	*m_pProcessingServer;
	HANDLE			m_connMutex;


};
#else
IFC_EXT_API CImgConn *IfxCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink,		
				DWORD Flags,
				CICamera *cam, ICAP_INTR_EVENT intrEvent,
				int iScale);
#endif
#endif // !defined(_IMGCONN_H)
