//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2C_BasicGrabDlg.cpp
//
//  BIRTH DATE:     November 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.6.1)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  HARDWARE:       PC2-CamLink Frame Grabber
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Basic acquisition and display with an Image Server.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "cl2cam.h"                         // PC2-CamLink related

#include "IFC_PC2C_BasicGrab.h"
#include "IFC_PC2C_BasicGrabDlg.h"
#include "CamSelDlg.h"                      // Cam Selector Dialog Box


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2C_BasicGrabDlg::CIFC_PC2C_BasicGrabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2C_BasicGrabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2C_BasicGrabDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pCam              = NULL;
    m_pImageConnection  = NULL;
    m_GrabID            = NULL;

    m_bIsGrabbing       = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;

    m_dwFrameCounter    = 0;
}



void CIFC_PC2C_BasicGrabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2C_BasicGrabDlg)
	DDX_Control(pDX, IDC_EDIT_ST, m_EditSensorType);
	DDX_Control(pDX, IDC_EDIT_FS, m_EditFrameSize);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2C_BasicGrabDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2C_BasicGrabDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2C_BasicGrabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    // Initializes IFC capture module

    if (InitIFC_Capture() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC capture object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes IFC Image connection module

    m_pImageConnection = InitIFC_ImageConnection(m_StaticDisplay.GetSafeHwnd(), m_pCam);
    if (m_pImageConnection == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Init GUI related variables

    m_dwGuiCounter = 0;
    m_bClearDisplay = TRUE;

    // Start a timer showing statistics every 2 seconds

    if (SetTimer(TIMER_STAT, 2000, NULL) == NULL)
    {
        AfxMessageBox(_T("Could not start a timer !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Start a timer managing some GUI housekeeping every half second

    if (SetTimer(TIMER_GUI, 500, NULL) == NULL)
    {
        AfxMessageBox(_T("Could not start a timer !!!"));
        EndDialog(7);
        return FALSE;
    }

    return TRUE;  // return TRUE  unless you set the focus to a control

}

//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2C_BasicGrabDlg::InitIFC_Capture()
{
CAM_ATTR attrib;


    // First, try to find and use the default configuration file "cl2test.txt"

    m_pBrdMod = IfxCreateCaptureModule("CL2", 0, "cl2test.txt");       // Use PC2-CamLink board # 0
    if (m_pBrdMod == NULL)
    {
        // Failed to find and use the default configuration file
        // Ask user to select a camera type

        m_pBrdMod = IfxCreateCaptureModule("CL2", 0);       // Use PC2-CamLink board # 0
        if (m_pBrdMod == NULL)
        {
            AfxMessageBox(_T("Can't find PC2-CamLink board in the system !!!"));
            return FALSE;
        }

        m_pCam = m_pBrdMod->GetCam(0);

        CCamSelDlg CamDlg(this, m_pCam);
        CamDlg.DoModal();

        // Keep port 0 and camera type

        SetPortAndCamType(0, CamDlg.m_pszCurCamera);
    }
    else
    {
        // Keep port 0

        m_pCam = m_pBrdMod->GetCam(0);
        m_pCam->GetAttr(&attrib);
        SetPortAndCamType(0, attrib.camName);
    }

    return TRUE;

}



//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2C_BasicGrabDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
{
CImgConn *ImgConn;

    ImgConn = IfxCreateImgConn(cam, hWnd, IFC_LIVE_IMAGE, ICAP_INTR_EOF);

    // Scale the image to fit the display window

    if (ImgConn)
    {
        CImgSink *imgSink = ImgConn->GetSink();
        imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
    }

    return ImgConn;

}



//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::ReleaseIFC_ImageConnection()
{

    if (m_pImageConnection)
    {
        delete m_pImageConnection;
        m_pImageConnection = NULL;
    }

}

//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::ReleaseAll()
{

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Get a Camera object from this port

    m_pCam = m_pBrdMod->GetCam(dwActivePort);

    // Assign the selected camera type to this port and show it

    m_pCam->SetCameraType(pszCamType);
    m_EditCameraType.SetWindowText(pszCamType);

    // Keep image size and show it

    m_pCam->GetAttr(&attr);

    m_dwCamSizeX = attr.dwWidth;
    m_dwCamSizeY = attr.dwHeight;

    strToShow.Format(_T("%d x %d"), m_dwCamSizeX, m_dwCamSizeY);
    m_EditFrameSize.SetWindowText(strToShow);

    // Determine if area-scan or line-scan camera is used

    if (m_pCam->GetAcqParam(P_FEN_ENABLE) == IFC_ENABLE)
    {
        m_bAreaScanMode = TRUE;
        m_EditSensorType.SetWindowText(_T("Area-Scan"));
    }
    else
    {
        m_bAreaScanMode = FALSE;
        m_EditSensorType.SetWindowText(_T("Line-Scan"));
    }

    // Determine if triggered mode is used

    if (m_pCam->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
    {
        m_bTriggerMode = TRUE;
    }
    else
    {
        m_bTriggerMode = FALSE;
    }

}



//------------------------------------------
//              ClearDisplay
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);
}




//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2C_BasicGrabDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
{
RECT  WinPosition;
POINT UpperLeft, LowerRight;


    if (lpRect == NULL)
    {
        return FALSE;
    }

    if (::GetWindowRect(hWnd, &WinPosition) == FALSE)
    {
        return FALSE;
    }

    UpperLeft.x     = WinPosition.left;
    UpperLeft.y     = WinPosition.top;
    LowerRight.x    = WinPosition.right;
    LowerRight.y    = WinPosition.bottom;

    if (::ScreenToClient(m_hWnd, &UpperLeft) == FALSE)
    {
        return FALSE;
    }
    if (::ScreenToClient(m_hWnd, &LowerRight) == FALSE)
    {
        return FALSE;
    }

    lpRect->left   = UpperLeft.x;
    lpRect->top    = UpperLeft.y;
    lpRect->right  = LowerRight.x;
    lpRect->bottom = LowerRight.y;

    return TRUE;
}



//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::ShowStatistics() 
{
double dFrameRate;
CString strToShow;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        return;
    }

    // Show acquisition frame rate

    dFrameRate = m_pImageConnection->GetLiveImageFPS();
    strToShow.Format("%.2f", dFrameRate);
    m_EditFrameRate.SetWindowText(strToShow);

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing && m_bTriggerMode);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}



//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::DrawWindowBorder(HWND hWnd)
{
CClientDC MyDC(this);
CPen MyBluePen (PS_SOLID, 3, RGB(0x00,0x00,0xFF));       // Blue Border 3 pixels thick
CBrush *pOldBrush;
CPen *pOldPen;
RECT rectToDraw;


    // Set-up GDI objects

    pOldPen = MyDC.SelectObject(&MyBluePen);
    pOldBrush = (CBrush *)MyDC.SelectStockObject(NULL_BRUSH);   // Don't paint inside rectangle
    MyDC.SetMapMode(MM_TEXT);

    // Draw the border rectangle

    GetWindowPosition(hWnd, &rectToDraw);
    InflateRect(&rectToDraw, 5, 5);
    MyDC.Rectangle(&rectToDraw);

    // Release the GDI objects

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}




//------------------------------------------
//              OnPaint
//------------------------------------------
/// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnPaint() 
{
	if (IsIconic())
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

        m_pImageConnection->Display();

        if (m_bClearDisplay)
        {
            ClearDisplay();
        }

        DrawWindowBorder(m_StaticDisplay.m_hWnd);

        m_dwOnPaintCounter++;
	}
}



//------------------------------------------
//              OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2C_BasicGrabDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              OnButtonCam
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonCam() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type and port number

    CCamSelDlg CamDlg(this, m_pCam);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(0, CamDlg.m_pszCurCamera);

        // Release current Image Server object

        ReleaseIFC_ImageConnection();

        // Allocate new Image Server object

        m_pImageConnection = InitIFC_ImageConnection(m_StaticDisplay.GetSafeHwnd(), m_pCam);
        if (m_pImageConnection == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        m_bClearDisplay = TRUE;

    }

}



//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonFreeze() 
{
    m_pCam->Freeze();
    m_bIsGrabbing = FALSE;
}




//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonGrab() 
{

    m_dwFrameCounter = 0;
    m_bClearDisplay = FALSE;

    m_pCam->Grab();

    m_bIsGrabbing = TRUE;
}




//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonSnap() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay = FALSE;

    m_pCam->Snap();

}



//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        if (m_bClearDisplay && ((m_dwGuiCounter & 0x0F) == 0))
        {
            ClearDisplay();
            DrawWindowBorder(m_StaticDisplay.m_hWnd);
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        UpdateButtons();                    // Enable or not some buttons

        m_dwGuiCounter++;
    }

	CDialog::OnTimer(nIDEvent);
}



//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnClose() 
{
CString strWarnText;

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before exiting"));
        return;
    }

    strWarnText = _T("Are you sure you want to exit ");
    strWarnText += APP_BASIC_TITLE;
    strWarnText += _T(" ?");

    int iAnswer = MessageBox(strWarnText, _TEXT("Question"), MB_YESNOCANCEL);
    if (iAnswer != IDYES)
    {
        return;                         // No, we don't exit
    }

    ReleaseAll();

	CDialog::OnClose();
}




//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}


//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2C_BasicGrabDlg::OnButtonTrigger() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


    //----------------------Logic for AREA-SCAN cameras

    if (m_bAreaScanMode)
    {
        TriggerSource = m_pCam->GetAcqParam(CL2_FRAME_TRIG_SRC);

        // Check if current TRIGGER source is software or not

        if (TriggerSource != CL2_SOFT_FRAME_TRIG)
        {
            bTriggerSrcWasExternal = TRUE;
        }

        // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

        m_pCam->SetAcqParam(CL2_FRAME_TRIG_SRC, CL2_SOFT_FRAME_TRIG);  // TRIGGER source is soft cmd

        m_pCam->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

        // Restore original TRIGGER source

        if (bTriggerSrcWasExternal)
        {
            m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
        }

    }

    //----------------------Logic for LINE-SCAN cameras

    else
    {
        TriggerSource = m_pCam->GetAcqParam(CL2_VFRAME_TRIG_SOURCE);

        // Check if current TRIGGER source is software or not

        if (TriggerSource != CL2_SOFT_VFRAME_TRIG)
        {
            bTriggerSrcWasExternal = TRUE;
        }

        // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

        m_pCam->SetAcqParam(CL2_VFRAME_TRIG_SOURCE, CL2_SOFT_VFRAME_TRIG);  // TRIGGER source is soft cmd

        m_pCam->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

        // Restore original TRIGGER source

        if (bTriggerSrcWasExternal)
        {
            m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
        }

    }

}
