// Grab3Doc.cpp : implementation of the CGrab3Doc class
//

#include "stdafx.h"
#include "Grab3.h"

#include "Grab3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrab3Doc

IMPLEMENT_DYNCREATE(CGrab3Doc, CDocument)

BEGIN_MESSAGE_MAP(CGrab3Doc, CDocument)
	//{{AFX_MSG_MAP(CGrab3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrab3Doc construction/destruction

CGrab3Doc::CGrab3Doc()
{
	// TODO: add one-time construction code here

}

CGrab3Doc::~CGrab3Doc()
{
}

BOOL CGrab3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGrab3Doc serialization

void CGrab3Doc::Serialize(CArchive& ar)
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
// CGrab3Doc diagnostics

#ifdef _DEBUG
void CGrab3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrab3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGrab3Doc commands
