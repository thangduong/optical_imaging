//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CamSwitchDlg.cpp
//
//  BIRTH DATE:     April 2003
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
//                  Up to six asynchronous cameras are acquired sequentially.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_CamSwitch.h"
#include "IFC_PC2V_CamSwitchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//-----------------------------------------------
//            Constructor
//-----------------------------------------------
CIFC_PC2V_CamSwitchDlg::CIFC_PC2V_CamSwitchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_CamSwitchDlg::IDD, pParent)
{
DWORD dwCamIndex;


	//{{AFX_DATA_INIT(CIFC_PC2V_CamSwitchDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pHostCapMemory    = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_aGrabID[dwCamIndex]           = NULL;
        m_apImageConnection[dwCamIndex] = NULL;
        m_apCam[dwCamIndex]             = NULL;
        m_apAcqThread[dwCamIndex]       = NULL;
        m_abIsGrabbing[dwCamIndex]      = FALSE;
    }

    m_dwCamSizeX    = 0;
    m_dwCamSizeY    = 0;
    m_dwPixBitDepth = 0;
    m_dwImageSize   = 0;
    m_CamColor      = IFC_MONO;
    m_dwSnapPolling = 0;

    m_pIntCallback_SOT  = NULL;
    m_pIntCallback_SOF  = NULL;
    m_pIntCallback_EOF  = NULL;
    m_pIntCallback_EOT1 = NULL;
    m_pIntCallback_EOT2 = NULL;
    m_pIntCallback_EOT3 = NULL;

    m_pDisplayThread    = NULL;

    m_bAppClosing           = FALSE;
    m_bTriggerMode          = FALSE;
    m_bCamSequenceTouched   = FALSE;
    m_bCamTypeTouched       = FALSE;
    m_bSnapping             = FALSE;
    m_bTriggerMode          = FALSE;

    m_dwIsSOT_EventDetected  = 0;
    m_dwIsSOF_EventDetected  = 0;
    m_dwIsEOF_EventDetected  = 0;
    m_dwIsEOT1_EventDetected = 0;
    m_dwIsEOT2_EventDetected = 0;
    m_dwIsEOT3_EventDetected = 0;

    m_bWasSOT_EventDetected  = FALSE;
    m_bWasSOF_EventDetected  = FALSE;
    m_bWasEOF_EventDetected  = FALSE;
    m_bWasEOT1_EventDetected = FALSE;
    m_bWasEOT2_EventDetected = FALSE;
    m_bWasEOT3_EventDetected = FALSE;

}



//-----------------------------------------------
//            DoDataExchange
//-----------------------------------------------
void CIFC_PC2V_CamSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_CamSwitchDlg)
	DDX_Control(pDX, IDC_STATIC_EOT3_LIGHT, m_StaticEOT3Light);
	DDX_Control(pDX, IDC_STATIC_EOT2_LIGHT, m_StaticEOT2Light);
	DDX_Control(pDX, IDC_STATIC_EOT1_LIGHT, m_StaticEOT1Light);
	DDX_Control(pDX, IDC_STATIC_EOF_LIGHT, m_StaticEOFLight);
	DDX_Control(pDX, IDC_STATIC_SOF_LIGHT, m_StaticSOFLight);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_EDIT_FR_TOTAL, m_EditFrameRateTotal);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE, m_EditCamType);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE, m_ButtonCamType);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_SEQ_COUNT, m_EditSequenceCount);
	DDX_Control(pDX, IDC_BUTTON_CAM_SEQ, m_ButtonCamSequence);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_STATIC_DISPLAY6, m_StaticDisplayCam6);
	DDX_Control(pDX, IDC_STATIC_DISPLAY5, m_StaticDisplayCam5);
	DDX_Control(pDX, IDC_STATIC_DISPLAY4, m_StaticDisplayCam4);
	DDX_Control(pDX, IDC_STATIC_DISPLAY3, m_StaticDisplayCam3);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplayCam2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplayCam1);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM6, m_StaticLightCam6);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM5, m_StaticLightCam5);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM4, m_StaticLightCam4);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM3, m_StaticLightCam3);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM2, m_StaticLightCam2);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM1, m_StaticLightCam1);
	DDX_Control(pDX, IDC_EDIT_CAM_SEQ, m_EditCamSeq);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2V_CamSwitchDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_CamSwitchDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM_SEQ, OnButtonCamSeq)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_EN_CHANGE(IDC_EDIT_CAM_SEQ, OnChangeEditCamSeq)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE, OnButtonCamType)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_CamSwitchDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_CamSwitchDlg *pMyClass;
DWORD dwMyCamera;
DWORD dwNewCamera;
DWORD dwMyThread;
DWORD dwTheCamSeqCount;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pMyCamera;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;
ACQ_THREAD_PARAM *pMyParams;
GRAB_EXT_ATTR ExtraAttrib;
CString strToShow;
BOOL bReleaseTheBuffer;
HWND *pahCamLights;


    // Get my parameters

    pMyParams = (ACQ_THREAD_PARAM *)pContext;

    // A static function has no access to it's own class, need a ptr to it

    pMyClass            = pMyParams->pMyClass;
    dwMyThread          = pMyParams->dwMyThreadIndex;
    dwMyCamera          = pMyParams->dwMyCameraIndex;
    dwTheCamSeqCount    = pMyParams->dwCamSeqCount;

    // To alleviate the code, keep useful local variables

    pBrdMod             = pMyClass->m_pBrdMod;
    GrabID              = pMyClass->m_aGrabID[dwMyThread];
    pMyCamera           = pMyClass->m_apCam[dwMyCamera];
    pImageConnect       = pMyClass->m_apImageConnection[dwMyCamera];
    pahCamLights        = pMyClass->m_ahCamLightOn;

    pMyClass->m_debugParallPort = 0;

    while (pMyClass->m_abIsGrabbing[dwMyThread])
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pMyCamera->GrabWaitFrameEx(GrabID, &pHostBuffer, IFC_WAIT_NEWER_FRAME,
                                              WAIT_ACQ_MAX_MSEC, TRUE, NULL, NULL, &ExtraAttrib);

        // If this frame is good and belongs to my camera

        if (iSeqNum != -1)
        {
            bReleaseTheBuffer = TRUE;

            // Determine if this image belongs to the camera I manage

            if (ExtraAttrib.camPortNum == dwMyCamera)
            {
                // Determine if this camera is the one I manage in the sequence
                //  because a camera may appear more than once in a sequence

                dwNewCamera = pMyClass->m_adwCamSequence[pMyClass->m_dwCurrentSeqIndex];

                if (dwMyThread == pMyClass->m_dwCurrentSeqIndex)
                {

                    // Take care of frame rate statistics once every whole sequence

                    if (pMyClass->m_dwCurrentSeqIndex == 0)
                    {
                        pMyClass->m_MeasureFramePeriod.TagTime();
                    }

                    // Take care of the Trigger-To-Image event counters

                    pMyClass->ReadAndClearEvents(dwMyCamera);

                    // If the last buffer is not waiting to be displayed,
                    //  flag it to be displayed and wake-up the Display thread
                    // otherwise, release the buffer immediately (will never be displayed)

                    if (pMyClass->m_aDispThreadParams[dwMyThread].bBusy == FALSE)
                    {
                        pMyClass->m_aDispThreadParams[dwMyThread].pTheBuffer    = pHostBuffer;
                        pMyClass->m_aDispThreadParams[dwMyThread].GrabID        = GrabID;
                        pMyClass->m_aDispThreadParams[dwMyThread].iBufferIndex  = iSeqNum;
                        pMyClass->m_aDispThreadParams[dwMyThread].dwCameraIndex = dwMyCamera;
                        pMyClass->m_aDispThreadParams[dwMyThread].bBusy         = TRUE;

                        pMyClass->m_pDisplayThread->AwakeThread(pMyClass);

                        bReleaseTheBuffer           = FALSE;         // Display thread will release it
                        pMyClass->m_bSystemOverload = FALSE;
                    }
                    else
                    {
                        pMyClass->m_bSystemOverload = TRUE;
                    }

                    // Put former (last) camera light OFF and current (new) camera light ON 

                    pMyClass->DrawRectangleLight(pahCamLights[pMyClass->m_dwLastCamera], RGB(0, 0, 0), FALSE, strToShow);
                    pMyClass->DrawRectangleLight(pahCamLights[dwNewCamera], RGB(0, 0xFF, 0), FALSE, strToShow);

                    pMyClass->m_dwCurrentSeqIndex++;
                    pMyClass->m_dwCurrentSeqIndex %= pMyClass->m_dwCamSequenceCount;
                    pMyClass->m_dwLastCamera = dwNewCamera;

                    // Determine if another frame is to be expected

                    if (pMyClass->m_bSnapping)
                    {
                        pMyClass->m_abIsGrabbing[dwMyThread] = FALSE;       // Go out of this loop
                    }

                } // This camera belongs to my thread

            } // This frame belongs to my camera

            // Release the frame back into the active acquisition buffer ring
            //  if it did not belong to my camera or it will not be displayed

            if (bReleaseTheBuffer)
            {
                pMyCamera->GrabRelease(GrabID, iSeqNum);
            }

        }
        else
        {
            // Grab failure, take care of the Trigger-To-Image event counters

            pMyClass->ReadAndClearEvents(dwMyCamera);
        }

    }

    // Return control to the calling thread
}





//------------------------------------------
//              ThreadDisplayProc
//------------------------------------------
// Called by the display thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_CamSwitchDlg).
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_CamSwitchDlg  *pMyClass;
CImgConn                *pImageConnect;
int                     iSeqNum;
HIFCGRAB                GrabID;
BYTE                    *pHostBuffer;
DWORD                   dwThreadIndex;
DWORD                   dwCamIndex;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    // While there is buffer ready to be to displayed

    while (pMyClass->GetBufferToDisplay(&dwThreadIndex))
    {
        // Get the information associated with the buffer and channel to display

        iSeqNum     = pMyClass->m_aDispThreadParams[dwThreadIndex].iBufferIndex;
        pHostBuffer = pMyClass->m_aDispThreadParams[dwThreadIndex].pTheBuffer;
        GrabID      = pMyClass->m_aDispThreadParams[dwThreadIndex].GrabID;
        dwCamIndex  = pMyClass->m_aDispThreadParams[dwThreadIndex].dwCameraIndex;

        // Get the ImageConnection object associated with this camera

        pImageConnect = pMyClass->m_apImageConnection[dwCamIndex];

        // Update the address associated with the image source to point
        // to the frame we just acquired

        pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

        // Display the  frame in our client window

        pImageConnect->Display();

        // Release the frame back into the active circular acquisition buffer

        pMyClass->m_apCam[dwCamIndex]->GrabRelease(GrabID, iSeqNum);

        // Flag the buffer as displayed

        pMyClass->m_aDispThreadParams[dwThreadIndex].bBusy = FALSE;

    }

    // Return control to the calling thread
}



//------------------------------------------
//              GetBufferToDisplay
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::GetBufferToDisplay(DWORD *pThreadIndex)
{
DWORD dwThreadIndex;


    // Look only among the User's Camera Sequence

    for (dwThreadIndex = 0; dwThreadIndex < m_dwCamSequenceCount ; dwThreadIndex++)
    {
        if (m_aDispThreadParams[dwThreadIndex].bBusy)
        {
            *pThreadIndex = dwThreadIndex;
            return TRUE;
        }
    }

    return FALSE;

}


//------------------------------------------
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventDetected++;

}



//------------------------------------------
//              MyCallback_SOF
//------------------------------------------
// Function called when the "Start of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_SOF(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOF_EventDetected++;

}



//------------------------------------------
//              MyCallback_EOF
//------------------------------------------
// Function called when the "End of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_EOF(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOF_EventDetected++;

}


//------------------------------------------
//              MyCallback_EOT1
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 1
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_EOT1(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT1_EventDetected++;

}



//------------------------------------------
//              MyCallback_EOT2
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 2
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_EOT2(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT2_EventDetected++;

}



//------------------------------------------
//              MyCallback_EOT3
//------------------------------------------
// Function called when the "End of TRANSFER"
// event occurs on channel # 3
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::MyCallback_EOT3(void *pContext)
{
CIFC_PC2V_CamSwitchDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT3_EventDetected++;

}



//------------------------------------------
//              ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ReadAndClearEvents(DWORD dwCamIndex)
{


    if (m_dwIsSOT_EventDetected > 0)
    {
        m_dwIsSOT_EventDetected--;
        m_bWasSOT_EventDetected = TRUE;
    }
    else
    {
        m_bWasSOT_EventDetected = FALSE;
    }

    if (m_dwIsSOF_EventDetected > 0)
    {
        m_dwIsSOF_EventDetected--;
        m_bWasSOF_EventDetected = TRUE;
    }
    else
    {
        m_bWasSOF_EventDetected = FALSE;
    }

    if (m_dwIsEOF_EventDetected > 0)
    {
        m_dwIsEOF_EventDetected--;
        m_bWasEOF_EventDetected = TRUE;
    }
    else
    {
        m_bWasEOF_EventDetected = FALSE;
    }

    if ((dwCamIndex == 0) || (dwCamIndex == 3))
    {
        if (m_dwIsEOT1_EventDetected > 0)
        {
            m_dwIsEOT1_EventDetected--;
            m_bWasEOT1_EventDetected = TRUE;
        }
        else
        {
            m_bWasEOT1_EventDetected = FALSE;
        }
    }

    if ((dwCamIndex == 1) || (dwCamIndex == 4))
    {
        if (m_dwIsEOT2_EventDetected > 0)
        {
            m_dwIsEOT2_EventDetected--;
            m_bWasEOT2_EventDetected = TRUE;
        }
        else
        {
            m_bWasEOT2_EventDetected = FALSE;
        }
    }

    if ((dwCamIndex == 2) || (dwCamIndex == 5))
    {
        if (m_dwIsEOT3_EventDetected > 0)
        {
            m_dwIsEOT3_EventDetected--;
            m_bWasEOT3_EventDetected = TRUE;
        }
        else
        {
            m_bWasEOT3_EventDetected = FALSE;
        }
    }

}




//-----------------------------------------------
//            OnInitDialog
//-----------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::OnInitDialog()
{
CString strToShow;
DWORD dwCamIndex;


    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog

    SetIcon(m_hIcon, TRUE);             // Set big icon
    SetIcon(m_hIcon, FALSE);            // Set small icon

    // Keep the handle of all the Camera Red Light windows

    m_ahCamLightOn[0] = m_StaticLightCam1.m_hWnd;
    m_ahCamLightOn[1] = m_StaticLightCam2.m_hWnd;
    m_ahCamLightOn[2] = m_StaticLightCam3.m_hWnd;
    m_ahCamLightOn[3] = m_StaticLightCam4.m_hWnd;
    m_ahCamLightOn[4] = m_StaticLightCam5.m_hWnd;
    m_ahCamLightOn[5] = m_StaticLightCam6.m_hWnd;

    // Keep a ptr to all the Camera display windows

    m_apCamDisplay[0] = &m_StaticDisplayCam1;
    m_apCamDisplay[1] = &m_StaticDisplayCam2;
    m_apCamDisplay[2] = &m_StaticDisplayCam3;
    m_apCamDisplay[3] = &m_StaticDisplayCam4;
    m_apCamDisplay[4] = &m_StaticDisplayCam5;
    m_apCamDisplay[5] = &m_StaticDisplayCam6;

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

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate capture memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes an IFC Image connection object for all cameras

    if (InitIFC_ImageConnection() == FALSE)
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

    // Init Camera Switching Sequence variables and Edit Box

    m_EditCamSeq.SetWindowText("1-2-3-4-5-6");
    OnButtonCamSeq();

    // Create an acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        strToShow.Format("Acquisition Thread For Camera # %d", dwCamIndex + 1);
        m_apAcqThread[dwCamIndex] = new CThread(strToShow);
        if (m_apAcqThread[dwCamIndex] == NULL)
        {
            AfxMessageBox(_T("Could not start the processing thread !!!"));
            EndDialog(7);
            return FALSE;
        }

        m_apAcqThread[dwCamIndex]->SetPriority(THREAD_PRIORITY_NORMAL);
        m_apAcqThread[dwCamIndex]->CallThis(ThreadAcqProc);
    }

    // Create a display thread

    strToShow.Format("Display Thread");
    m_pDisplayThread = new CThread(strToShow);
    if (m_pDisplayThread == NULL)
    {
        AfxMessageBox(_T("Could not start the display thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pDisplayThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pDisplayThread->CallThis(ThreadDisplayProc);

    return TRUE;            // return TRUE  unless you set the focus to a control

}






//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::InitIFC_Capture()
{
CAM_ATTR attrib;
CICamera *pCam;


    // First, try to find and use the default configuration file "p2vtest.txt"

    m_pBrdMod = (CPCVision2 *)IfxCreateCaptureModule("P2V", 0, "p2vtest.txt");       // Use PC2-Vision board # 0
    if (m_pBrdMod == NULL)
    {
        // Failed to find and use the default configuration file "p2vtest.txt"
        // Ask user to select a camera type for each port

        m_pBrdMod = (CPCVision2 *)IfxCreateCaptureModule("P2V", 0);       // Use PC2-Vsion board # 0
        if (m_pBrdMod == NULL)
        {
            AfxMessageBox(_T("Can't find PC2Vision board in the system !!!"));
            return FALSE;
        }

        pCam = m_pBrdMod->GetCam(0);

        CCamSelDlg CamDlg(this, pCam);
        CamDlg.DoModal();

        // Keep selected port and camera type

        SetPortAndCamType(CamDlg.m_pszCurCamera);
    }
    else
    {
        // Display all ports

        pCam = m_pBrdMod->GetCam(0);
        pCam->GetAttr(&attrib);
        SetPortAndCamType(attrib.camName);
    }

    return TRUE;

}




//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::SetPortAndCamType(char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;
DWORD dwCamIndex;



    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        // Get a Camera object from all ports

        m_apCam[dwCamIndex] = m_pBrdMod->GetCam(dwCamIndex);

        // Assign the selected camera type to this port

        m_apCam[dwCamIndex]->SetCameraType(pszCamType);

        // Set a new PLL gain and mode optimised for camera switching

        m_apCam[dwCamIndex]->SetAcqParam(P2V_PLL_GAIN, 0x35);
    }

    // Show camera type

    m_EditCamType.SetWindowText(pszCamType);

    // Keep attributes

    m_apCam[0]->GetAttr(&attr);

    m_dwCamSizeX    = attr.dwWidth;
    m_dwCamSizeY    = attr.dwHeight;
    m_dwPixBitDepth = attr.dwBitsPerPixel;
    m_CamColor      = attr.color;
    m_dwImageSize   = attr.dwWidth * attr.dwHeight * attr.dwBytesPerPixel;

    // Determine if triggered mode is used

    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
    {
        m_bTriggerMode = TRUE;
    }
    else
    {
        m_bTriggerMode = FALSE;
    }

}




//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::InitIFC_Callback()
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
BOOL CIFC_PC2V_CamSwitchDlg::InitIFC_ImageConnection()
{
CImgSink *imgSink;
HWND hDisplayWnd;
DWORD dwCamIndex;


    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        hDisplayWnd = m_apCamDisplay[dwCamIndex]->GetSafeHwnd();

        m_apImageConnection[dwCamIndex] = IfxCreateImgConn(m_pHostCapMemory,
                                                           (WORD)m_dwCamSizeX,
                                                           (WORD)m_dwCamSizeY,
                                                           (WORD)m_dwPixBitDepth,
                                                           hDisplayWnd,
                                                           m_CamColor,
                                                           IFC_DIB_SINK,
                                                           NULL, ICAP_INTR_EOF);

        // Scale the image to fit the display window

        if (m_apImageConnection[dwCamIndex])
        {
            imgSink = m_apImageConnection[dwCamIndex]->GetSink();

            imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
        }
        else
            return FALSE;
    }

    return TRUE;

}






//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_CamSwitchDlg::ReleaseIFC_ImageConnection()
{
DWORD dwCamIndex;


    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_apImageConnection[dwCamIndex])
        {
            delete m_apImageConnection[dwCamIndex];
            m_apImageConnection[dwCamIndex] = NULL;
        }
    }

}


//------------------------------------------
//          AllocateCaptureMemory
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    dwAllocSize = m_dwImageSize * BUFFER_COUNT;

    m_pHostCapMemory = (BYTE *)malloc(dwAllocSize);
    if (m_pHostCapMemory == NULL)
        return FALSE;

    m_CapMemLockHandle = m_pBrdMod->LockMem(m_pHostCapMemory, dwAllocSize);

    return TRUE;
}




//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ReleaseCaptureMemory()
{

    if (m_pHostCapMemory)
    {
        m_pBrdMod->UnLockMem(m_CapMemLockHandle);
        free(m_pHostCapMemory);
    }

    m_pHostCapMemory = NULL;

}




//-----------------------------------------------
//            OnPaint
//-----------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//-----------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnPaint() 
{
DWORD dwCamIndex;
CString strDummy;


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

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            if (m_abCameraUsage[dwCamIndex] == TRUE)       // Camera active in sequence ?
            {
                m_apImageConnection[dwCamIndex]->Display();
                DrawWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
            }
            else
            {
                ClearDisplay(dwCamIndex);
                EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
            }

            DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0, 0, 0), FALSE, strDummy);
        }


        if (m_bClearDisplay)
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                ClearDisplay(dwCamIndex);
            }
        }

        m_dwOnPaintCounter++;
    }

}





//-----------------------------------------------
//            OnQueryDragIcon
//-----------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//-----------------------------------------------
HCURSOR CIFC_PC2V_CamSwitchDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ReleaseAll() 
{
DWORD dwCamIndex;


    // Terminate the display thread

    delete m_pDisplayThread;
    m_pDisplayThread = NULL;

    // Terminate the acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        delete m_apAcqThread[dwCamIndex];
        m_apAcqThread[dwCamIndex] = NULL;
    }

    // Release the Host capture memory for all cameras

    ReleaseCaptureMemory();

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection();

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    // Kill the Timers

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}




//-----------------------------------------------
//            OnButtonCamSeq
//-----------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonCamSeq() 
{
CString strUserCamSeq;
CString strCamNumbers("123456");        // List of all possible digits to find
CString strToShow;
int iDigitIndex;
TCHAR chCamDigit;
UINT32 CamNumber;
DWORD dwCamIndex;
DWORD dwInSeqCamIndex;


    // Read User entered sequence

    m_EditCamSeq.GetWindowText(strUserCamSeq);

    if (strUserCamSeq.GetLength() == 0)             // User entered nothing !!!
    {
        strUserCamSeq = _T("1-2");             // Enter a 2 cameras sequence
    }

    // Build the Camera Switching Sequence table by parsing user's string for digits

    m_dwCamSequenceCount = 0;
    do
    {
        iDigitIndex = strUserCamSeq.FindOneOf(strCamNumbers);   // Try to find a digit
        if (iDigitIndex != -1)
        {
            chCamDigit = strUserCamSeq.GetAt(iDigitIndex);
            strUserCamSeq.SetAt(iDigitIndex, 'A');              // Won't be a digit next loop pass
            CamNumber = chCamDigit - '0' - 1;
            if (CamNumber <= CAM_MAX_NUMBER)            // Digit must be a valid camera number
            {
                m_adwCamSequence[m_dwCamSequenceCount] = CamNumber;
                m_dwCamSequenceCount++;
            }
        }
    }
    while ((iDigitIndex != -1) && (m_dwCamSequenceCount < CAM_MAX_NUMBER));

    // Show camera sequence count

    strToShow.Format("%d", m_dwCamSequenceCount);
    m_EditSequenceCount.SetWindowText(strToShow);

    // Reformat and show camera sequence string

    strToShow = "* ";
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSequenceCount; dwCamIndex++)
    {
        strToShow += "X * ";
    }
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSequenceCount; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwCamIndex];     // Next camera in sequence
        strToShow.SetAt((dwCamIndex * 4) + 2, (char)dwInSeqCamIndex + '1');
    }
    m_EditCamSeq.SetWindowText(strToShow);

    // Disable the GUI of the unused camera(s)

    UpdateCameraGUI();

    // Determine if triggered mode is used

    m_bTriggerMode = FALSE;
    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
    {
        m_bTriggerMode = TRUE;
    }

    // OK user pressed UPDATE

    m_bCamSequenceTouched = FALSE;

}





//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ClearDisplay(DWORD dwCamIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    // Clear the Display Window

    GetWindowPosition(m_apCamDisplay[dwCamIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);
}




//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
DWORD dwCamIndex;
static BOOL bToggler;
BOOL bSnapOver;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            if (m_bClearDisplay && ((m_dwGuiCounter & 0x0F) == 0))
            {
                ClearDisplay(dwCamIndex);
                EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
                DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0, 0, 0), FALSE, strToShow);
            }
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        UpdateButtons();                // Enable or not some buttons

        m_dwGuiCounter++;

        // Draw the Trigger-To-Image lights

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            ShowEventLights(dwCamIndex, bToggler);
        }

        // Make sure a SNAP command ends correctly

        if (m_bSnapping)
        {
            bSnapOver = FALSE;

            if (! IsGrabbing())
            {
                m_pBrdMod->SwitchCameraFreeze();        // Normal SNAP end
                m_bSnapping = FALSE;
                bSnapOver = TRUE;
            }
            else if (++m_dwSnapPolling > WAIT_SNAP_MAX)     // SNAP not end, wait encore
            {
                OnButtonFreeze();
                AfxMessageBox(_T("The SNAP process did not work properly !!!"));
                bSnapOver = TRUE;
            }

            // Erase all camera lights if the SNAP is over

            if (bSnapOver)
            {
                for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
                {
                    DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0, 0, 0), FALSE, strToShow);
                }
            }
        }

        bToggler = ! bToggler;

    }

    CDialog::OnTimer(nIDEvent);

}




//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ShowStatistics() 
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

            fFrameRate *= (float)m_dwCamSequenceCount;
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
void CIFC_PC2V_CamSwitchDlg::UpdateButtons()
{

    
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! IsGrabbing());
    m_ButtonSnap.EnableWindow(! IsGrabbing());
    m_ButtonFreeze.EnableWindow(IsGrabbing());

    m_ButtonTrigger.EnableWindow(m_bTriggerMode && IsGrabbing());

    m_ButtonCamSequence.EnableWindow(! IsGrabbing());
    m_EditCamSeq.EnableWindow(! IsGrabbing());

    m_ButtonCamType.EnableWindow(! IsGrabbing());

}





//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnClose() 
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

    m_bAppClosing = TRUE;

    ReleaseAll();

    CDialog::OnClose();
}





//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonGrab() 
{
DWORD dwSeqIndex;
DWORD dwInSeqCamIndex;


    // If User change the Camera sequence or type and did not press UPDATE, do it

    if (m_bCamSequenceTouched || m_bCamTypeTouched)
    {
        OnButtonCamSeq();
        m_bCamTypeTouched = FALSE;
    }

    // Make sure there is more than one camera in the sequence

    if (m_dwCamSequenceCount < 2)
    {
        AfxMessageBox(_T("Select at least two cameras in the Camera Switch Sequence !!!"));
        return;
    }

    // Reset some statistics variables

    m_dwCurrentSeqIndex = 0;
    m_dwLastCamera      = 0;
    m_bClearDisplay     = FALSE;
    m_bSystemOverload   = FALSE;

    // Define the grab Sequence for IFC

    m_pBrdMod->SwitchCameraDefineStart();

    // Note that one thread per camera in the sequence is started and if a camera appear
    //  more than once, more than one thread will manage that camera.

    // Note also that with the P2V_GOPT_ALL_CHAN_GRAB option, we tell the Grab function to
    //  use a single ring of buffers. In camera switching mode this is more efficient
    //   than a ring of buffers for each camera.

    for (dwSeqIndex = 0; dwSeqIndex < m_dwCamSequenceCount ; dwSeqIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwSeqIndex];     // Get next camera to take care of

        m_aGrabID[dwSeqIndex] = m_apCam[dwInSeqCamIndex]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                                                    m_pHostCapMemory, BUFFER_COUNT);

        m_abIsGrabbing[dwSeqIndex] = TRUE;
    }

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the grab

    m_pBrdMod->SwitchCameraGrab();

    // Start the acquisition threads of the User's Camera Sequence

    m_dwIsSOF_EventDetected     = 0;
    m_dwIsSOT_EventDetected     = 0;
    m_dwIsSOF_EventDetected     = 0;
    m_dwIsEOF_EventDetected     = 0;
    m_dwIsEOT1_EventDetected    = 0;
    m_dwIsEOT2_EventDetected    = 0;
    m_dwIsEOT3_EventDetected    = 0;

    for (dwSeqIndex = 0; dwSeqIndex < m_dwCamSequenceCount; dwSeqIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwSeqIndex];     // Get next camera to take care of

        m_aAcqThreadParams[dwSeqIndex].pMyClass         = this;
        m_aAcqThreadParams[dwSeqIndex].dwMyThreadIndex  = dwSeqIndex;
        m_aAcqThreadParams[dwSeqIndex].dwMyCameraIndex  = dwInSeqCamIndex;
        m_aAcqThreadParams[dwSeqIndex].dwCamSeqCount    = m_dwCamSequenceCount;

        m_apAcqThread[dwSeqIndex]->AwakeThread(&m_aAcqThreadParams[dwSeqIndex]);

        m_aDispThreadParams[dwSeqIndex].bBusy = FALSE;
    }

    // Draw a BLUE border around the Camera in the sequence

    for (dwSeqIndex = 0; dwSeqIndex < CAM_MAX_NUMBER; dwSeqIndex++)
    {
        if (m_abCameraUsage[dwSeqIndex])
        {
            DrawWindowBorder(m_apCamDisplay[dwSeqIndex]->m_hWnd);
        }
        else
        {
            EraseWindowBorder(m_apCamDisplay[dwSeqIndex]->m_hWnd);
        }
    }
}





//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonSnap() 
{
DWORD dwSeqIndex;
DWORD dwInSeqCamIndex;


    // If User change the Camera sequence or type and did not press UPDATE, do it

    if (m_bCamSequenceTouched || m_bCamTypeTouched)
    {
        OnButtonCamSeq();
        m_bCamTypeTouched = FALSE;
    }

    // Make sure there is more than one camera in the sequence

    if (m_dwCamSequenceCount < 2)
    {
        AfxMessageBox(_T("Select at least two cameras in the Camera Switch Sequence !!!"));
        return;
    }

    // Reset some statistics variables

    m_dwCurrentSeqIndex = 0;
    m_dwLastCamera      = 0;
    m_bClearDisplay     = FALSE;
    m_bSystemOverload   = FALSE;

    // Define the grab Sequence for IFC

    m_pBrdMod->SwitchCameraDefineStart();

    // Note that one thread per camera in the sequence is started and if a camera appear
    //  more than once, more than one thread will manage that camera.

    // Note also that with the P2V_GOPT_ALL_CHAN_GRAB option, we tell the Grab function to
    //  use a single ring of buffers. In camera switching mode this is more efficient
    //   than a ring of buffers for each camera.

    for (dwSeqIndex = 0; dwSeqIndex < m_dwCamSequenceCount; dwSeqIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwSeqIndex];     // Get next camera to take care of

        m_aGrabID[dwSeqIndex] = m_apCam[dwInSeqCamIndex]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                                                m_pHostCapMemory, BUFFER_COUNT);

        m_abIsGrabbing[dwSeqIndex] = TRUE;
    }

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the snap (note that the GUI timer will end the snap process)

    m_dwSnapPolling = 0;
    m_bSnapping     = TRUE;
    m_pBrdMod->SwitchCameraSnap(m_dwCamSequenceCount);

    // Start the acquisition threads of the User's Camera Sequence

    m_dwIsSOF_EventDetected     = 0;
    m_dwIsSOT_EventDetected     = 0;
    m_dwIsSOF_EventDetected     = 0;
    m_dwIsEOF_EventDetected     = 0;
    m_dwIsEOT1_EventDetected    = 0;
    m_dwIsEOT2_EventDetected    = 0;
    m_dwIsEOT3_EventDetected    = 0;

    for (dwSeqIndex = 0; dwSeqIndex < m_dwCamSequenceCount; dwSeqIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwSeqIndex];     // Get next camera to take care of

        m_aAcqThreadParams[dwSeqIndex].pMyClass         = this;
        m_aAcqThreadParams[dwSeqIndex].dwMyThreadIndex  = dwSeqIndex;
        m_aAcqThreadParams[dwSeqIndex].dwMyCameraIndex  = dwInSeqCamIndex;
        m_aAcqThreadParams[dwSeqIndex].dwCamSeqCount    = m_dwCamSequenceCount;

        m_apAcqThread[dwSeqIndex]->AwakeThread(&m_aAcqThreadParams[dwSeqIndex]);

        m_aDispThreadParams[dwSeqIndex].bBusy = FALSE;
    }

    // Draw a BLUE border around the Camera in the sequence

    for (dwSeqIndex = 0; dwSeqIndex < CAM_MAX_NUMBER; dwSeqIndex++)
    {
        if (m_abCameraUsage[dwSeqIndex])
        {
            DrawWindowBorder(m_apCamDisplay[dwSeqIndex]->m_hWnd);
        }
        else
        {
            EraseWindowBorder(m_apCamDisplay[dwSeqIndex]->m_hWnd);
        }
    }

}


//------------------------------------------
//          OnButtonTrigger()
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonTrigger() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;
DWORD dwInSeqCamIndex;
DWORD dwCamIndex;


  
    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[0]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    for (dwCamIndex = 0; dwCamIndex < m_dwCamSequenceCount ; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwCamIndex];     // Get next camera to take care of

        m_apCam[dwInSeqCamIndex]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd
        m_apCam[dwInSeqCamIndex]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command
    }

    // Raise the flag indicating that the SOT event occured

    m_dwIsSOT_EventDetected++;

    if (bTriggerSrcWasExternal)
    {
        for (dwCamIndex = 0; dwCamIndex < m_dwCamSequenceCount ; dwCamIndex++)
        {
            dwInSeqCamIndex = m_adwCamSequence[dwCamIndex];     // Get next camera to take care of

            m_apCam[dwInSeqCamIndex]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
        }
    }

}




//------------------------------------------
//          IsGrabbing()
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchDlg::IsGrabbing() 
{
DWORD dwCamIndex;

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER ; dwCamIndex++)
    {
        if (m_abIsGrabbing[dwCamIndex])
        {
            return TRUE;
        }
    }

    return FALSE;

}




//------------------------------------------
//          UpdateCameraGUI()
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::UpdateCameraGUI() 
{
DWORD dwCamIndex;
DWORD dwInSeqCamIndex;


    // Build a table of the camera(s) used in the sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_abCameraUsage[dwCamIndex] = FALSE;
    }

    for (dwCamIndex = 0; dwCamIndex < m_dwCamSequenceCount ; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSequence[dwCamIndex];     // Get next camera to take care of
        m_abCameraUsage[dwInSeqCamIndex] = TRUE;
    }

    // Enable the Display of only the camera(s) in the User's Sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_abCameraUsage[dwCamIndex] == FALSE)
        {
            DisableDisplay(dwCamIndex);
        }
    }

}





//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonFreeze() 
{
int dwCamIndex;
CString strDummy;


    if (IsGrabbing())
    {
        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0, 0, 0), FALSE, strDummy);
            EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
            m_abIsGrabbing[dwCamIndex] = FALSE;
        }

        m_pBrdMod->SwitchCameraFreeze();

    }

}



//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}



//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::ShowEventLights(DWORD dwCamIndex, BOOL bToggler)
{
CString strTheText;


    // Event detection indicators

    if (IsGrabbing())
    {
        //-------------------------Show TRIGGER EVENT presence light

        if (m_bTriggerMode == FALSE)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);           // No (black) light
        }
        else if (m_bWasSOT_EventDetected)
        {
            strTheText = _T("Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);         // Green light
        }
        else
        {
            strTheText = _T("No Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        //-------------------------Show START OF FRAME presence light

        if (m_bWasSOF_EventDetected)
        {
            strTheText = _T("Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);         // Green light
        }
        else
        {
            strTheText = _T("No Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        //-------------------------Show END OF FRAME presence light

        if (m_bWasEOF_EventDetected)
        {
            strTheText = _T("Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);         // Green light
        }
        else
        {
            strTheText = _T("No Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        //-------------------------Show END OF TRANSFER presence light (channel # 1)

        if ((m_abCameraUsage[0] == FALSE) && (m_abCameraUsage[3] == FALSE))
        {
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);          // No (black) light
        }
        else if (m_bWasEOT1_EventDetected)
        {
            strTheText = _T("Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else if ((dwCamIndex == 0) || (dwCamIndex == 3))
        {
            strTheText = _T("No Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }

        //-------------------------Show END OF TRANSFER presence light (channel # 2)

        if ((m_abCameraUsage[1] == FALSE) && (m_abCameraUsage[4] == FALSE))
        {
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);          // No (black) light
        }
        else if (m_bWasEOT2_EventDetected)
        {
            strTheText = _T("Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else if ((dwCamIndex == 1) || (dwCamIndex == 4))
        {
            strTheText = _T("No Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }

        //-------------------------Show END OF TRANSFER presence light (channel # 3)

        if ((m_abCameraUsage[2] == FALSE) && (m_abCameraUsage[5] == FALSE))
        {
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);          // No (black) light
        }
        else if (m_bWasEOT3_EventDetected)
        {
            strTheText = _T("Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else if ((dwCamIndex == 2) || (dwCamIndex == 5))
        {
            strTheText = _T("No Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
        DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
        DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
        DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
        DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
        DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);       // No (black) light
    }

}




//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_CamSwitchDlg::DrawWindowBorder(HWND hWnd)
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
//          EraseWindowBorder()
//------------------------------------------
// This function draw a neutral color border
//  around the view window.
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::EraseWindowBorder(HWND hWnd)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
CPen *pOldPen;
CPen *MyPen;
RECT rectToDraw;


    // Set-up GDI objects

    MyPen = new CPen(PS_SOLID, 3, MyDC.GetBkColor());       // Use DC backgroud color

    pOldPen = MyDC.SelectObject(MyPen);
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
//              DisableDisplay
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::DisableDisplay(DWORD dwCamIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(GRAY_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    // Paint in GREY the Display Window

    GetWindowPosition(m_apCamDisplay[dwCamIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);

    GdiFlush();

}



//------------------------------------------
//          OnChangeEditCamSeq
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnChangeEditCamSeq() 
{

    m_bCamSequenceTouched = TRUE;

}



//------------------------------------------
//          OnButtonCamType
//------------------------------------------
void CIFC_PC2V_CamSwitchDlg::OnButtonCamType() 
{

    if (IsGrabbing())
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[0]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory();

        ReleaseIFC_ImageConnection();

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection() == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        m_bCamTypeTouched = TRUE;

    }
}

