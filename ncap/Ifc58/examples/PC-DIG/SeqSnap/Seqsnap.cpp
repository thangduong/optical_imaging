/******************************************************************************
 *
 * MODULE
 *    seqsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/SEQSNAP/SEQSNAP.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 6/29/00 3:29p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 * seqsnap.cpp : Defines the class behaviors for the application.
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "seqsnap.h"

#include "MainFrm.h"
#include "seqsnapD.h"
#include "seqsnapV.h"
#include <ifc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapApp

BEGIN_MESSAGE_MAP(CSeqsnapApp, CWinApp)
	//{{AFX_MSG_MAP(CSeqsnapApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

void CSeqsnapApp::InitIFC(void)
{
	// This example accepts command line argument that is a number of the board to 
	// use (in case the multiple boards are present in the system)
	m_iActiveBoard=0;
	if (m_lpCmdLine && m_lpCmdLine[0])
		sscanf(m_lpCmdLine, "%d ", &m_iActiveBoard);


	if (!(m_iCap=IfxCreateCaptureModule("PCD",m_iActiveBoard,"pcdtest.txt"))) {
		if (!(m_iCap=IfxCreateCaptureModule("PCD",m_iActiveBoard))) {
			::MessageBox(NULL,"Specified Image Capture Module not detected.",
				"No Module",MB_OK);
			exit(0);
		}
		// If user config file not found, add all camera definitions in camera database directory
		m_iCap->ProcessCameraFilesInDir("camdb",TRUE);
	}

	// Enable Just-In_Time frame memory locking, allows acquiring to a frame ring buffer when the 
	// entire buffer is too large to be locked at once
	m_iCap->EnableJitGrabMemLock();

	m_cam = m_iCap->GetCam(0);


	CAM_ATTR attr;
	// Get the camera's basic attributes

	m_cam->GetAttr(&attr);
		
	m_srcBitspp = attr.dwBitsPerPixel;
}


/////////////////////////////////////////////////////////////////////////////
// CSeqsnapApp construction

CSeqsnapApp::CSeqsnapApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

CSeqsnapApp::~CSeqsnapApp()
{
	if (m_iCap)
		delete m_iCap;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSeqsnapApp object

CSeqsnapApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapApp initialization

BOOL CSeqsnapApp::InitInstance()
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
		RUNTIME_CLASS(CSeqsnapDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSeqsnapView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	InitIFC();

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
void CSeqsnapApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapApp commands
