//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2V_ThreadProcDlg.h
//
//  BIRTH DATE:     December 2002
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



#if !defined(AFX_IFC_PC2V_THREADPROCDLG_H__6CEC7573_C682_47D0_B1F5_FE5BB724A71E__INCLUDED_)
#define AFX_IFC_PC2V_THREADPROCDLG_H__6CEC7573_C682_47D0_B1F5_FE5BB724A71E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE         _T("IFC PC2V Thread Proc")

#define TIMER_STAT              10
#define TIMER_GUI               20



#define BUFFER_COUNT            10
#define PROC_QUEUE_WATERMARK    BUFFER_COUNT / 2

#define WAIT_ACQ_MAX_MSEC       2000






//------------------------------
//          Data Structures
//------------------------------

class CIFC_PC2V_ThreadProcDlg;



typedef struct tagPROC_THREAD_PARAM
{
    BYTE        *pTheBuffer;
    HIFCGRAB    GrabID;
    int         iBufferIndex;

} PROC_THREAD_PARAM;




class CIFC_PC2V_ThreadProcDlg : public CDialog
{

public:

	CIFC_PC2V_ThreadProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_ThreadProcDlg)
	enum { IDD = IDD_IFC_PC2V_THREADPROC_DIALOG };
	CEdit	m_EditFrameNotAcquired;
	CEdit	m_EditFrameNotProcessed;
	CStatic	m_Static_OVL_Light;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditCameraType;
	CEdit	m_EditFrameLost;
	CEdit	m_EditProcTime;
	CEdit	m_EditFrameRate;
	CEdit	m_EditFrameCount;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_ThreadProcDlg)
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

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(HWND hWnd);

    void DrawRectangleLight(HWND hWnd, COLORREF TheColor, BOOL bDrawText, CString& strTheText);

    void ShowStatistics(void); 
    void UpdateButtons(void);

    static void ThreadAcqFunc(void *pContext);
    static void ThreadProcFunc(void *pContext);

    static void MyCallback_SKF(void *pContext);

    // Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_ThreadProcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTrigger();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

    void ProcImageFunction(BYTE *pImageBuffer, DWORD dwBufferIndex,
                           DWORD dwImageSizeX, DWORD dwImageSizeY);

private:

    CICapMod    *m_pBrdMod;   // Ptr 2 PCVision2 board capture module
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;
    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    CImgConn        *m_pImageConnection;
    PCIntrCallback  m_pIntCallback_SKF;

    DWORD       m_dwCamSizeX;           // Camera frame X Pixel size
    DWORD       m_dwCamSizeY;           // Camera frame Y Pixel size
    DWORD       m_dwPixBitDepth;
    DWORD       m_dwImageSize;          // Camera frame Byte size
    IFC_COLOR   m_CamColor;

    DWORD       m_dwFrameCounter;
    DWORD       m_dwSkippedFieldCounter;
    DWORD       m_dwFrameMissedCounter;
    DWORD       m_dwFrameNotProcessedCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    float       m_fProcTime;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bTriggerMode;
    BOOL        m_bSystemOverload;
    BOOL        m_bAppClosing;

    CThread             *m_pAcquisitionThread;
    CThread             *m_pProcessingThread;

    CPtrList            m_BufToProcList;
    CCriticalSection    m_csProcList;
    PROC_THREAD_PARAM   m_aThreadProcParam[BUFFER_COUNT];

    CTimeMeasure    m_MeasureProcTime;
    CTimeMeasure    m_MeasureAcqRate;

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_THREADPROCDLG_H__6CEC7573_C682_47D0_B1F5_FE5BB724A71E__INCLUDED_)
