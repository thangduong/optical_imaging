//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CamSwitchPlanarVerticalDlg.h
//
//  BIRTH DATE:     October 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.7)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2V_CAMSWITCHPLANARVERTICALDLG_H__28875A18_34E6_4501_99C8_1538CE8BEF89__INCLUDED_)
#define AFX_IFC_PC2V_CAMSWITCHPLANARVERTICALDLG_H__28875A18_34E6_4501_99C8_1538CE8BEF89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE             _T("IFC PC2V Planar Vertical Camera Switching")

#define TIMER_STAT                  10
#define TIMER_GUI                   20

#define BUFFER_COUNT                10
#define CAMERA_GROUP_COUNT          2
#define CAMERA_COUNT_PER_GROUP      3

#define WAIT_ACQ_MAX_MSEC           2000
#define WAIT_SNAP_MAX               6



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_CamSwitchPlanarVerticalDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_CamSwitchPlanarVerticalDlg    *pMyClass;
    DWORD                                   dwMyGroupIndex;

} ACQ_THREAD_PARAM;


typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                *pTheBuffer;
    HIFCGRAB            GrabID;
    int                 iBufferIndex;
    BOOL                bBusy;

} DISPLAY_THREAD_PARAM;





class CIFC_PC2V_CamSwitchPlanarVerticalDlg : public CDialog
{
// Construction
public:
	CIFC_PC2V_CamSwitchPlanarVerticalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	enum { IDD = IDD_IFC_PC2V_CAMSWITCHPLANARVERTICAL_DIALOG };
	CStatic	m_StaticRedLightGroup2;
	CStatic	m_StaticRedLightGroup1;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonCamType;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonSnap;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRateTotal;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCamType;
	CStatic	m_StaticDisplayGroup2;
	CStatic	m_StaticDisplayGroup1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

    void ReleaseAll(void);

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    BOOL InitIFC_Callback(void);
    void ReleaseIFC_Callback(void);

    CImgConn * InitIFC_ImageConnection(CStatic *pDisplayWindow);
    void ReleaseIFC_ImageConnection(DWORD dwCamNumber);

    void SetCamType(char *pszCamType);
    BOOL IsGrabbing(void);

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics();
    void UpdateButtons(void);

    void DrawWindowBorder(HWND hWnd);
    BOOL GetBufferToDisplay(DWORD *pCameraIndex);

    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

    static void MyCallback_SOT(void *pContext);

    void ShowEventLights(void);
    void ReadAndClearEvents(void);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_CamSwitchPlanarVerticalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonTypeCam();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonTrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CPCVision2  *m_pBrdMod;                         // IFC board module handle
    CICamera    *m_apCam[CAMERA_GROUP_COUNT];       // Array of ptr to camera objects
    HIFCGRAB    m_aGrabID[CAMERA_GROUP_COUNT];

    CImgConn    *m_apImageConnection[CAMERA_GROUP_COUNT];

    PCIntrCallback  m_pIntCallback_SOT;

    DWORD       m_dwCamSizeX;
    DWORD       m_dwCamSizeY;
    DWORD       m_dwPixBitDepth;
    IFC_COLOR   m_CamColor;
    DWORD       m_dwImageSize;

    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwSnapPolling;

    BOOL        m_abIsGrabbing[CAMERA_GROUP_COUNT];
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bSnapping;
    BOOL        m_bSystemOverload;

    DWORD       m_dwIsSOT_EventCounter;         // Start of Trigger callback counter
    BOOL        m_bWasSOT_EventDetected;        // Start of Trigger official status

    BOOL        m_bTriggerMode;                 // PC2-Vision operating in triggered mode
    BOOL        m_dwLastGroup;
    HWND        m_hLastRedLightGroup;

    CThread                 *m_apAcqThread[CAMERA_GROUP_COUNT];
    ACQ_THREAD_PARAM        m_aAcqThreadParams[CAMERA_GROUP_COUNT];

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_aDispThreadParams[CAMERA_GROUP_COUNT];

    CTimeMeasure            m_MeasureFramePeriod;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_CAMSWITCHPLANARVERTICALDLG_H__28875A18_34E6_4501_99C8_1538CE8BEF89__INCLUDED_)
