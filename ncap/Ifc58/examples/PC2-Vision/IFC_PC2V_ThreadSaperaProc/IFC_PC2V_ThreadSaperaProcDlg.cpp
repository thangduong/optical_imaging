//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ThreadSaperaProcDlg.cpp
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
//                  Acquisition/Processing/Displaying using a thread for
//                  acquisition and another thread for processing and display.
//          Processing done using the Sapera Processing library.
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "CProSearch.h"                     // Search related classes
#include "Thread.h"                         // MFC based thread
#include "TimeMeasure.h"

#include "IFC_PC2V_ThreadSaperaProc.h"
#include "IFC_PC2V_ThreadSaperaProcDlg.h"

#include "CamSelDlg.h"                      // Cam Selector Dialog Box


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2V_ThreadSaperaProcDlg::CIFC_PC2V_ThreadSaperaProcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2V_ThreadSaperaProcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2V_ThreadSaperaProcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // IFC related object pointers

    m_pBrdMod                   = NULL;
    m_pCam                      = NULL;
    m_GrabID                    = NULL;
    m_pAcqImageConnection       = NULL;
    m_pResultImageConnection    = NULL;

    m_bIsGrabbing       = FALSE;
    m_bAppClosing       = FALSE;

    m_dwCamSizeX        = 0;
    m_dwCamSizeY        = 0;
    m_dwImageSize       = 0;

    m_dwFrameAcqCounter     = 0;
    m_dwFrameNotProcCounter = 0;
    m_fProcTime             = 0.0;

    m_pAcquisitionThread    = NULL;
    m_pProcessingThread     = NULL;

    m_pIntCallback_FNA      = NULL;

    m_pMySaperaBasicProcessor   = NULL;

}




void CIFC_PC2V_ThreadSaperaProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2V_ThreadSaperaProcDlg)
	DDX_Control(pDX, IDC_EDIT_DP_TIME, m_EditDisplayProcTime);
	DDX_Control(pDX, IDC_EDIT_DA_TIME, m_EditDisplayAcqTime);
	DDX_Control(pDX, IDC_COMBO_PROC_FUNC, m_ComboProcFunction);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_PROC, m_StaticDisplayResult);
	DDX_Control(pDX, IDC_EDIT_FLOST, m_EditFrameLost);
	DDX_Control(pDX, IDC_EDIT_FNP, m_EditFrameNotProc);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_ButtonCamSelect);
	DDX_Control(pDX, IDC_BUTTON_TRIGGER, m_ButtonTrigger);
	DDX_Control(pDX, IDC_BUTTON_FREEZE, m_ButtonFreeze);
	DDX_Control(pDX, IDC_BUTTON_SNAP, m_ButtonSnap);
	DDX_Control(pDX, IDC_BUTTON_GRAB, m_ButtonGrab);
	DDX_Control(pDX, IDC_EDIT_PROC_TIME, m_EditProcTime);
	DDX_Control(pDX, IDC_EDIT_FNA, m_EditFrameNotAcq);
	DDX_Control(pDX, IDC_EDIT_PROC_FR, m_EditProcFrameRate);
	DDX_Control(pDX, IDC_EDIT_ACQ_FR, m_EditAcqFrameRate);
	DDX_Control(pDX, IDC_EDIT_CUR_CAM, m_EditCameraType);
	DDX_Control(pDX, IDC_EDIT_CUR_PORT, m_EditCurrentPort);
	DDX_Control(pDX, IDC_EDIT_ACQ_FC, m_EditAcqFrameCount);
	DDX_Control(pDX, IDC_STATIC_DISPLAY_ACQ, m_StaticDisplayAcq);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CIFC_PC2V_ThreadSaperaProcDlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2V_ThreadSaperaProcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAM, OnButtonCam)
	ON_BN_CLICKED(IDC_BUTTON_FREEZE, OnButtonFreeze)
	ON_BN_CLICKED(IDC_BUTTON_GRAB, OnButtonGrab)
	ON_BN_CLICKED(IDC_BUTTON_SNAP, OnButtonSnap)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, OnButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_CBN_SELCHANGE(IDC_COMBO_PROC_FUNC, OnSelchangeComboProcFunc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2V_ThreadSaperaProcDlg::OnInitDialog()
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

    // Allocate Host capture memory

    if (AllocateCaptureMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate capture memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Allocate Host result memory

    if (AllocateResultMemory() == FALSE)
    {
        AfxMessageBox(_T("Could not allocate result memory !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes IFC Acquisition Image connection module

    m_pAcqImageConnection = InitIFC_AcqImageConnection(m_StaticDisplayAcq.GetSafeHwnd());
    if (m_pAcqImageConnection == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC acquisition Image connection object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Initializes IFC Result Image connection module

    m_pResultImageConnection = InitIFC_ResultImageConnection(m_StaticDisplayResult.GetSafeHwnd());
    if (m_pResultImageConnection == NULL)
    {
        AfxMessageBox(_T("Could not initializes IFC result Image connection object !!!"));
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

    m_pAcquisitionThread = new CThread;
    if (m_pAcquisitionThread == NULL)
    {
        AfxMessageBox(_T("Could not start the acquisition thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pAcquisitionThread->SetPriority(THREAD_PRIORITY_NORMAL);
    m_pAcquisitionThread->CallThis(ThreadAcqFunc);

    // Create the Processing and Display Thread

    m_pProcessingThread = new CThread;
    if (m_pProcessingThread == NULL)
    {
        AfxMessageBox(_T("Could not start the processing thread !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_pProcessingThread->SetPriority(THREAD_PRIORITY_BELOW_NORMAL);
    m_pProcessingThread->CallThis(ThreadProcFunc);

    // Create a Sapera Processing basic processor object

    m_pMySaperaBasicProcessor = new CProBasic();
    if (m_pMySaperaBasicProcessor == NULL)
    {
        AfxMessageBox(_T("Could not create a Sapera Processing Processor !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Fill the processing functions combo box

    m_CurrentProcFunc = PROCFUNC_NO_PROC;
    m_ComboProcFunction.AddString(_T("No Processing"));
    m_ComboProcFunction.AddString(_T("Thresholding"));
    m_ComboProcFunction.AddString(_T("Sobel Edge Dectector"));
    m_ComboProcFunction.AddString(_T("Convolution 2D"));
    m_ComboProcFunction.AddString(_T("Laplacian Filter"));
    m_ComboProcFunction.AddString(_T("Invert"));

    m_ComboProcFunction.SetCurSel(0);               // Default to No Processing

    return TRUE;  // return TRUE  unless you set the focus to a control

}






//------------------------------------------
//              ThreadAcqFunc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadSaperaProcDlg).
//
// Note that because we do not return control to the thread while
// grabbing, we must have a mechanism to end the working loop and
// return to the calling thread.
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ThreadAcqFunc(void *pContext) 
{
CIFC_PC2V_ThreadSaperaProcDlg *pMyClass;
CString strToShow;
int iSeqNum;
HIFCGRAB GrabID;
CICamera *pCam;
CICapMod *pBrdMod;
BYTE *pHostBuffer;


    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadSaperaProcDlg *)pContext;   // Context is the ptr to my class

    if (pMyClass == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // To alleviate the code, keep useful local variables

    GrabID              = pMyClass->m_GrabID;
    pCam                = pMyClass->m_pCam;
    pBrdMod             = pMyClass->m_pBrdMod;

    while (pMyClass->m_bIsGrabbing)
    {
        // Wait a frame ready in Host capture memory

        iSeqNum = pCam->GrabWaitFrameEx(GrabID, &pHostBuffer,
                                         IFC_WAIT_NEWER_FRAME, WAIT_ACQ_MAX_MSEC, TRUE);

        if ((iSeqNum == -1) && pMyClass->m_bIsGrabbing)
        {
            AfxMessageBox(_T("Could not acquire an image !!!"));
            pMyClass->m_pCam->Freeze();
            pMyClass->m_bIsGrabbing = FALSE;
        }
        else if (iSeqNum != -1)
        {
            pMyClass->m_MeasureAcqRate.TagTime();       // Measure the acq rate

            // Increment and show frame counter

            pMyClass->m_dwFrameAcqCounter++;
            strToShow.Format("%d", pMyClass->m_dwFrameAcqCounter);
            pMyClass->m_EditAcqFrameCount.SetWindowText(strToShow);

            // If processing queue can absorb another buffer,
            //  insert it and awake the processing thread
            // otherwise, release the buffer immediately (will never be processed)

            pMyClass->m_csProcList.Lock();                  // Get exclusive access to the processing buffer queue
            if (pMyClass->m_BufToProcList.GetCount() <= PROC_QUEUE_WATERMARK)
            {
                pMyClass->m_bSystemOverload = FALSE;

                pMyClass->m_aThreadProcParam[iSeqNum].pTheBuffer    = pHostBuffer;
                pMyClass->m_aThreadProcParam[iSeqNum].GrabID        = GrabID;
                pMyClass->m_aThreadProcParam[iSeqNum].iBufferIndex  = iSeqNum;

                pMyClass->m_BufToProcList.AddHead(&pMyClass->m_aThreadProcParam[iSeqNum]);

                pMyClass->m_pProcessingThread->AwakeThread(pMyClass);
            }
            else
            {
                // Release the acquisition buffer back into the ring

                pMyClass->m_pCam->GrabRelease(GrabID, iSeqNum);
                pMyClass->m_bSystemOverload = TRUE;
                pMyClass->m_dwFrameNotProcCounter++;
            }
            pMyClass->m_csProcList.Unlock();                  // Release access to the processing buffer queue

        }
    }

    // Return control to the calling thread

}




//------------------------------------------
//              ThreadProcFunc
//------------------------------------------
// Called by the acquisition thread, it is not executing under
// the thread of this dialog box class (CIFC_PC2V_ThreadSaperaProcDlg).
//
// Will process as many buffers waiting in the queue as it can.
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ThreadProcFunc(void *pContext) 
{
CIFC_PC2V_ThreadSaperaProcDlg *pMyClass;
PROC_THREAD_PARAM *pTheProcThreadParams;
BOOL bProcTest;
BYTE *pTheAcqBuffer;
int iBufferCountPending;


    // Get my context

    if (pContext == NULL)
    {
        AfxMessageBox(_T("Thread procedure received NULL context !!!"));
        return;                     // Return control to the calling thread
    }

    // A static function has no access to it's own class, need a ptr to it

    pMyClass = (CIFC_PC2V_ThreadSaperaProcDlg *)pContext;

    // While there is buffer to process in the queue

    pMyClass->m_csProcList.Lock();
    iBufferCountPending = pMyClass->m_BufToProcList.GetCount();
    pMyClass->m_csProcList.Unlock();

    while (iBufferCountPending > 0)
    {

        pMyClass->m_MeasureProcRate.TagTime();       // Measure the proc rate

        // Get a buffer to process from the queue

        pMyClass->m_csProcList.Lock();              // Get exclusive access to the processing buffer queue
        pTheProcThreadParams = (PROC_THREAD_PARAM *)pMyClass->m_BufToProcList.RemoveTail();
        pMyClass->m_csProcList.Unlock();            // Release access to the processing buffer queue

        // To alleviate the code, keep a local ptr to the last acquired buffer

        pTheAcqBuffer = pTheProcThreadParams->pTheBuffer;

        // Display the acquired frame in the ACQUISITION window

        pMyClass->m_MeasureDisplayAcqTime.StartTime();

        pMyClass->m_pAcqImageConnection->GetSrc()->SetBufferAddr(pTheAcqBuffer);

        pMyClass->m_pAcqImageConnection->Display();

        pMyClass->m_MeasureDisplayAcqTime.StopTime();
        pMyClass->m_fDisplayAcqTime = pMyClass->m_MeasureDisplayAcqTime.GetTimeMilli();

        // Prepare a Sapera Processing CProImage acuired buffer

        CProImage MyAcqImage(pMyClass->m_dwCamSizeX, pMyClass->m_dwCamSizeY, CProData::FormatUByte,
                             pTheAcqBuffer, FALSE);

        // Prepare a Sapera Processing CProImage result buffer

        CProImage MyResultImage(pMyClass->m_dwCamSizeX, pMyClass->m_dwCamSizeY, CProData::FormatUByte,
                             pMyClass->m_pHostResultMemory, FALSE);

        // Prepare a Sapera Processing CProKernel convolution matrix

        CProKernel myKernelHiPass(CProKernel::TypeHighPass1);

        // Apply a Sapera Processing function to the image

        pMyClass->m_MeasureProcTime.StartTime();

        switch(pMyClass->m_CurrentProcFunc)
        {
        case PROCFUNC_NO_PROC :

            bProcTest = MyResultImage.Copy(MyAcqImage);
            break;

        case PROCFUNC_THRESHOLD :

            bProcTest = pMyClass->m_pMySaperaBasicProcessor->Thresh(MyAcqImage, MyResultImage, 75.0, 175.0);
            break;

        case PROCFUNC_SOBEL_EDGE :

            bProcTest = pMyClass->m_pMySaperaBasicProcessor->EdgeDetect(MyAcqImage, MyResultImage,
                                                   CProBasic::EdgeDetectSobel, CProBasic::OutputGrayScale);
            break;

        case PROCFUNC_CONV_2D :

            bProcTest = pMyClass->m_pMySaperaBasicProcessor->Conv2d(MyAcqImage, MyResultImage, myKernelHiPass);
            break;

        case PROCFUNC_LAPLACIAN :

            bProcTest = pMyClass->m_pMySaperaBasicProcessor->Laplace(MyAcqImage, MyResultImage, CProBasic::Laplace0);
            break;

        case PROCFUNC_INVERT :

            bProcTest = pMyClass->m_pMySaperaBasicProcessor->Invert(MyAcqImage, MyResultImage);
            break;

        }

        pMyClass->m_MeasureProcTime.StopTime();
        pMyClass->m_fProcTime = pMyClass->m_MeasureProcTime.GetTimeMilli();

        // Check if the processing went OK

        if (bProcTest == FALSE)
        {
            pMyClass->m_pCam->GrabRelease(pTheProcThreadParams->GrabID, pTheProcThreadParams->iBufferIndex);
            AfxMessageBox(_T("Processing failure, do you have a Sapera Processing licence installed ?"));
            pMyClass->m_bIsGrabbing = FALSE;
            pMyClass->m_pCam->Freeze();
            return;
        }

        // Display the processed frame in the RESULT window

        pMyClass->m_MeasureDisplayProcTime.StartTime();

        pMyClass->m_pResultImageConnection->GetSrc()->SetBufferAddr(pMyClass->m_pHostResultMemory);

        pMyClass->m_pResultImageConnection->Display();

        pMyClass->m_MeasureDisplayProcTime.StopTime();
        pMyClass->m_fDisplayProcTime = pMyClass->m_MeasureDisplayProcTime.GetTimeMilli();

        // Release the acquisition buffer back into the ring

        pMyClass->m_pCam->GrabRelease(pTheProcThreadParams->GrabID, pTheProcThreadParams->iBufferIndex);

        // Look if there is more buffer queued for processing

        pMyClass->m_csProcList.Lock();
        iBufferCountPending = pMyClass->m_BufToProcList.GetCount();
        pMyClass->m_csProcList.Unlock();
    }

    // Return control to the calling thread

}




//------------------------------------------
//          DrawWindowBorder()
//------------------------------------------
// This function draw a border around the
//  view window.
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::DrawWindowBorder(HWND hWnd)
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
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2V_ThreadSaperaProcDlg::InitIFC_Capture()
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
//          AllocateCaptureMemory
//------------------------------------------
BOOL CIFC_PC2V_ThreadSaperaProcDlg::AllocateCaptureMemory()
{
DWORD dwAllocSize;


    dwAllocSize = m_dwImageSize * BUFFER_COUNT;
    if (dwAllocSize == 0)
        return FALSE;

    m_pHostAcqMemory = (BYTE *)malloc(dwAllocSize);
    if (m_pHostAcqMemory == NULL)
        return FALSE;

    m_AcqMemLockHandle = m_pBrdMod->LockMem(m_pHostAcqMemory, dwAllocSize);

    return TRUE;
}



//------------------------------------------
//          AllocateResultMemory
//------------------------------------------
BOOL CIFC_PC2V_ThreadSaperaProcDlg::AllocateResultMemory()
{

    // Allocate a processing result buffer

    m_pHostResultMemory = (BYTE *)malloc(m_dwImageSize);
    if (m_pHostResultMemory == NULL)
        return FALSE;

    return TRUE;
}



//------------------------------------------
//          ReleaseCaptureMemory
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseCaptureMemory()
{

    if (m_pHostAcqMemory)
    {
        m_pBrdMod->UnLockMem(m_AcqMemLockHandle);
        free(m_pHostAcqMemory);
    }

    m_pHostAcqMemory = NULL;

}


//------------------------------------------
//          ReleaseResultMemory
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseResultMemory()
{

    if (m_pHostResultMemory)
    {
        free(m_pHostResultMemory);
    }

    m_pHostResultMemory = NULL;

}

//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2V_ThreadSaperaProcDlg::InitIFC_Callback()
{

    // Want a callback on the SKIPPED FIELD detection (frame not acquired)

    m_pIntCallback_FNA = m_pBrdMod->CreateIntrCallback(P2V_INTR_SKIPPED_FIELD, MyCallback_FNA, this);

    if (m_pIntCallback_FNA == NULL)
        return FALSE;

    return TRUE;

}






//------------------------------------------
//         InitIFC_AcqImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_ThreadSaperaProcDlg::InitIFC_AcqImageConnection(HWND hWnd)
{
CImgConn *ImgConn;


    ImgConn = IfxCreateImgConn(m_pHostAcqMemory, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY,
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
//         InitIFC_ResultImageConnection
//------------------------------------------
CImgConn *CIFC_PC2V_ThreadSaperaProcDlg::InitIFC_ResultImageConnection(HWND hWnd)
{
CImgConn *ImgConn;


    ImgConn = IfxCreateImgConn(m_pHostResultMemory, (WORD)m_dwCamSizeX, (WORD)m_dwCamSizeY,
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
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseIFC_Capture()
{

    delete m_pBrdMod;
    m_pBrdMod = NULL;

}




//------------------------------------------
//        ReleaseIFC_AcqImageConnection
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseIFC_AcqImageConnection()
{

    if (m_pAcqImageConnection)
    {
        delete m_pAcqImageConnection;
        m_pAcqImageConnection = NULL;
    }

}




//------------------------------------------
//        ReleaseIFC_ResultImageConnection
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseIFC_ResultImageConnection()
{

    if (m_pResultImageConnection)
    {
        delete m_pResultImageConnection;
        m_pResultImageConnection = NULL;
    }

}



//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode = m_pIntCallback_FNA->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_FNA);
    m_pIntCallback_FNA = NULL;


}


//------------------------------------------
//              MyCallback_EOF
//------------------------------------------
// Function called when the "SKIPPED FIELD"
// event occurs
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::MyCallback_FNA(void *pContext)
{
CIFC_PC2V_ThreadSaperaProcDlg *pMyClass;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2V_ThreadSaperaProcDlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Increment the event counter

    pMyClass->m_dwFrameNotAcqCounter++;

}



//------------------------------------------
//              OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnPaint() 
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

        m_pAcqImageConnection->Display();
        m_pResultImageConnection->Display();

        if (m_bClearDisplay)
        {
            ClearDisplay();
        }

        DrawWindowBorder(m_StaticDisplayAcq.m_hWnd);
        DrawWindowBorder(m_StaticDisplayResult.m_hWnd);

        m_dwOnPaintCounter++;
	}
}



//------------------------------------------
//              OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
//------------------------------------------
HCURSOR CIFC_PC2V_ThreadSaperaProcDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::ReleaseAll()
{

    // Terminate the processing thread

    delete m_pProcessingThread;
    m_pProcessingThread = NULL;

    // Terminate the acquisition thread

    delete m_pAcquisitionThread;
    m_pAcquisitionThread = NULL;

    // Release the Sapera Processing processor object

    delete m_pMySaperaBasicProcessor;
    m_pMySaperaBasicProcessor = NULL;

    // Release the Host processing result memory

    ReleaseResultMemory();

    // Release the Host capture memory

    ReleaseCaptureMemory();

    // The "CImgConn" objects must be deleted before the "CICapMod" object

    ReleaseIFC_ResultImageConnection();
    ReleaseIFC_AcqImageConnection();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_STAT);
    KillTimer(TIMER_GUI);

}



//------------------------------------------
//              SetPortAndCamType
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::SetPortAndCamType(DWORD dwActivePort, char *pszCamType)
{
CAM_ATTR attr;
CString strToShow;


    // Show active port

    strToShow.Format("%d", dwActivePort + 1);
    m_EditCurrentPort.SetWindowText(strToShow);

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
void CIFC_PC2V_ThreadSaperaProcDlg::ClearDisplay()
{
CClientDC MyDC(this);
CBrush *pOldBrush;
RECT RectDraw;


    pOldBrush = (CBrush *)MyDC.SelectStockObject(BLACK_BRUSH);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticDisplayAcq.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    GetWindowPosition(m_StaticDisplayResult.GetSafeHwnd(), &RectDraw);
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
BOOL CIFC_PC2V_ThreadSaperaProcDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
void CIFC_PC2V_ThreadSaperaProcDlg::ShowStatistics() 
{
float fRate;
CString strToShow;
IFC_GRAB_STATS GrabStats;


    if (! m_bIsGrabbing)
    {
        m_EditAcqFrameRate.SetWindowText( _T("*****"));
        m_EditProcFrameRate.SetWindowText( _T("*****"));
        return;
    }

    // Compute and show acquisition frame rate

    fRate = m_MeasureAcqRate.GetTime();
    if (fRate != 0.0)
    {
        fRate = (float)1.0 / fRate;
        strToShow.Format("%.2f", fRate);
        m_EditAcqFrameRate.SetWindowText(strToShow);
    }
    else
    {
        m_EditAcqFrameRate.SetWindowText( _T("*****"));
    }

    // Compute and show processing frame rate

    fRate = m_MeasureProcRate.GetTime();
    if (fRate != 0.0)
    {
        fRate = (float)1.0 / fRate;
        strToShow.Format("%.2f", fRate);
        m_EditProcFrameRate.SetWindowText(strToShow);
    }
    else
    {
        m_EditProcFrameRate.SetWindowText( _T("*****"));
    }

    // Show frame lost count

    m_pBrdMod->GetGrabStats(m_GrabID, &GrabStats);

    strToShow.Format("%d", GrabStats.NumberOfFramesLost);
    m_EditFrameLost.SetWindowText(strToShow);

    // Show not acquired frame count

    strToShow.Format("%d", m_dwFrameNotAcqCounter);
    m_EditFrameNotAcq.SetWindowText(strToShow);

    // Show not processed frame count

    strToShow.Format("%d", m_dwFrameNotProcCounter);
    m_EditFrameNotProc.SetWindowText(strToShow);

    // Show processing time

    strToShow.Format("%.2f ms", m_fProcTime);
    m_EditProcTime.SetWindowText(strToShow);

    // Show Acq frame display time

    strToShow.Format("%.2f ms", m_fDisplayAcqTime);
    m_EditDisplayAcqTime.SetWindowText(strToShow);

    // Show processed frame display time

    strToShow.Format("%.2f ms", m_fDisplayProcTime);
    m_EditDisplayProcTime.SetWindowText(strToShow);

}






//------------------------------------------
//              UpdateButtons
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::UpdateButtons()
{
    // Depending on situation, some buttons are disabled

    m_ButtonGrab.EnableWindow(! m_bIsGrabbing);
    m_ButtonSnap.EnableWindow(! m_bIsGrabbing);
    m_ButtonFreeze.EnableWindow(m_bIsGrabbing);
    m_ButtonTrigger.EnableWindow(m_bTriggerMode && m_bIsGrabbing);

    m_ButtonCamSelect.EnableWindow(! m_bIsGrabbing);
}




//------------------------------------------
//              OnButtonCam
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonCam() 
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

        ReleaseIFC_AcqImageConnection();

        // Release current Host result memory and image connection object

        ReleaseResultMemory();

        ReleaseIFC_ResultImageConnection();

        // Allocate new host Capture Memory and Image Connection object

        if (AllocateCaptureMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate capture memory !!!"));
        }

        m_pAcqImageConnection = InitIFC_AcqImageConnection(m_StaticDisplayAcq.GetSafeHwnd());
        if (m_pAcqImageConnection == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Acquisition Image connection object !!!"));
        }

        // Allocate new host Result Memory and Image Connection object

        if (AllocateResultMemory() == FALSE)
        {
            AfxMessageBox(_T("Could not allocate result memory !!!"));
        }

        m_pResultImageConnection = InitIFC_ResultImageConnection(m_StaticDisplayResult.GetSafeHwnd());
        if (m_pResultImageConnection == NULL)
        {
            AfxMessageBox(_T("Could not initializes IFC Result Image connection object !!!"));
        }

        // Clear the display window

        m_bClearDisplay = TRUE;
    }

}



//------------------------------------------
//              OnButtonFreeze
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonFreeze() 
{

    m_bIsGrabbing = FALSE;

    m_pCam->Freeze();

}



//------------------------------------------
//              OnButtonGrab
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonGrab() 
{

    m_dwFrameAcqCounter     = 0;
    m_dwFrameNotProcCounter = 0;
    m_dwFrameNotAcqCounter  = 0;
    m_fProcTime             = 0.0;

    m_bClearDisplay     = FALSE;
    m_bSystemOverload   = FALSE;

    m_GrabID = m_pCam->Grab(IFC_GOPT_AUTO_FRAME_LOCK, m_pHostAcqMemory,
                             BUFFER_COUNT, IFC_INFINITE_FRAMES);

    m_bIsGrabbing = TRUE;
    m_pAcquisitionThread->AwakeThread(this);

}



//------------------------------------------
//              OnButtonSnap
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonSnap() 
{
CString strToShow;
BOOL bProcTest;


    if (m_bIsGrabbing)
    {
        AfxMessageBox(_T("Stop grabbing before snapping"));
        return;
    }

    m_bClearDisplay = FALSE;

    m_pCam->Snap(m_pHostAcqMemory, 0, 0, 0, 0);

    // Increment and show acquisition frame counter

    m_dwFrameAcqCounter++;
    strToShow.Format("%d", m_dwFrameAcqCounter);
    m_EditAcqFrameCount.SetWindowText(strToShow);

    // Show acquired frame in the ACQUIRED window

    m_pAcqImageConnection->GetSrc()->SetBufferAddr(m_pHostAcqMemory);
    m_pAcqImageConnection->Display();

    // Prepare a Sapera Processing CProImage acuired buffer

    CProImage MyAcqImage(m_dwCamSizeX, m_dwCamSizeY, CProData::FormatUByte,
                         m_pHostAcqMemory, FALSE);

    // Prepare a Sapera Processing CProImage result buffer

    CProImage MyResultImage(m_dwCamSizeX, m_dwCamSizeY, CProData::FormatUByte,
                         m_pHostResultMemory, FALSE);

    // Prepare a Sapera Processing CProKernel convolution matrix

    CProKernel myKernelHiPass(CProKernel::TypeHighPass1);

    switch(m_CurrentProcFunc)
    {
    case PROCFUNC_NO_PROC :

        bProcTest = MyResultImage.Copy(MyAcqImage);
        break;

    case PROCFUNC_THRESHOLD :

        bProcTest = m_pMySaperaBasicProcessor->Thresh(MyAcqImage, MyResultImage, 75.0, 175.0);
        break;

    case PROCFUNC_SOBEL_EDGE :

        bProcTest = m_pMySaperaBasicProcessor->EdgeDetect(MyAcqImage, MyResultImage,
                                               CProBasic::EdgeDetectSobel, CProBasic::OutputGrayScale);
        break;

    case PROCFUNC_CONV_2D :

        bProcTest = m_pMySaperaBasicProcessor->Conv2d(MyAcqImage, MyResultImage, myKernelHiPass);
        break;

    case PROCFUNC_LAPLACIAN :

        bProcTest = m_pMySaperaBasicProcessor->Laplace(MyAcqImage, MyResultImage, CProBasic::Laplace0);
        break;

    case PROCFUNC_INVERT :

        bProcTest = m_pMySaperaBasicProcessor->Invert(MyAcqImage, MyResultImage);
        break;

    }

    // Check if the processing went OK

    if (bProcTest == FALSE)
    {
        AfxMessageBox(_T("Processing failure, do you have a Sapera Processing licence installed ?"));
        return;
    }

    // Show processed frame in the PROCESSED window

    m_MeasureDisplayProcTime.StartTime();

    m_pResultImageConnection->GetSrc()->SetBufferAddr(m_pHostResultMemory);

    m_pResultImageConnection->Display();

}






//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnClose() 
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
void CIFC_PC2V_ThreadSaperaProcDlg::OnTimer(UINT nIDEvent) 
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
            DrawWindowBorder(m_StaticDisplayAcq.m_hWnd);
            DrawWindowBorder(m_StaticDisplayResult.m_hWnd);
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
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonTrigger() 
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

    // Restore original TRIGGER source

    if (bTriggerSrcWasExternal)
    {
        m_pCam->SetAcqParam(P_TRIGGER_SRC, TriggerSource);      // TRIGGER source is external
    }
}




//------------------------------------------
//              OnButtonTrap
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}


//------------------------------------------
//              OnSelchangeComboProcFunc
//------------------------------------------
void CIFC_PC2V_ThreadSaperaProcDlg::OnSelchangeComboProcFunc() 
{
    m_CurrentProcFunc = (PROC_FUNCTION)m_ComboProcFunction.GetCurSel();
}
