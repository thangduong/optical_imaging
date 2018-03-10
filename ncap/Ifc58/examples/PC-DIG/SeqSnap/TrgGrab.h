#if !defined(AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_)
#define AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrgGrab.h : header file
//

class CTrgGrab;

#include <ifc.h>
#include <pcdig.h>
#include "trgsheet.h"
#include "trgthrd.h"

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab dialog

class CTrgGrab : public CPropertyPage 
{
	DECLARE_DYNCREATE(CTrgGrab)
// Construction
public:
	CTrgGrab(CTrgSheet *parent);   // standard constructor
	CTrgGrab();   // standard constructor
	~CTrgGrab();   // standard constructor

	DWORD m_maxTime;
	DWORD m_minTime;
	DWORD m_avgTime;
	PCD_TRIG_MODE_TYPE m_startEvent , m_stopEvent;

// Dialog Data
	//{{AFX_DATA(CTrgGrab)
	enum { IDD = IDD_GRABTRIG };
	int		m_TrigStartEvent;
	int		m_TrigEndEvent;
	BOOL	m_continuousSWTrig;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrgGrab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	CTrgThrd *m_trgThread;
	CTrgSheet *m_parent;

protected:

	// Generated message map functions
	//{{AFX_MSG(CTrgGrab)
	afx_msg void OnTrgstart();
	afx_msg void OnTrgstop();
	afx_msg void OnTrgtime();
	virtual BOOL OnInitDialog();
	afx_msg void OnSwTrig();
	afx_msg void OnContSwTrig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRGGRAB_H__CB263FC6_DC71_11D2_B032_00105A0F576C__INCLUDED_)
