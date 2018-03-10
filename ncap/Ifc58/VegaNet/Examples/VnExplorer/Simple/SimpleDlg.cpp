// SimpleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Simple.h"
#include "SimpleDlg.h"

typedef HRESULT (STDAPICALLTYPE* CTLREGPROC)() ; // Requires stdole.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CSimpleDlg dialog

CSimpleDlg::CSimpleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleDlg)
	m_CurrentEvent = _T("");
	m_ItemText = _T("");
	m_xValue = _T("");
	m_yValue = _T("");
	m_FlagText = _T("");
	m_OldItemText = _T("");
	m_bDrag = FALSE;
	m_bDragTrace = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_VidSrcCfg = NULL;

	::CoInitialize(NULL);
	CoInitializeSecurity(0, -1, 0, 0, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, 0, 0, 0 );

	HRESULT hr=CoCreateInstance(__uuidof(VidSrcCfg), NULL, CLSCTX_INPROC_SERVER, __uuidof(IVidSrcCfg), (void**)&m_VidSrcCfg);
	
	if(hr == REGDB_E_CLASSNOTREG || hr == REGDB_E_IIDNOTREG)
	{
		VsCtlRegister("VnImgCon.dll");
		VsCtlRegister("VnVidSrc.dll");
		hr=CoCreateInstance(__uuidof(VidSrcCfg), NULL, CLSCTX_INPROC_SERVER, __uuidof(IVidSrcCfg), (void**)&m_VidSrcCfg);
	}
    
	if(FAILED(hr))
	{
		exit(0);
	}

	CVnExplorer VnExplorer;
	if(!IsCtrlRegistered(VnExplorer.GetClsid()))
	{
		if(!RegisterCtrl("VnExplorer.ocx"))
		{
			::MessageBox(NULL, "Failed to properly register VnExplorer Control.", "VegaNet Explorer Simple Example", MB_OK|MB_ICONSTOP);
			exit(0);
		}
	}

	m_hAttachedVideoSource = NULL;
}

BOOL CSimpleDlg::IsCtrlRegistered(CLSID clsid)
{
	IClassFactory* pCF=NULL;

	HRESULT hr = CoGetClassObject(clsid, CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory, (void**) &pCF); 

	if(hr == REGDB_E_CLASSNOTREG || hr == REGDB_E_IIDNOTREG)
	{
		return FALSE;
	}

	if(pCF)
	{
		pCF->Release();
	}

	return TRUE;

}

BOOL CSimpleDlg::RegisterCtrl(LPTSTR strCtrlName)
{
	BOOL bResult = FALSE;
	CTLREGPROC DLLRegisterServer;

	// Path to OLE Control in strCtrlName
	HMODULE hModule = LoadLibrary(strCtrlName);

	if(!hModule)
	{
		return FALSE;
	}
	
	DLLRegisterServer = (CTLREGPROC) GetProcAddress(hModule, "DllRegisterServer");

	if(DLLRegisterServer != NULL)
	{
		HRESULT regResult = DLLRegisterServer();
		bResult = (regResult == NOERROR); 
	}
	
	FreeLibrary(hModule);
	
	return bResult;
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleDlg::~CSimpleDlg - Destructor

CSimpleDlg::~CSimpleDlg()
{
	if(m_VidSrcCfg)
	{
		m_VidSrcCfg->Release();
		m_VidSrcCfg = NULL;
	}

	::CoUninitialize();
}

void CSimpleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleDlg)
	DDX_Control(pDX, IDC_DRAG_TRACE, m_DragTraceButton);
	DDX_Control(pDX, IDC_Y_STATIC, m_yStatic);
	DDX_Control(pDX, IDC_X_STATIC, m_xStatic);
	DDX_Control(pDX, IDC_OLD_ITEM_STATIC, m_OldItemStatic);
	DDX_Control(pDX, IDC_LOCAL_STATIC, m_LocalStatic);
	DDX_Control(pDX, IDC_MOD_NAME_STATIC, m_ModName);
	DDX_Control(pDX, IDC_VNEXPLORERCTRL, m_VnExplorerCtrl);
	DDX_Text(pDX, IDC_EVENT_NAME, m_CurrentEvent);
	DDX_Text(pDX, IDC_ITEM_TEXT, m_ItemText);
	DDX_Text(pDX, IDC_X_VALUE, m_xValue);
	DDX_Text(pDX, IDC_Y_VALUE, m_yValue);
	DDX_Text(pDX, IDC_FLAG_TEXT, m_FlagText);
	DDX_Text(pDX, IDC_OLD_ITEM_TEXT, m_OldItemText);
	DDX_Check(pDX, IDC_DRAG_ENABLE, m_bDrag);
	DDX_Check(pDX, IDC_DRAG_TRACE, m_bDragTrace);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_DRAG_ENABLE, OnDragEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSimpleDlg::InitValues()
{
	m_xValue = "";
	m_yValue = "";
	m_FlagText = "";
	m_ItemText = "";
	m_OldItemText = "";

	m_CurrentEvent = "";

	m_xStatic.ShowWindow(SW_HIDE);
	m_yStatic.ShowWindow(SW_HIDE);
	m_OldItemStatic.ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleDlg message handlers

BOOL CSimpleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	
	if(pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ModName.SetWindowText("");
	m_ModName.EnableWindow(FALSE);

	m_LocalStatic.SetWindowText("");
	m_LocalStatic.EnableWindow(FALSE);

	HCURSOR hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
	
	m_DisplayCtrl.CreateFromStatic(IDC_DISPLAYCTRL, this);

	m_VnExplorerCtrl.Explore((long) m_VidSrcCfg);

	SetCursor(hCursor);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleDlg::OnPaint() 
{
	if(IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSimpleDlg::OnDragEnable() 
{
	UpdateData();

	m_DragTraceButton.EnableWindow(m_bDrag);
}


BEGIN_EVENTSINK_MAP(CSimpleDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSimpleDlg)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 8 /* AttachVideoSource */, OnAttachVideoSource, VTS_I4 VTS_I2)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 9 /* DetachVideoSource */, OnDetachVideoSource, VTS_I4 VTS_I2)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 12 /* ItemExpanded */, OnItemExpanded, VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 14 /* SelectChanged */, OnSelectChanged, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 1 /* LeftClicked */, OnLeftClicked, VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 4 /* RightClicked */, OnRightClicked, VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 17 /* BeginDrag */, OnBeginDrag, VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 10 /* DragMove */, OnDragMove, VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSimpleDlg, IDC_VNEXPLORERCTRL, 11 /* EndDrag */, OnEndDrag, VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CSimpleDlg::OnAttachVideoSource(long hItem, short bIsLocal)
{
	VSPARAM vsParam;
	IVideoSrc* pIVideoSource = NULL;

	vsParam.parmName = VS_CONFIG_FILE_PARM_NAME;
	vsParam.parmVal  = m_VnExplorerCtrl.GetConfigFileName(hItem);

	CString NodeName		= m_VnExplorerCtrl.GetNodeName(hItem);
	CString FullModuleName	= m_VnExplorerCtrl.GetFullModuleName(hItem);

	m_VidSrcCfg->SyncSysTime(NodeName.GetBuffer(0)); NodeName.ReleaseBuffer();

	if(m_VidSrcCfg->CreateVideoSrc(NodeName.GetBuffer(0), FullModuleName.GetBuffer(0), 1, &vsParam, &pIVideoSource) != S_OK)
	{
		::MessageBox(NULL,"Unable to open selected image capture module.", NULL, MB_ICONSTOP|MB_OK);
		m_VnExplorerCtrl.VideoSourceAttached(NULL);

		m_ModName.SetWindowText("");
		m_ModName.EnableWindow(FALSE);

		m_LocalStatic.SetWindowText("");
		m_LocalStatic.EnableWindow(FALSE);
	}
	else
	{
		if(m_hAttachedVideoSource)
		{
			m_VnExplorerCtrl.VideoSourceDetached(m_hAttachedVideoSource);
		}

		m_DisplayCtrl.SetVideoSource(pIVideoSource, (BOOL) bIsLocal);
		m_VnExplorerCtrl.VideoSourceAttached(hItem);

		CString sPath = m_VnExplorerCtrl.GetDomainName(hItem);

		if(!sPath.IsEmpty())
		{
			sPath.Insert(0, "\\\\");
		}

		sPath += "\\";
		sPath += NodeName;
		sPath += "\\";
		sPath += FullModuleName;
		
		m_ModName.SetWindowText((LPCSTR) sPath);
		m_ModName.EnableWindow(TRUE);

		if(bIsLocal)
		{
			m_LocalStatic.SetWindowText("Local Node");
		}
		else
		{
			m_LocalStatic.SetWindowText("Remote Node");
		}

		m_LocalStatic.EnableWindow(TRUE);

		m_hAttachedVideoSource = hItem;
	}

	NodeName.ReleaseBuffer();
	FullModuleName.ReleaseBuffer();

	InitValues();

	m_CurrentEvent = "AttachVideoSource";
	m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);

	UpdateData(FALSE);
}

void CSimpleDlg::OnDetachVideoSource(long hItem, short bIsLocal)
{
	m_DisplayCtrl.SetVideoSource(NULL, (BOOL) bIsLocal);
	m_VnExplorerCtrl.VideoSourceDetached(hItem);

	m_ModName.SetWindowText("");
	m_ModName.EnableWindow(FALSE);

	m_LocalStatic.SetWindowText("");
	m_LocalStatic.EnableWindow(FALSE);

	InitValues();

	m_CurrentEvent = "DetachVideoSource";
	m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);

	UpdateData(FALSE);
}


void CSimpleDlg::OnItemExpanded(long hItem, long nAction)
{
	InitValues();

	m_CurrentEvent = "ItemExpanded";
	m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);

	if(nAction == TVE_COLLAPSE)
	{
		m_FlagText = "Item Collapsed";
	}
	else if(nAction == TVE_EXPAND)
	{
		m_FlagText = "Item Expanded";
	}

	UpdateData(FALSE);
}

void CSimpleDlg::OnSelectChanged(long hItemNew, long hItemOld, long nAction)
{
	InitValues();

	m_CurrentEvent = "SelectChanged";
	m_ItemText = m_VnExplorerCtrl.GetItemText(hItemNew);
	m_OldItemText = m_VnExplorerCtrl.GetItemText(hItemOld);

	if(!m_OldItemText.IsEmpty())
	{
		m_OldItemStatic.ShowWindow(SW_SHOWNORMAL);
	}

	if(nAction == TVC_BYKEYBOARD)
	{
		m_FlagText = "By a Keystroke";
	}
	else if(nAction == TVC_BYMOUSE)
	{
		m_FlagText = "By a Mouse Click";
	}
	else if(nAction == TVC_UNKNOWN)
	{
		m_FlagText = "By Internal Event";
	}

	UpdateData(FALSE);
}

void CSimpleDlg::OnLeftClicked(long x, long y) 
{
	InitValues();

	m_CurrentEvent = "LeftClicked";

	m_xValue.Format("%d", x);
	m_yValue.Format("%d", y);
	m_xStatic.ShowWindow(SW_SHOWNORMAL);
	m_yStatic.ShowWindow(SW_SHOWNORMAL);

	long lFlags;
	long hItem = m_VnExplorerCtrl.HitTest((short) x, (short) y, (long) &lFlags);

	m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);
	m_FlagText = FlagToText((UINT) lFlags);
	

	UpdateData(FALSE);
}

void CSimpleDlg::OnRightClicked(long x, long y) 
{
	InitValues();

	m_CurrentEvent = "RightClicked";

	m_xValue.Format("%d", x);
	m_yValue.Format("%d", y);
	m_xStatic.ShowWindow(SW_SHOWNORMAL);
	m_yStatic.ShowWindow(SW_SHOWNORMAL);

	long lFlags;
	long hItem = m_VnExplorerCtrl.HitTest((short) x, (short) y, (long) &lFlags);

	m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);
	m_FlagText = FlagToText((UINT) lFlags);

	UpdateData(FALSE);
}

void CSimpleDlg::OnBeginDrag(short nDrag, long hItem, long x, long y, long lParam) 
{
	UpdateData();

	if(m_bDrag)
	{
		m_VnExplorerCtrl.BeginDrag(lParam, (short) m_bDragTrace);

		InitValues();

		m_CurrentEvent = "BeginDrag";

		if(nDrag == 0)		// Left Drag
		{
			m_FlagText = "Left Drag";
		}
		else
		{
			m_FlagText = "Right Drag";
		}

		m_xValue.Format("%d", x);
		m_yValue.Format("%d", y);
		m_xStatic.ShowWindow(SW_SHOWNORMAL);
		m_yStatic.ShowWindow(SW_SHOWNORMAL);

		m_ItemText = m_VnExplorerCtrl.GetItemText(hItem);

		UpdateData(FALSE);
	}
}

void CSimpleDlg::OnDragMove(short nDrag, long x, long y) 
{
	m_CurrentEvent = "DragMove";

	if(nDrag == 0)		// Left Drag
	{
		m_FlagText = "Left Drag";
	}
	else
	{
		m_FlagText = "Right Drag";
	}

	m_xValue.Format("%d", x);
	m_yValue.Format("%d", y);
	m_xStatic.ShowWindow(SW_SHOWNORMAL);
	m_yStatic.ShowWindow(SW_SHOWNORMAL);

	UpdateData(FALSE);
}

void CSimpleDlg::OnEndDrag(short nDrag, long x, long y) 
{
	m_VnExplorerCtrl.EndDrag();

	m_CurrentEvent = "EndDrag";

	if(nDrag == 0)		// Left Drag
	{
		m_FlagText = "Left Drag";
	}
	else
	{
		m_FlagText = "Right Drag";
	}

	m_xValue.Format("%d", x);
	m_yValue.Format("%d", y);
	m_xStatic.ShowWindow(SW_SHOWNORMAL);
	m_yStatic.ShowWindow(SW_SHOWNORMAL);


	UpdateData(FALSE);
}

CString CSimpleDlg::FlagToText(UINT uFlags)
{
	CString Str = "";
	
	if(uFlags & TVHT_ABOVE)
	{
		Str = "Above the client area.";
	}
	else if(uFlags & TVHT_BELOW)
	{
		Str = "Below the client area.";
	}
	else if(uFlags & TVHT_NOWHERE)
	{
		Str = "In the client area, but below the last item.";
	}
	else if(uFlags & TVHT_ONITEMBUTTON)
	{
		Str = "On the item button.";
	}
	else if(uFlags & TVHT_ONITEMICON)
	{
		Str = "On the item bitmap.";
	}
	else if(uFlags & TVHT_ONITEMINDENT)
	{
		Str = "In the item indentation.";
	}
	else if(uFlags & TVHT_ONITEMLABEL)
	{
		Str = "On the item text.";
	}
	else if(uFlags & TVHT_ONITEMRIGHT)
	{
		Str = "In the area to the right of the item.";
	}
	else if(uFlags & TVHT_ONITEMSTATEICON)
	{
		Str = "On the item state icon.";
	}
	else if(uFlags & TVHT_TOLEFT)
	{
		Str = "To the left of the client area.";
	}
	else if(uFlags & TVHT_TORIGHT)
	{
		Str = "To the right of the client area.";
	}

	return Str;
}

void CSimpleDlg::OnClose() 
{
	if(m_hAttachedVideoSource)
	{
		m_VnExplorerCtrl.VideoSourceDetached(m_hAttachedVideoSource);
	}

	CDialog::OnClose();
}
