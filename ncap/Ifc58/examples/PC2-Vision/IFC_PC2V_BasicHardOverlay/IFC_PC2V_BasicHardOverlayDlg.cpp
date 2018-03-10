//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_BasicHardOverlayDlg.cpp
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
//                  Basic acquisition and display in an hardware overlay along
//                  with text drawing in the standard graphic surface.
//
//                  The hardware overlay is physically in the video memory of
//                  your display controller and convert in real-time a pixel
//                  in Y-Cr-Cb color format to the R-G-B format of your monitor.
//                  It also take care in real-time of the scaling (zoom).
//
//                  The benefit of using an hardware overlay is an extremely
//                  fast live display because the Host CPU don't have to do
//                  the pixel conversion and the image scaling.
//
//                  Keep in mind that the live image is in the overlay and the
//                  text drawned is in the standard graphic surface. The overlay
//                  and hence the live image is visible only if you draw the
//                  keying color in the standard graphic surface over the overlay.
//
//                  Your display controller must have an overlay feature for this
//                  demo to work.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "IFC_PC2V_BasicHardOverlay.h"
#include "IFC_PC2V_BasicHardOverlayDlg.h"
#include "CamSelDlg.h"                      // Cam Selector Dialog Box




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2V_BasicHardOverlayDlg::CIFC_PC2V_BasicHardOverlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_BasicHardOverlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_BasicHardOverlayDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_bIsGrabbing   = FALSE;

    m_dwFrameCounter        = 0;
    m_dwOnPaintCounter      = 0;
    m_dwLastOnPaintCounter  = 0;
	m_pImageConnection      = NULL;

}




void CIFC_PC2V_BasicHardOverlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_BasicHardOverlayDlg)
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_BasicHardOverlayDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_BasicHardOverlayDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_BasicHardOverlayDlg::OnInitDialog()
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

    m_pImageConnection = InitIFC_ImageConnection(m_StaticDisplay.GetSafeHwnd());
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
    // Start a timer drawing text every 2 seconds

    if (SetTimer(TIMER_DRAW, 2000, NULL) == NULL)
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
BOOL CIFC_PC2V_BasicHardOverlayDlg::InitIFC_Capture()
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
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_BasicHardOverlayDlg::InitIFC_ImageConnection(HWND hWnd)
{
CImgConn *ImgConn;
DWORD dwKeyColor;


    m_pSinkTemplate = IfxCreateImgSink(hWnd, YCRCB_SINK, 0, 0, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY);
    if (m_pSinkTemplate == NULL)
    {
        AfxMessageBox(_T("Your Video Controller does not have an Hardware Overlay !!!"));
        return NULL;
    }

    dwKeyColor = m_pSinkTemplate->GetColorKeyRep(KEY_COLOR);
    if (m_pSinkTemplate->SetDestColorKey(dwKeyColor) == FALSE)
    {
        return NULL;
    }

    m_pImgSrc = IfxCreateImgSrc(m_pCam);
    if (m_pImgSrc == NULL)
    {
        return NULL;
    }

    ImgConn = IfxCreateImgConn(m_pImgSrc, m_pSinkTemplate);

    // Scale the image to fit the display window

    if (ImgConn)
    {
        CImgSink *imgSink = ImgConn->GetSink();

        imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
    }

    // Create image server

    if (ImgConn->StartLiveImage(m_pCam, ICAP_INTR_VB) == FALSE)
    {
        return NULL;
    }

    return ImgConn;

}



//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::ReleaseIFC_ImageConnection()
{

    if (m_pImageConnection)
    {
        delete m_pImageConnection;
        m_pImageConnection = NULL;
    }

    if (m_pSinkTemplate != NULL)
    {
        delete m_pSinkTemplate;
        m_pSinkTemplate = NULL;
    }

    if (m_pImgSrc != NULL)
    {
        delete m_pImgSrc;
        m_pImgSrc = NULL;
    }

}




//------------------------------------------
//              OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnPaint() 
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
        FillDisplayWithKeyColor();

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
HCURSOR CIFC_PC2V_BasicHardOverlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::ReleaseAll()
{

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);
    KillTimer(TIMER_DRAW);

}




//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
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
void CIFC_PC2V_BasicHardOverlayDlg::ClearDisplay()
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
//         FillDisplayWithKeyColor
//------------------------------------------
// Make the overlay visible
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::FillDisplayWithKeyColor()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
CBrush KeyBrush;
RECT RectDraw;


    KeyBrush.CreateSolidBrush(KEY_COLOR);

    pOldBrush = (CBrush *)MyDC.SelectObject(&KeyBrush);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);

}


//------------------------------------------
//              DrawTextTopLeft
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::DrawTextTopLeft() 
{
CFont MyNewFont;
CFont *pOldFont;
CString strToShow;
CClientDC TheDC(this);
RECT RectPosition;
UINT OldTextAlign;
COLORREF OldColor;
int OldBkgnd;
int OldMapMode;


    // Create a desired Font

    MyNewFont.CreatePointFont(120, "Arial");
    pOldFont = TheDC.SelectObject(&MyNewFont);
    if (pOldFont == NULL)
    {
        AfxMessageBox("Cannot select font into display context");
        return;
    }

    // Set desired Modes

    OldMapMode      = TheDC.SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = TheDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = TheDC.SetTextAlign(TA_LEFT | TA_TOP);
    OldColor        = TheDC.SetTextColor(RGB(0, 0xFF, 0));

    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectPosition);

    strToShow = _T("Draw Text With Windows GDI");
    TheDC.TextOut(RectPosition.left, RectPosition.top, strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Restore old modes

    TheDC.SetMapMode(OldMapMode);
    TheDC.SetBkMode(OldBkgnd);
    TheDC.SetTextColor(OldColor);
    TheDC.SetTextAlign(OldTextAlign);
    TheDC.SelectObject(pOldFont);

}



//------------------------------------------
//              DrawTextBottomRight
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::DrawTextBottomRight() 
{
CFont MyNewFont;
CFont *pOldFont;
CString strToShow;
CClientDC TheDC(this);
RECT RectPosition;
UINT OldTextAlign;
COLORREF OldColor;
int OldBkgnd;
int OldMapMode;


    // Create a desired Font

    MyNewFont.CreatePointFont(120, "Times New Roman");
    pOldFont = TheDC.SelectObject(&MyNewFont);
    if (pOldFont == NULL)
    {
        AfxMessageBox("Cannot select font into display context");
        return;
    }

    // Set desired Modes

    OldMapMode      = TheDC.SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = TheDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = TheDC.SetTextAlign(TA_RIGHT | TA_BOTTOM);
    OldColor        = TheDC.SetTextColor(RGB(0, 0, 0xFF));

    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectPosition);

    strToShow = _T("Draw Text With Windows GDI");
    TheDC.TextOut(RectPosition.right, RectPosition.bottom, strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Restore old modes

    TheDC.SetMapMode(OldMapMode);
    TheDC.SetBkMode(OldBkgnd);
    TheDC.SetTextColor(OldColor);
    TheDC.SetTextAlign(OldTextAlign);
    TheDC.SelectObject(pOldFont);

}



//------------------------------------------
//              DrawTextCentered
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::DrawTextCentered() 
{
CFont MyNewFont;
CFont *pOldFont;
CString strToShow;
CClientDC TheDC(this);
RECT RectSize;
RECT RectPosition;
UINT OldTextAlign;
COLORREF OldColor;
int OldBkgnd;
int OldMapMode;


    // Create a desired Font

    MyNewFont.CreatePointFont(120, "Comic Sans MS");
    pOldFont = TheDC.SelectObject(&MyNewFont);
    if (pOldFont == NULL)
    {
        AfxMessageBox("Cannot select font into display context");
        return;
    }

    // Set desired Modes

    OldMapMode      = TheDC.SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = TheDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = TheDC.SetTextAlign(TA_CENTER | TA_BASELINE);
    OldColor        = TheDC.SetTextColor(RGB(0xFF, 0, 0));

    ::GetClientRect(m_StaticDisplay.GetSafeHwnd(), &RectSize);
    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectPosition);

    strToShow = _T("Draw Text With Windows GDI");
    TheDC.TextOut(RectPosition.left + (RectSize.right / 2),
                   RectPosition.top + (RectSize.bottom / 2),
                    strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Restore old modes

    TheDC.SetMapMode(OldMapMode);
    TheDC.SetBkMode(OldBkgnd);
    TheDC.SetTextColor(OldColor);
    TheDC.SetTextAlign(OldTextAlign);
    TheDC.SelectObject(pOldFont);

}



//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_BasicHardOverlayDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonCam() 
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

        SetPortAndCamType(CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);

        // Release current Image Server object

        ReleaseIFC_ImageConnection();

        // Allocate new Image Server object

        m_pImageConnection = InitIFC_ImageConnection(m_StaticDisplay.GetSafeHwnd());
        if (m_pImageConnection == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the display

        m_bClearDisplay = TRUE;

    }
}



//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonFreeze() 
{

    if (m_pImageConnection)
    {
        m_pImageConnection->StopLiveImage();
    }

    m_pCam->Freeze();
    m_bIsGrabbing = FALSE;

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonGrab() 
{

    if (m_pImageConnection)
    {
        m_pImageConnection->StartLiveImage(m_pCam, ICAP_INTR_EOF);
    }

    m_dwFrameCounter = 0;
    m_bClearDisplay = FALSE;

    m_pCam->Grab();

    m_bIsGrabbing = TRUE;
    FillDisplayWithKeyColor();          // Make the overlay visible
}





//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonSnap() 
{
BOOL bTest;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    if (m_pImageConnection)
    {
        bTest = m_pImageConnection->StopLiveImage();
    }

    m_bClearDisplay = FALSE;

    m_pCam->Snap();

    if (m_pImageConnection)
    {
        m_pImageConnection->Display();
    }

    FillDisplayWithKeyColor();          // Make the overlay visible
}



//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnClose() 
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
//              OnTimer
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnTimer(UINT nIDEvent) 
{
static DWORD dwNextTextPosition;


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

        UpdateButtons();                // Enable or not some buttons

        m_dwGuiCounter++;
    }
    else if (nIDEvent == TIMER_DRAW)
    {
        dwNextTextPosition++;
        dwNextTextPosition %= 4;        // Choose another text position

        if (dwNextTextPosition == 0)
            DrawTextTopLeft();

        else if (dwNextTextPosition == 1)
            DrawTextBottomRight();

        else if (dwNextTextPosition == 2)
            DrawTextCentered();

        else if (dwNextTextPosition == 3)
            FillDisplayWithKeyColor();      // Erase former text by drawing the key color
    }

	CDialog::OnTimer(nIDEvent);

}


//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::ShowStatistics() 
{
double dFrameRate;
CString strToShow;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        return;
    }

    // Compute and show acquisition frame rate

    dFrameRate = m_pImageConnection->GetLiveImageFPS();
    strToShow.Format("%.2f", dFrameRate);
    m_EditFrameRate.SetWindowText(strToShow);

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}



//------------------------------------------
//              OnMove
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::OnMove(int x, int y) 
{
    CDialog::OnMove(x, y);

    if (m_bIsGrabbing && m_pImageConnection)
    {
        m_pImageConnection->Display();
    }

}


//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_BasicHardOverlayDlg::DrawWindowBorder(HWND hWnd)
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
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonTrigger() 
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
void CIFC_PC2V_BasicHardOverlayDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}

