/******************************************************************************
 *
 * MODULE
 *    HwZoom.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/HwZoom.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/25/01 1:13p $
 *
 * ABSTRACT
 *    BanditII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Coreco Imaging, Inc.  All rights reserved.
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
	ZOOMCAP m_ZoomCap;

	CHwZoom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHwZoom)
	enum { IDD = IDD_HWZOOM };
	float	m_xZoom;
	float	m_yZoom;
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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HWZOOM_H__7C9ABA72_513D_11D1_AE53_00A0C959E757__INCLUDED_)
