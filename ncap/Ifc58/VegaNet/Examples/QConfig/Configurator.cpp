// Configurator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Configurator.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ConfiguratorDoc.h"
#include "ConfiguratorView.h"
#include "ModuleDlg.h"
#include <VnBase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorApp

BEGIN_MESSAGE_MAP(CConfiguratorApp, CWinApp)
	//{{AFX_MSG_MAP(CConfiguratorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorApp construction

CConfiguratorApp::CConfiguratorApp()
{
    HRESULT hr;
	int i;
	for (i=0; i < CFG_MAX_NUM_MODS;i++) {
		m_ModNames[i][0] = 0;
	}
	m_LibrarianModeEnabled = FALSE;

//	::CoInitializeEx(NULL,COINIT_MULTITHREADED );
	::CoInitialize(NULL);
	CoInitializeSecurity( 0, -1, 0, 0,
                       RPC_C_AUTHN_LEVEL_NONE,
                       RPC_C_IMP_LEVEL_IDENTIFY,
                       0, 0, 0 );

	hr=CoCreateInstance(__uuidof(VidSrcCfg), NULL, CLSCTX_INPROC_SERVER, __uuidof(IVidSrcCfg), (void**)&m_vidSrcCfg);
	if (hr == REGDB_E_CLASSNOTREG || hr == REGDB_E_IIDNOTREG) {
		VsCtlRegister("VnImgCon.dll");
		VsCtlRegister("VnVidSrc.dll");
		hr=CoCreateInstance(__uuidof(VidSrcCfg), NULL, CLSCTX_INPROC_SERVER, __uuidof(IVidSrcCfg), (void**)&m_vidSrcCfg);
	}
    if (FAILED(hr)) {
		MessageBox(NULL,"Error : Could not create VidSrcCfg COM object, check for registration of file VnVidSrc.dll",
			"VidSrcCfg Create Fail",MB_ICONEXCLAMATION | MB_OK );
		exit(0);
	}
}

CConfiguratorApp::~CConfiguratorApp()
{
	if (m_vidSrcCfg) {
		m_vidSrcCfg->Release();
		m_vidSrcCfg = NULL;
	}

	::CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConfiguratorApp object

CConfiguratorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorApp initialization

BOOL CConfiguratorApp::InitInstance()
{
	AfxEnableControlContainer();

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
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_CONFIGTYPE,
		RUNTIME_CLASS(CConfiguratorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CConfiguratorView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

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
void CConfiguratorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorApp message handlers



