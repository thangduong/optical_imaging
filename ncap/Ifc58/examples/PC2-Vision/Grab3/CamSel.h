/******************************************************************************
 *
 * MODULE
 *    camsel.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/grab3/CamSel.h $
 *    $Revision: 1.1 $
 *    $Modtime: 11/04/02 3:59p $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2002 Coreco Imaging , Inc.  All rights reserved.
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

#include "Grab3.h"


/////////////////////////////////////////////////////////////////////////////
// CCamSel dialog

class CCamSel : public CDialog
{
// Construction
public:
	~CCamSel();
	CCamSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCamSel)
	enum { IDD = IDD_CAMSEL };
	int		m_camConn;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSEL_H__709E2C13_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
