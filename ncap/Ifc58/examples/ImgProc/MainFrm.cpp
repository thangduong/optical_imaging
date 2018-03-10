// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ImgProc.h"

#include "MainFrm.h"
#include "ImgProcView.h"
#include "CamSel.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_CMDS_SELCAM, OnCmdsSelCam)
	ON_COMMAND(ID_WINDOW_NEW, OnWindowNew)
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
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
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

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnCmdsSelCam()
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	int i;
	WPARAM Update = 0;

	// Signal the View Classes to kill threre threads
	for(i=0; i<MAX_THREADS; i++)
	{
		if(theApp->m_bPoolID[i])
		{
			::SendMessage(theApp->m_hThreads[i], ID_MSG_CAMCHANGE, 0, 0);
		}
	}

	CCamSel dg;

	if(dg.DoModal() == IDOK)
	{
		if(!(theApp->m_cam = theApp->m_pMod->GetCam(0)))
		{
			::MessageBox(NULL,"Port 0 Camera object cannot be obtained.", "No Port 0 Camera", MB_OK);
		}
		else
		{
			Update = 1;
		}
	}

	// Signal the View Classes to create new threads
	for(i=0; i<MAX_THREADS; i++)
	{
		if(theApp->m_bPoolID[i])
		{
			::PostMessage(theApp->m_hThreads[i], ID_MSG_SELCAM, Update, 0);
		}
	}
}

void CMainFrame::OnWindowNew() 
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	if(theApp->m_NumOfActiveViews >= MAX_THREADS)
	{
		MessageBox("The maximum number of Threads is 4\nYou already have 4 active threads", "New Window");
		return;
	}

	CMDIFrameWnd::OnWindowNew();
}
