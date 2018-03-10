//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CamSwitchPlanarVerticalDlg.cpp
//
//  BIRTH DATE:     October 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V5.7)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Two blocks of three genlocked cameras acquiring in planar
//                  vertical mode using a single ring of buffers. 
//                  Each buffer contains three images and it is displayed in a
//                  single window where each camera image is on top of each other.
//                  The two blocks of three cameras are dynamically switched.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"		                // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera type Selector Dialog Box

#include "IFC_PC2V_CamSwitchPlanarVertical.h"
#include "IFC_PC2V_CamSwitchPlanarVerticalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





//------------------------------------------
//            Constructor
//------------------------------------------
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//            Constructor
//------------------------------------------
CIFC_PC2V_CamSwitchPlanarVerticalDlg::CIFC_PC2V_CamSwitchPlanarVerticalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_CamSwitchPlanarVerticalDlg::IDD, pParent)
{
DWORD dwCamIndex;


        //{{AFX_DATA_INIT(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        m_apImageConnection[dwCamIndex] = NULL;
        m_aGrabID[dwCamIndex]           = NULL;
        m_apCam[dwCamIndex]             = NULL;
        m_abIsGrabbing[dwCamIndex]      = FALSE;
        m_apAcqThread[dwCamIndex]       = NULL;
    }

    m_pIntCallback_SOT  = NULL;
    m_pHostCapMemory    = NULL;

    m_bAppClosing       = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwPixBitDepth     = 0;
    m_CamColor          = IFC_MONO;
    m_dwImageSize       = 0;
    m_dwSnapPolling     = 0;

    m_pDisplayThread        = NULL;

    m_dwIsSOT_EventCounter  = 0;
    m_bWasSOT_EventDetected = FALSE;

    m_bTriggerMode          = FALSE;
    m_bSnapping             = FALSE;
    m_bSystemOverload       = FALSE;

}




//------------------------------------------
//            DoDataExchange
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	DDX_Control(pDX, IDC_STATIC_GROUP2_LIGHT, m_StaticRedLightGroup2);
	DDX_Control(pDX, IDC_STATIC_GROUP1_LIGHT, m_StaticRedLightGroup1);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM, m_ButtonCamType);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR_TOTAL, m_EditFrameRateTotal);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM, m_EditCamType);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplayGroup2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplayGroup1);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CIFC_PC2V_CamSwitchPlanarVerticalDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM, OnButtonTypeCam)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_CamSwitchPlanarVerticalDlg *pMyClass;
DWORD               dwMyGroup;
DWORD               dwMyCamera;
CString             strToShow;
int                 iSeqNum;
HIFCGRAB            GrabID;
CICamera            *pMyCamera;
CICapMod            *pBrdMod;
CImgConn            *pImageConnect;
BYTE                *pHostBuffer;
BOOL                bReleaseTheBuffer;
ACQ_THREAD_PARAM    *pMyParams;
GRAB_EXT_ATTR       ExtraAttrib;
HWND                hMyRedLightGroup;


    // Get my parameters

    pMyParams = (ACQ_THREAD_PARAM *)pContext;

    // A static function has no access to it's own class, need a ptr to it

    pMyClass    = pMyParams->pMyClass;
    dwMyGroup   = pMyParams->dwMyGroupIndex;

    dwMyCamera  = dwMyGroup * CAMERA_COUNT_PER_GROUP;       // Group 0, Camera 0 - Group 1, Camera 3

    // To alleviate the code, keep useful local variables

    pBrdMod         = pMyClass->m_pBrdMod;
    GrabID          = pMyClass->m_aGrabID[dwMyGroup];
    pMyCamera       = pMyClass->m_apCam[dwMyGroup];
    pImageConnect   = pMyClass->m_apImageConnection[dwMyGroup];

    // Determine my group's red light

    if (dwMyGroup == 0)
    {
        hMyRedLightGroup = pMyClass->m_StaticRedLightGroup1;
    }
    else
    {
        hMyRedLightGroup = pMyClass->m_StaticRedLightGroup2;
    }

    while (pMyClass->m_abIsGrabbing[dwMyGroup])
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pMyCamera->GrabWaitFrameEx(GrabID, &pHostBuffer, IFC_WAIT_NEWER_FRAME,
                                              WAIT_ACQ_MAX_MSEC, TRUE, NULL, NULL, &ExtraAttrib);

        // If this frame is good and belongs to my group

        if (iSeqNum != -1)
        {
            bReleaseTheBuffer = TRUE;

            if (ExtraAttrib.camPortNum == dwMyCamera)   // Belong to my group of 3 cameras ?
            {
                // Only one group take care of the statistics

                if (dwMyGroup == 0)
                {
                    pMyClass->m_MeasureFramePeriod.TagTime();
                }

                // Take care of the Trigger-To-Image event counters

                pMyClass->ReadAndClearEvents();

                // If the last buffer is not waiting to be displayed,
                //  flag it to be displayed and wake-up the Display thread
                // otherwise, release the buffer immediately (will never be displayed)

                if (pMyClass->m_aDispThreadParams[dwMyGroup].bBusy == FALSE)
                {
                    pMyClass->m_aDispThreadParams[dwMyGroup].pTheBuffer    = pHostBuffer;
                    pMyClass->m_aDispThreadParams[dwMyGroup].GrabID        = GrabID;
                    pMyClass->m_aDispThreadParams[dwMyGroup].iBufferIndex  = iSeqNum;
                    pMyClass->m_aDispThreadParams[dwMyGroup].bBusy         = TRUE;

                    pMyClass->m_pDisplayThread->AwakeThread(pMyClass);

                    bReleaseTheBuffer           = FALSE;         // Display thread will release it
                    pMyClass->m_bSystemOverload = FALSE;
                }
                else
                {
                    pMyClass->m_bSystemOverload = TRUE;
                }

                // Put the former group light OFF and this group light ON 

                pMyClass->DrawRectangleLight(pMyClass->m_hLastRedLightGroup, RGB(0, 0, 0), FALSE, strToShow);
                pMyClass->DrawRectangleLight(hMyRedLightGroup, RGB(0, 0xFF, 0), FALSE, strToShow);
                pMyClass->m_hLastRedLightGroup = hMyRedLightGroup;

                // Determine if another frame is to be expected

                if (pMyClass->m_bSnapping)
                {
                    pMyClass->m_abIsGrabbing[dwMyGroup] = FALSE;       // Go out of this loop
                }

            }  // This frame belongs to my camera

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

            pMyClass->ReadAndClearEvents();
        }
    }

    // Return control to the calling thread
}



//------------------------------------------
//              ThreadDisplayProc
//------------------------------------------
// Called by the display thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_2x3CamSwitchDlg).
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ThreadDisplayProc(void *pContext) 
{
CIFC_PC2V_CamSwitchPlanarVerticalDlg   *pMyClass;
CImgConn                    *pImageConnect;
int                         iSeqNum;
HIFCGRAB                    GrabID;
BYTE                        *pHostBuffer;
DWORD                       dwGroupIndex;
CString strToShow;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchPlanarVerticalDlg *)pContext;

    // While there is buffer ready to be to displayed

    while (pMyClass->GetBufferToDisplay(&dwGroupIndex))
    {

        // Get the information associated with the buffer and channel to display

        iSeqNum         = pMyClass->m_aDispThreadParams[dwGroupIndex].iBufferIndex;
        pHostBuffer     = pMyClass->m_aDispThreadParams[dwGroupIndex].pTheBuffer;
        GrabID          = pMyClass->m_aDispThreadParams[dwGroupIndex].GrabID;

        // Get the ImageConnection object associated with this camera

        pImageConnect = pMyClass->m_apImageConnection[dwGroupIndex];

        // Update the address associated with the image source to point
        // to the frame we just acquired

        pImageConnect->GetSrc()->SetBufferAddr(pHostBuffer);

        // Display the  frame in our client window

        pImageConnect->Display();

        // Release the frame back into the active circular acquisition buffer

        pMyClass->m_apCam[dwGroupIndex]->GrabRelease(GrabID, iSeqNum);

        // Flag the buffer as displayed

        pMyClass->m_aDispThreadParams[dwGroupIndex].bBusy = FALSE;

    }

    // Return control to the calling thread
}





//------------------------------------------
//              GetBufferToDisplay
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::GetBufferToDisplay(DWORD *pCameraIndex)
{
DWORD dwCamIndex;


    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        if (m_aDispThreadParams[dwCamIndex].bBusy)
        {
            *pCameraIndex = dwCamIndex;
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_CamSwitchPlanarVerticalDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_CamSwitchPlanarVerticalDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

}



//------------------------------------------
//              ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReadAndClearEvents() 
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
//            OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnInitDialog()
{
DWORD dwCamIndex;



	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

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

    // Allocate Host capture memory (single ring for all cameras)

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate capture memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes an IFC Image connection object for the 2 camera groups

    m_apImageConnection[0] = InitIFC_ImageConnection(&m_StaticDisplayGroup1);
    if (m_apImageConnection[0] == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_apImageConnection[1] = InitIFC_ImageConnection(&m_StaticDisplayGroup2);
    if (m_apImageConnection[1] == NULL)
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

    // Create an acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
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

void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}




//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::InitIFC_Capture()
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::SetCamType(char *pszCamType)
{
CAM_ATTR attr;


    // Get a CICamera object from the first port of the two groups

    m_apCam[0] = m_pBrdMod->GetCam(0);
    m_apCam[1] = m_pBrdMod->GetCam(3);

    // Assign the selected camera type to all ports

    m_apCam[0]->SetCameraType(pszCamType);
    m_apCam[1]->SetCameraType(pszCamType);

    // Tell IFC we are in vertical planar mode

    m_apCam[0]->SetAcqParam(P2V_PLANAR_MODE, P2V_PLANAR_VERT);
    m_apCam[1]->SetAcqParam(P2V_PLANAR_MODE, P2V_PLANAR_VERT);

    // Tell IFC to acquire three times the number of lines per buffer

    m_apCam[0]->GetAttr(&attr);

    m_apCam[0]->SetAcqParam(P_HEIGHT_PIXELS, attr.dwHeight * 3);
    m_apCam[1]->SetAcqParam(P_HEIGHT_PIXELS, attr.dwHeight * 3);

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

    // Set a new PLL gain and mode optimised for camera switching

    m_apCam[0]->SetAcqParam(P2V_PLL_GAIN, 0x35);
    m_apCam[1]->SetAcqParam(P2V_PLL_GAIN, 0x35);

    // Show the selected camera type

    m_EditCamType.SetWindowText(pszCamType);

}





//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::InitIFC_Callback()
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
CImgConn *CIFC_PC2V_CamSwitchPlanarVerticalDlg::InitIFC_ImageConnection(CStatic *pDisplayWindow)
{
CImgConn *ImgConn;
HWND hDisplayWnd;


    // Get some variable depending on the targeted camera

    hDisplayWnd = pDisplayWindow->GetSafeHwnd();

    // Create an ImgeConnection object

    ImgConn = IfxCreateImgConn(m_pHostCapMemory, (WORD)m_dwCamSizeX,
                               (WORD)m_dwCamSizeY, (WORD)m_dwPixBitDepth, hDisplayWnd,
                                m_CamColor, IFC_DIB_SINK, NULL, ICAP_INTR_EOF);

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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

	delete m_pBrdMod;
	m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReleaseIFC_ImageConnection(DWORD dwCamNumber)
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
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::AllocateCaptureMemory()
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReleaseCaptureMemory()
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnPaint() 
{
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

        m_apImageConnection[0]->Display();
        m_apImageConnection[1]->Display();

        if (m_bClearDisplay)
        {
            ClearDisplay();
        }

        DrawWindowBorder(m_StaticDisplayGroup1.GetSafeHwnd());
        DrawWindowBorder(m_StaticDisplayGroup2.GetSafeHwnd());

        DrawRectangleLight(m_StaticRedLightGroup1, RGB(0, 0, 0), FALSE, strDummy);
        DrawRectangleLight(m_StaticRedLightGroup2, RGB(0, 0, 0), FALSE, strDummy);

        m_dwOnPaintCounter++;
    }
}




//------------------------------------------
//            OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ReleaseAll()
{
DWORD dwCamIndex;


    // Terminate the display thread

    delete m_pDisplayThread;
    m_pDisplayThread = NULL;

    // Terminate the acquisition thread for all cameras

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        delete m_apAcqThread[dwCamIndex];
        m_apAcqThread[dwCamIndex] = NULL;
    }

    // Release the Host capture memory

    ReleaseCaptureMemory();

    // Release the Image Connection object for all cameras

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticDisplayGroup1.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    GetWindowPosition(m_StaticDisplayGroup2.GetSafeHwnd(), &RectDraw);
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
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ShowStatistics() 
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::UpdateButtons()
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
//          IsGrabbing()
//------------------------------------------
BOOL CIFC_PC2V_CamSwitchPlanarVerticalDlg::IsGrabbing() 
{
DWORD dwCamIndex;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT ; dwCamIndex++)
    {
        if (m_abIsGrabbing[dwCamIndex])
        {
            return TRUE;
        }
    }

    return FALSE;

}





//------------------------------------------
//              ShowEventLights
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::ShowEventLights() 
{
static BOOL bToggler;
CString strDummy;


    // Event detection indicators

    if (IsGrabbing())
    {
        // Show TRIGGER EVENT presence light

        if (m_bWasSOT_EventDetected)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0xFF, 0), FALSE, strDummy);  // Trigger detected
        }
        else if (! m_bTriggerMode)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);  // No trigger mode used
        }
        else if (bToggler)
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0xFF, 0xFF, 0), FALSE, strDummy);  // Warning flashing
        }
        else
        {
            DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);  // Warning flashing
        }
    }
    else
    {
        DrawRectangleLight(m_StaticSOTLight.m_hWnd, RGB(0, 0, 0), FALSE, strDummy);  // No trigger light
    }

    bToggler = ! bToggler;

}


//------------------------------------------
//          DrawRectangleLight()
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::DrawWindowBorder(HWND hWnd)
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
//          OnButtonTypeCam()
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonTypeCam() 
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

        ReleaseCaptureMemory();

        for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
        {
            ReleaseIFC_ImageConnection(dwCamIndex);
        }

        // Allocate new host Capture Memory (single ring for all cameras)

        if (AllocateCaptureMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        // Initializes an IFC Image connection object for the 2 camera groups

        m_apImageConnection[0] = InitIFC_ImageConnection(&m_StaticDisplayGroup1);
        if (m_apImageConnection[0] == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Image connection object !!!"));
        }

        m_apImageConnection[1] = InitIFC_ImageConnection(&m_StaticDisplayGroup2);
        if (m_apImageConnection[1] == NULL)
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
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnClose() 
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

    m_bAppClosing       = FALSE;

    ReleaseAll();

	CDialog::OnClose();
}




//------------------------------------------
//              OnTimer
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnTimer(UINT nIDEvent) 
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

            DrawWindowBorder(m_StaticDisplayGroup1.GetSafeHwnd());
            DrawWindowBorder(m_StaticDisplayGroup2.GetSafeHwnd());
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
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonGrab() 
{
int dwGroupIndex;


    // Determine if triggered mode is used at least on one camera group

    m_bTriggerMode = FALSE;
    for (dwGroupIndex = 0; dwGroupIndex < CAMERA_GROUP_COUNT; dwGroupIndex++)
    {
        if (m_apCam[dwGroupIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
        {
            m_bTriggerMode = TRUE;
        }
    }

    // Define the grab Sequence for IFC

    m_bClearDisplay = FALSE;

    m_pBrdMod->SwitchCameraDefineStart();

    // Define Group 1, use a single ring of buffers for the 2 camera groups

    m_aGrabID[0] = m_apCam[0]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                     m_pHostCapMemory,
                                      BUFFER_COUNT);

    m_abIsGrabbing[0] = TRUE;

    // Define Group 2, use a single ring of buffers for the 2 camera groups

    m_aGrabID[1] = m_apCam[1]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                     m_pHostCapMemory,
                                      BUFFER_COUNT);

    m_abIsGrabbing[1] = TRUE;

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the GRAB

    m_pBrdMod->SwitchCameraGrab();

    m_bSystemOverload = FALSE;

    m_dwIsSOT_EventCounter = 0;

    // Start the two acquisition threads

    for (dwGroupIndex = 0; dwGroupIndex < CAMERA_GROUP_COUNT; dwGroupIndex++)
    {
        m_aDispThreadParams[dwGroupIndex].bBusy         = FALSE;

        m_aAcqThreadParams[dwGroupIndex].pMyClass       = this;
        m_aAcqThreadParams[dwGroupIndex].dwMyGroupIndex = dwGroupIndex;

        m_apAcqThread[dwGroupIndex]->AwakeThread(&m_aAcqThreadParams[dwGroupIndex]);
    }

    // Draw blue border arounf display windows

    DrawWindowBorder(m_StaticDisplayGroup1.GetSafeHwnd());
    DrawWindowBorder(m_StaticDisplayGroup2.GetSafeHwnd());

}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonSnap() 
{
int dwCamIndex;


    // Determine if the system is not already grabbing

    if (m_bSnapping)
    {
        AfxMessageBox(_T("Already snapping !!!"));
        return;
    }

    // Determine if triggered mode is used at least on one camera group

    m_bTriggerMode = FALSE;
    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        if (m_apCam[dwCamIndex]->GetAcqParam(P_TRIGGER_ENABLE) == IFC_ENABLE)
        {
            m_bTriggerMode = TRUE;
        }
    }

    // Define the grab Sequence for IFC

    m_bClearDisplay = FALSE;

    m_pBrdMod->SwitchCameraDefineStart();

    // Define Group 1, use a single ring of buffers for the 2 camera groups

    m_aGrabID[0] = m_apCam[0]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                     m_pHostCapMemory,
                                      BUFFER_COUNT);

    m_abIsGrabbing[0] = TRUE;

    // Define Group 2, use a single ring of buffers for the 2 camera groups

    m_aGrabID[1] = m_apCam[1]->Grab(P2V_GOPT_ALL_CHAN_GRAB | IFC_GOPT_AUTO_FRAME_LOCK,
                                     m_pHostCapMemory,
                                      BUFFER_COUNT);

    m_abIsGrabbing[1] = TRUE;

    m_pBrdMod->SwitchCameraDefineEnd();

    // Start the SNAP (note that the GUI timer will end the snap process)

    m_dwSnapPolling = 0;
    m_bSnapping     = TRUE;
    m_pBrdMod->SwitchCameraSnap(2);

    // Start the acquisition threads

    m_bSystemOverload = FALSE;

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        m_aDispThreadParams[dwCamIndex].bBusy           = FALSE;

        m_aAcqThreadParams[dwCamIndex].pMyClass         = this;
        m_aAcqThreadParams[dwCamIndex].dwMyGroupIndex   = dwCamIndex;

        m_apAcqThread[dwCamIndex]->AwakeThread(&m_aAcqThreadParams[dwCamIndex]);
    }

}





//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonFreeze() 
{
DWORD dwCamIndex;
CString strDummy;


    m_pBrdMod->SwitchCameraFreeze();

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        m_abIsGrabbing[dwCamIndex] = FALSE;
    }

    DrawRectangleLight(m_StaticRedLightGroup1, RGB(0, 0, 0), FALSE, strDummy);
    DrawRectangleLight(m_StaticRedLightGroup2, RGB(0, 0, 0), FALSE, strDummy);


}




//------------------------------------------
//              OnButtonTrigger
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonTrigger() 
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

    for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetAcqParam(P_TRIGGER_SRC, IFC_SOFT_TRIG);  // TRIGGER source is soft cmd
        m_apCam[dwCamIndex]->SetAcqParam(P_GEN_SW_TRIGGER, 0);           // Generate a TRIGGER soft command
    }

    // Raise the flag indicating that the SOT event occured

    m_dwIsSOT_EventCounter++;

    if (bTriggerSrcWasExternal)
    {
        for (dwCamIndex = 0; dwCamIndex < CAMERA_GROUP_COUNT; dwCamIndex++)
        {
            m_apCam[dwCamIndex]->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
        }
    }

}

//------------------------------------------
//          OnButtonTrap()
//------------------------------------------
void CIFC_PC2V_CamSwitchPlanarVerticalDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}
