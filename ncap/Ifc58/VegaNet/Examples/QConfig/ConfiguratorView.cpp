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
	CModuleDlg dlg(thisApp->m_vidSrcCfg);

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK) {
		m_vidSrc = dlg.GetModule();
		if (m_vidSrc) {
			strcpy(m_vidSrcNodeName,dlg.m_curNode);
			char *parm = "Thread parm";
//			HSERVERTHREAD hSrvThread;
//			m_vidSrc->CreateServerThread(&hSrvThread, "vsproces","MyServerThreadFunc",(BYTE*)parm,strlen(parm)+1);
//			Sleep(1000);
//			m_vidSrc->DeleteServerThread(hSrvThread);
		}
		
		m_VideoSrcIsLocal = dlg.m_VideoSrcIsLocal;
		int i;
		for (i=0; i < CFG_MAX_NUM_MODS;i++) {
			if (thisApp->m_ModNames[i][0] == 0) {
				strcpy(thisApp->m_ModNames[i],dlg.m_fullModName);
				break;
			}
		}
	}
	else {
		m_vidSrc = NULL;
	}
	m_nodeDisplay=NULL;
	m_vStream = NULL;
	m_currentSelectedGroup = VS_PGRP_GENERAL_ACQ; 
}


CConfiguratorView::~CConfiguratorView()
{
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();

	DeleteDisplay();

	// Close the image capture module associated with this document.
	VSPROPS props;
	if (m_vidSrc) {
		int i;
		m_vidSrc->GetProps(&props);
		for (i=0; i < CFG_MAX_NUM_MODS;i++) {
			if (props.installedName == thisApp->m_ModNames[i]) {
				thisApp->m_ModNames[i][0] = 0;
				break;
			}
		}
		VsDeleteVideoSrc(m_vidSrc);
		m_vidSrc = NULL;
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

	if (m_nodeDisplay) 
		m_nodeDisplay->SetSrcAoiPos( (WORD)sp.x, (WORD)sp.y);


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
	char docName[100];

	CBrush cbr;
	RECT rect;
	CDC *hdc;
	CSize sizeTotal;

	if (!m_vidSrc) {
		sizeTotal.cx = 640;
		sizeTotal.cy = 480;
		SetScrollSizes(MM_TEXT, sizeTotal);
		return;
	}
	CConfiguratorDoc* pDoc = GetDocument();
	VSPROPS vidSrcProps;
	m_vidSrc->GetProps(&vidSrcProps);
	sprintf(docName, "%s : %s", m_vidSrcNodeName,(char*)vidSrcProps.installedName);

	if (pDoc) {
		pDoc->SetTitle(docName);
	}
	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	(hdc = GetDC())->FillRect(&rect,&cbr);
	cbr.DeleteObject();

	VS_CAM_ATTR camAttrib;
	m_vidSrc->GetAttr(&camAttrib,TRUE);
	sizeTotal.cx = (long)camAttrib.dwWidth;
	sizeTotal.cy = (long)camAttrib.dwHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CreateDisplay();

	if ( (DWORD)hdc->GetDeviceCaps(HORZRES) >= camAttrib.dwWidth
		&& (DWORD)hdc->GetDeviceCaps(VERTRES) >= camAttrib.dwHeight)
		m_nodeDisplay->ResizeWindow();
	ReleaseDC(hdc);
}

void CConfiguratorView::OnEditConfig() 
{
	// This gets called when the selects "Configuration"
	// from the Edit menu. This runs the configuration
	// dialog box which is the most important dialog 
	// in this example program.
	if (!m_vidSrc)
		return;
	CConfigureDlg dlg(this, m_vidSrc);
	dlg.DoModal();

	if (m_nodeDisplay) {
		VS_CAM_ATTR camAttrib;
		m_vidSrc->GetAttr(&camAttrib,TRUE);
		CSize sizeTotal;
		sizeTotal.cx = (long)camAttrib.dwWidth;
		sizeTotal.cy = (long)camAttrib.dwHeight;
		SetScrollSizes(MM_TEXT, sizeTotal);
		CDC *hdc = GetDC();
		if ( (DWORD)hdc->GetDeviceCaps(HORZRES) >= camAttrib.dwWidth
			&& (DWORD)hdc->GetDeviceCaps(VERTRES) >= camAttrib.dwHeight)
		m_nodeDisplay->ResizeWindow();
		ReleaseDC(hdc);
	}
}

void CConfiguratorView::OnDestroy() 
{
	DeleteDisplay();

	CView::OnDestroy();	
}

void CConfiguratorView::OnEditTransform() 
{
	if (!m_vidSrc)
		return;
	CTransform dlg(this, m_vidSrc);
	if (dlg.DoModal()== IDOK) {
		m_vidSrc->Freeze(NULL);
		m_vidSrc->SetTransform((VS_TRANSFORM_TYPE)dlg.m_Transform);
		m_vidSrc->GrabOn();
	}	
}

void CConfiguratorView::DeleteDisplay()
{

	if (m_nodeDisplay) {
		VsDeleteDisplayNode(m_nodeDisplay);
		m_nodeDisplay = NULL;
	};
	if (m_vStream) {
		VsDeleteVideoStream(m_vStream);
		m_vStream = NULL;
	};
	if (m_vidSrc) {
		m_vidSrc->Freeze(0);
	}

}

void CConfiguratorView::CreateDisplay()
{
	VS_CAM_ATTR camAttrib;
	m_vidSrc->GetAttr(&camAttrib,TRUE);
	m_vidSrc->Freeze(0);

	if (m_VideoSrcIsLocal) {
		m_nodeDisplay=VsCreateVideoSrcDisplay(m_vidSrc,m_hWnd,VS_LIVE_IMAGE_FLAG,VS_ICAP_INTR_EOF,1);
		m_vidSrc->GrabOn();
	}
	else {
		VS_STREAM_PARAMS encParm;
		encParm.numIframes = 10;
		if (camAttrib.color != VS_MONO) {
			encParm.encodeKind = VS_FRAME_JPEG_ENCODE;
			encParm.desiredFramesPerSecond = 10;
		}
		else {
			encParm.encodeKind = VS_FRAME_DJPEG_ENCODE;
			encParm.desiredFramesPerSecond = 24;
		}
//		encParm.desiredFramesPerSecond = VS_FRAME_RATE_AUTO;
		
		m_vStream = VsCreateVideoStream(m_vidSrc,&encParm);
		m_nodeDisplay = VsCreateDisplayNode( m_hWnd,0,NULL,0);
		m_vStream->ConnectOutputTo(m_nodeDisplay);
	}

}
