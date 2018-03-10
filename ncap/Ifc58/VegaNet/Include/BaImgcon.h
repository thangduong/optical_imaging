/******************************************************************************
 *
 * MODULE   
 *		imgconn.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/BaImgcon.h $
 *		$Revision: 1.1 $
 *		$Modtime: 4/13/04 3:23p $
 *
 * ABSTRACT 
 *	Header file for image connection.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef	_VS_IMGCONN_H
#define _VS_IMGCONN_H

#include <windows.h>

#include <VnObject.h>
#include <vidsrct.h>
#include <disptype.h>
#include <VnImgCon.h>
#include <VnBase.h>
#include <VnOS.h>



class CCallBackServer;
class CBaImgConn;
class CImgSrc;
class CImgSink;
class COverlay;


#define IC_WAIT_MUTEX_TIME 10000


typedef void (*pVoidFunc)(void *);
typedef BOOL (*pBoolFunc)(void *);

//define structure that will be passed to process->display on the event
typedef struct{
	pBoolFunc pFunc;
	void *pArg;
	CBaImgConn *pConn;
} VS_PROCESSPARAM;




#ifdef __cplusplus
//export wrappers around new... ->Create

IVSV_EXT_API CBaImgConn *VsCreateImgConn(	
				IImgNode *pImgNode, 
				VS_HWND hWnd, 
				DWORD Flags = VS_DIB_SINK_FLAG,
				int iScale = 1,
				pNodeProcFunc pFunc = NULL, void *pArg= NULL);

IVSV_EXT_API CBaImgConn *VsCreateImgConn(	
				IVideoSrc *pVidSrc, 
				VS_HWND hWnd, 
				DWORD Flags = VS_DIB_SINK_FLAG,
				VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);

IVSV_EXT_API CBaImgConn *VsCreateImgConn(
				BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, 
				VS_HWND hwnd, 
				VS_COLOR eColor = VS_MONO,
				DWORD Flags = VS_DIB_SINK_FLAG,
				IVideoSrc *pVidSrc=NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1,
				pBoolFunc pFunc = NULL, void *pArg= NULL);

IVSV_EXT_API CBaImgConn *VsCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink,		
				DWORD Flags = VS_DEFAULT_FLAG,
				IVideoSrc *cam = NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);

IVSV_EXT_API CBaImgConn *VsCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink, 
				COverlay *pOverlay, 
				DWORD Flags = VS_DEFAULT_FLAG,
				IVideoSrc *cam=NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);



class IVSV_EXT_API CBaImgConn : public CVnObject  
{
public:
friend void DisplayConn(void* pArg);
friend void ProcessAndDisplayConn(void *pProcessArg);
//****************************************************************************
// Name: 
//	CBaImgConn
//
// Description: 
//	Creates CBaImgConn object. It will dynamicly create internal image source and image sink
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
//	CBaImgConn object (Create member of CBaImgConn has to be called before connection is
//	usable)
//
// Possible ways to create image connection:
//	CBaImgConn::CBaImgConn(IVideoSrc *pCamera, VS_HWND hwnd, DWORD Flags)	
//	 valid flags for this constructor:
//	 one of: VS_DIB_SINK_FLAG, VS_DDRAW_SINK_FLAG, VS_YCRCB_SINK_FLAG
//	 optional: VS_SW_OVERLAY or VS_HW_OVERLAY
//	 optional: VS_LIVE_IMAGE
//	Flags parameter can be ommited. Default value in this case is: VS_DIB_SINK_FLAG
//
//	CBaImgConn::CBaImgConn(BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, VS_HWND hwnd, DWORD Flags)
//	 valid flags for this constructor:
//	 one of: VS_DIB_SINK_FLAG, VS_DDRAW_SINK_FLAG, VS_YCRCB_SINK_FLAG
//	 optional: VS_SW_OVERLAY or VS_HW_OVERLAY
//	 optional: VS_LIVE_IMAGE
//	Flags parameter can be ommited. Default value in this case is: VS_DIB_SINK_FLAG
//
//  CBaImgConn::CBaImgConn(CImgSrc *pImgSrc, CImgSink *pImgSink, DWORD Flags)
//	 optional: VS_SW_OVERLAY or VS_HW_OVERLAY
//	 optional: VS_LIVE_IMAGE
//	Flags parameter can be ommited.
//
//	CBaImgConn::CBaImgConn(CImgSrc *pImgSrc, COverlay *pOverlay, CImgSink *pImgSink, DWORD Flags)
//	 optional: VS_LIVE_IMAGE
//	Flags parameter can be ommited.
//
//
// Note:
//	When connection is supplied with a handle to window display method can
//	be indicated by specifying one of the sink flags. 
//	Possible choices are:
//	*VS_DIB_SINK_FLAG	- uses GDI DIB display method
//	*VS_DDRAW_SINK_FLAG	- uses DDRAW display method
//	*VS_YCRCB_SINK_FLAG - uses DDRAW YCrCb surface and desination keying (allows to create
//					  overlay images without creating separate overlay surface)
//	*VS_IMG_SINK_FLAG   - reserved
//
//	Default is: VS_DIB_SINK_FLAG
//
//  Overlay can be created over the sink window by specifying one of the following:
//	*VS_SW_OVERLAY - software overlay (supported only with VS_DIB_SINK display)
//	*VS_HW_OVERLAY - hardware overlay (supported with VS_DIB_SINK_FLAG and VS_DDRAW_SINK_FLAG)
//	Please note that VS_YCRCB_SINK without VS_SW_OVERLAY or VS_HW_OVERLAY can be used to 
//	created overlay images.
//	Default is: No overlay
//
//	With any of the connection constructors live image can be displayed by specifying
//	VS_LIVE_IMAGE flag
//
//**************************************************************************** 




//#########################################################################################

	CBaImgConn(	IImgNode *pImgNode, 
				VS_HWND hWnd, 
				DWORD Flags = VS_DIB_SINK_FLAG,
				int iScale = 1,
				pNodeProcFunc pFunc = NULL, void *pArg= NULL);


	CBaImgConn(	IVideoSrc *pCamera, 
				VS_HWND hWnd, 
				DWORD Flags = VS_DIB_SINK_FLAG,
				VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);

	CBaImgConn(	BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, 
				VS_HWND hwnd, 
				VS_COLOR eColor = VS_MONO,
				DWORD Flags = VS_DIB_SINK_FLAG,
				IVideoSrc *cam = NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1,
				pBoolFunc pFunc = NULL, void *pArg= NULL);

	CBaImgConn(	CImgSrc *pImgSrc, 
				CImgSink *pImgSink,
				DWORD Flags = VS_DEFAULT_FLAG,
				IVideoSrc *cam = NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);

	CBaImgConn(	CImgSrc *pImgSrc, 
				CImgSink *pImgSink, 
				COverlay *pOverlay, 
				DWORD Flags = VS_DEFAULT_FLAG,
				IVideoSrc *cam = NULL, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB,
				int iScale = 1);

//#########################################################################################

	virtual ~CBaImgConn();
	void Display();
	BOOL Create();

///////////////////////////////////////////////////////////////////////////////
//basic connection operations
///////////////////////////////////////////////////////////////////////////////
	//live image
	BOOL StartLiveImage(IVideoSrc *vidSrc, VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EVEN_VB, WORD InterruptScale = 1);
	BOOL StopLiveImage();
	BOOL LiveImageSuspend();
	BOOL LiveImageResume();
	double GetLiveImageFPS();


	//overlay
	VS_HDC GetOverlayDC();
	void ReleaseOverlayDC(VS_HDC hDC);
	void EnableOverlay(BOOL bEnable);

	void AdjustNodeAttr(VS_INODE_IMG_ATTR *attr);


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
	VS_OVERLAY_KIND GetOverlayKind() const ;

private:
	BOOL SetupConnection();
	void CreateRequestedSink(DWORD Flags, VS_HWND hwnd );
	void CreateRequestedOverlay(DWORD Flags, WORD Width, WORD Height);

private:
	CImgSrc			*m_pImgSrc;
	COverlay		*m_pOverlay;
	CImgSink		*m_pImgSink;
	CCallBackServer	*m_pImgServer;
	HVSINTERRUPT	m_LiveImgIntr;
	BOOL			m_bError;
	BOOL			m_bConnCreatedSrc;
	BOOL			m_bConnCreatedOverlay;

	VS_PROCESSPARAM	*m_pProcessingParams;
	HVSINTERRUPT	m_ProcessingIntr;
	CCallBackServer	*m_pProcessingServer;
	IVideoSrc *m_pCamera;
	IImgNode *m_pImgNode;
	DWORD m_Flags;
	VS_HWND m_hWnd;
	VS_INODE_IMG_ATTR m_curImgAttr;
	HANDLE m_imgConnMutex;
	CVnOS m_os;

};

#else

IVSV_EXT_API CBaImgConn *VsCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink,		
				DWORD Flags,
				IVideoSrc *cam, VS_ICAP_INTR_EVENT intrEvent,
				int iScale);

#endif
#endif // !defined(_IMGCONN_H)
