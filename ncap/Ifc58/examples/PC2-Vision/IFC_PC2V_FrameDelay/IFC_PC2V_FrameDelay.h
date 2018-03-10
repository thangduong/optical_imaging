// IFC_PC2V_FrameDelay.h : main header file for the IFC_PC2V_FRAMEDELAY application
//

#if !defined(AFX_IFC_PC2V_FRAMEDELAY_H__4E4467FC_376B_445A_8E51_ED3A9F57212B__INCLUDED_)
#define AFX_IFC_PC2V_FRAMEDELAY_H__4E4467FC_376B_445A_8E51_ED3A9F57212B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_FrameDelayApp:
// See IFC_PC2V_FrameDelay.cpp for the implementation of this class
//

class CIFC_PC2V_FrameDelayApp : public CWinApp
{
public:
	CIFC_PC2V_FrameDelayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_FrameDelayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_FrameDelayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_FRAMEDELAY_H__4E4467FC_376B_445A_8E51_ED3A9F57212B__INCLUDED_)
