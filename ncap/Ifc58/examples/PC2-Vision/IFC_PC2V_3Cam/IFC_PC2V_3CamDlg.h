//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3CamDlg.h
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



#if !defined(AFX_IFC_PC2V_3CAMDLG_H__20AF6518_7306_43B3_9780_B8B6D1DAB133__INCLUDED_)
#define AFX_IFC_PC2V_3CAMDLG_H__20AF6518_7306_43B3_9780_B8B6D1DAB133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V 3 Genlocked Camera")

#define TIMER_STAT          10
#define TIMER_GUI           20

#define BUFFER_COUNT        10
#define CAMERA_COUNT        3

#define WAIT_ACQ_MAX_MSEC   2000
#define WAIT_SNAP_MAX       6



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_3CamDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_3CamDlg   *pMyClass;
    DWORD               dwCameraIndex;

} ACQ_THREAD_PARAM;



typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                *pTheBuffer;
    HIFCGRAB            GrabID;
    int                 iBufferIndex;
    BOOL                bBusy;

} DISPLAY_THREAD_PARAM;



class CIFC_PC2V_3CamDlg : public CDialog
{

public:

    CIFC_PC2V_3CamDlg(CWnd* pParent = NULL);        // standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_3CamDlg)
	enum { IDD = IDD_IFC_PC2V_3CAM_DIALOG };
	CEdit	m_EditFrameNotDisplayed;
	CButton	m_ButtonSnap;
	CButton	m_ButtonTrigger;
	CEdit	m_EditSkippedField;
	CEdit	m_EditConnector;
	CStatic	m_StaticEOT1Light;
	CStatic	m_StaticEOT3Light;
	CStatic	m_StaticEOT2Light;
	CStatic	m_StaticEOFLight;
	CStatic	m_StaticSOFLight;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCurrentCamera;
	CStatic	m_StaticDisplay3;
	CStatic	m_StaticDisplay2;
	CStatic	m_StaticDisplay1;
	CEdit	m_EditFrameCount;
	CEdit	m_EditFrameLost;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_3CamDlg)
	public:
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

    void SetConnectorAndCamType(DWORD dwConnector, char *pszCamType);
    BOOL IsGrabbing(void);

    BOOL AllocateCaptureMemory(DWORD dwCamNumber);
    void ReleaseCaptureMemory(DWORD dwCamNumber);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics(void); 
    void ShowEventLights(void);
    void UpdateButtons(void);
    BOOL GetBufferToDisplay(DWORD *pCameraIndex);

    void DrawWindowBorder(HWND hWnd);
    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

    static void MyCallback_SOT(void *pContext);
    static void MyCallback_SOF(void *pContext);
    static void MyCallback_EOF(void *pContext);
    static void MyCallback_EOT1(void *pContext);
    static void MyCallback_EOT2(void *pContext);
    static void MyCallback_EOT3(void *pContext);
    static void MyCallback_SKF(void *pContext);

    void ReadAndClearEvents(void);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_3CamDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonSnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;                 // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_apCam[CAMERA_COUNT];     // Array of ptr to camera objects
    HIFCGRAB    m_aGrabID[CAMERA_COUNT];

    CImgConn        *m_apImageConnection[CAMERA_COUNT];

    PCIntrCallback  m_pIntCallback_SOT;
    PCIntrCallback  m_pIntCallback_SOF;
    PCIntrCallback  m_pIntCallback_EOF;
    PCIntrCallback  m_pIntCallback_EOT1;
    PCIntrCallback  m_pIntCallback_EOT2;
    PCIntrCallback  m_pIntCallback_EOT3;
    PCIntrCallback  m_pIntCallback_SKF;

    DWORD       m_dwCamSizeX;
    DWORD       m_dwCamSizeY;
    DWORD       m_dwPixBitDepth;
    IFC_COLOR   m_CamColor;
    DWORD       m_dwImageSize;

    BYTE        *m_apHostCapMemory[CAMERA_COUNT];
    MEMLOCKHDL  m_aCapMemLockHandle[CAMERA_COUNT];

    DWORD       m_dwFrameCounter;
    DWORD       m_dwSkippedFrameCounter;
    DWORD       m_dwFrameNotDisplayedCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_dwSnapPolling;

    int         m_aiFrameCountToGrab[CAMERA_COUNT];

    BOOL        m_abIsGrabbing[CAMERA_COUNT];
    BOOL        m_bIsSnapping;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bTriggerMode;                 // PC2-Vision is operating in triggered mode
    BOOL        m_bSystemOverload;              // The host cannot display all the images

    DWORD       m_dwIsSOT_EventCounter;         // Start of Trigger callback counter
    DWORD       m_dwIsSOF_EventCounter;         // Start of Frame callback counter
    DWORD       m_dwIsEOF_EventCounter;         // End of Frame callback counter
    DWORD       m_dwIsEOT1_EventCounter;        // End of Transfer on channel # 1 callback counter
    DWORD       m_dwIsEOT2_EventCounter;        // End of Transfer on channel # 2 callback counter
    DWORD       m_dwIsEOT3_EventCounter;        // End of Transfer on channel # 3 callback counter


    BOOL        m_bWasSOT_EventDetected;
    BOOL        m_bWasSOF_EventDetected; 
    BOOL        m_bWasEOF_EventDetected; 
    BOOL        m_bWasEOT1_EventDetected; 
    BOOL        m_bWasEOT2_EventDetected; 
    BOOL        m_bWasEOT3_EventDetected;


    CThread             *m_apAcqThread[CAMERA_COUNT];
    ACQ_THREAD_PARAM    m_aAcqThreadParams[CAMERA_COUNT];

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_aDispThreadParams[CAMERA_COUNT];

    CTimeMeasure        m_MeasureFramePeriod;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_3CAMDLG_H__20AF6518_7306_43B3_9780_B8B6D1DAB133__INCLUDED_)
