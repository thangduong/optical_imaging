// focus.h : main header file for the FOCUS application
//

#if !defined(AFX_FOCUS_H__05434E0A_4882_42E5_8BD8_AE145B13363E__INCLUDED_)
#define AFX_FOCUS_H__05434E0A_4882_42E5_8BD8_AE145B13363E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFocusApp:
// See focus.cpp for the implementation of this class
//

class CFocusApp : public CWinApp
{
public:
	CFocusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFocusApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUS_H__05434E0A_4882_42E5_8BD8_AE145B13363E__INCLUDED_)
