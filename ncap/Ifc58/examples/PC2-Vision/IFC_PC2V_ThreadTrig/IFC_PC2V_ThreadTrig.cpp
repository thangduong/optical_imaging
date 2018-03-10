//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ThreadTrig.cpp
//
//  BIRTH DATE:     January 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.6.1)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Acquisition and display with external camera triggering.
//                  Note that your camera must be in external trigger mode.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"

#include "CamSelDlg.h"                      // Cam Selector Dialog Box
#include "CamSigParamDlg.h"                 // Cam Signals parameter Dialog Box
#include "StrobeParamDlg.h"                 // Strobe Signal parameter Dialog Box


#include "IFC_PC2V_ThreadTrig.h"
#include "IFC_PC2V_ThreadTrigDlg.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadTrigApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_ThreadTrigApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_ThreadTrigApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadTrigApp construction

CIFC_PC2V_ThreadTrigApp::CIFC_PC2V_ThreadTrigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_ThreadTrigApp object

CIFC_PC2V_ThreadTrigApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadTrigApp initialization

BOOL CIFC_PC2V_ThreadTrigApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	CIFC_PC2V_ThreadTrigDlg dlg;
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
