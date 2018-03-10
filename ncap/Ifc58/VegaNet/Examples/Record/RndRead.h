#if !defined(AFX_RNDREAD_H__C6500AD5_05E2_11D6_B220_00105A0F576C__INCLUDED_)
#define AFX_RNDREAD_H__C6500AD5_05E2_11D6_B220_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RndRead.h : header file
//

//#include "RecordView.h"
class CMyRecordView;

/////////////////////////////////////////////////////////////////////////////
// CRndRead dialog

class CRndRead : public CDialog
{
// Construction
public:
	CRndRead(CWnd* pParent = NULL);   // standard constructor

	CString	m_activeFileName;
	DWORD m_startPos;
	BOOL m_inRandomRead;
	DWORD m_nTimer;
	BOOL m_pause;

// Dialog Data
	//{{AFX_DATA(CRndRead)
	enum { IDD = IDD_READ_RANDOM };
	CSliderCtrl	m_ctlSlider;
	UINT	m_rndFrameNum;
	CString	m_timeStampStr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRndRead)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyRecordView *m_vparent;


	// Generated message map functions
	//{{AFX_MSG(CRndRead)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPlay();
	afx_msg void OnFast();
	afx_msg void OnStop();
	afx_msg void OnPause();
	afx_msg void OnRewind();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RNDREAD_H__C6500AD5_05E2_11D6_B220_00105A0F576C__INCLUDED_)
