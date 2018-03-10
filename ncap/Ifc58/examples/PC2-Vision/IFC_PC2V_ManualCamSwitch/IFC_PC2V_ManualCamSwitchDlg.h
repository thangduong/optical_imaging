//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ManualCamSwitchDlg.h
//
//  BIRTH DATE:     September 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.6 SP3)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2V_MANUALCAMSWITCHDLG_H__2B6D273C_CE73_4D7F_B2BD_B2A00FC313AE__INCLUDED_)
#define AFX_IFC_PC2V_MANUALCAMSWITCHDLG_H__2B6D273C_CE73_4D7F_B2BD_B2A00FC313AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------
//          Constants
//--------------------------------

#define     APP_BASIC_TITLE     _T("IFC PC2V Manual Camera Switching")

#define     CAM_MAX_NUMBER      6
#define     BUFFER_COUNT        10

#define     TIMER_STAT          10
#define     TIMER_GUI           20

#define     WAIT_ACQ_MAX_MSEC   2000
#define     WAIT_SNAP_MAX       6



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_ManualCamSwitchDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_ManualCamSwitchDlg    *pMyClass;
    DWORD                           dwCamSeqCount;
    int                             iFrameCountToGrab;

} ACQ_THREAD_PARAM;




class CIFC_PC2V_ManualCamSwitchDlg : public CDialog
{

public:

	CIFC_PC2V_ManualCamSwitchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_ManualCamSwitchDlg)
	enum { IDD = IDD_IFC_PC2V_MANUALCAMSWITCH_DIALOG };
	CEdit	m_EditPllLockWait;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonCamSequence;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRateTotal;
	CEdit	m_EditFrameRate;
	CEdit	m_EditSequenceCount;
	CEdit	m_EditCamSeq;
	CButton	m_ButtonCamType6;
	CButton	m_ButtonCamType5;
	CButton	m_ButtonCamType4;
	CButton	m_ButtonCamType3;
	CButton	m_ButtonCamType2;
	CButton	m_ButtonCamType1;
	CEdit	m_EditCamType6;
	CEdit	m_EditCamType5;
	CEdit	m_EditCamType4;
	CEdit	m_EditCamType3;
	CEdit	m_EditCamType2;
	CEdit	m_EditCamType1;
	CStatic	m_StaticDisplayCam6;
	CStatic	m_StaticDisplayCam5;
	CStatic	m_StaticDisplayCam4;
	CStatic	m_StaticDisplayCam3;
	CStatic	m_StaticDisplayCam2;
	CStatic	m_StaticDisplayCam1;
	CStatic	m_StaticLightCam6;
	CStatic	m_StaticLightCam5;
	CStatic	m_StaticLightCam4;
	CStatic	m_StaticLightCam3;
	CStatic	m_StaticLightCam2;
	CStatic	m_StaticLightCam1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_ManualCamSwitchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	HICON m_hIcon;

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    BOOL InitIFC_Callback(void);
    void ReleaseIFC_Callback(void);

    BOOL InitIFC_ImageConnection(DWORD dwCamNumber);
    void ReleaseIFC_ImageConnection(DWORD dwCamNumber);

    BOOL AllocateCaptureMemory(DWORD dwCamNumber);
    void ReleaseCaptureMemory(DWORD dwCamNumber);

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);
    BOOL IsTriggerModeUsed(void);

    void ReleaseAll(void);

    void ClearDisplay(DWORD dwCamIndex);
    void DrawWindowBorder(HWND hWnd);
    void EraseWindowBorder(HWND hWnd);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void UpdateCameraGUI(void);
    void DisableDisplay(DWORD dwBoardIndex);
    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    void ShowStatistics(void); 
    void EnableGui(void);

    void ShowEventLights(void);
    void ReadAndClearEvents(void);

    static void ThreadAcqProc(void *pContext);

    static void MyCallback_SOT(void *pContext);


	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_ManualCamSwitchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCamSeq();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrap();
	afx_msg void OnChangeEditCamSeq();
	afx_msg void OnButtonCamType1();
	afx_msg void OnButtonCamType2();
	afx_msg void OnButtonCamType3();
	afx_msg void OnButtonCamType4();
	afx_msg void OnButtonCamType5();
	afx_msg void OnButtonCamType6();
	afx_msg void OnChangeEditPllLockTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                 // IFC board module handle
    CICamera    *m_apCam[CAM_MAX_NUMBER];   // Array of ptr to camera objects

    CImgConn    *m_apImageConnection[CAM_MAX_NUMBER];

    PCIntrCallback  m_pIntCallback_SOT;
    PCIntrCallback  m_pIntCallback_SOF;
    PCIntrCallback  m_pIntCallback_EOF;
    PCIntrCallback  m_pIntCallback_EOT1;
    PCIntrCallback  m_pIntCallback_EOT2;
    PCIntrCallback  m_pIntCallback_EOT3;

    DWORD       m_adwCamSizeX[CAM_MAX_NUMBER];       // Image frame X size for each camera
    DWORD       m_adwCamSizeY[CAM_MAX_NUMBER];       // Image frame Y size for each camera
    DWORD       m_adwPixBitDepth[CAM_MAX_NUMBER];
    DWORD       m_adwImageSize[CAM_MAX_NUMBER];      // Camera frame Byte size
    IFC_COLOR   m_aCamColor[CAM_MAX_NUMBER];

    BYTE        *m_apHostCapMemory[CAM_MAX_NUMBER];
    MEMLOCKHDL  m_aCapMemLockHandle[CAM_MAX_NUMBER];

    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwFrameCounter;

    int         m_iFrameCountToGrab;
    DWORD       m_dwPllLockWaitTime;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bCamSequenceTouched;
    BOOL        m_bCamTypeTouched;
    BOOL        m_bIsPllLockWaitTouched;
    BOOL        m_bTriggerMode;                 // At least one camera is operating in Trigger mode

    DWORD       m_dwIsSOT_EventCounter;         // Start of Trigger event counter

    BOOL        m_bWasSOT_EventDetected;

    CThread             *m_pAcqThread;
    ACQ_THREAD_PARAM    m_AcqThreadParams;

    CTimeMeasure        m_MeasureFramePeriod;

    // Camera sequence related variables

    DWORD   m_dwCamSequenceCount;
    DWORD   m_dwCurrentCamera;
    DWORD   m_adwCamSequence[CAM_MAX_NUMBER];
    BOOL    m_abCameraUsage[CAM_MAX_NUMBER];

    // GUI arrays

    HWND    m_ahCamLightOn[CAM_MAX_NUMBER];
    CStatic *m_apCamDisplay[CAM_MAX_NUMBER];
    CEdit   *m_apEditCameraType[CAM_MAX_NUMBER];
    CButton *m_apButtonCamSelect[CAM_MAX_NUMBER];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_MANUALCAMSWITCHDLG_H__2B6D273C_CE73_4D7F_B2BD_B2A00FC313AE__INCLUDED_)
