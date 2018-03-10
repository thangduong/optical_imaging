// 3Cam1GrabView.cpp : implementation of the C3Cam1GrabView class
//

#include "stdafx.h"
#include "3Cam1Grab.h"

#include "3Cam1GrabDoc.h"
#include "3Cam1GrabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabView

IMPLEMENT_DYNCREATE(C3Cam1GrabView, CView)

BEGIN_MESSAGE_MAP(C3Cam1GrabView, CView)
	//{{AFX_MSG_MAP(C3Cam1GrabView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabView construction/destruction

C3Cam1GrabView::C3Cam1GrabView()
{

	C3Cam1GrabApp *theapp=(C3Cam1GrabApp*)AfxGetApp();	
	m_viewID = theapp->m_childCount++;


}

C3Cam1GrabView::~C3Cam1GrabView()
{
	C3Cam1GrabApp *theapp=(C3Cam1GrabApp*)AfxGetApp();	
}


BOOL C3Cam1GrabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabView drawing

void C3Cam1GrabView::OnDraw(CDC* pDC)
{
	C3Cam1GrabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void C3Cam1GrabView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	C3Cam1GrabApp *theapp=(C3Cam1GrabApp*)AfxGetApp();	

	CAM_ATTR *attr=&theapp->m_camAttrib;

	m_imgConn = IfxCreateImgConn(theapp->m_imgBuf,(WORD)attr->dwWidth,(WORD)attr->dwHeight,(WORD)attr->dwBitsPerPixel, m_hWnd);
	theapp->m_imgConn[m_viewID] = m_imgConn;
}



void C3Cam1GrabView::OnDestroy()
{
	C3Cam1GrabApp *theapp=(C3Cam1GrabApp*)AfxGetApp();	

	WaitForSingleObject(theapp->m_connMutex,10000);
	theapp->m_imgConn[m_viewID] = NULL;
	delete m_imgConn;
	::ReleaseMutex(theapp->m_connMutex);


	CView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabView diagnostics

#ifdef _DEBUG
void C3Cam1GrabView::AssertValid() const
{
	CView::AssertValid();
}

void C3Cam1GrabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C3Cam1GrabDoc* C3Cam1GrabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C3Cam1GrabDoc)));
	return (C3Cam1GrabDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabView message handlers


