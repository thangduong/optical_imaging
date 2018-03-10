// imgviewer.h : main header file for the IMGVIEWER application
//

#if !defined(AFX_IMGVIEWER_H__4F1CFA97_B4E0_45B8_8336_10EC4CE4419D__INCLUDED_)
#define AFX_IMGVIEWER_H__4F1CFA97_B4E0_45B8_8336_10EC4CE4419D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImgviewerApp:
// See imgviewer.cpp for the implementation of this class
//

class CImgviewerApp : public CWinApp
{
public:
	CImgviewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgviewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImgviewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGVIEWER_H__4F1CFA97_B4E0_45B8_8336_10EC4CE4419D__INCLUDED_)
