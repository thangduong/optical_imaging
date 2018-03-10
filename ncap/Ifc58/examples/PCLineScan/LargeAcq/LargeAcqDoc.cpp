// LargeAcqDoc.cpp : implementation of the CLargeAcqDoc class
//

#include "stdafx.h"
#include "LargeAcq.h"

#include "LargeAcqDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLargeAcqDoc

IMPLEMENT_DYNCREATE(CLargeAcqDoc, CDocument)

BEGIN_MESSAGE_MAP(CLargeAcqDoc, CDocument)
	//{{AFX_MSG_MAP(CLargeAcqDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLargeAcqDoc construction/destruction

CLargeAcqDoc::CLargeAcqDoc()
{
	// TODO: add one-time construction code here

}

CLargeAcqDoc::~CLargeAcqDoc()
{
}

BOOL CLargeAcqDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLargeAcqDoc serialization

void CLargeAcqDoc::Serialize(CArchive& ar)
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
// CLargeAcqDoc diagnostics

#ifdef _DEBUG
void CLargeAcqDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLargeAcqDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLargeAcqDoc commands
