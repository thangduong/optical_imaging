/******************************************************************************
 *
 * MODULE
 *    PulseGenDlg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PulseGen/PulseGenDlg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 2/29/00 4:14p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PULSEGENDLG_H__A2670647_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_)
#define AFX_PULSEGENDLG_H__A2670647_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "VixnTime.h"

/////////////////////////////////////////////////////////////////////////////
// CPulseGenDlg dialog

class CPulseGenDlg : public CDialog
{
// Construction
public:
	CPulseGenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPulseGenDlg)
	enum { IDD = IDD_PULSEGEN_DIALOG };
	double	m_Frequency;
	UINT	m_PulseWidth;
	UINT	m_NumPulses;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPulseGenDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	CVixnTimer *m_vixnTime;

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPulseGenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContinuous();
	afx_msg void OnFireOne();
	afx_msg void OnIntrCount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PULSEGENDLG_H__A2670647_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_)
