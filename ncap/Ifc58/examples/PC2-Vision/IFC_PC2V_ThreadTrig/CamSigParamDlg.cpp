//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           CCamSigParamDlg.cpp
//
//  BIRTH DATE:     January 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.6.1)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Dialog Box to edit the camera signals parameters.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related
#include "math.h"                           // ceil()

#include "StrobeParamDlg.h"
#include "CamSigParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//              Constructor
//------------------------------------------
CCamSigParamDlg::CCamSigParamDlg(CWnd* pParent, CICamera *pCam)
	: CDialog(CCamSigParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamSigParamDlg)
	//}}AFX_DATA_INIT

    m_pCam              = pCam;

    GetParamMinMax();           // Init local MIN-MAX parameter values

    GetParamValue();            // Init local parameter values

    ValidateParamValue();       // Make sure parameter values are within MIN-MAX

    RetouchVsDelay();           // Make sure the Vs is AFTER the FRAME RESET pulse

}




//------------------------------------------
//              DoDataExchange
//------------------------------------------
void CCamSigParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSigParamDlg)
	DDX_Control(pDX, IDC_BUTTON_STROBE_PARM, m_ButtonStrobeParms);
	DDX_Control(pDX, IDC_STATIC_STROBE_TIMING, m_StaticTimingBarStrobe);
	DDX_Control(pDX, IDC_EDIT_VS_WIDTH, m_EditVSyncWidth);
	DDX_Control(pDX, IDC_EDIT_FR_WIDTH, m_EditFrameResetWidth);
	DDX_Control(pDX, IDC_EDIT_VS_DELAY, m_EditVSyncDelay);
	DDX_Control(pDX, IDC_EDIT_TRIG_DEBOUNCE, m_EditTrigDebounce);
	DDX_Control(pDX, IDC_EDIT_FR_DELAY, m_EditFrameResetDelay);
	DDX_Control(pDX, IDC_STATIC_FR_TIMING, m_StaticTimingBarFr);
	DDX_Control(pDX, IDC_STATIC_VS_TIMING, m_StaticTimingBarVs);
	DDX_Control(pDX, IDC_STATIC_TRIG_TIMING, m_StaticTimingBarTrig);
	DDX_Control(pDX, IDC_BUTTON_VS_HI, m_ButtonVsHi);
	DDX_Control(pDX, IDC_BUTTON_VS_LO, m_ButtonVsLo);
	DDX_Control(pDX, IDC_BUTTON_FR_HI, m_ButtonFrHi);
	DDX_Control(pDX, IDC_BUTTON_FR_LO, m_ButtonFrLo);
	DDX_Control(pDX, IDC_BUTTON_TRIG_HI, m_ButtonTrigHi);
	DDX_Control(pDX, IDC_BUTTON_TRIG_LO, m_ButtonTrigLo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSigParamDlg, CDialog)
	//{{AFX_MSG_MAP(CCamSigParamDlg)
	ON_BN_CLICKED(IDC_BUTTON_FR_HI, OnButtonFrHi)
	ON_BN_CLICKED(IDC_BUTTON_FR_LO, OnButtonFrLo)
	ON_BN_CLICKED(IDC_BUTTON_TRIG_HI, OnButtonTrigHi)
	ON_BN_CLICKED(IDC_BUTTON_TRIG_LO, OnButtonTrigLo)
	ON_BN_CLICKED(IDC_BUTTON_VS_HI, OnButtonVsHi)
	ON_BN_CLICKED(IDC_BUTTON_VS_LO, OnButtonVsLo)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_TRIG_DEBOUNCE, OnChangeEditTrigDebounce)
	ON_EN_CHANGE(IDC_EDIT_FR_DELAY, OnChangeEditFrDelay)
	ON_EN_CHANGE(IDC_EDIT_FR_WIDTH, OnChangeEditFrWidth)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_VS_DELAY, OnChangeEditVsDelay)
	ON_EN_CHANGE(IDC_EDIT_VS_WIDTH, OnChangeEditVsWidth)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_BUTTON_STROBE_PARM, OnButtonStrobeParm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//------------------------------------------
//           OnInitDialog
//------------------------------------------
BOOL CCamSigParamDlg::OnInitDialog() 
{
CString strToFormat;


    CDialog::OnInitDialog();

    //-----------------------------------------
    // Edit box with the current numeric value

    InitNumericGUI();

    //-----------------------------------------
    // Start a timer managing the GUI housekeeping

    if (SetTimer(TIMER_PARAM_GUI, 500, NULL) == NULL)
    {
        AfxMessageBox(_T("Could not start a timer !!!"));
        EndDialog(7);
        return FALSE;
    }

    m_dwDebugCounter = 0;

    m_dwOnChangeCounter = 0;

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}



//------------------------------------------
//           GetParamValue
//------------------------------------------
// Get the current parameter values from IFC.
//------------------------------------------
void CCamSigParamDlg::GetParamValue(void)
{
double dParamValue;


    //-------------------------------------------
    // Init the TRIGGER polarity

    m_bTrigPolIsHigh = DEFAULT_TRIG_POL_HI;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_TRIGGER_POLARITY) == IFC_ACTIVE_HIGH)
        {
            m_bTrigPolIsHigh = TRUE;
        }
        else
        {
            m_bTrigPolIsHigh = FALSE;
        }
    }

    //-------------------------------------------
    // Init the TRIGGER debounce

    m_dwTriggerDebounce = DEFAULT_TRIG_DEBOUNCE;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P_TRIGGER_DEBOUNCE);
        m_dwTriggerDebounce = (DWORD)dParamValue;
    }

    //-----------------------------------------
    // Init the FRAME RESET polarity

    m_bFrPolIsHigh = DEFAULT_FR_POL_HI;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_FRAME_RESET_POLARITY) == IFC_ACTIVE_HIGH)
        {
            m_bFrPolIsHigh = TRUE;
        }
        else
        {
            m_bFrPolIsHigh = FALSE;
        }
    }

    //-----------------------------------------
    // Init the FRAME RESET Delay

    m_dwFrameResetDelay = DEFAULT_FR_DELAY;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P_FRAME_RESET_OFFSET);
        m_dwFrameResetDelay = (DWORD)dParamValue;
    }

    //-----------------------------------------
    // Init the FRAME RESET width

    m_dwFrameResetWidth = DEFAULT_FR_WIDTH;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P_FRAME_RESET_SIZE);
        m_dwFrameResetWidth = (DWORD)dParamValue;
    }

    //-----------------------------------------
    // Init the VS polarity

    m_bVsPolIsHigh = DEFAULT_VS_POL_HI;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_VSYNC_POLARITY) == IFC_ACTIVE_HIGH)
        {
            m_bVsPolIsHigh = TRUE;
        }
        else
        {
            m_bVsPolIsHigh = FALSE;
        }
    }

    //-----------------------------------------
    // Init the VS Delay

    m_dwVSyncDelay = DEFAULT_VS_DELAY;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P2V_VS_PULSE_OFFSET);
        m_dwVSyncDelay = (DWORD)dParamValue;
    }

    //-----------------------------------------
    // Init the VS Width

    m_dwVSyncWidth = DEFAULT_VS_WIDTH;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P2V_VS_PULSE_DURATION);
        m_dwVSyncWidth = (DWORD)dParamValue;
    }

}





//------------------------------------------
//           GetParamMinMax
//------------------------------------------
// Get from IFC the MIN and MAX value for
// the numeric parameters.
//------------------------------------------
void CCamSigParamDlg::GetParamMinMax() 
{
IFC_PARAM_CAPS VsCaps;


    //-----------------------------------------------------
    // Init the TRIGGER Debounce MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P_TRIGGER_DEBOUNCE, &VsCaps);
        m_dwTrigDebounceMin = (DWORD)VsCaps.Range.Min;
        m_dwTrigDebounceMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwTrigDebounceMin = 0;
        m_dwTrigDebounceMax = 1;
    }

    //------------------------------------------------------
    // Init the FRAME RESET Delay MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P_FRAME_RESET_OFFSET, &VsCaps);
        m_dwFrDelayMin = (DWORD)VsCaps.Range.Min;
        m_dwFrDelayMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwFrDelayMin = 0;
        m_dwFrDelayMax = 1;
    }

    //-----------------------------------------
    // Init the FRAME RESET Width MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P_FRAME_RESET_SIZE, &VsCaps);
        m_dwFrWidthMin = (DWORD)VsCaps.Range.Min;
        m_dwFrWidthMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwFrWidthMin = 0;
        m_dwFrWidthMax = 1;
    }

    //-----------------------------------------
    // Init the VS Delay MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P2V_VS_PULSE_OFFSET, &VsCaps);
        m_dwVsDelayMin = (DWORD)VsCaps.Range.Min;
        m_dwVsDelayMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwVsDelayMin = 0;
        m_dwVsDelayMax = 1;
    }

    //-----------------------------------------
    // Init the VS Width MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P2V_VS_PULSE_DURATION, &VsCaps);
        m_dwVsWidthMin = (DWORD)VsCaps.Range.Min;
        m_dwVsWidthMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwVsWidthMin = 0;
        m_dwVsWidthMax = 1;
    }

}



//------------------------------------------
//           ValidateParamValue
//------------------------------------------
// Make sure numeric parameters are within
// the capability of the system.
//------------------------------------------
BOOL CCamSigParamDlg::ValidateParamValue() 
{
BOOL bWasOK;
DWORD dwTestValue;


    bWasOK = TRUE;

    //-----------------------------------------------------
    // Validate the TRIGGER Debounce numeric value

    dwTestValue = m_dwTriggerDebounce;
    dwTestValue = min(m_dwTrigDebounceMax, dwTestValue);
    dwTestValue = max(m_dwTrigDebounceMin, dwTestValue);
    if (dwTestValue != m_dwTriggerDebounce)
    {
        bWasOK = FALSE;
        m_dwTriggerDebounce = dwTestValue;
    }

    //------------------------------------------------------
    // Validate the FRAME RESET Delay numeric value

    dwTestValue = m_dwFrameResetDelay;
    dwTestValue = min(m_dwFrDelayMax, dwTestValue);
    dwTestValue = max(m_dwFrDelayMin, dwTestValue);
    if (dwTestValue != m_dwFrameResetDelay)
    {
        bWasOK = FALSE;
        m_dwFrameResetDelay = dwTestValue;
    }

    //-----------------------------------------
    // Validate the FRAME RESET Width numeric value

    dwTestValue = m_dwFrameResetWidth;
    dwTestValue = min(m_dwFrWidthMax, dwTestValue);
    dwTestValue = max(m_dwFrWidthMin, dwTestValue);
    if (dwTestValue != m_dwFrameResetWidth)
    {
        bWasOK = FALSE;
        m_dwFrameResetWidth = dwTestValue;
    }

    //-----------------------------------------
    // Validate the VS Delay numeric value

    dwTestValue = m_dwVSyncDelay;
    dwTestValue = min(m_dwVsDelayMax, dwTestValue);
    dwTestValue = max(m_dwVsDelayMin, dwTestValue);
    if (dwTestValue != m_dwVSyncDelay)
    {
        bWasOK = FALSE;
        m_dwVSyncDelay = dwTestValue;
    }

    //-----------------------------------------
    // Validate the VS Width numeric value

    dwTestValue = m_dwVSyncWidth;
    dwTestValue = min(m_dwVsWidthMax, dwTestValue);
    dwTestValue = max(m_dwVsWidthMin, dwTestValue);
    if (dwTestValue != m_dwVSyncWidth)
    {
        bWasOK = FALSE;
        m_dwVSyncWidth = dwTestValue;
    }

    return bWasOK;
}





//------------------------------------------
//           UpdateParamToIFC
//------------------------------------------
void CCamSigParamDlg::UpdateParamToIFC() 
{
CString strUser;

    if (m_pCam)
    {

        //-------------------------
        // Update the TRIGGER polarity

        if (m_bTrigPolIsHigh)
        {
            m_pCam->SetAcqParam(P_TRIGGER_POLARITY, IFC_ACTIVE_HIGH);
        }
        else
        {
            m_pCam->SetAcqParam(P_TRIGGER_POLARITY, IFC_ACTIVE_LOW);
        }

        //-------------------------
        // Update the FRAME RESET polarity

        if (m_bFrPolIsHigh)
        {
            m_pCam->SetAcqParam(P_FRAME_RESET_POLARITY, IFC_ACTIVE_HIGH);
        }
        else
        {
            m_pCam->SetAcqParam(P_FRAME_RESET_POLARITY, IFC_ACTIVE_LOW);
        }

        //-------------------------
        // Update the V sync polarity

        if (m_bVsPolIsHigh)
        {
            m_pCam->SetAcqParam(P_VSYNC_POLARITY, IFC_ACTIVE_HIGH);
        }
        else
        {
            m_pCam->SetAcqParam(P_VSYNC_POLARITY, IFC_ACTIVE_LOW);
        }

        //-------------------------
        // Update the TRIGGER debounce

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("TRIGGER Debounce out of range !!!"));
        }
        m_pCam->SetAcqParam(P_TRIGGER_DEBOUNCE, m_dwTriggerDebounce);

        //-------------------------
        // Update the FRAME RESET delay

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Frame Reset Delay out of range !!!"));
        }
        m_pCam->SetAcqParam(P_FRAME_RESET_OFFSET, m_dwFrameResetDelay);

        //-------------------------
        // Update the FRAME RESET width

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Frame Reset Width out of range !!!"));
        }
        m_pCam->SetAcqParam(P_FRAME_RESET_SIZE, m_dwFrameResetWidth);

        //-------------------------
        // Update the V sync delay

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Vsync Delay out of range !!!"));
        }
        m_pCam->SetAcqParam(P2V_VS_PULSE_OFFSET, m_dwVSyncDelay);

        //-------------------------
        // Update the V sync width

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Vsync Width out of range !!!"));
        }
        m_pCam->SetAcqParam(P2V_VS_PULSE_DURATION, m_dwVSyncWidth);

    }

}




//------------------------------------------
//           InitNumericGUI
//------------------------------------------
// Init Edit Box
//------------------------------------------
void CCamSigParamDlg::InitNumericGUI() 
{
CString strToFormat;


    // Init the TRIGGER debounce

    strToFormat.Format("%d", m_dwTriggerDebounce);
    m_EditTrigDebounce.SetWindowText(strToFormat);

    // Init the FRAME RESET delay

    strToFormat.Format("%d", m_dwFrameResetDelay);
    m_EditFrameResetDelay.SetWindowText(strToFormat);

    // Init the FRAME RESET width

    strToFormat.Format("%d", m_dwFrameResetWidth);
    m_EditFrameResetWidth.SetWindowText(strToFormat);

    // Init the V sync delay

    strToFormat.Format("%d", m_dwVSyncDelay);
    m_EditVSyncDelay.SetWindowText(strToFormat);

    // Init the V sync width

    strToFormat.Format("%d", m_dwVSyncWidth);
    m_EditVSyncWidth.SetWindowText(strToFormat);

}




//------------------------------------------
//              RetouchVsDelay
//------------------------------------------
// Retouch the "m_dwVsDelay" parameter so
// that the Vs is AFTER the FRAME RESET pulse.
//
// We assume that the camera needs 140 micro-
// seconds minimum between the end of the
// FRAME RESET and the beginning of the Vs.
//
// Vs delay = max(Vs delay, (FRAME RESET delay + FRAME RESET width + 140))
//
// Returns TRUE if value changed
//------------------------------------------
BOOL CCamSigParamDlg::RetouchVsDelay() 
{
DWORD dwEndOfFR;
DWORD dwInitialValue;

    dwInitialValue = m_dwVSyncDelay;

    dwEndOfFR = m_dwFrameResetDelay;
    dwEndOfFR += m_dwFrameResetWidth;
    dwEndOfFR += 140;

    m_dwVSyncDelay = max(m_dwVSyncDelay, dwEndOfFR);
    m_dwVSyncDelay = min(m_dwVSyncDelay, m_dwVsDelayMax);

    if (m_dwVSyncDelay != dwInitialValue)
        return TRUE;
    else
        return FALSE;
}



//------------------------------------------
//              OnButtonFrHi
//------------------------------------------
void CCamSigParamDlg::OnButtonFrHi() 
{

    m_bFrPolIsHigh = TRUE;

}



//------------------------------------------
//              OnButtonFrLo
//------------------------------------------
void CCamSigParamDlg::OnButtonFrLo() 
{

    m_bFrPolIsHigh = FALSE;

}



//------------------------------------------
//              OnButtonTrigHi
//------------------------------------------
void CCamSigParamDlg::OnButtonTrigHi() 
{

    m_bTrigPolIsHigh = TRUE;

}



//------------------------------------------
//              OnButtonTrigLo
//------------------------------------------
void CCamSigParamDlg::OnButtonTrigLo() 
{

    m_bTrigPolIsHigh = FALSE;

}



//------------------------------------------
//              OnButtonVsHi
//------------------------------------------
void CCamSigParamDlg::OnButtonVsHi() 
{

    m_bVsPolIsHigh = TRUE;

}



//------------------------------------------
//              OnButtonVsLo
//------------------------------------------
void CCamSigParamDlg::OnButtonVsLo() 
{

    m_bVsPolIsHigh = FALSE;

}



//------------------------------------------
//           OnTimer
//------------------------------------------
void CCamSigParamDlg::OnTimer(UINT nIDEvent) 
{

    if (nIDEvent == TIMER_PARAM_GUI)
    {
        UpdateGUIButton();
        
        // Repaint if an OnPaint() has been called

        if (m_dwOnPaintCounter != m_dwLastOnPaintCounter)
        {
            OnPaint();
            m_dwLastOnPaintCounter = m_dwOnPaintCounter;
        }

        // Redraw the timing bars if user change a numeric value

        if (m_dwOnChangeCounter != m_dwLastOnChangeCounter)
        {
            DrawVsTimingBar();                // Redraw the Vsync timing bar
            DrawFrTimingBar();                // Redraw the FRAME RESET timing bar
            DrawStrobeTimingBar();            // Redraw the STROBE timing bar
            m_dwLastOnChangeCounter = m_dwOnChangeCounter;
        }

    }

    CDialog::OnTimer(nIDEvent);
}



//------------------------------------------
//           UpdateGUIButton
//------------------------------------------
void CCamSigParamDlg::UpdateGUIButton() 
{

    // Update the Buttons

    m_ButtonTrigLo.EnableWindow(m_bTrigPolIsHigh);
    m_ButtonTrigHi.EnableWindow(! m_bTrigPolIsHigh);

    m_ButtonFrLo.EnableWindow(m_bFrPolIsHigh);
    m_ButtonFrHi.EnableWindow(! m_bFrPolIsHigh);

    m_ButtonVsLo.EnableWindow(m_bVsPolIsHigh);
    m_ButtonVsHi.EnableWindow(! m_bVsPolIsHigh);

}





//------------------------------------------
//           OnClose
//------------------------------------------
void CCamSigParamDlg::OnClose() 
{

    KillTimer(TIMER_PARAM_GUI);

    CDialog::OnOK();
}



//------------------------------------------
//           OnOK
//------------------------------------------
void CCamSigParamDlg::OnOK() 
{

    UpdateParamToIFC();

    KillTimer(TIMER_PARAM_GUI);

    CDialog::OnOK();
}




//------------------------------------------
//          GetWindowPosition
//------------------------------------------
// This function determine where in the
// main application window the passed window
// is located in pixel value.
//------------------------------------------
BOOL CCamSigParamDlg::GetWindowPosition(HWND hWnd, LPRECT lpRect)
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
//           OnPaint
//------------------------------------------
void CCamSigParamDlg::OnPaint() 
{
    CPaintDC dc(this); // device context for painting

    // Draw the timimg bars

    DrawTrigTimingBar();
    DrawFrTimingBar();
    DrawVsTimingBar();
    DrawStrobeTimingBar();

    m_dwOnPaintCounter++;

	// Do not call CDialog::OnPaint() for painting messages
}





//------------------------------------------
//           OnChangeEditTrigDebounce
//------------------------------------------
void CCamSigParamDlg::OnChangeEditTrigDebounce() 
{
CString strUser;


    m_dwOnChangeCounter++;                  // Notify Timer to redraw Timing Bars

    m_EditTrigDebounce.GetWindowText(strUser);              // Read user's entry
    m_dwTriggerDebounce = atol(strUser);                    // ASCII to binary

    if (ValidateParamValue() == FALSE)
    {
        AfxMessageBox(_T("Trigger Debounce out of range !!!"));
    }

}




//------------------------------------------
//           OnChangeEditFrDelay
//------------------------------------------
void CCamSigParamDlg::OnChangeEditFrDelay() 
{
CString strUser;

    m_dwOnChangeCounter++;                  // Notify Timer to redraw Timing Bars

    m_EditFrameResetDelay.GetWindowText(strUser);           // Read user's entry
    m_dwFrameResetDelay = atol(strUser);                    // ASCII to binary

    if (ValidateParamValue() == FALSE)
    {
        AfxMessageBox(_T("Frame Reset Delay out of range !!!"));
    }

    // VSync Delay dependant on Frame Reset

    if (RetouchVsDelay() == TRUE)
    {
        strUser.Format("%d", m_dwVSyncDelay);
        m_EditVSyncDelay.SetWindowText(strUser);    // Draw retouched VS delay value
        m_dwOnChangeCounter++;                      // Notify Timer to redraw Timing Bars
    }

}



//------------------------------------------
//           OnChangeEditFrWidth
//------------------------------------------
void CCamSigParamDlg::OnChangeEditFrWidth() 
{
CString strUser;


    m_dwOnChangeCounter++;                  // Notify Timer to redraw Timing Bars

    m_EditFrameResetWidth.GetWindowText(strUser);       // Read user's entry
    m_dwFrameResetWidth = atol(strUser);                // ASCII to binary

    if (ValidateParamValue() == FALSE)
    {
        AfxMessageBox(_T("Frame Reset Width out of range !!!"));
    }

    // VSync Delay dependant on Frame Reset

    if (RetouchVsDelay() == TRUE)
    {
        strUser.Format("%d", m_dwVSyncDelay);
        m_EditVSyncDelay.SetWindowText(strUser);    // Draw retouched VS delay value
        m_dwOnChangeCounter++;                      // Notify Timer to redraw Timing Bars
    }


}



//------------------------------------------
//           OnChangeEditVsDelay
//------------------------------------------
void CCamSigParamDlg::OnChangeEditVsDelay() 
{
CString strUser;


    m_dwOnChangeCounter++;                  // Notify Timer to redraw Timing Bars

    m_EditVSyncDelay.GetWindowText(strUser);                // Read user's entry
    m_dwVSyncDelay = atol(strUser);                         // ASCII to binary

    if (ValidateParamValue() == FALSE)
    {
        AfxMessageBox(_T("Vertical Sync Delay out of range !!!"));
    }

    // VSync Delay dependant on Frame Reset

    if (RetouchVsDelay() == TRUE)
    {
        strUser.Format("%d", m_dwVSyncDelay);
        m_EditVSyncDelay.SetWindowText(strUser);    // Draw retouched VS delay value
        m_dwOnChangeCounter++;                      // Notify Timer to redraw Timing Bars
    }


}



//------------------------------------------
//           OnChangeEditVsWidth
//------------------------------------------
void CCamSigParamDlg::OnChangeEditVsWidth() 
{
CString strUser;


    m_dwOnChangeCounter++;                  // Notify Timer to redraw Timing Bars

    m_EditVSyncWidth.GetWindowText(strUser);        // Read user's entry
    m_dwVSyncWidth = atol(strUser);                 // ASCII to binary

    if (ValidateParamValue() == FALSE)
    {
        AfxMessageBox(_T("Vertical Sync Width out of range !!!"));
    }

}




//------------------------------------------
//           DrawTrigTimingBar
//------------------------------------------
void CCamSigParamDlg::DrawTrigTimingBar() 
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
CString strToGet;


    // Draw a BLACK rectangle as the Timing Bar (two pixels per milli-sec.)

    pOldPen = MyDC.SelectObject(&MyBlackPen);
    pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticTimingBarTrig.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // Draw milli-second tick marks under the Timing Bar

    DrawTimingBarTickMark(m_StaticTimingBarTrig.GetSafeHwnd());
    
    // Draw a RED rectangle 3 pixels wide as the Trigger Position

    MyDC.SelectObject(&MyRedBrush);

    RectDraw.right = RectDraw.left + MIN_PIXEL_WIDTH;

    MyDC.Rectangle(&RectDraw);

    // Restore original brush and pen

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

    GdiFlush();             // Force drawing of the timing bar

}





//------------------------------------------
//           DrawFrTimingBar
//------------------------------------------
void CCamSigParamDlg::DrawFrTimingBar() 
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush MyGrayBrush (RGB(128,128,128));  // Gray Interior filling (disabled)
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
CString strToGet;
DWORD dwDelay;
DWORD dwWidth;
BOOL bFrameResetEnabled;


    // Ask IFC to know if the Frame Reset signal generation is enabled

    bFrameResetEnabled = FALSE;
    if (m_pCam->GetAcqParam(P_FRAME_RESET_MODE) == IFC_ENABLE)
    {
        bFrameResetEnabled = TRUE;
    }

    // Convert param. values to pixels and insure a minimum pixel width

    dwDelay = m_dwFrameResetDelay / 1000;           // Delay in milli-sec.
    dwDelay <<= 1;                                  // Two pixels per milli-sec.
    dwDelay = max(dwDelay, MIN_PIXEL_WIDTH);

    dwWidth = m_dwFrameResetWidth / 1000;           // Width in milli-sec.
    dwWidth <<= 1;                                  // Two pixels per milli-sec.
    dwWidth = max(dwWidth, MIN_PIXEL_WIDTH);

    // Draw a BLACK rectangle as the Timing Bar (two pixels per milli-sec.)

    if (bFrameResetEnabled)
    {
        pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    }
    else
    {
        pOldBrush = MyDC.SelectObject(&MyGrayBrush);
    }
    pOldPen = MyDC.SelectObject(&MyBlackPen);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticTimingBarFr.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // Draw milli-second tick marks under the Timing Bar

    DrawTimingBarTickMark(m_StaticTimingBarFr.GetSafeHwnd());
    
    // Draw a RED rectangle as the Frame Reset position and width

    if (bFrameResetEnabled)
    {
        MyDC.SelectObject(&MyRedBrush);

        RectDraw.left += dwDelay;                   // Position of rect ~ delay
        RectDraw.right = RectDraw.left + dwWidth;   // Width of rect ~ width

        MyDC.Rectangle(&RectDraw);
    }

    // Restore original brush and pen

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

    GdiFlush();             // Force drawing of the timing bar

}


//------------------------------------------
//           DrawVsTimingBar
//------------------------------------------
void CCamSigParamDlg::DrawVsTimingBar() 
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush MyGrayBrush (RGB(128,128,128));  // Gray Interior filling (disabled)
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
CString strToGet;
DWORD dwDelay;
DWORD dwWidth;
BOOL bVsyncEnabled;
double dVsEnable;


    // Get param. values from IFC

    bVsyncEnabled = TRUE;
//    if (m_pCam->GetAcqParam(P2V_VS_PULSE_ENABLE) == P2V_VSYNC_DISABLE)
    dVsEnable = m_pCam->GetAcqParam(P2V_VS_PULSE_ENABLE);
    if (dVsEnable == P2V_VSYNC_DISABLE)
    {
        bVsyncEnabled = FALSE;
    }

    // Convert param. values to pixels and insure a minimum pixel width

    dwDelay = m_dwVSyncDelay / 1000;                // Delay in milli-sec.
    dwDelay <<= 1;                                  // Two pixels per milli-sec.
    dwDelay = max(dwDelay, MIN_PIXEL_WIDTH);

    dwWidth = m_dwVSyncWidth / 1000;                // Width in milli-sec.
    dwWidth <<= 1;                                  // Two pixels per milli-sec.
    dwWidth = max(dwWidth, MIN_PIXEL_WIDTH);

    // Draw a BLACK rectangle as the Timing Bar (two pixels per milli-sec.)

    if (bVsyncEnabled)
    {
        pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    }
    else
    {
        pOldBrush = MyDC.SelectObject(&MyGrayBrush);
    }
    pOldPen = MyDC.SelectObject(&MyBlackPen);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticTimingBarVs.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // Draw milli-second tick marks under the Timing Bar

    DrawTimingBarTickMark(m_StaticTimingBarVs.GetSafeHwnd());
    
    // Draw a RED rectangle as the Frame Reset position and width

    if (bVsyncEnabled)
    {
        MyDC.SelectObject(&MyRedBrush);

        RectDraw.left += dwDelay;                   // Position of rect ~ delay
        RectDraw.right = RectDraw.left + dwWidth;   // Width of rect ~ width

        MyDC.Rectangle(&RectDraw);
    }

    // Restore original brush and pen

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

    GdiFlush();             // Force drawing of the timing bar

}



//------------------------------------------
//           DrawStrobeTimingBar
//------------------------------------------
void CCamSigParamDlg::DrawStrobeTimingBar() 
{
CClientDC MyDC(this);
CBrush MyRedBrush (RGB(255,0,0));       // Red Interior filling
CBrush MyBlackBrush (RGB(0,0,0));       // Black Interior filling
CBrush MyGrayBrush (RGB(128,128,128));  // Gray Interior filling (disabled)
CBrush *pOldBrush;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Exterior lines
CPen *pOldPen;
RECT RectDraw;
CString strToGet;
DWORD dwDelay;
DWORD dwWidth;
BOOL bStrobeEnabled;
BOOL bVsyncEnabled;


    // Get param. values from IFC

    bStrobeEnabled = FALSE;
    if (m_pCam->GetAcqParam(P_STROBE_ENABLE) == IFC_ENABLE)
    {
        bStrobeEnabled = TRUE;
    }

    bVsyncEnabled = TRUE;
    if (m_pCam->GetAcqParam(P2V_VS_PULSE_ENABLE) == P2V_VSYNC_DISABLE)
    {
        bVsyncEnabled = FALSE;
    }

    if (m_pCam->GetAcqParam(P_STROBE_MODE) == IFC_SLOW_STROBE)
    {
        dwDelay = (DWORD)m_pCam->GetAcqParam(P_STROBE_DELAY);
        if (bVsyncEnabled)
        {
            dwDelay += m_dwVSyncDelay;      // In slow mode it is after VS
        }
        else
        {
            dwDelay += m_dwFrameResetDelay;      // In slow mode it is after FR
            dwDelay += m_dwFrameResetWidth;      // In slow mode it is after FR
        }
    }
    else
    {
        dwDelay = 0;                    // In fast mode it is immediately after trigger
    }

    dwWidth = (DWORD)m_pCam->GetAcqParam(P_STROBE_DURATION);

    // Convert param. values to pixels and insure a minimum pixel width

    dwDelay /= 1000;                                // Delay in milli-sec.
    dwDelay <<= 1;                                  // Two pixels per milli-sec.
    dwDelay = max(dwDelay, MIN_PIXEL_WIDTH);

    dwWidth /= 1000;                                // Width in milli-sec.
    dwWidth <<= 1;                                  // Two pixels per milli-sec.
    dwWidth = max(dwWidth, MIN_PIXEL_WIDTH);

    // Draw a BLACK rectangle as the Timing Bar (two pixels per milli-sec.)

    if (bStrobeEnabled)
    {
        pOldBrush = MyDC.SelectObject(&MyBlackBrush);
    }
    else
    {
        pOldBrush = MyDC.SelectObject(&MyGrayBrush);
    }
    pOldPen = MyDC.SelectObject(&MyBlackPen);
    MyDC.SetMapMode(MM_TEXT);

    GetWindowPosition(m_StaticTimingBarStrobe.GetSafeHwnd(), &RectDraw);
    MyDC.Rectangle(&RectDraw);

    // Draw milli-second tick marks under the Timing Bar

    DrawTimingBarTickMark(m_StaticTimingBarStrobe.GetSafeHwnd());
    
    // Draw a RED rectangle as the Frame Reset position and width

    if (bStrobeEnabled)
    {
        MyDC.SelectObject(&MyRedBrush);

        RectDraw.left += dwDelay;                   // Position of rect = delay
        RectDraw.right = RectDraw.left + dwWidth;   // Width of rect = width

        MyDC.Rectangle(&RectDraw);
    }

    // Restore original brush and pen

    MyDC.SelectObject(pOldPen);
    MyDC.SelectObject(pOldBrush);

    GdiFlush();             // Force drawing of the timing bar

}





//------------------------------------------
//           DrawTimingBarTickMark
//------------------------------------------
void CCamSigParamDlg::DrawTimingBarTickMark(HWND hWnd) 
{
CClientDC MyDC(this);
RECT RectDraw;
CPen MyBlackPen (PS_SOLID, 1, RGB(0,0,0));       // Tick mark lines
CPen *pOldPen;
DWORD dwMilliSec;
DWORD dwTimingBarLength;
CString strHundred;
UINT OldTextAlign;
int OldBkgnd;
int OldMapMode;


    pOldPen         = MyDC.SelectObject(&MyBlackPen);
    OldMapMode      = MyDC.SetMapMode(MM_TEXT);              // Logical mapping for text
    OldBkgnd        = MyDC.SetBkMode(TRANSPARENT);           // Do not draw a background color under text
    OldTextAlign    = MyDC.SetTextAlign(TA_CENTER);

    // Determine the lower-left point of the Timing Bar and it's length

    GetWindowPosition(hWnd, &RectDraw);

    dwTimingBarLength = RectDraw.right - RectDraw.left;

    // Draw a small Tick Mark every 25 pixels ( 12.5milli-sec.)

    for (dwMilliSec = 0; dwMilliSec <= dwTimingBarLength; dwMilliSec += 25)
    {
        MyDC.MoveTo(RectDraw.left + dwMilliSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMilliSec, RectDraw.bottom + 5);
    }

    // Draw a medium Tick Mark every 50 pixels ( 25 milli-sec.)

    for (dwMilliSec = 0; dwMilliSec <= dwTimingBarLength; dwMilliSec += 50)
    {
        MyDC.MoveTo(RectDraw.left + dwMilliSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMilliSec, RectDraw.bottom + 10);
    }

    // Draw a large Tick Mark every 100 pixels ( 50 milli-sec.) as well as numbers

    for (dwMilliSec = 0; dwMilliSec <= dwTimingBarLength; dwMilliSec += 100)
    {
        MyDC.MoveTo(RectDraw.left + dwMilliSec, RectDraw.bottom);
        MyDC.LineTo(RectDraw.left + dwMilliSec, RectDraw.bottom + 15);
        strHundred.Format("%d", dwMilliSec / 2);        // 2 pixels per milli-sec.
        MyDC.TextOut(RectDraw.left + dwMilliSec, RectDraw.bottom + 15, strHundred);
    }

    // Restore original pen and modes

    MyDC.SelectObject(pOldPen);
    MyDC.SetMapMode(OldMapMode);
    MyDC.SetBkMode(OldBkgnd);
    MyDC.SetTextAlign(OldTextAlign);

    GdiFlush();             // Force drawing of the timing bar

}



//------------------------------------------
//           OnDefault
//------------------------------------------
void CCamSigParamDlg::OnDefault() 
{

    m_bTrigPolIsHigh    = DEFAULT_TRIG_POL_HI;
    m_bFrPolIsHigh      = DEFAULT_FR_POL_HI;
    m_bVsPolIsHigh      = DEFAULT_VS_POL_HI;

    m_dwTriggerDebounce = DEFAULT_TRIG_DEBOUNCE;
    m_dwFrameResetDelay = DEFAULT_FR_DELAY;
    m_dwFrameResetWidth = DEFAULT_FR_WIDTH;
    m_dwVSyncDelay      = DEFAULT_VS_DELAY;
    m_dwVSyncWidth      = DEFAULT_VS_WIDTH;

    InitNumericGUI();           // Update the Numeric values on the screen

    m_dwOnChangeCounter++;      // Notify Timer to redraw Timing Bars

}



//------------------------------------------
//           OnButtonStrobeParm
//------------------------------------------
void CCamSigParamDlg::OnButtonStrobeParm() 
{
CStrobeParamDlg MyStrobeParamDlg(this, m_pCam);

    MyStrobeParamDlg.DoModal();

    DrawStrobeTimingBar();

}
