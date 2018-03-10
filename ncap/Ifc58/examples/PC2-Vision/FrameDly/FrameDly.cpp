// FrameDly.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FrameDly.h"

#include "MainFrm.h"
#include "FrameDlyDoc.h"
#include "FrameDlyView.h"
#include "CamSel.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp

BEGIN_MESSAGE_MAP(CFrameDlyApp, CWinApp)
	//{{AFX_MSG_MAP(CFrameDlyApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp construction

CFrameDlyApp::CFrameDlyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}


/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp destruction

CFrameDlyApp::~CFrameDlyApp()
{


	// TODO: add destruction code here,
	if (m_pMod)
		delete m_pMod;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CFrameDlyApp object

CFrameDlyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp initialization

BOOL CFrameDlyApp::InitInstance()
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
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFrameDlyDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFrameDlyView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Initialize the IFC module
	IFCInit();


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
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
void CFrameDlyApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL CFrameDlyApp::IFCInit()
{
	
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	
#ifndef _DEBUG
	//  The following line will suppress the IFC error log
	IfxSetConsoleHandler(NULL);
#endif
	
	if (!(m_pMod=(CPCVision2*)IfxCreateCaptureModule("P2V",0,"p2vtest.txt"))) {
		if (!(m_pMod=(CPCVision2*)IfxCreateCaptureModule("P2V",0,NULL))) {
			::MessageBox(NULL,"No Image Capture Module detected",
				"No Module",MB_OK);
			return FALSE;
		}
		// If user config file not found, add all camera definitions in camera database directory
		m_pMod->ProcessCameraFilesInDir("camdb",TRUE);
		m_cam = m_pMod->GetCam(0);
		CCamSel dg;
		dg.DoModal();
	}


	if (!(m_cam = m_pMod->GetCam(0))) {
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.",
			"No Port 0 Camera",MB_OK);
		return FALSE;
	}

	
	m_cam->Grab();

	m_cam->GetAttr(&m_camAttrib);

		
	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	m_anyTrigThread = FALSE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp commands






