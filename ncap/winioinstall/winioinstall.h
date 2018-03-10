// winioinstall.h : main header file for the WINIOINSTALL application
//

#if !defined(AFX_WINIOINSTALL_H__9223A21C_D708_4DF1_A286_4319D32DD475__INCLUDED_)
#define AFX_WINIOINSTALL_H__9223A21C_D708_4DF1_A286_4319D32DD475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinioinstallApp:
// See winioinstall.cpp for the implementation of this class
//

class CWinioinstallApp : public CWinApp
{
public:
	CWinioinstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinioinstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinioinstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINIOINSTALL_H__9223A21C_D708_4DF1_A286_4319D32DD475__INCLUDED_)
