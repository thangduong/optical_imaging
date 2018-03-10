#if !defined(AFX_LINETRIG_H__DF62FABF_F699_457D_A522_51365DFF1456__INCLUDED_)
#define AFX_LINETRIG_H__DF62FABF_F699_457D_A522_51365DFF1456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineTrig.h : header file
//
#include <ifc.h>
#include <PC2Link.h>


/////////////////////////////////////////////////////////////////////////////
// CLineTrig dialog

class CLineTrig : public CDialog
{
// Construction
public:
	CLineTrig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLineTrig)
	enum { IDD = IDD_LINE_TRIG };
	UINT	m_trigCycleTime;
	UINT	m_lineTrigDebounce;
	UINT	m_numPhase;
	int		m_lineTrigSrc;
	UINT	m_linesPerTrig;
	int		m_lineTrigEnable;
	int		m_vframeStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineTrig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLineTrig)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETRIG_H__DF62FABF_F699_457D_A522_51365DFF1456__INCLUDED_)
