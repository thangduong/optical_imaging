#if !defined(AFX_COLORDLG_H__0F44B7EB_451D_11D3_B5C4_00A0C99ACB20__INCLUDED_)
#define AFX_COLORDLG_H__0F44B7EB_451D_11D3_B5C4_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorDlg.h : header file
//

#include "seqsnapv.h"

#define NUM_COLOR_OPTIONS 7

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog

class CColorDlg : public CDialog
{
// Construction
public:
	CColorDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColorDlg)
	enum { IDD = IDD_COLOR };
	CButton	m_radioButtonRed;
	int		m_iRadioButtonColorMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioRed();
	afx_msg void OnRadioGreen();
	afx_msg void OnRadioBlue();
	afx_msg void OnRADIOaRGBPLANAR();
	afx_msg void OnRadioRgb();
	afx_msg void OnRadioRgb24();
	afx_msg void OnRadioRgbPlanar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void NewImageServer();

	CSeqsnapView*	m_parent;
	CICamera*		m_pCam;
	static DWORD	m_dwColorButtonIds[NUM_COLOR_OPTIONS];
	static DWORD	m_dwBitmapIds[NUM_COLOR_OPTIONS];
	CBitmap			m_Bitmaps[NUM_COLOR_OPTIONS];
	static DWORD	m_dwColorButtonVals[IFC_NUM_COLOR_MODES];
	IFC_COLOR		m_color;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORDLG_H__0F44B7EB_451D_11D3_B5C4_00A0C99ACB20__INCLUDED_)
