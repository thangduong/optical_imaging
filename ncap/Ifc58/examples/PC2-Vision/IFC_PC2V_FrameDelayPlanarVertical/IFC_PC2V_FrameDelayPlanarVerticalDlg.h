//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_FrameDelayDlg.h
//
//  BIRTH DATE:     September 2003
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

#if !defined(AFX_IFC_PC2V_FRAMEDELAYPLANARVERTICALDLG_H__01467793_FDCD_415E_8634_C1EF496EA534__INCLUDED_)
#define AFX_IFC_PC2V_FRAMEDELAYPLANARVERTICALDLG_H__01467793_FDCD_415E_8634_C1EF496EA534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------
//          Constants
//--------------------------------

#define     APP_BASIC_TITLE     _T("IFC PC2V Frame Delay Planar Vertical")

#define     CAM_COUNT           6
#define     CAM_GROUP_COUNT     2
#define     CAM_COUNT_PERGROUP  3
#define     BUFFER_COUNT        10

#define TIMER_STAT          10
#define TIMER_GUI           20

#define WAIT_ACQ_MAX_MSEC   2000





class CIFC_PC2V_FrameDelayPlanarVerticalDlg : public CDialog
{

public:

    CIFC_PC2V_FrameDelayPlanarVerticalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
	enum { IDD = IDD_IFC_PC2V_FRAMEDELAYPLANARVERTICAL_DIALOG };
	CButton	m_RadioDisplayEnable;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCamType;
	CButton	m_RadioExt_0;
	CStatic	m_StaticDisplayGroup2;
	CStatic	m_StaticDisplayGroup1;
	CEdit	m_EditFrameCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    HICON m_hIcon;

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    BOOL InitIFC_Callback(void);
    void ReleaseIFC_Callback(void);

    BOOL InitIFC_ImageConnection(void);
    void ReleaseIFC_ImageConnection(void);

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    void SetCamType(char *pszCamType);

    void ReleaseAll(void);

    void ClearDisplay(DWORD dwGroupIndex);
    void DrawWindowBorder(HWND hWnd);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics(void); 
    void EraseWindowBorder(HWND hWnd);

    void ReadAndClearEvents(void);
    void ShowEventLights(void);

    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    void UpdateButtons(void);

    static void ThreadAcqProc(void *pContext);

    static void MyCallback_SOT(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_FrameDelayPlanarVerticalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTypeCam();
	afx_msg void OnRadioExt0();
	afx_msg void OnRadioExt1();
	afx_msg void OnRadioSoft();
	afx_msg void OnRadioDispDisable();
	afx_msg void OnRadioDispEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                 // IFC board module handle
    CICamera    *m_apCam[CAM_GROUP_COUNT];   // Array of ptr to camera objects

    CImgConn    *m_apImageConnection[CAM_GROUP_COUNT];

    PCIntrCallback  m_pIntCallback_SOT;

    DWORD       m_dwCamSizeX;       // Camera frame X size for each module
    DWORD       m_dwCamSizeY;       // Camera frame Y size for each module
    DWORD       m_dwPixBitDepth;
    DWORD       m_dwImageSize;      // Camera frame Byte size
    IFC_COLOR   m_CamColor;

    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    DWORD       m_dwFrameCounter;
    DWORD       m_dwSkippedFrameCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwStatCamera;

    int         m_iFrameCountToGrab;

    BOOL        m_bIsGrabbing;
    BOOL        m_bIsSnapping;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bDisplayEnable;

    DWORD       m_dwIsSOT_EventCounter;
    BOOL        m_bWasSOT_EventDetected;

    IFC_TRIG_SRC_TYPE   m_TrigSource;

    CThread             *m_pAcqThread;

    CTimeMeasure        m_MeasureAcqRate;

    // GUI arrays

    CStatic *m_apCamDisplay[CAM_GROUP_COUNT];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_FRAMEDELAYPLANARVERTICALDLG_H__01467793_FDCD_415E_8634_C1EF496EA534__INCLUDED_)
