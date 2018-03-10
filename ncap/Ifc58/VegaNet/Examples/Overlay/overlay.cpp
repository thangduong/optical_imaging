/********************************************************************
 *
 * MODULE
 *    overlay.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/overlay.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 7/15/02 10:08a $
 *
 * ABSTRACT
 *    IFC Overlay example program
 *    
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/	
// overlay.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "overlay.h"

#include "MainFrm.h"
#include "overlayd.h"
#include "overlayv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <afxmt.h>
//create global mutex used for verification that only one instance exists
CMutex t_GlobalAppMutex(FALSE, "ITIOverlayExampleMutex");

/////////////////////////////////////////////////////////////////////////////
// COverlayApp

BEGIN_MESSAGE_MAP(COverlayApp, CWinApp)
	//{{AFX_MSG_MAP(COverlayApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COverlayApp construction

COverlayApp::COverlayApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	HRESULT result;
	::CoInitialize(NULL);
	CoInitializeSecurity( 0, -1, 0, 0,
                       RPC_C_AUTHN_LEVEL_NONE,
                       RPC_C_IMP_LEVEL_IDENTIFY,
                       0, 0, 0 );
	m_vidSrcCfg = VsCreateVidSrcCfg(&result);
}

COverlayApp::~COverlayApp()
{
	if (m_vidSrcCfg) {
		m_vidSrcCfg->Release();
		m_vidSrcCfg = NULL;
	}

	::CoUninitialize();
}


/////////////////////////////////////////////////////////////////////////////
// The one and only COverlayApp object

COverlayApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COverlayApp initialization

BOOL COverlayApp::InitInstance()
{

//Make sure that only one instance of this app runs on the system
	if(t_GlobalAppMutex.Lock(0) == 0)
		return FALSE;

	if (!m_vidSrcCfg) {
		MessageBox(NULL,"Error : Could not create VidSrcCfg COM object, check for registration of file VnVidSrc.dll",
			"VidSrcCfg Create Fail",MB_ICONEXCLAMATION | MB_OK );
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COverlayDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(COverlayView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	if(((COverlayView*) ((CMainFrame*)m_pMainWnd)->GetActiveView())->m_bErrorConfiguring == TRUE)
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void COverlayApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COverlayApp commands
