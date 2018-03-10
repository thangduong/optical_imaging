//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           StrobeSettingsDlg.cpp
//
//  BIRTH DATE:     December 2002
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
//                  Dialog Box to set the strobe pulse output parameters.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "StrobeParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//------------------------------------------
//              Constructor
//------------------------------------------
CStrobeParamDlg::CStrobeParamDlg(CWnd* pParent, CICamera *pCam)
	: CDialog(CStrobeParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStrobeSettingsDlg)
	m_dwStrobeDuration = 0;
	//}}AFX_DATA_INIT

    m_pCam = pCam;

    GetParamMinMax();           // Init local MIN-MAX parameter values

    GetParamValue();            // Init local parameter values

    ValidateParamValue();       // Make sure parameter values are within MIN-MAX

    UpdateParamToIFC();         // Set IFC parameters from local variables
    
}




//------------------------------------------
//              DoDataExchange
//------------------------------------------
void CStrobeParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrobeParamDlg)
	DDX_Control(pDX, IDC_BUTTON_ENABLE, m_ButtonEnable);
	DDX_Control(pDX, IDC_BUTTON_DISABLE, m_ButtonDisable);
	DDX_Control(pDX, IDC_EDIT_DELAY, m_EditDelay);
	DDX_Control(pDX, IDC_EDIT_DURATION, m_EditDuration);
	DDX_Control(pDX, IDC_BUTTON_POL_LO, m_ButtonPolLo);
	DDX_Control(pDX, IDC_BUTTON_POL_HI, m_ButtonPolHi);
	DDX_Control(pDX, IDC_BUTTON_MODE_SLOW, m_ButtonModeSlow);
	DDX_Control(pDX, IDC_BUTTON_MODE_FAST, m_ButtonModeFast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStrobeParamDlg, CDialog)
	//{{AFX_MSG_MAP(CStrobeParamDlg)
	ON_BN_CLICKED(IDC_BUTTON_MODE_SLOW, OnButtonModeSlow)
	ON_BN_CLICKED(IDC_BUTTON_MODE_FAST, OnButtonModeFast)
	ON_BN_CLICKED(IDC_BUTTON_POL_HI, OnButtonPolHi)
	ON_BN_CLICKED(IDC_BUTTON_POL_LO, OnButtonPolLo)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_DISABLE, OnButtonDisable)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE, OnButtonEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CStrobeParamDlg::OnInitDialog() 
{
CString strToShow;


    CDialog::OnInitDialog();

    //-----------------------------------------
    // Edit box with the current numeric value

    InitNumericGUI();

    //-----------------------------------------
    // Start a timer doing GUI housekeeping

    if (SetTimer(TIMER_GUI_UPDATE, 500, NULL) == NULL)
    {
        AfxMessageBox(_T("Could not start a timer !!!"));
        EndDialog(7);
        return FALSE;
    }

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}



//------------------------------------------
//           GetParamValue
//------------------------------------------
// Get the current parameter values from IFC.
//------------------------------------------
void CStrobeParamDlg::GetParamValue(void)
{
double dParamValue;

    //----------------------
    // Init the ENABLE state

    m_bStrobeIsOn = DEFAULT_STROBE_ENABLE;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_STROBE_ENABLE) == IFC_ENABLE)
        {
            m_bStrobeIsOn = TRUE;
        }
        else
        {
            m_bStrobeIsOn = FALSE;
        }
    }

    //-------------------------------------------
    // Init the MODE

    m_bStrobeIsSlow = DEFAULT_STROBE_MODE_SLOW;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_STROBE_MODE) == IFC_SLOW_STROBE)
        {
            m_bStrobeIsSlow = TRUE;
        }
        else
        {
            m_bStrobeIsSlow = FALSE;
        }
    }

    //----------------------
    // Init the POLARITY

    m_bStrobeIsHigh = DEFAULT_STROBE_POL_HI;
    if (m_pCam)
    {
        if (m_pCam->GetAcqParam(P_STROBE_POLARITY) == IFC_ACTIVE_HIGH)
        {
            m_bStrobeIsHigh = TRUE;
        }
        else
        {
            m_bStrobeIsHigh = FALSE;
        }
    }

    //----------------------
    // Init the DURATION

    m_dwStrobeDuration = DEFAULT_STROBE_WIDTH;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P_STROBE_DURATION);
        m_dwStrobeDuration = (DWORD)dParamValue;
    }

    //----------------------
    // Init the DELAY

    m_dwStrobeDelay = DEFAULT_STROBE_DELAY;
    if (m_pCam)
    {
        dParamValue = m_pCam->GetAcqParam(P_STROBE_DELAY);
        m_dwStrobeDelay = (DWORD)dParamValue;
    }

}




//------------------------------------------
//           GetParamMinMax
//------------------------------------------
// Get from IFC the MIN and MAX value for
// the numeric parameters.
//------------------------------------------
void CStrobeParamDlg::GetParamMinMax() 
{
IFC_PARAM_CAPS VsCaps;


    //-----------------------------------------------------
    // Init the DURATION MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P_STROBE_DURATION, &VsCaps);
        m_dwStrobeDurationMin = (DWORD)VsCaps.Range.Min;
        m_dwStrobeDurationMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwStrobeDurationMin = 0;
        m_dwStrobeDurationMax = 1;
    }

    //-----------------------------------------------------
    // Init the DELAY MIN and MAX numeric value

    if (m_pCam)
    {
        m_pCam->GetParamCaps(P_STROBE_DELAY, &VsCaps);
        m_dwStrobeDelayMin = (DWORD)VsCaps.Range.Min;
        m_dwStrobeDelayMax = (DWORD)VsCaps.Range.Max;
    }
    else
    {
        m_dwStrobeDelayMin = 0;
        m_dwStrobeDelayMax = 1;
    }

}


//------------------------------------------
//           ValidateParamValue
//------------------------------------------
// Make sure numeric parameters are within
// the capability of the system.
//------------------------------------------
BOOL CStrobeParamDlg::ValidateParamValue() 
{
DWORD dwTestValue;
BOOL bWasOK;


    bWasOK = TRUE;

    // Validate the DURATION numeric value

    dwTestValue = m_dwStrobeDuration;
    dwTestValue = min(m_dwStrobeDurationMax, dwTestValue);
    dwTestValue = max(m_dwStrobeDurationMin, dwTestValue);
    if (dwTestValue != m_dwStrobeDuration)
    {
        bWasOK = FALSE;
        m_dwStrobeDuration = dwTestValue;
    }

    // Validate the DELAY numeric value

    dwTestValue = m_dwStrobeDelay;
    dwTestValue = min(m_dwStrobeDelayMax, dwTestValue);
    dwTestValue = max(m_dwStrobeDelayMin, dwTestValue);
    if (dwTestValue != m_dwStrobeDelay)
    {
        bWasOK = FALSE;
        m_dwStrobeDelay = dwTestValue;
    }

    return bWasOK;

}




//------------------------------------------
//        UpdateParamToIFC
//------------------------------------------
void CStrobeParamDlg::UpdateParamToIFC() 
{

    if (m_pCam)
    {
        //-------------------------
        // Update the ENABLE state

        if (m_bStrobeIsOn)
        {
            m_pCam->SetAcqParam(P_STROBE_ENABLE, IFC_ENABLE);
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_ENABLE, IFC_DISABLE);
        }

        //-------------------------
        // Update the MODE

        if (m_bStrobeIsSlow)
        {
            m_pCam->SetAcqParam(P_STROBE_MODE, IFC_SLOW_STROBE);		
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_MODE, IFC_FAST_STROBE);		
        }

        //-------------------------
        // Update the POLARITY

        if (m_bStrobeIsHigh)
        {
            m_pCam->SetAcqParam(P_STROBE_POLARITY, IFC_ACTIVE_HIGH);		
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_POLARITY, IFC_ACTIVE_LOW);		
        }

        //-------------------------
        // Update DURATION

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Duration out of range !!!"));
        }
        m_pCam->SetAcqParam(P_STROBE_DURATION, m_dwStrobeDuration);

        //-------------------------
        // Update DELAY

        if (m_bStrobeIsSlow)
        {
            if (ValidateParamValue() == FALSE)
            {
                AfxMessageBox(_T("Delay out of range !!!"));
            }
            m_pCam->SetAcqParam(P_STROBE_DELAY, m_dwStrobeDelay);
        }
    }
}




//------------------------------------------
//        UpdateParamToIFCFromGUI
//------------------------------------------
void CStrobeParamDlg::UpdateParamToIFCFromGUI() 
{
char pszValueToGet[256];


    if (m_pCam)
    {
        //-------------------------
        // Update the ENABLE state

        if (m_bStrobeIsOn)
        {
            m_pCam->SetAcqParam(P_STROBE_ENABLE, IFC_ENABLE);
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_ENABLE, IFC_DISABLE);
        }

        //-------------------------
        // Update the MODE

        if (m_bStrobeIsSlow)
        {
            m_pCam->SetAcqParam(P_STROBE_MODE, IFC_SLOW_STROBE);		
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_MODE, IFC_FAST_STROBE);		
        }

        //-------------------------
        // Update the POLARITY

        if (m_bStrobeIsHigh)
        {
            m_pCam->SetAcqParam(P_STROBE_POLARITY, IFC_ACTIVE_HIGH);		
        }
        else
        {
            m_pCam->SetAcqParam(P_STROBE_POLARITY, IFC_ACTIVE_LOW);		
        }

        //-------------------------
        // Update DURATION

        m_EditDuration.GetWindowText(pszValueToGet, sizeof(pszValueToGet));
        m_dwStrobeDuration = atol(pszValueToGet);

        if (ValidateParamValue() == FALSE)
        {
            AfxMessageBox(_T("Duration out of range !!!"));
        }
        m_pCam->SetAcqParam(P_STROBE_DURATION, m_dwStrobeDuration);

        //-------------------------
        // Update DELAY

        if (m_bStrobeIsSlow)
        {
            m_EditDelay.GetWindowText(pszValueToGet, sizeof(pszValueToGet));
            m_dwStrobeDelay = atol(pszValueToGet);
            if (ValidateParamValue() == FALSE)
            {
                AfxMessageBox(_T("Delay out of range !!!"));
            }
            m_pCam->SetAcqParam(P_STROBE_DELAY, m_dwStrobeDelay);
        }
    }
}



//------------------------------------------
//           InitNumericGUI
//------------------------------------------
// Init numeric Edit Box
//------------------------------------------
void CStrobeParamDlg::InitNumericGUI() 
{
CString strToFormat;


    // Init the DURATION numeric value

    strToFormat.Format("%d", m_dwStrobeDuration);
    m_EditDuration.SetWindowText(strToFormat);

    // Init the DELAY numeric value

    strToFormat.Format("%d", m_dwStrobeDelay);
    m_EditDelay.SetWindowText(strToFormat);

}





//------------------------------------------
//              OnButtonModeSlow
//------------------------------------------
void CStrobeParamDlg::OnButtonModeSlow() 
{
    m_bStrobeIsSlow = TRUE;
}



//------------------------------------------
//              OnButtonModeFast
//------------------------------------------
void CStrobeParamDlg::OnButtonModeFast() 
{
    m_bStrobeIsSlow = FALSE;
}


//------------------------------------------
//              OnButtonPolHi
//------------------------------------------
void CStrobeParamDlg::OnButtonPolHi() 
{
    m_bStrobeIsHigh = TRUE;
}


//------------------------------------------
//              OnButtonPolLo
//------------------------------------------
void CStrobeParamDlg::OnButtonPolLo() 
{
    m_bStrobeIsHigh = FALSE;
}




//------------------------------------------
//              OnButtonDisable
//------------------------------------------
void CStrobeParamDlg::OnButtonDisable() 
{
    m_bStrobeIsOn = FALSE;
}



//------------------------------------------
//              OnButtonEnable
//------------------------------------------
void CStrobeParamDlg::OnButtonEnable() 
{
    m_bStrobeIsOn = TRUE;
}


//------------------------------------------
//              OnTimer
//------------------------------------------
void CStrobeParamDlg::OnTimer(UINT nIDEvent) 
{

    if (nIDEvent == TIMER_GUI_UPDATE)
    {
        UpdateGUIButton();
    }

    CDialog::OnTimer(nIDEvent);
}



//------------------------------------------
//              UpdateGUIButton
//------------------------------------------
void CStrobeParamDlg::UpdateGUIButton()
{

    m_ButtonModeSlow.EnableWindow(! m_bStrobeIsSlow);
    m_ButtonModeFast.EnableWindow(m_bStrobeIsSlow);

    m_ButtonPolHi.EnableWindow(! m_bStrobeIsHigh);
    m_ButtonPolLo.EnableWindow(m_bStrobeIsHigh);

    m_ButtonEnable.EnableWindow(! m_bStrobeIsOn);
    m_ButtonDisable.EnableWindow(m_bStrobeIsOn);

    m_EditDelay.EnableWindow(m_bStrobeIsSlow);

}




//------------------------------------------
//              OnClose
//------------------------------------------
void CStrobeParamDlg::OnClose() 
{

    KillTimer(TIMER_GUI_UPDATE);
	
	CDialog::OnClose();
}



//------------------------------------------
//              OnOK
//------------------------------------------
void CStrobeParamDlg::OnOK() 
{

    UpdateParamToIFCFromGUI();      // Get user's inputs

    KillTimer(TIMER_GUI_UPDATE);
	
	CDialog::OnOK();
}

