#if !defined(AFX_FLATFLD_H__47EF8416_04A9_11D4_B1A6_00105A0F576C__INCLUDED_)
#define AFX_FLATFLD_H__47EF8416_04A9_11D4_B1A6_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlatFld.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlatField dialog

class CFlatField : public CDialog
{
// Construction
public:
	void PlotGainOffset();
	CFlatField(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFlatField)
	enum { IDD = IDD_FLATFIELD };
	CEdit	m_ctlGainPlot;
	CEdit	m_ctlOffsetPlot;
	BOOL	m_FlatFieldEnable;
	UINT	m_GainMapTo;
	int		m_OffsetMapTo;
	float	m_ExplicitGain;
	UINT	m_ExplicitOffset;
	int		m_MaxXPos;
	int		m_MaxXPos2;
	int		m_maxOffset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlatField)
	afx_msg void OnSetGains();
	afx_msg void OnSetOffsets();
	afx_msg void OnReadFfcFile();
	afx_msg void OnWriteFfcFile();
	afx_msg void OnFlatFieldEnable();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetExplicitOffsets();
	afx_msg void OnSetExplicitGain();
	afx_msg void OnSetOffsetsSpectrum();
	afx_msg void OnSetGainSpectrum();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATFLD_H__47EF8416_04A9_11D4_B1A6_00105A0F576C__INCLUDED_)
