//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3CamPlanarVerticalDlg.cpp
//
//  BIRTH DATE:     October 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.7)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Acquisition and display of 3 genlocked monochrome cameras
//                  using a single ring and a single buffer for the 3 channels.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"

#include "IFC_PC2V_3CamPlanarVertical.h"
#include "IFC_PC2V_3CamPlanarVerticalDlg.h"

#include "ConnSelDlg.h"                     // Connector Selector Dialog Box



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif






//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_3CamPlanarVerticalDlg::CIFC_PC2V_3CamPlanarVerticalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_3CamPlanarVerticalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_3CamPlanarVerticalDlg)
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

    m_dwFrameCounter                = 0;
    m_dwFrameNotDisplayedCounter    = 0;
    m_dwSkippedFieldCounter         = 0;

    m_pAcqThread        = NULL;
    m_pHostCapMemory    = NULL;
    m_pDisplayThread    = NULL;

    m_dwIsSOT_EventCounter  = FALSE;
    m_dwIsSOF_EventCounter  = FALSE;
    m_dwIsEOF_EventCounter  = FALSE;
    m_dwIsEOT1_EventCounter = FALSE;
    m_dwIsEOT2_EventCounter = FALSE;
    m_dwIsEOT3_EventCounter = FALSE;

    m_bWasSOT_EventDetected  = FALSE;
    m_bWasSOF_EventDetected  = FALSE;
    m_bWasEOF_EventDetected  = FALSE;
    m_bWasEOT1_EventDetected = FALSE;
    m_bWasEOT2_EventDetected = FALSE;
    m_bWasEOT3_EventDetected = FALSE;

}




//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_3CamPlanarVerticalDlg)
	DDX_Control(pDX, IDC_EDIT_NA, m_EditFrameNotAcquired);
	DDX_Control(pDX, IDC_EDIT_FLOST, m_EditFrameLost);
	DDX_Control(pDX, IDC_EDIT_ND, m_EditFrameNotDisplayed);
	DDX_Control(pDX, IDC_STATIC_EOT3_LIGHT, m_StaticEOT3Light);
	DDX_Control(pDX, IDC_STATIC_EOT1_LIGHT, m_StaticEOT1Light);
	DDX_Control(pDX, IDC_STATIC_EOT2_LIGHT, m_StaticEOT2Light);
	DDX_Control(pDX, IDC_STATIC_EOF_LIGHT, m_StaticEOFLight);
	DDX_Control(pDX, IDC_STATIC_SOF_LIGHT, m_StaticSOFLight);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCurrentCamera);
	DDX_Control(pDX, IDC_EDIT_CUR_CONN, m_EditConnector);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_StaticDisplay);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIFC_PC2V_3CamPlanarVerticalDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_3CamPlanarVerticalDlg)
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
void CIFC_PC2V_3CamPlanarVerticalDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pCam;
CICapMod *pBrdMod;
CImgConn *pImageConnect;
BYTE *pHostBuffer;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;   // Context is the ptr to my class

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
                pMyClass->m_dwFrameNotDisplayedCounter++;
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
// the thread of this dialog box class (CIFC_PC2V_3CamPlanarVerticalDlg).
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;
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

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_SOF(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_EOF(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_EOT1(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_EOT2(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_EOT3(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsEOT3_EventCounter++;

}



//------------------------------------------
//              MyCallback_SKF
//------------------------------------------
// Function called when the "SKIPPED FIELD"
// event occurs
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::MyCallback_SKF(void *pContext)
{
CIFC_PC2V_3CamPlanarVerticalDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_3CamPlanarVerticalDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    pMyClass->m_dwSkippedFieldCounter++;

}




//------------------------------------------
//            ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ReadAndClearEvents()
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
BOOL CIFC_PC2V_3CamPlanarVerticalDlg::OnInitDialog()
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
BOOL CIFC_PC2V_3CamPlanarVerticalDlg::InitIFC_Capture()
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

        CConnSelDlg ConnDlg(this, m_pCam);
        ConnDlg.DoModal();

        // Keep selected port and camera type

        SetConnectorAndCamType(ConnDlg.m_dwCurConn, ConnDlg.m_pszCurCamera);
    }
    else
    {
        // Keep port 0

        m_pCam = m_pBrdMod->GetCam(0);
        m_pCam->GetAttr(&attrib);
        SetConnectorAndCamType(0, attrib.camName);
    }

    return TRUE;

}




//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_3CamPlanarVerticalDlg::InitIFC_Callback()
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
CImgConn *CIFC_PC2V_3CamPlanarVerticalDlg::InitIFC_ImageConnection(HWND hWnd, CICamera *cam)
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
void CIFC_PC2V_3CamPlanarVerticalDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_3CamPlanarVerticalDlg::ReleaseIFC_ImageConnection()
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
BOOL CIFC_PC2V_3CamPlanarVerticalDlg::AllocateCaptureMemory()
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
void CIFC_PC2V_3CamPlanarVerticalDlg::ReleaseCaptureMemory()
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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnPaint() 
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
HCURSOR CIFC_PC2V_3CamPlanarVerticalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ReleaseAll()
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

}



//------------------------------------------
//         SetConnectorAndCamType
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::SetConnectorAndCamType(DWORD dwConnector, char *pszCamType)
{
CAM_ATTR attr;
double dOriginalHeight;


    // Get a CICamera object from the first port of the 3 cameras group

    if (dwConnector == 0)
    {
        m_pCam = m_pBrdMod->GetCam(0);

        m_EditConnector.SetWindowText("1");
    }
    else
    {
        m_pCam = m_pBrdMod->GetCam(3);

        m_EditConnector.SetWindowText("2");
    }

    // Assign the selected camera type and show it

    m_pCam->SetCameraType(pszCamType);

    m_EditCurrentCamera.SetWindowText(pszCamType);

    // Tell IFC to acquire three times the number of lines per buffer

    dOriginalHeight = m_pCam->GetAcqParam(P_HEIGHT_PIXELS);

    m_pCam->SetAcqParam(P_HEIGHT_PIXELS, dOriginalHeight * 3);

    // Tell IFC we are in three camera planar mode

    m_pCam->SetAcqParam(P2V_PLANAR_MODE, P2V_PLANAR_VERT);
    m_pCam->SetAcqParam(P_PIXEL_COLOR, IFC_RGB_PLANAR);

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
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ClearDisplay()
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
BOOL CIFC_PC2V_3CamPlanarVerticalDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_3CamPlanarVerticalDlg::ShowStatistics() 
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

    // Show skipped field count (frame not acquired)

    strToShow.Format("%d", m_dwSkippedFieldCounter);
    m_EditFrameNotAcquired.SetWindowText(strToShow);

    // Show frame not displayed

    strToShow.Format("%d", m_dwFrameNotDisplayedCounter);
    m_EditFrameNotDisplayed.SetWindowText(strToShow);

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing && m_bTriggerMode);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}




//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strTheText;


    if (m_bIsGrabbing)
    {
        //-----------------------------------Show START OF TRIGGER presence light

        if (m_bWasSOT_EventDetected)
        {
            strTheText = _T("Trigger");
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
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
        //-----------------------------------Show START OF FRAME presence light

        if (m_bWasSOF_EventDetected)
        {
            strTheText = _T("Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Video Begin");
            DrawRectangleLight(m_StaticSOFLight.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        //-----------------------------------Show END OF FRAME presence light

        if (m_bWasEOF_EventDetected)
        {
            strTheText = _T("Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Video End");
            DrawRectangleLight(m_StaticEOFLight.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        //-----------------------------------Show END OF TRANSFER (3) presence light

        if (m_bWasEOT1_EventDetected)
        {
            strTheText = _T("Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 1");
            DrawRectangleLight(m_StaticEOT1Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        if (m_bWasEOT2_EventDetected)
        {
            strTheText = _T("Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 2");
            DrawRectangleLight(m_StaticEOT2Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }

        if (m_bWasEOT3_EventDetected)
        {
            strTheText = _T("Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0, 0xFF, 0), TRUE, strTheText);        // Green light
        }
        else
        {
            strTheText = _T("No Memory Xfer 3");
            DrawRectangleLight(m_StaticEOT3Light.m_hWnd, RGB(0xFF, 0xFF, 0), bToggler, strTheText);  // Yellow light
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strTheText);   // No light
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
void CIFC_PC2V_3CamPlanarVerticalDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_3CamPlanarVerticalDlg::DrawWindowBorder(HWND hWnd)
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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonCam() 
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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnClose() 
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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnTimer(UINT nIDEvent) 
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
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonTrigger() 
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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonGrab() 
{

    m_dwFrameCounter                = 0;
    m_dwFrameNotDisplayedCounter    = 0;
    m_dwSkippedFieldCounter         = 0;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay = FALSE;

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
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonFreeze() 
{

    m_pCam->Freeze();	
    m_bIsGrabbing = FALSE;

}




//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_3CamPlanarVerticalDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
