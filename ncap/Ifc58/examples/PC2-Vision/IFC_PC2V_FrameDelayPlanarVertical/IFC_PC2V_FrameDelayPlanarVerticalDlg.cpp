//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_FrameDelayDlg.cpp
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
//                  Up to six cameras capture an image at the
//                  same moment and then are acquired three at a time,
//                  store in the host memory in a planar way and
//                  displayed in a vertical planar way.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <math.h>                           // Function floor()
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "resource.h"                       // Main symbols

#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"
#include "CamSelDlg.h"                      // Camera Selector Dialog Box

#include "IFC_PC2V_FrameDelayPlanarVertical.h"
#include "IFC_PC2V_FrameDelayPlanarVerticalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//-----------------------------------------------
//            Constructor
//-----------------------------------------------
CIFC_PC2V_FrameDelayPlanarVerticalDlg::CIFC_PC2V_FrameDelayPlanarVerticalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_FrameDelayPlanarVerticalDlg::IDD, pParent)
{
DWORD dwCamIndex;



	//{{AFX_DATA_INIT(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod           = NULL;
    m_pAcqThread        = NULL;
    m_pHostCapMemory    = NULL;

    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
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
    m_bIsSnapping           = FALSE;
    m_bAppClosing           = FALSE;

    m_dwIsSOT_EventCounter = 0;
    m_bWasSOT_EventDetected = FALSE;

}



//-----------------------------------------------
//            DoDataExchange
//-----------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
	DDX_Control(pDX, IDC_RADIO_DISP_ENABLE, m_RadioDisplayEnable);
	DDX_Control(pDX, IDC_STATIC_SOT_LIGHT, m_StaticSOTLight);
	DDX_Control(pDX, IDC_BUTTON_TYPE_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_FR, m_EditFrameRate);
	DDX_Control(pDX, IDC_EDIT_TYPE_CAM, m_EditCamType);
	DDX_Control(pDX, IDC_RADIO_EXT_0, m_RadioExt_0);
	DDX_Control(pDX, IDC_STATIC_DISPLAY2, m_StaticDisplayGroup2);
	DDX_Control(pDX, IDC_STATIC_DISPLAY1, m_StaticDisplayGroup1);
	DDX_Control(pDX, IDC_EDIT_FC, m_EditFrameCount);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_FrameDelayPlanarVerticalDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_BUTTON_TYPE_CAM, OnButtonTypeCam)
	ON_BN_CLICKED(IDC_RADIO_EXT_0, OnRadioExt0)
	ON_BN_CLICKED(IDC_RADIO_EXT_1, OnRadioExt1)
	ON_BN_CLICKED(IDC_RADIO_SOFT, OnRadioSoft)
	ON_BN_CLICKED(IDC_RADIO_DISP_DISABLE, OnRadioDispDisable)
	ON_BN_CLICKED(IDC_RADIO_DISP_ENABLE, OnRadioDispEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//              ThreadAcqProc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_FrameDelayPlanarVerticalDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ThreadAcqProc(void *pContext) 
{
CIFC_PC2V_FrameDelayPlanarVerticalDlg *pMyClass;
CString             strToShow;
CPCVision2          *pBrdMod;
CImgConn            *pImageConnect;
BYTE                *pHostBuffer;
BYTE                *pImage;
DWORD               dwGroupIndex;
DWORD               adwCameraSeq[CAM_GROUP_COUNT];


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_FrameDelayPlanarVerticalDlg *)pContext;

    // To alleviate the code, keep useful local variables

    pBrdMod     = pMyClass->m_pBrdMod;
    pHostBuffer = pMyClass->m_pHostCapMemory;

    // Camera used are the first of each group

    adwCameraSeq[0] = 0;
    adwCameraSeq[1] = 3;

    // Tell IFC the camera sequence

    pBrdMod->SetFrameDelaySequence(adwCameraSeq, CAM_GROUP_COUNT, pMyClass->m_TrigSource);

    while (pMyClass->m_bIsGrabbing || pMyClass->m_bIsSnapping)
    {
        // Starts the acquisition

        pBrdMod->FrameDelaySnap(pMyClass->m_TrigSource, pHostBuffer, 0, 0,
                                (short)pMyClass->m_dwCamSizeX,
                                (short)pMyClass->m_dwCamSizeY, 0);

        // Wait for the sequence ready in Host capture memory

        if (pBrdMod->FrameDelayWait(WAIT_ACQ_MAX_MSEC))
        {
            // Take care of Statistics

            pMyClass->m_MeasureAcqRate.TagTime();

            // Increment and show frame counter

            pMyClass->m_dwFrameCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameCounter);
            pMyClass->m_EditFrameCount.SetWindowText(strToShow);

            // Show the three planar images all on top of each other in a single window

            if (pMyClass->m_bDisplayEnable)
            {
                for (dwGroupIndex = 0; dwGroupIndex < CAM_GROUP_COUNT; dwGroupIndex++)
                {
                    pImage          = pHostBuffer + (dwGroupIndex * pMyClass->m_dwImageSize);
                    pImageConnect   = pMyClass->m_apImageConnection[dwGroupIndex];

                    // Update the address associated with the image source to point
                    // to the frame we just acquired

                    pImageConnect->GetSrc()->SetBufferAddr(pImage);

                    // Display the  frame in our client window

                    pImageConnect->Display();
                }
            }

        }   // Wait end of acquisition

        // Read the Trigger event

        pMyClass->ReadAndClearEvents();

        // Are we snapping or grabbing ?

        if (pMyClass->m_bIsSnapping)
        {
            pMyClass->m_bIsSnapping = FALSE;
        }

    }       // while (grabbing OR snapping)

    // Return control to the calling thread
}





//------------------------------------------
//              MyCallback_SOT
//------------------------------------------
// Function called when the "Start of TRIGGER"
// event occurs
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::MyCallback_SOT(void *pContext)
{
CIFC_PC2V_FrameDelayPlanarVerticalDlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_FrameDelayPlanarVerticalDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Raise the flag indicating that the event occured

    pMyClass->m_dwIsSOT_EventCounter++;

}



//-----------------------------------------------
//            OnInitDialog
//-----------------------------------------------
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnInitDialog()
{
CString strToShow;


	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    // Keep a ptr to all the Camera display windows

    m_apCamDisplay[0] = &m_StaticDisplayGroup1;
    m_apCamDisplay[1] = &m_StaticDisplayGroup2;

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

    m_TrigSource = IFC_EXT0_TRIG;
    m_RadioExt_0.SetCheck(BST_CHECKED);

    // Init Display Enable radio buttons

    m_bDisplayEnable = TRUE;
    m_RadioDisplayEnable.SetCheck(BST_CHECKED);


    return TRUE;  // return TRUE  unless you set the focus to a control

}



//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::InitIFC_Capture()
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

        CCamSelDlg CamDlg(this, pCam, 0);
        CamDlg.DoModal();

        // Keep selected port and camera type

        SetCamType(CamDlg.m_pszCurCamera);
    }
    else
    {
        // Display camera type and sets CICamera objects

        pCam = m_pBrdMod->GetCam(0);
        pCam->GetAttr(&attrib);
        SetCamType(attrib.camName);
    }

    return TRUE;

}




//------------------------------------------
//              SetCamType
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::SetCamType(char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;
DWORD dwCamIndex;



    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
    {
        // Get a Camera object from all ports

        m_apCam[dwCamIndex] = m_pBrdMod->GetCam(dwCamIndex * CAM_COUNT_PERGROUP);

        // Assign the selected camera type to this port

        m_apCam[dwCamIndex]->SetCameraType(pszCamType);
    }

    // Show camera type

    m_EditCamType.SetWindowText(pszCamType);

    // Tell IFC to acquire three times the number of lines per buffer

    m_apCam[0]->GetAttr(&attr);
    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetAcqParam(P_HEIGHT_PIXELS, attr.dwHeight * 3);
    }

    // Tell IFC we are in three camera planar VERTICAL mode

    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
    {
        m_apCam[dwCamIndex]->SetAcqParam(P2V_PLANAR_MODE, P2V_PLANAR_VERT);
        m_apCam[dwCamIndex]->SetAcqParam(P_PIXEL_COLOR, IFC_RGB_PLANAR);
    }

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
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::InitIFC_Callback()
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
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::InitIFC_ImageConnection()
{
HWND hDisplayWnd;
DWORD dwCamIndex;


    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReleaseIFC_Capture()
{

    // Delete the "CICapMod" object

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReleaseIFC_Callback()
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReleaseIFC_ImageConnection()
{
DWORD dwCamIndex;


    for (dwCamIndex = 0; dwCamIndex < CAM_GROUP_COUNT; dwCamIndex++)
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
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    // Determine the total buffer size

    dwAllocSize = m_dwImageSize * CAM_COUNT;
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReleaseCaptureMemory()
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnPaint() 
{
DWORD dwGroupIndex;

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

        for (dwGroupIndex = 0; dwGroupIndex < CAM_GROUP_COUNT; dwGroupIndex++)
        {
            DrawWindowBorder(m_apCamDisplay[dwGroupIndex]->m_hWnd);

            if (m_bClearDisplay)
            {
                ClearDisplay(dwGroupIndex);
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
HCURSOR CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReleaseAll() 
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
BOOL CIFC_PC2V_FrameDelayPlanarVerticalDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ClearDisplay(DWORD dwGroupIndex)
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_apCamDisplay[dwGroupIndex]->GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldBrush);
}





//------------------------------------------
//              ShowStatistics
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ShowStatistics() 
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

        fFrameRate = m_MeasureAcqRate.GetTime();
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::UpdateButtons()
{

    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);

}




//------------------------------------------
//            ReadAndClearEvents
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ReadAndClearEvents()
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::ShowEventLights() 
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText)
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::DrawWindowBorder(HWND hWnd)
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
//              OnTimer
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;
DWORD dwGroupIndex;


    if (nIDEvent == TIMER_STAT)
    {
        ShowStatistics();
    }
    else if (nIDEvent == TIMER_GUI)
    {
        if (m_bClearDisplay && ((m_dwGuiCounter & 0x0F) == 0))
        {
            for (dwGroupIndex = 0; dwGroupIndex < CAM_GROUP_COUNT; dwGroupIndex++)
            {
                ClearDisplay(dwGroupIndex);
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
//              OnClose
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnClose() 
{
CString strWarnText;

    if (m_bIsGrabbing || m_bIsSnapping)
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
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonSnap() 
{
CString strToShow;


    if (m_bIsGrabbing || m_bIsSnapping)
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

    // Init acquisition related variables

    m_dwSkippedFrameCounter = 0;

    m_bClearDisplay = FALSE;

    m_dwFrameCounter = 0;

    // Start the acquisition thread

    m_bIsSnapping = TRUE;
    m_dwIsSOT_EventCounter = 0;

    m_pAcqThread->AwakeThread(this);

}




//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonGrab() 
{
DWORD dwGroupIndex;


    // Determine if triggered mode is used

    if (m_apCam[0]->GetAcqParam(P_TRIGGER_ENABLE) != IFC_ENABLE)
    {
        AfxMessageBox(_T("Trigger is not enabled, please choose another camera type"));
        return;
    }

    // Init acquisition related variables

    m_dwSkippedFrameCounter = 0;

    m_bClearDisplay = FALSE;

    m_dwFrameCounter = 0;

    // Start the acquisition thread

    m_bIsGrabbing = TRUE;
    m_dwIsSOT_EventCounter = 0;

    m_pAcqThread->AwakeThread(this);

    // Draw window border

    for (dwGroupIndex = 0; dwGroupIndex < CAM_GROUP_COUNT; dwGroupIndex++)
    {
        DrawWindowBorder(m_apCamDisplay[dwGroupIndex]->m_hWnd);
    }

}






//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonFreeze() 
{

    // Stop the acquisition thread

    m_bIsGrabbing = FALSE;
    m_bIsSnapping = FALSE;

}




//------------------------------------------
//          OnButtonTrigger()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonTrigger() 
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
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}



//------------------------------------------
//          OnButtonTypeCam()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnButtonTypeCam() 
{

    if (m_bIsGrabbing || m_bIsSnapping)
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
//          OnRadioExt0()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnRadioExt0() 
{

    if (! (m_bIsGrabbing || m_bIsSnapping))
    {
        m_TrigSource = IFC_EXT0_TRIG;
    }

}

//------------------------------------------
//          OnRadioExt1()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnRadioExt1() 
{

    if (! (m_bIsGrabbing || m_bIsSnapping))
    {
        m_TrigSource = IFC_EXT1_TRIG;
    }

}



//------------------------------------------
//          OnRadioSoft()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnRadioSoft() 
{

    if (! (m_bIsGrabbing || m_bIsSnapping))
    {
        m_TrigSource = IFC_SOFT_TRIG;
    }

}


//------------------------------------------
//          OnRadioDispDisable()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnRadioDispDisable() 
{

    m_bDisplayEnable = FALSE;
	
}



//------------------------------------------
//          OnRadioDispEnable()
//------------------------------------------
void CIFC_PC2V_FrameDelayPlanarVerticalDlg::OnRadioDispEnable() 
{

    m_bDisplayEnable = TRUE;
	
}
