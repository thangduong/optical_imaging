#if !defined(AFX_FRAMETRIG_H__AA011C57_33D8_41EF_BF14_59989314DB4B__INCLUDED_)
#define AFX_FRAMETRIG_H__AA011C57_33D8_41EF_BF14_59989314DB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameTrig.h : header file
//

#include <ifc.h>
#include <PC2Link.h>


/////////////////////////////////////////////////////////////////////////////
// CFrameTrig dialog

class CFrameTrig : public CDialog
{
// Construction
public:
	CFrameTrig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFrameTrig)
	enum { IDD = IDD_FRAME_TRIG };
	float	m_frameTrigFreq;
	int		m_frameTrigSrc;
	UINT	m_framePerTrigger;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameTrig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrameTrig)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMETRIG_H__AA011C57_33D8_41EF_BF14_59989314DB4B__INCLUDED_)
