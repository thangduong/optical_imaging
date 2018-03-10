//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_FrameDelayDlg.h
//
//  BIRTH DATE:     May 2003
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

#if !defined(AFX_IFC_PC2V_FRAMEDELAYDLG_H__A943A278_A7DD_481E_BE4E_78511D7862E5__INCLUDED_)
#define AFX_IFC_PC2V_FRAMEDELAYDLG_H__A943A278_A7DD_481E_BE4E_78511D7862E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------
//          Constants
//--------------------------------

#define     APP_BASIC_TITLE     _T("IFC PC2V Frame Delay")

#define     CAM_MAX_NUMBER      6
#define     BUFFER_COUNT        10

#define TIMER_STAT          10
#define TIMER_GUI           20

#define WAIT_ACQ_MAX_MSEC   2000



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_FrameDelayDlg;



typedef enum
{
   SRC_EXT_TRIG_0 = 0,
   SRC_EXT_TRIG_1,
   SRC_SOFT_TRIG,
   ALTERNATE_TRIG_0_1

} TRIGGER_SOURCE;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_FrameDelayDlg *pMyClass;
    TRIGGER_SOURCE          TrigSrc;
    BOOL                    bGrabbing;

} ACQ_THREAD_PARAM;




class CIFC_PC2V_FrameDelayDlg : public CDialog
{

public:

    CIFC_PC2V_FrameDelayDlg(CWnd* pParent = NULL);      // standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_FrameDelayDlg)
	enum { IDD = IDD_IFC_PC2V_FRAMEDELAY_DIALOG };
	CStatic	m_StaticLightCam4;
	CStatic	m_StaticLightCam3;
	CStatic	m_StaticLightCam5;
	CStatic	m_StaticLightCam2;
	CStatic	m_StaticLightCam6;
	CStatic	m_StaticLightCam1;
	CStatic	m_StaticSOTLight;
	CButton	m_RadioExt_0;
	CEdit	m_EditCamType;
	CEdit	m_EditCamSeqSoftTrig;
	CEdit	m_EditCamSeqExtTrig1;
	CEdit	m_EditCamSeqExtTrig0;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRate;
	CEdit	m_EditFrameCount;
	CStatic	m_StaticDisplayCam4;
	CStatic	m_StaticDisplayCam5;
	CStatic	m_StaticDisplayCam3;
	CStatic	m_StaticDisplayCam6;
	CStatic	m_StaticDisplayCam2;
	CStatic	m_StaticDisplayCam1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_FrameDelayDlg)
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
    void UpdateCamSeqExtTrig_0(void);
    void UpdateCamSeqExtTrig_1(void);
    void UpdateCamSeqSoftTrig(void);
    void BuildCamUsageTable(void); 

    void ReleaseAll(void);

    void ClearDisplay(DWORD dwCamIndex);
    void DrawWindowBorder(HWND hWnd);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics(void); 
    void DisableDisplay(DWORD dwCamIndex);
    void EraseWindowBorder(HWND hWnd);
    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    void ReadAndClearEvents(void);
    void ShowEventLights(void);

    void UpdateCameraGUI(void);
    void UpdateButtons(void);

    static void ThreadAcqProc(void *pContext);

    static void MyCallback_SOT(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_FrameDelayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTypeCam();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonUpdateCamSequence();
	afx_msg void OnRadioExt0();
	afx_msg void OnRadioExt1();
	afx_msg void OnRadioSoft();
	afx_msg void OnRadioAlternate();
	afx_msg void OnChangeEditCamSeq0();
	afx_msg void OnChangeEditCamSeq1();
	afx_msg void OnChangeEditCamSeqSoft();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                 // IFC board module handle
    CICamera    *m_apCam[CAM_MAX_NUMBER];   // Array of ptr to camera objects

    CImgConn    *m_apImageConnection[CAM_MAX_NUMBER];

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
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bCamSequenceTouched;

    DWORD       m_dwIsSOT_EventCounter;
    BOOL        m_bWasSOT_EventDetected;

    TRIGGER_SOURCE  m_TrigSource;

    CThread             *m_pAcqThread;
    ACQ_THREAD_PARAM    m_AcqThreadParams;

    CTimeMeasure        m_MeasureFramePeriod;

    // Camera Sequences related
    
    DWORD   m_adwCamSeqExtTrig_0[CAM_MAX_NUMBER];
    DWORD   m_adwCamSeqExtTrig_1[CAM_MAX_NUMBER];
    DWORD   m_adwCamSeqSoftTrig[CAM_MAX_NUMBER];

    BOOL    m_abCamUsageExtTrig_0[CAM_MAX_NUMBER];
    BOOL    m_abCamUsageExtTrig_1[CAM_MAX_NUMBER];
    BOOL    m_abCamUsageSoftTrig[CAM_MAX_NUMBER];

    DWORD   m_dwCamSeqCountExtTrig_0;
    DWORD   m_dwCamSeqCountExtTrig_1;
    DWORD   m_dwCamSeqCountSoftTrig;

    BOOL    m_abCamUsageTotal[CAM_MAX_NUMBER];
    DWORD   m_dwCamSeqCountTotal;

    // GUI arrays

    HWND    m_ahCamLightOn[CAM_MAX_NUMBER];
    CStatic *m_apCamDisplay[CAM_MAX_NUMBER];

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_FRAMEDELAYDLG_H__A943A278_A7DD_481E_BE4E_78511D7862E5__INCLUDED_)
