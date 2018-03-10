// Grab3View.cpp : implementation of the CGrab3View class
//

#include "stdafx.h"
#include "Grab3.h"

#include "Grab3Doc.h"
#include "Grab3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrab3View

IMPLEMENT_DYNCREATE(CGrab3View, CView)

BEGIN_MESSAGE_MAP(CGrab3View, CView)
	//{{AFX_MSG_MAP(CGrab3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrab3View construction/destruction

CGrab3View::CGrab3View()
{
	CGrab3App *theapp=(CGrab3App*)AfxGetApp();	
	m_viewID = theapp->m_childCount++;
	m_trgThread = NULL;

	// TODO: add construction code here

}

CGrab3View::~CGrab3View()
{
	CGrab3App *theapp=(CGrab3App*)AfxGetApp();	
	if (m_trgThread) { 
		delete m_trgThread;
	}
}


BOOL CGrab3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGrab3View drawing

void CGrab3View::OnDraw(CDC* pDC)
{
	CGrab3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CGrab3View::OnInitialUpdate()
{
	CView::OnInitialUpdate();



	CGrab3App *theapp=(CGrab3App*)AfxGetApp();	
	if (theapp->m_pMod) {
		m_trgThread = new CTrgThrd(this);
	}
	// TODO: Add your specialized code here and/or call the base class
}



void CGrab3View::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.


	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}


   CView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// CGrab3View diagnostics

#ifdef _DEBUG
void CGrab3View::AssertValid() const
{
	CView::AssertValid();
}

void CGrab3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrab3Doc* CGrab3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrab3Doc)));
	return (CGrab3Doc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CGrab3View message handlers


