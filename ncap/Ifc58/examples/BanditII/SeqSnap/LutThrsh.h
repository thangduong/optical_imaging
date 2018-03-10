/******************************************************************************
 *
 * MODULE
 *    LutThrsh.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/LutThrsh.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/02/01 2:54p $
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

#if !defined(AFX_LUTTHRSH_H__1BAE34E2_3FDC_11D1_AE3E_00A0C959E757__INCLUDED_)
#define AFX_LUTTHRSH_H__1BAE34E2_3FDC_11D1_AE3E_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LutThrsh.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLutThrsh dialog

class CLutThrsh : public CDialog
{
// Construction
public:
	CLutThrsh(CWnd* pParent = NULL,DWORD pixMaxVal=255);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLutThrsh)
	enum { IDD = IDD_LUTFLOOR };
	UINT	m_lutThresh;
	//}}AFX_DATA

	DWORD m_pixMaxVal;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLutThrsh)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLutThrsh)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUTTHRSH_H__1BAE34E2_3FDC_11D1_AE3E_00A0C959E757__INCLUDED_)
