/******************************************************************************
 *
 * MODULE
 *    Grab3.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/grab3/Grab3.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 4/02/03 1:58p $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 * Grab3.cpp : implementation of the CSeqsnapView class
 *
 *
 * Copyright (c) 1998-2002 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/
// Grab3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Grab3.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "Grab3Doc.h"
#include "Grab3View.h"
#include "CamSel.H"
#include <windowsx.h>
#include <PCVision2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrab3App

BEGIN_MESSAGE_MAP(CGrab3App, CWinApp)
	//{{AFX_MSG_MAP(CGrab3App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrab3App construction

CGrab3App::CGrab3App()
{
	m_childCount = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CGrab3App destruction

CGrab3App::~CGrab3App()
{


	// TODO: add destruction code here,
	if (m_pMod)
		delete m_pMod;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CGrab3App object

CGrab3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CGrab3App initialization

BOOL CGrab3App::InitInstance()
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
		IDR_GRAB3TYPE,
		RUNTIME_CLASS(CGrab3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGrab3View));
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
void CGrab3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL CGrab3App::IFCInit()
{
	
	HCURSOR hcurSave;

	m_camBasePort=0;
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
		m_cam = m_pMod->GetCam(m_camBasePort);
		CCamSel dg;
		dg.DoModal();
		if (dg.m_camConn)
			m_camBasePort=3;
		m_cam->GetAttr(&m_camAttrib);
		m_cam = m_pMod->GetCam(m_camBasePort);
		m_cam->SetCameraType(m_camAttrib.camName);
	}


	if (!(m_cam = m_pMod->GetCam(m_camBasePort))) {
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.",
			"No Port 0 Camera",MB_OK);
		return FALSE;
	}

	m_cam->GetAttr(&m_camAttrib);
	char *camName;
	P2V_SYNC_SRC_TYPE syncSrc = (P2V_SYNC_SRC_TYPE)(DWORD)m_cam->GetAcqParam(P2V_SYNC_SOURCE);

	camName = m_camAttrib.camName;

	for (int c=2; c >= 0; c--) {
		m_cam = m_pMod->GetCam(c + m_camBasePort);
		m_cam->SetCameraType(camName);
		m_cam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);		
	}

	m_cam->GetAttr(&m_camAttrib);
	
	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGrab3App commands



