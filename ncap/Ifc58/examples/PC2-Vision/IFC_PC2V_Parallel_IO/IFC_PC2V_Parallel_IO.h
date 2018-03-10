// IFC_PC2V_Parallel_IO.h : main header file for the IFC_PC2V_PARALLEL_IO application
//

#if !defined(AFX_IFC_PC2V_PARALLEL_IO_H__1DCB14F1_E155_4CAD_820F_00B810521DDF__INCLUDED_)
#define AFX_IFC_PC2V_PARALLEL_IO_H__1DCB14F1_E155_4CAD_820F_00B810521DDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_Parallel_IOApp:
// See IFC_PC2V_Parallel_IO.cpp for the implementation of this class
//

class CIFC_PC2V_Parallel_IOApp : public CWinApp
{
public:
	CIFC_PC2V_Parallel_IOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_Parallel_IOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_Parallel_IOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_PARALLEL_IO_H__1DCB14F1_E155_4CAD_820F_00B810521DDF__INCLUDED_)
