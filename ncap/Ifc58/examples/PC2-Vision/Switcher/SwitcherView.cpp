// SwitcherView.cpp : implementation of the CSwitcherView class
//

#include "stdafx.h"
#include "Switcher.h"

#include "SwitcherDoc.h"
#include "SwitcherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSwitcherView

IMPLEMENT_DYNCREATE(CSwitcherView, CView)

BEGIN_MESSAGE_MAP(CSwitcherView, CView)
	//{{AFX_MSG_MAP(CSwitcherView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwitcherView construction/destruction

CSwitcherView::CSwitcherView()
{
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();	
	m_viewID = theapp->m_childCount++;
	m_trgThread = NULL;

	// TODO: add construction code here

}

CSwitcherView::~CSwitcherView()
{
	if (m_trgThread) { 
		delete m_trgThread;
	}
}


BOOL CSwitcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSwitcherView drawing

void CSwitcherView::OnDraw(CDC* pDC)
{
	CSwitcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CSwitcherView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();	
	CSwitcherDoc* pDoc = GetDocument();
	CString docName;
	docName.Format(	"Camera Port %d",theapp->m_camIdx[m_viewID]);
	pDoc->SetTitle(docName);


	if (theapp->m_pMod) {
		m_trgThread = new CTrgThrd(this);
	}
	// TODO: Add your specialized code here and/or call the base class
}



void CSwitcherView::OnDestroy()
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
// CSwitcherView diagnostics

#ifdef _DEBUG
void CSwitcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSwitcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSwitcherDoc* CSwitcherView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSwitcherDoc)));
	return (CSwitcherDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CSwitcherView message handlers


