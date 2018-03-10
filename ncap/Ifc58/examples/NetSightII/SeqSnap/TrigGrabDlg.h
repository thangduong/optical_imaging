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
	void Toggle();

// Dialog Data
	//{{AFX_DATA(CTrigGrabDlg)
	enum { IDD = IDD_GRABTRIG };
	CButton	m_ctlStrobePolLow;
	CButton	m_ctlStrobePolHi;
	CSliderCtrl	m_ctlStrobeDelay;
	CEdit	m_ctlFrameResetSize;
	CButton	m_ctlFramePolHigh;
	CButton	m_ctlFramePolLow;
	CButton	m_ctlFrameDisable;
	CButton	m_ctlFrameEnable;
	CSliderCtrl	m_ctlFrameDelay;
	CButton	m_ctlFastStrobe;
	CButton	m_ctlSlowStrobe;
	CButton	m_ctlStrobeDisable;
	CButton	m_ctlStrobeEnable;
	CButton	m_TrigEnable;
	CButton	m_TrigStart;
	CStatic	m_winStats;
	CEdit	m_ImagesNum;
	int	m_iTrigPolarity;
	int m_iTrigSrc;
	int	m_iStrobeEnable;
	int	m_iStrobeMode;
	int m_iStrobePolarity;
	int m_iStrobeDelay;
	int m_iFrameMode;
	int	m_iFramePolarity;
	int m_iFrameDelay;
	int		m_iImagesNum;
	BOOL	m_bContinuous;
	int		m_iTrigEnable;
	int  m_nVerifyEnd;			// ending line of verification
	int  m_nVerifyThreshold;	// pixel threshold
	DWORD	m_nVerifyStart;
	float	m_frameResetSize;
	//}}AFX_DATA


	
	

	CSeqsnapView* m_vParent;


	int  m_nTriggers;			// number of triggers

	DWORD m_maxTime;		// max time between trig
	DWORD m_minTime;		// min time between trig
	DWORD m_avgTime;		// avg time of trig
	DWORD m_dwLastInterval;		// last time between trig
	DWORD m_dwIntrTime;			// time of last intr

	DWORD m_nNumMissed;
	DWORD m_nNumLost;

	int  m_nVerifyGood;			// verification passed
	int  m_nVerifyBad;			// verification failure

	CString m_strData;     // data from snap
	CString m_strLastData; // data on display



/// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrigGrabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


protected:





protected:

	// Generated message map functions
	//{{AFX_MSG(CTrigGrabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTrgstart();
	afx_msg void OnTrgstop();
	afx_msg void OnTrgtime();
	afx_msg void OnExit();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnContinuous();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnKillMe(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void RefreshStatistics();
	int GetStatistics(LPTSTR pszData);
	void ResetStatistics();

	CTrgThrd* m_trgThread;
	void RefreshDialogFromCamParams();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIGGRABDLG_H__0CC400BC_4F62_11D3_B5D4_00A0C99ACB20__INCLUDED_)
