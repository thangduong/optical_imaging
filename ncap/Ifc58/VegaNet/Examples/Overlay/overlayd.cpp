/********************************************************************
 *
 * MODULE
 *    overlayd.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/overlayd.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/30/99 7:14p $
 *
 * ABSTRACT
 *    IFC Overlay example program
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/

// overlayd.cpp : implementation of the COverlayDoc class
//

#include "stdafx.h"
#include "overlay.h"

#include "overlayd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COverlayDoc

IMPLEMENT_DYNCREATE(COverlayDoc, CDocument)

BEGIN_MESSAGE_MAP(COverlayDoc, CDocument)
	//{{AFX_MSG_MAP(COverlayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COverlayDoc construction/destruction

COverlayDoc::COverlayDoc()
{

}

COverlayDoc::~COverlayDoc()
{
	if(!m_ImgElemList.IsEmpty())
	{
	    POSITION pos;
		COlayElem *pImgElement;
		pos = m_ImgElemList.GetHeadPosition();
		pImgElement = (COlayElem*)m_ImgElemList.GetAt(pos); 
		delete pImgElement;
		// Iterate through the list 
		while(m_ImgElemList.GetNext(pos) && pos!=NULL){
			pImgElement = (COlayElem*)m_ImgElemList.GetAt(pos);
			delete pImgElement;
		}
		m_ImgElemList.RemoveAll();
	}
}

BOOL COverlayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COverlayDoc serialization

void COverlayDoc::Serialize(CArchive& ar)
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
// COverlayDoc diagnostics

#ifdef _DEBUG
void COverlayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COverlayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COverlayDoc commands

BOOL COverlayDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!CDocument::OnOpenDocument(lpszPathName))
//		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}
