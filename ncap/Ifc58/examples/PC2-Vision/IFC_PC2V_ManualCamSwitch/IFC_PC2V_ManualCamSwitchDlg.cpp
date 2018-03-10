//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ManualCamSwitchDlg.cpp
//
//  BIRTH DATE:     September 2003
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
//                  Up to six asynchronous cameras are acquired sequentially
//                  using SNAPs.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_ManualCamSwitch.h"
#include "IFC_PC2V_ManualCamSwitchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//-----------------------------------------------
//            Constructor
//-----------------------------------------------
CIFC_PC2V_ManualCamSwitchDlg::CIFC_PC2V_ManualCamSwitchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_ManualCamSwitchDlg::IDD, pParent)
{
DWORD dwCamIndex;



	//{{AFX_DATA_INIT(CIFC_PC2V_ManualCamSwitchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pAcqThread        = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_apImageConnection[dwCamIndex] = NULL;
        m_apCam[dwCamIndex]             = NULL;
        m_apHostCapMemory[dwCamIndex]   = NULL;

        m_adwCamSizeX[dwCamIndex]       = 0;
        m_adwCamSizeY[dwCamIndex]       = 0;
        m_adwPixBitDepth[dwCamIndex]    = 0;
        m_adwImageSize[dwCamIndex]      = 0;
        m_aCamColor[dwCamIndex]         = IFC_MONO;
    }

    m_pIntCallback_SOT  = NULL;
    m_pIntCallback_SOF  = NULL;
    m_pIntCallback_EOF  = NULL;
    m_pIntCallback_EOT1 = NULL;
    m_pIntCallback_EOT2 = NULL;
    m_pIntCallback_EOT3 = NULL;

    m_bIsGrabbing           = FALSE;
    m_bAppClosing           = FALSE;
    m_bTriggerMode          = FALSE;
    m_bCamSequenceTouched   = FALSE;
    m_bCamTypeTouched       = FALSE;
    m_bIsPllLockWaitTouched = FALSE;

    m_dwIsSOT_EventCounter  = 0;

    m_bWasSOT_EventDetected = FALSE;

}



//-----------------------------------------------
//            DoDataExchange
//-----------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_ManualCamSwitchDlg)
	DDX_Control(pDX, IDC_EDIT_PLL_LOCK_TIME, m_EditPllLockWait);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_CAM_SEQ, m_ButtonCamSequence);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR_TOTAL, m_EditFrameRateTotal);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_SEQ_COUNT, m_EditSequenceCount);
	DDX_Control(pDX, IDC_EDIT_CAM_SEQ, m_EditCamSeq);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE6, m_ButtonCamType6);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE5, m_ButtonCamType5);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE4, m_ButtonCamType4);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE3, m_ButtonCamType3);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE2, m_ButtonCamType2);
	DDX_Control(pDX, IDC_BUTTON_CAM_TYPE1, m_ButtonCamType1);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE6, m_EditCamType6);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE5, m_EditCamType5);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE4, m_EditCamType4);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE3, m_EditCamType3);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE2, m_EditCamType2);
	DDX_Control(pDX, IDC_EDIT_CAM_TYPE1, m_EditCamType1);
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
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2V_ManualCamSwitchDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_ManualCamSwitchDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM_SEQ, OnButtonCamSeq)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_EN_CHANGE(IDC_EDIT_CAM_SEQ, OnChangeEditCamSeq)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE1, OnButtonCamType1)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE2, OnButtonCamType2)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE3, OnButtonCamType3)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE4, OnButtonCamType4)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE5, OnButtonCamType5)
	ON_BN_CLICKED(IDC_BUTTON_CAM_TYPE6, OnButtonCamType6)
	ON_EN_CHANGE(IDC_EDIT_PLL_LOCK_TIME, OnChangeEditPllLockTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PV2V_ManualCamSwitchDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_ManualCamSwitchDlg *  pMyClass;
CICamera *          pNextCamera;
CImgConn *          pImageConnect;
BYTE *              pHostBuffer;
ACQ_THREAD_PARAM *  pMyParams;
CString             strToShow;
DWORD               dwCamSeqScan;
DWORD               dwInSeqCamIndex;
DWORD               dwTheCamSeqCount;
int                 iFrameCountToGrab;

static unsigned char ucOutputPort;

    // Get my parameters

    pMyParams = (ACQ_THREAD_PARAM *)pContext;

    // A static function has no access to it's own class, need a ptr to it

    pMyClass            = pMyParams->pMyClass;
    dwTheCamSeqCount    = pMyParams->dwCamSeqCount;
    iFrameCountToGrab   = pMyParams->iFrameCountToGrab;

    while (pMyClass->m_bIsGrabbing)
    {
        for (dwCamSeqScan = 0; dwCamSeqScan < pMyClass->m_dwCamSequenceCount; dwCamSeqScan++)
        {
            // Get next camera index, it's camera and image object pointer and host buffer pointer

            dwInSeqCamIndex     = pMyClass->m_adwCamSequence[dwCamSeqScan];     // Next camera in sequence
            pNextCamera         = pMyClass->m_apCam[dwInSeqCamIndex];
            pHostBuffer         = pMyClass->m_apHostCapMemory[dwInSeqCamIndex];
            pImageConnect       = pMyClass->m_apImageConnection[dwInSeqCamIndex];

            // Connect the next camera to the acquisition channel

            pMyClass->m_pBrdMod->SetActiveCamera(pNextCamera);

            // Wait a little while to let the PLL lock onto this new video signal

            Sleep(pMyClass->m_dwPllLockWaitTime);

            // Trigger a SNAP on it and if OK display it

            if (pNextCamera->Snap(pHostBuffer))
            {
                // Take care of the Frame Rate statistic

                pMyClass->m_dwFrameCounter++;
                pMyClass->m_MeasureFramePeriod.TagTime();

                // Update the address associated with the image source to point
                // to the frame we just acquired

                pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

                // Display the frame in our client window

                pImageConnect->Display();

                // Put former camera light OFF and this camera light ON 

                pMyClass->DrawRectangleLight(pMyClass->m_ahCamLightOn[pMyClass->m_dwCurrentCamera], RGB(0, 0, 0), FALSE, strToShow);
                pMyClass->DrawRectangleLight(pMyClass->m_ahCamLightOn[dwInSeqCamIndex], RGB(0, 0xFF, 0), FALSE, strToShow);
                pMyClass->m_dwCurrentCamera = dwInSeqCamIndex;

                // Determine if another frame is to be expected

                if (iFrameCountToGrab != IFC_INFINITE_FRAMES)
                {
                    if (--iFrameCountToGrab <= 0)
                    {
                        pMyClass->m_bIsGrabbing = FALSE;       // Go out of this loop
                    }
                }

            }  // SNAP succeed

            // Read the Trigger event counters

            pMyClass->ReadAndClearEvents();

        }  // scan all cam sequence

    }  // while(GRAB)

    // Return control to the calling thread
}


//------------------------------------------
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_ManualCamSwitchDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ManualCamSwitchDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

}



//------------------------------------------
//              ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ReadAndClearEvents() 
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



//-----------------------------------------------
//            OnInitDialog
//-----------------------------------------------
BOOL CIFC_PC2V_ManualCamSwitchDlg::OnInitDialog()
{
DWORD dwCamIndex;
CString strToShow;


	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
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

    // Keep a ptr to all the Camera Type Edit Boxes

    m_apEditCameraType[0] = &m_EditCamType1;
    m_apEditCameraType[1] = &m_EditCamType2;
    m_apEditCameraType[2] = &m_EditCamType3;
    m_apEditCameraType[3] = &m_EditCamType4;
    m_apEditCameraType[4] = &m_EditCamType5;
    m_apEditCameraType[5] = &m_EditCamType6;

    // Keep a ptr to all the Camera Type Buttons

    m_apButtonCamSelect[0] = &m_ButtonCamType1;
    m_apButtonCamSelect[1] = &m_ButtonCamType2;
    m_apButtonCamSelect[2] = &m_ButtonCamType3;
    m_apButtonCamSelect[3] = &m_ButtonCamType4;
    m_apButtonCamSelect[4] = &m_ButtonCamType5;
    m_apButtonCamSelect[5] = &m_ButtonCamType6;

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

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (AllocateCaptureMemory(dwCamIndex) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
            EndDialog(7);
            return FALSE;
        }
    }

    // Initializes an IFC Image connection object for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (InitIFC_ImageConnection(dwCamIndex) == FALSE)
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

    // Init Camera Switching Sequence variables and Edit Box

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        strToShow += ('0' + (char)dwCamIndex + 1);
        strToShow += "-";
        m_adwCamSequence[dwCamIndex] = dwCamIndex;
    }
    m_EditCamSeq.SetWindowText(strToShow);         // Show camera sequence

    m_dwCurrentCamera = 0;

    m_dwPllLockWaitTime = 0;
    strToShow.Format("%d", m_dwPllLockWaitTime);
    m_EditPllLockWait.SetWindowText(strToShow);         // Show PLL lock wait delay

    m_dwCamSequenceCount = CAM_MAX_NUMBER;
    strToShow.Format("%d", m_dwCamSequenceCount);
    m_EditSequenceCount.SetWindowText(strToShow);         // Show camera sequence count

    // Create an acquisition thread

    strToShow.Format("Acquisition Thread");
    m_pAcqThread = new CThread(strToShow);
    if (m_pAcqThread == NULL)
    {
        AfxMessageBox(_T("Could not start the acquisition thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pAcqThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pAcqThread->CallThis(ThreadAcqProc);

    return TRUE;  // return TRUE  unless you set the focus to a control

}




//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_ManualCamSwitchDlg::InitIFC_Capture()
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

        pCam = m_pBrdMod->GetCam(0);

        CCamSelDlg CamDlg(this, pCam);
        CamDlg.DoModal();

        // Keep selected port and camera type

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            SetPortAndCamType(dwCamIndex, CamDlg.m_pszCurCamera);
        }
    }
    else
    {
        // Display all ports

        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            pCam = m_pBrdMod->GetCam(dwCamIndex);
            pCam->GetAttr(&attrib);
            SetPortAndCamType(dwCamIndex, attrib.camName);
        }
    }

    return TRUE;

}




//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Get a Camera object from this port

    m_apCam[dwActivePort] = m_pBrdMod->GetCam(dwActivePort);

    // Assign the selected camera type to this port and show it

    m_apCam[dwActivePort]->SetCameraType(pszCamType);
    m_apEditCameraType[dwActivePort]->SetWindowText(pszCamType);

    // Keep attributes

    m_apCam[dwActivePort]->GetAttr(&attr);

    m_adwCamSizeX[dwActivePort]     = attr.dwWidth;
    m_adwCamSizeY[dwActivePort]     = attr.dwHeight;
    m_adwPixBitDepth[dwActivePort]  = attr.dwBitsPerPixel;
    m_aCamColor[dwActivePort]       = attr.color;
    m_adwImageSize[dwActivePort]    = attr.dwWidth * attr.dwHeight * attr.dwBytesPerPixel;

    // Set a new PLL gain and mode optimised for camera switching

    m_apCam[dwActivePort]->SetAcqParam(P2V_PLL_GAIN, 0x35);

}


//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_ManualCamSwitchDlg::InitIFC_Callback()
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
BOOL CIFC_PC2V_ManualCamSwitchDlg::InitIFC_ImageConnection(DWORD dwCamNumber)
{
CImgSink *imgSink;
HWND hDisplayWnd;


    hDisplayWnd = m_apCamDisplay[dwCamNumber]->GetSafeHwnd();

    m_apImageConnection[dwCamNumber] = IfxCreateImgConn(m_apHostCapMemory[dwCamNumber],
                                                       (WORD)m_adwCamSizeX[dwCamNumber],
                                                       (WORD)m_adwCamSizeY[dwCamNumber],
                                                       (WORD)m_adwPixBitDepth[dwCamNumber],
                                                       hDisplayWnd,
                                                       m_aCamColor[dwCamNumber],
                                                       IFC_DIB_SINK,
                                                       NULL, ICAP_INTR_EOF);

    // Scale the image to fit the display window

    if (m_apImageConnection[dwCamNumber])
    {
        imgSink = m_apImageConnection[dwCamNumber]->GetSink();

        imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
    }
    else
        return FALSE;

    return TRUE;

}




//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_ManualCamSwitchDlg::ReleaseIFC_ImageConnection(DWORD dwCamNumber)
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
BOOL CIFC_PC2V_ManualCamSwitchDlg::AllocateCaptureMemory(DWORD dwCamNumber)
{
DWORD dwAllocSize;


    dwAllocSize = m_adwImageSize[dwCamNumber] * BUFFER_COUNT;

    m_apHostCapMemory[dwCamNumber] = (BYTE *)malloc(dwAllocSize);
    if (m_apHostCapMemory[dwCamNumber] == NULL)
        return FALSE;

    m_aCapMemLockHandle[dwCamNumber] = m_pBrdMod->LockMem(m_apHostCapMemory[dwCamNumber], dwAllocSize);

    return TRUE;
}




//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ReleaseCaptureMemory(DWORD dwCamNumber)
{

    if (m_apHostCapMemory[dwCamNumber])
    {
        m_pBrdMod->UnLockMem(m_aCapMemLockHandle[dwCamNumber]);
        free(m_apHostCapMemory[dwCamNumber]);
    }

    m_apHostCapMemory[dwCamNumber] = NULL;

}




//-----------------------------------------------
//            OnPaint
//-----------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//-----------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnPaint() 
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

            DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strDummy);
        }


        if (m_bClearDisplay)
        {
            for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
            {
                ClearDisplay(dwCamIndex);
            }
        }

        m_dwOnPaintCounter++;

        if (m_bIsGrabbing)
        {
            ShowEventLights();
        }

    }

}



//-----------------------------------------------
//            OnQueryDragIcon
//-----------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//-----------------------------------------------
HCURSOR CIFC_PC2V_ManualCamSwitchDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ReleaseAll() 
{
DWORD dwCamIndex;



    // Terminate the acquisition thread

    delete m_pAcqThread;
    m_pAcqThread = NULL;

    // Release the Host capture memory for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        ReleaseCaptureMemory(dwCamIndex);
    }

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
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
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_ManualCamSwitchDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_ManualCamSwitchDlg::ClearDisplay(DWORD dwCamIndex)
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
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ShowStatistics() 
{
float fFrameRate;
float fFrameRateCeiling;
float fFrameRateFloor;
CString strToShow;


    if (! m_bIsGrabbing)
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

            // Compute and show Frame Rate total

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
            m_EditFrameRateTotal.SetWindowText(strToShow);

            // Compute and show Frame Rate per camera

            fFrameRate /= (float)m_dwCamSequenceCount;
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
        }
    }

}



//------------------------------------------
//              EnableGui
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::EnableGui()
{
DWORD dwCamIndex;


    // Depending on situation, some Buttons and Edit Box are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);

    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSequence.EnableWindow(! m_bIsGrabbing);
    m_EditCamSeq.EnableWindow(! m_bIsGrabbing);

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        m_apButtonCamSelect[dwCamIndex]->EnableWindow(! m_bIsGrabbing);
    }

    m_EditPllLockWait.EnableWindow(! m_bIsGrabbing);

}





//------------------------------------------
//          UpdateCameraGUI()
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::UpdateCameraGUI() 
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
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strDummy;


    if (m_bIsGrabbing && m_bTriggerMode)
    {
        // Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), FALSE, strDummy);      // Greeen light
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
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);         // No light
    }

    bToggler = ! bToggler;

}



//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_ManualCamSwitchDlg::DrawWindowBorder(HWND hWnd)
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
void CIFC_PC2V_ManualCamSwitchDlg::EraseWindowBorder(HWND hWnd)
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
void CIFC_PC2V_ManualCamSwitchDlg::DisableDisplay(DWORD dwCamIndex)
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
//              IsTriggerModeUsed
//------------------------------------------
BOOL CIFC_PC2V_ManualCamSwitchDlg::IsTriggerModeUsed()
{
DWORD dwInSeqCamIndex;
DWORD dwCamSeqScan;


    // Determine if triggered mode is used on at least one camera in the current sequence

    for (dwCamSeqScan = 0; dwCamSeqScan < m_dwCamSequenceCount; dwCamSeqScan++)
    {
        // Get next camera index, it's camera and image object pointer and host buffer pointer

        dwInSeqCamIndex = m_adwCamSequence[dwCamSeqScan];     // Next camera in sequence

        if (m_apCam[dwInSeqCamIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
        {
            return TRUE;
        }
    }

    return FALSE;

}





//-----------------------------------------------
//            OnButtonCamSeq
//-----------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamSeq() 
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
            if (CamNumber <= CAM_MAX_NUMBER)
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

    // OK user pressed UPDATE
    
    m_bCamSequenceTouched = FALSE;

}




//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
DWORD dwCamIndex;


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
                DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strToShow);
            }
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        EnableGui();                // Enable or not some Buttons and Edit Box

        ShowEventLights();

        m_dwGuiCounter++;
    }

    CDialog::OnTimer(nIDEvent);
}




//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnClose() 
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
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonGrab() 
{
DWORD dwCamIndex;
CString strToShow;


    // Make sure there is more than one camera in the sequence

    if (m_dwCamSequenceCount < 2)
    {
        AfxMessageBox(_T("Select at least two cameras in the Camera Switch Sequence !!!"));
        return;
    }

    // If User change the Camera sequence or type and did not press UPDATE, do it

    if (m_bCamSequenceTouched || m_bCamTypeTouched)
    {
        OnButtonCamSeq();
        m_bCamTypeTouched       = FALSE;
        m_bCamSequenceTouched   = FALSE;
    }

    // Reset some statistics variables

    m_bClearDisplay = FALSE;
    m_dwFrameCounter = 0;

    // Determine if triggered mode is used

    m_bTriggerMode = IsTriggerModeUsed();

    // Start the GRAB process by waking-up the acquisition thread
    
    m_dwIsSOT_EventCounter = 0;

    m_bIsGrabbing = TRUE;

    m_AcqThreadParams.pMyClass              = this;
    m_AcqThreadParams.dwCamSeqCount         = m_dwCamSequenceCount;
    m_AcqThreadParams.iFrameCountToGrab     = IFC_INFINITE_FRAMES;

    m_pAcqThread->AwakeThread(&m_AcqThreadParams);

    // Draw a BLUE border around the Camera in the sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_abCameraUsage[dwCamIndex])
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
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonSnap() 
{
DWORD dwCamIndex;


    // Make sure there is more than one camera in the sequence

    if (m_dwCamSequenceCount < 2)
    {
        AfxMessageBox(_T("Select at least two cameras in the Camera Switch Sequence !!!"));
        return;
    }

    // If User change the Camera sequence or type and did not press UPDATE, do it

    if (m_bCamSequenceTouched || m_bCamTypeTouched)
    {
        OnButtonCamSeq();
        m_bCamTypeTouched       = FALSE;
        m_bCamSequenceTouched   = FALSE;
    }

    // Reset some statistics variables

    m_bClearDisplay = FALSE;
    m_dwFrameCounter = 0;

    // Determine if triggered mode is used

    m_bTriggerMode = IsTriggerModeUsed();

    // Start the GRAB process by waking-up the acquisition thread
    
    m_bIsGrabbing = TRUE;

    m_AcqThreadParams.pMyClass              = this;
    m_AcqThreadParams.dwCamSeqCount         = m_dwCamSequenceCount;
    m_AcqThreadParams.iFrameCountToGrab     = 1;

    m_pAcqThread->AwakeThread(&m_AcqThreadParams);

    // Draw a BLUE border around the Camera in the sequence

    for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
    {
        if (m_abCameraUsage[dwCamIndex])
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
//          OnButtonTrigger()
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonTrigger() 
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

    m_dwIsSOT_EventCounter++;

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
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonFreeze() 
{
int dwCamIndex;
CString strDummy;


    if (m_bIsGrabbing)
    {
        for (dwCamIndex = 0; dwCamIndex < CAM_MAX_NUMBER; dwCamIndex++)
        {
            DrawRectangleLight(m_ahCamLightOn[dwCamIndex], RGB(0,0,0), FALSE, strDummy);
            EraseWindowBorder(m_apCamDisplay[dwCamIndex]->m_hWnd);
        }

    m_bIsGrabbing = FALSE;

    }

}



//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}



//------------------------------------------
//          OnChangeEditCamSeq
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnChangeEditCamSeq() 
{

    m_bCamSequenceTouched = TRUE;

}



//------------------------------------------
//          OnChangeEditPllLockTime
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnChangeEditPllLockTime() 
{
CString strUser;


    m_EditPllLockWait.GetWindowText(strUser);      // Read user's entry
    m_dwPllLockWaitTime = atol(strUser);            // ASCII to binary

    m_bIsPllLockWaitTouched = TRUE;
}




//------------------------------------------
//          OnButtonCamType1
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType1() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[0]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(0, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(0);

        ReleaseIFC_ImageConnection(0);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(0) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(0) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}

//------------------------------------------
//          OnButtonCamType2
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType2() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[1]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(1, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(1);

        ReleaseIFC_ImageConnection(1);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(1) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(1) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}

//------------------------------------------
//          OnButtonCamType3
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType3() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[2]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(2, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(2);

        ReleaseIFC_ImageConnection(2);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(2) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(2) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}

//------------------------------------------
//          OnButtonCamType4
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType4() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[3]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(3, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(3);

        ReleaseIFC_ImageConnection(3);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(3) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(3) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}



//------------------------------------------
//          OnButtonCamType5
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType5() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[4]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(4, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(4);

        ReleaseIFC_ImageConnection(4);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(4) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(4) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}

//------------------------------------------
//          OnButtonCamType6
//------------------------------------------
void CIFC_PC2V_ManualCamSwitchDlg::OnButtonCamType6() 
{

    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    // Ask user to select a camera type

    CCamSelDlg CamDlg(this, m_apCam[5]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(5, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(5);

        ReleaseIFC_ImageConnection(5);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(5) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        if (InitIFC_ImageConnection(5) == FALSE)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_bClearDisplay = TRUE;

        // Trace user action

        m_bCamTypeTouched = TRUE;
    }

}



