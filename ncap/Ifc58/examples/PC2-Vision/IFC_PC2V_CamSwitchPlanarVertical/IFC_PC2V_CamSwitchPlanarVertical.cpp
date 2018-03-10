//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CamSwitchPlanarVertical.cpp
//
//  BIRTH DATE:     October 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V5.7)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Two blocks of three genlocked cameras acquiring in planar
//                  vertical mode using a single ring of buffers. 
//                  Each buffer contains three images and it is displayed in a
//                  single window where each camera image is on top of each other.
//                  The two blocks of three cameras are dynamically switched.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"		                // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera type Selector Dialog Box

#include "IFC_PC2V_CamSwitchPlanarVertical.h"
#include "IFC_PC2V_CamSwitchPlanarVerticalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_CamSwitchPlanarVerticalApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_CamSwitchPlanarVerticalApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_CamSwitchPlanarVerticalApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_CamSwitchPlanarVerticalApp construction

CIFC_PC2V_CamSwitchPlanarVerticalApp::CIFC_PC2V_CamSwitchPlanarVerticalApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_CamSwitchPlanarVerticalApp object

CIFC_PC2V_CamSwitchPlanarVerticalApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_CamSwitchPlanarVerticalApp initialization

BOOL CIFC_PC2V_CamSwitchPlanarVerticalApp::InitInstance()
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

	CIFC_PC2V_CamSwitchPlanarVerticalDlg dlg;
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
