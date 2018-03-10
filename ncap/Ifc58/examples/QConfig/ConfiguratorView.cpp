// ConfiguratorView.cpp : implementation of the CConfiguratorView class
//

#include "stdafx.h"
#include "Configurator.h"

#include "ConfiguratorDoc.h"
#include "ConfiguratorView.h"

#include "ConfigureDlg.h"
#include "ModuleDlg.h"
#include "xform.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef enum {transparent, dark_red, dark_green, dark_yellow, dark_blue, dark_magenta, dark_cyan, light_gray1,
			  money_green, sky_blue, cream, light_gray2, medium_gray, red, green, yellow, blue, magenta, cyan, white} STATIC_COLOR;


/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView

IMPLEMENT_DYNCREATE(CConfiguratorView, CScrollView)

BEGIN_MESSAGE_MAP(CConfiguratorView, CScrollView)
	//{{AFX_MSG_MAP(CConfiguratorView)
	ON_COMMAND(ID_EDIT_CONFIG, OnEditConfig)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDIT_TRANSFORM, OnEditTransform)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView construction/destruction

CConfiguratorView::CConfiguratorView()
{
	// Get Capture Module from Application 
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	CModuleDlg dlg;

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK) {
		m_pICap = dlg.GetModule();
		int i;
		if (!m_pICap->IsVirtualModule()) {
			for (i=0; i < CFG_MAX_NUM_MODS;i++) {
				if (thisApp->m_ModSeqNum[i] == -1) {
					thisApp->m_ModSeqNum[i] = m_pICap->m_seqNum;
					strcpy(thisApp->m_ModNames[i],m_pICap->m_modName);
					break;
				}
			}
		}
	}
	else {
		m_pICap = NULL;
	}
	m_pImgConn=NULL;
	m_currentSelectedGroup = IFC_PGRP_GENERAL_ACQ; 
}

CConfiguratorView::~CConfiguratorView()
{
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	if (m_pImgConn) {
		delete m_pImgConn;
		m_pImgConn = NULL;
	}
	// Close the image capture module associated with this document.
	if (m_pICap) {
		int i;
		for (i=0; i < CFG_MAX_NUM_MODS;i++) {
			if (!strcmp(m_pICap->m_modName,thisApp->m_ModNames[i]) && thisApp->m_ModSeqNum[i] == (int)m_pICap->m_seqNum) {
				thisApp->m_ModSeqNum[i] = -1;
				break;
			}
		}
		delete m_pICap;
		m_pICap = NULL;
	}

}

BOOL CConfiguratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView drawing

void CConfiguratorView::OnDraw(CDC* pDC)
{
	CConfiguratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBrush cbr;
	RECT rect;
	CDC *hdc;

	CPoint sp = GetScrollPosition();

	if (m_pImgConn) 
		m_pImgConn->GetSrc()->SetAoiPos( (WORD)sp.x, (WORD)sp.y);


	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	(hdc = GetDC())->FillRect(&rect,&cbr);
	cbr.DeleteObject();
	ReleaseDC(hdc);
}

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView printing

BOOL CConfiguratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CConfiguratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CConfiguratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView diagnostics

#ifdef _DEBUG
void CConfiguratorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CConfiguratorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CConfiguratorDoc* CConfiguratorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConfiguratorDoc)));
	return (CConfiguratorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorView message handlers

void CConfiguratorView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();

	CBrush cbr;
	RECT rect;
	CDC *hdc;
	CSize sizeTotal;
	DWORD imgConnFlag=0;

	if (!m_pICap) {
		sizeTotal.cx = 640;
		sizeTotal.cy = 480;
		SetScrollSizes(MM_TEXT, sizeTotal);
		return;
	}
	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	(hdc = GetDC())->FillRect(&rect,&cbr);
	cbr.DeleteObject();
	CICamera *pCamera = m_pICap->GetCam(0);



	CAM_ATTR camAttrib;
	pCamera->GetAttr(&camAttrib);
	sizeTotal.cx = (long)camAttrib.dwWidth;
	sizeTotal.cy = (long)camAttrib.dwHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
	if ( pCamera->GetAcqParam(P_PIXEL_COLOR) == IFC_YCRCB )	{ 
		imgConnFlag |= IFC_YCRCB_SINK;
	}

	if (pCamera->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED 
		|| strcmp(m_pICap->ModName(),"P2V")==0 
		|| strcmp(m_pICap->ModName(),"CL2")==0 
		|| strcmp(m_pICap->ModName(),"X64")==0 
		|| strcmp(m_pICap->ModName(),"NSP")==0 
		) 
		m_pImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | imgConnFlag, ICAP_INTR_EOF);
	else
		m_pImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | imgConnFlag, ICAP_INTR_VB);

	if ( (strcmp(m_pICap->ModName(),"CL2")==0 
		|| strcmp(m_pICap->ModName(),"X64")==0 )
		&& camAttrib.dwBitsPerPixel > 8 && camAttrib.dwBitsPerPixel <= 16
		) {
		
		m_pImgConn->GetSrc()->SetOptions(IFC_IMGSRC_OPT_PIX_LEAST_SIG);
	}

	CImgSink *imgSink = m_pImgConn->GetSink();
	if (imgConnFlag & IFC_YCRCB_SINK) {
		imgSink->SetDestColorKey(dark_yellow);
	}
	pCamera->Grab();

	if ( (DWORD)hdc->GetDeviceCaps(HORZRES) >= camAttrib.dwWidth
		&& (DWORD)hdc->GetDeviceCaps(VERTRES) >= camAttrib.dwHeight)
		imgSink->ResizeWindow();
	ReleaseDC(hdc);
}

void CConfiguratorView::OnEditConfig() 
{
	// This gets called when the selects "Configuration"
	// from the Edit menu. This runs the configuration
	// dialog box which is the most important dialog 
	// in this example program.
	// Imaging Technology, 3/11/99
	if (!m_pICap)
		return;
	CConfigureDlg dlg(this, m_pICap);
	dlg.DoModal();

	if (m_pImgConn) {
		CImgSink *imgSink = m_pImgConn->GetSink();
		CAM_ATTR camAttrib;
		CICamera *pCamera = m_pICap->GetCam(0);
		pCamera->GetAttr(&camAttrib);
		CSize sizeTotal;
		sizeTotal.cx = (long)camAttrib.dwWidth;
		sizeTotal.cy = (long)camAttrib.dwHeight;
		SetScrollSizes(MM_TEXT, sizeTotal);
		CDC *hdc = GetDC();
		if ( (DWORD)hdc->GetDeviceCaps(HORZRES) >= camAttrib.dwWidth
			&& (DWORD)hdc->GetDeviceCaps(VERTRES) >= camAttrib.dwHeight)
		imgSink->ResizeWindow();
		ReleaseDC(hdc);
	}
}

void CConfiguratorView::OnDestroy() 
{
	if (m_pImgConn) {
		delete m_pImgConn;
		m_pImgConn = NULL;
	}
	CView::OnDestroy();	
}

void CConfiguratorView::OnEditTransform() 
{
	if (!m_pICap)
		return;
	CICamera *pCamera = m_pICap->GetCam(0);
	CTransform dlg(this, pCamera);
	if (dlg.DoModal()== IDOK) {
		pCamera->Freeze();
		pCamera->SetTransform((IFC_TRANSFORM_TYPE)dlg.m_Transform);
		pCamera->Grab();
	}	
}
