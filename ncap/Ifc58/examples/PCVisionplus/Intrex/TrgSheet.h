/******************************************************************************
 *
 * MODULE
 *    TrgSheet.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/IntrEx/TrgSheet.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/30/99 9:10a $
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

#if !defined(AFX_TRGSHEET_H__237127C8_334A_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRGSHEET_H__237127C8_334A_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TrgSheet.h : header file
//

class CTrgSheet;

#include "trgGrab.h"
#include "trigpro.h"


/////////////////////////////////////////////////////////////////////////////
// CTrgSheet

class CTrgSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTrgSheet)

// Construction
public:
	CTrgSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTrgSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrgSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrgSheet();

	CTrgGrab *m_trigProp;
	CTrigPro *m_trigAttr[2];

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrgSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRGSHEET_H__237127C8_334A_11D1_AE32_00A0C959E757__INCLUDED_)
