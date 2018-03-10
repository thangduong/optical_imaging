// ImgProcDoc.cpp : implementation of the CImgProcDoc class
//

#include "stdafx.h"
#include "ImgProc.h"

#include "ImgProcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc

IMPLEMENT_DYNCREATE(CImgProcDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgProcDoc, CDocument)
	//{{AFX_MSG_MAP(CImgProcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CImgProcDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CImgProcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IImgProc to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C2055DC5-88B3-11D3-A228-005004051D9B}
static const IID IID_IImgProc =
{ 0xc2055dc5, 0x88b3, 0x11d3, { 0xa2, 0x28, 0x0, 0x50, 0x4, 0x5, 0x1d, 0x9b } };

BEGIN_INTERFACE_MAP(CImgProcDoc, CDocument)
	INTERFACE_PART(CImgProcDoc, IID_IImgProc, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc construction/destruction

CImgProcDoc::CImgProcDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CImgProcDoc::~CImgProcDoc()
{
	AfxOleUnlockApp();
}

BOOL CImgProcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc serialization

void CImgProcDoc::Serialize(CArchive& ar)
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
// CImgProcDoc diagnostics

#ifdef _DEBUG
void CImgProcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgProcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgProcDoc commands

BOOL CImgProcDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
