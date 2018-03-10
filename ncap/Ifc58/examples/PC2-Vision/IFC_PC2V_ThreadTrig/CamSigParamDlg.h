//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           CCamSigParamDlg.h
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

#if !defined(AFX_PARAMDLG_H__C32D9F8A_3BBD_4D48_A81B_99890599EABC__INCLUDED_)
#define AFX_PARAMDLG_H__C32D9F8A_3BBD_4D48_A81B_99890599EABC__INCLUDED_


#include "resource.h"                       // main symbols



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamDlg.h : header file
//



//------------------------------
//          Constants
//------------------------------


#define     TIMER_PARAM_GUI     10

#define     MIN_PIXEL_WIDTH     10


    // Default values

#define     DEFAULT_TRIG_POL_HI         TRUE
#define     DEFAULT_FR_POL_HI           TRUE
#define     DEFAULT_VS_POL_HI           FALSE

#define     DEFAULT_TRIG_DEBOUNCE       1
#define     DEFAULT_FR_DELAY            0
#define     DEFAULT_FR_WIDTH            10000
#define     DEFAULT_VS_DELAY            10140
#define     DEFAULT_VS_WIDTH            300



class CCamSigParamDlg : public CDialog
{

public:

    CCamSigParamDlg(CWnd* pParent = NULL, CICamera *pCam = NULL);   // Constructor

// Dialog Data
	//{{AFX_DATA(CCamSigParamDlg)
	enum { IDD = IDD_CAM_SIG_PARAM_DIALOG };
	CButton	m_ButtonStrobeParms;
	CStatic	m_StaticTimingBarStrobe;
	CEdit	m_EditVSyncWidth;
	CEdit	m_EditFrameResetWidth;
	CEdit	m_EditVSyncDelay;
	CEdit	m_EditTrigDebounce;
	CEdit	m_EditFrameResetDelay;
	CStatic	m_StaticTimingBarFr;
	CStatic	m_StaticTimingBarVs;
	CStatic	m_StaticTimingBarTrig;
	CButton	m_ButtonVsHi;
	CButton	m_ButtonVsLo;
	CButton	m_ButtonFrHi;
	CButton	m_ButtonFrLo;
	CButton	m_ButtonTrigHi;
	CButton	m_ButtonTrigLo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamSigParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    void GetParamValue(void);
    void UpdateParamToIFC(void);

    void GetParamMinMax(void);

    BOOL ValidateParamValue(void);

    void InitNumericGUI(void);
    void UpdateGUIButton(void);

    void DrawTrigTimingBar(void);
    void DrawFrTimingBar(void);
    void DrawVsTimingBar(void);
    void DrawStrobeTimingBar(void);
    void DrawTimingBarTickMark(HWND hWnd);

    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);

    BOOL RetouchVsDelay(void);

	// Generated message map functions
	//{{AFX_MSG(CCamSigParamDlg)
	afx_msg void OnButtonFrHi();
	afx_msg void OnButtonFrLo();
	afx_msg void OnButtonTrigHi();
	afx_msg void OnButtonTrigLo();
	afx_msg void OnButtonVsHi();
	afx_msg void OnButtonVsLo();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnChangeEditTrigDebounce();
	afx_msg void OnChangeEditFrDelay();
	afx_msg void OnChangeEditFrWidth();
	afx_msg void OnPaint();
	afx_msg void OnChangeEditVsDelay();
	afx_msg void OnChangeEditVsWidth();
	afx_msg void OnDefault();
	afx_msg void OnButtonStrobeParm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

    BOOL    m_bTrigPolIsHigh;
    BOOL    m_bFrPolIsHigh;
    BOOL    m_bVsPolIsHigh;

    DWORD   m_dwTriggerDebounce;
    DWORD   m_dwFrameResetDelay;
    DWORD   m_dwFrameResetWidth;
    DWORD   m_dwVSyncDelay;
    DWORD   m_dwVSyncWidth;

private:

    CICamera    *m_pCam;

    DWORD   m_dwTrigDebounceMin;
    DWORD   m_dwTrigDebounceMax;

    DWORD   m_dwFrDelayMin;
    DWORD   m_dwFrDelayMax;

    DWORD   m_dwFrWidthMin;
    DWORD   m_dwFrWidthMax;

    DWORD   m_dwVsDelayMin;
    DWORD   m_dwVsDelayMax;

    DWORD   m_dwVsWidthMin;
    DWORD   m_dwVsWidthMax;

    DWORD   m_dwOnPaintCounter;
    DWORD   m_dwLastOnPaintCounter;

    DWORD   m_dwOnChangeCounter;
    DWORD   m_dwLastOnChangeCounter;

    DWORD   m_dwDebugCounter;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDLG_H__C32D9F8A_3BBD_4D48_A81B_99890599EABC__INCLUDED_)
