/******************************************************************************
 *
 * MODULE
 *    LargeAcqView.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PiPAcq/LargeAcqView.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/13/00 4:24p $
 *
 * ABSTRACT
 *    PCDig Large Frame Acquisition Example Program
 *	This program shows how the PCDig can be used to acquire very large frames.
 *  To see the power of this program use a line scan camera and set the image height
 *  to a large value, e.g.,
 *  HEIGHT_PIXELS = 8192
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "pipacq.h"

#include "LargeAcqDoc.h"
#include "LargeAcqView.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define YCRCB_COLOR_KEY RGB(0x80,0x80,0)

typedef enum {
	transparent, 
	dark_red, 
	dark_green, 
	dark_yellow, 
	dark_blue, 
	dark_magenta, 
	dark_cyan, 
	light_gray1,
	money_green, 
	sky_blue, 
	cream, 
	light_gray2, 
	medium_gray, 
	red, 
	green, 
	yellow, 
	blue, 
	magenta, 
	cyan, 
	white
}STATIC_COLOR;

/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView

IMPLEMENT_DYNCREATE(CLargeAcqView, CScrollView)

BEGIN_MESSAGE_MAP(CLargeAcqView, CScrollView)
	//{{AFX_MSG_MAP(CLargeAcqView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_ACQUIRE_GRAB, OnAcquireGrab)
	ON_COMMAND(ID_ACQUIRE_SNAP, OnAcquireSnap)
	ON_COMMAND(ID_ACQUIRE_FREEZE, OnAcquireFreeze)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView construction/destruction

CLargeAcqView::CLargeAcqView()
{
	m_hImgConn = NULL;
	m_hSinkTemplate = NULL;
	m_hImgSrc = NULL;
	m_pImgBuff = NULL;
	m_pHostBuffFrame = NULL;
	m_grabThread = NULL;	
	m_DrawMode = DIB_SINK;
	m_numFramesInHostBuf = 2;
	m_SnapDialog = NULL;

//	m_DrawMode = YCRCB_SINK;
}

CLargeAcqView::~CLargeAcqView()
{

}


BOOL CLargeAcqView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

void CLargeAcqView::ColorFillCDC(COLORREF color, CDC * pCDC)
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
    CBrush KeyColorBrush;
    RECT rect;
    if ( m_DrawMode == YCRCB_SINK) {
		GetClientRect(&rect);
		KeyColorBrush.CreateSolidBrush(color);
		pCDC->FillRect(&rect,&KeyColorBrush);
		KeyColorBrush.DeleteObject();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView drawing

void CLargeAcqView::OnDraw(CDC* pDC)
{
	CLargeAcqDoc* pDoc = GetDocument();
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	ASSERT_VALID(pDoc);

	CPoint sp = GetScrollPosition();

	sp.x=min(sp.x, (long)theapp->m_camAttrib.dwWidth - 1);
	sp.y=min(sp.y, (long)theapp->m_camAttrib.dwHeight - 1);

	if (m_hImgSrc)
		m_hImgSrc->SetAoiPos( (WORD)sp.x, (WORD)sp.y);

    if ( m_DrawMode == YCRCB_SINK) {
        ColorFillCDC(YCRCB_COLOR_KEY, pDC);
		OnPrepareDC(pDC);
    }

	if (m_hImgConn)
		m_hImgConn->Display();		

}


void CLargeAcqView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();


	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	DWORD imgDx=theapp->m_camAttrib.dwWidth;	// DX of the image area being acquired
	DWORD imgDy=theapp->m_camAttrib.dwHeight;  // DY of the image area being acquired

	CSize sizeTotal;
	sizeTotal.cx = (long)imgDx;
	sizeTotal.cy = (long)imgDy;
	SetScrollSizes(MM_TEXT, sizeTotal);
	
	m_FrameSize = imgDx * imgDy * theapp->m_camAttrib.dwBytesPerPixel;	
	MEMORYSTATUS memstat;
	GlobalMemoryStatus(&memstat);
	if ((m_FrameSize * m_numFramesInHostBuf) > (memstat.dwTotalPhys-0x1800000)) {
		MessageBox("You don't have enough memory for this operation."
			"Try reducing your camera HEIGHT_PIXELS value.", "Memory Error");
		return;
	}
	else if ((m_FrameSize * m_numFramesInHostBuf) > memstat.dwAvailPhys) {
		if (MessageBox("Page swapping will have to occur for this operation to complete, "
			" the snap could take minutes. Are you sure you want to continue?",
			"Memory Alert",MB_OKCANCEL) == IDCANCEL )
			return;
		
	}
	
	m_pImgBuff = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_FrameSize * m_numFramesInHostBuf);
	
	DWORD sinkDx = min((DWORD)GetDC()->GetDeviceCaps(HORZRES),imgDx);
	DWORD sinkDy = min((DWORD)GetDC()->GetDeviceCaps(VERTRES),imgDy);

	m_hImgSrc = IfxCreateImgSrc( (unsigned char *)m_pImgBuff, (WORD)imgDx, (WORD)imgDy, (WORD)theapp->m_camAttrib.dwBitsPerPixel, 
		theapp->m_camAttrib.color,0,0,(WORD)sinkDx,(WORD)sinkDy);
	
	m_hSinkTemplate=IfxCreateImgSink(m_hWnd,DIB_SINK, 0, 0, (WORD)imgDx, (WORD)imgDy );
    if ( m_DrawMode == YCRCB_SINK) {
		m_hSinkTemplate->SetDestColorKey(dark_yellow);
	}	
	m_hImgConn=IfxCreateImgConn(m_hImgSrc, m_hSinkTemplate);
	if(!m_hImgConn){
		::MessageBox(NULL, "Creation of image connection failed", "", MB_OK);
		return;
	}
	m_hImgSink=m_hImgConn->GetSink();

	m_grabThread = new CTrgThrd(this);
	m_SnapDialog = new CDlgsnap(this);
	m_SnapDialog->Create(IDD_DLGSNAP);



}


/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView printing

BOOL CLargeAcqView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLargeAcqView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLargeAcqView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void CLargeAcqView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.

	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	if (m_grabThread) {
		delete m_grabThread;
		m_grabThread = NULL;
	}
	if (m_SnapDialog) {
		delete m_SnapDialog;
		m_SnapDialog = NULL;
	}
	theapp->m_cam->Freeze();
	if (m_hImgConn) {
		delete m_hImgConn;
		m_hImgConn = NULL;
	}
	if (m_hSinkTemplate) {
		delete m_hSinkTemplate;
		m_hSinkTemplate = NULL;
	}
	if (m_hImgSrc) {
		delete m_hImgSrc;
		m_hImgSrc = NULL;
	}
	if (m_pImgBuff) {
		GlobalFreePtr(m_pImgBuff);
		m_pImgBuff = NULL;
		m_pHostBuffFrame = NULL;
	}


   CScrollView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView diagnostics

#ifdef _DEBUG
void CLargeAcqView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLargeAcqView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLargeAcqDoc* CLargeAcqView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLargeAcqDoc)));
	return (CLargeAcqDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CLargeAcqView message handlers



BOOL CLargeAcqView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{	
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}

void CLargeAcqView::OnAcquireGrab() 
{
	if (!m_grabThread)
		m_grabThread = new CTrgThrd(this);
	
}

void CLargeAcqView::OnAcquireSnap() 
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	if (m_grabThread) {
		delete m_grabThread;
		m_grabThread = NULL;
	}
	if (m_hImgConn) {
		m_hImgConn->GetSrc()->SetBufferAddr(m_pImgBuff);
		theapp->m_cam->SeqSnap(m_pImgBuff,1);
		m_hImgConn->Display();		
	}
}

void CLargeAcqView::OnAcquireFreeze() 
{
	if (m_grabThread) {
		delete m_grabThread;
		m_grabThread = NULL;
	}
	if (m_hImgConn) 
		m_hImgConn->Display();		
	
}

void CLargeAcqView::StopGrab(void)
{
	if (m_grabThread) {
		delete m_grabThread;
		m_grabThread = NULL;
	}
}


