/******************************************************************************
 *
 * MODULE
 *    seqsnapD.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/seqsnap/seqsnapd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/17/01 10:54a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *  seqsnapD.h : implementation of the CSeqsnapDoc class
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_SEQSNAPDOC_H__17D20ADC_3064_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_SEQSNAPDOC_H__17D20ADC_3064_11D1_AE31_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSeqsnapDoc : public CDocument
{
protected: // create from serialization only
	CSeqsnapDoc();
	DECLARE_DYNCREATE(CSeqsnapDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeqsnapDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSeqsnapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSeqsnapDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQSNAPDOC_H__17D20ADC_3064_11D1_AE31_00A0C959E757__INCLUDED_)
