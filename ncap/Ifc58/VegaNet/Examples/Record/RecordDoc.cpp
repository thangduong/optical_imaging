// RecordDoc.cpp : implementation of the CRecordDoc class
//

#include "stdafx.h"
#include "Record.h"

#include "RecordDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordDoc

IMPLEMENT_DYNCREATE(CRecordDoc, CDocument)

BEGIN_MESSAGE_MAP(CRecordDoc, CDocument)
	//{{AFX_MSG_MAP(CRecordDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordDoc construction/destruction

CRecordDoc::CRecordDoc()
{
	// TODO: add one-time construction code here

}

CRecordDoc::~CRecordDoc()
{
}

BOOL CRecordDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRecordDoc serialization

void CRecordDoc::Serialize(CArchive& ar)
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
// CRecordDoc diagnostics

#ifdef _DEBUG
void CRecordDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRecordDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRecordDoc commands

BOOL CRecordDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	
	
	return TRUE;
}
