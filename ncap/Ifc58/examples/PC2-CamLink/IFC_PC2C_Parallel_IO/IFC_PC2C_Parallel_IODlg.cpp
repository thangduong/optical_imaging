//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2C_Parallel_IODlg.cpp
//
//  BIRTH DATE:     November 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.8)
//
//  OS:             Windows XP (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  HARDWARE:       PC2-CamLink Frame Grabber
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Parallel I/O Port functionnality demonstration
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ifc.h"                            // IFC related
#include "PC2Link.h"                        // PC2-CamLink related

#include "IFC_PC2C_Parallel_IO.h"
#include "IFC_PC2C_Parallel_IODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CIFC_PC2C_Parallel_IODlg::CIFC_PC2C_Parallel_IODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFC_PC2C_Parallel_IODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIFC_PC2C_Parallel_IODlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}




//------------------------------------------
//              DoDataExchange
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFC_PC2C_Parallel_IODlg)
	DDX_Control(pDX, IDC_STATIC_OUT_4, m_StaticOutBit4);
	DDX_Control(pDX, IDC_STATIC_OUT_3, m_StaticOutBit3);
	DDX_Control(pDX, IDC_STATIC_OUT_5, m_StaticOutBit5);
	DDX_Control(pDX, IDC_STATIC_OUT_6, m_StaticOutBit6);
	DDX_Control(pDX, IDC_STATIC_OUT_2, m_StaticOutBit2);
	DDX_Control(pDX, IDC_STATIC_OUT_7, m_StaticOutBit7);
	DDX_Control(pDX, IDC_STATIC_OUT_1, m_StaticOutBit1);
	DDX_Control(pDX, IDC_STATIC_OUT_0, m_StaticOutBit0);
	DDX_Control(pDX, IDC_CHECK_O_HIZ, m_CheckOutHighZ);
	DDX_Control(pDX, IDC_CHECK_O_STROBE, m_CheckOutStrobed);
	DDX_Control(pDX, IDC_CHECK_I_STROBE, m_CheckInStrobed);
	DDX_Control(pDX, IDC_EDIT_IN_VAL, m_EditInValue);
	DDX_Control(pDX, IDC_EDIT_OUT_VAL, m_EditOutValue);
	DDX_Control(pDX, IDC_RADIO_OUT_LOW, m_RadioOutLow);
	DDX_Control(pDX, IDC_EDIT_INT_COUNT, m_EditInterruptCount);
	DDX_Control(pDX, IDC_RADIO_IN_RISE, m_RadioInRising);
	DDX_Control(pDX, IDC_RADIO_INT_RISE, m_RadioIntRising);
	DDX_Control(pDX, IDC_STATIC_IN_7, m_StaticInBit7);
	DDX_Control(pDX, IDC_STATIC_IN_6, m_StaticInBit6);
	DDX_Control(pDX, IDC_STATIC_IN_5, m_StaticInBit5);
	DDX_Control(pDX, IDC_STATIC_IN_4, m_StaticInBit4);
	DDX_Control(pDX, IDC_STATIC_IN_3, m_StaticInBit3);
	DDX_Control(pDX, IDC_STATIC_IN_2, m_StaticInBit2);
	DDX_Control(pDX, IDC_STATIC_IN_1, m_StaticInBit1);
	DDX_Control(pDX, IDC_STATIC_IN_0, m_StaticInBit0);
	//}}AFX_DATA_MAP
}






BEGIN_MESSAGE_MAP(CIFC_PC2C_Parallel_IODlg, CDialog)
	//{{AFX_MSG_MAP(CIFC_PC2C_Parallel_IODlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_I_STROBE, OnCheckIStrobe)
	ON_BN_CLICKED(IDC_CHECK_O_STROBE, OnCheckOStrobe)
	ON_BN_CLICKED(IDC_CHECK_O_HIZ, OnCheckOHiz)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TRAP, OnButtonTrap)
	ON_BN_CLICKED(IDC_RADIO_IN_FALL, OnRadioInputStrobeFalling)
	ON_BN_CLICKED(IDC_RADIO_IN_RISE, OnRadioInputStrobeRising)
	ON_BN_CLICKED(IDC_RADIO_INT_FALL, OnRadioInterruptFalling)
	ON_BN_CLICKED(IDC_RADIO_INT_RISE, OnRadioInterruptRising)
	ON_BN_CLICKED(IDC_RADIO_OUT_HIGH, OnRadioOutStrobeHigh)
	ON_BN_CLICKED(IDC_RADIO_OUT_LOW, OnRadioOutStrobeLow)
	ON_BN_CLICKED(IDC_BUTTON_I_READ, OnButtonInputRead)
	ON_BN_CLICKED(IDC_BUTTON_O_SET, OnButtonOutputSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CIFC_PC2C_Parallel_IODlg::OnInitDialog()
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

    // Initializes IFC interrupt callback module

    if (InitIFC_Callback() == FALSE)
    {
        AfxMessageBox(_T("Could not initializes IFC interrupt callback object !!!"));
        EndDialog(7);
        return FALSE;
    }

    // Keep the handle of all the Output bit Light windows

    m_ahOutBitLight[0] = m_StaticOutBit0.m_hWnd;
    m_ahOutBitLight[1] = m_StaticOutBit1.m_hWnd;
    m_ahOutBitLight[2] = m_StaticOutBit2.m_hWnd;
    m_ahOutBitLight[3] = m_StaticOutBit3.m_hWnd;
    m_ahOutBitLight[4] = m_StaticOutBit4.m_hWnd;
    m_ahOutBitLight[5] = m_StaticOutBit5.m_hWnd;
    m_ahOutBitLight[6] = m_StaticOutBit6.m_hWnd;
    m_ahOutBitLight[7] = m_StaticOutBit7.m_hWnd;

    // Keep the handle of all the Input bit Light windows

    m_ahInBitLight[0] = m_StaticInBit0.m_hWnd;
    m_ahInBitLight[1] = m_StaticInBit1.m_hWnd;
    m_ahInBitLight[2] = m_StaticInBit2.m_hWnd;
    m_ahInBitLight[3] = m_StaticInBit3.m_hWnd;
    m_ahInBitLight[4] = m_StaticInBit4.m_hWnd;
    m_ahInBitLight[5] = m_StaticInBit5.m_hWnd;
    m_ahInBitLight[6] = m_StaticInBit6.m_hWnd;
    m_ahInBitLight[7] = m_StaticInBit7.m_hWnd;

    // Start a timer taking care of some GUI housekeeping

    if (SetTimer(TIMER_GUI, 1000, NULL) == NULL)
    {
        AfxMessageBox(_T("Could not start a timer !!!"));
    }

    // Init the I/O port to a default and known state

    // Interrupt edge mode

    m_bInterruptRisingEdge = TRUE;

    m_RadioIntRising.SetCheck(BST_CHECKED);
    m_EditInterruptCount.SetWindowText(_T("0"));
    m_pBrdMod->InportInterruptPolarity(IFC_RISING_EDGE);

    m_dwInterruptCounter = 0;

    // Input Strobe mode

    m_bInputStrobed         = FALSE;
    m_bInStrobeFallingEdge  = TRUE;

    m_RadioInRising.SetCheck(BST_CHECKED);
    m_pBrdMod->InportMode(FALSE, IFC_RISING_EDGE);

    // Read input data

    ReadInputPortBit(0, 0);

    // Output Strobe mode

    m_bOutputStrobed    = FALSE;
    m_bOutputHiZ        = FALSE;
    m_bOutStrobeLow     = TRUE;

    m_RadioOutLow.SetCheck(BST_CHECKED);
    m_pBrdMod->OutportStrobeVal(IFC_LEVEL_HIGH);

    // Output data cleared

    SetOutputPortBit(0, 0);
    SetOutputPortBit(1, 0);
    SetOutputPortBit(2, 0);
    SetOutputPortBit(3, 0);
    SetOutputPortBit(4, 0);
    SetOutputPortBit(5, 0);
    SetOutputPortBit(6, 0);
    SetOutputPortBit(7, 0);

    m_bAppClosing = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}




//------------------------------------------
//              OnPaint
//------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnPaint() 
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
	}
}




//------------------------------------------
//              OnQueryDragIcon
//------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIFC_PC2C_Parallel_IODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




//------------------------------------------
//              InitIFC_Capture
//------------------------------------------
BOOL CIFC_PC2C_Parallel_IODlg::InitIFC_Capture()
{

    // First, try to find and use the default configuration file "cl2test.txt"

    m_pBrdMod = IfxCreateCaptureModule("CL2", 0, "cl2test.txt");       // Use PC2-CamLink board # 0
    if (m_pBrdMod == NULL)
    {
        // Failed to find and use the default configuration file
        AfxMessageBox(_T("Could not find config file cl2test.txt !!!"));
        return FALSE;
    }

    return TRUE;

}




//------------------------------------------
//         ReleaseIFC_Capture
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::ReleaseIFC_Capture()
{

    if (m_pBrdMod)
    {
        delete m_pBrdMod;
        m_pBrdMod = NULL;
    }

}



//------------------------------------------
//              InitIFC_Callback
//------------------------------------------
BOOL CIFC_PC2C_Parallel_IODlg::InitIFC_Callback()
{

    //    m_pIntCallback_INP = m_pBrdMod->CreateIntrCallback(CL2_INTR_SOT, MyInterruptCallback_INP, this);
    m_pIntCallback_INP = m_pBrdMod->CreateIntrCallback(CL2_INTR_INPORT, MyInterruptCallback_INP, this);

    if (m_pIntCallback_INP == NULL)
        return FALSE;


    return TRUE;

}





//------------------------------------------
//              ReleaseIFC_Callback
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::ReleaseIFC_Callback()
{
LPVOID ExceptionAddress;
DWORD ExceptCode;


    ExceptCode= m_pIntCallback_INP->GetExceptionCode(&ExceptionAddress);

    m_pBrdMod->DeleteIntrCallback(m_pIntCallback_INP);
    m_pIntCallback_INP = NULL;

}



//------------------------------------------
//         MyInterruptCallback_INP
//------------------------------------------
// Function called when the "P2V_INTR_INPORT"
//  event occurs
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::MyInterruptCallback_INP(void *pContext)
{
CIFC_PC2C_Parallel_IODlg *pMyClass;
CString strToShow;


    // A static fct has no access to it's own class, need ptr to it

    pMyClass = (CIFC_PC2C_Parallel_IODlg *)pContext;

    if (pMyClass->m_bAppClosing)
        return;

    // Increment and show the Interrupt counter

    pMyClass->m_dwInterruptCounter++;

    strToShow.Format("%d", pMyClass->m_dwInterruptCounter);
    pMyClass->m_EditInterruptCount.SetWindowText(strToShow);

}



//------------------------------------------
//              ReleaseAll
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::ReleaseAll()
{

    // Release the "PCIntrCallback" object

    ReleaseIFC_Callback();

    // Release the "CICapMod" object

    ReleaseIFC_Capture();

    KillTimer(TIMER_GUI);

}



//-----------------------------------------------
//            SetOutputPortBit
//-----------------------------------------------
void CIFC_PC2C_Parallel_IODlg::SetOutputPortBit(DWORD dwBitIndex, DWORD dwBitValue) 
{
DWORD dwBitColumn;
CString strToShow;


    // Draw the bit in GREEN (low) or in RED (high)

    if (dwBitValue == 0)
    {
        DrawOutputBitLow(dwBitIndex);
    }
    else
    {
        DrawOutputBitHigh(dwBitIndex);
    }

    // Keep a shadow value of the Output Port

    dwBitColumn = 1;
    dwBitColumn <<= dwBitIndex;
    if (dwBitValue == 0)
    {
        m_ucOutputPort &= ~dwBitColumn;
    }
    else
    {
        m_ucOutputPort |= dwBitColumn;
    }

    // Display the HEX value in the Edit Box

    strToShow.Format(_T("0x%2.2X"), m_ucOutputPort);
    m_EditOutValue.SetWindowText(strToShow);

    // Physically set the bit on the Output Port

    if (m_bOutputHiZ)
    {
        m_pBrdMod->OutportVal(m_ucOutputPort, CL2_TRI_STATE_OUTPUT_VAL);
    }
    else
    {
        m_pBrdMod->OutportVal(m_ucOutputPort);
    }

}





//-----------------------------------------------
//            SetOutputPortByte
//-----------------------------------------------
void CIFC_PC2C_Parallel_IODlg::SetOutputPortByte(char cByteValue) 
{


    // Keep a shadow value of the Output Port

    m_ucOutputPort = cByteValue;

    // Physically set the bit on the Output Port

    if (m_bOutputHiZ)
    {
        m_pBrdMod->OutportVal(m_ucOutputPort, CL2_TRI_STATE_OUTPUT_VAL);
    }
    else
    {
        m_pBrdMod->OutportVal(m_ucOutputPort);
    }

}




//-----------------------------------------------
//            ReadInputPortBit
//-----------------------------------------------
BOOL CIFC_PC2C_Parallel_IODlg::ReadInputPortBit(DWORD dwBitIndex, DWORD dwBitValue) 
{
DWORD dwBitColumn;
CString strToShow;


    // Physically read the bits on the Input Port

    m_ucInputPort = (char)m_pBrdMod->InportVal();

    // Draw the read bit in GREEN (low) or in RED (high)

    dwBitColumn = 1;
    dwBitColumn <<= dwBitIndex;
    if ((m_ucInputPort & dwBitColumn) == 0)
    {
        DrawInputBitLow(dwBitIndex);
    }
    else
    {
        DrawInputBitHigh(dwBitIndex);
    }

    // Display the HEX value in the Edit Box

    strToShow.Format(_T("0x%2.2X"), m_ucInputPort);
    m_EditInValue.SetWindowText(strToShow);

    // Compare the read value with the passed value

    if ((m_ucInputPort & dwBitColumn) && (dwBitValue == 1))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}




//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CIFC_PC2C_Parallel_IODlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//          DrawIObits()
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DrawIObits()
{
DWORD dwBitScanner;
DWORD dwBitColumn;


    // Draw the status of the Output Port

    for (dwBitScanner = 0; dwBitScanner < 8; dwBitScanner++)
    {
        dwBitColumn = 1;
        dwBitColumn <<= dwBitScanner;
        if (m_ucOutputPort & dwBitColumn)
        {
            DrawOutputBitHigh(dwBitScanner);
        }
        else
        {
            DrawOutputBitLow(dwBitScanner);
        }
    }

    // Draw the status of the Input Port

    for (dwBitScanner = 0; dwBitScanner < 8; dwBitScanner++)
    {
        dwBitColumn = 1;
        dwBitColumn <<= dwBitScanner;
        if (m_ucInputPort & dwBitColumn)
        {
            DrawInputBitHigh(dwBitScanner);
        }
        else
        {
            DrawInputBitLow(dwBitScanner);
        }
    }

}





//------------------------------------------
//          DrawOutputBitHigh()
//------------------------------------------
// Draw a RED rectangle over a bit box signifying HIGH
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DrawOutputBitHigh(DWORD dwBitIndex)
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    hWindowLight = m_ahOutBitLight[dwBitIndex];

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyRedBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in RED camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}




//------------------------------------------
//          DrawOutputBitLow()
//------------------------------------------
// Draw a BLACK rectangle over a bit box signifying LOW
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DrawOutputBitLow(DWORD dwBitIndex)
{
CClientDC MyDC(this);
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    hWindowLight = m_ahOutBitLight[dwBitIndex];

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in BLACK camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}




//------------------------------------------
//          DrawInputBitHigh()
//------------------------------------------
// Draw a RED rectangle over a bit box signifying HIGH
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DrawInputBitHigh(DWORD dwBitIndex)
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    hWindowLight = m_ahInBitLight[dwBitIndex];

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyRedBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in RED camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}




//------------------------------------------
//          DrawInputBitLow()
//------------------------------------------
// Draw a BLACK rectangle over a bit box signifying LOW
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::DrawInputBitLow(DWORD dwBitIndex)
{
CClientDC MyDC(this);
CBrush MyBlackBrush (RGB(0,0,0));               // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));      // Exterior lines
CPen *pOldPen;
RECT RectDraw;
HWND hWindowLight;


    hWindowLight = m_ahInBitLight[dwBitIndex];

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    MyDC.SetMapMode(MM_TEXT);

    // Draw in BLACK camera rectangle

    GetWindowPosition(hWindowLight, &RectDraw);
    MyDC.Rectangle(&RectDraw);

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

}





//------------------------------------------
//              OnClose
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnClose() 
{
CString strWarnText;

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
//              OnCheckInputStrobe
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnCheckIStrobe() 
{

    if (m_CheckInStrobed.GetCheck() == 1)
    {
        m_bInputStrobed = TRUE;

        if (m_bInStrobeFallingEdge)
        {
            m_pBrdMod->InportMode(TRUE, IFC_FALLING_EDGE);
        }
        else
        {
            m_pBrdMod->InportMode(TRUE, IFC_RISING_EDGE);
        }
    }
    else
    {
        m_bInputStrobed = FALSE;

        m_pBrdMod->InportMode(FALSE, IFC_FALLING_EDGE);
    }

}




//------------------------------------------
//              OnCheckOutputStrobe
//------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnCheckOStrobe() 
{

    if (m_CheckOutStrobed.GetCheck() == 1)
    {
        m_bOutputStrobed = TRUE;
    }
    else
    {
        m_bOutputStrobed = FALSE;
    }

}




//-------------------------------------------
//          OnCheckOutputHiz()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnCheckOHiz() 
{

    if (m_CheckOutHighZ.GetCheck() == 1)
    {
        m_bOutputHiZ = TRUE;
        m_pBrdMod->OutportVal(m_ucOutputPort, CL2_TRI_STATE_OUTPUT_VAL);
    }
    else
    {
        m_bOutputHiZ = FALSE;
        m_pBrdMod->OutportVal(m_ucOutputPort);
    }

}





//-------------------------------------------
//          OnTimer()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnTimer(UINT nIDEvent) 
{
CString strToShow;


    if (nIDEvent == TIMER_GUI)
    {
        DrawIObits();
    }

	CDialog::OnTimer(nIDEvent);
}



//-------------------------------------------
//          OnRadioInputStrobeFalling()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioInputStrobeFalling() 
{

    m_bInStrobeFallingEdge = TRUE;

    if (m_bInputStrobed)
    {
        m_pBrdMod->InportMode(TRUE, IFC_FALLING_EDGE);
    }

}



//-------------------------------------------
//          OnRadioInputStrobeRising()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioInputStrobeRising() 
{

    m_bInStrobeFallingEdge = FALSE;

    if (m_bInputStrobed)
    {
        m_pBrdMod->InportMode(TRUE, IFC_RISING_EDGE);
    }

}



//-------------------------------------------
//          OnRadioInterruptFallingEdge()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioInterruptFalling() 
{

    m_bInterruptRisingEdge = FALSE;
    m_pBrdMod->InportInterruptPolarity(IFC_FALLING_EDGE);

}



//-------------------------------------------
//          OnRadioInterruptRisingEdge()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioInterruptRising() 
{

    m_bInterruptRisingEdge = TRUE;
    m_pBrdMod->InportInterruptPolarity(IFC_RISING_EDGE);

}



//-------------------------------------------
//          OnRadioOutStrobeHigh()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioOutStrobeHigh() 
{

    m_pBrdMod->OutportStrobeVal(IFC_LEVEL_LOW);
    m_bOutStrobeLow = FALSE;

}



//-------------------------------------------
//          OnRadioOutStrobeLow()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnRadioOutStrobeLow() 
{

    m_pBrdMod->OutportStrobeVal(IFC_LEVEL_HIGH);
    m_bOutStrobeLow = TRUE;

}


//-------------------------------------------
//          OnButtonTrap()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnButtonTrap() 
{
    // Will be called if user press Enter while
    // the focus is in an Edit Box.
    // Nothing is done but the application
    // will not end.
}






//-------------------------------------------
//          OnButtonReadInput()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnButtonInputRead() 
{

    ReadInputPortBit(0, 0);         // Physically read the input port

    DrawIObits();                   // Draw on the 8 lights

}



//-------------------------------------------
//          OnButtonSetOutput()
//-------------------------------------------
void CIFC_PC2C_Parallel_IODlg::OnButtonOutputSet() 
{
CString strToOutput;
char cOutValue;


    m_EditOutValue.GetWindowText(strToOutput);
    sscanf(strToOutput, "0x%x", &cOutValue);    // HEX to decimal

    SetOutputPortByte(cOutValue);    // Physically write on the output port

    DrawIObits();                               // Draw on the 8 lights

    if (m_bOutputStrobed)
    {
        if (m_bOutStrobeLow)
        {
            m_pBrdMod->OutportStrobeVal(IFC_LEVEL_LOW, 0);
            Sleep(50);
            m_pBrdMod->OutportStrobeVal(IFC_LEVEL_HIGH, 0);
        }
        else
        {
            m_pBrdMod->OutportStrobeVal(IFC_LEVEL_HIGH, 0);
            Sleep(50);
            m_pBrdMod->OutportStrobeVal(IFC_LEVEL_LOW, 0);
        }
    }

}
