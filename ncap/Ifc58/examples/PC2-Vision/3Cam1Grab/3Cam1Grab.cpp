// 3Cam1Grab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "3Cam1Grab.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "3Cam1GrabDoc.h"
#include "3Cam1GrabView.h"
#include "CamSel.H"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp

BEGIN_MESSAGE_MAP(C3Cam1GrabApp, CWinApp)
	//{{AFX_MSG_MAP(C3Cam1GrabApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp construction

C3Cam1GrabApp::C3Cam1GrabApp()
{
	m_trgThread = NULL;
	m_pMod = NULL;
	m_imgBuf = NULL;
	m_childCount = 0;
	for (int i=0; i < NUM_CAMERAS;i++) 
		m_imgConn[i] = NULL;

	m_connMutex = CreateMutex(NULL, FALSE, NULL);

}


/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp destruction

C3Cam1GrabApp::~C3Cam1GrabApp()
{

	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}

	if (m_pMod)
		delete m_pMod;

	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);

	CloseHandle(m_connMutex);

}


/////////////////////////////////////////////////////////////////////////////
// The one and only C3Cam1GrabApp object

C3Cam1GrabApp theApp;

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp initialization

BOOL C3Cam1GrabApp::InitInstance()
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

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MY3CAMTYPE,
		RUNTIME_CLASS(C3Cam1GrabDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(C3Cam1GrabView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Initialize the IFC module
	IFCInit();


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	pDocTemplate->OpenDocumentFile(NULL);
	pDocTemplate->OpenDocumentFile(NULL);

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
void C3Cam1GrabApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL C3Cam1GrabApp::IFCInit()
{
	
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	
#ifndef _DEBUG
	//  The following line will suppress the IFC error log
	IfxSetConsoleHandler(NULL);
#endif
	
	if (!(m_pMod=IfxCreateCaptureModule("P2V",0,"p2vtest.txt"))) {
		if (!(m_pMod=IfxCreateCaptureModule("P2V",0,NULL))) {
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
	char *camName = m_camAttrib.camName;

	for (int c=2; c >= 0; c--) {
		m_cam = m_pMod->GetCam(c );
		m_cam->SetCameraType(camName);
		m_cam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);		
	}
		
	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED, m_camAttrib.dwWidth * m_camAttrib.dwHeight * m_camAttrib.dwBytesPerPixel * FRAMES_IN_HOSTBUFF * NUM_CAMERAS);

	m_trgThread = new CTrgThrd();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp commands






