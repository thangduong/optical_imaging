//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3Cam1Ring.cpp
//
//  BIRTH DATE:     July 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC V5.8
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Simultaneous acquisition and display of three genlocked
//                  cameras in planar mode in a single ring of acquisition buffers.
//
//                  Planar mode means that the three images are at three
//                  different locations in memory.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"		                // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "ConnSelDlg.h"                     // Connector Selector Dialog Box

#include "IFC_PC2V_3Cam1Ring.h"
#include "IFC_PC2V_3Cam1RingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3Cam1RingApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_3Cam1RingApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_3Cam1RingApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3Cam1RingApp construction

CIFC_PC2V_3Cam1RingApp::CIFC_PC2V_3Cam1RingApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_3Cam1RingApp object

CIFC_PC2V_3Cam1RingApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3Cam1RingApp initialization

BOOL CIFC_PC2V_3Cam1RingApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2V_3Cam1RingDlg dlg;
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
