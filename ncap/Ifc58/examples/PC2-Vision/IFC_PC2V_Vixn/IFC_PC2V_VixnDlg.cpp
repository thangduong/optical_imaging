//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_VixnDlg.cpp
//
//  BIRTH DATE:     December 2003
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
//                  This demo shows how fast and constant a VIXN interrupt
//                  callback is by comparing graphically the response time
//                  jitter of both a VIXN and a regular callback.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "vixni.h"                          // IFC related
#include "MyVixn.h"                         // My Vixn derived class

#include "CamSelDlg.h"                      // Cam Selector Dialog Box

#include "IFC_PC2V_Vixn.h"
#include "IFC_PC2V_VixnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_VixnDlg::CIFC_PC2V_VixnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_VixnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_VixnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pCam              = NULL;
    m_pImageConnection  = NULL;
    m_GrabID            = NULL;

    m_pIntCallback_EOF  = NULL;

    m_bIsGrabbing       = FALSE;
    m_bAppClosing       = FALSE;
    m_bSystemOverload   = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwImageSize       = 0;

    m_dwFrameCounter        = 0;
    m_dwJitterArrayIndex    = 0;

    m_pAcqThread        = NULL;
    m_pHostCapMemory    = NULL;
    m_pDisplayThread    = NULL;

    m_dwEOF_EventCounter    = 0;

    m_bWasEOF_EventDetected = FALSE;

}



//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_VixnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_VixnDlg)
	DDX_Control(pDX, IDC_STATIC_VIXN_JITTER, m_StaticVixnCursor);
	DDX_Control(pDX, IDC_STATIC_CB_JITTER, m_StaticNonVixnCursor);
	DDX_Control(pDX, IDC_EDIT_VIXN_JITTER, m_EditVixnJitter);
	DDX_Control(pDX, IDC_EDIT_NON_VIXN_JITTER, m_EditNonVixnJitter);
	DDX_Control(pDX, IDC_EDIT_VFC, m_EditVixnFrameCount);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	DDX_Control(pDX, IDC_EDIT_FL, m_EditFrameLost);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_VixnDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_VixnDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the processing thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadTrigDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_VixnDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_VixnDlg *pMyClass;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pCam;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;
IFC_GRAB_STATS GrabStats;
double dThisFrameTime;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_VixnDlg *)pContext;   // Context is the ptr to my class

    // To alleviate the code, keep useful local variables

    GrabID              = pMyClass->m_GrabID;
    pCam                = pMyClass->m_pCam;
    pBrdMod             = pMyClass->m_pBrdMod;
    pImageConnect       = pMyClass->m_pImageConnection;

    while (pMyClass->m_bIsGrabbing)
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pCam->GrabWaitFrameEx(GrabID, &pHostBuffer, IFC_WAIT_NEWER_FRAME,
                                         WAIT_ACQ_MAX_MSEC, TRUE);

        // Read the "Trigger To Image" events flags

        pMyClass->ReadAndClearEvents();

        if (iSeqNum != -1)
        {
            // Compute frame period

            dThisFrameTime                  = CIFCOS::GetSystimeMicrosecs();
            pMyClass->m_dLastFramePeriod    = pMyClass->m_dFramePeriod;
            pMyClass->m_dFramePeriod        = dThisFrameTime - pMyClass->m_dLastFrameTime;
            pMyClass->m_dLastFrameTime      = dThisFrameTime;

            // Compute frame period jitter average

            pMyClass->ComputeAverageFramePeriodJitter();

            // Show lost frame count

            pMyClass->m_pBrdMod->GetGrabStats(GrabID, &GrabStats);

            strToShow.Format("%d", GrabStats.NumberOfFramesLost);
            pMyClass->m_EditFrameLost.SetWindowText(strToShow);

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

            // Get and show frame counter from the VIXN object

            strToShow.Format("%d", pMyClass->m_pMyVixn->GetFrameInterruptCount());
            pMyClass->m_EditVixnFrameCount.SetWindowText(strToShow);

            // If the last buffer is not waiting to be displayed,
            //  flag it to be displayed otherwise, release the buffer
            //   immediately (will never be displayed)

            if (pMyClass->m_DispThreadParams.bBusy == FALSE)
            {
                pMyClass->m_DispThreadParams.pTheBuffer     = pHostBuffer;
                pMyClass->m_DispThreadParams.GrabID         = GrabID;
                pMyClass->m_DispThreadParams.iBufferIndex   = iSeqNum;
                pMyClass->m_DispThreadParams.bBusy          = TRUE;

                pMyClass->m_bSystemOverload = FALSE;
            }
            else
            {
                // Release the acquisition buffer back into the ring

                pMyClass->m_pCam->GrabRelease(GrabID, iSeqNum);

                pMyClass->m_bSystemOverload = TRUE;

            }

            //  Wake-up the Display thread

            pMyClass->m_pDisplayThread->AwakeThread(pMyClass);

        }

    }

    // Return control to the calling thread
}




//------------------------------------------
//              ThreadDisplayProc
//------------------------------------------
// Called by the display thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadTrigDlg).
//------------------------------------------
void CIFC_PC2V_VixnDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_VixnDlg   *pMyClass;
CImgConn            *pImageConnect;
int                 iSeqNum;
HIFCGRAB            GrabID;
BYTE                *pHostBuffer;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_VixnDlg *)pContext;

    // Is buffer ready to be to displayed ?

    if (pMyClass->m_DispThreadParams.bBusy == TRUE)
    {
        // Get the information associated with the buffer and channel to display

        iSeqNum         = pMyClass->m_DispThreadParams.iBufferIndex;
        pHostBuffer     = pMyClass->m_DispThreadParams.pTheBuffer;
        GrabID          = pMyClass->m_DispThreadParams.GrabID;

        // Get the ImageConnection object associated with this camera

        pImageConnect = pMyClass->m_pImageConnection;

        // Update the address associated with the image source to point
        // to the frame we just acquired

        pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

        // Display the  frame in our client window

        pImageConnect->Display();

        // Release the frame back into the active circular acquisition buffer

        pMyClass->m_pCam->GrabRelease(GrabID, iSeqNum);

        // Flag the buffer as displayed

        pMyClass->m_DispThreadParams.bBusy = FALSE;

    }

    // Return control to the calling thread
}


//------------------------------------------
//              MyCallback_EOF
//------------------------------------------
// Function called when the "End of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_VixnDlg::MyCallback_EOF(void *pContext)
{
CIFC_PC2V_VixnDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_VixnDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Increment the counter indicating that the event occured

    pMyClass->m_dwEOF_EventCounter++;

}



//------------------------------------------------------
//            ComputeAverageFramePeriodJitter
//------------------------------------------------------
void CIFC_PC2V_VixnDlg::ComputeAverageFramePeriodJitter()
{
double dVixnFramePeriod;
double dVixnLastFramePeriod;
double dVixnJitter;
double dNonVixnJitter;
CString strToShow;
DWORD dwArrayScan;


    //----------------------------
    // Compute VIXN period jitter

    dVixnFramePeriod        = (double)m_pMyVixn->GetFrameInterruptPeriod();
    dVixnLastFramePeriod    = (double)m_pMyVixn->GetFrameInterruptLastPeriod();
    dVixnJitter             = fabs(dVixnFramePeriod - dVixnLastFramePeriod);

    // Insert it in the averaging array if it's valid

    if ((dVixnLastFramePeriod != 0.0) && (dVixnJitter < 2000000.0))
    {
        m_adVixnJitter[m_dwJitterArrayIndex] = dVixnJitter;
    }
    else
    {
        return;
    }

    // Compute it's period jitter average

    dVixnJitter = m_adVixnJitter[0];
    for (dwArrayScan = 1; dwArrayScan < JITTER_AVERAGE_COUNT; dwArrayScan++)
    {
        dVixnJitter += m_adVixnJitter[dwArrayScan];
    }
    m_dVixnAverageJitter = dVixnJitter / JITTER_AVERAGE_COUNT;

    //--------------------------------------------
    // Compute regular EOF callback period jitter

    dNonVixnJitter  = fabs(m_dFramePeriod - m_dLastFramePeriod);

    // Insert it in the averaging array if it's valid

    if ((m_dLastFramePeriod != 0.0) && (dNonVixnJitter < 2000000.0))
    {
        m_adNonVixnJitter[m_dwJitterArrayIndex] = dNonVixnJitter;
    }
    else
    {
        return;
    }

    // Compute it's period jitter average

    dNonVixnJitter = m_adNonVixnJitter[0];
    for (dwArrayScan = 1; dwArrayScan < JITTER_AVERAGE_COUNT; dwArrayScan++)
    {
        dNonVixnJitter += m_adNonVixnJitter[dwArrayScan];
    }
    m_dNonVixnAverageJitter = dNonVixnJitter / JITTER_AVERAGE_COUNT;

    //--------------------------------------------------------
    // Adjust circular indexing in the jitter averaging arrays

    m_dwJitterArrayIndex++;
    m_dwJitterArrayIndex %= JITTER_AVERAGE_COUNT;

}




//------------------------------------------
//            ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_VixnDlg::ReadAndClearEvents()
{

    if (m_dwEOF_EventCounter > 0)
    {
        m_dwEOF_EventCounter--;
        m_bWasEOF_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOF_EventDetected = FALSE;
    }


}




//------------------------------------------
//            OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_VixnDlg::OnInitDialog()
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

    // Create a Vixn derived class

    m_pMyVixn = new CMyVixn(m_pBrdMod);
    if (m_pMyVixn == NULL)
    {
        AfxMessageBox(_T("Could not instantiate a Vixn object !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pMyVixn->Create();

    // Create the acquisition thread

    m_pAcqThread = new CThread;
    if (m_pAcqThread == NULL)
    {
        AfxMessageBox(_T("Could not start the acquisition thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pAcqThread->SetPriority(THREAD_PRIORITY_NORMAL);
    m_pAcqThread->CallThis(ThreadAcqProc);

    // Create a display thread

    m_pDisplayThread = new CThread;
    if (m_pDisplayThread == NULL)
    {
        AfxMessageBox(_T("Could not start the display thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pDisplayThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pDisplayThread->CallThis(ThreadDisplayProc);

    return TRUE;  // return TRUE  unless you set the focus to a control

}


//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_VixnDlg::InitIFC_Capture()
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
BOOL CIFC_PC2V_VixnDlg::InitIFC_Callback()
{

    // Want a callback on the END OF FRAME

    m_pIntCallback_EOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_EOFRM, MyCallback_EOF, this);

    if (m_pIntCallback_EOF == NULL)
        return FALSE;

    return TRUE;

}





//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_VixnDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
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
void CIFC_PC2V_VixnDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_VixnDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_EOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOF);
    m_pIntCallback_EOF = NULL;

}





//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_VixnDlg::ReleaseIFC_ImageConnection()
{

    if (m_pImageConnection)
    {
        delete m_pImageConnection;
        m_pImageConnection = NULL;
    }

}


//------------------------------------------
//          AllocateCaptureMemory
//------------------------------------------
BOOL CIFC_PC2V_VixnDlg::AllocateCaptureMemory()
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
void CIFC_PC2V_VixnDlg::ReleaseCaptureMemory()
{

    if (m_pHostCapMemory)
    {
        m_pBrdMod->UnLockMem(m_CapMemLockHandle);
        free(m_pHostCapMemory);
    }

    m_pHostCapMemory = NULL;

}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_VixnDlg::ReleaseAll()
{

    // Terminate the display thread

    delete m_pDisplayThread;
    m_pDisplayThread = NULL;

    // Terminate the acquisition thread

    if (m_pAcqThread)
    {
        delete m_pAcqThread;
        m_pAcqThread = NULL;
    }

    // Release the Host capture memory

    ReleaseCaptureMemory();

    // Release the Host capture memory
    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    // Release the Vixn object

    delete m_pMyVixn;
    m_pMyVixn = NULL;

    // Kill the Timers

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_VixnDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Show active port

    strToShow.Format("%d", dwActivePort + 1);
    m_EditCurrentPort.SetWindowText(strToShow);
    m_dwActivePort = dwActivePort;

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
void CIFC_PC2V_VixnDlg::ClearDisplay()
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
BOOL CIFC_PC2V_VixnDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_VixnDlg::ShowStatistics() 
{
double dFrameRate;
CString strToShow;
IFC_GRAB_STATS GrabStats;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        return;
    }

    // Compute and show acquisition frame rate

    if (m_dFramePeriod != 0.0)
    {
        dFrameRate = m_dFramePeriod / 1000000.0;    // Convert from micro-sec to sec.
        dFrameRate = (double)1.0 / dFrameRate;
        strToShow.Format("%.2f", dFrameRate);
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

    // Show interrupt average delay jitter only if not in triggered mode

    if (! m_bTriggerMode)
    {
        // Show VIXN average delay jitter (in microsecs)

        strToShow.Format("%.2f", m_dVixnAverageJitter);
        m_EditVixnJitter.SetWindowText(strToShow);

        // Show regular callback average delay jitter (in microsecs)

        strToShow.Format("%.2f", m_dNonVixnAverageJitter);
        m_EditNonVixnJitter.SetWindowText(strToShow);

        // Show VIXN and normal average delay jitter graphically

        DrawCursor(m_StaticVixnCursor, RGB(0, 0xFF, 0), (DWORD)m_dVixnAverageJitter);
        DrawCursor(m_StaticNonVixnCursor, RGB(0, 0xFF, 0), (DWORD)m_dNonVixnAverageJitter);
    }
    else
    {
        m_EditVixnJitter.SetWindowText( _T("*****"));
        m_EditNonVixnJitter.SetWindowText( _T("*****"));
        DrawCursor(m_StaticVixnCursor, RGB(0, 0, 0), (DWORD)m_dVixnAverageJitter);
        DrawCursor(m_StaticNonVixnCursor, RGB(0, 0, 0), (DWORD)m_dNonVixnAverageJitter);
    }

}





//------------------------------------------
//          DrawCursor()
//------------------------------------------
void CIFC_PC2V_VixnDlg::DrawCursor(HWND hWnd, COLORREF TheColor, DWORD dwWidth)
{
CClientDC MyDC(this);
CBrush MyNewBrush (TheColor);       // Interior filling with passed color
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
long lWindowWidth;
long lWidthToDraw;


    pOldPen = MyDC.SelectObject(&MyBlackPen);
    MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    // Draw a black rectangle to erase former cursor

    GetWindowPosition(hWnd, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // Get the width of the target window

    ::GetClientRect(hWnd, &RectDraw);
    lWindowWidth = (DWORD)RectDraw.right;

    // Determine the width of the cursor to draw within the target window

    lWidthToDraw = dwWidth * PIXEL_PER_MICRO_SEC;
    lWidthToDraw = min(lWidthToDraw, lWindowWidth);   // Clip to window width maximum

    // Draw a colored rectangle which is the desired cursor

    pOldBrush = MyDC.SelectObject(&MyNewBrush);
    GetWindowPosition(hWnd, &RectDraw);
    RectDraw.right = RectDraw.left + lWidthToDraw;
    MyDC.Rectangle(&RectDraw);

    // Restore original drawing pen and brush

    MyDC.SelectObject(pOldBrush);
    MyDC.SelectObject(pOldPen);

}


//------------------------------------------
//           DrawTimingBarTickMark
//------------------------------------------
void CIFC_PC2V_VixnDlg::DrawTimingBarTickMark(HWND hWnd) 
{
CClientDC MyDC(this);
RECT RectDraw;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Tick mark lines
CPen *pOldPen;
DWORD dwMicroSec;
DWORD dwTimingBarLength;
CString strHundred;
UINT OldTextAlign;
int OldBkgnd;
int OldMapMode;


    pOldPen         = MyDC.SelectObject(&MyBlackPen);
    OldMapMode      = MyDC.SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = MyDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = MyDC.SetTextAlign(TA_CENTER);

    // Determine the lower-left point of the Timing Bar and it's length

    GetWindowPosition(hWnd, &RectDraw);

    dwTimingBarLength = RectDraw.right - RectDraw.left;

    // Draw a small Tick Mark every 25 pixels ( 5 microSec.)

    for (dwMicroSec = 0; dwMicroSec <= dwTimingBarLength; dwMicroSec += 25)
    {
        MyDC.MoveTo(RectDraw.left + dwMicroSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMicroSec, RectDraw.bottom + 5);   // Small tick 5 pixels high
    }

    // Draw a medium Tick Mark every 50 pixels ( 10 microSec.)

    for (dwMicroSec = 0; dwMicroSec <= dwTimingBarLength; dwMicroSec += 50)
    {
        MyDC.MoveTo(RectDraw.left + dwMicroSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMicroSec, RectDraw.bottom + 10);   // Medium tick 10 pixels high
    }

    // Draw a large Tick Mark every 100 pixels ( 20 microSec.) as well as numbers under

    for (dwMicroSec = 0; dwMicroSec <= dwTimingBarLength; dwMicroSec += 100)
    {
        MyDC.MoveTo(RectDraw.left + dwMicroSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMicroSec, RectDraw.bottom + 15);   // Large tick 15 pixels high
        strHundred.Format("%d", dwMicroSec / PIXEL_PER_MICRO_SEC);
        MyDC.TextOut(RectDraw.left + dwMicroSec, RectDraw.bottom + 15, strHundred);
    }

    // Restore original pen and modes

    MyDC.SelectObject(pOldPen);
    MyDC.SetMapMode(OldMapMode);
    MyDC.SetBkMode(OldBkgnd);
    MyDC.SetTextAlign(OldTextAlign);

    GdiFlush();             // Force drawing of the timing bar

}


//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_VixnDlg::DrawWindowBorder(HWND hWnd)
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
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_VixnDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing && m_bTriggerMode);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}





//------------------------------------------
//            OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnPaint() 
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

        // Redraw average delay jitter graphically

        DrawTimingBarTickMark(m_StaticVixnCursor) ;
        DrawCursor(m_StaticVixnCursor, RGB(0, 0xFF, 0), (DWORD)m_dVixnAverageJitter);

        DrawTimingBarTickMark(m_StaticNonVixnCursor) ;
        DrawCursor(m_StaticNonVixnCursor, RGB(0, 0xFF, 0), (DWORD)m_dNonVixnAverageJitter);

        m_dwOnPaintCounter++;
	}
}






//------------------------------------------
//            OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_VixnDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//------------------------------------------
//              OnButtonCam
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonCam() 
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

        // Clear the Display Window

        m_bClearDisplay = TRUE;
    }
}



//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnClose() 
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
void CIFC_PC2V_VixnDlg::OnTimer(UINT nIDEvent) 
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
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonTrigger() 
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

    // Raise the flag indicating that the SOT event occured

    if (bTriggerSrcWasExternal)
    {
        m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonGrab() 
{

    m_dwFrameCounter        = 0;
    m_dwEOF_EventCounter    = 0;
    m_dwJitterArrayIndex    = 0;

    m_dVixnAverageJitter        = 0.0;
    m_dNonVixnAverageJitter     = 0.0;

    m_dFramePeriod      = 0;
    m_dLastFramePeriod  = 0;

    m_pMyVixn->ResetFrameInterruptCount();
    m_pMyVixn->ResetFrameInterruptLastPeriod();

    m_bClearDisplay             = FALSE;
    m_DispThreadParams.bBusy    = FALSE;

    m_GrabID = m_pCam->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_pHostCapMemory,
                             BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_bIsGrabbing = TRUE;
    m_pAcqThread->AwakeThread(this);

}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay             = FALSE;

    m_pCam->Snap(m_pHostCapMemory, 0, 0, 0, 0);

    // Increment and show frame counter

    m_dwFrameCounter++;
    strToShow.Format("%d", m_dwFrameCounter);
    m_EditFrameCount.SetWindowText(strToShow);

    // Show frame on the screen

    m_pImageConnection->GetSrc()->SetBufferAddr(m_pHostCapMemory);
    m_pImageConnection->Display();

}



//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonFreeze() 
{

    m_pCam->Freeze();
    m_bIsGrabbing = FALSE;

}

//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_VixnDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
