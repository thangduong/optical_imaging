//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2C_BasicGrabDlg.h
//
//  BIRTH DATE:     November 2003
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
//  HARDWARE:       PC2-CamLink Frame Grabber
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2C_BASICGRABDLG_H__EE0C8089_2A8B_4287_8B15_246D06A9A79D__INCLUDED_)
#define AFX_IFC_PC2C_BASICGRABDLG_H__EE0C8089_2A8B_4287_8B15_246D06A9A79D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2C Basic Grab")

#define TIMER_STAT          10
#define TIMER_GUI           20





class CIFC_PC2C_BasicGrabDlg : public CDialog
{

public:

	CIFC_PC2C_BasicGrabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2C_BasicGrabDlg)
	enum { IDD = IDD_IFC_PC2C_BASICGRAB_DIALOG };
	CEdit	m_EditSensorType;
	CEdit	m_EditFrameSize;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCameraType;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2C_BasicGrabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	HICON m_hIcon;

    void ReleaseAll(void);

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    CImgConn * InitIFC_ImageConnection(HWND hWnd, CICamera *cam);
    void ReleaseIFC_ImageConnection(void);

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(HWND hWnd);
    void ShowStatistics(void); 
    void UpdateButtons(void);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2C_BasicGrabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTrigger();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;   // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;

    CImgConn    *m_pImageConnection;

    DWORD       m_dwCamSizeX;      // Camera frame X size for each module
    DWORD       m_dwCamSizeY;      // Camera frame Y size for each module
    DWORD       m_dwFrameCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    BOOL        m_bTriggerMode;
    BOOL        m_bAreaScanMode;
    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2C_BASICGRABDLG_H__EE0C8089_2A8B_4287_8B15_246D06A9A79D__INCLUDED_)
