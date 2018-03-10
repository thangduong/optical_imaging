// 6Cam2GrabView.cpp : implementation of the C6Cam2GrabView class
//

#include "stdafx.h"
#include "6Cam2Grab.h"

#include "6Cam2GrabDoc.h"
#include "6Cam2GrabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabView

IMPLEMENT_DYNCREATE(C6Cam2GrabView, CView)

BEGIN_MESSAGE_MAP(C6Cam2GrabView, CView)
	//{{AFX_MSG_MAP(C6Cam2GrabView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabView construction/destruction

C6Cam2GrabView::C6Cam2GrabView()
{

	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	
	m_viewID = theapp->m_childCount++;


}

C6Cam2GrabView::~C6Cam2GrabView()
{
	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	
}


BOOL C6Cam2GrabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabView drawing

void C6Cam2GrabView::OnDraw(CDC* pDC)
{
	C6Cam2GrabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void C6Cam2GrabView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	

	CAM_ATTR *attr=&theapp->m_camAttrib;

	m_imgConn = IfxCreateImgConn(theapp->m_imgBuf,(WORD)attr->dwWidth,(WORD)attr->dwHeight,(WORD)attr->dwBitsPerPixel, m_hWnd);
	theapp->m_imgConn[m_viewID] = m_imgConn;
}



void C6Cam2GrabView::OnDestroy()
{
	C6Cam2GrabApp *theapp=(C6Cam2GrabApp*)AfxGetApp();	

	WaitForSingleObject(theapp->m_connMutex,10000);
	theapp->m_imgConn[m_viewID] = NULL;
	delete m_imgConn;
	::ReleaseMutex(theapp->m_connMutex);


	CView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabView diagnostics

#ifdef _DEBUG
void C6Cam2GrabView::AssertValid() const
{
	CView::AssertValid();
}

void C6Cam2GrabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C6Cam2GrabDoc* C6Cam2GrabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C6Cam2GrabDoc)));
	return (C6Cam2GrabDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabView message handlers


