//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo
//
//  FILE:           IFC_PC2V_ThreadSaperaProcDlg.h
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

#if !defined(AFX_IFC_PC2V_THREADSAPERAPROCDLG_H__81743897_6830_4BA5_8FD2_EE1DFD151B22__INCLUDED_)
#define AFX_IFC_PC2V_THREADSAPERAPROCDLG_H__81743897_6830_4BA5_8FD2_EE1DFD151B22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE         _T("IFC PC2V Thread Sapera Processing")

#define TIMER_STAT              10
#define TIMER_GUI               20

#define BUFFER_COUNT            10
#define PROC_QUEUE_WATERMARK    BUFFER_COUNT / 2

#define WAIT_ACQ_MAX_MSEC       2000






//------------------------------
//      Data Structures
//------------------------------


typedef enum
{
    PROCFUNC_NO_PROC = 0,
    PROCFUNC_THRESHOLD,
    PROCFUNC_SOBEL_EDGE,
    PROCFUNC_CONV_2D,
    PROCFUNC_LAPLACIAN,
    PROCFUNC_INVERT

} PROC_FUNCTION;


typedef struct tagPROC_THREAD_PARAM
{
    BYTE        *pTheBuffer;
    HIFCGRAB    GrabID;
    int         iBufferIndex;

} PROC_THREAD_PARAM;



class CIFC_PC2V_ThreadSaperaProcDlg : public CDialog
{
// Construction
public:
	CIFC_PC2V_ThreadSaperaProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_ThreadSaperaProcDlg)
	enum { IDD = IDD_IFC_PC2V_THREADSAPERAPROC_DIALOG };
	CEdit	m_EditDisplayProcTime;
	CEdit	m_EditDisplayAcqTime;
	CComboBox	m_ComboProcFunction;
	CStatic	m_StaticDisplayResult;
	CEdit	m_EditFrameLost;
	CEdit	m_EditFrameNotProc;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonTrigger;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditProcTime;
	CEdit	m_EditFrameNotAcq;
	CEdit	m_EditProcFrameRate;
	CEdit	m_EditAcqFrameRate;
	CEdit	m_EditCameraType;
	CEdit	m_EditCurrentPort;
	CEdit	m_EditAcqFrameCount;
	CStatic	m_StaticDisplayAcq;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_ThreadSaperaProcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    HICON m_hIcon;

    void ReleaseAll(void);

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    CImgConn * InitIFC_AcqImageConnection(HWND hWnd);
    void ReleaseIFC_AcqImageConnection(void);

    CImgConn * InitIFC_ResultImageConnection(HWND hWnd);
    void ReleaseIFC_ResultImageConnection(void);

    BOOL InitIFC_Callback(void);
    void ReleaseIFC_Callback(void);

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);

    BOOL AllocateCaptureMemory(void);
    void ReleaseCaptureMemory(void);

    BOOL AllocateResultMemory(void);
    void ReleaseResultMemory(void);

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(HWND hWnd);

    void ShowStatistics(void); 
    void UpdateButtons(void);

    static void ThreadAcqFunc(void *pContext);
    static void ThreadProcFunc(void *pContext);

    static void MyCallback_FNA(void *pContext);


	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_ThreadSaperaProcDlg)
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
	afx_msg void OnButtonEnterTrap();
	afx_msg void OnButtonTrap();
	afx_msg void OnSelchangeComboProcFunc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

    void ProcImageFunction(BYTE *pImageBuffer, DWORD dwBufferIndex,
                           DWORD dwImageSizeX, DWORD dwImageSizeY);

private:

    CICapMod    *m_pBrdMod;   // Ptr 2 PCVision2 board capture module
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;
    BYTE        *m_pHostAcqMemory;
    MEMLOCKHDL  m_AcqMemLockHandle;
    BYTE        *m_pHostResultMemory;

    PCIntrCallback  m_pIntCallback_FNA;

    CImgConn    *m_pAcqImageConnection;
    CImgConn    *m_pResultImageConnection;

    DWORD       m_dwCamSizeX;           // Camera frame X Pixel size
    DWORD       m_dwCamSizeY;           // Camera frame Y Pixel size
    DWORD       m_dwPixBitDepth;
    DWORD       m_dwImageSize;          // Camera frame Byte size
    IFC_COLOR   m_CamColor;

    DWORD       m_dwFrameAcqCounter;
    DWORD       m_dwFrameNotProcCounter;
    DWORD       m_dwFrameNotAcqCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    float       m_fProcTime;
    float       m_fDisplayAcqTime;
    float       m_fDisplayProcTime;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bTriggerMode;
    BOOL        m_bSystemOverload;
    BOOL        m_bAppClosing;

    CThread             *m_pAcquisitionThread;
    CThread             *m_pProcessingThread;
    CPtrList            m_BufToProcList;
    CCriticalSection    m_csProcList;

    CTimeMeasure    m_MeasureProcTime;
    CTimeMeasure    m_MeasureDisplayAcqTime;
    CTimeMeasure    m_MeasureDisplayProcTime;
    CTimeMeasure    m_MeasureAcqRate;
    CTimeMeasure    m_MeasureProcRate;

    CProBasic           *m_pMySaperaBasicProcessor;
    PROC_FUNCTION       m_CurrentProcFunc;
    PROC_THREAD_PARAM   m_aThreadProcParam[BUFFER_COUNT];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_THREADSAPERAPROCDLG_H__81743897_6830_4BA5_8FD2_EE1DFD151B22__INCLUDED_)
