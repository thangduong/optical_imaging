// IFC_PC2V_ThreadSaperaProc.h : main header file for the IFC_PC2V_THREADSAPERAPROC application
//

#if !defined(AFX_IFC_PC2V_THREADSAPERAPROC_H__4CF7B2A1_209C_46F2_AF14_89A32A5F283A__INCLUDED_)
#define AFX_IFC_PC2V_THREADSAPERAPROC_H__4CF7B2A1_209C_46F2_AF14_89A32A5F283A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_ThreadSaperaProcApp:
// See IFC_PC2V_ThreadSaperaProc.cpp for the implementation of this class
//

class CIFC_PC2V_ThreadSaperaProcApp : public CWinApp
{
public:
	CIFC_PC2V_ThreadSaperaProcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_ThreadSaperaProcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_ThreadSaperaProcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_THREADSAPERAPROC_H__4CF7B2A1_209C_46F2_AF14_89A32A5F283A__INCLUDED_)
