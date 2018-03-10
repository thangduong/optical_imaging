//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_FrameDelayDlg.cpp
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
//                  Up to six cameras capture an image at the
//                  same moment and then are acquired sequentially.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_FrameDelay.h"
#include "IFC_PC2V_FrameDelayDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//-----------------------------------------------
//            Constructor
//-----------------------------------------------
CIFC_PC2V_FrameDelayDlg::CIFC_PC2V_FrameDelayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_FrameDelayDlg::IDD, pParent)
{
DWORD dwCamIndex;


	//{{AFX_DATA_INIT(CIFC_PC2V_FrameDelayDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pAcqThread        = NULL;
    m_pHostCapMemory    = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_apImageConnection[dwCamIndex] = NULL;
        m_apCam[dwCamIndex]             = NULL;
    }

    m_dwCamSizeX    = 0;
    m_dwCamSizeY    = 0;
    m_dwPixBitDepth = 0;
    m_dwImageSize   = 0;
    m_CamColor      = IFC_MONO;

    m_pIntCallback_SOT  = NULL;

    m_bIsGrabbing           = FALSE;
    m_bAppClosing           = FALSE;
    m_bCamSequenceTouched   = FALSE;

    m_dwIsSOT_EventCounter = 0;
    m_bWasSOT_EventDetected = FALSE;

}



//-----------------------------------------------
//            DoDataExchange
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_FrameDelayDlg)
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM4, m_StaticLightCam4);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM3, m_StaticLightCam3);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM5, m_StaticLightCam5);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM2, m_StaticLightCam2);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM6, m_StaticLightCam6);
	DDX_Control(pDX, IDC_STATIC_LIGHT_CAM1, m_StaticLightCam1);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_RADIO_EXT_0, m_RadioExt_0);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM, m_EditCamType);
	DDX_Control(pDX, IDC_EDIT_CAM_SEQ_SOFT, m_EditCamSeqSoftTrig);
	DDX_Control(pDX, IDC_EDIT_CAM_SEQ_1, m_EditCamSeqExtTrig1);
	DDX_Control(pDX, IDC_EDIT_CAM_SEQ_0, m_EditCamSeqExtTrig0);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	DDX_Control(pDX, IDC_STATIC_DISPLAY4, m_StaticDisplayCam4);
	DDX_Control(pDX, IDC_STATIC_DISPLAY5, m_StaticDisplayCam5);
	DDX_Control(pDX, IDC_STATIC_DISPLAY3, m_StaticDisplayCam3);
	DDX_Control(pDX, IDC_STATIC_DISPLAY6, m_StaticDisplayCam6);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplayCam2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplayCam1);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_FrameDelayDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_FrameDelayDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM, OnButtonTypeCam)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdateCamSequence)
	ON_BN_CLICKED(IDC_RADIO_EXT_0, OnRadioExt0)
	ON_BN_CLICKED(IDC_RADIO_EXT_1, OnRadioExt1)
	ON_BN_CLICKED(IDC_RADIO_SOFT, OnRadioSoft)
	ON_BN_CLICKED(IDC_RADIO_ALTERNATE, OnRadioAlternate)
	ON_EN_CHANGE(IDC_EDIT_CAM_SEQ_0, OnChangeEditCamSeq0)
	ON_EN_CHANGE(IDC_EDIT_CAM_SEQ_1, OnChangeEditCamSeq1)
	ON_EN_CHANGE(IDC_EDIT_CAM_SEQ_SOFT, OnChangeEditCamSeqSoft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_FrameDelayDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_FrameDelayDlg *pMyClass;
CString                 strToShow;
CPCVision2              *pBrdMod;
CImgConn                *pImageConnect;
ACQ_THREAD_PARAM        *pMyParams;
TRIGGER_SOURCE          MyTrigSource;
IFC_TRIG_SRC_TYPE       IFC_TrigSource;
BYTE                    *pHostBuffer;
BYTE                    *pImage;
DWORD                   dwCamCount;
DWORD                   dwCamIndex;
DWORD                   dwTheCamera;
DWORD                   *pdwCamSequence;
BOOL                    bIsGrabbing;
BOOL                    bAlternatorMode;
static BOOL             bSrcAlternator;


    // Get my parameters

    pMyParams = (ACQ_THREAD_PARAM *)pContext;

    // A static function has no access to it's own class, need a ptr to it

    pMyClass        = pMyParams->pMyClass;
    MyTrigSource    = pMyParams->TrigSrc;
    bIsGrabbing     = pMyParams->bGrabbing;

    if (MyTrigSource == SRC_EXT_TRIG_0)
    {
        IFC_TrigSource  = IFC_EXT0_TRIG;
        bAlternatorMode = FALSE;
    }
    else if (MyTrigSource == SRC_EXT_TRIG_1)
    {
        IFC_TrigSource  = IFC_EXT1_TRIG;
        bAlternatorMode = FALSE;
    }
    else if (MyTrigSource == SRC_SOFT_TRIG)
    {
        IFC_TrigSource  = IFC_SOFT_TRIG;
        bAlternatorMode = FALSE;
    }
    else if (MyTrigSource == ALTERNATE_TRIG_0_1)
    {
        bAlternatorMode = TRUE;
    }
    else
    {
        IFC_TrigSource  = IFC_EXT0_TRIG;
        bAlternatorMode = FALSE;
    }

    // To alleviate the code, keep useful local variables

    pBrdMod     = pMyClass->m_pBrdMod;
    pHostBuffer = pMyClass->m_pHostCapMemory;

    // Tell IFC the camera sequence for all three trigger sources

    pBrdMod->SetFrameDelaySequence(pMyClass->m_adwCamSeqExtTrig_0, pMyClass->m_dwCamSeqCountExtTrig_0, IFC_EXT0_TRIG);
    pBrdMod->SetFrameDelaySequence(pMyClass->m_adwCamSeqExtTrig_1, pMyClass->m_dwCamSeqCountExtTrig_1, IFC_EXT1_TRIG);
    pBrdMod->SetFrameDelaySequence(pMyClass->m_adwCamSeqSoftTrig, pMyClass->m_dwCamSeqCountSoftTrig, IFC_SOFT_TRIG);

    while (pMyClass->m_bIsGrabbing)
    {

        // Determine camera sequence and trigger source

        if (bAlternatorMode)
        {
            if (bSrcAlternator)
            {
                IFC_TrigSource = IFC_EXT0_TRIG;
            }
            else
            {
                IFC_TrigSource = IFC_EXT1_TRIG;
            }
        }

        switch (IFC_TrigSource)
        {
            case IFC_EXT0_TRIG:
            {
                dwCamCount      = pMyClass->m_dwCamSeqCountExtTrig_0;
                pdwCamSequence  = pMyClass->m_adwCamSeqExtTrig_0;
                break;
            }
            case IFC_EXT1_TRIG:
            {
                dwCamCount      = pMyClass->m_dwCamSeqCountExtTrig_1;
                pdwCamSequence  = pMyClass->m_adwCamSeqExtTrig_1;
                break;
            }
            case IFC_SOFT_TRIG:
            {
                dwCamCount      = pMyClass->m_dwCamSeqCountSoftTrig;
                pdwCamSequence  = pMyClass->m_adwCamSeqSoftTrig;
                break;
            }
        }

        // Start the acquisition

        pBrdMod->FrameDelaySnap(IFC_TrigSource, pHostBuffer, 0, 0,
                                (short)pMyClass->m_dwCamSizeX,
                                (short)pMyClass->m_dwCamSizeY, 0);

        // Wait for the sequence ready in Host capture memory

        if (pBrdMod->FrameDelayWait(WAIT_ACQ_MAX_MSEC))
        {
            // Take care of Statistics

            pMyClass->m_MeasureFramePeriod.TagTime();

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

            // Determine image buffer pointer and show the image

            for (dwCamIndex = 0; dwCamIndex < dwCamCount; dwCamIndex++)
            {
                dwTheCamera     = pdwCamSequence[dwCamIndex];
                pImage          = pHostBuffer + (dwCamIndex * pMyClass->m_dwImageSize);
                pImageConnect   = pMyClass->m_apImageConnection[dwTheCamera];

                // Update the address associated with the image source to point
                // to the frame we just acquired

                pImageConnect->GetSrc()->SetBufferAddr(pImage);

                // Display the  frame in our client window

                pImageConnect->Display();
            }

            // Light OFF all the camera lights

            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                pMyClass->DrawRectangleLight(pMyClass->m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strToShow);
            }

            // Light ON the camera in this sequence

            for (dwCamIndex = 0; dwCamIndex < dwCamCount; dwCamIndex++)
            {
                pMyClass->DrawRectangleLight(pMyClass->m_ahCamLightOn[pdwCamSequence[dwCamIndex]], RGB(0,0xFF,0), FALSE, strToShow);
            }

        }   // Wait end of acquisition

        // Read the Trigger event

        pMyClass->ReadAndClearEvents();

        // Toggle the external trigger source if in alternating grab mode

        if (bAlternatorMode)
        {
            bSrcAlternator = ! bSrcAlternator;
        }

        // If we are SNAPing, terminate the thread

        if (! bIsGrabbing)
        {
            pMyClass->m_bIsGrabbing = FALSE;
        }

    }       // while (grabbing)...

    // Return control to the calling thread
}





//------------------------------------------
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_FrameDelayDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_FrameDelayDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

}



//-----------------------------------------------
//            OnInitDialog
//-----------------------------------------------
BOOL CIFC_PC2V_FrameDelayDlg::OnInitDialog()
{
CString strToShow;
DWORD dwCamIndex;


    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog

    SetIcon(m_hIcon, TRUE);                 // Set big icon
    SetIcon(m_hIcon, FALSE);                // Set small icon

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

    // Allocate the Host capture memory

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate host memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes an IFC Image connection object for all cameras

    if (InitIFC_ImageConnection() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC Image Connection object !!!"));
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

    m_pAcqThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pAcqThread->CallThis(ThreadAcqProc);

    // Init Trigger source radio buttons

    m_TrigSource = SRC_EXT_TRIG_0;
    m_RadioExt_0.SetCheck(BST_CHECKED);

    // Init Camera Switching Sequence variables and Edit Box

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        strToShow += ('0' + (char)dwCamIndex + 1);
        strToShow += "-";
        m_adwCamSeqExtTrig_0[dwCamIndex] = dwCamIndex;
        m_adwCamSeqExtTrig_1[dwCamIndex] = dwCamIndex;
        m_adwCamSeqSoftTrig[dwCamIndex] = dwCamIndex;
    }
    m_EditCamSeqExtTrig0.SetWindowText(strToShow);         // Show camera sequence
    m_EditCamSeqExtTrig1.SetWindowText(strToShow);         // Show camera sequence
    m_EditCamSeqSoftTrig.SetWindowText(strToShow);         // Show camera sequence

    m_dwCamSeqCountExtTrig_0 = CAM_MAX_NUMBER;
    m_dwCamSeqCountExtTrig_1 = CAM_MAX_NUMBER;
    m_dwCamSeqCountSoftTrig = CAM_MAX_NUMBER;

    return TRUE;  // return TRUE  unless you set the focus to a control
}




//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_FrameDelayDlg::InitIFC_Capture()
{
CAM_ATTR attrib;
CICamera *pCam;
DWORD dwCamIndex;


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

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            pCam = m_pBrdMod->GetCam(dwCamIndex);

            CCamSelDlg CamDlg(this, pCam, dwCamIndex);
            CamDlg.DoModal();

            // Keep selected port and camera type

            SetCamType(CamDlg.m_pszCurCamera);
        }
    }
    else
    {
        // Display all ports

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            pCam = m_pBrdMod->GetCam(dwCamIndex);
            pCam->GetAttr(&attrib);
            SetCamType(attrib.camName);
        }
    }

    return TRUE;

}




//------------------------------------------
//              SetCamType
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::SetCamType(char *pszCamType)
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

}



//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_FrameDelayDlg::InitIFC_Callback()
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
BOOL CIFC_PC2V_FrameDelayDlg::InitIFC_ImageConnection()
{
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
                                                          IFC_DIB_SINK, NULL, ICAP_INTR_EOF);

        // Scale the image to fit the display window

        if (m_apImageConnection[dwCamIndex])
        {
            CImgSink *imgSink = m_apImageConnection[dwCamIndex]->GetSink();

            imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
        }
        else
        {
            return FALSE;
        }
    }

    return TRUE;

}





//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_FrameDelayDlg::ReleaseIFC_ImageConnection()
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
BOOL CIFC_PC2V_FrameDelayDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    // Determine the total buffer size

    dwAllocSize = m_dwImageSize * CAM_MAX_NUMBER;
    if (dwAllocSize == 0)
        return FALSE;

    // Allocate and lock the memory

    m_pHostCapMemory = (BYTE *)malloc(dwAllocSize);
    if (m_pHostCapMemory == NULL)
        return FALSE;

    m_CapMemLockHandle = m_pBrdMod->LockMem(m_pHostCapMemory, dwAllocSize);

    return TRUE;
}



//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ReleaseCaptureMemory()
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
void CIFC_PC2V_FrameDelayDlg::OnPaint() 
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
            // Draw a BLUE border around the Camera in the sequence

            if (m_abCamUsageTotal[dwCamIndex])
            {
                DrawWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);

                // Redraw the last live image

                m_apImageConnection[dwCamIndex]->Display();
            }
            else
            {
                EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
                ClearDisplay(dwCamIndex);
            }

            // Shutt-off the camera lights if not grabbing

            if (! m_bIsGrabbing)
            {
                DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strDummy);
            }

            if (m_bClearDisplay)
            {
                ClearDisplay(dwCamIndex);
            }

        }

        ShowEventLights();

        m_dwOnPaintCounter++;
    }

}

//-----------------------------------------------
//            OnQueryDragIcon
//-----------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//-----------------------------------------------
HCURSOR CIFC_PC2V_FrameDelayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ReleaseAll() 
{


    // Terminate the acquisition thread

    delete m_pAcqThread;
    m_pAcqThread = NULL;

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



//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_FrameDelayDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_FrameDelayDlg::ClearDisplay(DWORD dwCamIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_apCamDisplay[dwCamIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);
}





//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
DWORD dwCamIndex;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        if (m_bClearDisplay && ((m_dwGuiCounter & 0x0F) == 0))
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strToShow);
                ClearDisplay(dwCamIndex);
            }
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        ShowEventLights();

        UpdateButtons();                    // Enable or not some buttons

        m_dwGuiCounter++;
    }

    CDialog::OnTimer(nIDEvent);
}



//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ShowStatistics() 
{
float fFrameRate;
CString strToShow;


    if (! m_bIsGrabbing)
    {
        m_EditFrameRate.SetWindowText( _T("*****"));
    }
    else
    {
        // Compute and show acquisition frame rate

        fFrameRate = m_MeasureFramePeriod.GetTime();
        if (fFrameRate != 0.0)
        {
            fFrameRate = (float)1.0 / fFrameRate;
            strToShow.Format("%.2f", fFrameRate);
            m_EditFrameRate.SetWindowText(strToShow);
        }
    }

}



//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::UpdateButtons()
{

    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);

}


//------------------------------------------
//          UpdateCameraGUI()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::UpdateCameraGUI() 
{
DWORD dwCamIndex;


    // Enable the Display of only the camera(s) in the User's Sequence
    // Also, Last camera in sequence take care of statistics

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_abCamUsageTotal[dwCamIndex] == TRUE)
        {
            m_dwStatCamera = dwCamIndex;
        }
        else
        {
            DisableDisplay(dwCamIndex);
        }
    }

}


//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnClose() 
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
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    // Determine if triggered mode is used

    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) != IFC_ENABLE)
    {
        AfxMessageBox(_T("Trigger is not enabled, cannot proceed !!!"));
        return;
    }

    // Check if user changed a camera sequence whithout clicking UPDATE

    if (m_bCamSequenceTouched)
    {
        OnButtonUpdateCamSequence();
    }

    // Determine camera usage

    BuildCamUsageTable();

    // Disable the GUI of the unused camera(s)

    UpdateCameraGUI();

    // Init acquisition related variables

    m_dwSkippedFrameCounter = 0;

    m_bClearDisplay = FALSE;

    // Start the acquisition thread

    m_bIsGrabbing = TRUE;
    m_dwIsSOT_EventCounter = 0;

    m_AcqThreadParams.pMyClass  = this;
    m_AcqThreadParams.TrigSrc   = m_TrigSource;
    m_AcqThreadParams.bGrabbing = FALSE;

    m_pAcqThread->AwakeThread(&m_AcqThreadParams);

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonGrab() 
{
DWORD dwCamIndex;


    // Determine if triggered mode is used

    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) != IFC_ENABLE)
    {
        AfxMessageBox(_T("Trigger is not enabled, please choose another camera type"));
        return;
    }

    // Check if user changed a camera sequence whithout clicking UPDATE

    if (m_bCamSequenceTouched)
    {
        OnButtonUpdateCamSequence();
    }

    // Determine camera usage

    BuildCamUsageTable();

    // Disable the GUI of the unused camera(s)

    UpdateCameraGUI();

    // Init acquisition related variables

    m_dwSkippedFrameCounter = 0;

    m_bClearDisplay = FALSE;

    m_dwFrameCounter = 0;

    // Start the acquisition thread

    m_bIsGrabbing = TRUE;
    m_dwIsSOT_EventCounter = 0;

    m_AcqThreadParams.pMyClass  = this;
    m_AcqThreadParams.TrigSrc   = m_TrigSource;
    m_AcqThreadParams.bGrabbing = TRUE;

    m_pAcqThread->AwakeThread(&m_AcqThreadParams);

    // Draw a BLUE border around the Camera in the sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_abCamUsageTotal[dwCamIndex])
        {
            DrawWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
        }
        else
        {
            EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
        }
    }

}





//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonFreeze() 
{

    // Stop the acquisition thread

    m_bIsGrabbing = FALSE;

}





//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}



//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::DrawWindowBorder(HWND hWnd)
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
void CIFC_PC2V_FrameDelayDlg::EraseWindowBorder(HWND hWnd)
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
void CIFC_PC2V_FrameDelayDlg::DisableDisplay(DWORD dwCamIndex)
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
//            ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ReadAndClearEvents()
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

}



//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strDummy;


    if (m_bIsGrabbing)
    {
        // Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), FALSE, strDummy);      // Green light
        }
        else if (bToggler)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0xFF, 0xFF, 0), FALSE, strDummy);   // Yellow flashing
        }
        else
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);         // Yellow flashing
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);             // No light
    }

    bToggler = ! bToggler;

}





//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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






//-----------------------------------------------
//            OnButtonUpdateCamSequence
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonUpdateCamSequence() 
{

    UpdateCamSeqExtTrig_0();
    UpdateCamSeqExtTrig_1();
    UpdateCamSeqSoftTrig();

    BuildCamUsageTable(); 
    m_bCamSequenceTouched = FALSE;

}






//-----------------------------------------------
//            UpdateCamSeqExtTrig_0
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::UpdateCamSeqExtTrig_0() 
{
CString strUserCamSeq;
CString strCamNumbers("123456");        // List of all possible digits to find
CString strToShow;
int iDigitIndex;
TCHAR chCamDigit;
UINT32 CamNumber;
DWORD dwCamIndex;
DWORD dwInSeqCamIndex;


    // In case of bad user entry, init to all camera selected in sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_adwCamSeqExtTrig_0[dwCamIndex] = dwCamIndex;
        m_abCamUsageExtTrig_0[dwCamIndex] = FALSE;
    }

    // Read User entered sequence

    m_EditCamSeqExtTrig0.GetWindowText(strUserCamSeq);

    if (strUserCamSeq.GetLength() == 0)             // User entered nothing !!!
    {
        strUserCamSeq = _T("1-2");             // Enter a 2 cameras sequence
    }

    // Build the Camera Switching Sequence table by parsing user's string for digits

    m_dwCamSeqCountExtTrig_0 = 0;
    do
    {
        iDigitIndex = strUserCamSeq.FindOneOf(strCamNumbers);   // Try to find a digit
        if (iDigitIndex != -1)
        {
            chCamDigit = strUserCamSeq.GetAt(iDigitIndex);
            strUserCamSeq.SetAt(iDigitIndex, 'A');              // Won't be a digit next loop pass
            CamNumber = chCamDigit - '0' - 1;
            if ((CamNumber <= CAM_MAX_NUMBER) && (m_abCamUsageExtTrig_0[CamNumber] == FALSE))
            {
                m_adwCamSeqExtTrig_0[m_dwCamSeqCountExtTrig_0] = CamNumber;
                m_abCamUsageExtTrig_0[CamNumber] = TRUE;
                m_dwCamSeqCountExtTrig_0++;
            }
        }
    }
    while ((iDigitIndex != -1) && (m_dwCamSeqCountExtTrig_0 < CAM_MAX_NUMBER));

    // Reformat and show new camera sequence string

    strToShow = "* ";
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountExtTrig_0; dwCamIndex++)
    {
        strToShow += "X * ";
    }
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountExtTrig_0; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSeqExtTrig_0[dwCamIndex];     // Next camera in sequence
        strToShow.SetAt((dwCamIndex * 4) + 2, (char)dwInSeqCamIndex + '1');
    }
    m_EditCamSeqExtTrig0.SetWindowText(strToShow);

}



//-----------------------------------------------
//            UpdateCamSeqExtTrig_1
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::UpdateCamSeqExtTrig_1() 
{
CString strUserCamSeq;
CString strCamNumbers("123456");        // List of all possible digits to find
CString strToShow;
int iDigitIndex;
TCHAR chCamDigit;
UINT32 CamNumber;
DWORD dwCamIndex;
DWORD dwInSeqCamIndex;


    // In case of bad user entry, init to all camera selected in sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_adwCamSeqExtTrig_1[dwCamIndex] = dwCamIndex;
        m_abCamUsageExtTrig_1[dwCamIndex] = FALSE;
    }

    // Read User entered sequence

    m_EditCamSeqExtTrig1.GetWindowText(strUserCamSeq);

    if (strUserCamSeq.GetLength() == 0)             // User entered nothing !!!
    {
        strUserCamSeq = _T("1-2");             // Enter a 2 cameras sequence
    }

    // Build the Camera Switching Sequence table by parsing user's string for digits

    m_dwCamSeqCountExtTrig_1 = 0;
    do
    {
        iDigitIndex = strUserCamSeq.FindOneOf(strCamNumbers);   // Try to find a digit
        if (iDigitIndex != -1)
        {
            chCamDigit = strUserCamSeq.GetAt(iDigitIndex);
            strUserCamSeq.SetAt(iDigitIndex, 'A');              // Won't be a digit next loop pass
            CamNumber = chCamDigit - '0' - 1;
            if ((CamNumber <= CAM_MAX_NUMBER) && (m_abCamUsageExtTrig_1[CamNumber] == FALSE))
            {
                m_adwCamSeqExtTrig_1[m_dwCamSeqCountExtTrig_1] = CamNumber;
                m_abCamUsageExtTrig_1[CamNumber] = TRUE;
                m_dwCamSeqCountExtTrig_1++;
            }
        }
    }
    while ((iDigitIndex != -1) && (m_dwCamSeqCountExtTrig_1 < CAM_MAX_NUMBER));

    // Reformat and show new camera sequence string

    strToShow = "* ";
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountExtTrig_1; dwCamIndex++)
    {
        strToShow += "X * ";
    }
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountExtTrig_1; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSeqExtTrig_1[dwCamIndex];     // Next camera in sequence
        strToShow.SetAt((dwCamIndex * 4) + 2, (char)dwInSeqCamIndex + '1');
    }
    m_EditCamSeqExtTrig1.SetWindowText(strToShow);

}



//-----------------------------------------------
//            UpdateCamSeqSoftTrig
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::UpdateCamSeqSoftTrig() 
{
CString strUserCamSeq;
CString strCamNumbers("123456");        // List of all possible digits to find
CString strToShow;
int iDigitIndex;
TCHAR chCamDigit;
UINT32 CamNumber;
DWORD dwCamIndex;
DWORD dwInSeqCamIndex;


    // In case of bad user entry, init to all camera selected in sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_adwCamSeqSoftTrig[dwCamIndex] = dwCamIndex;
        m_abCamUsageSoftTrig[dwCamIndex] = FALSE;
    }

    // Read User entered sequence

    m_EditCamSeqSoftTrig.GetWindowText(strUserCamSeq);

    if (strUserCamSeq.GetLength() == 0)             // User entered nothing !!!
    {
        strUserCamSeq = _T("1-2");             // Enter a 2 cameras sequence
    }

    // Build the Camera Switching Sequence table by parsing user's string for digits

    m_dwCamSeqCountSoftTrig = 0;
    do
    {
        iDigitIndex = strUserCamSeq.FindOneOf(strCamNumbers);   // Try to find a digit
        if (iDigitIndex != -1)
        {
            chCamDigit = strUserCamSeq.GetAt(iDigitIndex);
            strUserCamSeq.SetAt(iDigitIndex, 'A');              // Won't be a digit next loop pass
            CamNumber = chCamDigit - '0' - 1;
            if ((CamNumber <= CAM_MAX_NUMBER) && (m_abCamUsageSoftTrig[CamNumber] == FALSE))
            {
                m_adwCamSeqSoftTrig[m_dwCamSeqCountSoftTrig] = CamNumber;
                m_abCamUsageSoftTrig[CamNumber] = TRUE;
                m_dwCamSeqCountSoftTrig++;
            }
        }
    }
    while ((iDigitIndex != -1) && (m_dwCamSeqCountSoftTrig < CAM_MAX_NUMBER));

    // Reformat and show new camera sequence string

    strToShow = "* ";
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountSoftTrig; dwCamIndex++)
    {
        strToShow += "X * ";
    }
    for (dwCamIndex = 0; dwCamIndex < m_dwCamSeqCountSoftTrig; dwCamIndex++)
    {
        dwInSeqCamIndex = m_adwCamSeqSoftTrig[dwCamIndex];     // Next camera in sequence
        strToShow.SetAt((dwCamIndex * 4) + 2, (char)dwInSeqCamIndex + '1');
    }
    m_EditCamSeqSoftTrig.SetWindowText(strToShow);

}





//-----------------------------------------------
//            BuildCamUsageTable
//-----------------------------------------------
// Build a table of all the camera in use
//-----------------------------------------------
void CIFC_PC2V_FrameDelayDlg::BuildCamUsageTable() 
{
DWORD dwCamIndex;


    m_dwCamSeqCountTotal = 0;

    switch (m_TrigSource)
    {
        case SRC_EXT_TRIG_0:
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                m_abCamUsageTotal[dwCamIndex] = m_abCamUsageExtTrig_0[dwCamIndex];
            }

            m_dwCamSeqCountTotal = m_dwCamSeqCountExtTrig_0;

            break;
        }
        case SRC_EXT_TRIG_1:
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                m_abCamUsageTotal[dwCamIndex] = m_abCamUsageExtTrig_1[dwCamIndex];
            }

            m_dwCamSeqCountTotal = m_dwCamSeqCountExtTrig_1;

            break;
        }
        case SRC_SOFT_TRIG:
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                m_abCamUsageTotal[dwCamIndex] = m_abCamUsageSoftTrig[dwCamIndex];
            }

            m_dwCamSeqCountTotal = m_dwCamSeqCountSoftTrig;

            break;
        }
        case ALTERNATE_TRIG_0_1:
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                m_abCamUsageTotal[dwCamIndex] = FALSE;
                if (m_abCamUsageExtTrig_0[dwCamIndex] || m_abCamUsageExtTrig_1[dwCamIndex])
                {
                    m_abCamUsageTotal[dwCamIndex] = TRUE;
                }
            }

            m_dwCamSeqCountTotal = max(m_dwCamSeqCountExtTrig_0, m_dwCamSeqCountExtTrig_1);

            break;
        }
    }

}






//------------------------------------------
//          OnButtonTypeCam()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonTypeCam() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[0], 0);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetCamType(CamDlg.m_pszCurCamera);

        // Clear the Display Window

        m_bClearDisplay = TRUE;
    }
}




//------------------------------------------
//          OnButtonTrigger()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnButtonTrigger() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[0]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    m_apCam[0]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd

    m_apCam[0]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

    // Raise the flag indicating that the SOT event occured

    m_dwIsSOT_EventCounter++;

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_apCam[0]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}



//------------------------------------------
//          OnRadioExt0()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnRadioExt0() 
{

    m_TrigSource = SRC_EXT_TRIG_0;

}



//------------------------------------------
//          OnRadioExt1()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnRadioExt1() 
{

    m_TrigSource = SRC_EXT_TRIG_1;

}



//------------------------------------------
//          OnRadioSoft()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnRadioSoft() 
{

    m_TrigSource = SRC_SOFT_TRIG;

}



//------------------------------------------
//          OnRadioAlternate()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnRadioAlternate() 
{

    m_TrigSource = ALTERNATE_TRIG_0_1;

}


//------------------------------------------
//          OnChangeEditCamSeq0()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnChangeEditCamSeq0() 
{

    m_bCamSequenceTouched = TRUE;

}


//------------------------------------------
//          OnChangeEditCamSeq1()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnChangeEditCamSeq1() 
{

    m_bCamSequenceTouched = TRUE;

}


//------------------------------------------
//          OnChangeEditCamSeqSoft()
//------------------------------------------
void CIFC_PC2V_FrameDelayDlg::OnChangeEditCamSeqSoft() 
{

    m_bCamSequenceTouched = TRUE;

}
