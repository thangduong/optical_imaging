/******************************************************************************
 *
 * MODULE
 *    PulseGen.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/PulseGen/PulseGen.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/12/03 3:06p $
 *
 * ABSTRACT
 *    PC-CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "PulseGen.h"
#include "PulseGenDlg.h"
#include "CamSel.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPulseGenApp

BEGIN_MESSAGE_MAP(CPulseGenApp, CWinApp)
	//{{AFX_MSG_MAP(CPulseGenApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulseGenApp construction

CPulseGenApp::CPulseGenApp()
{
	// Place all significant initialization in InitInstance
	m_pMod = NULL;
}

CPulseGenApp::~CPulseGenApp()
{
	if (m_pMod)
		delete m_pMod;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPulseGenApp object

CPulseGenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPulseGenApp initialization

BOOL CPulseGenApp::InitInstance()
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

	DWORD iActiveBoard=0;
	if (m_lpCmdLine && m_lpCmdLine[0])
		sscanf(m_lpCmdLine, "%d ", &iActiveBoard);

	if (!(m_pMod=(CICapMod*)IfxCreateParentModule("LNK",iActiveBoard,"lnktest.txt"))) {
		if ((m_pMod=(CICapMod*)IfxCreateParentModule("LNK",iActiveBoard,NULL))) {
			m_cam = m_pMod->GetCam(0);
			CCamSel dg(NULL);
			dg.DoModal();

		}
		else {
			::MessageBox(NULL,"No Image Capture Module detected",
				"No Module",MB_OK);
			return FALSE;
		}
	}
	if (!(m_cam = m_pMod->GetCam(0))) {
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.",
			"No Port 0 Camera",MB_OK);
		return FALSE;
	}

	// Get the camera's basic attributes

	m_cam->GetAttr(&m_camAttrib);

	// Do a dummy output to enable the parallel out port
	m_pMod->OutportVal(0);

	CPulseGenDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
