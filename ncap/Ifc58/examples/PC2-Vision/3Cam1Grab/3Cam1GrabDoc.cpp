// 3Cam1GrabDoc.cpp : implementation of the C3Cam1GrabDoc class
//

#include "stdafx.h"
#include "3Cam1Grab.h"

#include "3Cam1GrabDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabDoc

IMPLEMENT_DYNCREATE(C3Cam1GrabDoc, CDocument)

BEGIN_MESSAGE_MAP(C3Cam1GrabDoc, CDocument)
	//{{AFX_MSG_MAP(C3Cam1GrabDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabDoc construction/destruction

C3Cam1GrabDoc::C3Cam1GrabDoc()
{
	// TODO: add one-time construction code here

}

C3Cam1GrabDoc::~C3Cam1GrabDoc()
{
}

BOOL C3Cam1GrabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabDoc serialization

void C3Cam1GrabDoc::Serialize(CArchive& ar)
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
// C3Cam1GrabDoc diagnostics

#ifdef _DEBUG
void C3Cam1GrabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C3Cam1GrabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabDoc commands
