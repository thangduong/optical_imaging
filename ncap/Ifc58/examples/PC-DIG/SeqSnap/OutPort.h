/******************************************************************************
 *
 * MODULE
 *    OutPort.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/SEQSNAP/OutPort.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/13/99 3:34p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_OUTPORT_H__48C560E2_3FF4_11D1_AE3E_00A0C959E757__INCLUDED_)
#define AFX_OUTPORT_H__48C560E2_3FF4_11D1_AE3E_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutPort.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutPort dialog

class COutPort : public CDialog
{
// Construction
public:
	COutPort(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutPort)
	enum { IDD = IDD_OUTPORT };
	BOOL	m_genstrobe;
	UINT	m_outport_val;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutPort)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutPort)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPORT_H__48C560E2_3FF4_11D1_AE3E_00A0C959E757__INCLUDED_)
