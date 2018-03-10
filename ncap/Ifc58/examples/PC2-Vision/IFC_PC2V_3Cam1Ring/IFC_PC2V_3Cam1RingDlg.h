//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3Cam1RingDlg.h
//
//  BIRTH DATE:     July 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC V5.8
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2V_3CAM1RINGDLG_H__6723EB18_0C4B_4089_BAAF_94FD6C555DFE__INCLUDED_)
#define AFX_IFC_PC2V_3CAM1RINGDLG_H__6723EB18_0C4B_4089_BAAF_94FD6C555DFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V 3 Genlocked Camera into 1 Ring")

#define TIMER_STAT          10
#define TIMER_GUI           20

#define BUFFER_COUNT        10

#define WAIT_ACQ_MAX_MSEC   2000



//------------------------------
//          Data Structures
//------------------------------

class CIFC_PC2V_3Cam1RingDlg;



typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                    *pTheBuffer;
    HIFCGRAB                GrabID;
    int                     iBufferIndex;
    BOOL                    bBusy;

} DISPLAY_THREAD_PARAM;





class CIFC_PC2V_3Cam1RingDlg : public CDialog
{

public:

	CIFC_PC2V_3Cam1RingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_3Cam1RingDlg)
	enum { IDD = IDD_IFC_PC2V_3CAM1RING_DIALOG };
	CEdit	m_EditNotDisplayed;
	CStatic	m_StaticEOT3Light;
	CStatic	m_StaticEOT2Light;
	CStatic	m_StaticEOT1Light;
	CStatic	m_StaticEOFLight;
	CStatic	m_StaticSOFLight;
	CStatic	m_StaticSOTLight;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditSkippedField;
	CEdit	m_EditLostFrame;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCurrentCamera;
	CEdit	m_EditConnector;
	CStatic	m_StaticDisplay3;
	CStatic	m_StaticDisplay2;
	CStatic	m_StaticDisplay1;
	CEdit	m_EditFrameCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_3Cam1RingDlg)
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

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics(void); 
    void UpdateButtons(void);

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

    void ShowEventLights(void);
    void ReadAndClearEvents(void);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_3Cam1RingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonTrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;                 // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;                    // Ptr to camera objects
    HIFCGRAB    m_GrabID;                   // Grab token

    CImgConn        *m_apImageConnection[3];

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

    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    DWORD       m_dwFrameCounter;
    DWORD       m_dwSkippedFieldCounter;
    DWORD       m_dwFrameNotDisplayedCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    int         m_iFrameCountToGrab;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bSystemOverload;

    DWORD       m_dwIsSOT_EventCounter;         // Start of Trigger event counter
    DWORD       m_dwIsSOF_EventCounter;         // Start of Frame event counter
    DWORD       m_dwIsEOF_EventCounter;         // End of Frame event counter
    DWORD       m_dwIsEOT1_EventCounter;        // End of Transfer on channel # 1 event counter
    DWORD       m_dwIsEOT2_EventCounter;        // End of Transfer on channel # 2 event counter
    DWORD       m_dwIsEOT3_EventCounter;        // End of Transfer on channel # 3 event counter

    BOOL        m_bWasSOT_EventDetected;
    BOOL        m_bWasSOF_EventDetected; 
    BOOL        m_bWasEOF_EventDetected; 
    BOOL        m_bWasEOT1_EventDetected; 
    BOOL        m_bWasEOT2_EventDetected; 
    BOOL        m_bWasEOT3_EventDetected;

    BOOL        m_bTriggerMode;             // PC2-Vision is operating in triggered mode

    CThread     *m_pAcqThread;

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_aDispThreadParams[3];

    CTimeMeasure        m_MeasureFramePeriod;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_3CAM1RINGDLG_H__6723EB18_0C4B_4089_BAAF_94FD6C555DFE__INCLUDED_)
