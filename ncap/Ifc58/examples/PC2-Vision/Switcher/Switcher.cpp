/******************************************************************************
 *
 * MODULE
 *    Switcher.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/Switcher.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/27/03 8:42a $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 * Switcher.cpp : implementation of the CSeqsnapView class
 *
 *
 * Copyright (c) 1998-2002 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/
// Switcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Switcher.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SwitcherDoc.h"
#include "SwitcherView.h"
#include "CamSel.H"
#include "CamSwitchM.h"

#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp

BEGIN_MESSAGE_MAP(CSwitcherApp, CWinApp)
	//{{AFX_MSG_MAP(CSwitcherApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp construction

CSwitcherApp::CSwitcherApp()
{
	m_childCount = 0;
	for (DWORD i = 0; i < P2V_MAX_NUM_CAMERAS; i++) {
		m_camIdx[i] = i;
		m_pHostBuffFrame[i] = NULL;
		m_grabID[i] = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp destruction

CSwitcherApp::~CSwitcherApp()
{
	if (m_pMod) {
		m_pMod->SwitchCameraFreeze();
	}

	for (DWORD i = 0; i < P2V_MAX_NUM_CAMERAS; i++) {
		if (m_pHostBuffFrame[i])
			GlobalFreePtr(m_pHostBuffFrame[i]);
		
	}

	// TODO: add destruction code here,
	if (m_pMod)
		delete m_pMod;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CSwitcherApp object

CSwitcherApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp initialization

BOOL CSwitcherApp::InitInstance()
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
		IDR_SWITCHERTYPE,
		RUNTIME_CLASS(CSwitcherDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSwitcherView));
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
	if (!IFCInit())
		return FALSE;


	StartSwitchingGrab();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	for (DWORD i = 1; i < m_nbCamera; i++) {
		pDocTemplate->OpenDocumentFile(NULL);
	}

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
void CSwitcherApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL CSwitcherApp::IFCInit()
{
	
	HCURSOR hcurSave;

	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	
#ifndef _DEBUG
	//  The following line will suppress the IFC error log
	IfxSetConsoleHandler(NULL);
#endif
	
	m_currentAcqChannel = 0;
	if (!(m_pMod=(CPCVision2*)IfxCreateCaptureModule("P2V",0,"p2vtest.txt"))) {
		if (!(m_pMod=(CPCVision2*)IfxCreateCaptureModule("P2V",0,NULL))) {
			::MessageBox(NULL,"No Image Capture Module detected",
				"No Module",MB_OK);
			return FALSE;
		}
		m_cam = m_pMod->GetCam(0);
		// If user config file not found, add all camera definitions in camera database directory
		m_pMod->ProcessCameraFilesInDir("camdb",TRUE);
		CCamSel dg;
		dg.DoModal();
	}


	if (!(m_cam = m_pMod->GetCam(m_currentAcqChannel))) {
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.",
			"No Port 0 Camera",MB_OK);
		return FALSE;
	}


	m_cam->GetAttr(&m_camAttrib);
	
	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	return TRUE;
}


void CSwitcherApp::StartSwitchingGrab()
{
	CCamSwitchM camSwitchDlg(P2V_MAX_NUM_CAMERAS);
	if(camSwitchDlg.DoModal() == IDOK) {
		
		m_nbCamera = min( P2V_MAX_NUM_CAMERAS, camSwitchDlg.GetNbCamera());
		m_singleRing = camSwitchDlg.m_singleRing;

		
		m_pMod->SwitchCameraDefineStart();

		for (DWORD i = 0; i < m_nbCamera; i++) {
			CICamera *cam;
			m_camIdx[i] = camSwitchDlg.GetCameraIndex(i) - 1;
			cam = m_pMod->GetCam(m_camIdx[i]);

			CAM_ATTR attr;
			cam->GetAttr(&attr);

			if (m_singleRing) {
				if (i==0) {
					m_pHostBuffFrame[i] = (BYTE*)GlobalAllocPtr(GMEM_FIXED,attr.dwWidth * attr.dwHeight * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF * m_nbCamera);
				}
				m_grabID[i] = cam->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,m_pHostBuffFrame[0], FRAMES_IN_HOSTBUFF * m_nbCamera);
			}
			else {
				m_pHostBuffFrame[i] = (BYTE*)GlobalAllocPtr(GMEM_FIXED,attr.dwWidth * attr.dwHeight * attr.dwBytesPerPixel * FRAMES_IN_HOSTBUFF);
				m_grabID[i] = cam->Grab(IFC_GOPT_AUTO_FRAME_LOCK,m_pHostBuffFrame[i], FRAMES_IN_HOSTBUFF);
			}

		}
		m_currentAcqChannel = m_camIdx[0];

		m_pMod->SwitchCameraDefineEnd();
		m_pMod->SwitchCameraGrab();
		
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp commands



