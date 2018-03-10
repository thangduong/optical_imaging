//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_BasicSoftOverlayDlg.cpp
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
//                  Basic acquisition and display along with text drawing in
//                  a software overlay.
//
//                  The software overlay allow you to draw over your live image
//                  using the Windows GDI. It is not in the video memory and it
//                  is not as fast as an hardware overlay.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "IFC_PC2V_BasicSoftOverlay.h"
#include "IFC_PC2V_BasicSoftOverlayDlg.h"
#include "CamSelDlg.h"                      // Cam Selector Dialog Box


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2V_BasicSoftOverlayDlg::CIFC_PC2V_BasicSoftOverlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_BasicSoftOverlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_BasicSoftOverlayDlg)
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



void CIFC_PC2V_BasicSoftOverlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_BasicSoftOverlayDlg)
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2V_BasicSoftOverlayDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_BasicSoftOverlayDlg)
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
void CIFC_PC2V_BasicSoftOverlayDlg::MyAcqCallback_EOF(void *pContext)
{
CIFC_PC2V_BasicSoftOverlayDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_BasicSoftOverlayDlg *)pContext;

    // Erase all previous drawing in the overlay

    pMyClass->ClearOverlay();

    // Increment and show the frame counter in the live image

    pMyClass->m_dwFrameCounter++;

    pMyClass->DrawFrameCountAsText();

    // Draw text in the live image

    if ((pMyClass->m_dwFrameCounter & 0x20) == 0)
    {
        pMyClass->DrawTextTopLeft();
    }
    else
    {
        pMyClass->DrawTextBottomRight();
    }

}




//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_BasicSoftOverlayDlg::OnInitDialog()
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

    // Initializes IFC callback mechanism

    if (InitIFC_Callback() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC callback object !!!"));
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}



//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_BasicSoftOverlayDlg::InitIFC_Capture()
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
CImgConn *CIFC_PC2V_BasicSoftOverlayDlg::InitIFC_ImageConnection(HWND hWnd)
{
CImgConn *ImgConn;


    // Create a software overlay object with the same size as the captured image
    // because it will be scaled on the screen as well as the captured image

    m_pImgOverlay = IfxCreateOverlay(SW_OVERLAY,(WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY);
    if (m_pImgOverlay == NULL)
    {
        return NULL;
    }

    // Create a source object feeded by the camera

    m_pImgSrc = IfxCreateImgSrc(m_pCam);
    if (m_pImgSrc == NULL)
    {
        return NULL;
    }

    // Create a DIB sink object to show the live image

    m_pImgSink = IfxCreateImgSink(hWnd, DIB_SINK, 0, 0, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY);
    if (m_pImgSink == NULL)
    {
        return NULL;
    }

    // Create an image connection object

    ImgConn = IfxCreateImgConn(m_pImgSrc, m_pImgSink, m_pImgOverlay);

    // Scale the image to fit the window size

    if (ImgConn)
    {
        CImgSink *imgSink = ImgConn->GetSink();

        imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
    }

    // Hookup interrupt and create server

    if (ImgConn->StartLiveImage(m_pCam, ICAP_INTR_EOF) == FALSE)
    {
        return NULL;
    }

    return ImgConn;

}



//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_BasicSoftOverlayDlg::InitIFC_Callback()
{
    m_pIntCallback_EOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_EOFRM, MyAcqCallback_EOF, this);

    if (m_pIntCallback_EOF == NULL)
        return FALSE;

    return TRUE;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_EOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOF);
    m_pIntCallback_EOF = NULL;

}





//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ReleaseIFC_ImageConnection()
{

    if (m_pImageConnection)
    {
        delete m_pImageConnection;
        m_pImageConnection = NULL;
    }

    if (m_pImgSink != NULL)
    {
        delete m_pImgSink;
        m_pImgSink = NULL;
    }

    if (m_pImgOverlay != NULL)
    {
        delete m_pImgOverlay;
        m_pImgOverlay = NULL;
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
void CIFC_PC2V_BasicSoftOverlayDlg::OnPaint() 
{
CString strToShow;


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
HCURSOR CIFC_PC2V_BasicSoftOverlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ReleaseAll()
{

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
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
//              OnButtonCam
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonCam() 
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

        // Clear the display window

        m_bClearDisplay = TRUE;
    }
}




//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonFreeze() 
{
    m_pCam->Freeze();	
    m_bIsGrabbing = FALSE;
}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonGrab() 
{

    m_dwFrameCounter = 0;
    m_bClearDisplay = FALSE;

    m_pCam->Grab();
    m_bIsGrabbing = TRUE;
}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonSnap() 
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
void CIFC_PC2V_BasicSoftOverlayDlg::OnClose() 
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
void CIFC_PC2V_BasicSoftOverlayDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
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

    CDialog::OnTimer(nIDEvent);

}




//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ShowStatistics() 
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
void CIFC_PC2V_BasicSoftOverlayDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}




//------------------------------------------
//              DrawTextTopLeft
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::DrawTextTopLeft() 
{
HDC hDC;
CDC *pOverlayDC;
CFont MyNewFont;
CFont *pOldFont;
CString strToShow;
UINT OldTextAlign;
COLORREF OldColor;
int OldBkgnd;
int OldMapMode;


    // Get the Display Context of the Software Overlay

    hDC = m_pImageConnection->GetOverlayDC();
    pOverlayDC = CDC::FromHandle(hDC);
    if ((hDC == NULL) || (pOverlayDC == NULL))
    {
        AfxMessageBox("Cannot get display context (DrawTextTopLeft)");
        return;
    }

    // Create a desired Font

    MyNewFont.CreatePointFont(250, "Arial");
    pOldFont = pOverlayDC->SelectObject(&MyNewFont);
    if (pOldFont == NULL)
    {
        AfxMessageBox("Cannot select font into display context");
        return;
    }

    // Set desired Modes

    OldMapMode      = pOverlayDC->SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = pOverlayDC->SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = pOverlayDC->SetTextAlign(TA_LEFT | TA_TOP);
    OldColor        = pOverlayDC->SetTextColor(RGB(0, 0xFF, 0));

    strToShow = _T("Draw Text With Windows GDI");
    pOverlayDC->TextOut(0, 0, strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Restore old modes

    pOverlayDC->SetMapMode(OldMapMode);
    pOverlayDC->SetBkMode(OldBkgnd);
    pOverlayDC->SetTextColor(OldColor);
    pOverlayDC->SetTextAlign(OldTextAlign);
    pOverlayDC->SelectObject(pOldFont);

    // Done with the overlay DC, release it

    pOverlayDC->DeleteTempMap();
    m_pImageConnection->ReleaseOverlayDC(hDC);

}



//------------------------------------------
//              DrawTextBottomRight
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::DrawTextBottomRight() 
{
HDC hDC;
CDC *pOverlayDC;
CFont MyNewFont;
CFont *pOldFont;
CString strToShow;
UINT OldTextAlign;
COLORREF OldColor;
int OldBkgnd;
int OldMapMode;
WORD wOvlaySizeX;
WORD wOvlaySizeY;


    // Get the Display Context of the Software Overlay

    hDC = m_pImageConnection->GetOverlayDC();
    pOverlayDC = CDC::FromHandle(hDC);
    if ((hDC == NULL) || (pOverlayDC == NULL))
    {
        AfxMessageBox("Cannot get display context (DrawTextBottomRight)");
        return;
    }

    // Create a desired Font

    MyNewFont.CreatePointFont(250, "Times New Roman");
    pOldFont = pOverlayDC->SelectObject(&MyNewFont);
    if (pOldFont == NULL)
    {
        AfxMessageBox("Cannot select font into display context");
        return;
    }

    // Set desired Modes

    OldMapMode      = pOverlayDC->SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = pOverlayDC->SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = pOverlayDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
    OldColor        = pOverlayDC->SetTextColor(RGB(0, 0, 0xFF));

    // Get overlay size

    wOvlaySizeX = m_pImgOverlay->GetWidth();
    wOvlaySizeY = m_pImgOverlay->GetHeight();

    // Draw the text

    strToShow = _T("Draw Text With Windows GDI");
    pOverlayDC->TextOut(wOvlaySizeX, wOvlaySizeY, strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Restore old modes

    pOverlayDC->SetMapMode(OldMapMode);
    pOverlayDC->SetBkMode(OldBkgnd);
    pOverlayDC->SetTextColor(OldColor);
    pOverlayDC->SetTextAlign(OldTextAlign);
    pOverlayDC->SelectObject(pOldFont);

    // Done with the overlay DC, release it

    pOverlayDC->DeleteTempMap();
    m_pImageConnection->ReleaseOverlayDC(hDC);

}





//------------------------------------------
//              DrawFrameCountAsText
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::DrawFrameCountAsText()
{
HDC hDC;
CDC *pOverlayDC;
COLORREF OldColor;
CFont MyNewFont;
CFont *pOldFont;
int iOldMapMode;
int iOldBkMode;
int iTextOffsetX;
int iTextOffsetY;
CString strToShow;
WORD wOvlaySizeX;
WORD wOvlaySizeY;
CSize TextSize;


    // Get the Display Context of the Software Overlay

    hDC = m_pImageConnection->GetOverlayDC();
    pOverlayDC = CDC::FromHandle(hDC);
    if ((hDC == NULL) || (pOverlayDC == NULL))
    {
        AfxMessageBox("Cannot get display context (DrawFrame)");
        return;
    }

    // Create a desired Font

    MyNewFont.CreatePointFont(250, "Comic Sans MS");
    pOldFont = pOverlayDC->SelectObject(&MyNewFont);

    // Set device-context parameters

    iOldMapMode     = pOverlayDC->SetMapMode(MM_TEXT);
    iOldBkMode      = pOverlayDC->SetBkMode(TRANSPARENT);
    OldColor        = pOverlayDC->SetTextColor(RGB(0xFF, 0, 0));

    // Draw the Frame Counter as text

    wOvlaySizeX = m_pImgOverlay->GetWidth();
    wOvlaySizeY = m_pImgOverlay->GetHeight();

    // Get text size in pixel and compute the text position

    strToShow.Format(_T("Frame # %d"), m_dwFrameCounter);
    TextSize = pOverlayDC->GetTextExtent(strToShow);
    iTextOffsetX = (wOvlaySizeX - TextSize.cx) / 2;
    iTextOffsetY = (wOvlaySizeY - TextSize.cy) / 2;

    pOverlayDC->TextOut(iTextOffsetX, iTextOffsetY, strToShow, strToShow.GetLength());

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    // Destroy GDI objects

    pOverlayDC->SetMapMode(iOldMapMode);
    pOverlayDC->SetBkMode(iOldBkMode);
    pOverlayDC->SetTextColor(OldColor);
    pOverlayDC->SelectObject(pOldFont);

    // Done with the overlay DC, release it

    pOverlayDC->DeleteTempMap();
    m_pImageConnection->ReleaseOverlayDC(hDC);

}





//------------------------------------------
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticDisplay.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    MyDC.SelectObject(pOldBrush);
}




//------------------------------------------
//              ClearOverlay
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::ClearOverlay()
{
HDC hDC;
CBrush *pOldBrush;
RECT RectDraw;
CDC *pOverlayDC;


    // Get the Display Context of the Software Overlay

    hDC = m_pImageConnection->GetOverlayDC();
    pOverlayDC = CDC::FromHandle(hDC);
    if ((hDC == NULL) || (pOverlayDC == NULL))
    {
        AfxMessageBox("Cannot get display context (ClearOverlay)");
        return;
    }

    pOldBrush = (CBrush *)pOverlayDC->SelectStockObject(BLACK_BRUSH);

    ::GetClientRect(m_StaticDisplay.GetSafeHwnd(), &RectDraw);

    // The software overlay is of the same size as the captured image
    // because it is scaled on the screen as well as the captured image

    RectDraw.right  = RectDraw.left + m_dwCamSizeX;
    RectDraw.bottom = RectDraw.top + m_dwCamSizeY;

    pOverlayDC->Rectangle(&RectDraw);

    // This Windows call ensures that all queued GDI calls are executed
    // immediately, to avoid any problems related to delayed execution

    GdiFlush();

    pOverlayDC->SelectObject(pOldBrush);

    // Done with the overlay DC, release it

    pOverlayDC->DeleteTempMap();
    m_pImageConnection->ReleaseOverlayDC(hDC);

}





//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_BasicSoftOverlayDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::DrawWindowBorder(HWND hWnd)
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
//          OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonTrigger() 
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
//          OnButtonTrap
//------------------------------------------
void CIFC_PC2V_BasicSoftOverlayDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
