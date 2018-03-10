//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_BasicHardOverlay.cpp
//
//  BIRTH DATE:     December 2002
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
//                  Basic acquisition and display in an hardware overlay along
//                  with text drawing in the standard graphic surface.
//
//                  The hardware overlay is physically in the video memory of
//                  your display controller and convert in real-time a pixel
//                  in Y-Cr-Cb color format to the R-G-B format of your monitor.
//                  It also take care in real-time of the scaling (zoom).
//
//                  The benefit of using an hardware overlay is an extremely
//                  fast live display because the Host CPU don't have to do
//                  the pixel conversion and the image scaling.
//
//                  Keep in mind that the live image is in the overlay and the
//                  text drawned is in the standard graphic surface. The overlay
//                  and hence the live image is visible only if you draw the
//                  keying color in the standard graphic surface over the overlay.
//
//                  Your display controller must have an overlay feature for this
//                  demo to work.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "IFC_PC2V_BasicHardOverlay.h"
#include "IFC_PC2V_BasicHardOverlayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_BasicHardOverlayApp

BEGIN_MESSAGE_MAP(CIFC_PC2V_BasicHardOverlayApp, CWinApp)
	//{{AFX_MSG_MAP(CIFC_PC2V_BasicHardOverlayApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_BasicHardOverlayApp construction

CIFC_PC2V_BasicHardOverlayApp::CIFC_PC2V_BasicHardOverlayApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIFC_PC2V_BasicHardOverlayApp object

CIFC_PC2V_BasicHardOverlayApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_BasicHardOverlayApp initialization

BOOL CIFC_PC2V_BasicHardOverlayApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CIFC_PC2V_BasicHardOverlayDlg dlg;
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
