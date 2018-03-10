//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2V_BasicGrab.h
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

#if !defined(AFX_IFC_PC2V_BASICGRAB_H__1D861942_2ABF_4CF8_AE16_E212E54912F4__INCLUDED_)
#define AFX_IFC_PC2V_BASICGRAB_H__1D861942_2ABF_4CF8_AE16_E212E54912F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_BasicGrabApp:
// See IFC_PC2V_BasicGrab.cpp for the implementation of this class
//

class CIFC_PC2V_BasicGrabApp : public CWinApp
{
public:
	CIFC_PC2V_BasicGrabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_BasicGrabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_BasicGrabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_BASICGRAB_H__1D861942_2ABF_4CF8_AE16_E212E54912F4__INCLUDED_)
