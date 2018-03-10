//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           StrobeSettingsDlg.h
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

#if !defined(AFX_STROBESETTINGSDLG_H__4D2EBC3B_22D1_41D0_89CD_66831A3B106F__INCLUDED_)
#define AFX_STROBESETTINGSDLG_H__4D2EBC3B_22D1_41D0_89CD_66831A3B106F__INCLUDED_

#include "resource.h"                       // main symbols



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//------------------------------
//          Constants
//------------------------------


#define     TIMER_GUI_UPDATE    10


    // Default values

#define     DEFAULT_STROBE_ENABLE       TRUE
#define     DEFAULT_STROBE_POL_HI       TRUE
#define     DEFAULT_STROBE_MODE_SLOW    FALSE
#define     DEFAULT_STROBE_DELAY        0
#define     DEFAULT_STROBE_WIDTH        1000





class CStrobeParamDlg : public CDialog
{

public:

    CStrobeParamDlg(CWnd* pParent = NULL, CICamera *pCam = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStrobeParamDlg)
	enum { IDD = IDD_STROBE_PARAM_DIALOG };
	CButton	m_ButtonEnable;
	CButton	m_ButtonDisable;
	CEdit	m_EditDelay;
	CEdit	m_EditDuration;
	CButton	m_ButtonPolLo;
	CButton	m_ButtonPolHi;
	CButton	m_ButtonModeSlow;
	CButton	m_ButtonModeFast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrobeParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    void GetParamValue(void);
    void GetParamMinMax(void);

    BOOL ValidateParamValue(void);

    void UpdateParamToIFC(void);
    void UpdateParamToIFCFromGUI(void);

    void InitNumericGUI(void);

    void UpdateGUIButton(void);

    
    // Generated message map functions
	//{{AFX_MSG(CStrobeParamDlg)
	afx_msg void OnButtonModeSlow();
	afx_msg void OnButtonModeFast();
	afx_msg void OnButtonPolHi();
	afx_msg void OnButtonPolLo();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnButtonDisable();
	afx_msg void OnButtonEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICamera    *m_pCam;

    BOOL    m_bStrobeIsSlow;
    BOOL    m_bStrobeIsHigh;
    BOOL    m_bStrobeIsOn;

    DWORD   m_dwStrobeDelay;
    DWORD   m_dwStrobeDelayMin;
    DWORD   m_dwStrobeDelayMax;

    DWORD   m_dwStrobeDuration;
    DWORD   m_dwStrobeDurationMin;
    DWORD   m_dwStrobeDurationMax;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STROBESETTINGSDLG_H__4D2EBC3B_22D1_41D0_89CD_66831A3B106F__INCLUDED_)
