#if !defined(AFX_MAXSIZE_H__96B8F375_9019_11D6_B252_00105A0F576C__INCLUDED_)
#define AFX_MAXSIZE_H__96B8F375_9019_11D6_B252_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaxSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MaxSize dialog

class MaxSize : public CDialog
{
// Construction
public:
	MaxSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MaxSize)
	enum { IDD = IDD_MAX_SIZE };
	CSliderCtrl	m_ctlQuality;
	DWORD	m_maxFileSize;
	int		m_stop;
	int		m_compMethod;
	BOOL	m_Sound;
	int		m_quality;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MaxSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MaxSize)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAXSIZE_H__96B8F375_9019_11D6_B252_00105A0F576C__INCLUDED_)
