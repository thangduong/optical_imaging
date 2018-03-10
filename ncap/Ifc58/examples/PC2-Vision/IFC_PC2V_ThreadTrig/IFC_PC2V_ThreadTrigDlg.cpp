//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ThreadTrigDlg.cpp
//
//  BIRTH DATE:     January 2003
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
//                  Acquisition and display with external camera triggering.
//                  Note that your camera must be in external trigger mode.
//
//  The goal of this demo is to trigger the camera with an external (or manual)
//  trigger pulse instead of letting the camera free-running. This mode is
//  usefull to synchronize the images to an event and/or to capture fast moving
//  objects.
//
//  The use of progressive camera is recommended for fast moving objects.
//
//  Study carefully the different external trigger modes offered by your
//  camera in order to fullfill it's requirements.
//
//------------------------------------------------------------------------------
//  EXTERNAL TRIGGER OPERATION DESCRIPTION
//------------------------------------------------------------------------------
//  A typical sequence of events is this :
//
//      1- An external or manual TRIGGER event occurs.
//
//      2- The Frame Grabber generates a FRAME RESET pulse on it's
//          Camera_Trigger1-2-3 outputs.
//          The camera starts the frame acquisition by accumulating
//          charges on it's sensor. The camera shutter speed determine
//          the amount of time the light will hit the sensor.
//         
//      3- The Frame Grabber generates a Vs pulse on it's Vs1-2-3 outputs.
//          The camera starts to output the video signal. Note that on
//          some camera, the Vs pulse is generated internally and it
//          doesn't need a Vs from the Frame Grabber.
//         
//      4- Optionnally the camera can generates a WEN (Write Enable)
//          signal to instruct the Frame Grabber about the validity
//          of the video signal. This mode must be enabled at both the
//          camera and the Frame Grabber sides.
//
//------------------------------------------------------------------------------
//  CAMERA SHUTTER SPEED
//------------------------------------------------------------------------------
//  The camera shutter speed determine the amount of time the light
//  will reach the sensor and thus the image luminance level.
//  Some camera has DIP switched to select the shutter speed.
//  On some camera mode, the time between the FRAME RESET and the Vs
//  will determine the shutter speed. On some other mode, the shutter
//  speed is the width of the FRAME RESET pulse.
//
//------------------------------------------------------------------------------
// WARNING :    Some camera need a minimum time between the FRAME RESET and
//              the Vs. You must take care yourself of settings the
//              "P2V_VS_PULSE_OFFSET" parameter to that the Vs will be
//              generated after the FRAME RESET signal.
//
//          For example the SONY XC-55 camera needs a minimum time of
//          140 micro-second between the end of FRAME RESET and the
//          beginning of Vs, then "P2V_VS_PULSE_OFFSET" must be at least
//          equals to :
//
//  (P_FRAME_RESET_OFFSET * Line Time in microsec) + P_FRAME_RESET_SIZE + 140
//
//      The Line Time is equal to 1 / HSYNC_FREQ.
//
//      Failing to meet this requirement will most likely "hang" your
//      camera and/or your image acquisition system.
//
//------------------------------------------------------------------------------
//  TERMINOLOGY :
//------------------------------------------------------------------------------
//  Trigger Event : A pulse sent to the PC2-Vision Frame Grabber to start
//                  a single or multiple frames acquisition. It can be an
//                  electric pulse on the Ext_Trig pins of the PC2-Vision
//                  connectors or a software command. This must not be
//                  confused with the Camera_Trigger1-2-3 outputs (see FrameReset).
//
//  Master Mode :   A PC2-Vision mode in which the frame grabber is generating 
//                  the Vertical (Vs) and/or the Horizontal (Hs) sync signal.
//                  Note that this mode MUST be used when using more than one
//                  camera per connector in order to have all the camera
//                  genlocked (all video signals synchronised with the
//                  same phase).
//
//  Frame Reset :   A PC2-Vision signal generated on the Camera_Trigger1-2-3
//                  outputs to instructs the camera to start acquiring the
//                  image.
//
//------------------------------------------------------------------------------
//  KEY PARAMETERS INVOLVED:
//------------------------------------------------------------------------------
//                      TRIGGER EVENT
//------------------------------------------------------------------------------
//
//  P_TRIGGER_ENABLE        : Enable the trigger event detection.
//
//  P_TRIGGER_SRC           : Source of the Trigger Event, external or software.
//
//  P_TRIGGER_POLARITY      : Polarity of the external Trigger Event.
//
//  P_GEN_SW_TRIGGER        : Starts a trigger cycle when the Trigger Event
//                              source is software.
//
//  P_FRAMES_PER_TRIGGER    : Number of frames to acquire after a Trigger Event.
//                              Range 1-1000.
//
//  P_TRIGGER_DEBOUNCE      : Debouncing delay for the external trigger pulse.
//                              Range 1-255 micro-seconds.
//
//------------------------------------------------------------------------------
//                      FRAME RESET
//------------------------------------------------------------------------------
//
//  P_FRAME_RESET_MODE      : Enable or not the generation of the Frame Reset.
//
//  P_FRAME_RESET_POLARITY  : Polarity of the Frame Reset, low or high.
//
//  P_FRAME_RESET_OFFSET    : Frame Reset assertion delay after the Trigger Event.
//                              Range 0-256 lines.
//
//  P_FRAME_RESET_SIZE      : Width of the Frame Reset signal.
//                              Range 1-200 000 micro-seconds.
//
//------------------------------------------------------------------------------
//                      VERTICAL SYNC
//------------------------------------------------------------------------------
//
//  P2V_VS_PULSE_ENABLE     : Enables the Master Mode for Vs.
// 
//  P2V_VS_PULSE_DURATION   : Width of the Vs.
//                              Range 1-200 000 micro-seconds.
//
//  P2V_VS_PULSE_OFFSET     : Vs assertion delay after the Trigger event.
//                              Range 1-200 000 micro-seconds.
//
//------------------------------------------------------------------------------
//                      HORIZONTAL SYNC
//------------------------------------------------------------------------------
//
//  P2V_MASTER_HSYNC        : Enables the Master Mode for Hs.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"

#include "CamSelDlg.h"                      // Cam Selector Dialog Box
#include "CamSigParamDlg.h"                 // Cam Signals parameter Dialog Box
#include "StrobeParamDlg.h"                 // Strobe Signal parameter Dialog Box

#include "IFC_PC2V_ThreadTrig.h"
#include "IFC_PC2V_ThreadTrigDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_ThreadTrigDlg::CIFC_PC2V_ThreadTrigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_ThreadTrigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_ThreadTrigDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pCam              = NULL;
    m_pImageConnection  = NULL;
    m_GrabID            = NULL;

    m_pIntCallback_SOT  = NULL;
    m_pIntCallback_SOF  = NULL;
    m_pIntCallback_EOF  = NULL;
    m_pIntCallback_EOT1 = NULL;
    m_pIntCallback_EOT2 = NULL;
    m_pIntCallback_EOT3 = NULL;

    m_bIsGrabbing       = FALSE;
    m_bAppClosing       = FALSE;
    m_bIsTrigBeepEnable = FALSE;
    m_bSystemOverload   = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwImageSize       = 0;

    m_dwFrameCounter    = 0;

    m_pAcqThread        = NULL;
    m_pHostCapMemory    = NULL;
    m_pDisplayThread    = NULL;

    m_dwIsSOT_EventCounter  = 0;
    m_dwIsSOF_EventCounter  = 0;
    m_dwIsEOF_EventCounter  = 0;
    m_dwIsEOT1_EventCounter = 0;
    m_dwIsEOT2_EventCounter = 0;
    m_dwIsEOT3_EventCounter = 0;

    m_bWasSOT_EventDetected  = FALSE;
    m_bWasSOF_EventDetected  = FALSE;
    m_bWasEOF_EventDetected  = FALSE;
    m_bWasEOT1_EventDetected = FALSE;
    m_bWasEOT2_EventDetected = FALSE;
    m_bWasEOT3_EventDetected = FALSE;

    m_pMyCamSigParamDlg = NULL;

}



//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_ThreadTrigDlg)
	DDX_Control(pDX, IDC_CHECK_TRIG_BEEP, m_CheckTrigBeep);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_BUTTON_STROBE_PARAM, m_ButtonStrobeParam);
	DDX_Control(pDX, IDC_BUTTON_CAM_SIG_PARAM, m_ButtonCamSigParam);
	DDX_Control(pDX, IDC_STATIC_EOT_LIGHT, m_StaticEOTLight);
	DDX_Control(pDX, IDC_STATIC_EOF_LIGHT, m_StaticEOFLight);
	DDX_Control(pDX, IDC_STATIC_SOF_LIGHT, m_StaticSOFLight);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_EDIT_FL, m_EditFrameLost);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIFC_PC2V_ThreadTrigDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_ThreadTrigDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_CAM_SIG_PARAM, OnButtonCamSigParam)
	ON_BN_CLICKED(IDC_BUTTON_STROBE_PARAM, OnButtonStrobeParam)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_CHECK_TRIG_BEEP, OnCheckTrigBeep)
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
void CIFC_PC2V_ThreadTrigDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pCam;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;
IFC_GRAB_STATS GrabStats;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;   // Context is the ptr to my class

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
            pMyClass->m_MeasureFramePeriod.TagTime();

            // Show lost frame count

            pMyClass->m_pBrdMod->GetGrabStats(GrabID, &GrabStats);

            strToShow.Format("%d", GrabStats.NumberOfFramesLost);
            pMyClass->m_EditFrameLost.SetWindowText(strToShow);

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

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
void CIFC_PC2V_ThreadTrigDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;
CImgConn                *pImageConnect;
int                     iSeqNum;
HIFCGRAB                GrabID;
BYTE                    *pHostBuffer;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

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
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

    if (pMyClass->m_bIsTrigBeepEnable)
    {
        Beep(1000, 100);
    }

}



//------------------------------------------
//              MyCallback_SOF
//------------------------------------------
// Function called when the "Start of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_SOF(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    if (pMyClass->m_bIsGrabbing)
    {
        pMyClass->m_dwIsSOF_EventCounter++;
    }

}



//------------------------------------------
//              MyCallback_EOF
//------------------------------------------
// Function called when the "End of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_EOF(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOF_EventCounter++;

}


//------------------------------------------
//              MyCallback_EOT1
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 1
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_EOT1(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT1_EventCounter++;

}



//------------------------------------------
//              MyCallback_EOT2
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 2
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_EOT2(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT2_EventCounter++;

}



//------------------------------------------
//              MyCallback_EOT3
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 3
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::MyCallback_EOT3(void *pContext)
{
CIFC_PC2V_ThreadTrigDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadTrigDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT3_EventCounter++;

}


//------------------------------------------
//            ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ReadAndClearEvents()
{

    if (m_dwIsSOT_EventCounter > 0)
    {
        m_dwIsSOT_EventCounter--;
        m_bWasSOT_EventDetected = TRUE;
    }
    else
    {
        m_bWasSOT_EventDetected = FALSE;
    }

    if (m_dwIsSOF_EventCounter > 0)
    {
        m_dwIsSOF_EventCounter--;
        m_bWasSOF_EventDetected = TRUE;
    }
    else
    {
        m_bWasSOF_EventDetected = FALSE;
    }

    if (m_dwIsEOF_EventCounter > 0)
    {
        m_dwIsEOF_EventCounter--;
        m_bWasEOF_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOF_EventDetected = FALSE;
    }

    if (m_dwIsEOT1_EventCounter > 0)
    {
        m_dwIsEOT1_EventCounter--;
        m_bWasEOT1_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOT1_EventDetected = FALSE;
    }

    if (m_dwIsEOT2_EventCounter > 0)
    {
        m_dwIsEOT2_EventCounter--;
        m_bWasEOT2_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOT2_EventDetected = FALSE;
    }

    if (m_dwIsEOT3_EventCounter > 0)
    {
        m_dwIsEOT3_EventCounter--;
        m_bWasEOT3_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOT3_EventDetected = FALSE;
    }

}




//------------------------------------------
//            OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_ThreadTrigDlg::OnInitDialog()
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

    // Initializes IFC camera interface signals parameters Dialog Box

    m_pMyCamSigParamDlg = new CCamSigParamDlg(this, m_pCam);
    if (m_pMyCamSigParamDlg == NULL)
    {
        AfxMessageBox(_T("Could not initializes Cam signal Dialog Box object !!!"));
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

    
    return TRUE;  // return TRUE unless you set the focus to a control
}




//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_ThreadTrigDlg::InitIFC_Capture()
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
BOOL CIFC_PC2V_ThreadTrigDlg::InitIFC_Callback()
{

    // Want a callback on the TRIGGER EVENT detection

    m_pIntCallback_SOT = m_pBrdMod->CreateIntrCallback(P2V_INTR_SOT, MyCallback_SOT, this);

    if (m_pIntCallback_SOT == NULL)
        return FALSE;

    // Want a callback on the START OF FRAME

    m_pIntCallback_SOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_START_OF_FRAME, MyCallback_SOF, this);

    if (m_pIntCallback_SOF == NULL)
        return FALSE;

    // Want a callback on the END OF FRAME

    m_pIntCallback_EOF = m_pBrdMod->CreateIntrCallback(P2V_INTR_EOFRM, MyCallback_EOF, this);

    if (m_pIntCallback_EOF == NULL)
        return FALSE;

    // Want a callback on the END OF TRANSFER on channel # 1

    m_pIntCallback_EOT1 = m_pBrdMod->CreateIntrCallback(P2V_INTR_BMDONE, MyCallback_EOT1, this);

    if (m_pIntCallback_EOT1 == NULL)
        return FALSE;

    // Want a callback on the END OF TRANSFER on channel # 2

    m_pIntCallback_EOT2 = m_pBrdMod->CreateIntrCallback(P2V_INTR_BMDONE2, MyCallback_EOT2, this);

    if (m_pIntCallback_EOT2 == NULL)
        return FALSE;

    // Want a callback on the END OF TRANSFER on channel # 3

    m_pIntCallback_EOT3 = m_pBrdMod->CreateIntrCallback(P2V_INTR_BMDONE3, MyCallback_EOT3, this);

    if (m_pIntCallback_EOT3 == NULL)
        return FALSE;

    return TRUE;

}





//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_ThreadTrigDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
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
void CIFC_PC2V_ThreadTrigDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_SOT->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SOT);
    m_pIntCallback_SOT = NULL;

    ExceptCode= m_pIntCallback_SOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SOF);
    m_pIntCallback_SOF = NULL;

    ExceptCode= m_pIntCallback_EOF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOF);
    m_pIntCallback_EOF = NULL;

    ExceptCode= m_pIntCallback_EOT1->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOT1);
    m_pIntCallback_EOT1 = NULL;

    ExceptCode= m_pIntCallback_EOT2->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOT2);
    m_pIntCallback_EOT2 = NULL;

    ExceptCode= m_pIntCallback_EOT3->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_EOT3);
    m_pIntCallback_EOT3 = NULL;

}





//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ReleaseIFC_ImageConnection()
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
BOOL CIFC_PC2V_ThreadTrigDlg::AllocateCaptureMemory()
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
void CIFC_PC2V_ThreadTrigDlg::ReleaseCaptureMemory()
{

    if (m_pHostCapMemory)
    {
        m_pBrdMod->UnLockMem(m_CapMemLockHandle);
        free(m_pHostCapMemory);
    }

    m_pHostCapMemory = NULL;

}



//------------------------------------------
//            OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnPaint() 
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
//            OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_ThreadTrigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ReleaseAll()
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

    // Kill the Timers

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

    // Release the Camera Parameters Dialog Box

    if (m_pMyCamSigParamDlg)
    {
        delete m_pMyCamSigParamDlg;
        m_pMyCamSigParamDlg = NULL;
    }

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
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

    // Enable the trigger beeper check accordingly

    m_CheckTrigBeep.EnableWindow(m_bTriggerMode);

}




//------------------------------------------
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ClearDisplay()
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
BOOL CIFC_PC2V_ThreadTrigDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_ThreadTrigDlg::OnButtonCam() 
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
void CIFC_PC2V_ThreadTrigDlg::OnClose() 
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
void CIFC_PC2V_ThreadTrigDlg::OnTimer(UINT nIDEvent) 
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

        ShowEventLights();              // Show "Trigger TO Image" lights

        m_dwGuiCounter++;

    }

    CDialog::OnTimer(nIDEvent);

}


//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ShowStatistics() 
{
float fFrameRate;
CString strToShow;
IFC_GRAB_STATS GrabStats;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
        return;
    }

    // Compute and show acquisition frame rate

    fFrameRate = m_MeasureFramePeriod.GetTime();
    if (fFrameRate != 0.0)
    {
        fFrameRate = (float)1.0 / fFrameRate;
        strToShow.Format("%.2f", fFrameRate);
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

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing && m_bTriggerMode);

    m_ButtonCamSigParam.EnableWindow(! m_bIsGrabbing && m_bTriggerMode);
    m_ButtonStrobeParam.EnableWindow(! m_bIsGrabbing && m_bTriggerMode);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}






//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnButtonTrigger() 
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

    m_dwIsSOT_EventCounter++;

    if (bTriggerSrcWasExternal)
    {
        m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }

}




//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnButtonGrab() 
{

    m_dwFrameCounter            = 0;

    m_dwIsSOF_EventCounter     = 0;
    m_dwIsSOT_EventCounter     = 0;
    m_dwIsSOF_EventCounter     = 0;
    m_dwIsEOF_EventCounter     = 0;
    m_dwIsEOT1_EventCounter    = 0;
    m_dwIsEOT2_EventCounter    = 0;
    m_dwIsEOT3_EventCounter    = 0;

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
void CIFC_PC2V_ThreadTrigDlg::OnButtonSnap() 
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
void CIFC_PC2V_ThreadTrigDlg::OnButtonFreeze() 
{

    m_pCam->Freeze();
    m_bIsGrabbing = FALSE;

}





//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strTheText;


    // START OF TRIGGER Event detection indicator

    if (m_bIsGrabbing)
    {
        //------------------------Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            strTheText = _T("Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);           // Green light
        }
        else if (! m_bTriggerMode)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0,0,0), FALSE, strTheText);             // No (black) light
        }
        else
        {
            strTheText = _T("No Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0xFF,0xFF,0), bToggler, strTheText);    // Yellow light
        }
        //------------------------Show START OF FRAME presence light

        if (m_bWasSOF_EventDetected)
        {
            strTheText = _T("Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);           // Green light
        }
        else
        {
            strTheText = _T("No Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0xFF,0xFF,0), bToggler, strTheText);    // Yellow light
        }

        //------------------------Show END OF FRAME presence light

        if (m_bWasEOF_EventDetected)
        {
            strTheText = _T("Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);           // Green light
        }
        else
        {
            strTheText = _T("No Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0xFF,0xFF,0), bToggler, strTheText);    // Yellow light
        }

        //------------------------Show END OF TRANSFER presence lights

        if (m_bWasEOT1_EventDetected && ((m_dwActivePort == 0) || (m_dwActivePort == 3)))
        {
            strTheText = _T("Memory Xfer");
            DrawRectangleLight(m_StaticEOTLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);   // Green light
        }
        else if (m_bWasEOT2_EventDetected && ((m_dwActivePort == 1) || (m_dwActivePort == 4)))
        {
            strTheText = _T("Memory Xfer");
            DrawRectangleLight(m_StaticEOTLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);   // Green light
        }
        else if (m_bWasEOT3_EventDetected && ((m_dwActivePort == 2) || (m_dwActivePort == 5)))
        {
            strTheText = _T("Memory Xfer");
            DrawRectangleLight(m_StaticEOTLight.m_hWnd, RGB(0,0xFF,0), TRUE, strTheText);   // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer");
            DrawRectangleLight(m_StaticEOTLight.m_hWnd, RGB(0xFF,0xFF,0), bToggler, strTheText);    // Yellow light
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0,0,0), FALSE, strTheText);   // No (black) light
        DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0,0,0), FALSE, strTheText);   // No (black) light
        DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0,0,0), FALSE, strTheText);   // No (black) light
        DrawRectangleLight(m_StaticEOTLight.m_hWnd, RGB(0,0,0), FALSE, strTheText);   // No (black) light
    }

    bToggler = ! bToggler;

}


//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
        ::GetClientRect(hWnd, &RectSize);                 // Size of the rectangle in pixel
        TextSize = MyDC.GetTextExtent(strTheText);      // Size of the text in pixel

        MyDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
        MyDC.SetTextColor(RGB(0, 0, 0));

        iTextOffsetX = (RectSize.right - TextSize.cx) / 2;
        iTextOffsetY = (RectSize.bottom - TextSize.cy) / 2;
        MyDC.TextOut(RectDraw.left + iTextOffsetX, RectDraw.top + iTextOffsetY, strTheText, strTheText.GetLength());
    }

    MyDC.SelectObject(pOldPen);

}



//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::DrawWindowBorder(HWND hWnd)
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
//          OnButtonCamSigParam()
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnButtonCamSigParam() 
{

    if (m_pMyCamSigParamDlg)
    {
        m_pMyCamSigParamDlg->DoModal();
    }

}



//------------------------------------------
//          OnButtonStrobeParam()
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnButtonStrobeParam() 
{
CStrobeParamDlg MyStrobeParamDlg(this, m_pCam);

    MyStrobeParamDlg.DoModal();

}




//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}




//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_ThreadTrigDlg::OnCheckTrigBeep() 
{

    m_bIsTrigBeepEnable = FALSE;

    if (m_CheckTrigBeep.GetCheck())
    {
        m_bIsTrigBeepEnable = TRUE;
    }

}
