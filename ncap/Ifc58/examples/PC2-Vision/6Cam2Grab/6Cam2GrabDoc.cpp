// 6Cam2GrabDoc.cpp : implementation of the C6Cam2GrabDoc class
//

#include "stdafx.h"
#include "6Cam2Grab.h"

#include "6Cam2GrabDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabDoc

IMPLEMENT_DYNCREATE(C6Cam2GrabDoc, CDocument)

BEGIN_MESSAGE_MAP(C6Cam2GrabDoc, CDocument)
	//{{AFX_MSG_MAP(C6Cam2GrabDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabDoc construction/destruction

C6Cam2GrabDoc::C6Cam2GrabDoc()
{
	// TODO: add one-time construction code here

}

C6Cam2GrabDoc::~C6Cam2GrabDoc()
{
}

BOOL C6Cam2GrabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabDoc serialization

void C6Cam2GrabDoc::Serialize(CArchive& ar)
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
// C6Cam2GrabDoc diagnostics

#ifdef _DEBUG
void C6Cam2GrabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C6Cam2GrabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabDoc commands
