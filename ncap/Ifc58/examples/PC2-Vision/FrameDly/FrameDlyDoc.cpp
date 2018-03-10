// FrameDlyDoc.cpp : implementation of the CFrameDlyDoc class
//

#include "stdafx.h"
#include "FrameDly.h"

#include "FrameDlyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyDoc

IMPLEMENT_DYNCREATE(CFrameDlyDoc, CDocument)

BEGIN_MESSAGE_MAP(CFrameDlyDoc, CDocument)
	//{{AFX_MSG_MAP(CFrameDlyDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyDoc construction/destruction

CFrameDlyDoc::CFrameDlyDoc()
{
	// TODO: add one-time construction code here

}

CFrameDlyDoc::~CFrameDlyDoc()
{
}

BOOL CFrameDlyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFrameDlyDoc serialization

void CFrameDlyDoc::Serialize(CArchive& ar)
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
// CFrameDlyDoc diagnostics

#ifdef _DEBUG
void CFrameDlyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFrameDlyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyDoc commands
