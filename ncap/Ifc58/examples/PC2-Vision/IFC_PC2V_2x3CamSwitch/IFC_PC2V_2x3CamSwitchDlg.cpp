//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_2x3CamDlg.cpp
//
//  BIRTH DATE:     May 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V5.6)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Two blocks of three genlocked cameras dynamically switched.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"		                // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera type Selector Dialog Box

#include "IFC_PC2V_2x3CamSwitch.h"
#include "IFC_PC2V_2x3CamSwitchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_2x3CamSwitchDlg::CIFC_PC2V_2x3CamSwitchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_2x3CamSwitchDlg::IDD, pParent)
{
DWORD dwCamIndex;

	//{{AFX_DATA_INIT(CIFC_PC2V_2x3CamSwitchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apImageConnection[dwCamIndex] = NULL;
        m_aGrabID[dwCamIndex]           = NULL;
        m_apCam[dwCamIndex]             = NULL;
        m_abIsGrabbing[dwCamIndex]      = FALSE;
    }

    m_pIntCallback_SOT  = NULL;

    m_bAppClosing       = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwPixBitDepth     = 0;
    m_CamColor          = IFC_MONO;
    m_dwImageSize       = 0;
    m_dwSnapPolling     = 0;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apAcqThread[dwCamIndex]       = NULL;
        m_apHostCapMemory[dwCamIndex]   = NULL;
    }

    m_bIsSOT_EventDetected  = FALSE;
    m_bWasSOT_EventDetected = FALSE;

    m_bTriggerMode  = FALSE;
    m_bSnapping     = FALSE;

}





//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_2x3CamSwitchDlg)
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_EDIT_FR_TOTAL, m_EditFrameRateTotal);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM, m_ButtonCamType);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM, m_EditCamType);
	DDX_Control(pDX, IDC_STATIC_PAK2, m_StaticLightGroup2);
	DDX_Control(pDX, IDC_STATIC_PAK1, m_StaticLightGroup1);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_STATIC_DISPLAY23, m_StaticDisplayCam23);
	DDX_Control(pDX, IDC_STATIC_DISPLAY22, m_StaticDisplayCam22);
	DDX_Control(pDX, IDC_STATIC_DISPLAY21, m_StaticDisplayCam21);
	DDX_Control(pDX, IDC_STATIC_DISPLAY13, m_StaticDisplayCam13);
	DDX_Control(pDX, IDC_STATIC_DISPLAY12, m_StaticDisplayCam12);
	DDX_Control(pDX, IDC_STATIC_DISPLAY11, m_StaticDisplayCam11);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_2x3CamSwitchDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_2x3CamSwitchDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM, OnButtonTypeCam)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_2x3CamSwitchDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_2x3CamSwitchDlg *pMyClass;
DWORD dwMyCamera;
DWORD dwMyGroup;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pMyCamera;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;
ACQ_THREAD_PARAM *pMyParams;


    // Get my parameters

    pMyParams = (ACQ_THREAD_PARAM *)pContext;

    // A static function has no access to it's own class, need a ptr to it

    pMyClass    = pMyParams->pMyClass;
    dwMyCamera  = pMyParams->dwMyCameraIndex;

    if (dwMyCamera < 3)
    {
        dwMyGroup = 0;
    }
    else
    {
        dwMyGroup = 1;
    }

    // To alleviate the code, keep useful local variables

    pBrdMod             = pMyClass->m_pBrdMod;
    GrabID              = pMyClass->m_aGrabID[dwMyCamera];
    pMyCamera           = pMyClass->m_apCam[dwMyCamera];
    pImageConnect       = pMyClass->m_apImageConnection[dwMyCamera];

    while (pMyClass->m_abIsGrabbing[dwMyCamera])
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pMyCamera->GrabWaitFrameEx(GrabID, &pHostBuffer, IFC_WAIT_NEWER_FRAME,
                                              WAIT_ACQ_MAX_MSEC, TRUE);

        if (iSeqNum != -1)
        {
            // Statistics taken care by first camera of the 3-pack only

            if (dwMyCamera == 0)
            {
                pMyClass->m_MeasureFramePeriod.TagTime();
            }

            // Update the address associated with the image source to point
            // to the frame we just acquired

            pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

            // Display the  frame in our client window

            pImageConnect->Display();

            // Release the frame back into the active circular acquisition buffer

            pMyCamera->GrabRelease(GrabID, iSeqNum);

            // Put the former camera light OFF and this camera light ON 

            pMyClass->DrawCameraLightOff(pMyClass->m_dwLastGroup);
            pMyClass->DrawCameraLightOn(dwMyGroup);
            pMyClass->m_dwLastGroup = dwMyGroup;

            // Determine if another frame is to be expected

            if (pMyClass->m_bSnapping)
            {
                pMyClass->m_abIsGrabbing[dwMyCamera] = FALSE;       // Go out of this loop
            }

        }

        // Only one camera take care of the "Trigger To Image" events flags

        if ((dwMyCamera == 0) || (dwMyCamera == 3))
        {
            pMyClass->ReadAndClearEvents();
        }

    }

    // Return control to the calling thread
}





//------------------------------------------
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_2x3CamSwitchDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_2x3CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_bIsSOT_EventDetected = TRUE;

}

//------------------------------------------
//              ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ReadAndClearEvents() 
{
    m_bWasSOT_EventDetected     = m_bIsSOT_EventDetected;

    m_bIsSOT_EventDetected      = FALSE;
}



//------------------------------------------
//            OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::OnInitDialog()
{
DWORD dwCamIndex;


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

    // Hook a callback to some events in order to monitor the acquisition phases

    if (InitIFC_Callback() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC callback object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Allocate Host capture memory for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        if (AllocateCaptureMemory(dwCamIndex) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
            EndDialog(7);
            return FALSE;
        }
    }

    // Keep a ptr to all the Camera display windows

    m_apCamDisplay[0] = &m_StaticDisplayCam11;
    m_apCamDisplay[1] = &m_StaticDisplayCam12;
    m_apCamDisplay[2] = &m_StaticDisplayCam13;
    m_apCamDisplay[3] = &m_StaticDisplayCam21;
    m_apCamDisplay[4] = &m_StaticDisplayCam22;
    m_apCamDisplay[5] = &m_StaticDisplayCam23;

    // Initializes an IFC Image connection object for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apImageConnection[dwCamIndex] = InitIFC_ImageConnection(m_apCamDisplay[dwCamIndex], dwCamIndex);
        if (m_apImageConnection[dwCamIndex] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
            EndDialog(7);
            return FALSE;
        }
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

    // Start an acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apAcqThread[dwCamIndex] = new CThread;
        if (m_apAcqThread[dwCamIndex] == NULL)
        {
            AfxMessageBox(_T("Could not start the processing thread !!!"));
            EndDialog(7);
            return FALSE;
        }

        m_apAcqThread[dwCamIndex]->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
        m_apAcqThread[dwCamIndex]->CallThis(ThreadAcqProc);
    }

    return TRUE;  // return TRUE  unless you set the focus to a control

}

//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::InitIFC_Capture()
{
CICamera *pCam;
CAM_ATTR attrib;

    // First, try to find and use the default configuration file "p2vtest.txt"

    m_pBrdMod = (CPCVision2 *)IfxCreateCaptureModule("P2V", 0, "p2vtest.txt");       // Use PC2-Vision board # 0
    if (m_pBrdMod == NULL)
    {
        // Failed to find and use the default configuration file "p2vtest.txt"
        // Ask user to select a camera type

        m_pBrdMod = (CPCVision2 *)IfxCreateCaptureModule("P2V", 0);       // Use PC2-Vsion board # 0
        if (m_pBrdMod == NULL)
        {
            AfxMessageBox(_T("Can't find PC2Vision board in the system !!!"));
            return FALSE;
        }

        pCam = m_pBrdMod->GetCam(0);

        CCamSelDlg CamDlg(this, pCam);
        CamDlg.DoModal();

        // Keep selected camera type

        SetCamType(CamDlg.m_pszCurCamera);
    }
    else
    {
        // Keep connector 0

        pCam = m_pBrdMod->GetCam(0);
        pCam->GetAttr(&attrib);
        SetCamType(attrib.camName);
    }

    return TRUE;
}


//------------------------------------------
//         SetCamType
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::SetCamType(char *pszCamType)
{
CAM_ATTR attr;
DWORD dwCamIndex;



    // Get a CICamera object from all three port

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex] = m_pBrdMod->GetCam(dwCamIndex);
    }

    // Assign the selected camera type to all ports

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetCameraType(pszCamType);
    }

    // Tell IFC we are in three camera planar mode

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetAcqParam(P_PIXEL_COLOR, IFC_RGB_PLANAR);
    }

    // Show the selected camera type

    m_EditCamType.SetWindowText(pszCamType);

    // Keep attributes of camera zero

    m_apCam[0]->GetAttr(&attr);

    m_dwCamSizeX    = attr.dwWidth;
    m_dwCamSizeY    = attr.dwHeight;
    m_dwPixBitDepth = attr.dwBitsPerPixel;
    m_CamColor      = attr.color;
    m_dwImageSize   = m_dwCamSizeX * m_dwCamSizeY * attr.dwBytesPerPixel;

    // Determine if triggered mode is used

    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
    {
        m_bTriggerMode = TRUE;
    }

}





//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::InitIFC_Callback()
{

    // Want a callback on the TRIGGER EVENT detection

    m_pIntCallback_SOT = m_pBrdMod->CreateIntrCallback(P2V_INTR_SOT, MyCallback_SOT, this);

    if (m_pIntCallback_SOT == NULL)
        return FALSE;

    return TRUE;

}






//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_2x3CamSwitchDlg::InitIFC_ImageConnection(CStatic *pDisplayWindow, DWORD dwCamNumber)
{
CImgConn *ImgConn;
RECT recSize;
double dZoomX, dZoomY;
HWND hDisplayWnd;


    // Get some variable depending on the targeted camera

    hDisplayWnd = pDisplayWindow->GetSafeHwnd();

    // Create an ImgeConnection object and set-up the image scaling

    ImgConn = IfxCreateImgConn(m_apHostCapMemory[dwCamNumber], (WORD)m_dwCamSizeX,
                               (WORD)m_dwCamSizeY, (WORD)m_dwPixBitDepth, hDisplayWnd,
                                m_CamColor, IFC_DIB_SINK, NULL, ICAP_INTR_EOF);
    if (ImgConn)
    {
        CImgSink *imgSink = ImgConn->GetSink();
        pDisplayWindow->GetClientRect(&recSize);

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
void CIFC_PC2V_2x3CamSwitchDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

	delete m_pBrdMod;
	m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_SOT->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SOT);
    m_pIntCallback_SOT = NULL;

}






//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ReleaseIFC_ImageConnection(DWORD dwCamNumber)
{

    if (m_apImageConnection[dwCamNumber])
    {
        delete m_apImageConnection[dwCamNumber];
        m_apImageConnection[dwCamNumber] = NULL;
    }

}


//------------------------------------------
//          AllocateCaptureMemory
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::AllocateCaptureMemory(DWORD dwCamNumber)
{
DWORD dwAllocSize;


    dwAllocSize = m_dwImageSize * BUFFER_COUNT;

    if (dwAllocSize == 0)
        return FALSE;

    m_apHostCapMemory[dwCamNumber] = (BYTE *)malloc(dwAllocSize);
    if (m_apHostCapMemory[dwCamNumber] == NULL)
        return FALSE;

    m_aCapMemLockHandle[dwCamNumber] = m_pBrdMod->LockMem(m_apHostCapMemory[dwCamNumber], dwAllocSize);

    return TRUE;

}



//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ReleaseCaptureMemory(DWORD dwCamNumber)
{

    if (m_apHostCapMemory[dwCamNumber])
    {
        m_pBrdMod->UnLockMem(m_aCapMemLockHandle[dwCamNumber]);
        free(m_apHostCapMemory[dwCamNumber]);
    }

    m_apHostCapMemory[dwCamNumber] = NULL;

}



//------------------------------------------
//            OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnPaint() 
{
DWORD dwCamIndex;


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

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            m_apImageConnection[dwCamIndex]->Display();
        }

        if (m_bClearDisplay)
        {
            ClearDisplay();
        }

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            DrawWindowBorder(m_apCamDisplay[dwCamIndex]->GetSafeHwnd());
        }

        DrawCameraLightOff(0);
        DrawCameraLightOff(1);

        m_dwOnPaintCounter++;
    }
}




//------------------------------------------
//            OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_2x3CamSwitchDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ReleaseAll()
{
DWORD dwCamIndex;


    // Terminate the acquisition thread for all cameras

	for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
	{
		delete m_apAcqThread[dwCamIndex];
		m_apAcqThread[dwCamIndex] = NULL;
	}

    // Release the Host capture memory for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        ReleaseCaptureMemory(dwCamIndex);
    }

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        ReleaseIFC_ImageConnection(dwCamIndex);
    }

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    // Kill the Timers

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}


//------------------------------------------
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;
DWORD dwCamIndex;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        GetWindowPosition(m_apCamDisplay[dwCamIndex]->GetSafeHwnd(), &RectDraw);
        MyDC.Rectangle(&RectDraw);
    }

    MyDC.SelectObject(pOldBrush);
}




//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//          OnButtonTypeCam()
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonTypeCam() 
{
DWORD dwCamIndex;
CCamSelDlg CamDlg(this, m_apCam[0]);


    if (IsGrabbing())
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected camera type

        SetCamType(CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            ReleaseCaptureMemory(dwCamIndex);
        }

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            ReleaseIFC_ImageConnection(dwCamIndex);
        }

        // Allocate new host Capture Memory and Image Connection object

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            if (AllocateCaptureMemory(dwCamIndex) == FALSE)
            {
                AfxMessageBox(_T("Could not allocate capture memory !!!"));
            }
        }

        // Initializes an IFC Image connection object for all cameras

        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            m_apImageConnection[dwCamIndex] = InitIFC_ImageConnection(m_apCamDisplay[dwCamIndex], 0);
            if (m_apImageConnection[dwCamIndex] == NULL)
            {
                AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
            }
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;
    }

}




//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnClose() 
{
CString strWarnText;

    if (IsGrabbing())
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
void CIFC_PC2V_2x3CamSwitchDlg::OnTimer(UINT nIDEvent) 
{
DWORD dwCamIndex;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        if (m_bClearDisplay && ((m_dwGuiCounter & 0x0F) == 0))
        {
            ClearDisplay();

            for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
            {
                DrawWindowBorder(m_apCamDisplay[dwCamIndex]->GetSafeHwnd());
            }
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        UpdateButtons();                // Enable or not some buttons

        DrawEventLights();              // Show "Trigger TO Image" lights

        m_dwGuiCounter++;

        // Make sure a SNAP command ends correctly

        if (m_bSnapping)
        {
            if (! IsGrabbing())
            {
                m_pBrdMod->SwitchCameraFreeze();        // Normal SNAP end
                m_bSnapping = FALSE;
            }
            else if (++m_dwSnapPolling > WAIT_SNAP_MAX)     // SNAP not end, wait encore
            {
                OnButtonFreeze();
                AfxMessageBox(_T("The SNAP process did not work properly !!!"));
            }
        }

    }

    CDialog::OnTimer(nIDEvent);
}




//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::ShowStatistics() 
{
float fFrameRate;
float fFrameRateCeiling;
float fFrameRateFloor;
CString strToShow;


    if (! IsGrabbing())
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        m_EditFrameRateTotal.SetWindowText( _T("*****"));
    }
    else
    {
        // Compute and show acquisition frame rate

        fFrameRate = m_MeasureFramePeriod.GetTime();
        if (fFrameRate != 0.0)
        {

            // Compute and show Frame Rate per camera

            fFrameRate = (float)1.0 / fFrameRate;
            fFrameRateCeiling = (float)ceil(fFrameRate);
            fFrameRateFloor = (float)floor(fFrameRate);
            if ((fFrameRateCeiling - fFrameRate) <= 0.1)
            {
                fFrameRate = fFrameRateCeiling;
            }
            else if ((fFrameRate - fFrameRateFloor) <= 0.1)
            {
                fFrameRate = fFrameRateFloor;
            }

            strToShow.Format("%.2f", fFrameRate);
            m_EditFrameRate.SetWindowText(strToShow);

            // Compute and show Frame Rate total

            fFrameRate *= 2.0;
            fFrameRateCeiling = (float)ceil(fFrameRate);
            fFrameRateFloor = (float)floor(fFrameRate);
            if ((fFrameRateCeiling - fFrameRate) <= 0.1)
            {
                fFrameRate = fFrameRateCeiling;
            }
            else if ((fFrameRate - fFrameRateFloor) <= 0.1)
            {
                fFrameRate = fFrameRateFloor;
            }

            strToShow.Format("%.2f", fFrameRate);
            m_EditFrameRateTotal.SetWindowText(strToShow);
        }
    }

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::UpdateButtons()
{
BOOL bIsGrabbing;


    bIsGrabbing = IsGrabbing();

    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! bIsGrabbing);
    m_ButtonSnap.EnableWindow(! bIsGrabbing);
    m_ButtonFreeze.EnableWindow(bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && bIsGrabbing);

    m_ButtonCamType.EnableWindow(! bIsGrabbing);

}





//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonGrab() 
{
int dwCamIndex;


    // Determine if triggered mode is used at least on one camera group

    m_bTriggerMode = FALSE;
    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        if (m_apCam[dwCamIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
        {
            m_bTriggerMode = TRUE;
        }
    }

    // Define the grab Sequence for IFC

    m_bClearDisplay = FALSE;

    m_pBrdMod->SwitchCameraDefineStart();

    // Define Group 1

    for (dwCamIndex = 2; dwCamIndex >= 0; dwCamIndex--)
    {
        m_aGrabID[dwCamIndex] = m_apCam[dwCamIndex]->Grab(IFC_GOPT_PLANAR_INIT,
                                                          m_apHostCapMemory[dwCamIndex],
                                                          BUFFER_COUNT);

        m_abIsGrabbing[dwCamIndex] = TRUE;
    }

    // Define Group 2

    for (dwCamIndex = CAMERA_COUNT-1; dwCamIndex >= 3; dwCamIndex--)
    {
        m_aGrabID[dwCamIndex] = m_apCam[dwCamIndex]->Grab(IFC_GOPT_PLANAR_INIT,
                                                          m_apHostCapMemory[dwCamIndex],
                                                          BUFFER_COUNT);

        m_abIsGrabbing[dwCamIndex] = TRUE;
    }

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the GRAB

    m_pBrdMod->SwitchCameraGrab();

    // Start the acquisition threads

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_aAcqThreadParams[dwCamIndex].pMyClass = this;
        m_aAcqThreadParams[dwCamIndex].dwMyCameraIndex = dwCamIndex;

        m_apAcqThread[dwCamIndex]->AwakeThread(&m_aAcqThreadParams[dwCamIndex]);
    }

}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonSnap() 
{
int dwCamIndex;


    // Determine if triggered mode is used at least on one camera group

    m_bTriggerMode = FALSE;
    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        if (m_apCam[dwCamIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
        {
            m_bTriggerMode = TRUE;
        }
    }

    // Define the grab Sequence for IFC

    m_bClearDisplay = FALSE;

    m_pBrdMod->SwitchCameraDefineStart();

    // Define Group 1

    for (dwCamIndex = 2; dwCamIndex >= 0; dwCamIndex--)
    {
        m_aGrabID[dwCamIndex] = m_apCam[dwCamIndex]->Grab(IFC_GOPT_PLANAR_INIT,
                                                          m_apHostCapMemory[dwCamIndex],
                                                          BUFFER_COUNT);

        m_abIsGrabbing[dwCamIndex] = TRUE;
    }

    // Define Group 2

    for (dwCamIndex = CAMERA_COUNT-1; dwCamIndex >= 3; dwCamIndex--)
    {
        m_aGrabID[dwCamIndex] = m_apCam[dwCamIndex]->Grab(IFC_GOPT_PLANAR_INIT,
                                                          m_apHostCapMemory[dwCamIndex],
                                                          BUFFER_COUNT);

        m_abIsGrabbing[dwCamIndex] = TRUE;
    }

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the SNAP (note that the GUI timer will end the snap process)

    m_dwSnapPolling = 0;
    m_bSnapping     = TRUE;
    m_pBrdMod->SwitchCameraSnap(2);

    // Start the acquisition threads

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_aAcqThreadParams[dwCamIndex].pMyClass = this;
        m_aAcqThreadParams[dwCamIndex].dwMyCameraIndex = dwCamIndex;

        m_apAcqThread[dwCamIndex]->AwakeThread(&m_aAcqThreadParams[dwCamIndex]);
    }

}






//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonFreeze() 
{
DWORD dwCamIndex;


    m_pBrdMod->SwitchCameraFreeze();

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_abIsGrabbing[dwCamIndex] = FALSE;
    }

    DrawCameraLightOff(0);
    DrawCameraLightOff(1);

}


//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonTrigger() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;
DWORD dwCamIndex;



    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[0]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd
        m_apCam[dwCamIndex]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command
    }

    // Raise the flag indicating that the SOT event occured

    m_bIsSOT_EventDetected = TRUE;

    if (bTriggerSrcWasExternal)
    {
        for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT; dwCamIndex++)
        {
            m_apCam[dwCamIndex]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
        }
    }

}




//------------------------------------------
//          IsGrabbing()
//------------------------------------------
BOOL CIFC_PC2V_2x3CamSwitchDlg::IsGrabbing() 
{
DWORD dwCamIndex;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_COUNT ; dwCamIndex++)
    {
        if (m_abIsGrabbing[dwCamIndex])
        {
            return TRUE;
        }
    }

    return FALSE;

}





//------------------------------------------
//              DrawEventLights
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawEventLights() 
{
static BOOL bToggler;


    // Event detection indicators

    if (IsGrabbing())
    {
        // Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            DrawEventDetected(m_StaticSOTLight.m_hWnd);         // Trigger detected
        }
        else if (! m_bTriggerMode)
        {
            EraseEventDetected(m_StaticSOTLight.m_hWnd);        // No trigger mode used
        }
        else if (bToggler)
        {
            DrawEventNotDetected(m_StaticSOTLight.m_hWnd);      // Warning flashing
        }
        else
        {
            EraseEventDetected(m_StaticSOTLight.m_hWnd);        // Warning flashing
        }
    }
    else
    {
        EraseEventDetected(m_StaticSOTLight.m_hWnd);
    }

    bToggler = ! bToggler;

}




//------------------------------------------
//          DrawEventDetected()
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawEventDetected(HWND hWnd)
{
CClientDC MyDC(this);
CBrush MyGreenBrush (RGB(0,0xFF,0));       // Green Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;


    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyGreenBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw a GREEN rectangle

    GetWindowPosition(hWnd, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}





//------------------------------------------
//          DrawEventNotDetected()
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawEventNotDetected(HWND hWnd)
{
CClientDC MyDC(this);
CBrush MyYellowBrush (RGB(0xFF,0xFF,0));       // Yellow Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;


    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyYellowBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw a YELLOW rectangle

    GetWindowPosition(hWnd, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}


//------------------------------------------
//          DrawCameraLightOn()
//------------------------------------------
// Draw a RED rectangle below the camera
// window to show it is selected
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawCameraLightOn(DWORD dwConnIndex)
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    if (dwConnIndex == 0)
    {
        hWindowLight = m_StaticLightGroup1.m_hWnd;
    }
    else
    {
        hWindowLight = m_StaticLightGroup2.m_hWnd;
    }

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyRedBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in RED camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}




//------------------------------------------
//          DrawCameraLightOff()
//------------------------------------------
// Draw a BLACK rectangle below the camera
// window to show it is NOT selected
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawCameraLightOff(DWORD dwConnIndex)
{
CClientDC MyDC(this);
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    if (dwConnIndex == 0)
    {
        hWindowLight = m_StaticLightGroup1.m_hWnd;
    }
    else
    {
        hWindowLight = m_StaticLightGroup2.m_hWnd;
    }

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in BLACK camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}


//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::DrawWindowBorder(HWND hWnd)
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
//          EraseEventDetected()
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::EraseEventDetected(HWND hWnd)
{
CClientDC MyDC(this);
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;


    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw a BLACK rectangle

    GetWindowPosition(hWnd, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}


//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_2x3CamSwitchDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}

