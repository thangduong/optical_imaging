/******************************************************************************
 *
 * MODULE
 *    camsel.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/seqsnap/CamSel.h $
 *    $Revision: 1.1 $
 *    $Modtime: 11/06/03 4:13p $
 *
 * ABSTRACT
 *    NetSight II Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_CAMSEL_H__709E2C13_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_CAMSEL_H__709E2C13_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CamSel.h : header file
//

class CCamSel;

#include "seqsnapV.h"

/////////////////////////////////////////////////////////////////////////////
// CCamSel dialog

class CCamSel : public CDialog
{
// Construction
public:
	~CCamSel();
	CCamSel(CWnd* pParent = NULL);   // standard constructor

	CSeqsnapView * m_parent;

// Dialog Data
	//{{AFX_DATA(CCamSel)
	enum { IDD = IDD_CAMSEL };
	CButton	m_ctlPort0;
	CButton	m_ctlPort1;
	CButton	m_ctlPort2;
	CButton	m_ctlPort3;
	CButton	m_ctlPort4;
	CButton	m_ctlPort5;
	int		m_PortNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamSel)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCamSel)
	afx_msg void OnSelchangeListCamname();
	virtual BOOL OnInitDialog();
	afx_msg void OnPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSEL_H__709E2C13_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
