/********************************************************************
 *
 * MODULE
 *    overlayv.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/overlayv.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 9/19/03 6:41p $
 *
 * ABSTRACT
 *    VegaNet Overlay example program
 *    This example shows how to use YCRCB and software overlay.
 *              
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999-2001, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/  
// overlayv.cpp : implementation of the COverlayView class
//

#include "stdafx.h"
#include "overlay.h"

#include "overlayd.h"
#include "overlayv.h"
#include "mainfrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "OElem.h"


#define YCRCB_COLOR_KEY RGB(0x80,0x80,0)
#define TEXT_MESSAGE "** Overlay Demo **"

//global variables 
int     nUsedOverlay		= SOFTWARE_OVERLAY;
int     nRemapActive		= 0;
int		nDrawingMode		= FREE;
static BOOL   bDrawingActive = FALSE;
int	 nImageSource = NODE_IMG_SRC;
STATIC_COLOR CurrentColorEnum = green;
ZOOM nImageZoom = zoom10;

// software overlay supported colors
DWORD system_colors[]={
	RGB(0,		0,		0),
	RGB(0x80,	0,		0),
	RGB(0,		0x80,	0),
	RGB(0x80,	0x80,	0),
	RGB(0,		0,		0x80),
	RGB(0x80,	0,		0x80),
	RGB(0,		0x80,	0x80),
	RGB(0xC0,	0xC0,	0xC0),
	RGB(0xC0,	0xDC,	0xC0),
	RGB(0xA4,	0xC8,	0xF0),
	RGB(0xFF,	0xFB,	0xF0),
	RGB(0xA0,	0xA0,	0xA4),
	RGB(0x80,	0x80,	0x80),
	RGB(0xFF,	0,		0),
	RGB(0,		0xFF,	0),
	RGB(0xFF,	0xFF,	0),
	RGB(0,		0,		0xFF),
	RGB(0xFF,	0,		0xFF),
	RGB(0,		0xFF,	0xFF),
    RGB(0xFF,	0xFF,	0xFF)
};


//thread procedure prototype
UINT SoftwareOverlayThread (LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// COverlayView

IMPLEMENT_DYNCREATE(COverlayView, CScrollView)

BEGIN_MESSAGE_MAP(COverlayView, CScrollView)
	//{{AFX_MSG_MAP(COverlayView)
	ON_COMMAND(ID_OVERLAY_SOFTWARE, OnOverlaySoftware)
	ON_COMMAND(ID_ZOOM_ITXSTRETCHTOFIT, OnZoomStretchToFit)
	ON_COMMAND(ID_ZOOM_2, OnZoom2)
	ON_COMMAND(ID_ZOOM_1, OnZoom1)
	ON_COMMAND(ID_DRAWING_RECTANGLE, OnDrawingRectangle)
	ON_COMMAND(ID_DRAWING_CIRCLE, OnDrawingCircle)
	ON_COMMAND(ID_DRAWING_TEXT, OnDrawingText)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAWING_NONE, OnDrawingNone)
	ON_COMMAND(ID_IMAGESOURCE_FRAME, OnImagesourceFrame)
	ON_COMMAND(ID_IMAGESOURCE_HOSTBUFF, OnImagesourceHostbuff)
	ON_COMMAND(ID_OVERLAYDRAWING_FREEDRAWING, OnOverlaydrawingFreedrawing)
	ON_COMMAND(ID_ZOOM_05, OnZoom05)
	ON_COMMAND(ID_OVERLAY_OVERLAYONPRIMARY, OnOverlayOnPrimary)
	ON_COMMAND(ID_OVERLAY_PRIMARY_REMAP, OnOverlayPrimaryRemap)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CLEAROVERLAY, OnClearoverlay)
	ON_COMMAND_RANGE(ID_COLORS_TRANSPARENT, ID_COLORS_WHITE, OnColorChange)
	ON_WM_DESTROY()
	ON_COMMAND(ID_IMAGESOURCE_IMGNODE, OnImageSourceImgnode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COverlayView construction/destruction

COverlayView::COverlayView()
{
	//initialize member variables
	m_nCurdx = 640;
	m_nCurdy = 480;
	m_vidSrc                = NULL;
	m_nodeDisplay           = NULL;
	m_vStream               = NULL;

	m_bErrorConfiguring     = FALSE;
	m_pBuffer				= NULL;
	m_procthrd				= NULL;
	m_numImgAreas			= 3;
    m_LButtonDownPoint.y	= -1;
    m_LastMousePoint.x		= -1;
    m_LastMousePoint.y		= -1;
    m_iLineThickness		= 5;
    m_CurrentColor = system_colors[CurrentColorEnum];
    m_pTransparentThickPen	= NULL;
    m_pTransparentPen		= NULL;
    m_pTransparentBrush		= NULL;
    m_pPen					= NULL;
	m_pScalledPen			= NULL;
    m_pPen1					= NULL;
    m_pBrush				= NULL;
	m_pCurrentElem			= NULL;

	COverlayApp *thisApp = (COverlayApp *) AfxGetApp();
	m_vidSrc = VsQueryCreateVidSrc(thisApp->m_vidSrcCfg,NULL);

	if (m_vidSrc) {
		m_VideoSrcIsLocal = VsCallerLocalToObj(m_vidSrc);
		VsQueryCameraType(m_vidSrc);
	}

}

COverlayView::~COverlayView()
{
	// delete all open sources, sinks, connections and servers
	KillOpenConnections();
	// on exit cleanup hardware
	DeleteTransparentPenAndBrush();
	DeletePenAndBrush();
	if (m_vidSrc) {
		VsDeleteVideoSrc(m_vidSrc);
		m_vidSrc = NULL;
	}
}

BOOL COverlayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COverlayView drawing

void COverlayView::OnDraw(CDC* pDC)
{
    COverlayDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    CDC* pOverlayDC;
    HDC hDC;
    float fZoomX;
    float fZoomY; 

	if (!m_vidSrc) {
		return;
	}

	CalculateZoomVal(&fZoomX, &fZoomY);

	CPoint sp = GetScrollPosition();
	sp.x = (long)(sp.x / fZoomX);
	sp.y = (long)(sp.y / fZoomY);

	sp.x=min(sp.x, (long)m_nCurdx - 1);
	sp.y=min(sp.y, (long)m_nCurdy - 1);

	if (m_nodeDisplay &&  nImageZoom != STRETCH_TO_FIT) 
		m_nodeDisplay->SetSrcAoiPos( (DWORD)sp.x, (DWORD)sp.y);

    // paint sink window with YCRCB_COLOR_KEY
    if( nUsedOverlay == YCRCB_OVERLAY){
        ColorFillCDC(YCRCB_COLOR_KEY, pDC);
		OnPrepareDC(pDC);
        pOverlayDC = pDC;
    }
	else {
		// software overlay is in seperate buffer, but we still want to
		// repaint it because of the zoom (fit setting)
        m_nodeDisplay->GetOverlayDC(&hDC);
		if(!hDC)
			return; 
        // create DC fom hDC and paint it
        pOverlayDC = CDC::FromHandle(hDC);
        ColorFillCDC(RGB(0,0,0), pOverlayDC);
		fZoomX = fZoomY = 1.0;
    }
  
	RepaintOverlay(pOverlayDC, fZoomX, fZoomY);

    if( nUsedOverlay != YCRCB_OVERLAY){
		pOverlayDC->DeleteTempMap();
		m_nodeDisplay->ReleaseOverlayDC(hDC);
    }
}

/////////////////////////////////////////////////////////////////////////////
// COverlayView diagnostics

#ifdef _DEBUG
void COverlayView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COverlayView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COverlayDoc* COverlayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COverlayDoc)));
	return (COverlayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COverlayView message handlers



// initiate grab
void COverlayView::InitiateGrabWithOverlay() 
{

	DWORD Flags=0;
	VSPROPS vidSrcProps;
	if (!m_vidSrc)
		return;

	m_vidSrc->GetProps(&vidSrcProps);


	if (vidSrcProps.installedName == "ITI.PCR.0"
		|| vidSrcProps.installedName == "ITI.PCR.1" ) {
		
		if (m_camAttrib.dwBitsPerPixel != 8) {
			if (nUsedOverlay == YCRCB_OVERLAY) {
				m_vidSrc->SetAcqParam(VSP_COLOR_SPACE_CONV,VS_CSC_RGB_TO_YCRCB422,0);
				m_vidSrc->SetAcqParam(VSP_PIXEL_COLOR,VS_YCRCB,0);
			}
			else {
				m_vidSrc->SetAcqParam(VSP_COLOR_SPACE_CONV,VS_CSC_RGB_TO_RGB,0);
				m_vidSrc->SetAcqParam(VSP_PIXEL_COLOR,VS_RGB_PACK24,0);
			}
			m_vidSrc->GetAttr(&m_camAttrib,TRUE);
		}
	}
	if (vidSrcProps.installedName == "ITI.ICP.0"
		|| vidSrcProps.installedName == "ITI.ICP.1" ) {

		m_vidSrc->SetAcqParam((VS_ACQ_PARAMS_TYPE)VPCV_YCRCB_MONO_ACQ,(nUsedOverlay == YCRCB_OVERLAY && nImageSource == CAM_IMG_SRC)?VS_ENABLE:VS_DISABLE,0);

	}
	// allocate host buffer for host grab
	if(!m_pBuffer)
		if((m_pBuffer =  (BYTE*)malloc(m_nCurdx * m_nCurdy * m_camAttrib.dwBytesPerPixel * m_numImgAreas)) == NULL)
			return;

	if (nUsedOverlay == SOFTWARE_OVERLAY) {
		Flags |= VS_SW_OVERLAY_FLAG;
	}
	else if (nUsedOverlay == YCRCB_OVERLAY) {
		Flags |= VS_YCRCB_SINK_FLAG;
	}

	// create image source
	if (nImageSource == NODE_IMG_SRC) {
		if (m_VideoSrcIsLocal) {
			m_nodeDisplay = VsCreateDisplayNode( m_hWnd,Flags,NULL,0);
			m_vidSrc->ConnectOutputTo(0,m_nodeDisplay);
			m_vidSrc->GrabToImgNode(VS_FRAME_JPEG_ENCODE, VS_AUTO_THROTTLE_PRODUCER,VS_INFINITE_FRAMES,0,0,0,0);
		}
		else {
			VS_STREAM_PARAMS encParm;
			encParm.numIframes = 4;
//			encParm.desiredFramesPerSecond = VS_FRAME_RATE_AUTO;
			if (m_camAttrib.color != VS_MONO) {
				encParm.desiredFramesPerSecond = 10;
				encParm.encodeKind = VS_FRAME_JPEG_ENCODE;
			}
			else {
				encParm.desiredFramesPerSecond = 20;
				encParm.encodeKind = VS_FRAME_JPEG_ENCODE;
//				encParm.encodeKind = VS_FRAME_DJPEG_ENCODE;
			}
			
			m_vStream = VsCreateVideoStream(m_vidSrc,&encParm);
			m_nodeDisplay = VsCreateDisplayNode( m_hWnd,Flags,NULL,0);
			m_vStream->ConnectOutputTo(m_nodeDisplay);
		}
	}
	else if(nImageSource == CAM_IMG_SRC) {
		m_nodeDisplay=VsCreateVideoSrcDisplay(m_vidSrc,m_hWnd,Flags,VS_ICAP_INTR_EOF,1);
		m_vidSrc->GrabOn();
	}
	else {
		m_nodeDisplay=VsCreateBuffDisplay(m_pBuffer,m_nCurdx, m_nCurdy,m_camAttrib.dwBitsPerPixel, m_hWnd, m_camAttrib.color,Flags);
		m_vidSrc->Grab(&m_grabID,0,(DWORD)m_pBuffer, m_numImgAreas,VS_INFINITE_FRAMES,0,0,0,0);
	}
	if(!m_nodeDisplay){
		KillOpenConnections();
		::MessageBox(NULL, "Selected overlay is not supported on this hardware/driver", "", MB_OK);
		return;
	}

	if (nUsedOverlay == YCRCB_OVERLAY) {
		m_nodeDisplay->SetDestColorKey(PALETTEINDEX(dark_yellow));
	}

	// set zoom setting
	switch (nImageZoom) {
	case STRETCH_TO_FIT:
		m_nodeDisplay->SetZoom( VS_STRETCH_TO_FIT, VS_STRETCH_TO_FIT);
		break;
	case zoom20: 
		m_nodeDisplay->SetZoom( 2.0, 2.0);
		break;
	case zoom05:
		m_nodeDisplay->SetZoom( 0.5, 0.5);
		break;

	}

	// start live image
	if(nImageSource == CAM_IMG_SRC) {
		VS_ICAP_INTR_EVENT intrEvent;
		double iLaced;
		m_vidSrc->GetAcqParam(VSP_SCAN_MODE_STAT,&iLaced,0);
		// hookup interrupt and create server
		if((DWORD)iLaced == VS_ILACED) {
			intrEvent = VS_ICAP_INTR_EOF;
		}
		else {
			intrEvent = VS_ICAP_INTR_VB;
		}

		if (m_nodeDisplay->StartLiveImage(m_vidSrc, intrEvent,1) != S_OK)
			::MessageBox(NULL,"Could not create VB interrupt driven live image!", "Error", MB_OK);
	}
	else if (nImageSource == HOSTBUFF_IMGSRC) {
		m_procthrd = new PROCTHRD(this);
	}
}


void COverlayView::KillOpenConnections()
{
	// delete all active servers, image sources, sinks
	// and connections
	// do it in the reverse order than creation
	if (m_procthrd != NULL){
		delete m_procthrd;
		m_procthrd = NULL;
	}

	if (m_vStream) {
		VsDeleteVideoStream(m_vStream);
		m_vStream = NULL;
	};

	if (m_vidSrc) {
		m_vidSrc->FreezeImgNode();
		m_vidSrc->Freeze(0);
	}

	if (m_nodeDisplay) {
		VsDeleteDisplayNode(m_nodeDisplay);
		m_nodeDisplay = NULL;
	};

	if (m_pBuffer != NULL) {
		free(m_pBuffer);
		m_pBuffer = NULL;
	}
}

void COverlayView::OnInitialUpdate() 
{
	COverlayApp *theapp=(COverlayApp*)AfxGetApp();	
	CScrollView::OnInitialUpdate();

	
	// The following code is a standard initialization of an ITI
	// board and will appear in all applications using this hardware

	
	// Get the camera's basic attributes

	if (m_vidSrc) {
		m_vidSrc->GetAttr(&m_camAttrib,TRUE);

		m_nCurdx = m_camAttrib.dwWidth;
		m_nCurdy = m_camAttrib.dwHeight;
	}
	SetScrollLimits();

	RestartConnection();
	ResizeClientArea();
}


void COverlayView::OnOverlaySoftware() 
{
/*
	if((strcmp("ICP", m_iCap->m_modName) == 0) && m_iCap->m_revision > 0x13)	// PCVision Board
	{
		((CPCVision*) m_iCap)->SetYCRCBacqMode(FALSE);
	}
*/
	nUsedOverlay = SOFTWARE_OVERLAY;
	KillOpenConnections();
	InitiateGrabWithOverlay();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();

    float fZoomX;
    float fZoomY; 
	CalculateZoomVal(&fZoomX, &fZoomY);
	CPoint sp = GetScrollPosition();
	sp.x = (long)(sp.x / fZoomX);
	sp.y = (long)(sp.y / fZoomY);
	sp.x=min(sp.x, (long)m_nCurdx - 1);
	sp.y=min(sp.y, (long)m_nCurdy - 1);

	if (m_nodeDisplay &&  nImageZoom != STRETCH_TO_FIT) 
		m_nodeDisplay->SetSrcAoiPos( (WORD)sp.x, (WORD)sp.y);
}



void COverlayView::RestartConnection() 
{
	if(nUsedOverlay == SOFTWARE_OVERLAY)
		OnOverlaySoftware();
	else
		OnOverlayOnPrimary();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}


void COverlayView::OnZoomStretchToFit()
{
	if(m_nodeDisplay)
		m_nodeDisplay->SetZoom( VS_STRETCH_TO_FIT, VS_STRETCH_TO_FIT);
	nImageZoom = STRETCH_TO_FIT;
	if (m_nodeDisplay) 
		m_nodeDisplay->SetSrcAoiPos( 0,0);
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom2() 
{ 
	nImageZoom = zoom20;
	if(m_nodeDisplay) {
		m_nodeDisplay->SetZoom( 2.0, 2.0);
		m_nodeDisplay->SetSrcAoiPos( 0,0);
	}
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom1() 
{
	nImageZoom = zoom10;
	if(m_nodeDisplay) {
		m_nodeDisplay->SetZoom( 1.0, 1.0);
		m_nodeDisplay->SetSrcAoiPos( 0,0);
	}
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom05() 
{
	nImageZoom = zoom05;
	if(m_nodeDisplay) {
		m_nodeDisplay->SetZoom( 0.5, 0.5);
		m_nodeDisplay->SetSrcAoiPos( 0,0);
	}
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}


void COverlayView::OnDrawingNone() 
{
	nDrawingMode = NONE;
}

void COverlayView::OnDrawingRectangle() 
{
	nDrawingMode = RECTANGLE;
}

void COverlayView::OnDrawingCircle() 
{
	nDrawingMode = ELLIPSE;
}

void COverlayView::OnDrawingText() 
{
	nDrawingMode = TEXT;
}

void COverlayView::OnOverlaydrawingFreedrawing() 
{
	nDrawingMode = FREE;
}


void COverlayView::OnMouseMove(UINT nFlags, CPoint point)
{
	//if button is down handle mouse painting
    if(nFlags & MK_LBUTTON)
    {
        HDC hDC;
        CDC *pDC = NULL;
        CPen *pOldPen;
        CBrush *pOldBrush;
		CPoint ptOvlScalledLast;
		CPoint ptOvlScalledCurrent;
		CPoint ptOvlScalledButtonDown;

        float fZoomX;
        float fZoomY;
        CalculateZoomVal(&fZoomX, &fZoomY);

        if (nUsedOverlay == YCRCB_OVERLAY){
            pDC = GetDC();
			ptOvlScalledLast = m_LastMousePoint;
			ptOvlScalledCurrent = point;
			ptOvlScalledButtonDown = m_LButtonDownPoint;
		}else /* software overlay */{
            m_nodeDisplay->GetOverlayDC(&hDC);
			if(hDC){
				// create DC fom hDC and paint it
				pDC = CDC::FromHandle(hDC);
				ptOvlScalledLast.x = (int)(m_LastMousePoint.x/fZoomX);
				ptOvlScalledLast.y = (int)(m_LastMousePoint.y/fZoomY);
				ptOvlScalledCurrent.x = (int)(point.x/fZoomX);
				ptOvlScalledCurrent.y = (int)(point.y/fZoomY);
				ptOvlScalledButtonDown.x = (int)(m_LButtonDownPoint.x/fZoomX);
				ptOvlScalledButtonDown.y = (int)(m_LButtonDownPoint.y/fZoomY);
			}
        }

        if(!pDC)
            return;

        switch(nDrawingMode){
        case FREE:
				if(m_pCurrentElem){
					if( nUsedOverlay != SOFTWARE_OVERLAY)
						pOldPen = pDC->SelectObject(m_pScalledPen);
					else
						pOldPen = pDC->SelectObject(m_pPen);

					pDC->MoveTo(ptOvlScalledLast.x, ptOvlScalledLast.y);
					pDC->LineTo(ptOvlScalledCurrent.x, ptOvlScalledCurrent.y);
					((CFreeLine*)m_pCurrentElem)->AddPoint((int)(point.x/fZoomX), (int)(point.y/fZoomY));
					pDC->SelectObject(*pOldPen);
				}
				break;
        case RECTANGLE:
                //if we did draw something before, then erase it
                if(m_LastMousePoint.x != -1 && m_LastMousePoint.y != -1){
                    pOldBrush = pDC->SelectObject(m_pTransparentBrush);
                    pOldPen = pDC->SelectObject(m_pTransparentPen);
                    pDC->Rectangle( min(ptOvlScalledButtonDown.x, ptOvlScalledLast.x),
									min(ptOvlScalledButtonDown.y, ptOvlScalledLast.y),
									max(ptOvlScalledButtonDown.x, ptOvlScalledLast.x),
									max(ptOvlScalledButtonDown.y, ptOvlScalledLast.y));
                    pDC->SelectObject(pOldBrush);
                    pDC->SelectObject(pOldPen);
                }
                pOldBrush = pDC->SelectObject(m_pBrush);
                pOldPen = pDC->SelectObject(m_pPen1);
                pDC->Rectangle( min(ptOvlScalledButtonDown.x, ptOvlScalledCurrent.x),
								min(ptOvlScalledButtonDown.y, ptOvlScalledCurrent.y),
								max(ptOvlScalledButtonDown.x, ptOvlScalledCurrent.x),
								max(ptOvlScalledButtonDown.y, ptOvlScalledCurrent.y));
                pDC->SelectObject(pOldBrush);
                pDC->SelectObject(pOldPen);
                break;
        case ELLIPSE:
                //if we did draw something before, then erase it
                if(m_LastMousePoint.x != -1 && m_LastMousePoint.y != -1){
                    pOldBrush = pDC->SelectObject(m_pTransparentBrush);
                    pOldPen = pDC->SelectObject(m_pTransparentPen);
                    pDC->Ellipse(	min(ptOvlScalledButtonDown.x, ptOvlScalledLast.x),
									min(ptOvlScalledButtonDown.y, ptOvlScalledLast.y),
									max(ptOvlScalledButtonDown.x, ptOvlScalledLast.x),
									max(ptOvlScalledButtonDown.y, ptOvlScalledLast.y));

                    pDC->SelectObject(pOldBrush);
                    pDC->SelectObject(pOldPen);
                }
                pOldBrush = pDC->SelectObject(m_pBrush);
                pOldPen = pDC->SelectObject(m_pPen1);
                pDC->Ellipse(	min(ptOvlScalledButtonDown.x, ptOvlScalledCurrent.x),
								min(ptOvlScalledButtonDown.y, ptOvlScalledCurrent.y),
								max(ptOvlScalledButtonDown.x, ptOvlScalledCurrent.x),
								max(ptOvlScalledButtonDown.y, ptOvlScalledCurrent.y));
                pDC->SelectObject(pOldBrush);
                pDC->SelectObject(pOldPen);
            break;
        case TEXT:
				pDC->SetBkColor(m_TransparentColor);
                //if we did draw something before, then erase it
                if(m_LastMousePoint.x != -1 && m_LastMousePoint.y != -1){
					pDC->SetTextColor(m_TransparentColor);
					pDC->TextOut(ptOvlScalledLast.x, ptOvlScalledLast.y, TEXT_MESSAGE);
				}
				pDC->SetTextColor(m_CurrentColor);
				pDC->TextOut((int)(point.x/fZoomX), (int)(point.y/fZoomY), TEXT_MESSAGE);
            break;
        }

        if(nUsedOverlay == YCRCB_OVERLAY){
            ReleaseDC(pDC);
        }else{
            pDC->DeleteTempMap();
            m_nodeDisplay->ReleaseOverlayDC(hDC);
        }
    }
    m_LastMousePoint.x = point.x;
    m_LastMousePoint.y = point.y;

    CScrollView::OnMouseMove(nFlags, point);
}

void COverlayView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_LastMousePoint = m_LButtonDownPoint = point;
    bDrawingActive = TRUE;

    float fZoomX;
    float fZoomY;
	CalculateZoomVal(&fZoomX, &fZoomY);

    if(nDrawingMode == FREE){
        m_pCurrentElem =  new CFreeLine(m_CurrentColor,m_iLineThickness);
        ((CFreeLine*)m_pCurrentElem)->AddPoint((int)(point.x/fZoomX), (int)(point.y/fZoomY));
    }

    CScrollView::OnLButtonDown(nFlags, point);
}

void COverlayView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (bDrawingActive == TRUE) {
        COverlayDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

        float fZoomX;
        float fZoomY;
        CalculateZoomVal(&fZoomX, &fZoomY);

		m_LastMousePoint.x = (int)(m_LastMousePoint.x/fZoomX);
		m_LastMousePoint.y = (int)(m_LastMousePoint.y/fZoomY);
		m_LButtonDownPoint.x = (int)(m_LButtonDownPoint.x/fZoomX);
		m_LButtonDownPoint.y = (int)(m_LButtonDownPoint.y/fZoomY);


        switch(nDrawingMode){
        case FREE:
			if(	m_pCurrentElem ){
                pDoc->m_ImgElemList.AddTail(m_pCurrentElem);
				m_pCurrentElem = NULL;
			}
            break;
        case RECTANGLE:
                pDoc->m_ImgElemList.AddTail(new CORectangle(m_CurrentColor, m_LastMousePoint, m_LButtonDownPoint));
				m_pCurrentElem = NULL;
				Invalidate();
				SendMessage(WM_PAINT);
            break;
        case ELLIPSE:
				pDoc->m_ImgElemList.AddTail(new COEllipse(m_CurrentColor, m_LastMousePoint, m_LButtonDownPoint));
				m_pCurrentElem = NULL;
				Invalidate();
				SendMessage(WM_PAINT);
            break;
        case TEXT:
                pDoc->m_ImgElemList.AddTail(new COText(m_CurrentColor, point, TEXT_MESSAGE));
				m_pCurrentElem = NULL;
				Invalidate();
				SendMessage(WM_PAINT);
            break;
        }
    }

    bDrawingActive = FALSE;
    m_LastMousePoint.x = -1;
    m_LastMousePoint.y = -1;

	//Invalidate();

    CScrollView::OnLButtonUp(nFlags, point);
}


void COverlayView::OnImageSourceImgnode() 
{
	nImageSource = NODE_IMG_SRC;
	RestartConnection();
	
}

void COverlayView::OnImagesourceFrame() 
{
	nImageSource = CAM_IMG_SRC;
	RestartConnection();
}

void COverlayView::OnImagesourceHostbuff() 
{
	nImageSource = HOSTBUFF_IMGSRC;
	RestartConnection();
}

void COverlayView::OnColorChange(UINT nID) 
{
	CurrentColorEnum = (STATIC_COLOR)(nID - ID_COLORS_TRANSPARENT);
	m_CurrentColor = system_colors[CurrentColorEnum];
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
}


void COverlayView::OnOverlayOnPrimary() 
{
/*
	if((strcmp("ICP", m_iCap->m_modName) == 0) && m_iCap->m_revision > 0x13)	// PCVision Board
	{
		((CPCVision*) m_iCap)->SetYCRCBacqMode(TRUE);
	}
*/
	nUsedOverlay = YCRCB_OVERLAY;
	nRemapActive = 0;
	KillOpenConnections();
	CBrush cbr;
	RECT rect;
	CDC *hdc;

	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	(hdc = GetDC())->FillRect(&rect,&cbr);
	cbr.DeleteObject();
	ReleaseDC(hdc);

	InitiateGrabWithOverlay();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}


void COverlayView::OnOverlayPrimaryRemap() 
{
/*
	if((strcmp("ICP", m_iCap->m_modName) == 0) && m_iCap->m_revision > 0x13)	// PCVision Board
	{
		((CPCVision*) m_iCap)->SetYCRCBacqMode(TRUE);
	}
*/
	// this is overlay on primary with activated remapping
	OnOverlayOnPrimary();
	nRemapActive = 1;
	if (m_nodeDisplay) {
		m_nodeDisplay->SetRemapColor(0,19,RGB(0xff,0x0,0x0));
		m_nodeDisplay->SetRemapColor(246,255,RGB(0x0,0xff,0x0));
	}
}

void COverlayView::CalculateZoomVal(float *pfZoomX, float *pfZoomY)
{
    RECT SinkClientWindowRect;
    GetClientRect(&SinkClientWindowRect);

    switch(nImageZoom){
        case STRETCH_TO_FIT:
            *pfZoomX = (float)SinkClientWindowRect.right/m_nCurdx;
            *pfZoomY = (float)SinkClientWindowRect.bottom/m_nCurdy;
            break;
        case zoom05:
            *pfZoomX = 0.5;
            *pfZoomY = 0.5;
            break;
        case zoom10:
            *pfZoomX = 1.0;
            *pfZoomY = 1.0;
            break;
        case zoom20:
            *pfZoomX = 2.0;
            *pfZoomY = 2.0;
            break;
    }
}

void COverlayView::DeleteTransparentPenAndBrush()
{
    if(m_pTransparentThickPen)
        delete m_pTransparentThickPen;
    if(m_pTransparentPen)
        delete m_pTransparentPen;
    if(m_pTransparentBrush)
        delete m_pTransparentBrush;
}

void COverlayView::ReCreateTransparentPenAndBrush()
{

    float pfZoomX;
    float pfZoomY;
    CalculateZoomVal(&pfZoomX, &pfZoomY);

	DeleteTransparentPenAndBrush();

    if(nUsedOverlay == SOFTWARE_OVERLAY )
        m_TransparentColor = RGB(0,0,0);
    else
        m_TransparentColor = YCRCB_COLOR_KEY;

    m_pTransparentThickPen = new CPen(PS_SOLID,(int)(m_iLineThickness*(pfZoomX+pfZoomY)/2), m_TransparentColor);
    m_pTransparentPen = new CPen(PS_SOLID, 1, m_TransparentColor );
    m_pTransparentBrush = new CBrush(m_TransparentColor);
}

void COverlayView::DeletePenAndBrush()
{
    if(m_pScalledPen)
        delete m_pScalledPen;
    if(m_pPen)
        delete m_pPen;
    if(m_pPen1)
        delete m_pPen1;
    if(m_pBrush)
        delete m_pBrush;
}

void COverlayView::ReCreatePenAndBrush()
{
	float fZoomX;
    float fZoomY;
    CalculateZoomVal(&fZoomX, &fZoomY);

	DeletePenAndBrush();

    m_pScalledPen = new CPen(PS_SOLID, (int)(m_iLineThickness*(fZoomX+fZoomY)/2),m_CurrentColor );
    m_pPen = new CPen(PS_SOLID, m_iLineThickness, m_CurrentColor );
    m_pPen1 = new CPen(PS_SOLID, 1,m_CurrentColor );
    m_pBrush = new CBrush(m_CurrentColor );
}

void COverlayView::ColorFillCDC(COLORREF color, CDC * pCDC)
{
    CBrush KeyColorBrush;
    RECT rect;
	if( nUsedOverlay == YCRCB_OVERLAY){
		GetClientRect(&rect);
	}else{
		rect.left=rect.top=0;
		rect.right=m_nCurdx;
		rect.bottom=m_nCurdy;
	}
    KeyColorBrush.CreateSolidBrush(color);
    pCDC->FillRect(&rect,&KeyColorBrush);
    KeyColorBrush.DeleteObject();
}



void COverlayView::ResizeClientArea()
{
    if(nImageZoom == STRETCH_TO_FIT)
        return;

    switch(nImageZoom){
        case zoom05:
            SetClientWndSize((int)(m_nCurdx*0.5), (int)(m_nCurdy*0.5));
            break;
        case zoom10:
            SetClientWndSize((int)(m_nCurdx*1.0), (int)(m_nCurdy*1.0));
            break;
        case zoom20:
            SetClientWndSize((int)(m_nCurdx*2.0), (int)(m_nCurdy*2.0));
            break;
    }
}

void COverlayView::SetClientWndSize(int iWidth, int iHeight)
{
	HWND hParentWnd = ::GetParent(m_hWnd); 
    if (hParentWnd == NULL)
        return;

	for (int i=0; i<2;i++) {
		// Do the following twice because if border size changes it's necessary to hit steady-state
		RECT SinkClientWindowRect;
		GetClientRect(&SinkClientWindowRect);
		
		RECT ClientWindowRect;
		::GetClientRect(hParentWnd,&ClientWindowRect);
		long VertAdjust = ClientWindowRect.bottom - SinkClientWindowRect.bottom;
		long HorzAdjust = ClientWindowRect.right - SinkClientWindowRect.right;
		
		RECT WindowRect;
		::GetWindowRect(hParentWnd,&WindowRect);
		
		long lBorderHorz = (WindowRect.right - WindowRect.left) - ClientWindowRect.right;
		long lBorderTop = (WindowRect.bottom - WindowRect.top) - ClientWindowRect.bottom;
				
		::MoveWindow(hParentWnd,WindowRect.left,WindowRect.top,
			iWidth + lBorderHorz +  HorzAdjust,
			iHeight + lBorderTop + VertAdjust,
			TRUE);
				
		::SendMessage(hParentWnd,WM_PAINT, 0, 0);
		::SendMessage(m_hWnd,WM_PAINT, 0, 0);
	}
}


void COverlayView::RepaintOverlay(CDC *pOverlayDC, float fZoomX, float fZoomY)
{
    COverlayDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    if(!pDoc->m_ImgElemList.IsEmpty())
    {
        POSITION pos;
        COlayElem *pImgElement;
        pos = pDoc->m_ImgElemList.GetHeadPosition();
        pImgElement = (COlayElem*)pDoc->m_ImgElemList.GetAt(pos);
        pImgElement->Display(pOverlayDC, fZoomX, fZoomY, m_TransparentColor);
        // Iterate through the list in head-to-tail order.
        while(pDoc->m_ImgElemList.GetNext(pos) && pos!=NULL){
            pImgElement = (COlayElem*)pDoc->m_ImgElemList.GetAt(pos);
            pImgElement->Display(pOverlayDC, fZoomX, fZoomY, m_TransparentColor);
        }
    }
}


BOOL COverlayView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void COverlayView::OnClearoverlay() 
{
    COverlayDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

	if(!pDoc->m_ImgElemList.IsEmpty())
	{
	    POSITION pos;
		COlayElem *pImgElement;
		pos = pDoc->m_ImgElemList.GetHeadPosition();
		pImgElement = (COlayElem*)pDoc->m_ImgElemList.GetAt(pos); 
		delete pImgElement;
		// Iterate through the list 
		while(pDoc->m_ImgElemList.GetNext(pos) && pos!=NULL){
			pImgElement = (COlayElem*)pDoc->m_ImgElemList.GetAt(pos);
			delete pImgElement;
		}
		pDoc->m_ImgElemList.RemoveAll();
	}	

	Invalidate();
	SendMessage(WM_PAINT);
}


void COverlayView::SetScrollLimits()
{
    float pfZoomX;
    float pfZoomY;
    CalculateZoomVal(&pfZoomX, &pfZoomY);

	CSize sizeTotal;
	if ( nImageZoom == STRETCH_TO_FIT) {
		sizeTotal.cx = 0;
		sizeTotal.cy = 0;
	}
	else {
		sizeTotal.cx = (long)((m_nCurdx-4)*pfZoomX);
		sizeTotal.cy = (long)((m_nCurdy-4)*pfZoomY);
	}
	SetScrollSizes(MM_TEXT, sizeTotal);
};

BOOL COverlayView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	Invalidate();
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}


void COverlayView::OnDestroy() 
{
	KillOpenConnections();
	CScrollView::OnDestroy();
		
}

