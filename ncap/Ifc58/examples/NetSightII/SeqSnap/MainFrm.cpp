/******************************************************************************
 *
 * MODULE
 *    MainFrm.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/seqsnap/MainFrm.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 11/06/03 4:13p $
 *
 * ABSTRACT
 *    NetSight II Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2003-2002 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "seqsnap.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_CMDS_TRIGOPS, OnUpdateCmdsTrigOps)
	ON_UPDATE_COMMAND_UI(ID_LUT_INVERT, OnUpdateLutInvert)
	ON_UPDATE_COMMAND_UI(ID_LUT_LINEAR, OnUpdateLutLinear)
	ON_UPDATE_COMMAND_UI(ID_LUT_THRESH, OnUpdateLutThresh)
	ON_UPDATE_COMMAND_UI(ID_CMDS_HWZOOM, OnUpdateCmdsHwzoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CSeqsnapApp* theApp = (CSeqsnapApp*) AfxGetApp();
	m_pcv2=(CPCVision2*)theApp->m_iCap;

	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers




void CMainFrame::OnUpdateCmdsTrigOps(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateLutInvert(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateLutLinear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateLutThresh(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateCmdsHwzoom(CCmdUI* pCmdUI) 
{
	ZOOMCAP zCaps;
	CSeqsnapApp* theApp = (CSeqsnapApp*) AfxGetApp();
	theApp->m_cam->GetZoomCaps(&zCaps);
	pCmdUI->Enable(zCaps.minXZoom != 1.0 || zCaps.minYZoom != 1.0);	
}
