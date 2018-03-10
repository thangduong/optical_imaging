//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ThreadProcDlg.cpp
//
//  BIRTH DATE:     December 2002
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC V5.8
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Acquisition/Processing/Displaying using a thread for
//                  acquisition and another thread for processing and display.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "IFC_PC2V_ThreadProc.h"
#include "IFC_PC2V_ThreadProcDlg.h"
#include "CamSelDlg.h"                      // Cam Selector Dialog Box


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2V_ThreadProcDlg::CIFC_PC2V_ThreadProcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_ThreadProcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_ThreadProcDlg)
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
    m_dwImageSize       = 0;

    m_dwFrameCounter    = 0;
    m_fProcTime         = 0.0;

    m_pAcquisitionThread = NULL;
    m_pProcessingThread = NULL;

}




void CIFC_PC2V_ThreadProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_ThreadProcDlg)
	DDX_Control(pDX, IDC_EDIT_NA, m_EditFrameNotAcquired);
	DDX_Control(pDX, IDC_EDIT_NP, m_EditFrameNotProcessed);
	DDX_Control(pDX, IDC_STATIC_OVL_LIGHT, m_Static_OVL_Light);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_LF, m_EditFrameLost);
	DDX_Control(pDX, IDC_EDIT_PROC_TIME, m_EditProcTime);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_ThreadProcDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_ThreadProcDlg)
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
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_ThreadProcDlg::OnInitDialog()
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

    // Hook a callback to some events in order to monitor the acquisition phases

    if (InitIFC_Callback() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC callback object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Allocate Host capture memory

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate capture memory !!!"));
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

    // Create the acquisition thread

    m_pAcquisitionThread = new CThread;
    if (m_pAcquisitionThread == NULL)
    {
        AfxMessageBox(_T("Could not start the acquisition thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pAcquisitionThread->SetPriority(THREAD_PRIORITY_NORMAL);
    m_pAcquisitionThread->CallThis(ThreadAcqFunc);

    // Create the Processing Thread

    m_pProcessingThread = new CThread;
    if (m_pProcessingThread == NULL)
    {
        AfxMessageBox(_T("Could not start the processing thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pProcessingThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pProcessingThread->CallThis(ThreadProcFunc);

    m_bAppClosing = FALSE;

    return TRUE;  // return TRUE  unless you set the focus to a control

}



//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_ThreadProcDlg::InitIFC_Capture()
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
BOOL CIFC_PC2V_ThreadProcDlg::InitIFC_Callback()
{

    // Want a callback on the SKIPPED FIELD

    m_pIntCallback_SKF = m_pBrdMod->CreateIntrCallback(P2V_INTR_SKIPPED_FIELD, MyCallback_SKF, this);

    if (m_pIntCallback_SKF == NULL)
        return FALSE;


    return TRUE;

}


//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_SKF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SKF);
    m_pIntCallback_SKF = NULL;

}







//------------------------------------------
//          AllocateCaptureMemory
//------------------------------------------
BOOL CIFC_PC2V_ThreadProcDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    dwAllocSize = m_dwImageSize * BUFFER_COUNT;
    if (dwAllocSize == 0)
        return FALSE;

    m_pHostCapMemory = (BYTE *)malloc(dwAllocSize);
    if (m_pHostCapMemory == NULL)
        return FALSE;

    m_CapMemLockHandle = m_pBrdMod->LockMem(m_pHostCapMemory, dwAllocSize);

    return TRUE;
}




//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ReleaseCaptureMemory()
{

    if (m_pHostCapMemory)
    {
        m_pBrdMod->UnLockMem(m_CapMemLockHandle);
        free(m_pHostCapMemory);
    }

    m_pHostCapMemory = NULL;

}





//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_ThreadProcDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
{
CImgConn *ImgConn;


    ImgConn = IfxCreateImgConn(m_pHostCapMemory, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY,
                                (WORD)m_dwPixBitDepth, hWnd, m_CamColor, IFC_DIB_SINK,
                                 NULL, ICAP_INTR_EOF);

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
void CIFC_PC2V_ThreadProcDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ReleaseIFC_ImageConnection()
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
void CIFC_PC2V_ThreadProcDlg::OnPaint() 
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
HCURSOR CIFC_PC2V_ThreadProcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ReleaseAll()
{

    // Terminate the processing thread

    delete m_pProcessingThread;
    m_pProcessingThread = NULL;

    // Terminate the acquisition thread

    delete m_pAcquisitionThread;
    m_pAcquisitionThread = NULL;

    // Release the Host capture memory

    ReleaseCaptureMemory();

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
void CIFC_PC2V_ThreadProcDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
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
    m_dwPixBitDepth = attr.dwBitsPerPixel;
    m_CamColor      = attr.color;
    m_dwImageSize   = m_dwCamSizeX * m_dwCamSizeY * attr.dwBytesPerPixel;;

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
void CIFC_PC2V_ThreadProcDlg::ClearDisplay()
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
BOOL CIFC_PC2V_ThreadProcDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_ThreadProcDlg::OnButtonCam() 
{
CCamSelDlg CamDlg(this, m_pCam);

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory();

        ReleaseIFC_ImageConnection();

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

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
void CIFC_PC2V_ThreadProcDlg::OnButtonFreeze() 
{

    m_bIsGrabbing = FALSE;

    m_pCam->Freeze();

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::OnButtonGrab() 
{

    m_dwFrameCounter                = 0;
    m_dwFrameMissedCounter          = 0;
    m_dwSkippedFieldCounter         = 0;
    m_dwFrameNotProcessedCounter    = 0;
    m_fProcTime                     = 0.0;

    m_bClearDisplay     = FALSE;
    m_bSystemOverload   = FALSE;

    m_GrabID = m_pCam->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_pHostCapMemory,
                             BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_bIsGrabbing = TRUE;
    m_pAcquisitionThread->AwakeThread(this);

}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay = FALSE;

    m_pCam->Snap(m_pHostCapMemory, 0, 0, 0, 0);

    // Apply some processing to the image

    ProcImageFunction(m_pHostCapMemory, 0, m_dwCamSizeX, m_dwCamSizeY);

    // Increment and show frame counter

    m_dwFrameCounter++;
    strToShow.Format("%d", m_dwFrameCounter);
    m_EditFrameCount.SetWindowText(strToShow);

    // Show frame on the screen

    m_pImageConnection->GetSrc()->SetBufferAddr(m_pHostCapMemory);
    m_pImageConnection->Display();

}



//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::OnClose() 
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
void CIFC_PC2V_ThreadProcDlg::OnTimer(UINT nIDEvent) 
{


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
void CIFC_PC2V_ThreadProcDlg::ShowStatistics() 
{
float fRate;
CString strToShow;
IFC_GRAB_STATS GrabStats;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        DrawRectangleLight(m_Static_OVL_Light.m_hWnd, RGB(0, 0, 0), FALSE, strToShow);
        return;
    }

    // Compute and show acquisition frame rate

    fRate = m_MeasureAcqRate.GetTime();
    if (fRate != 0.0)
    {
        fRate = (float)1.0 / fRate;
        strToShow.Format("%.2f", fRate);
        m_EditFrameRate.SetWindowText(strToShow);
    }
    else
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
    }

    // Show lost frame count

    m_pBrdMod->GetGrabStats(m_GrabID, &GrabStats);

    strToShow.Format("%d", GrabStats.NumberOfFramesLost);
    m_EditFrameLost.SetWindowText(strToShow);

    // Show processing time

    strToShow.Format("%.2f ms", m_fProcTime);
    m_EditProcTime.SetWindowText(strToShow);

    // Show not acquired frame count

    strToShow.Format("%d", m_dwSkippedFieldCounter);
    m_EditFrameNotAcquired.SetWindowText(strToShow);

    // Show not processed frame count

    strToShow.Format("%d", m_dwFrameNotProcessedCounter);
    m_EditFrameNotProcessed.SetWindowText(strToShow);

    // Show red light if system is overloaded

    if (m_bSystemOverload)
    {
        strToShow = _T("System Overload");
        DrawRectangleLight(m_Static_OVL_Light.m_hWnd, RGB(0xFF, 0, 0), TRUE, strToShow);
        m_bSystemOverload = FALSE;
    }
    else
    {
        strToShow = _T("System OK");
        DrawRectangleLight(m_Static_OVL_Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strToShow);
    }

}








//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}




//------------------------------------------
//              ThreadAcqFunc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadProcDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ThreadAcqFunc(void *pContext) 
{
CIFC_PC2V_ThreadProcDlg *pMyClass;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pCam;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;
DWORD dwErrorCode;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadProcDlg *)pContext;   // Context is the ptr to my class

    if (pMyClass == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // To alleviate the code, keep useful local variables

    GrabID              = pMyClass->m_GrabID;
    pCam                = pMyClass->m_pCam;
    pBrdMod             = pMyClass->m_pBrdMod;
    pImageConnect       = pMyClass->m_pImageConnection;

    while (pMyClass->m_bIsGrabbing)
    {

        // Wait a frame ready in Host capture memory

        iSeqNum = pCam->GrabWaitFrameEx(GrabID, &pHostBuffer,
                                         IFC_WAIT_NEWER_FRAME, WAIT_ACQ_MAX_MSEC, TRUE);

        if ((iSeqNum == -1) && pMyClass->m_bIsGrabbing)
        {
            dwErrorCode = pMyClass->m_pBrdMod->GetLastError();
            if (dwErrorCode == IFC_ERROR_MEMLOCK_FAIL)
            {
                AfxMessageBox(_T("Could not snap an image !!!"));
            }
            AfxMessageBox(_T("Could not acquire an image !!!"));
            pMyClass->m_pCam->Freeze();
            pMyClass->m_bIsGrabbing = FALSE;
        }
        else if (iSeqNum != -1)
        {
            pMyClass->m_MeasureAcqRate.TagTime();       // Measure the acq rate

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

            // If processing queue can absorb another buffer,
            //  insert it and awake the processing thread
            // otherwise, release the buffer immediately (will never be processed)

            pMyClass->m_csProcList.Lock();                  // Get exclusive access to the processing buffer queue
            if (pMyClass->m_BufToProcList.GetCount() <= PROC_QUEUE_WATERMARK)
            {
                    pMyClass->m_aThreadProcParam[iSeqNum].pTheBuffer    = pHostBuffer;
                    pMyClass->m_aThreadProcParam[iSeqNum].GrabID        = GrabID;
                    pMyClass->m_aThreadProcParam[iSeqNum].iBufferIndex  = iSeqNum;

                    pMyClass->m_BufToProcList.AddHead(&pMyClass->m_aThreadProcParam[iSeqNum]);

                    pMyClass->m_pProcessingThread->AwakeThread(pMyClass);
            }
            else
            {
                // Release the acquisition buffer back into the ring

                pMyClass->m_pCam->GrabRelease(GrabID, iSeqNum);
                pMyClass->m_bSystemOverload = TRUE;
                pMyClass->m_dwFrameNotProcessedCounter++;
            }
            pMyClass->m_csProcList.Unlock();                  // Release access to the processing buffer queue

        }
    }

    // Return control to the calling thread

}




//------------------------------------------
//              MyCallback_SKF
//------------------------------------------
// Function called when the "SKIPPED FIELD"
// event occurs
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::MyCallback_SKF(void *pContext)
{
CIFC_PC2V_ThreadProcDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadProcDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    pMyClass->m_dwSkippedFieldCounter++;

}






//------------------------------------------
//              ThreadProcFunc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadProcDlg).
//
// Will process as many buffers waiting in the queue as it can.
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ThreadProcFunc(void *pContext) 
{
CIFC_PC2V_ThreadProcDlg *pMyClass;
PROC_THREAD_PARAM *pTheProcThreadParams;
int iBufferCountPending;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadProcDlg *)pContext;

    // While there is buffer to process in the queue

    pMyClass->m_csProcList.Lock();
    iBufferCountPending = pMyClass->m_BufToProcList.GetCount();
    pMyClass->m_csProcList.Unlock();

    while (iBufferCountPending > 0)
    {
        // Get a buffer to process from the queue

        pMyClass->m_csProcList.Lock();              // Get exclusive access to the processing buffer queue
        pTheProcThreadParams = (PROC_THREAD_PARAM *)pMyClass->m_BufToProcList.RemoveTail();
        pMyClass->m_csProcList.Unlock();            // Release access to the processing buffer queue

        // Apply some processing to the image

        pMyClass->m_MeasureProcTime.StartTime();

        pMyClass->ProcImageFunction(pTheProcThreadParams->pTheBuffer, pTheProcThreadParams->iBufferIndex,
                            pMyClass->m_dwCamSizeX, pMyClass->m_dwCamSizeY);

        pMyClass->m_MeasureProcTime.StopTime();
        pMyClass->m_fProcTime = pMyClass->m_MeasureProcTime.GetTimeMilli();

        // Update the address associated with the image source to point
        // to the frame we just acquired

        pMyClass->m_pImageConnection->GetSrc()->SetBufferAddr(pTheProcThreadParams->pTheBuffer);

        // Display the  frame in our client window

        pMyClass->m_pImageConnection->Display();

        // Release the acquisition buffer back into the ring

        pMyClass->m_pCam->GrabRelease(pTheProcThreadParams->GrabID, pTheProcThreadParams->iBufferIndex);

        // Look if there is more buffer queued for processing

        pMyClass->m_csProcList.Lock();
        iBufferCountPending = pMyClass->m_BufToProcList.GetCount();
        pMyClass->m_csProcList.Unlock();
    }

    // Return control to the calling thread

}




//------------------------------------------
//              ProcImageFunction
//------------------------------------------
// Apply a thresholding, then draw a white
// block positioned according to buffer index.
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::ProcImageFunction(BYTE *pImageBuffer, DWORD dwBufferIndex,
                                                DWORD dwImageSizeX, DWORD dwImageSizeY)
{
BYTE *pHostBufferProc;
DWORD nLine;
DWORD nPixel;


    // Apply a thresholding to each pixel of the image

    pHostBufferProc = pImageBuffer;

    for (nLine = 0; nLine < dwImageSizeY; nLine++)
    {
        for (nPixel = 0; nPixel < dwImageSizeX; nPixel++)
        {
            if (*pHostBufferProc < 75)
                *pHostBufferProc = 0;
            else if (*pHostBufferProc > 175)
                *pHostBufferProc = 0xFF;

            pHostBufferProc++;
        }
    }

    // Then draw a 30x30 white block in image left edge proportional to buffer index

    if (((30 * dwBufferIndex) + 30) < dwImageSizeY)     // Don't go beyond image floor
    {
        for (nLine = 0; nLine < 30; nLine++)
        {
            pHostBufferProc = pImageBuffer;
            pHostBufferProc += (30 * dwImageSizeX * dwBufferIndex);
            pHostBufferProc += (nLine * dwImageSizeX);

            for (nPixel = 0; nPixel < 30; nPixel++)
            {
                *pHostBufferProc = 0xFF;
                pHostBufferProc++;
            }
        }
    }

}


//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::DrawWindowBorder(HWND hWnd)
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
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
{
CClientDC MyDC(this);
CBrush MyNewBrush (TheColor);       // Interior filling with passed color
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
RECT RectSize;
CSize TextSize;
int iTextOffsetX, iTextOffsetY;


    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyNewBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw a colored rectangle

    GetWindowPosition(hWnd, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);

    // Draw a text message in the middle of the rectangle

    if (bDrawText)
    {
        ::GetClientRect(hWnd, &RectSize);                   // Size of the rectangle in pixel
        TextSize = MyDC.GetTextExtent(strTheText);          // Size of the text in pixel

        MyDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
        MyDC.SetTextColor(RGB(0, 0, 0));

        iTextOffsetX = (RectSize.right - TextSize.cx) / 2;
        iTextOffsetY = (RectSize.bottom - TextSize.cy) / 2;
        MyDC.TextOut(RectDraw.left + iTextOffsetX, RectDraw.top + iTextOffsetY, strTheText, strTheText.GetLength());
    }

    MyDC.SelectObject(pOldPen);

}



//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_ThreadProcDlg::OnButtonTrigger() 
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
void CIFC_PC2V_ThreadProcDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}


