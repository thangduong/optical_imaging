#if !defined(AFX_CSCDLG_H__86660CED_5CC0_11D3_B5DC_00A0C99ACB20__INCLUDED_)
#define AFX_CSCDLG_H__86660CED_5CC0_11D3_B5DC_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CscDlg.h : header file
//

#include "seqsnapv.h"

#define NUM_CSC_OPTIONS 7

/////////////////////////////////////////////////////////////////////////////
// CCscDlg dialog

class CCscDlg : public CDialog
{
// Construction
public:
	CCscDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCscDlg)
	enum { IDD = IDD_COLOR_SPACE_CONV };
	int		m_iRadioButtonCsc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCscDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCscDlg)
	afx_msg void OnRadioRgbToYuv();
	afx_msg void OnRadioRgbToYiq();
	afx_msg void OnRadioRgbToYcrcb444();
	afx_msg void OnRadioRgbToYcrcb422();
	afx_msg void OnRadioRgbToYcbcr422();
	afx_msg void OnRadioRgbToHsi();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void NewImageServer();
	CSeqsnapView*	m_parent;
	CICamera*		m_pCam;
	static DWORD m_dwCscButtonVals[NUM_CSC_OPTIONS];
	DWORD m_dwCscSel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSCDLG_H__86660CED_5CC0_11D3_B5DC_00A0C99ACB20__INCLUDED_)
