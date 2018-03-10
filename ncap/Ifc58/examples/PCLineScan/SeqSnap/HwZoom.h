/******************************************************************************
 *
 * MODULE
 *    HwZoom.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/HwZoom.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/22/00 3:06p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_HWZOOM_H__7C9ABA72_513D_11D1_AE53_00A0C959E757__INCLUDED_)
#define AFX_HWZOOM_H__7C9ABA72_513D_11D1_AE53_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HwZoom.h : header file
//
#include <ifc.h>

/////////////////////////////////////////////////////////////////////////////
// CHwZoom dialog

class CHwZoom : public CDialog
{
// Construction
public:
	float m_yzoom;
	float m_xzoom;
	CHwZoom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHwZoom)
	enum { IDD = IDD_HWZOOM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHwZoom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHwZoom)
	afx_msg void OnXz2();
	afx_msg void OnXzNo();
	afx_msg void OnYz2();
	afx_msg void OnYzNo();
	virtual BOOL OnInitDialog();
	afx_msg void OnXz3();
	afx_msg void OnYz3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HWZOOM_H__7C9ABA72_513D_11D1_AE53_00A0C959E757__INCLUDED_)
