#if !defined(AFX_RULEEDIT_H__446A88B3_3D60_11D5_B1AD_00105A0F576C__INCLUDED_)
#define AFX_RULEEDIT_H__446A88B3_3D60_11D5_B1AD_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleEdit.h : header file
//
#include "ConfiguratorView.h"

class CConfigureDlg;
/////////////////////////////////////////////////////////////////////////////
// CRuleEdit dialog

class CRuleEdit : public CDialog
{
// Construction
public:
	void AddRuleStr(PIFC_UART_RULE rule);
	CRuleEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleEdit)
	enum { IDD = IDD_RULE_EDITOR };
	CEdit	m_byt0Ctl;
	CComboBox	m_paramValList;
	CComboBox	m_paramIdList;
	CListBox	m_ruleList;
	CListBox	m_conditionList;
	CString	m_conditionParamVal;
	CString	m_currentCondition;
	CString	m_currentRule;
	BYTE	m_cmdByte0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CConfigureDlg *m_parent;
	CICamera *m_pCamera;
	PCICapMod m_pICap;
	int m_numParams;
	IFC_UART_RULE m_rule;

	IFC_PARAM_CAPS m_curParmCaps;
	ACQ_PARAMS_TYPE m_curParamID;

	// Generated message map functions
	//{{AFX_MSG(CRuleEdit)
	afx_msg void OnAddCondition();
	afx_msg void OnAddRule();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCondParamid();
	afx_msg void OnClearConditions();
	afx_msg void OnDeleteCondition();
	afx_msg void OnDelRule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULEEDIT_H__446A88B3_3D60_11D5_B1AD_00105A0F576C__INCLUDED_)
