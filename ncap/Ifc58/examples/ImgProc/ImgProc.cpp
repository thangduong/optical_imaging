// ImgProc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ImgProc.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ImgProcDoc.h"
#include "ImgProcView.h"
#include "CamSel.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgProcApp

BEGIN_MESSAGE_MAP(CImgProcApp, CWinApp)
	//{{AFX_MSG_MAP(CImgProcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProcApp construction

CImgProcApp::CImgProcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}


/////////////////////////////////////////////////////////////////////////////
// CImgProcApp destruction

CImgProcApp::~CImgProcApp()
{


	// TODO: add destruction code here,
	if (m_pMod)
		delete m_pMod;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CImgProcApp object

CImgProcApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {C2055DC3-88B3-11D3-A228-005004051D9B}
static const CLSID clsid =
{ 0xc2055dc3, 0x88b3, 0x11d3, { 0xa2, 0x28, 0x0, 0x50, 0x4, 0x5, 0x1d, 0x9b } };

/////////////////////////////////////////////////////////////////////////////
// CImgProcApp initialization

BOOL CImgProcApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

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
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_IMGPROTYPE,
		RUNTIME_CLASS(CImgProcDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CImgProcView));
	AddDocTemplate(pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Initialize the IFC module
	IFCInit();


	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

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
void CImgProcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


BOOL CImgProcApp::IFCInit()
{
	
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	
#ifndef _DEBUG
	//  The following line will suppress the IFC error log
	IfxSetConsoleHandler(NULL);
#endif

	// The following code is a standard initialization of an ITI
	// board and will appear in all applications using this hardware

	//Setup hardware and get basic information about camera
	char modName[80];
	char fileName[80];

	modName[0]  = '\0';
	fileName[0] = '\0';

	if(m_lpCmdLine && m_lpCmdLine[0])
	{
		strcpy(modName, m_lpCmdLine);
	}
	else
	{
		CITIMods topo;
		ITI_PARENT_MOD *pICap;
		
		// MAX_MODNAME_LEN
		// How to handle sequence numbers ?

		pICap = topo.GetFirst();

		if(pICap)
		{
			strcpy(modName, pICap->name);
		}
	}

	if(modName)
	{
		if(strcmp(modName, "ICP") == 0)
		{
			strcpy(fileName, "PCVtest.txt");
		}
		else
		{
			wsprintf(fileName,"%stest.txt", modName);
		}
	}
	
	if(!(m_pMod=IfxCreateCaptureModule(modName, 0, fileName)))
	{
		if(!(m_pMod=IfxCreateCaptureModule(modName, 0, NULL)))
		{
			::MessageBox(NULL,"No Image Capture Module detected", "No Module", MB_OK);
			return FALSE;
		}

		// If user config file not found, add all camera definitions in camera database directory
		m_pMod->ProcessCameraFilesInDir("camdb",TRUE);
		m_cam = m_pMod->GetCam(0);
		CCamSel dg;
		dg.DoModal();
	}


	if(!(m_cam = m_pMod->GetCam(0)))
	{
		::MessageBox(NULL,"Port 0 Camera object cannot be obtained.", "No Port 0 Camera", MB_OK);
		return FALSE;
	}


	DWORD dwWidth	= (DWORD) m_cam->GetAcqParam(P_WIDTH_PIXELS);
	DWORD dwHeight	= (DWORD) m_cam->GetAcqParam(P_HEIGHT_PIXELS);

	CAM_ATTR attr;
	m_cam->GetAttr(&attr);

	DWORD dwFrameSize  = dwWidth * dwHeight * attr.dwBytesPerPixel;
	DWORD dwImgBufSize = dwFrameSize * FRAMES_IN_HOSTBUFF;
	MEMORYSTATUS memstat;
	GlobalMemoryStatus(&memstat);

	if(MAX_THREADS*(dwImgBufSize + (2*dwFrameSize)) > (memstat.dwTotalPhys-0x800000))
	{
		::MessageBox(NULL, "You don't have enough memory for this configuration", "Memory Error", MB_OK);
		return FALSE;
	}

	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	for(int i=0; i<MAX_THREADS; i++)
	{
		m_bPoolID[i] = FALSE;
	}

	m_anyTrigThread    = 0;
	m_NumOfActiveViews = 0;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CImgProcApp commands

int CImgProcApp::GetID()
{
	int i = 0;

	if(m_NumOfActiveViews < MAX_THREADS)
	{
		while(i<MAX_THREADS && m_bPoolID[i])
		{
			i++;
		}

		m_bPoolID[i] = TRUE;
		m_NumOfActiveViews++;

		return i;
	}

	return -1;
}

void CImgProcApp::ReturnID(int ID)
{
	if(m_bPoolID[ID])
	{
		m_bPoolID[ID] = FALSE;
		m_NumOfActiveViews--;
	}
}
