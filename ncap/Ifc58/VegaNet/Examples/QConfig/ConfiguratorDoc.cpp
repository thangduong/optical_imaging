// ConfiguratorDoc.cpp : implementation of the CConfiguratorDoc class
//

#include "stdafx.h"
#include "Configurator.h"

#include "ConfiguratorDoc.h"
#include "ConfiguratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorDoc

IMPLEMENT_DYNCREATE(CConfiguratorDoc, CDocument)

BEGIN_MESSAGE_MAP(CConfiguratorDoc, CDocument)
	//{{AFX_MSG_MAP(CConfiguratorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorDoc construction/destruction

CConfiguratorDoc::CConfiguratorDoc()
{
}

CConfiguratorDoc::~CConfiguratorDoc()
{
}

BOOL CConfiguratorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	POSITION pos = GetFirstViewPosition();
	CConfiguratorView* pFirstView = (CConfiguratorView*)GetNextView( pos );

	if (!pFirstView->m_vidSrc)
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CConfiguratorDoc serialization

void CConfiguratorDoc::Serialize(CArchive& ar)
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
// CConfiguratorDoc diagnostics

#ifdef _DEBUG
void CConfiguratorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CConfiguratorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConfiguratorDoc commands

BOOL CConfiguratorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// Override of MFC's OnOpenDocument()
	//
	// This gets called by MFC when we do an OpenDocumentFile()
	// when the user opens an image capture module. We bypass
	// all of MFC's file system operations overriding here by
	// basically  doing nothing. However the other things MFC
	// does for us such as creating a frame/window for the
	// document still occur elsewhere.
	// Imaging Technology, 3/11/99

	return TRUE;
}

void CConfiguratorDoc::OnCloseDocument() 
{
	// Override of MFC's OnCloseDocument()
	//

	CDocument::OnCloseDocument();
}
