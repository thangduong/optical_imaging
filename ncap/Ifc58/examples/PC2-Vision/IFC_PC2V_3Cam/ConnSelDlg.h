//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           ConnSelDlg.h
//
//  BIRTH DATE:     February 2003
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
//  DESCRIPTION:
//                  Dialog Box to select connector and camera type.
//------------------------------------------------------------------------------



#if !defined(AFX_CONNSELDLG_H__004739F5_2346_423B_9722_0173134D61E3__INCLUDED_)
#define AFX_CONNSELDLG_H__004739F5_2346_423B_9722_0173134D61E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CConnSelDlg : public CDialog
{

public:

	CConnSelDlg(CWnd* pParent, CICamera *pCam);

	~CConnSelDlg(void);

	char *m_pszCurCamera;
    DWORD m_dwCurConn;

// Dialog Data
	//{{AFX_DATA(CConnSelDlg)
	enum { IDD = IDD_CONNSEL };
	CButton	m_ButtonConn0;
	CButton	m_ButtonConn1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnSelDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CConnSelDlg)
	afx_msg void OnConnector0();
	afx_msg void OnConnector1();
	afx_msg void OnSelchangeListCamname();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICamera    *m_pCam;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNSELDLG_H__004739F5_2346_423B_9722_0173134D61E3__INCLUDED_)
