// BlobViewDoc.cpp : implementation of the CBlobViewDoc class
//

#include "stdafx.h"
#include "BlobView.h"

#include "BlobViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlobViewDoc

IMPLEMENT_DYNCREATE(CBlobViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CBlobViewDoc, CDocument)
	//{{AFX_MSG_MAP(CBlobViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlobViewDoc construction/destruction

CBlobViewDoc::CBlobViewDoc()
{
	// TODO: add one-time construction code here

}

CBlobViewDoc::~CBlobViewDoc()
{
}

BOOL CBlobViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBlobViewDoc serialization

void CBlobViewDoc::Serialize(CArchive& ar)
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
// CBlobViewDoc diagnostics

#ifdef _DEBUG
void CBlobViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBlobViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBlobViewDoc commands
