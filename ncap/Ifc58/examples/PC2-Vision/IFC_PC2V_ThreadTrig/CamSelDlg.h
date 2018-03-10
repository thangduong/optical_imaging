//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           CamSelDlg.h
//
//  BIRTH DATE:     December 2002
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------


#if !defined(AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_)
#define AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_



#include "resource.h"                       // main GUI symbols



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamSelDlg dialog

class CCamSelDlg : public CDialog
{

public:

	CCamSelDlg(CWnd* pParent = NULL, CICamera *pCam = NULL);   // standard constructor

	~CCamSelDlg(void);

	char *m_pszCurCamera;
    DWORD m_dwCurPort;

// Dialog Data
	//{{AFX_DATA(CCamSelDlg)
	enum { IDD = IDD_CAMSEL };
	CButton	m_RadioPort0;
	CButton	m_RadioPort1;
	CButton	m_RadioPort2;
	CButton	m_RadioPort3;
	CButton	m_RadioPort4;
	CButton	m_RadioPort5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CCamSelDlg)
	afx_msg void OnSelchangeListCamname();
	afx_msg void OnPort0();
	afx_msg void OnPort1();
	afx_msg void OnPort2();
	afx_msg void OnPort3();
	afx_msg void OnPort4();
	afx_msg void OnPort5();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICamera    *m_pCam;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_)
