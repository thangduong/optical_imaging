#if !defined(AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_)
#define AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModuleDlg.h : header file
//

#include "direct.h"
#include <ifc.h>

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog

class CModuleDlg : public CDialog
{
// Construction
public:
	PCICapMod GetModule();
	CModuleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModuleDlg)
	enum { IDD = IDD_SELECTMODULE };
	CListBox	m_ctrlVModuleList;
	CListBox	m_ctrlModuleList;
	CButton	m_buttonSelConfigFile;
	CButton	m_buttonOK;
	CString	m_strConfigFileName;
	UINT	m_VmodSeqNum;
	CString	m_SelVModName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModuleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeModuleList();
	virtual void OnOK();
	afx_msg void OnSelectConfigFile();
	afx_msg void OnOpenVmod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	char m_strModName[80];
	DWORD m_modSeqNum;
	PCICapMod m_pICap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_)
