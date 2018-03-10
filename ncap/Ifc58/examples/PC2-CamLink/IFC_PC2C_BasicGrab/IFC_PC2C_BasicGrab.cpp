// IFC_PC2C_BasicGrab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related

#include "IFC_PC2C_BasicGrab.h"
#include "IFC_PC2C_BasicGrabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2C_BasicGrabApp

BEGIN_MESSAGE_MAP(CIFC_PC2C_BasicGrabApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2C_BasicGrabApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2C_BasicGrabApp construction

CIFC_PC2C_BasicGrabApp::CIFC_PC2C_BasicGrabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2C_BasicGrabApp object

CIFC_PC2C_BasicGrabApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2C_BasicGrabApp initialization

BOOL CIFC_PC2C_BasicGrabApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2C_BasicGrabDlg dlg;
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
