//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_2x3CamSwitchDlg.h
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


#if !defined(AFX_IFC_PC2V_2X3CAMSWITCHDLG_H__EDE26EC2_CF83_43B8_A9BA_7CA9F1B781F6__INCLUDED_)
#define AFX_IFC_PC2V_2X3CAMSWITCHDLG_H__EDE26EC2_CF83_43B8_A9BA_7CA9F1B781F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V 2x3 Genlocked Camera Switched")

#define TIMER_STAT          10
#define TIMER_GUI           20

#define BUFFER_COUNT        10
#define CAMERA_COUNT        6

#define WAIT_ACQ_MAX_MSEC   2000
#define WAIT_SNAP_MAX       6



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_2x3CamSwitchDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_2x3CamSwitchDlg   *pMyClass;
    DWORD                       dwMyCameraIndex;

} ACQ_THREAD_PARAM;




class CIFC_PC2V_2x3CamSwitchDlg : public CDialog
{

public:

	CIFC_PC2V_2x3CamSwitchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_2x3CamSwitchDlg)
	enum { IDD = IDD_IFC_PC2V_2X3CAMSWITCH_DIALOG };
	CButton	m_ButtonSnap;
	CButton	m_ButtonTrigger;
	CEdit	m_EditFrameRateTotal;
	CButton	m_ButtonCamType;
	CEdit	m_EditCamType;
	CStatic	m_StaticLightGroup2;
	CStatic	m_StaticLightGroup1;
	CEdit	m_EditFrameRate;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonGrab;
	CStatic	m_StaticDisplayCam23;
	CStatic	m_StaticDisplayCam22;
	CStatic	m_StaticDisplayCam21;
	CStatic	m_StaticDisplayCam13;
	CStatic	m_StaticDisplayCam12;
	CStatic	m_StaticDisplayCam11;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_2x3CamSwitchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    HICON m_hIcon;

    void ReleaseAll(void);

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    BOOL InitIFC_Callback(void);
    void ReleaseIFC_Callback(void);

    CImgConn * InitIFC_ImageConnection(CStatic *pDisplayWindow, DWORD dwCamNumber);
    void ReleaseIFC_ImageConnection(DWORD dwCamNumber);

    void SetCamType(char *pszCamType);
    BOOL IsGrabbing(void);

    BOOL AllocateCaptureMemory(DWORD dwCamNumber);
    void ReleaseCaptureMemory(DWORD dwCamNumber);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics();
    void UpdateButtons(void);
    void DrawEventLights(void);

    void DrawWindowBorder(HWND hWnd);
    void DrawEventDetected(HWND hWnd);
    void DrawEventNotDetected(HWND hWnd);
    void EraseEventDetected(HWND hWnd);
    void DrawCameraLightOn(DWORD dwConnIndex);
    void DrawCameraLightOff(DWORD dwConnIndex);

    static void ThreadAcqProc(void *pContext);

    static void MyCallback_SOT(void *pContext);

    void ReadAndClearEvents(void);


	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_2x3CamSwitchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTypeCam();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonSnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                 // IFC board module handle
    CICamera    *m_apCam[CAMERA_COUNT];     // Array of ptr to camera objects
    HIFCGRAB    m_aGrabID[CAMERA_COUNT];

    CImgConn    *m_apImageConnection[CAMERA_COUNT];

    PCIntrCallback  m_pIntCallback_SOT;

    DWORD       m_dwCamSizeX;
    DWORD       m_dwCamSizeY;
    DWORD       m_dwPixBitDepth;
    IFC_COLOR   m_CamColor;
    DWORD       m_dwImageSize;

    BYTE        *m_apHostCapMemory[CAMERA_COUNT];
    MEMLOCKHDL  m_aCapMemLockHandle[CAMERA_COUNT];

    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwSnapPolling;

    BOOL        m_abIsGrabbing[CAMERA_COUNT];
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bSnapping;

    BOOL        m_bIsSOT_EventDetected;         // Start of Trigger
    BOOL        m_bWasSOT_EventDetected;        // Start of Trigger copy

    BOOL        m_bTriggerMode;                 // PC2-Vision operating in triggered mode
    BOOL        m_dwLastGroup;

    CThread             *m_apAcqThread[CAMERA_COUNT];
    ACQ_THREAD_PARAM    m_aAcqThreadParams[CAMERA_COUNT];

    CTimeMeasure        m_MeasureFramePeriod;

    CStatic     *m_apCamDisplay[CAMERA_COUNT];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_2X3CAMSWITCHDLG_H__EDE26EC2_CF83_43B8_A9BA_7CA9F1B781F6__INCLUDED_)
