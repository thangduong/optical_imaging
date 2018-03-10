// Configurator.h : main header file for the CONFIGURATOR application
//

#if !defined(AFX_CONFIGURATOR_H__5F5B5B31_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
#define AFX_CONFIGURATOR_H__5F5B5B31_C772_11D2_B530_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <VnVidSrc.h> 
#include "ModuleDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CConfiguratorApp:
// See Configurator.cpp for the implementation of this class
//


class CConfiguratorApp : public CWinApp
{
public:
	CConfiguratorApp();
	~CConfiguratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfiguratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CConfiguratorApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	char m_ModNames[CFG_MAX_NUM_MODS][40];
	BOOL m_LibrarianModeEnabled;
	IVidSrcCfg *m_vidSrcCfg;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATOR_H__5F5B5B31_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
