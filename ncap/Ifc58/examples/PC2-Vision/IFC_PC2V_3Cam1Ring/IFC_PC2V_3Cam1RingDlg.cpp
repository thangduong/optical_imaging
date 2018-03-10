//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3Cam1RingDlg.cpp
//
//  BIRTH DATE:     July 2003
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
//                  Simultaneous acquisition and display of three genlocked
//                  cameras in planar mode in a single ring of acquisition buffers.
//
//                  Planar mode means that the three images are at three
//                  different locations in memory.
//
//                  In this demo IFC thinks that it is grabbing from a single
//                  RGB camera but the three colors signals could be in fact
//                  three monochrome signals coming from three cameras.
//------------------------------------------------------------------------------
// NOTES ON IFC PARAMETERS:
//
//                  In order for this demo to work as planned, here is a
//                  list of some key IFC parameters and their required settings:
//
//      P2V_MASTER_HSYNC    = IFC_ENABLE - enable HSync output to genlocked all 3 cameras
//      P_PIXEL_COLOR       = IFC_RGB_PLANAR
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"		                // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "ConnSelDlg.h"                     // Connector Selector Dialog Box

#include "IFC_PC2V_3Cam1Ring.h"
#include "IFC_PC2V_3Cam1RingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_3Cam1RingDlg::CIFC_PC2V_3Cam1RingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_3Cam1RingDlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CIFC_PC2V_3Cam1RingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod   = NULL;
    m_GrabID    = NULL;
    m_pCam      = NULL;

    m_apImageConnection[0] = NULL;
    m_apImageConnection[1] = NULL;
    m_apImageConnection[2] = NULL;

    m_pIntCallback_SOT  = NULL;
    m_pIntCallback_SOF  = NULL;
    m_pIntCallback_EOF  = NULL;
    m_pIntCallback_EOT1 = NULL;
    m_pIntCallback_EOT2 = NULL;
    m_pIntCallback_EOT3 = NULL;

    m_bIsGrabbing       = FALSE;
    m_bAppClosing       = FALSE;
    m_bSystemOverload   = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwImageSize       = 0;

    m_dwFrameCounter                = 0;
    m_dwFrameNotDisplayedCounter    = 0;
    m_dwSkippedFieldCounter         = 0;

    m_pAcqThread        = NULL;
    m_pDisplayThread    = NULL;
    m_pHostCapMemory    = NULL;

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

    m_bTriggerMode = FALSE;

}



//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_3Cam1RingDlg)
	DDX_Control(pDX, IDC_EDIT_ND, m_EditNotDisplayed);
	DDX_Control(pDX, IDC_STATIC_EOT_LIGHT3, m_StaticEOT3Light);
	DDX_Control(pDX, IDC_STATIC_EOT_LIGHT2, m_StaticEOT2Light);
	DDX_Control(pDX, IDC_STATIC_EOT_LIGHT, m_StaticEOT1Light);
	DDX_Control(pDX, IDC_STATIC_EOF_LIGHT, m_StaticEOFLight);
	DDX_Control(pDX, IDC_STATIC_SOF_LIGHT, m_StaticSOFLight);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_SKF, m_EditSkippedField);
	DDX_Control(pDX, IDC_EDIT_LF, m_EditLostFrame);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCurrentCamera);
	DDX_Control(pDX, IDC_EDIT_CONN, m_EditConnector);
	DDX_Control(pDX, IDC_STATIC_DISPLAY3, m_StaticDisplay3);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplay2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplay1);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	//}}AFX_DATA_MAP
}





BEGIN_MESSAGE_MAP(CIFC_PC2V_3Cam1RingDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_3Cam1RingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_3Cam1RingDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;
CString strToShow;
int iSeqNum[3];
int iFrameCountToGrab;
HIFCGRAB GrabID;
CICamera *pMyCamera;
BYTE *pHostBuffer[3];
DWORD dwPlanarScan;
DWORD dwAwaitedFrameSeqNum;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    // To alleviate the code, keep useful local variables

    GrabID              = pMyClass->m_GrabID;
    pMyCamera           = pMyClass->m_pCam;
    iFrameCountToGrab   = pMyClass->m_iFrameCountToGrab;

    dwAwaitedFrameSeqNum = 0;
    do
    {
        // Wait for 3 cameras frames ready in Host capture memory

        for (dwPlanarScan = 0; dwPlanarScan < 3; dwPlanarScan++)
        {
            iSeqNum[dwPlanarScan] = pMyCamera->GrabWaitFrameEx(GrabID, &pHostBuffer[dwPlanarScan],
                                                dwAwaitedFrameSeqNum + dwPlanarScan, WAIT_ACQ_MAX_MSEC, TRUE);
        }

        // Take care of the "Trigger To Image" events flags

        pMyClass->ReadAndClearEvents();

        if (iSeqNum[0] != -1)
        {
            // Take care of Statistics

            pMyClass->m_MeasureFramePeriod.TagTime();

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

            // Display all frames if possible

            // If the last 3 buffers are not waiting to be displayed,
            //  flag it to be displayed, otherwise, release the 3 buffers
            //   immediately (will never be displayed)
            // Finally wake-up the Display thread.

            for (dwPlanarScan = 0; dwPlanarScan < 3; dwPlanarScan++)
            {
                if (pMyClass->m_aDispThreadParams[dwPlanarScan].bBusy == FALSE)
                {
                    pMyClass->m_aDispThreadParams[dwPlanarScan].GrabID          = GrabID;
                    pMyClass->m_aDispThreadParams[dwPlanarScan].pTheBuffer      = pHostBuffer[dwPlanarScan];
                    pMyClass->m_aDispThreadParams[dwPlanarScan].iBufferIndex    = iSeqNum[dwPlanarScan];
                    pMyClass->m_aDispThreadParams[dwPlanarScan].bBusy           = TRUE;

                    pMyClass->m_bSystemOverload = FALSE;
                }
                else
                {
                    // Release the frames back into the acquisition buffer ring

                    pMyCamera->GrabRelease(GrabID, iSeqNum[dwPlanarScan]);
                    pMyClass->m_dwFrameNotDisplayedCounter++;
                    pMyClass->m_bSystemOverload = TRUE;
                }

                pMyClass->m_pDisplayThread->AwakeThread(pMyClass);

            }

            // Determine if another frame is to be expected

            if (iFrameCountToGrab != IFC_INFINITE_FRAMES)
            {
                iFrameCountToGrab -= 3;
                if (iFrameCountToGrab == 0)
                {
                    pMyClass->m_bIsGrabbing = FALSE;
                    pMyCamera->Freeze();
                }
            }

            dwAwaitedFrameSeqNum += 3;

        }

    } while (pMyClass->m_bIsGrabbing);

    // Return control to the calling thread
}







//------------------------------------------
//              ThreadDisplayProc
//------------------------------------------
// Called by the display thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_3Cam1RingDlg).
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_3Cam1RingDlg  *pMyClass;
int                     iSeqNum;
HIFCGRAB                GrabID;
BYTE                    * pHostBufferImage;
DWORD                   dwPlanarScan;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    // Is buffer ready to be to displayed ?

    for (dwPlanarScan = 0; dwPlanarScan < 3; dwPlanarScan++)
    {
        if (pMyClass->m_aDispThreadParams[dwPlanarScan].bBusy == TRUE)
        {
            // Get the information associated with the buffer and channel to display

            iSeqNum             = pMyClass->m_aDispThreadParams[dwPlanarScan].iBufferIndex;
            pHostBufferImage    = pMyClass->m_aDispThreadParams[dwPlanarScan].pTheBuffer;
            GrabID              = pMyClass->m_aDispThreadParams[dwPlanarScan].GrabID;

            // Update the address associated with the image source to point
            // to the image we just acquired

            pMyClass->m_apImageConnection[dwPlanarScan]->GetSrc()->SetBufferAddr(pHostBufferImage);

            // Display the frame in it's window

            pMyClass->m_apImageConnection[dwPlanarScan]->Display();

            // Release the frame back into the acquisition buffer ring

            pMyClass->m_pCam->GrabRelease(GrabID, iSeqNum);

            // Flag the buffer as displayed

            pMyClass->m_aDispThreadParams[dwPlanarScan].bBusy = FALSE;

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
void CIFC_PC2V_3Cam1RingDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

}



//------------------------------------------
//              MyCallback_SOF
//------------------------------------------
// Function called when the "Start of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::MyCallback_SOF(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOF_EventCounter++;

}



//------------------------------------------
//              MyCallback_EOF
//------------------------------------------
// Function called when the "End of FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::MyCallback_EOF(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

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
void CIFC_PC2V_3Cam1RingDlg::MyCallback_EOT1(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

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
void CIFC_PC2V_3Cam1RingDlg::MyCallback_EOT2(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

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
void CIFC_PC2V_3Cam1RingDlg::MyCallback_EOT3(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT3_EventCounter++;

}



//------------------------------------------
//              MyCallback_SKF
//------------------------------------------
// Function called when the "SKIPPED FRAME"
// event occurs
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::MyCallback_SKF(void *pContext)
{
CIFC_PC2V_3Cam1RingDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3Cam1RingDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    pMyClass->m_dwSkippedFieldCounter++;

}




//------------------------------------------
//              ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ReadAndClearEvents() 
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
BOOL CIFC_PC2V_3Cam1RingDlg::OnInitDialog()
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

    // Allocate Host capture memory for all cameras

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate capture memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes an IFC Image connection object for all cameras

    m_apImageConnection[0] = InitIFC_ImageConnection(&m_StaticDisplay1, 0);
    if (m_apImageConnection[0] == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_apImageConnection[1] = InitIFC_ImageConnection(&m_StaticDisplay2, 1);
    if (m_apImageConnection[1] == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_apImageConnection[2] = InitIFC_ImageConnection(&m_StaticDisplay3, 2);
    if (m_apImageConnection[2] == NULL)
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

    // Create an acquisition thread

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
BOOL CIFC_PC2V_3Cam1RingDlg::InitIFC_Capture()
{
CICamera *pCam;
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

        pCam = m_pBrdMod->GetCam(0);

        CConnSelDlg CamDlg(this, pCam);
        CamDlg.DoModal();

        // Keep selected connector and camera type

        SetConnectorAndCamType(CamDlg.m_dwCurConn, CamDlg.m_pszCurCamera);
    }
    else
    {
        // Keep connector 0

        pCam = m_pBrdMod->GetCam(0);
        pCam->GetAttr(&attrib);
        SetConnectorAndCamType(0, attrib.camName);
    }

    return TRUE;
}




//------------------------------------------
//         SetConnectorAndCamType
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::SetConnectorAndCamType(DWORD dwConnector, char *pszCamType)
{
CAM_ATTR attr;


    // Get a CICamera object from first camera in group
    // Tell IFC we are in three camera planar mode
    // Assign the selected camera type to all three port

    if (dwConnector == 0)
    {
        m_pCam = m_pBrdMod->GetCam(0);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(1);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(2);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(0);
        m_EditConnector.SetWindowText("1");
    }
    else
    {
        m_pCam = m_pBrdMod->GetCam(3);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(4);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(5);

        m_pCam->SetCameraType(pszCamType);
        m_pCam->SetAcqParam(P_PIXEL_COLOR,IFC_RGB_PLANAR);

        m_pCam = m_pBrdMod->GetCam(3);
        m_EditConnector.SetWindowText("2");
    }

    // Show camera type

    m_EditCurrentCamera.SetWindowText(pszCamType);

    // Keep attributes of camera zero

    m_pCam->GetAttr(&attr);

    m_dwCamSizeX    = attr.dwWidth;
    m_dwCamSizeY    = attr.dwHeight;
    m_dwPixBitDepth = attr.dwBitsPerPixel;
    m_CamColor      = attr.color;
    m_dwImageSize   = m_dwCamSizeX * m_dwCamSizeY * attr.dwBytesPerPixel;

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
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_3Cam1RingDlg::InitIFC_Callback()
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

    // Want a callback on the SKIPPED FIELD

    m_pIntCallback_SKF = m_pBrdMod->CreateIntrCallback(P2V_INTR_SKIPPED_FIELD, MyCallback_SKF, this);

    if (m_pIntCallback_SKF == NULL)
        return FALSE;


    return TRUE;

}






//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_3Cam1RingDlg::InitIFC_ImageConnection(CStatic *pDisplayWindow, DWORD dwCamNumber)
{
CImgConn *ImgConn;
HWND    hDisplayWnd;

    hDisplayWnd = pDisplayWindow->GetSafeHwnd();

    ImgConn = IfxCreateImgConn(m_pHostCapMemory, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY,
                                (WORD)m_dwPixBitDepth, hDisplayWnd, m_CamColor, IFC_DIB_SINK,
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
void CIFC_PC2V_3Cam1RingDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

	delete m_pBrdMod;
	m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ReleaseIFC_Callback()
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

    ExceptCode= m_pIntCallback_SKF->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_SKF);
    m_pIntCallback_SKF = NULL;

}






//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ReleaseIFC_ImageConnection(DWORD dwCamNumber)
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
BOOL CIFC_PC2V_3Cam1RingDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    dwAllocSize = m_dwImageSize * BUFFER_COUNT * 3;
    if (dwAllocSize == 0)
    {
        return FALSE;
    }

    m_pHostCapMemory = (BYTE *)malloc(dwAllocSize);
    if (m_pHostCapMemory == NULL)
    {
        return FALSE;
    }

    m_CapMemLockHandle = m_pBrdMod->LockMem(m_pHostCapMemory, dwAllocSize);

    return TRUE;

}



//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ReleaseCaptureMemory()
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
void CIFC_PC2V_3Cam1RingDlg::ReleaseAll()
{

    // Terminate the display thread

    delete m_pDisplayThread;
    m_pDisplayThread = NULL;

    // Terminate the acquisition thread

    delete m_pAcqThread;
    m_pAcqThread = NULL;

    // Release the Host capture memory

    ReleaseCaptureMemory();

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ImageConnection(0);
    ReleaseIFC_ImageConnection(1);
    ReleaseIFC_ImageConnection(2);

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
void CIFC_PC2V_3Cam1RingDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

	// Clear Display Window of camera # 1
    
	GetWindowPosition(m_StaticDisplay1.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

	// Clear Display Window of camera # 2
    
	GetWindowPosition(m_StaticDisplay2.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

	// Clear Display Window of camera # 3
    
	GetWindowPosition(m_StaticDisplay3.GetSafeHwnd(), &RectDraw);
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
BOOL CIFC_PC2V_3Cam1RingDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//            OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnPaint() 
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

        m_apImageConnection[0]->Display();
        m_apImageConnection[1]->Display();
        m_apImageConnection[2]->Display();

        if (m_bClearDisplay)
        {
            ClearDisplay();
        }

        DrawWindowBorder(m_StaticDisplay1.m_hWnd);
        DrawWindowBorder(m_StaticDisplay2.m_hWnd);
        DrawWindowBorder(m_StaticDisplay3.m_hWnd);

        m_dwOnPaintCounter++;
	}
}



//------------------------------------------
//            OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_3Cam1RingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ShowStatistics() 
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
    m_EditLostFrame.SetWindowText(strToShow);

    // Show frame not acquired (skipped field callback) count

    strToShow.Format("%d", m_dwSkippedFieldCounter);
    m_EditSkippedField.SetWindowText(strToShow);

    // Show frame not displayed count

    strToShow.Format("%d", m_dwFrameNotDisplayedCounter);
    m_EditNotDisplayed.SetWindowText(strToShow);

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}


//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strTheText;


    // Event detection indicators

    if (m_bIsGrabbing)
    {
        //-------------------------Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            strTheText = _T("Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);         // Green light
        }
        else if (! m_bTriggerMode)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);           // No light
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

        if (m_bWasEOT1_EventDetected)
        {
            strTheText = _T("Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }

        //-------------------------Show END OF TRANSFER presence light (channel # 2)

        if (m_bWasEOT2_EventDetected)
        {
            strTheText = _T("Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }

        //-------------------------Show END OF TRANSFER presence light (channel # 3)

        if (m_bWasEOT3_EventDetected)
        {
            strTheText = _T("Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText); // Yellow light
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);  // No light
        DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);
        DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);
        DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);
        DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);
        DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);
    }

    bToggler = ! bToggler;

}


//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_3Cam1RingDlg::DrawWindowBorder(HWND hWnd)
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
//              OnButtonCam
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonCam() 
{
CConnSelDlg ConnDlg(this, m_pCam);


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    if (ConnDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetConnectorAndCamType(ConnDlg.m_dwCurConn, ConnDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory();

        ReleaseIFC_ImageConnection(0);
        ReleaseIFC_ImageConnection(1);
        ReleaseIFC_ImageConnection(2);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        // Initializes an IFC Image connection object for all cameras

        m_apImageConnection[0] = InitIFC_ImageConnection(&m_StaticDisplay1, 0);
        if (m_apImageConnection[0] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        m_apImageConnection[1] = InitIFC_ImageConnection(&m_StaticDisplay2, 1);
        if (m_apImageConnection[1] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        m_apImageConnection[2] = InitIFC_ImageConnection(&m_StaticDisplay3, 2);
        if (m_apImageConnection[2] == NULL)
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
void CIFC_PC2V_3Cam1RingDlg::OnClose() 
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
void CIFC_PC2V_3Cam1RingDlg::OnTimer(UINT nIDEvent) 
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
            DrawWindowBorder(m_StaticDisplay1.m_hWnd);
            DrawWindowBorder(m_StaticDisplay2.m_hWnd);
            DrawWindowBorder(m_StaticDisplay3.m_hWnd);
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        UpdateButtons();                    // Enable or not some buttons

        ShowEventLights();                  // Show "Trigger TO Image" lights

        m_dwGuiCounter++;
    }

    CDialog::OnTimer(nIDEvent);
}




//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay                 = FALSE;
    m_bSystemOverload               = FALSE;
    m_aDispThreadParams[0].bBusy    = FALSE;
    m_aDispThreadParams[1].bBusy    = FALSE;
    m_aDispThreadParams[2].bBusy    = FALSE;

    m_iFrameCountToGrab = 3;

    m_GrabID = m_pCam->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_pHostCapMemory,
                             BUFFER_COUNT * 3, m_iFrameCountToGrab);

    // Start the acquisition thread

    m_bIsGrabbing = TRUE;

    m_pAcqThread->AwakeThread(this);
}





//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonGrab() 
{

    // Start the acquisition

    m_dwFrameCounter                = 0;
    m_dwSkippedFieldCounter         = 0;
    m_dwFrameNotDisplayedCounter    = 0;

    m_bSystemOverload               = FALSE;
    m_bClearDisplay                 = FALSE;
    m_aDispThreadParams[0].bBusy    = FALSE;
    m_aDispThreadParams[1].bBusy    = FALSE;
    m_aDispThreadParams[2].bBusy    = FALSE;

    m_iFrameCountToGrab = IFC_INFINITE_FRAMES;

    m_GrabID = m_pCam->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_pHostCapMemory,
                             BUFFER_COUNT * 3, m_iFrameCountToGrab);

    // Start the acquisition thread

    m_bIsGrabbing = TRUE;

    m_pAcqThread->AwakeThread(this);

}




//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonFreeze() 
{

    m_pCam->Freeze();

    m_bIsGrabbing = FALSE;

}



//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonTrigger() 
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
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_3Cam1RingDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
