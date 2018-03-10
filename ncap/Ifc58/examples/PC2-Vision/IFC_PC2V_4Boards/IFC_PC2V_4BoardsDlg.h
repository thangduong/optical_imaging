//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_4BoardsDlg.h
//
//  BIRTH DATE:     April 2003
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

#if !defined(AFX_IFC_PC2V_4BOARDSDLG_H__FBB1DA4B_29E7_437D_91BE_3B6F1533CADD__INCLUDED_)
#define AFX_IFC_PC2V_4BOARDSDLG_H__FBB1DA4B_29E7_437D_91BE_3B6F1533CADD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//--------------------------------
//          Constants
//--------------------------------

#define     APP_BASIC_TITLE     _T("IFC PC2V Four Boards")

#define     BOARD_MAX_NUMBER    4
#define     BUFFER_COUNT        10

#define TIMER_STAT          10
#define TIMER_GUI           20

#define WAIT_ACQ_MAX_MSEC   2000



//------------------------------
//          Data Structure
//------------------------------

class CIFC_PC2V_4BoardsDlg;


typedef struct tag_ACQ_THREAD_PARAM
{
    CIFC_PC2V_4BoardsDlg    *pMyClass;
    DWORD                   dwMyBoardIndex;

} ACQ_THREAD_PARAM;


typedef struct tagDISPLAY_THREAD_PARAM
{
    BYTE                *pTheBuffer;
    HIFCGRAB            GrabID;
    int                 iBufferIndex;
    BOOL                bBusy;

} DISPLAY_THREAD_PARAM;





class CIFC_PC2V_4BoardsDlg : public CDialog
{

public:

	CIFC_PC2V_4BoardsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_4BoardsDlg)
	enum { IDD = IDD_IFC_PC2V_4BOARDS_DIALOG };
	CEdit	m_EditSerialNumber3;
	CEdit	m_EditSerialNumber4;
	CEdit	m_EditSerialNumber2;
	CEdit	m_EditSerialNumber1;
	CButton	m_ButtonTrigger4;
	CButton	m_ButtonTrigger3;
	CButton	m_ButtonTrigger2;
	CButton	m_ButtonTrigger1;
	CEdit	m_EditPort4;
	CEdit	m_EditPort3;
	CEdit	m_EditPort2;
	CEdit	m_EditPort1;
	CButton	m_ButtonSnap4;
	CButton	m_ButtonSnap3;
	CButton	m_ButtonSnap2;
	CButton	m_ButtonSnap1;
	CButton	m_ButtonFreeze4;
	CButton	m_ButtonFreeze3;
	CButton	m_ButtonFreeze2;
	CButton	m_ButtonFreeze1;
	CButton	m_ButtonGrab4;
	CButton	m_ButtonGrab3;
	CButton	m_ButtonGrab2;
	CButton	m_ButtonGrab1;
	CButton	m_ButtonCamType4;
	CButton	m_ButtonCamType3;
	CButton	m_ButtonCamType2;
	CButton	m_ButtonCamType1;
	CEdit	m_EditCamType4;
	CEdit	m_EditCamType3;
	CEdit	m_EditCamType2;
	CEdit	m_EditCamType1;
	CEdit	m_EditFrameRate4;
	CEdit	m_EditFrameRate3;
	CEdit	m_EditFrameRate2;
	CEdit	m_EditFrameRate1;
	CEdit	m_EditFrameCount4;
	CEdit	m_EditFrameCount3;
	CEdit	m_EditFrameCount2;
	CEdit	m_EditFrameCount1;
	CStatic	m_StaticDisplayCam4;
	CStatic	m_StaticDisplayCam3;
	CStatic	m_StaticDisplayCam2;
	CStatic	m_StaticDisplayCam1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_4BoardsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

    HICON m_hIcon;

    BOOL InitIFC_Capture(DWORD *pdwBoardCount);
    void ReleaseIFC_Capture(void);

    CImgConn * InitIFC_ImageConnection(DWORD dwBoardNumber);
    void ReleaseIFC_ImageConnection(DWORD dwBoardNumber);

    BOOL AllocateCaptureMemory(DWORD dwBoardNumber);
    void ReleaseCaptureMemory(DWORD dwBoardNumber);

    void ClearDisplay(DWORD dwBoardIndex);
    void DisableDisplay(DWORD dwBoardIndex);

    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(DWORD dwBoardIndex);
    void ShowStatistics(void); 
    void UpdateButtons(DWORD dwBoardIndex);
    void ShowSerialNumber(DWORD dwBoardIndex);

    void GetUserCamType(DWORD dwBoardIndex);
    void SetPortAndCamType(DWORD dwBoardIndex, DWORD dwActivePort, char *pszCamType);

    void ReleaseAll(void);
    BOOL GetBufferToDisplay(DWORD *dwBoardIndex);

    static void ThreadAcqProc(void *pContext);
    static void ThreadDisplayProc(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_4BoardsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonGrab1();
	afx_msg void OnButtonGrab2();
	afx_msg void OnButtonGrab3();
	afx_msg void OnButtonGrab4();
	afx_msg void OnButtonFreeze1();
	afx_msg void OnButtonFreeze2();
	afx_msg void OnButtonFreeze3();
	afx_msg void OnButtonFreeze4();
	afx_msg void OnButtonTypeCam1();
	afx_msg void OnButtonTypeCam2();
	afx_msg void OnButtonTypeCam3();
	afx_msg void OnButtonTypeCam4();
	afx_msg void OnButtonSnap1();
	afx_msg void OnButtonSnap2();
	afx_msg void OnButtonSnap3();
	afx_msg void OnButtonSnap4();
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTrigger1();
	afx_msg void OnButtonTrigger2();
	afx_msg void OnButtonTrigger3();
	afx_msg void OnButtonTrigger4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_apBrdMod[BOARD_MAX_NUMBER];  // Array of ptr to PCVision2 board capture modules
    CICamera    *m_apCam[BOARD_MAX_NUMBER];     // Array of ptr to camera objects
    HIFCGRAB    m_aGrabID[BOARD_MAX_NUMBER];

    CImgConn    *m_apImageConnection[BOARD_MAX_NUMBER];

    DWORD       m_adwCamSizeX[BOARD_MAX_NUMBER];        // Camera frame X size for each module
    DWORD       m_adwCamSizeY[BOARD_MAX_NUMBER];        // Camera frame Y size for each module
    DWORD       m_adwBitDepth[BOARD_MAX_NUMBER];        // Bits per pixel
    DWORD       m_adwImageSize[BOARD_MAX_NUMBER];       // Camera frame Byte size
    IFC_COLOR   m_aCamColor[BOARD_MAX_NUMBER];
    BOOL        m_abTriggerMode[BOARD_MAX_NUMBER];

    BYTE        *m_apHostCapMemory[BOARD_MAX_NUMBER];
    MEMLOCKHDL  m_aCapMemLockHandle[BOARD_MAX_NUMBER];

    DWORD       m_adwFrameCounter[BOARD_MAX_NUMBER];
    DWORD       m_adwSelectedPort[BOARD_MAX_NUMBER];

    BOOL        m_abIsGrabbing[BOARD_MAX_NUMBER];
    BOOL        m_abClearDisplay[BOARD_MAX_NUMBER];
    BOOL        m_bSystemOverload;

    DWORD       m_dwBoardCount;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;
    DWORD       m_adwBoardSerial[BOARD_MAX_NUMBER];

    CThread             *m_apAcqThread[BOARD_MAX_NUMBER];
    ACQ_THREAD_PARAM    m_aAcqThreadParams[BOARD_MAX_NUMBER];

    CTimeMeasure        m_aMeasureFramePeriod[BOARD_MAX_NUMBER];

    CThread                 *m_pDisplayThread;
    DISPLAY_THREAD_PARAM    m_aDispThreadParams[BOARD_MAX_NUMBER];

    // GUI arrays

    CStatic *m_apCamDisplay[BOARD_MAX_NUMBER];

    CEdit   *m_apEditFrameCount[BOARD_MAX_NUMBER];
    CEdit   *m_apEditFrameRate[BOARD_MAX_NUMBER];
    CEdit   *m_apEditPort[BOARD_MAX_NUMBER];
    CEdit   *m_apEditCameraType[BOARD_MAX_NUMBER];
    CEdit   *m_apEditSerialNumber[BOARD_MAX_NUMBER];

    CButton *m_apButtonGrab[BOARD_MAX_NUMBER];
    CButton *m_apButtonFreeze[BOARD_MAX_NUMBER];
    CButton *m_apButtonSnap[BOARD_MAX_NUMBER];
    CButton *m_apButtonTrigger[BOARD_MAX_NUMBER];
    CButton *m_apButtonCamSelect[BOARD_MAX_NUMBER];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_4BOARDSDLG_H__FBB1DA4B_29E7_437D_91BE_3B6F1533CADD__INCLUDED_)
