//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_ThreadTrigDlg.h
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


#if !defined(AFX_IFC_PC2V_THREADTRIGDLG_H__B0A58C66_C415_4E3F_A3BE_009B78BA07FA__INCLUDED_)
#define AFX_IFC_PC2V_THREADTRIGDLG_H__B0A58C66_C415_4E3F_A3BE_009B78BA07FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V Thread Frame Triggered")

#define TIMER_STAT          10
#define TIMER_GUI           20


#define BUFFER_COUNT        10
#define WAIT_ACQ_MAX_MSEC   2000


//------------------------------
//          Data Structures
//------------------------------


typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                *pTheBuffer;
    HIFCGRAB            GrabID;
    int                 iBufferIndex;
    BOOL                bBusy;

} DISPLAY_THREAD_PARAM;




class CIFC_PC2V_ThreadTrigDlg : public CDialog
{

public:

	CIFC_PC2V_ThreadTrigDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_ThreadTrigDlg)
	enum { IDD = IDD_IFC_PC2V_THREADTRIG_DIALOG };
	CButton	m_CheckTrigBeep;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CButton	m_ButtonFreeze;
	CEdit	m_EditCameraType;
	CButton	m_ButtonStrobeParam;
	CButton	m_ButtonCamSigParam;
	CStatic	m_StaticEOTLight;
	CStatic	m_StaticEOFLight;
	CStatic	m_StaticSOFLight;
	CStatic	m_StaticSOTLight;
	CStatic	m_StaticTrigLight;
	CEdit	m_EditFrameLost;
	CEdit	m_EditFrameCount;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonStop;
	CButton	m_ButtonStart;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_ThreadTrigDlg)
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

    CImgConn * InitIFC_ImageConnection(HWND hWnd, CICamera *cam);
    void ReleaseIFC_ImageConnection(void);

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(HWND hWnd);

    void ShowStatistics(void); 
    void UpdateButtons(void);

    void ShowEventLights(void);
    void ReadAndClearEvents(void);

    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

    static void MyCallback_SOT(void *pContext);
    static void MyCallback_SOF(void *pContext);
    static void MyCallback_EOF(void *pContext);
    static void MyCallback_EOT1(void *pContext);
    static void MyCallback_EOT2(void *pContext);
    static void MyCallback_EOT3(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_ThreadTrigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonCamSigParam();
	afx_msg void OnButtonStrobeParam();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonSnap();
	afx_msg void OnCheckTrigBeep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;         // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;

    CImgConn        *m_pImageConnection;

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
    DWORD       m_dwActivePort;

    DWORD       m_dwFrameCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bSystemOverload;

    BOOL        m_bTriggerMode;
    BOOL        m_bIsTrigBeepEnable;

    DWORD       m_dwIsSOT_EventCounter;         // Start of Trigger
    DWORD       m_dwIsSOF_EventCounter;         // Start of Frame
    DWORD       m_dwIsEOF_EventCounter;         // End of Frame
    DWORD       m_dwIsEOT1_EventCounter;        // End of Transfer on channel # 1
    DWORD       m_dwIsEOT2_EventCounter;        // End of Transfer on channel # 2
    DWORD       m_dwIsEOT3_EventCounter;        // End of Transfer on channel # 3

    BOOL        m_bWasSOT_EventDetected;
    BOOL        m_bWasSOF_EventDetected; 
    BOOL        m_bWasEOF_EventDetected; 
    BOOL        m_bWasEOT1_EventDetected; 
    BOOL        m_bWasEOT2_EventDetected; 
    BOOL        m_bWasEOT3_EventDetected;

    CThread             *m_pAcqThread;
    CTimeMeasure        m_MeasureFramePeriod;

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_DispThreadParams;

    CCamSigParamDlg     *m_pMyCamSigParamDlg;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_THREADTRIGDLG_H__B0A58C66_C415_4E3F_A3BE_009B78BA07FA__INCLUDED_)
