//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_VixnDlg.h
//
//  BIRTH DATE:     December 2003
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

#if !defined(AFX_IFC_PC2V_VIXNDLG_H__59153778_9597_41A5_B57C_F59F6D0E4FB2__INCLUDED_)
#define AFX_IFC_PC2V_VIXNDLG_H__59153778_9597_41A5_B57C_F59F6D0E4FB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE         _T("IFC PC2V Vixn")

#define TIMER_STAT              10
#define TIMER_GUI               20


#define BUFFER_COUNT            10
#define JITTER_AVERAGE_COUNT    10
#define WAIT_ACQ_MAX_MSEC       2000

#define PIXEL_PER_MICRO_SEC     5


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



class CIFC_PC2V_VixnDlg : public CDialog
{

public:

	CIFC_PC2V_VixnDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_VixnDlg)
	enum { IDD = IDD_IFC_PC2V_VIXN_DIALOG };
	CEdit	m_EditMaxNonVixnJitter;
	CEdit	m_EditMaxVixnJitter;
	CStatic	m_StaticVixnCursor;
	CStatic	m_StaticNonVixnCursor;
	CEdit	m_EditVixnJitter;
	CEdit	m_EditNonVixnJitter;
	CEdit	m_EditVixnFrameCount;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCameraType;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	CEdit	m_EditFrameCount;
	CEdit	m_EditFrameLost;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_VixnDlg)
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
    void DrawCursor(HWND hWnd, COLORREF TheColor, DWORD dwWidth);
    void DrawTimingBarTickMark(HWND hWnd);

    void ShowStatistics(void); 
    void UpdateButtons(void);
    void ComputeAverageFramePeriodJitter(void);

    void ReadAndClearEvents(void);


    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

    static void MyCallback_EOF(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_VixnDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonTrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;         // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;

    CImgConn        *m_pImageConnection;

    PCIntrCallback  m_pIntCallback_EOF;

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

    double      m_dFramePeriod;
    double      m_dLastFramePeriod;
    double      m_dLastFrameTime;

    double      m_adVixnJitter[JITTER_AVERAGE_COUNT];
    double      m_adNonVixnJitter[JITTER_AVERAGE_COUNT];
    DWORD       m_dwJitterArrayIndex;

    double      m_dVixnAverageJitter;
    double      m_dNonVixnAverageJitter;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bSystemOverload;

    BOOL        m_bTriggerMode;

    DWORD       m_dwEOF_EventCounter;

    BOOL        m_bWasEOF_EventDetected; 

    CMyVixn     *m_pMyVixn;

    CThread     *m_pAcqThread;

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_DispThreadParams;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_VIXNDLG_H__59153778_9597_41A5_B57C_F59F6D0E4FB2__INCLUDED_)
