/******************************************************************************
 *
 * MODULE
 *    seqsnapd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/seqsnapd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/16/03 2:21p $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/



#include "stdafx.h"
#include "seqsnap.h"

#include "seqsnapD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapDoc

IMPLEMENT_DYNCREATE(CSeqsnapDoc, CDocument)

BEGIN_MESSAGE_MAP(CSeqsnapDoc, CDocument)
	//{{AFX_MSG_MAP(CSeqsnapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapDoc construction/destruction

CSeqsnapDoc::CSeqsnapDoc()
{
	// TODO: add one-time construction code here

}

CSeqsnapDoc::~CSeqsnapDoc()
{
}

BOOL CSeqsnapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSeqsnapDoc serialization

void CSeqsnapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapDoc diagnostics

#ifdef _DEBUG
void CSeqsnapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSeqsnapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapDoc commands

BOOL CSeqsnapDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
