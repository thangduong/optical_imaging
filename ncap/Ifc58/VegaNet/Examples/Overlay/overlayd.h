/********************************************************************
 *
 * MODULE
 *    overlayd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/overlayd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/30/99 7:14p $
 *
 * ABSTRACT
 *    IFC Overlay example program file
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/

// overlayd.h : interface of the COverlayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OVERLAYDOC_H__ECEE69FA_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
#define AFX_OVERLAYDOC_H__ECEE69FA_3E85_11D1_A000_00A0246D9D39__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OElem.h"


class COverlayDoc : public CDocument
{
protected: // create from serialization only
	COverlayDoc();
	DECLARE_DYNCREATE(COverlayDoc)

// Attributes
public:
	CObList m_ImgElemList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COverlayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COverlayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COverlayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERLAYDOC_H__ECEE69FA_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
