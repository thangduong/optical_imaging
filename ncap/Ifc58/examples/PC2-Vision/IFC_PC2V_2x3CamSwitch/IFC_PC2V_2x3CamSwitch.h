//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_2x3CamSwitch.h
//
//  BIRTH DATE:     May 2003
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

#if !defined(AFX_IFC_PC2V_2X3CAMSWITCH_H__94743B4D_6EA0_45D8_A155_0A0ADB6901AA__INCLUDED_)
#define AFX_IFC_PC2V_2X3CAMSWITCH_H__94743B4D_6EA0_45D8_A155_0A0ADB6901AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_2x3CamSwitchApp:
// See IFC_PC2V_2x3CamSwitch.cpp for the implementation of this class
//

class CIFC_PC2V_2x3CamSwitchApp : public CWinApp
{
public:
	CIFC_PC2V_2x3CamSwitchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_2x3CamSwitchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_2x3CamSwitchApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_2X3CAMSWITCH_H__94743B4D_6EA0_45D8_A155_0A0ADB6901AA__INCLUDED_)
