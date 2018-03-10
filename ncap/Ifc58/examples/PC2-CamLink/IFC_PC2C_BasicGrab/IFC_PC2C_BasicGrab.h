// IFC_PC2C_BasicGrab.h : main header file for the IFC_PC2C_BASICGRAB application
//

#if !defined(AFX_IFC_PC2C_BASICGRAB_H__761B1CC1_5AA0_453D_B50D_4AF53B6C2FD6__INCLUDED_)
#define AFX_IFC_PC2C_BASICGRAB_H__761B1CC1_5AA0_453D_B50D_4AF53B6C2FD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2C_BasicGrabApp:
// See IFC_PC2C_BasicGrab.cpp for the implementation of this class
//

class CIFC_PC2C_BasicGrabApp : public CWinApp
{
public:
	CIFC_PC2C_BasicGrabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2C_BasicGrabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2C_BasicGrabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2C_BASICGRAB_H__761B1CC1_5AA0_453D_B50D_4AF53B6C2FD6__INCLUDED_)
