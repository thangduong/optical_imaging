// smsync.h : main header file for the SMSYNC application
//

#if !defined(AFX_SMSYNC_H__87F6FAAB_CDAB_40E6_83DB_9A3CC183BAC1__INCLUDED_)
#define AFX_SMSYNC_H__87F6FAAB_CDAB_40E6_83DB_9A3CC183BAC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "CSmsyncDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSmsyncApp:
// See smsync.cpp for the implementation of this class
//

class CSmsyncApp : public CWinApp
{
public:
	CSmsyncApp();

	CSmsyncDlg* mydlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmsyncApp)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmsyncApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMSYNC_H__87F6FAAB_CDAB_40E6_83DB_9A3CC183BAC1__INCLUDED_)
