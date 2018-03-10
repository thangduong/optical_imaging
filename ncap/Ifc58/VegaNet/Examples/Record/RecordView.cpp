// RecordView.cpp : implementation of the CMyRecordView class
//

#include "stdafx.h"
#include "Record.h"

#include "RecordDoc.h"
#include "RecordView.h"
#include "RndRead.h"
#include "MaxSize.h"
#include <mmsystem.h> 

#include <vfw.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define dark_yellow 3
#define YCRCB_COLOR_KEY RGB(0x80,0x80,0)

/////////////////////////////////////////////////////////////////////////////
// CMyRecordView

IMPLEMENT_DYNCREATE(CMyRecordView, CView)

BEGIN_MESSAGE_MAP(CMyRecordView, CView)
	//{{AFX_MSG_MAP(CMyRecordView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_STOP, OnStop)
	ON_WM_TIMER()
	ON_COMMAND(ID_READRANDOM, OnReadRandom)
	ON_COMMAND(ID_CONVERTTOAVI, OnConvertToAvi)
	ON_COMMAND(ID_SETMAXSIZE, OnSetMaxSize)
	ON_COMMAND(ID_QUERYAVICONVERT, OnQueryAviConvert)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyRecordView construction/destruction

CMyRecordView::CMyRecordView()
{
	m_mode = R_IDLE; 
	m_imgAttr.ArrivalTime = 0;
	m_maxFileSize = 0;
	m_stop = 0;
	m_TimerCount = 0;
	m_fileNum = 0;
	m_ImgDisplay = NULL;
	m_rndDialog = NULL;
	m_frameEncode = VS_FRAME_JPEG_ENCODE;
	m_randomNumFrames = 0;
	m_progressInd = NULL;
	m_Sound = TRUE;
	m_isYcrcbDisplay = FALSE;
	m_pause = FALSE;
	m_quality = 75;
}

CMyRecordView::~CMyRecordView()
{
}

BOOL CMyRecordView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyRecordView drawing

void CMyRecordView::OnDraw(CDC* pDC)
{
	CRecordDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyRecordView diagnostics

#ifdef _DEBUG
void CMyRecordView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRecordView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRecordDoc* CMyRecordView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRecordDoc)));
	return (CRecordDoc*)m_pDocument;
}
#endif //_DEBUG

BOOL  IVSAPI UpdateTimeData(BYTE *imgPtr, void *pProcessArg, BYTE *payload, DWORD PayloadSize)
{
	VS_INODE_IMG_ATTR *imgAttr= (VS_INODE_IMG_ATTR*)payload;
	CMyRecordView *view= (CMyRecordView*)pProcessArg;
	if (PayloadSize > 0 && payload)
		view->m_imgAttr = *imgAttr;
	return TRUE;
}

	

/////////////////////////////////////////////////////////////////////////////
// CMyRecordView message handlers

void CMyRecordView::OnInitialUpdate() 
{
	DWORD Flags=0;
	CView::OnInitialUpdate();
	
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	VS_CAM_ATTR camAttrib;
	if (theApp->m_pICap)
		theApp->m_pICap->GetAttr(&camAttrib,TRUE);
	
	Flags |= VS_YCRCB_SINK_FLAG;
	m_ImgDisplay = VsCreateDisplayNode( m_hWnd,Flags,UpdateTimeData,this);
	if (m_ImgDisplay) {
		m_isYcrcbDisplay = TRUE;
	}
	else {
		Flags &= ~VS_YCRCB_SINK_FLAG;
		m_isYcrcbDisplay = FALSE;
		m_ImgDisplay = VsCreateDisplayNode( m_hWnd,Flags,UpdateTimeData,this);
	}

	if (m_isYcrcbDisplay) {
		m_ImgDisplay->SetDestColorKey(PALETTEINDEX(dark_yellow));
		m_backBrush = CreateSolidBrush(YCRCB_COLOR_KEY);
		::SetClassLong(m_hWnd,GCL_HBRBACKGROUND,(long)m_backBrush);
	}

	m_nTimer = SetTimer(1, 1000, 0);

	if (theApp->m_vnmFileName[0]) {
		theApp->m_FileNode->ConnectOutputTo(0,m_ImgDisplay);
		theApp->m_FileNode->StartRandomRead(theApp->m_vnmFileName, &m_randomNumFrames );

		m_rndDialog = new CRndRead(this);
		m_rndDialog->m_activeFileName = theApp->m_vnmFileName;
		BOOL ret = m_rndDialog->Create(IDD_READ_RANDOM,this);
		m_rndDialog->ShowWindow(SW_SHOW);
	}
	else {
		theApp->m_splitNode->ConnectOutputTo(1,m_ImgDisplay);
	}	
}


void CMyRecordView::OnDestroy() 
{
	if (m_rndDialog) {
		m_rndDialog->DestroyWindow();
	}
	if (m_ImgDisplay) {
		m_ImgDisplay->Close();
		m_ImgDisplay->Release();
		m_ImgDisplay = NULL;
	}

	KillTimer(m_nTimer);   
	CView::OnDestroy();	
}


void CMyRecordView::OnFileOpen() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	OnStop();
	CFileDialog dg(TRUE,"AVI",NULL,	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "AVI Files (*.AVI)|*.AVI|"
                "VNM Files (*.VNM)|*.VNM|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
		m_mode = R_PLAYBACK;
   		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		theApp->m_FileNode->ConnectOutputTo(0,m_ImgDisplay);
		theApp->m_FileNode->StartRead(fname.GetBuffer(80) );
	}		
	
}

void CMyRecordView::OnFileSave() 
{
	int result;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();

	VS_CAM_ATTR camAttrib;
	if (theApp->m_pICap)
		theApp->m_pICap->GetAttr(&camAttrib,TRUE);

	FN_SOUND_DESC sound;
	sound.nChannels = 2;
	sound.nSamplesPerSec = 8000;
	sound.wBitsPerSample = 16;

	OnStop();
	CFileDialog dg(FALSE,"AVI",NULL,
    			OFN_HIDEREADONLY,
                "AVI Files (*.AVI)|*.AVI|"
                "VNM Files (*.VNM)|*.VNM|"
                "All Files (*.*)|*.*||");
	result = dg.DoModal();
	if (result == IDOK) {
		theApp->m_splitNode->DisconnectOutput(1);

		m_mode = R_RECORDING;
   		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		m_baseFileName = dg.GetFileTitle();
		m_baseFileExt = dg.GetFileExt();
		m_baseFileExt.MakeUpper();
		if (m_baseFileExt == "AVI") {
			VS_AVICOMPRESSOPTIONS	opts;
			memset(&opts, 0, sizeof(VS_AVICOMPRESSOPTIONS));	
			opts.dwFlags = AVICOMPRESSF_VALID |AVICOMPRESSF_KEYFRAMES | AVICOMPRESSF_DATARATE;
			opts.fccType = streamtypeVIDEO;
			opts.fccHandler = mmioFOURCC('X', 'V', 'I', 'D'); // DIVX Codec
			opts.dwQuality = 10000;                         //Quality factor 0 to 10000
			opts.dwKeyFrameEvery = 100;             // Maximum period between key frames
			opts.dwBytesPerSecond = 150000;           // Data rate to be used by compressor
			if (theApp->m_FileNode->StartWriteAVI(fname.GetBuffer(80), &opts, m_Sound?&sound:NULL, NULL, 0) != S_OK)
				MessageBox("Cannot open file for write","Movie Write Error");
		}
		else {
			if (theApp->m_FileNode->StartWriteEx(fname.GetBuffer(80), m_frameEncode, m_Sound?&sound:NULL, NULL) != S_OK)
				MessageBox("Cannot open file for write","Movie Write Error");
		}
		theApp->m_splitNode->ConnectOutputTo(1,m_ImgDisplay);
	}		
}


void CMyRecordView::OnStop() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();

	switch (m_mode) {
	case R_RECORDING:
		theApp->m_FileNode->StopWrite();		
	break;

	case R_PLAYBACK:
		theApp->m_FileNode->StopRead();		
	break;
	
	}
	m_mode = R_IDLE; 
	if (theApp->m_splitNode) {
		theApp->m_pICap->ConnectOutputTo(0,theApp->m_splitNode);
		theApp->m_splitNode->ConnectOutputTo(1,m_ImgDisplay);
	}

}


void CMyRecordView::OnTimer(UINT nIDEvent) 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	if (m_mode == R_PLAYBACK && theApp->m_FileNode->ReadIsComplete() == S_OK) {
		theApp->m_FileNode->StopRead();		
		m_mode = R_IDLE; 
		MessageBox("The file read is complete","Read Complete");
	}	
	m_TimerCount++;
	if (m_mode == R_RECORDING  && m_maxFileSize) {
		DWORD numFramesSaved;
		DWORD numFramesAcquired;
		theApp->m_FileNode->GetSaveStats(&numFramesSaved,&numFramesAcquired);
		if (numFramesSaved > m_maxFileSize) {
			theApp->m_FileNode->StopWrite();		
			if (m_stop) {
				m_mode = R_IDLE; 
				theApp->m_splitNode->ConnectOutputTo(1,m_ImgDisplay);
			}
			else {
				char tstr[40];
				FN_SOUND_DESC sound;
				sound.nChannels = 2;
				sound.nSamplesPerSec = 8000;
				sound.wBitsPerSample = 16;

				theApp->m_splitNode->DisconnectOutput(1);

   				CString fname= m_baseFileName + itoa(m_fileNum,tstr,10) + "." + m_baseFileExt;   // dgf.GetPathName();
				m_fileNum++;
				theApp->m_FileNode->StartWriteEx(fname.GetBuffer(80), m_frameEncode, m_Sound?&sound:NULL, NULL);

				theApp->m_splitNode->ConnectOutputTo(1,m_ImgDisplay);

			}
		}
	}
	CView::OnTimer(nIDEvent);
}


void CMyRecordView::OnReadRandom() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	OnStop();
	theApp->m_FileNode->StopRead();
	CFileDialog dg(TRUE,"AVI",NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "AVI Files (*.AVI)|*.AVI|"
                "VNM Files (*.VNM)|*.VNM|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
//		m_mode = R_PLAYBACK;
   		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		theApp->m_FileNode->ConnectOutputTo(0,m_ImgDisplay);
		theApp->m_FileNode->StartRandomRead(fname.GetBuffer(80),&m_randomNumFrames );
		CRndRead dgRnd(this);
		dgRnd.m_activeFileName = fname;
		dgRnd.DoModal();
		OnStop();
	}		
	
}


BOOL  IVSAPI ConvProgressUpdate( DWORD numFramesConverted, DWORD totalNumFrames, void*param)
{
	CMyRecordView *view=(CMyRecordView *)param;
	return view->ProgressUpdate(numFramesConverted,totalNumFrames);
}


BOOL CMyRecordView::ProgressUpdate( DWORD numFramesConverted, DWORD totalNumFrames)
{
	if (!m_progressInd) {
		m_progressInd = new CConvProg(this);
		BOOL ret = m_progressInd->Create(IDD_DG_CONV_PROGRESS,this);
		m_progressInd->ShowWindow(SW_SHOW);
	}
		
	m_progressInd->m_convText.Format("%d of %d Frames Converted",numFramesConverted,totalNumFrames);
	m_progressInd->UpdateData(FALSE);
	
	MSG* pMsg = &AfxGetThread()->m_msgCur;
	
	do {
		if (!AfxGetThread()->PumpMessage())
			break;
		m_progressInd->ShowWindow(SW_SHOWNORMAL);
		m_progressInd->UpdateWindow();
		
		if (AfxGetThread()->IsIdleMessage(pMsg))
			break;
		
	} while (::PeekMessage(pMsg, NULL, NULL, NULL, PM_NOREMOVE));
	
	return !m_progressInd->m_cancelRequested;
}



void CMyRecordView::OnConvertToAvi() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	VS_CAM_ATTR camAttrib;
	if (theApp->m_pICap)
		theApp->m_pICap->GetAttr(&camAttrib,TRUE);
	OnStop();
	CFileDialog dg(TRUE,"VNM",NULL,	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "VNM Files (*.VNM)|*.VNM|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
		CString vnmFname = dg.GetFileTitle() + "." + dg.GetFileExt(); 
		CFileDialog dgAvi(FALSE,"AVI",NULL,	
			OFN_HIDEREADONLY,
			"AVI Files (*.AVI)|*.AVI|"
			"All Files (*.*)|*.*||");
		if (dgAvi.DoModal() == IDOK) {
			CString aviFname= dgAvi.GetFileTitle() + "." + dgAvi.GetFileExt();
			HCURSOR  hCursor; 
			hCursor = SetCursor(LoadCursor(NULL,IDC_APPSTARTING));          //Put the glass-hour indicator
			ShowCursor(TRUE);
			
			AVICOMPRESSOPTIONS	opts;
			memset(&opts, 0, sizeof(AVICOMPRESSOPTIONS));	
			opts.dwFlags = AVICOMPRESSF_VALID |AVICOMPRESSF_KEYFRAMES | AVICOMPRESSF_DATARATE;
			opts.fccType = streamtypeVIDEO;
			if (camAttrib.color == VS_RGB)
				opts.fccHandler = mmioFOURCC('X', 'V', 'I', 'D'); // DIVX Codec; 
			else
				opts.fccHandler = mmioFOURCC('c', 'v', 'i', 'd'); // Cinepak Codec
			opts.dwQuality = 10000;                         //Quality factor 0 to 10000
			opts.dwKeyFrameEvery = 15;             // Maximum period between key frames
			opts.dwBytesPerSecond = 150;           // Data rate to be used by compressor
			
			VnConvertVnmToAviEx(vnmFname.GetBuffer(80),aviFname.GetBuffer(80),&opts,
				ConvProgressUpdate,this );
			
			ShowCursor(FALSE);                    // Restore cursor
			SetCursor(hCursor);                     
			
			if (m_progressInd) {
				m_progressInd->DestroyWindow();
				m_progressInd = NULL;
			}
			
		}
	}
}



void CMyRecordView::OnSetMaxSize() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	int result;
	MaxSize dg(this);
	result = dg.DoModal();
	if (result == IDOK) {
		m_maxFileSize = dg.m_maxFileSize;
		m_stop = !dg.m_stop;	
		m_frameEncode = (VS_FRAME_ENCODE)dg.m_compMethod;
		m_Sound = dg.m_Sound;
		m_quality = dg.m_quality;
		theApp->m_FileNode->SetWriteQuality(m_quality);
	}
}

void CMyRecordView::OnQueryAviConvert() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	OnStop();
	CFileDialog dg(TRUE,"VNM",NULL,	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "VNM Files (*.VNM)|*.VNM|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
		CString vnmFname= dg.GetFileTitle() + "." + dg.GetFileExt(); 
		CFileDialog dgAvi(FALSE,"AVI",NULL,	
			OFN_HIDEREADONLY,
			"AVI Files (*.AVI)|*.AVI|"
			"All Files (*.*)|*.*||");
		if (dgAvi.DoModal() == IDOK) {
	   		CString aviFname= dgAvi.GetFileTitle() + "." + dgAvi.GetFileExt();

		    HCURSOR  hCursor; 
		    hCursor = SetCursor(LoadCursor(NULL,IDC_APPSTARTING));          //Put the glass-hour indicator
			ShowCursor(TRUE);

			VnConvertVnmToAviQuery(m_hWnd,vnmFname.GetBuffer(80),aviFname.GetBuffer(80),
				 ConvProgressUpdate, this );

		    ShowCursor(FALSE);                    // Restore cursor
			SetCursor(hCursor);                     

			if (m_progressInd) {
				m_progressInd->DestroyWindow();
				m_progressInd = NULL;
			}

		}
	}	
}


void CMyRecordView::OnPause() 
{
	m_pause = !m_pause;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();

	switch (m_mode) {
	case R_RECORDING:
		if (m_pause)
			theApp->m_FileNode->Pause();
		else
			theApp->m_FileNode->Resume();
	break;

	case R_PLAYBACK:
		theApp->m_FileNode->StopRead();		
	break;
	
	}


	
}


void CMyRecordView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	LONG vol=0;
	theApp->m_FileNode->GetVolume(&vol);

	switch (nChar) {
	case VK_UP:
		vol = min(0,vol+200);
		theApp->m_FileNode->SetVolume(vol);
		break;

	case VK_DOWN:
		vol = max( -2000, vol-200);
		theApp->m_FileNode->SetVolume(vol);
		break;

	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
