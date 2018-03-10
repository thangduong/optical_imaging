// IFC_PC2V_ThreadSaperaProc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "CProSearch.h"                     // Search related classes
#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"

#include "IFC_PC2V_ThreadSaperaProc.h"
#include "IFC_PC2V_ThreadSaperaProcDlg.h"

#include "CamSelDlg.h"                      // Cam Selector Dialog Box


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadSaperaProcApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_ThreadSaperaProcApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_ThreadSaperaProcApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadSaperaProcApp construction

CIFC_PC2V_ThreadSaperaProcApp::CIFC_PC2V_ThreadSaperaProcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_ThreadSaperaProcApp object

CIFC_PC2V_ThreadSaperaProcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadSaperaProcApp initialization

BOOL CIFC_PC2V_ThreadSaperaProcApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2V_ThreadSaperaProcDlg dlg;
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
