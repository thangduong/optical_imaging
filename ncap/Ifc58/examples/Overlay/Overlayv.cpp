/********************************************************************
 *
 * MODULE
 *    overlayv.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/overlay/OVERLAYV.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 10/16/03 9:50a $
 *
 * ABSTRACT
 *    IFC Overlay example program
 *    This example shows how to use YCRCB and software overlay.
 *              
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/  
// overlayv.cpp : implementation of the COverlayView class
//

#include "stdafx.h"
#include "overlay.h"

#include "overlayd.h"
#include "overlayv.h"
#include "mainfrm.h"
#include "camsel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "OElem.h"

#include <ifc.h>
#include <pcvision.h>

#define YCRCB_COLOR_KEY RGB(0x80,0x80,0)
#define TEXT_MESSAGE "** Overlay Demo **"

//global variables 
int     nUsedOverlay		= SOFTWARE_OVERLAY;
int     nRemapActive		= 0;
int		nDrawingMode		= FREE;
static BOOL   bDrawingActive = FALSE;
int	 nImageSource = CAM_IMG_SRC;
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
	ON_COMMAND(ID_ZOOM_ITXSTRETCHTOFIT, OnZoomItxstretchtofit)
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
	ON_COMMAND(ID_SOFTWAREOVERLAYWITHREMAP, OnSoftwareOverlayWithRemap)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_COLORS_TRANSPARENT, ID_COLORS_WHITE, OnColorChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COverlayView construction/destruction

COverlayView::COverlayView()
{
	//initialize member variables
	m_nCurdx = 0;
	m_nCurdy = 0;
	m_iCap               = NULL;
	m_cam                = NULL;
	m_hSrvconn              = NULL;
	m_hSrvsink = NULL;
	m_hSinkTemplate = NULL;
	m_hOverlay = NULL;
	m_hImgsrc = NULL;
	m_hGrabId = 0;

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
}

COverlayView::~COverlayView()
{
	// delete all open sources, sinks, connections and servers
	KillOpenConnections();
	// on exit cleanup hardware
	DeleteTransparentPenAndBrush();
	DeletePenAndBrush();
	if (m_iCap)
		delete m_iCap;
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


	CalculateZoomVal(&fZoomX, &fZoomY);

	CPoint sp = GetScrollPosition();
	sp.x = (long)(sp.x / fZoomX);
	sp.y = (long)(sp.y / fZoomY);

	sp.x=min(sp.x, (long)m_nCurdx - 1);
	sp.y=min(sp.y, (long)m_nCurdy - 1);
													 
	if (m_hImgsrc &&  nImageZoom != STRETCH_TO_FIT) 
		m_hImgsrc->SetAoiPos( (WORD)sp.x, (WORD)sp.y);

    // paint sink window with YCRCB_COLOR_KEY
    if( nUsedOverlay == YCRCB_OVERLAY){
        ColorFillCDC(YCRCB_COLOR_KEY, pDC);
		OnPrepareDC(pDC);
        pOverlayDC = pDC;
    }
	else {
		// software overlay is in seperate buffer, but we still want to
		// repaint it because of the zoom (fit setting)
        if(!m_hOverlay)
            return;
        hDC=  m_hSrvconn->GetOverlayDC();
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
		m_hSrvconn->ReleaseOverlayDC(hDC);
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

// create software overlay
void COverlayView::CreateSwOverlay(DWORD m_nCurdx, DWORD m_nCurdy ) 
{
	m_hOverlay = IfxCreateOverlay(SW_OVERLAY,(WORD)m_nCurdx, (WORD)m_nCurdy);
	if(!m_hOverlay){
		KillOpenConnections();
		::MessageBox(NULL, "Creation of overlay failed", "", MB_OK);
		return;
	}
}


// initiate grab
void COverlayView::InitiateGrabWithOverlay() 
{
	if(!m_hOverlay && nUsedOverlay != YCRCB_OVERLAY)
		return;

	if (strcmp("PCR", m_iCap->m_modName) == 0)	// PC-RGB Board
	{
		if (m_camAttrib.dwBitsPerPixel != 8) {
			if (nUsedOverlay == YCRCB_OVERLAY) {
				m_cam->SetAcqParam(P_COLOR_SPACE_CONV,IFC_CSC_RGB_TO_YCRCB422);
				m_cam->SetAcqParam(P_PIXEL_COLOR,IFC_YCRCB);
			}
			else {
				m_cam->SetAcqParam(P_COLOR_SPACE_CONV,IFC_CSC_RGB_TO_RGB);
				m_cam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB);
			}
			m_cam->GetAttr(&m_camAttrib);
		}
	}



	// allocate host buffer for host grab
	if(!m_pBuffer)
		if((m_pBuffer =  (BYTE*)malloc(m_nCurdx * m_nCurdy * m_camAttrib.dwBytesPerPixel * m_numImgAreas)) == NULL)
			return;

	// create image source
	if(nImageSource == CAM_IMG_SRC) {
		m_cam->Grab();
		m_hImgsrc = IfxCreateImgSrc(m_cam);
		if(!m_hImgsrc){
			KillOpenConnections();
			::MessageBox(NULL, "Creation of image source failed", "", MB_OK);
			return;
		}
	}
	else {
		// This example demonstrates a Grab to buffer where the data is left justified.
		// Left Justified 10 or 12 bit data in a 16 bit pixel makes it easy and is faster to display image, since the
		// 8 MSBs are available in a single BYTE.
		m_hGrabId = m_cam->Grab(IFC_GOPT_LEFTJUSTIFIED|IFC_GOPT_AUTO_FRAME_LOCK,(unsigned char *)m_pBuffer, m_numImgAreas);
		DWORD imgSrcOptions=0;
		if (m_cam->AcqParamSupported(P_BAYER_FILTER) && m_cam->GetAcqParam(P_BAYER_FILTER) == IFC_BAYER_GB_RG)
			imgSrcOptions |= IFC_IMGSRC_OPT_BAYER_GB_RG; 

		m_hImgsrc = IfxCreateImgSrc( (unsigned char *)m_pBuffer, (WORD)m_nCurdx, (WORD)m_nCurdy, (WORD)m_camAttrib.dwBitsPerPixel, m_camAttrib.color,0,0,0,0,imgSrcOptions);
		if(!m_hImgsrc){
			KillOpenConnections();
			::MessageBox(NULL, "Creation of image source failed", "", MB_OK);
			return;
		}

	}
	if ( (strcmp("CL2", m_iCap->m_modName) == 0 || strcmp("X64", m_iCap->m_modName) == 0)
		&& m_camAttrib.dwBitsPerPixel > 8 && m_camAttrib.dwBitsPerPixel < 16 ) {	// PC2-Camlink Board
		m_hImgsrc->SetOptions(IFC_IMGSRC_OPT_PIX_LEAST_SIG);
	}


	if (nUsedOverlay == YCRCB_OVERLAY) {
		m_hSinkTemplate->SetDestColorKey(dark_yellow);
		m_hSrvconn=IfxCreateImgConn(m_hImgsrc, m_hSinkTemplate);
		if(!m_hSrvconn){
			KillOpenConnections();
			::MessageBox(NULL, "Selected overlay is not supported on this hardware/driver", "", MB_OK);
			return;
		}
	}
	else {
		m_hSinkTemplate=IfxCreateImgSink(m_hWnd,DIB_SINK, 0, 0, (WORD)m_nCurdx, (WORD)m_nCurdy );
		if (!m_hSinkTemplate) {
			KillOpenConnections();
			::MessageBox(NULL, "Creation of sink failed", "", MB_OK);
			return;
		}
		
		m_hSrvconn=IfxCreateImgConn(m_hImgsrc, m_hSinkTemplate, m_hOverlay);
		if(!m_hSrvconn){
			KillOpenConnections();
			::MessageBox(NULL, "Creation of image connection failed", "", MB_OK);
			return;
		}
	}
	m_hSrvsink=m_hSrvconn->GetSink();

	// set zoom setting
	switch (nImageZoom) {
	case STRETCH_TO_FIT:
		m_hSrvsink->SetZoom( IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
		break;
	case zoom20: 
		m_hSrvsink->SetZoom( 2.0, 2.0);
		break;
	case zoom05:
		m_hSrvsink->SetZoom( 0.5, 0.5);
		break;

	}

	// start live image
	if(nImageSource == CAM_IMG_SRC)
	{
		ICAP_INTR_EVENT intrEvent;
		CICamera *pCamera = m_iCap->GetCam(0);

		// hookup interrupt and create server
		if (pCamera->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED 
			|| strcmp("P2V", m_iCap->m_modName) == 0 || strcmp("NSP", m_iCap->m_modName) == 0)

		{
			intrEvent = ICAP_INTR_EOF;
		}
		else
		{
			intrEvent = ICAP_INTR_VB;
		}

		if (!m_hSrvconn->StartLiveImage(m_cam, intrEvent))
			::MessageBox(NULL,"Could not create VB interrupt driven live image!", "Error", MB_OK);
	}
	else
	{
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

	if (m_cam){
		if (m_hGrabId){
			m_cam->Freeze(m_hGrabId);
			m_hGrabId = 0;
		} else
			m_cam->Freeze();
	}


	if (m_hSrvconn != NULL) {
		delete m_hSrvconn;
		m_hSrvconn = NULL;
		m_hSrvsink = NULL; // Null the image connection internal sink handle
	};

	if (m_hSinkTemplate != NULL) {
		delete m_hSinkTemplate;
		m_hSinkTemplate = NULL;
	};

	if (m_hOverlay != NULL) {
		delete m_hOverlay;
		m_hOverlay = NULL;
	};

	if (m_hImgsrc != NULL) {
		delete m_hImgsrc;
		m_hImgsrc = NULL;
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

	//Setup hardware and get basic information about camera
	char modName[80];
	char fileName[80];

	modName[0]  = '\0';
	fileName[0] = '\0';

	if(theapp->m_lpCmdLine && theapp->m_lpCmdLine[0])
	{
		strcpy(modName, theapp->m_lpCmdLine);
	}
	else
	{
		CITIMods topo;
		ITI_PARENT_MOD *pICap;
		
		// MAX_MODNAME_LEN
		// How to handle sequence numbers ?

		pICap = topo.GetFirst();

		if(pICap)
		{
			strcpy(modName, pICap->name);
		}
	}

	if(modName)
	{
		if(strcmp(modName, "ICP") == 0)
		{
			strcpy(fileName, "PCVtest.txt");
		}
		else
		{
			wsprintf(fileName,"%stest.txt", modName);
		}
	}

	if (!(m_iCap=IfxCreateCaptureModule(modName,0,fileName))) {
		if (!(m_iCap=IfxCreateCaptureModule(modName,0))) {
			::MessageBox(NULL,"No Image Capture Module detected",
				"No Module",MB_OK);
			exit(0);
		}
		// If user config file not found, add all camera definitions in camera database directory
		m_iCap->ProcessCameraFilesInDir("camdb",TRUE);
		m_cam = m_iCap->GetCam(0);
		CCamSel dg(this);
		dg.DoModal();
	}
	if (!(m_cam = m_iCap->GetCam(0))) {
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.",
			"No Port 0 Camera",MB_OK);
		return;
	}

	// Get the camera's basic attributes

	m_cam->GetAttr(&m_camAttrib);

	m_nCurdx = m_camAttrib.dwWidth;
	m_nCurdy = m_camAttrib.dwHeight;

	SetScrollLimits();

	RestartConnection();
	ResizeClientArea();
}


void COverlayView::OnOverlaySoftware() 
{
	if((strcmp("ICP", m_iCap->m_modName) == 0) && m_iCap->m_revision > 0x13)	// PCVision Board
	{
		((CPCVision*) m_iCap)->SetYCRCBacqMode(FALSE);
	}

	nUsedOverlay = SOFTWARE_OVERLAY;
	KillOpenConnections();
	CreateSwOverlay(m_nCurdx, m_nCurdy);
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

	if (m_hImgsrc &&  nImageZoom != STRETCH_TO_FIT) 
		m_hImgsrc->SetAoiPos( (WORD)sp.x, (WORD)sp.y);
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

void COverlayView::OnZoomItxstretchtofit() 
{
	if(m_hSrvconn)
		m_hSrvsink->SetZoom( IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
	nImageZoom = STRETCH_TO_FIT;
	if (m_hImgsrc) 
		m_hImgsrc->SetAoiPos( 0,0);
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom2() 
{ 
	if(m_hSrvconn)
		m_hSrvsink->SetZoom( 2.0, 2.0);
	nImageZoom = zoom20;
	if (m_hImgsrc) 
		m_hImgsrc->SetAoiPos( 0,0);
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom1() 
{
	if(m_hSrvconn)
		m_hSrvsink->SetZoom( 1.0, 1.0);
	nImageZoom = zoom10;
	if (m_hImgsrc) 
		m_hImgsrc->SetAoiPos( 0,0);
	SetScrollLimits();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}

void COverlayView::OnZoom05() 
{
	if(m_hSrvconn)
		m_hSrvsink->SetZoom( 0.5, 0.5);
	nImageZoom = zoom05;
	if (m_hImgsrc) 
		m_hImgsrc->SetAoiPos( 0,0);
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
			if(!m_hOverlay)
				return;
            hDC= m_hSrvconn->GetOverlayDC();
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
            m_hSrvconn->ReleaseOverlayDC(hDC);
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



void COverlayView::OnImagesourceFrame() 
{
	// TODO: Add your command handler code here
	nImageSource = CAM_IMG_SRC;
	RestartConnection();
}

void COverlayView::OnImagesourceHostbuff() 
{
	// TODO: Add your command handler code here
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
	KillOpenConnections();
	nUsedOverlay = YCRCB_OVERLAY;
	nRemapActive = 0;
	CBrush cbr;
	RECT rect;
	CDC *hdc;

	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	(hdc = GetDC())->FillRect(&rect,&cbr);
	cbr.DeleteObject();
	ReleaseDC(hdc);

	if ((m_hSinkTemplate=IfxCreateImgSink(m_hWnd,YCRCB_SINK,  0, 0, (WORD)m_nCurdx, (WORD)m_nCurdy))==NULL) {
		::MessageBox(NULL, "YCRCB Overlay not suported on this video hardware/driver", "", MB_OK);
		return;
	}
	if((strcmp("ICP", m_iCap->m_modName) == 0) && m_iCap->m_revision > 0x13)	// PCVision Board
		((CPCVision*) m_iCap)->SetYCRCBacqMode(TRUE);

	InitiateGrabWithOverlay();
	ReCreateTransparentPenAndBrush();
	ReCreatePenAndBrush();
	ResizeClientArea();
}


void COverlayView::OnOverlayPrimaryRemap() 
{

	// this is overlay on primary with activated remapping
	OnOverlayOnPrimary();
	nRemapActive = 1;
	if (m_hSrvconn) {
		m_hSrvsink->SetRemapColor(0,19,RGB(0xff,0x0,0x0));
		m_hSrvsink->SetRemapColor(246,255,RGB(0x0,0xff,0x0));
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

void COverlayView::OnSoftwareOverlayWithRemap() 
{
	OnOverlaySoftware();
	nRemapActive = 1;
	if (m_hSrvconn) {
		// First 10 and last 10 colors are reserved for system colors to draw overlay content.
		// To keep values available for these overlay colors, mono 8-bit image content is clipped
		// to impose a floor of 10 and a ceiling of 245.
		// So remap colors >= 10 and <= 245
		m_hSrvsink->SetRemapColor(10,29,RGB(0xff,0x0,0x0));
		m_hSrvsink->SetRemapColor(236,245,RGB(0x0,0xff,0x0));
	}
	
}
