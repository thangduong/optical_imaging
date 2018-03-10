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
//                  -IFC V5.8
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
#if !defined(AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_)
#define AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_

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

// Dialog Data
	//{{AFX_DATA(CCamSelDlg)
	enum { IDD = IDD_CAMSEL };
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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICamera    *m_pCam;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSELDLG_H__3C35D27C_293C_4C22_9C90_82D2D4B2C757__INCLUDED_)
