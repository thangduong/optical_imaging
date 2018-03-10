// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Record.h"

#include "MainFrm.h"
#include "RecordView.h"

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
	//}}AFX_MSG_MAP

	ON_UPDATE_COMMAND_UI(ID_INDICATOR_FRAMES_SAVED, OnUpdateFramesSaved)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_FRAMES_ACQ, OnUpdateFramesAcquired)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIMESTAMP, OnUpdateTimeStamp)

END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_FRAMES_SAVED,
	ID_INDICATOR_FRAMES_ACQ,
	ID_INDICATOR_TIMESTAMP
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
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!theApp->m_vnmFileName[0]) {		
		if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
			!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!theApp->m_vnmFileName[0]) {		
		m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndToolBar);
	}
	else {
		CMenu *pMenu=GetMenu();
		pMenu->EnableMenuItem(ID_STOP, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(ID_READRANDOM, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(ID_SETMAXSIZE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

		CMenu* submenu = pMenu->GetSubMenu(0);
		submenu->EnableMenuItem(ID_FILE_OPEN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		submenu->EnableMenuItem(ID_FILE_SAVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		submenu->EnableMenuItem(ID_FILE_SAVE_AS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


void CMainFrame::OnUpdateFramesSaved(CCmdUI *pCmdUI)
{
	DWORD numFramesSaved;
	DWORD numFramesAcquired;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
    pCmdUI->Enable(); 
	theApp->m_FileNode->GetSaveStats(&numFramesSaved,&numFramesAcquired);

    CString strFramesSaved;
    strFramesSaved.Format( "Frames Saved: %d", numFramesSaved ); 
    pCmdUI->SetText( strFramesSaved ); 
}

void CMainFrame::OnUpdateFramesAcquired(CCmdUI *pCmdUI)
{
	DWORD numFramesSaved;
	DWORD numFramesAcquired;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
    pCmdUI->Enable(); 
	theApp->m_FileNode->GetSaveStats(&numFramesSaved,&numFramesAcquired);

    CString strFramesAcq;
    strFramesAcq.Format( "Frames Acquired: %d", numFramesAcquired ); 
    pCmdUI->SetText( strFramesAcq ); 
}

static char *months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

void CMainFrame::OnUpdateTimeStamp(CCmdUI *pCmdUI)
{
	SYSTEMTIME sysTime;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
    pCmdUI->Enable(); 

	CMyRecordView *view=(CMyRecordView*)GetActiveView();
	if (view && view->m_mode == R_PLAYBACK && view->m_imgAttr.ArrivalTime) {
		ULONGLONG time = view->m_imgAttr.ArrivalTime * 10;
		FileTimeToSystemTime((FILETIME*)&time,&sysTime);
	}
	else {
		GetSystemTime(&sysTime);
	}
    CString strTimeStamp;
    strTimeStamp.Format( "%s %02d, %04d %02d:%02d:%02d.%03d GMT",
		months[sysTime.wMonth-1],
		sysTime.wDay,sysTime.wYear,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds); 

    pCmdUI->SetText( strTimeStamp ); 
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


