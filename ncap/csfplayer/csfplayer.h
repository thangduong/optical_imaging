// csfplayer.h : main header file for the CSFPLAYER application
//

#if !defined(AFX_CSFPLAYER_H__827367E2_27AF_4948_B1E6_4C0D6F41FFD0__INCLUDED_)
#define AFX_CSFPLAYER_H__827367E2_27AF_4948_B1E6_4C0D6F41FFD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCsfplayerApp:
// See csfplayer.cpp for the implementation of this class
//

class CCsfplayerApp : public CWinApp
{
public:
	CCsfplayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCsfplayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCsfplayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSFPLAYER_H__827367E2_27AF_4948_B1E6_4C0D6F41FFD0__INCLUDED_)
