//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CamSwitchDlg.h
//
//  BIRTH DATE:     April 2003
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


#if !defined(AFX_IFC_PC2V_CAMSWITCHDLG_H__5E9FFD90_9A06_432B_A783_31534A4F595D__INCLUDED_)
#define AFX_IFC_PC2V_CAMSWITCHDLG_H__5E9FFD90_9A06_432B_A783_31534A4F595D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//--------------------------------
//          Constants
//--------------------------------

#define     APP_BASIC_TITLE     _T("IFC PC2V Camera Switching")

#define     CAM_MAX_NUMBER      6
#define     BUFFER_COUNT        10

#define     TIMER_STAT          10
#define     TIMER_GUI           20

#define     WAIT_ACQ_MAX_MSEC   2000
#define     WAIT_SNAP_MAX       6



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_CamSwitchDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_CamSwitchDlg  *pMyClass;
    DWORD                   dwMyThreadIndex;
    DWORD                   dwMyCameraIndex;
    DWORD                   dwCamSeqCount;

} ACQ_THREAD_PARAM;


typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                *pTheBuffer;
    HIFCGRAB            GrabID;
    int                 iBufferIndex;
    DWORD               dwCameraIndex;
    BOOL                bBusy;

} DISPLAY_THREAD_PARAM;






class CIFC_PC2V_CamSwitchDlg : public CDialog
{

public:

    CIFC_PC2V_CamSwitchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_CamSwitchDlg)
	enum { IDD = IDD_IFC_PC2V_CAMSWITCH_DIALOG };
	CStatic	m_StaticEOT3Light;
	CStatic	m_StaticEOT2Light;
	CStatic	m_StaticEOT1Light;
	CStatic	m_StaticEOFLight;
	CStatic	m_StaticSOFLight;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonSnap;
	CButton	m_ButtonTrigger;
	CEdit	m_EditFrameRateTotal;
	CEdit	m_EditCamType;
	CButton	m_ButtonCamType;
	CEdit	m_EditFrameRate;
	CEdit	m_EditSequenceCount;
	CButton	m_ButtonCamSequence;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonGrab;
	CEdit	m_EditConnector;
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
	CEdit	m_EditCamSeq;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_CamSwitchDlg)
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

    void SetPortAndCamType(char *pszCamType);

    void ReleaseAll(void);
    BOOL IsGrabbing(void);

    void ClearDisplay(DWORD dwCamIndex);
    void DrawWindowBorder(HWND hWnd);
    void EraseWindowBorder(HWND hWnd);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void UpdateCameraGUI(void);
    void DisableDisplay(DWORD dwBoardIndex);
    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);
    BOOL GetBufferToDisplay(DWORD *pThreadIndex);

    void ShowStatistics(void); 
    void UpdateButtons(void);

    void ShowEventLights(DWORD dwCamIndex, BOOL bToggler);
    void ReadAndClearEvents(DWORD dwCamIndex);

    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

    static void MyCallback_SOT(void *pContext);
    static void MyCallback_SOF(void *pContext);
    static void MyCallback_EOF(void *pContext);
    static void MyCallback_EOT1(void *pContext);
    static void MyCallback_EOT2(void *pContext);
    static void MyCallback_EOT3(void *pContext);
    static void MyCallback_SKF(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_CamSwitchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCamSeq();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrap();
	afx_msg void OnChangeEditCamSeq();
	afx_msg void OnButtonCamType();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonSnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                 // IFC board module handle
    CICamera    *m_apCam[CAM_MAX_NUMBER];   // Array of ptr to camera objects
    HIFCGRAB    m_aGrabID[CAM_MAX_NUMBER];
    BOOL        m_abIsGrabbing[CAM_MAX_NUMBER];

    CImgConn    *m_apImageConnection[CAM_MAX_NUMBER];

    PCIntrCallback  m_pIntCallback_SOT;
    PCIntrCallback  m_pIntCallback_SOF;
    PCIntrCallback  m_pIntCallback_EOF;
    PCIntrCallback  m_pIntCallback_EOT1;
    PCIntrCallback  m_pIntCallback_EOT2;
    PCIntrCallback  m_pIntCallback_EOT3;

    DWORD       m_dwCamSizeX;       // Camera frame X size for each module
    DWORD       m_dwCamSizeY;       // Camera frame Y size for each module
    DWORD       m_dwPixBitDepth;
    DWORD       m_dwImageSize;      // Camera frame Byte size
    IFC_COLOR   m_CamColor;

    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwSnapPolling;

    int         m_iFrameCountToGrab;

    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bCamSequenceTouched;
    BOOL        m_bCamTypeTouched;
    BOOL        m_bSystemOverload;

    DWORD       m_dwIsSOT_EventDetected;         // Start of Trigger callback counter
    DWORD       m_dwIsSOF_EventDetected;         // Start of Frame callback counter
    DWORD       m_dwIsEOF_EventDetected;         // End of Frame callback counter
    DWORD       m_dwIsEOT1_EventDetected;        // End of Transfer on channel # 1 callback counter
    DWORD       m_dwIsEOT2_EventDetected;        // End of Transfer on channel # 2 callback counter
    DWORD       m_dwIsEOT3_EventDetected;        // End of Transfer on channel # 3 callback counter

    BOOL        m_bWasSOT_EventDetected;
    BOOL        m_bWasSOF_EventDetected; 
    BOOL        m_bWasEOF_EventDetected; 
    BOOL        m_bWasEOT1_EventDetected; 
    BOOL        m_bWasEOT2_EventDetected; 
    BOOL        m_bWasEOT3_EventDetected;

    BOOL        m_bTriggerMode;                 // At least one camera is operating in Trigger mode
    BOOL        m_bSnapping;

    CThread             *m_apAcqThread[CAM_MAX_NUMBER];
    ACQ_THREAD_PARAM    m_aAcqThreadParams[CAM_MAX_NUMBER];

    CTimeMeasure        m_MeasureFramePeriod;

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_aDispThreadParams[CAM_MAX_NUMBER];

    // Camera sequence related variables

    DWORD   m_dwCamSequenceCount;
    DWORD   m_dwCurrentSeqIndex;
    DWORD   m_dwLastCamera;
    DWORD   m_adwCamSequence[CAM_MAX_NUMBER];
    BOOL    m_abCameraUsage[CAM_MAX_NUMBER];

    // GUI arrays

    HWND    m_ahCamLightOn[CAM_MAX_NUMBER];
    CStatic *m_apCamDisplay[CAM_MAX_NUMBER];

    BYTE    m_debugParallPort;

};





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_CAMSWITCHDLG_H__5E9FFD90_9A06_432B_A783_31534A4F595D__INCLUDED_)
