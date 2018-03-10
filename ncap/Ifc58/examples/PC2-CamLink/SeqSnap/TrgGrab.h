#if !defined(AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_)
#define AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrgGrab.h : header file
//

class CTrgGrab;

#include <ifc.h>
#include <PC2Link.h>
#include "trgthrd.h"
#include "seqsnapV.h"

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab dialog

class CTrgGrab : public CDialog 
{
// Construction
public:
	CTrgGrab(CWnd* pParent = NULL);   // standard constructor
	~CTrgGrab();   // standard constructor

	DWORD m_maxTime;
	DWORD m_minTime;
	DWORD m_avgTime;

// Dialog Data
	//{{AFX_DATA(CTrgGrab)
	enum { IDD = IDD_GRABTRIG };
	CButton	m_ctlLineTrig;
	CButton	m_ctlFrameTrig;
	int		m_trigEnable;
	int		m_trigPolarity;
	UINT	m_trigDebounce;
	BOOL	m_contiuouseSWTrig;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrgGrab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CTrgThrd *m_trgThread;
	CSeqsnapView * m_parent;

	DWORD m_debounceParamid;
	DWORD m_trigEnableParamid;
	DWORD m_trigPolParamid;

protected:

	// Generated message map functions
	//{{AFX_MSG(CTrgGrab)
	afx_msg void OnTrgstart();
	afx_msg void OnTrgstop();
	afx_msg void OnTrgtime();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSwTrig();
	afx_msg void OnFrameTrig();
	afx_msg void OnLineTrig();
	afx_msg void OnApplyTrig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_)
