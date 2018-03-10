// Record.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Record.h"

#include "MainFrm.h"
#include "RecordDoc.h"
#include "RecordView.h"
#include "ModuleDlg.h"
#include "CamSel.h"

// To add capability to record into file only image delta, run VegaNet Tutorial to generate ImgDifOb
// and uncomment line below
//#define SUPPORT_IMG_DIFF_SAVE

#ifdef SUPPORT_IMG_DIFF_SAVE
#include "..\ImgDifOb\ImgDifOb.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordApp

BEGIN_MESSAGE_MAP(CRecordApp, CWinApp)
	//{{AFX_MSG_MAP(CRecordApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordApp construction

CRecordApp::CRecordApp()
{
	HRESULT result;
	::CoInitialize(NULL);
	CoInitializeSecurity( 0, -1, 0, 0,
                       RPC_C_AUTHN_LEVEL_NONE,
                       RPC_C_IMP_LEVEL_IDENTIFY,
                       0, 0, 0 );
	m_vidSrcCfg = VsCreateVidSrcCfg(&result);
	m_FileNode=NULL;
	m_hImgSplit = NULL;

#ifdef SUPPORT_IMG_DIFF_SAVE
	m_RecordDeltaOnly = TRUE;
#else
	m_RecordDeltaOnly = FALSE;
#endif
	m_ImgProc = NULL;
	m_pICap = NULL;
	m_vnmFileName[0] = 0;
}


CRecordApp::~CRecordApp()
{

	if (m_ImgProc) {
		if (m_hSrvThread) {
			VsDeleteProcessThread(m_ImgProc,m_hSrvThread,(IDispatch*)m_MyProcessObj);
			m_hSrvThread=0;
			m_MyProcessObj = NULL;
		}
		VsDeleteProcessNode(m_pICap,m_ImgProc);
		m_ImgProc = NULL;
	}

	if (m_pICap) {
		m_pICap->FreezeImgNode();
	}

	if (m_FileNode)
		VsDeleteFileNode(m_FileNode);

	if (m_hImgSplit)
		VsDeleteNodeSplitter(m_hImgSplit);

	if (m_pICap) {
		VsDeleteVideoSrc(m_pICap);
		m_pICap = NULL;
	}

	if (m_vidSrcCfg) {
		m_vidSrcCfg->Release();
		m_vidSrcCfg = NULL;
	}

	::CoUninitialize();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRecordApp object

CRecordApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRecordApp initialization

BOOL CRecordApp::InitInstance()
{
	AfxEnableControlContainer();

	if (!m_vidSrcCfg) {
		MessageBox(NULL,"Error : Could not create VidSrcCfg COM object, check for registration of file VnVidSrc.dll",
			"VidSrcCfg Create Fail",MB_ICONEXCLAMATION | MB_OK );
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRecordDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMyRecordView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	if(m_lpCmdLine && m_lpCmdLine[0]) {
		if (strstr(_strupr(m_lpCmdLine),".VNM")) {
			char *fname=m_lpCmdLine;
			if (fname[0]=='"') 
				fname++;
			int last=strlen(fname)-1;
			if (fname[last]=='"') 
				fname[last]=0;
			strcpy(m_vnmFileName,fname);
		}
		else {
			char fullModName[80]={0,};
			char *space;
			m_vidSrcNodeName[0]=0;
			strcpy(fullModName,m_lpCmdLine);
			if (space=strchr(fullModName,' ')) {
				strcpy(m_vidSrcNodeName,space+1);
				*space=0;
			}
			
			if (m_vidSrcCfg->CreateVideoSrc(m_vidSrcNodeName, fullModName, 0,NULL,&m_pICap) != S_OK) 
				m_pICap = NULL;
			
		}
	}

	if (!m_pICap && !m_vnmFileName[0]) {
		CModuleDlg dlg(m_vidSrcCfg);
		
		int nResponse = dlg.DoModal();
		
		if (nResponse == IDOK) {
			m_pICap = dlg.GetModule();
			strcpy(m_vidSrcNodeName,dlg.m_curNode);
			
			m_VideoSrcIsLocal = dlg.m_VideoSrcIsLocal;
			CCamSel csdg;
			csdg.DoModal();
			
		}
		else {
			m_pICap = NULL;
		}
	}
	if (!m_pICap && !m_vnmFileName[0])
		return FALSE;

	m_FileNode = VsCreateFileNode(m_pICap);
	if (!m_FileNode)
		return FALSE;

	if (m_pICap) {
		m_hImgSplit = VsCreateNodeSplitter(m_pICap,&m_splitNode,VS_FRAME_JPEG_ENCODE);
		m_pICap->ConnectOutputTo(0,m_splitNode);
		
		if (m_RecordDeltaOnly) {
			m_ImgProc = VsCreateProcessNode(m_splitNode);
			m_splitNode->ConnectOutputTo(0,m_ImgProc);
			m_ImgProc->ConnectOutputTo(0,m_FileNode);
			m_ImgProc->RegisterServer("ImgDifOb.dll");
#ifdef SUPPORT_IMG_DIFF_SAVE
			m_hSrvThread = VsCreateServerObjThread(m_ImgProc,__uuidof(ImageDIff), __uuidof(IImageDIff),(void**) &m_MyProcessObj);
#endif
		}
		else {
			m_splitNode->ConnectOutputTo(0,m_FileNode);
		}
		
		// Start a grab going to supply the process node m_ImgProc, and consequently the thread object inside m_hSrvThread
		m_pICap->GrabToImgNode(	VS_FRAME_JPEG_ENCODE, VS_AUTO_THROTTLE_PRODUCER,VS_INFINITE_FRAMES,0,0,0,0);
	}


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CRecordApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CRecordApp message handlers

