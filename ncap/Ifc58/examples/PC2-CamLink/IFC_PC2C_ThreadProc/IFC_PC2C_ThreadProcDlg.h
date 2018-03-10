//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Camlink Frame Grabber
//
//  FILE:           IFC_PC2C_ThreadProcDlg.h
//
//  BIRTH DATE:     December 2003
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

#if !defined(AFX_IFC_PC2C_THREADPROCDLG_H__8557A8D3_F2B2_4E50_B0FC_C6EAB0E40C5A__INCLUDED_)
#define AFX_IFC_PC2C_THREADPROCDLG_H__8557A8D3_F2B2_4E50_B0FC_C6EAB0E40C5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE         _T("IFC PC2C Thread Proc")

#define TIMER_STAT              10
#define TIMER_GUI               20



#define BUFFER_COUNT            10
#define PROC_QUEUE_WATERMARK    BUFFER_COUNT / 2

#define WAIT_ACQ_MAX_MSEC       2000






//------------------------------
//          Data Structures
//------------------------------

class CIFC_PC2C_ThreadProcDlg;



typedef struct tagPROC_THREAD_PARAM
{
    BYTE        *pTheBuffer;
    HIFCGRAB    GrabID;
    int         iBufferIndex;

} PROC_THREAD_PARAM;



class CIFC_PC2C_ThreadProcDlg : public CDialog
{

public:

	CIFC_PC2C_ThreadProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2C_ThreadProcDlg)
	enum { IDD = IDD_IFC_PC2C_THREADPROC_DIALOG };
	CButton	m_ButtonCamSelect;
	CEdit	m_EditFrameCount;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditFrameNotProcessed;
	CEdit	m_EditFrameNotAcquired;
	CEdit	m_EditProcTime;
	CEdit	m_EditFrameLost;
	CStatic	m_Static_OVL_Light;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCameraType;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2C_ThreadProcDlg)
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

    void SetPortAndCamType(char *pszCamType);

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
	//{{AFX_MSG(CIFC_PC2C_ThreadProcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonTrigger();
	afx_msg void OnButtonTrap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

    void ProcImageFunctionMono8(BYTE *pImageBuffer, DWORD dwBufferIndex,
                                 DWORD dwImageSizeX, DWORD dwImageSizeY);

    void ProcImageFunctionMono10(BYTE *pImageBuffer, DWORD dwBufferIndex,
                                  DWORD dwImageSizeX, DWORD dwImageSizeY);

private:

    CICapMod    *m_pBrdMod;                 // Ptr 2 PCVision2 board capture module
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;
    BYTE        *m_pHostCapMemory;
    MEMLOCKHDL  m_CapMemLockHandle;

    CImgConn        *m_pImageConnection;
    PCIntrCallback  m_pIntCallback_SKF;

    DWORD       m_dwCamSizeX;               // Camera frame X Pixel size
    DWORD       m_dwCamSizeY;               // Camera frame Y Pixel size
    DWORD       m_dwPixBitDepth;
    DWORD       m_dwBytePerPixel;
    DWORD       m_dwImageSize;              // Camera frame Byte size
    IFC_COLOR   m_CamColor;

    DWORD       m_dwFrameCounter;
    DWORD       m_dwSkippedFieldCounter;
    DWORD       m_dwFrameMissedCounter;
    DWORD       m_dwFrameNotProcessedCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    int         m_iFrameCountToGrab;
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

#endif // !defined(AFX_IFC_PC2C_THREADPROCDLG_H__8557A8D3_F2B2_4E50_B0FC_C6EAB0E40C5A__INCLUDED_)
