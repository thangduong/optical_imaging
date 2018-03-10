//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_4BoardsDlg.cpp
//
//  BIRTH DATE:     April 2003
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
//                  Up to four PC2-Vision borads are handled concurrently
//                  and independantly.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_4Boards.h"
#include "IFC_PC2V_4BoardsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//-----------------------------------------------
//            Constructor
//-----------------------------------------------
CIFC_PC2V_4BoardsDlg::CIFC_PC2V_4BoardsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_4BoardsDlg::IDD, pParent)
{
DWORD dwBoardIndex;


	//{{AFX_DATA_INIT(CIFC_PC2V_4BoardsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // Initialises array variables

    for (dwBoardIndex = 0; dwBoardIndex < BOARD_MAX_NUMBER; dwBoardIndex++)
    {
        m_apBrdMod[dwBoardIndex]            = NULL;
        m_apCam[dwBoardIndex]               = NULL;
        m_aGrabID[dwBoardIndex]             = NULL;

        m_apImageConnection[dwBoardIndex]   = NULL;

        m_adwCamSizeX[dwBoardIndex]     = 0;
        m_adwCamSizeY[dwBoardIndex]     = 0;
        m_adwBitDepth[dwBoardIndex]     = 0;
        m_adwImageSize[dwBoardIndex]    = 0;
        m_aCamColor[dwBoardIndex]       = IFC_MONO;

        m_apHostCapMemory[dwBoardIndex]     = NULL;
        m_aCapMemLockHandle[dwBoardIndex]   = 0;

        m_adwFrameCounter[dwBoardIndex] = 0;
        m_adwSelectedPort[dwBoardIndex] = 0;

        m_apAcqThread[dwBoardIndex]     = NULL;

        m_abIsGrabbing[dwBoardIndex]    = FALSE;

        m_apAcqThread[dwBoardIndex]     = NULL;
        m_adwBoardSerial[dwBoardIndex]  = 0;
    }

    m_dwBoardCount          = 0;
    m_dwOnPaintCounter      = 0;
    m_dwLastOnPaintCounter  = 0;
    m_bSystemOverload       = FALSE;

    m_pDisplayThread        = NULL;

}






//-----------------------------------------------
//            DoDataExchange
//-----------------------------------------------
void CIFC_PC2V_4BoardsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_4BoardsDlg)
	DDX_Control(pDX, IDC_EDIT_SN3, m_EditSerialNumber3);
	DDX_Control(pDX, IDC_EDIT_SN4, m_EditSerialNumber4);
	DDX_Control(pDX, IDC_EDIT_SN2, m_EditSerialNumber2);
	DDX_Control(pDX, IDC_EDIT_SN1, m_EditSerialNumber1);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER4, m_ButtonTrigger4);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER3, m_ButtonTrigger3);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER2, m_ButtonTrigger2);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER1, m_ButtonTrigger1);
	DDX_Control(pDX, IDC_EDIT_PORT4, m_EditPort4);
	DDX_Control(pDX, IDC_EDIT_PORT3, m_EditPort3);
	DDX_Control(pDX, IDC_EDIT_PORT2, m_EditPort2);
	DDX_Control(pDX, IDC_EDIT_PORT1, m_EditPort1);
	DDX_Control(pDX, IDC_BUTTON_SNAP4, m_ButtonSnap4);
	DDX_Control(pDX, IDC_BUTTON_SNAP3, m_ButtonSnap3);
	DDX_Control(pDX, IDC_BUTTON_SNAP2, m_ButtonSnap2);
	DDX_Control(pDX, IDC_BUTTON_SNAP1, m_ButtonSnap1);
	DDX_Control(pDX, IDC_BUTTON_FREEZE4, m_ButtonFreeze4);
	DDX_Control(pDX, IDC_BUTTON_FREEZE3, m_ButtonFreeze3);
	DDX_Control(pDX, IDC_BUTTON_FREEZE2, m_ButtonFreeze2);
	DDX_Control(pDX, IDC_BUTTON_FREEZE1, m_ButtonFreeze1);
	DDX_Control(pDX, IDC_BUTTON_GRAB4, m_ButtonGrab4);
	DDX_Control(pDX, IDC_BUTTON_GRAB3, m_ButtonGrab3);
	DDX_Control(pDX, IDC_BUTTON_GRAB2, m_ButtonGrab2);
	DDX_Control(pDX, IDC_BUTTON_GRAB1, m_ButtonGrab1);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM4, m_ButtonCamType4);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM3, m_ButtonCamType3);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM2, m_ButtonCamType2);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM1, m_ButtonCamType1);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM4, m_EditCamType4);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM3, m_EditCamType3);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM2, m_EditCamType2);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM1, m_EditCamType1);
	DDX_Control(pDX, IDC_EDIT_FR_CAM4, m_EditFrameRate4);
	DDX_Control(pDX, IDC_EDIT_FR_CAM3, m_EditFrameRate3);
	DDX_Control(pDX, IDC_EDIT_FR_CAM2, m_EditFrameRate2);
	DDX_Control(pDX, IDC_EDIT_FR_CAM1, m_EditFrameRate1);
	DDX_Control(pDX, IDC_EDIT_FC_CAM4, m_EditFrameCount4);
	DDX_Control(pDX, IDC_EDIT_FC_CAM3, m_EditFrameCount3);
	DDX_Control(pDX, IDC_EDIT_FC_CAM2, m_EditFrameCount2);
	DDX_Control(pDX, IDC_EDIT_FC_CAM1, m_EditFrameCount1);
	DDX_Control(pDX, IDC_STATIC_DISPLAY4, m_StaticDisplayCam4);
	DDX_Control(pDX, IDC_STATIC_DISPLAY3, m_StaticDisplayCam3);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplayCam2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplayCam1);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2V_4BoardsDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_4BoardsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_GRAB1, OnButtonGrab1)
	ON_BN_CLICKED(IDC_BUTTON_GRAB2, OnButtonGrab2)
	ON_BN_CLICKED(IDC_BUTTON_GRAB3, OnButtonGrab3)
	ON_BN_CLICKED(IDC_BUTTON_GRAB4, OnButtonGrab4)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE1, OnButtonFreeze1)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE2, OnButtonFreeze2)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE3, OnButtonFreeze3)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE4, OnButtonFreeze4)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM1, OnButtonTypeCam1)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM2, OnButtonTypeCam2)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM3, OnButtonTypeCam3)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM4, OnButtonTypeCam4)
	ON_BN_CLICKED(IDC_BUTTON_SNAP1, OnButtonSnap1)
	ON_BN_CLICKED(IDC_BUTTON_SNAP2, OnButtonSnap2)
	ON_BN_CLICKED(IDC_BUTTON_SNAP3, OnButtonSnap3)
	ON_BN_CLICKED(IDC_BUTTON_SNAP4, OnButtonSnap4)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER1, OnButtonTrigger1)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER2, OnButtonTrigger2)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER3, OnButtonTrigger3)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER4, OnButtonTrigger4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_4BoardsDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_4BoardsDlg *pMyClass;
DWORD dwMyBoard;
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
    dwMyBoard   = pMyParams->dwMyBoardIndex;

    // To alleviate the code, keep useful local variables

    pBrdMod             = pMyClass->m_apBrdMod[dwMyBoard];
    GrabID              = pMyClass->m_aGrabID[dwMyBoard];
    pMyCamera           = pMyClass->m_apCam[dwMyBoard];
    pImageConnect       = pMyClass->m_apImageConnection[dwMyBoard];

    while (pMyClass->m_abIsGrabbing[dwMyBoard])
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pMyCamera->GrabWaitFrameEx(GrabID, &pHostBuffer, IFC_WAIT_NEWER_FRAME,
                                              WAIT_ACQ_MAX_MSEC, TRUE);

        if (iSeqNum != -1)
        {
            // Take care of Statistics

            pMyClass->m_aMeasureFramePeriod[dwMyBoard].TagTime();

            // Increment and show frame counter

            pMyClass->m_adwFrameCounter[dwMyBoard]++;
            strToShow.Format("%d", pMyClass->m_adwFrameCounter[dwMyBoard]);
            pMyClass->m_apEditFrameCount[dwMyBoard]->SetWindowText(strToShow);

            // If the last buffer is not waiting to be displayed,
            //  flag it to be displayed otherwise, release the buffer
            //   immediately (will never be displayed)

            if (pMyClass->m_aDispThreadParams[dwMyBoard].bBusy == FALSE)
            {
                pMyClass->m_aDispThreadParams[dwMyBoard].pTheBuffer     = pHostBuffer;
                pMyClass->m_aDispThreadParams[dwMyBoard].GrabID         = GrabID;
                pMyClass->m_aDispThreadParams[dwMyBoard].iBufferIndex   = iSeqNum;
                pMyClass->m_aDispThreadParams[dwMyBoard].bBusy          = TRUE;

                pMyClass->m_bSystemOverload = FALSE;
            }
            else
            {
                // Release the acquisition buffer back into the ring

                pMyCamera->GrabRelease(GrabID, iSeqNum);

                pMyClass->m_bSystemOverload = TRUE;

            }

            // Wake-up the Display thread

            pMyClass->m_pDisplayThread->AwakeThread(pMyClass);

        }
    }

    // Return control to the calling thread
}





//------------------------------------------
//              ThreadDisplayProc
//------------------------------------------
// Called by the display thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_4BoardsDlg).
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_4BoardsDlg    *pMyClass;
CImgConn                *pImageConnect;
int                     iSeqNum;
HIFCGRAB                GrabID;
BYTE                    *pHostBuffer;
DWORD                   dwBoardIndex;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_4BoardsDlg *)pContext;

    // While there is buffer ready to be to displayed

    while (pMyClass->GetBufferToDisplay(&dwBoardIndex))
    {
        // Get the information associated with the buffer and channel to display

        iSeqNum         = pMyClass->m_aDispThreadParams[dwBoardIndex].iBufferIndex;
        pHostBuffer     = pMyClass->m_aDispThreadParams[dwBoardIndex].pTheBuffer;
        GrabID          = pMyClass->m_aDispThreadParams[dwBoardIndex].GrabID;

        // Get the ImageConnection object associated with this camera

        pImageConnect = pMyClass->m_apImageConnection[dwBoardIndex];

        // Update the address associated with the image source to point
        // to the frame we just acquired

        pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

        // Display the  frame in our client window

        pImageConnect->Display();

        // Release the frame back into the active circular acquisition buffer

        pMyClass->m_apCam[dwBoardIndex]->GrabRelease(GrabID, iSeqNum);

        // Flag the buffer as displayed

        pMyClass->m_aDispThreadParams[dwBoardIndex].bBusy = FALSE;

    }

    // Return control to the calling thread
}





//------------------------------------------
//              GetBufferToDisplay
//------------------------------------------
BOOL CIFC_PC2V_4BoardsDlg::GetBufferToDisplay(DWORD *dwBoardIndex)
{
DWORD dwBoardScan;


    for (dwBoardScan = 0; dwBoardScan < m_dwBoardCount; dwBoardScan++)
    {
        if (m_aDispThreadParams[dwBoardScan].bBusy)
        {
            *dwBoardIndex = dwBoardScan;
            return TRUE;
        }
    }

    return FALSE;

}




//-----------------------------------------------
//            OnInitDialog
//-----------------------------------------------
BOOL CIFC_PC2V_4BoardsDlg::OnInitDialog()
{
CString strToShow;
DWORD dwBoardIndex;

    CDialog::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog

    SetIcon(m_hIcon, TRUE);             // Set big icon
    SetIcon(m_hIcon, FALSE);            // Set small icon

    // Keep a ptr to all the Camera display windows

    m_apCamDisplay[0] = &m_StaticDisplayCam1;
    m_apCamDisplay[1] = &m_StaticDisplayCam2;
    m_apCamDisplay[2] = &m_StaticDisplayCam3;
    m_apCamDisplay[3] = &m_StaticDisplayCam4;

    // Keep a ptr to all the Frame Count Edit Boxes

    m_apEditFrameCount[0] = &m_EditFrameCount1;
    m_apEditFrameCount[1] = &m_EditFrameCount2;
    m_apEditFrameCount[2] = &m_EditFrameCount3;
    m_apEditFrameCount[3] = &m_EditFrameCount4;

    // Keep a ptr to all the Frame Rate Edit Boxes

    m_apEditFrameRate[0] = &m_EditFrameRate1;
    m_apEditFrameRate[1] = &m_EditFrameRate2;
    m_apEditFrameRate[2] = &m_EditFrameRate3;
    m_apEditFrameRate[3] = &m_EditFrameRate4;

    // Keep a ptr to all the Port Edit Boxes

    m_apEditPort[0] = &m_EditPort1;
    m_apEditPort[1] = &m_EditPort2;
    m_apEditPort[2] = &m_EditPort3;
    m_apEditPort[3] = &m_EditPort4;

    // Keep a ptr to all the Camera Type Edit Boxes

    m_apEditCameraType[0] = &m_EditCamType1;
    m_apEditCameraType[1] = &m_EditCamType2;
    m_apEditCameraType[2] = &m_EditCamType3;
    m_apEditCameraType[3] = &m_EditCamType4;

    // Keep a ptr to all the Board Serial Number Edit Boxes

    m_apEditSerialNumber[0] = &m_EditSerialNumber1;
    m_apEditSerialNumber[1] = &m_EditSerialNumber2;
    m_apEditSerialNumber[2] = &m_EditSerialNumber3;
    m_apEditSerialNumber[3] = &m_EditSerialNumber4;

    // Keep a ptr to all the GRAB Buttons

    m_apButtonGrab[0] = &m_ButtonGrab1;
    m_apButtonGrab[1] = &m_ButtonGrab2;
    m_apButtonGrab[2] = &m_ButtonGrab3;
    m_apButtonGrab[3] = &m_ButtonGrab4;

    // Keep a ptr to all the FREEZE Buttons

    m_apButtonFreeze[0] = &m_ButtonFreeze1;
    m_apButtonFreeze[1] = &m_ButtonFreeze2;
    m_apButtonFreeze[2] = &m_ButtonFreeze3;
    m_apButtonFreeze[3] = &m_ButtonFreeze4;

    // Keep a ptr to all the SNAP Buttons

    m_apButtonSnap[0] = &m_ButtonSnap1;
    m_apButtonSnap[1] = &m_ButtonSnap2;
    m_apButtonSnap[2] = &m_ButtonSnap3;
    m_apButtonSnap[3] = &m_ButtonSnap4;

    // Keep a ptr to all the TRIGGER Buttons

    m_apButtonTrigger[0] = &m_ButtonTrigger1;
    m_apButtonTrigger[1] = &m_ButtonTrigger2;
    m_apButtonTrigger[2] = &m_ButtonTrigger3;
    m_apButtonTrigger[3] = &m_ButtonTrigger4;

    // Keep a ptr to all the Camera Type Select Buttons

    m_apButtonCamSelect[0] = &m_ButtonCamType1;
    m_apButtonCamSelect[1] = &m_ButtonCamType2;
    m_apButtonCamSelect[2] = &m_ButtonCamType3;
    m_apButtonCamSelect[3] = &m_ButtonCamType4;

    // Determine how many PC2-Vision board(s) in system and
    // initializes IFC capture module for every one

    if (InitIFC_Capture(&m_dwBoardCount) == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC capture object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Allocate Host capture memory for all cameras

    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        if (AllocateCaptureMemory(dwBoardIndex) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
            EndDialog(7);
            return FALSE;
        }
    }

    // Initializes an IFC Image connection object for all cameras

    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        m_apImageConnection[dwBoardIndex] = InitIFC_ImageConnection(dwBoardIndex);
        if (m_apImageConnection[dwBoardIndex] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
            EndDialog(7);
            return FALSE;
        }
    }

    // Init GUI related variables

    m_dwGuiCounter = 0;
    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        m_abClearDisplay[dwBoardIndex] = TRUE;
    }

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

    // Initialises the Display parameters array so that no board has an image to display yet

    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        m_aDispThreadParams[dwBoardIndex].bBusy = FALSE;
    }

    // Create an acquisition thread for all board in the system

    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        m_apAcqThread[dwBoardIndex] = new CThread;
        if (m_apAcqThread[dwBoardIndex] == NULL)
        {
            AfxMessageBox(_T("Could not start the processing thread !!!"));
            EndDialog(7);
            return FALSE;
        }

        m_apAcqThread[dwBoardIndex]->SetPriority(THREAD_PRIORITY_NORMAL);
        m_apAcqThread[dwBoardIndex]->CallThis(ThreadAcqProc);
    }

    // Create a single display thread

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
BOOL CIFC_PC2V_4BoardsDlg::InitIFC_Capture(DWORD *pdwBoardCount)
{
CICamera    *pCam;
CAM_ATTR    attrib;
DWORD       dwBoardAbsent;
DWORD       dwBoardScan;


    // Determine number of PC2-Vision boards in the system

    for (dwBoardScan = 0; dwBoardScan < BOARD_MAX_NUMBER; dwBoardScan++)
    {
        // First, try to find and use the default configuration file "p2vtest.txt"

        m_apBrdMod[dwBoardScan] = IfxCreateCaptureModule("P2V", dwBoardScan, "p2vtest.txt");
        if (m_apBrdMod[dwBoardScan] == NULL)
        {
            // Failed to find and use the default configuration file "p2vtest.txt"
            // Ask user to select a camera type

            m_apBrdMod[dwBoardScan] = IfxCreateCaptureModule("P2V", dwBoardScan);
            if (m_apBrdMod[dwBoardScan] == NULL)
            {
                break;                      // Board search is over
            }

            pCam = m_apBrdMod[dwBoardScan]->GetCam(0);

            CCamSelDlg CamDlg(this, pCam);
            CamDlg.DoModal();

            SetPortAndCamType(dwBoardScan, CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);
        }
        else
        {
            // Keep port 0

            m_apCam[dwBoardScan] = m_apBrdMod[dwBoardScan]->GetCam(0);
            m_apCam[dwBoardScan]->GetAttr(&attrib);
            SetPortAndCamType(dwBoardScan, 0, attrib.camName);
        }

        // Keep Board Serial Number

        if (m_apBrdMod[dwBoardScan]->IfxGetBoardParam(IFC_HW_SERIAL_NUM, &m_adwBoardSerial[dwBoardScan]) == FALSE)
        {
            AfxMessageBox(_T("Can't get PC2Vision board Serial Number !!!"));
            return FALSE;
        }

    }

    *pdwBoardCount = dwBoardScan;

    // Return FALSE if no board was found

    if (dwBoardScan == 0)
    {
        AfxMessageBox(_T("Can't find PC2Vision board in the system !!!"));
        return FALSE;
    }

    // Disable BUTTONS and EDIT BOXES for absent board

    for (dwBoardAbsent = dwBoardScan; dwBoardAbsent < BOARD_MAX_NUMBER; dwBoardAbsent++)
    {
        m_apButtonCamSelect[dwBoardAbsent]->EnableWindow(FALSE);
        m_apButtonGrab[dwBoardAbsent]->EnableWindow(FALSE);
        m_apButtonFreeze[dwBoardAbsent]->EnableWindow(FALSE);
        m_apButtonSnap[dwBoardAbsent]->EnableWindow(FALSE);
        m_apButtonTrigger[dwBoardAbsent]->EnableWindow(FALSE);

        m_apEditFrameCount[dwBoardAbsent]->EnableWindow(FALSE);
        m_apEditFrameRate[dwBoardAbsent]->EnableWindow(FALSE);
        m_apEditPort[dwBoardAbsent]->EnableWindow(FALSE);
        m_apEditCameraType[dwBoardAbsent]->EnableWindow(FALSE);
        m_apEditSerialNumber[dwBoardAbsent]->EnableWindow(FALSE);

        DisableDisplay(dwBoardAbsent);
    }

    return TRUE;

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::SetPortAndCamType(DWORD dwBoardIndex, DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Keep and show active port

    m_adwSelectedPort[dwBoardIndex] = dwActivePort;

    strToShow.Format("%d", dwActivePort + 1);
    m_apEditPort[dwBoardIndex]->SetWindowText(strToShow);

    // Get a Camera object from this port

    m_apCam[dwBoardIndex] = m_apBrdMod[dwBoardIndex]->GetCam(dwActivePort);

    // Assign the selected camera type to this port and show it

    m_apCam[dwBoardIndex]->SetCameraType(pszCamType);
    m_apEditCameraType[dwBoardIndex]->SetWindowText(pszCamType);

    // Keep attributes

    m_apCam[dwBoardIndex]->GetAttr(&attr);

    m_adwCamSizeX[dwBoardIndex]     = attr.dwWidth;
    m_adwCamSizeY[dwBoardIndex]     = attr.dwHeight;
    m_adwBitDepth[dwBoardIndex]     = attr.dwBitsPerPixel;
    m_adwImageSize[dwBoardIndex]    = attr.dwBytesPerPixel * attr.dwWidth * attr.dwHeight;
    m_aCamColor[dwBoardIndex]       = attr.color;

    // Determine if triggered mode is used

    if (m_apCam[dwBoardIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
    {
        m_abTriggerMode[dwBoardIndex] = TRUE;
    }
    else
    {
        m_abTriggerMode[dwBoardIndex] = FALSE;
    }

}



//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ReleaseIFC_Capture()
{
DWORD dwBoardIndex;


    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        delete m_apBrdMod[dwBoardIndex];
        m_apBrdMod[dwBoardIndex] = NULL;
    }

}



//------------------------------------------
//         InitIFC_ImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_4BoardsDlg::InitIFC_ImageConnection(DWORD dwBoardNumber)
{
HWND hDisplayWnd;

    hDisplayWnd = m_apCamDisplay[dwBoardNumber]->GetSafeHwnd();

    m_apImageConnection[dwBoardNumber] = IfxCreateImgConn(m_apHostCapMemory[dwBoardNumber],
                                                         (WORD)m_adwCamSizeX[dwBoardNumber],
                                                         (WORD)m_adwCamSizeY[dwBoardNumber],
                                                         (WORD)m_adwBitDepth[dwBoardNumber],
                                                         hDisplayWnd,
                                                         m_aCamColor[dwBoardNumber],
                                                         IFC_DIB_SINK, NULL, ICAP_INTR_EOF);

    // Scale the image to fit the display window

    if (m_apImageConnection[dwBoardNumber])
    {
        CImgSink *imgSink = m_apImageConnection[dwBoardNumber]->GetSink();

        imgSink->SetZoom(IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT);
    }

    return m_apImageConnection[dwBoardNumber];

}




//------------------------------------------
//        ReleaseIFC_ImageConnection
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ReleaseIFC_ImageConnection(DWORD dwCamNumber)
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
BOOL CIFC_PC2V_4BoardsDlg::AllocateCaptureMemory(DWORD dwBoardNumber)
{
DWORD dwAllocSize;


    dwAllocSize = m_adwImageSize[dwBoardNumber] * BUFFER_COUNT;
    if (dwAllocSize == 0)
        return FALSE;

    m_apHostCapMemory[dwBoardNumber] = (BYTE *)malloc(dwAllocSize);
    if (m_apHostCapMemory[dwBoardNumber] == NULL)
        return FALSE;

    m_aCapMemLockHandle[dwBoardNumber] =
        m_apBrdMod[dwBoardNumber]->LockMem(m_apHostCapMemory[dwBoardNumber], dwAllocSize);

    return TRUE;
}



//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ReleaseCaptureMemory(DWORD dwBoardNumber)
{

    if (m_apHostCapMemory[dwBoardNumber])
    {
        m_apBrdMod[dwBoardNumber]->UnLockMem(m_aCapMemLockHandle[dwBoardNumber]);
        free(m_apHostCapMemory[dwBoardNumber]);
    }

    m_apHostCapMemory[dwBoardNumber] = NULL;

}


//-----------------------------------------------
//            OnPaint
//-----------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIFC_PC2V_4BoardsDlg::OnPaint() 
{
DWORD dwBoardIndex;
DWORD dwBoardAbsent;


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

        for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
        {
            m_apImageConnection[dwBoardIndex]->Display();

            DrawWindowBorder(dwBoardIndex);

            ShowSerialNumber(dwBoardIndex);

            if (m_abClearDisplay[dwBoardIndex])
            {
                ClearDisplay(dwBoardIndex);
            }
        }

        for (dwBoardAbsent = m_dwBoardCount; dwBoardAbsent < BOARD_MAX_NUMBER; dwBoardAbsent++)
        {
            DisableDisplay(dwBoardAbsent);
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
HCURSOR CIFC_PC2V_4BoardsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ReleaseAll() 
{
DWORD dwCamIndex;


    // Terminate the display thread

    delete m_pDisplayThread;
    m_pDisplayThread = NULL;

    // Terminate the acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < m_dwBoardCount; dwCamIndex++)
    {
        delete m_apAcqThread[dwCamIndex];
        m_apAcqThread[dwCamIndex] = NULL;
    }

    // Release the Host capture memory for all cameras

    for (dwCamIndex = 0; dwCamIndex < m_dwBoardCount; dwCamIndex++)
    {
        ReleaseCaptureMemory(dwCamIndex);
    }

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    for (dwCamIndex = 0; dwCamIndex < m_dwBoardCount; dwCamIndex++)
    {
        ReleaseIFC_ImageConnection(dwCamIndex);
    }

    // Release the "CICapMod" object for all cameras and boards

    ReleaseIFC_Capture();

    // Kill the Timers

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}


//------------------------------------------
//              ClearDisplay
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ClearDisplay(DWORD dwBoardIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    // Clear the Display Window

    GetWindowPosition(m_apCamDisplay[dwBoardIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);
}



//------------------------------------------
//              DisableDisplay
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::DisableDisplay(DWORD dwBoardIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(GRAY_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    // Paint in GREY the Display Window

    GetWindowPosition(m_apCamDisplay[dwBoardIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);

    GdiFlush();
}





//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2V_4BoardsDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//          OnTimer
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
DWORD dwBoardIndex;
DWORD dwBoardAbsent;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
        {
            if (m_abClearDisplay[dwBoardIndex] && ((m_dwGuiCounter & 0x0F) == 0))
            {
                ClearDisplay(dwBoardIndex);
                DrawWindowBorder(dwBoardIndex);
                ShowSerialNumber(dwBoardIndex);
            }
        }

        for (dwBoardAbsent = m_dwBoardCount; dwBoardAbsent < BOARD_MAX_NUMBER; dwBoardAbsent++)
        {
            if ((m_dwGuiCounter & 0x0F) == 0)
            {
                DisableDisplay(dwBoardAbsent);
            }
        }

        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
        {
            UpdateButtons(dwBoardIndex);                // Enable or not some buttons
        }

        m_dwGuiCounter++;
    }

    CDialog::OnTimer(nIDEvent);
}





//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ShowStatistics() 
{
float fFrameRate;
CString strToShow;
DWORD dwBoardIndex;


    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        // Compute and show acquisition frame rate

        if (! m_abIsGrabbing[dwBoardIndex])
        {
            m_apEditFrameRate[dwBoardIndex]->SetWindowText( _T("*****"));
        }
        else
        {
            fFrameRate = m_aMeasureFramePeriod[dwBoardIndex].GetTime();
            if (fFrameRate != 0.0)
            {
                fFrameRate = (float)1.0 / fFrameRate;
                strToShow.Format("%.2f", fFrameRate);
                m_apEditFrameRate[dwBoardIndex]->SetWindowText(strToShow);
            }
        }
    }
}


//------------------------------------------
//              ShowSerialNumber
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::ShowSerialNumber(DWORD dwBoardIndex)
{
CString strToShow;


    strToShow.Format("S%d", m_adwBoardSerial[dwBoardIndex]);
    m_apEditSerialNumber[dwBoardIndex]->SetWindowText(strToShow);

}




//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::UpdateButtons(DWORD dwBoardIndex)
{
    // Depending on situation, some buttons are disabled

    m_apButtonGrab[dwBoardIndex]->EnableWindow(! m_abIsGrabbing[dwBoardIndex]);
    m_apButtonSnap[dwBoardIndex]->EnableWindow(! m_abIsGrabbing[dwBoardIndex]);
    m_apButtonFreeze[dwBoardIndex]->EnableWindow(m_abIsGrabbing[dwBoardIndex]);
    m_apButtonTrigger[dwBoardIndex]->EnableWindow(m_abTriggerMode[dwBoardIndex] && m_abIsGrabbing[dwBoardIndex]);

    m_apButtonCamSelect[dwBoardIndex]->EnableWindow(! m_abIsGrabbing[dwBoardIndex]);
}




//------------------------------------------
//          OnClose
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnClose() 
{
CString strWarnText;
DWORD dwBoardIndex;


    for (dwBoardIndex = 0; dwBoardIndex < m_dwBoardCount; dwBoardIndex++)
    {
        if (m_abIsGrabbing[dwBoardIndex])
        {
            strWarnText.Format(_T("Stop grabbing on board # %d before exiting"), dwBoardIndex + 1);
            AfxMessageBox(strWarnText);
            return;
        }
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
//          OnButtonGrab1
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonGrab1() 
{

    // Start the acquisition

    m_adwFrameCounter[0] = 0;

    m_abClearDisplay[0] = FALSE;
    m_aDispThreadParams[0].bBusy = FALSE;

    m_aGrabID[0] = m_apCam[0]->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_apHostCapMemory[0],
                                    BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_abIsGrabbing[0] = TRUE;

    m_aAcqThreadParams[0].pMyClass          = this;
    m_aAcqThreadParams[0].dwMyBoardIndex    = 0;

    // Start the acquisition thread

    m_apAcqThread[0]->AwakeThread(&m_aAcqThreadParams[0]);

}



//------------------------------------------
//          OnButtonGrab2
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonGrab2() 
{

    // Start the acquisition

    m_adwFrameCounter[1] = 0;

    m_abClearDisplay[1] = FALSE;
    m_aDispThreadParams[1].bBusy = FALSE;

    m_aGrabID[1] = m_apCam[1]->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_apHostCapMemory[1],
                                    BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_abIsGrabbing[1] = TRUE;

    m_aAcqThreadParams[1].pMyClass          = this;
    m_aAcqThreadParams[1].dwMyBoardIndex    = 1;

    // Start the acquisition thread

    m_apAcqThread[1]->AwakeThread(&m_aAcqThreadParams[1]);

}



//------------------------------------------
//          OnButtonGrab3
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonGrab3() 
{

    // Start the acquisition

    m_adwFrameCounter[2] = 0;

    m_abClearDisplay[2] = FALSE;
    m_aDispThreadParams[2].bBusy = FALSE;

    m_aGrabID[2] = m_apCam[2]->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_apHostCapMemory[2],
                                    BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_abIsGrabbing[2] = TRUE;

    m_aAcqThreadParams[2].pMyClass          = this;
    m_aAcqThreadParams[2].dwMyBoardIndex    = 2;

    // Start the acquisition thread

    m_apAcqThread[2]->AwakeThread(&m_aAcqThreadParams[2]);

}



//------------------------------------------
//          OnButtonGrab4
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonGrab4() 
{

    // Start the acquisition

    m_adwFrameCounter[3] = 0;

    m_abClearDisplay[3] = FALSE;
    m_aDispThreadParams[3].bBusy = FALSE;

    m_aGrabID[3] = m_apCam[3]->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_apHostCapMemory[3],
                                    BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_abIsGrabbing[3] = TRUE;

    m_aAcqThreadParams[3].pMyClass          = this;
    m_aAcqThreadParams[3].dwMyBoardIndex    = 3;

    // Start the acquisition thread

    m_apAcqThread[3]->AwakeThread(&m_aAcqThreadParams[3]);

}



//------------------------------------------
//          OnButtonFreeze1
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonFreeze1() 
{
    // Stop the acquisition

    m_apCam[0]->Freeze();

    // Stop the acquisition thread

    m_abIsGrabbing[0]   = FALSE;
}



//------------------------------------------
//          OnButtonFreeze2
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonFreeze2() 
{
    // Stop the acquisition

    m_apCam[1]->Freeze();

    // Stop the acquisition thread

    m_abIsGrabbing[1]   = FALSE;
}



//------------------------------------------
//          OnButtonFreeze3
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonFreeze3() 
{
    // Stop the acquisition

    m_apCam[2]->Freeze();

    // Stop the acquisition thread

    m_abIsGrabbing[2]   = FALSE;
}



//------------------------------------------
//          OnButtonFreeze4
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonFreeze4() 
{
    // Stop the acquisition

    m_apCam[3]->Freeze();

    // Stop the acquisition thread

    m_abIsGrabbing[3]   = FALSE;
}




//------------------------------------------
//              OnButtonTypeCam1
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTypeCam1() 
{
    GetUserCamType(0);
}



//------------------------------------------
//              OnButtonTypeCam2
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTypeCam2() 
{
    GetUserCamType(1);
}



//------------------------------------------
//              OnButtonTypeCam3
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTypeCam3() 
{
    GetUserCamType(2);
}



//------------------------------------------
//              OnButtonTypeCam4
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTypeCam4() 
{
    GetUserCamType(3);
}


//------------------------------------------
//              GetUserCamType
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::GetUserCamType(DWORD dwBoardIndex) 
{

    if (m_abIsGrabbing[dwBoardIndex])
    {
        AfxMessageBox(_T("Stop grabbing before changing active camera"));
        return;
    }

    CCamSelDlg CamDlg(this, m_apCam[dwBoardIndex]);

    if (CamDlg.DoModal() == IDOK)
    {
        // Assign the selected port and camera type

        SetPortAndCamType(dwBoardIndex, CamDlg.m_dwCurPort, CamDlg.m_pszCurCamera);

        // Release current Host capture memory and image connection object

        ReleaseCaptureMemory(dwBoardIndex);

        ReleaseIFC_ImageConnection(dwBoardIndex);

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory(dwBoardIndex) == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        m_apImageConnection[dwBoardIndex] = InitIFC_ImageConnection(dwBoardIndex);
        if (m_apImageConnection[dwBoardIndex] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        // Clear the Display Window

        m_abClearDisplay[dwBoardIndex] = TRUE;

    }

}



//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around all
//  the view windows.
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::DrawWindowBorder(DWORD dwBoardIndex)
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

    GetWindowPosition(m_apCamDisplay[dwBoardIndex]->m_hWnd, &rectToDraw);
    InflateRect(&rectToDraw, 5, 5);
    MyDC.Rectangle(&rectToDraw);

    // Release the GDI objects

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}



//------------------------------------------
//          OnButtonSnap1()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonSnap1() 
{
CString strToShow;


    if (m_abIsGrabbing[0])
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_abClearDisplay[0] = FALSE;

    m_apCam[0]->Snap(m_apHostCapMemory[0], 0, 0, 0, 0);

    // Increment and show frame counter

    m_adwFrameCounter[0]++;
    strToShow.Format("%d", m_adwFrameCounter[0]);
    m_apEditFrameCount[0]->SetWindowText(strToShow);

    // Show frame on the screen

    m_apImageConnection[0]->GetSrc()->SetBufferAddr(m_apHostCapMemory[0]);
    m_apImageConnection[0]->Display();

}



//------------------------------------------
//          OnButtonSnap2()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonSnap2() 
{
CString strToShow;


    if (m_abIsGrabbing[1])
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_abClearDisplay[1] = FALSE;

    m_apCam[1]->Snap(m_apHostCapMemory[1], 0, 0, 0, 0);

    // Increment and show frame counter

    m_adwFrameCounter[1]++;
    strToShow.Format("%d", m_adwFrameCounter[1]);
    m_apEditFrameCount[1]->SetWindowText(strToShow);

    // Show frame on the screen

    m_apImageConnection[1]->GetSrc()->SetBufferAddr(m_apHostCapMemory[1]);
    m_apImageConnection[1]->Display();

}



//------------------------------------------
//          OnButtonSnap3()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonSnap3() 
{
CString strToShow;


    if (m_abIsGrabbing[2])
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_abClearDisplay[2] = FALSE;

    m_apCam[2]->Snap(m_apHostCapMemory[2], 0, 0, 0, 0);

    // Increment and show frame counter

    m_adwFrameCounter[2]++;
    strToShow.Format("%d", m_adwFrameCounter[2]);
    m_apEditFrameCount[2]->SetWindowText(strToShow);

    // Show frame on the screen

    m_apImageConnection[2]->GetSrc()->SetBufferAddr(m_apHostCapMemory[2]);
    m_apImageConnection[2]->Display();

}



//------------------------------------------
//          OnButtonSnap4()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonSnap4() 
{
CString strToShow;


    if (m_abIsGrabbing[3])
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_abClearDisplay[3] = FALSE;

    m_apCam[3]->Snap(m_apHostCapMemory[3], 0, 0, 0, 0);

    // Increment and show frame counter

    m_adwFrameCounter[3]++;
    strToShow.Format("%d", m_adwFrameCounter[3]);
    m_apEditFrameCount[3]->SetWindowText(strToShow);

    // Show frame on the screen

    m_apImageConnection[3]->GetSrc()->SetBufferAddr(m_apHostCapMemory[3]);
    m_apImageConnection[3]->Display();

}



//------------------------------------------
//          OnButtonTrigger1()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTrigger1() 
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

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_apCam[0]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}




//------------------------------------------
//          OnButtonTrigger2()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTrigger2() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[1]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    m_apCam[1]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd

    m_apCam[1]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_apCam[1]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}




//------------------------------------------
//          OnButtonTrigger3()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTrigger3() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[2]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    m_apCam[2]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd

    m_apCam[2]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_apCam[2]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}



//------------------------------------------
//          OnButtonTrigger4()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTrigger4() 
{
BOOL bTriggerSrcWasExternal = FALSE;
double TriggerSource;


    // Check if current TRIGGER source is external

    TriggerSource = m_apCam[3]->GetAcqParam(P_TRIGGER_SRC);

    if (TriggerSource != IFC_SOFT_TRIG)
    {
        bTriggerSrcWasExternal = TRUE;
    }

    // Force TRIGGER source to be from a soft command and generate a TRIGGER soft command

    m_apCam[3]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd

    m_apCam[3]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_apCam[3]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}



//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_4BoardsDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}

