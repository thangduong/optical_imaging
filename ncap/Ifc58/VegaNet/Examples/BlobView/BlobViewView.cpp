// BlobViewView.cpp : implementation of the CBlobViewView class
//

#include "stdafx.h"
#include "BlobView.h"

#include "BlobViewDoc.h"
#include "BlobViewView.h"
#include "ModuleDlg.h"
#include <VnImgCon.h>
#include "BlobDlg.h"
#include "CamSel.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlobViewView

IMPLEMENT_DYNCREATE(CBlobViewView, CView)

BEGIN_MESSAGE_MAP(CBlobViewView, CView)
	//{{AFX_MSG_MAP(CBlobViewView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()


#define CENTROID_WIDTH 3

static const COLORREF  syscolors[] = {
	RGB( 0x0 , 0x0 , 0x0 ),
	RGB( 0x0 , 0x0 , 0xff ),
	RGB( 0x0 , 0xff , 0x0 ),
	RGB( 0x0 , 0xff , 0xff ),
	RGB( 0xff , 0x0 , 0x0 ),
	RGB( 0xff , 0x0 , 0xff ),
	RGB( 0xff , 0xff , 0x0 ),
};


#define MAX_NUM_BLOBS 20000

/////////////////////////////////////////////////////////////////////////////
// CBlobViewView construction/destruction

CBlobViewView::CBlobViewView()
{
	CBlobViewApp *thisApp = (CBlobViewApp *) AfxGetApp();
	CModuleDlg dlg(thisApp->m_vidSrcCfg);

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK) {
		m_pICap = dlg.GetModule();
		strcpy(m_vidSrcNodeName,dlg.m_curNode);

		m_VideoSrcIsLocal = dlg.m_VideoSrcIsLocal;
		CCamSel csdg(this);
		csdg.DoModal();

	}
	else {
		m_pICap = NULL;
	}
	m_ImgDisplay = NULL;
	m_ImgProc = NULL;
	m_hSrvThread=0;
	m_blobObj = NULL;
	m_BlobDlg = NULL;

	m_blobList = (VS_BLOB_DESC_LIST*)malloc(sizeof( VS_BLOB_DESC)*MAX_NUM_BLOBS);
	m_blobList->numBlobs = 0;

}

CBlobViewView::~CBlobViewView()
{
	if (m_pICap) {
		m_pICap->FreezeImgNode();
	}
	if (m_ImgDisplay) {
		VsDeleteDisplayNode(m_ImgDisplay);
		m_ImgDisplay = NULL;
	}
	if (m_pICap) {
		VsDeleteVideoSrc(m_pICap);
		m_pICap = NULL;
	}
	free(m_blobList);
}

BOOL CBlobViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBlobViewView drawing

void CBlobViewView::OnDraw(CDC* pDC)
{
	CBlobViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBlobViewView printing

BOOL CBlobViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBlobViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBlobViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBlobViewView diagnostics

#ifdef _DEBUG
void CBlobViewView::AssertValid() const
{
	CView::AssertValid();
}

void CBlobViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBlobViewDoc* CBlobViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBlobViewDoc)));
	return (CBlobViewDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CBlobViewView message handlers


// UpdateBlobData is passed to VsCreateDisplayNode, this causes it to be invoked
// before each new image is displayed.	The BlobAnlz object supplies the image and payload data
// when it calls CProcThread::Enqueue
BOOL  IVSAPI UpdateBlobData(BYTE *imgPtr, void *pProcessArg, BYTE *payload, DWORD PayloadSize)
{
	VS_BLOB_DESC_LIST *blobList= (VS_BLOB_DESC_LIST*)payload;
	CBlobViewView *view= (CBlobViewView*)pProcessArg;
    VS_HDC hDC;
    CDC* cdc;
	VS_BLOB_DESC *blob;
	DWORD i;
	
	view->m_ImgDisplay->GetOverlayDC(&hDC);
	if(hDC) {
		COLORREF color;
		DWORD blobWidth;
		cdc = CDC::FromHandle(hDC);
		for (i=0,blob=view->m_blobList->blobs ; i < (DWORD)view->m_blobList->numBlobs; i++,blob++) { 
			blobWidth = 1+blob->x1-blob->x0;
			cdc->Draw3dRect(blob->x0,blob->y0,blobWidth,1+blob->y1-blob->y0,syscolors[0],syscolors[0]);
			cdc->Draw3dRect(blob->x_cent-CENTROID_WIDTH,blob->y_cent-CENTROID_WIDTH,2*CENTROID_WIDTH,2*CENTROID_WIDTH,syscolors[0],syscolors[0]);
		}
		
		memcpy(view->m_blobList, payload, PayloadSize);

		
		DWORD totalBlobArea=0;
		for (i=0,blob=view->m_blobList->blobs ; i < (DWORD)view->m_blobList->numBlobs; i++,blob++) { 
			blobWidth = 1+blob->x1-blob->x0;
			totalBlobArea += blob->area;
			color = syscolors[3];
			//						color = syscolors[colorIndex++%6 + 1];
			cdc->Draw3dRect(blob->x_cent-CENTROID_WIDTH,blob->y_cent-CENTROID_WIDTH,2*CENTROID_WIDTH,2*CENTROID_WIDTH,color,color);
			cdc->Draw3dRect(blob->x0,blob->y0,blobWidth,1+blob->y1-blob->y0,color,color);
		}
		if (i > 0)
			view->m_avgBlobArea = totalBlobArea / i;
		view->m_numDetectedBlobs = i;
		cdc->DeleteTempMap();
		view->m_ImgDisplay->ReleaseOverlayDC(hDC);
	}
	
	return TRUE;
}


void CBlobViewView::OnInitialUpdate() 
{
	char docName[100];
	CView::OnInitialUpdate();

	if (!m_pICap)
		return;
	CBlobViewDoc* pDoc = GetDocument();
	VSPROPS vidSrcProps;
	m_pICap->GetProps(&vidSrcProps);
	sprintf(docName, "%s : %s", m_vidSrcNodeName,(char*)vidSrcProps.installedName);

	pDoc->SetTitle(docName);

	m_ImgDisplay = VsCreateDisplayNode( m_hWnd,VS_SW_OVERLAY_FLAG,UpdateBlobData,this);
	m_ImgProc = VsCreateProcessNode(m_pICap);
	m_pICap->ConnectOutputTo(0,m_ImgProc);
	m_ImgProc->ConnectOutputTo(0,m_ImgDisplay);

	// VsCreateServerObjThread causes a BlobAnlz object to be created local to m_ImgProc
	// BlobAnlz offers a special method "STDMETHODIMP CBlobAnlz::ThreadFunction(HCProcThread thrdObj)"
	// this ThreadFunction method is invoked in it's own thread context which was created for it.
	m_ImgProc->RegisterServer("blobob.dll");
	m_hSrvThread = VsCreateServerObjThread(m_ImgProc,__uuidof(BlobAnlz), __uuidof(IBlobAnlz),(void**) &m_blobObj);

	// Start a grab going to supply the process node m_ImgProc, and consequently the thread object inside m_hSrvThread
	m_pICap->GrabToImgNode(	VS_FRAME_JPEG_ENCODE, VS_AUTO_THROTTLE_PRODUCER,VS_INFINITE_FRAMES,0,0,0,0);

	m_BlobDlg = new BlobAnlz(this);
	m_BlobDlg->Create(BlobAnlz::IDD, this);

	VS_CAM_ATTR camAttrib;
	m_pICap->GetAttr(&camAttrib,TRUE);

	CDC *hdc = GetDC();
	if ( (DWORD)hdc->GetDeviceCaps(HORZRES) >= camAttrib.dwWidth
		&& (DWORD)hdc->GetDeviceCaps(VERTRES) >= camAttrib.dwHeight)
		m_ImgDisplay->ResizeWindow();
	ReleaseDC(hdc);

	
}


void CBlobViewView::OnDestroy() 
{
	if (m_BlobDlg) {
		delete m_BlobDlg;
		m_BlobDlg = NULL;
	}

	if (m_ImgProc) {
		if (m_hSrvThread) {
			VsDeleteProcessThread(m_ImgProc,m_hSrvThread,m_blobObj);
			m_hSrvThread=0;
			m_blobObj = NULL;
		}
		VsDeleteProcessNode(m_pICap,m_ImgProc);
		m_ImgProc = NULL;
	}
	if (m_pICap) {
		m_pICap->FreezeImgNode();
	}

	if (m_ImgDisplay) {
		m_ImgDisplay->Close();
		m_ImgDisplay->Release();
		m_ImgDisplay = NULL;
	}

	CView::OnDestroy();	
}
