// IFC_PC2V_ManualCamSwitch.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_ManualCamSwitch.h"
#include "IFC_PC2V_ManualCamSwitchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ManualCamSwitchApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_ManualCamSwitchApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_ManualCamSwitchApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ManualCamSwitchApp construction

CIFC_PC2V_ManualCamSwitchApp::CIFC_PC2V_ManualCamSwitchApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_ManualCamSwitchApp object

CIFC_PC2V_ManualCamSwitchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ManualCamSwitchApp initialization

BOOL CIFC_PC2V_ManualCamSwitchApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2V_ManualCamSwitchDlg dlg;
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
