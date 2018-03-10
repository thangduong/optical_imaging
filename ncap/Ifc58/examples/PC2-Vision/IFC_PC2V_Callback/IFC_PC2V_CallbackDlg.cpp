//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CallbackDlg.cpp
//
//  BIRTH DATE:     December 2002
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
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Basic acquisition and display with callback functions.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "IFC_PC2V_Callback.h"
#include "IFC_PC2V_CallbackDlg.h"
#include "CamSelDlg.h"                      // Cam Selector Dialog Box

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2V_CallbackDlg::CIFC_PC2V_CallbackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_CallbackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_CallbackDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pCam              = NULL;
    m_pImageConnection  = NULL;

    m_bIsGrabbing       = FALSE;
    m_bAppClosing       = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;

    m_dwFrameCounter    = 0;
    m_dwFieldCounter    = 0;
}

void CIFC_PC2V_CallbackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_CallbackDlg)
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_SOF, m_EditCallBkSOF);
	DDX_Control(pDX, IDC_EDIT_EOF, m_EditCallBkEOF);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIFC_PC2V_CallbackDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_CallbackDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------
//              MyAcqCallback_EOF
//------------------------------------------
// Function called when the "End of Frame"
// event occurs
//------------------------------------------
void CIFC_PC2V_CallbackDlg::MyAcqCallback_EOF(void *pContext)
{
CIFC_PC2V_CallbackDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CallbackDlg *)pContext;

    // Increment and show the frame counter

    pMyClass->m_dwFrameCounter++;

    strToShow.Format("%d", pMyClass->m_dwFrameCounter);
    pMyClass->m_EditCallBkEOF.SetWindowText(strToShow);

    // Show the acquired image from camera

    pMyClass->m_pImageConnection->Display();

}


//------------------------------------------
//              MyAcqCallback_SOF
//------------------------------------------
// Function called when the "Start of Field"
// event occurs
//------------------------------------------
void CIFC_PC2V_CallbackDlg::MyAcqCallback_SOF(void *pContext)
{
CIFC_PC2V_CallbackDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CallbackDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Increment and show the field counter

    pMyClass->m_dwFieldCounter++;

    strToShow.Format("%d", pMyClass->m_dwFieldCounter);
    pMyClass->m_EditCallBkSOF.SetWindowText(strToShow);
}




//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_CallbackDlg::OnInitDialog()
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

    if (InitIFC_Callback() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC callback object !!!"));
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
BOOL CIFC_PC2V_CallbackDlg::InitIFC_Capture()
{
CAM_ATTR attrib;

    // First, try to find and use the default configuration file "p2vtest.txt"

    m_pBrdMod = IfxCreateCaptureModule("P2V", 0, "p2vtest.txt");       // Use PC2-Vision board # 0
    if (m_pBrdMod == NULL)
    {
        // Failed to find and use the default configuration file "p2vtest.txt"
        // Ask user to select a camera type

        m_pBrdMod = IfxCreateCaptureModule("P2V", 0);       // Use PC2-Vsion board # 0
        if (m_pBrdMod == NULL)
        {
            AfxMessageBox(_T("Can't find PC2Vision board in the system !!!"));
            return FALSE;
        }

        m_pCam = m_pBrdMod->GetCam(0);

        CCamSelDlg CamDlg(this, m_pCam);
        CamDlg.DoModal();

        // Keep selected port and camera type

        SetPortAndCamType(CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);
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
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_CallbackDlg::InitIFC_Callback()
{
    m_pIntCallback_EOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_EOFRM, MyAcqCallback_EOF, this);

    if (m_pIntCallback_EOF == NULL)
        return FALSE;

    m_pIntCallback_SOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_START_OF_FIELD, MyAcqCallback_SOF, this);

    if (m_pIntCallback_SOF == NULL)
        return FALSE;

    return TRUE;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_CallbackDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_EOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOF);
    m_pIntCallback_EOF = NULL;

    ExceptCode= m_pIntCallback_SOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SOF);
    m_pIntCallback_SOF = NULL;

}




//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_CallbackDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
{
CImgConn *ImgConn;
RECT recSize;
double dZoomX, dZoomY;

    ImgConn = IfxCreateImgConn(cam, hWnd, IFC_DIB_SINK, ICAP_INTR_EOF);
    if (ImgConn)
    {
        CImgSink *imgSink = ImgConn->GetSink();
        m_StaticDisplay.GetClientRect(&recSize);

        // Scale the image to fit the window size
        
        dZoomX = (double)recSize.right / (double)m_dwCamSizeX;
        dZoomY = (double)recSize.bottom / (double)m_dwCamSizeY;

        dZoomX *= 10.0;
        dZoomX = floor(dZoomX);
        dZoomX /= 10.0;                 // Keep only one decimal digit

        dZoomY *= 10.0;
        dZoomY = floor(dZoomY);
        dZoomY /= 10.0;                 // Keep only one decimal digit

        imgSink->SetZoom(dZoomX, dZoomY);
    }

    return ImgConn;

}



//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_CallbackDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_CallbackDlg::ReleaseIFC_ImageConnection()
{

    if (m_pImageConnection)
    {
        delete m_pImageConnection;
        m_pImageConnection = NULL;
    }

}


//------------------------------------------
//              OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnPaint() 
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
HCURSOR CIFC_PC2V_CallbackDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_CallbackDlg::ReleaseAll()
{

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_GUI);

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_CallbackDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Show active port

    strToShow.Format("%d", dwActivePort + 1);
    m_EditCurrentPort.SetWindowText(strToShow);

    // Get a Camera object from this port

    m_pCam = m_pBrdMod->GetCam(dwActivePort);

    // Assign the selected camera type to this port and show it

    m_pCam->SetCameraType(pszCamType);
    m_EditCameraType.SetWindowText(pszCamType);

    // Keep attributes

    m_pCam->GetAttr(&attr);

    m_dwCamSizeX    = attr.dwWidth;
    m_dwCamSizeY    = attr.dwHeight;

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
void CIFC_PC2V_CallbackDlg::ClearDisplay()
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
BOOL CIFC_PC2V_CallbackDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//              OnButtonCam
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonCam() 
{
CCamSelDlg CamDlg(this, m_pCam);

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type and port number

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);

        // Release current Image Server object

        ReleaseIFC_ImageConnection();

        // Allocate new Image Server object

        m_pImageConnection = InitIFC_ImageConnection(m_StaticDisplay.GetSafeHwnd(), m_pCam);
        if (m_pImageConnection == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the display window

        m_bClearDisplay = TRUE;
    }

}





//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonFreeze() 
{

    m_pCam->Freeze();
    m_bIsGrabbing = FALSE;

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonGrab() 
{

    m_dwFrameCounter = 0;
    m_dwFieldCounter = 0;
    m_bClearDisplay = FALSE;

    m_pCam->Grab();

    m_bIsGrabbing = TRUE;
}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonSnap() 
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
//              OnClose
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnClose() 
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

    m_bAppClosing = TRUE;

    ReleaseAll();

    CDialog::OnClose();
}


//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnTimer(UINT nIDEvent) 
{

    if (nIDEvent == TIMER_GUI)
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

        UpdateButtons();            // Enable or not some buttons

        m_dwGuiCounter++;
    }

    CDialog::OnTimer(nIDEvent);
}




//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_CallbackDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}




//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_CallbackDlg::DrawWindowBorder(HWND hWnd)
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
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonTrigger() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


  
    // Check if current TRIGGER source is external

    TriggerSource = m_pCam->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    m_pCam->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd

    m_pCam->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }

}



//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_CallbackDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
