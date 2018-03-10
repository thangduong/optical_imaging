#if !defined(AFX_TRIGGRABDLG_H__0CC400BC_4F62_11D3_B5D4_00A0C99ACB20__INCLUDED_)
#define AFX_TRIGGRABDLG_H__0CC400BC_4F62_11D3_B5D4_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrigGrabDlg.h : header file
//

class CTrigGrabDlg;
#include "TrgThrd.h"
#include "seqsnapV.h"


/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg dialog

class CTrigGrabDlg : public CDialog
{
// Construction
public:
	CTrigGrabDlg(CWnd* pParent = NULL);   // standard constructor
	~CTrigGrabDlg();

// Dialog Data
	//{{AFX_DATA(CTrigGrabDlg)
	enum { IDD = IDD_GRABTRIG };
	int	m_iTrigEnable;
	int	m_iTrigPolarity;
	int	m_iTrigSrc;
	int	m_iStrobeEnable;
	int	m_iStrobeMode;
	int m_iStrobePolarity;
	int m_iStrobeDelay;
	int m_iFrameMode;
	int	m_iFramePolarity;
	int	m_iFrameSize;
	int m_iFrameDelay;
	//}}AFX_DATA

	DWORD m_maxTime;
	DWORD m_minTime;
	DWORD m_avgTime;

	CSeqsnapView* m_vParent;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrigGrabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrigGrabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTrgstart();
	afx_msg void OnTrgstop();
	afx_msg void OnTrgtime();
	afx_msg void OnExit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CTrgThrd* m_trgThread;
	void RefreshDialogFromCamParams();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIGGRABDLG_H__0CC400BC_4F62_11D3_B5D4_00A0C99ACB20__INCLUDED_)