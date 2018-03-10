// IFC_PC2V_3CamPlanarVertical.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"


#include "IFC_PC2V_3CamPlanarVertical.h"
#include "IFC_PC2V_3CamPlanarVerticalDlg.h"

#include "ConnSelDlg.h"                     // Connector Selector Dialog Box

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3CamPlanarVerticalApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_3CamPlanarVerticalApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_3CamPlanarVerticalApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3CamPlanarVerticalApp construction

CIFC_PC2V_3CamPlanarVerticalApp::CIFC_PC2V_3CamPlanarVerticalApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_3CamPlanarVerticalApp object

CIFC_PC2V_3CamPlanarVerticalApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3CamPlanarVerticalApp initialization

BOOL CIFC_PC2V_3CamPlanarVerticalApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2V_3CamPlanarVerticalDlg dlg;
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
