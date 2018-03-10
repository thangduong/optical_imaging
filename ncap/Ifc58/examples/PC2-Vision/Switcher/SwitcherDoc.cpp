// SwitcherDoc.cpp : implementation of the CSwitcherDoc class
//

#include "stdafx.h"
#include "Switcher.h"

#include "SwitcherDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitcherDoc

IMPLEMENT_DYNCREATE(CSwitcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSwitcherDoc, CDocument)
	//{{AFX_MSG_MAP(CSwitcherDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitcherDoc construction/destruction

CSwitcherDoc::CSwitcherDoc()
{
	// TODO: add one-time construction code here

}

CSwitcherDoc::~CSwitcherDoc()
{
}

BOOL CSwitcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSwitcherDoc serialization

void CSwitcherDoc::Serialize(CArchive& ar)
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
// CSwitcherDoc diagnostics

#ifdef _DEBUG
void CSwitcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSwitcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSwitcherDoc commands
