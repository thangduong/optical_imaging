// IntrDlg.h : header file
//

#if !defined(AFX_INTREXDLG_H__D59E9155_0072_11D2_A128_00A0246D9D39__INCLUDED_)
#define AFX_INTREXDLG_H__D59E9155_0072_11D2_A128_00A0246D9D39__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define NUM_PIN_INTR 8

/////////////////////////////////////////////////////////////////////////////
// CIntrExDlg dialog

class CIntrExDlg : public CDialog
{
// Construction
public:
	CIntrExDlg(CWnd* pParent = NULL);	// standard constructor

	BYTE *m_pbyImageBuffer;

// Dialog Data
	//{{AFX_DATA(CIntrExDlg)
	enum { IDD = IDD_INTREX_DIALOG };
	CButton	m_ctlSoftTrig;
	CButton	m_ctlTrigSetup;
	CButton	m_GrabAcriveButton;
	long	m_lCounterGotSOT;
	long	m_lCounterGotBMDONE;
	long	m_lCounterGotEOFRM;
	BOOL	m_bGrabActive;
	long	m_lCounterGotVB;
	long	m_lCounterGotOddVB;
	long	m_lCounterGotEvenVB;
	long	m_lCounterGotStartEven;
	long	m_lCounterGotStartField;
	long	m_lCounterGotStartFrame;
	long	m_lCounterGotStartOdd;
	long	m_lCounterGotBMDONE2;
	long	m_lCounterGotBMDONE3;
	long	m_lCounterGotSkipField;
	long	m_lCounterGotLossOfSync;
	long	m_lCounterGotInport;
	long	m_lCounterGotTrigSkip;
	long	m_lCounterGotSWTimer;
	long	m_lCounterGotDecisionLate;
	long	m_lCounterGotDecisionAbsent;
	long	m_lCounterGotAioFifoOverflow;
	//}}AFX_DATA

	long	m_lCounterGotPin[NUM_PIN_INTR];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntrExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIntrExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButton(UINT nID);
	afx_msg void OnSetupTrig();
	afx_msg void OnSoftTrig();
	afx_msg void OnGrabActive();
	afx_msg void OnReset();
	afx_msg void OnButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTREXDLG_H__D59E9155_0072_11D2_A128_00A0246D9D39__INCLUDED_)
