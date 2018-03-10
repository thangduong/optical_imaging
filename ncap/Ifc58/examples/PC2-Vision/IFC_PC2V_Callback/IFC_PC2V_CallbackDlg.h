//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_CallbackDlg.h
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


#if !defined(AFX_IFC_PC2V_CALLBACKDLG_H__17205A2F_6BF2_4B1F_B566_A9680000B91F__INCLUDED_)
#define AFX_IFC_PC2V_CALLBACKDLG_H__17205A2F_6BF2_4B1F_B566_A9680000B91F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V Callback")


#define TIMER_GUI           20






class CIFC_PC2V_CallbackDlg : public CDialog
{

public:

	CIFC_PC2V_CallbackDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_CallbackDlg)
	enum { IDD = IDD_IFC_PC2V_CALLBACK_DIALOG };
	CButton	m_ButtonTrigger;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditCameraType;
	CEdit	m_EditCallBkSOF;
	CEdit	m_EditCallBkEOF;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_CallbackDlg)
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

    void ClearDisplay(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void DrawWindowBorder(HWND hWnd);
    void UpdateButtons(void);

    static void MyAcqCallback_EOF(void *pContext);
    static void MyAcqCallback_SOF(void *pContext);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_CallbackDlg)
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

private:

    CICapMod    *m_pBrdMod;   // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;

    CImgConn        *m_pImageConnection;
    PCIntrCallback  m_pIntCallback_EOF;
    PCIntrCallback  m_pIntCallback_SOF;

    DWORD       m_dwCamSizeX;      // Camera frame X size for each module
    DWORD       m_dwCamSizeY;      // Camera frame Y size for each module
    DWORD       m_dwFrameCounter;
    DWORD       m_dwFieldCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bAppClosing;
    BOOL        m_bTriggerMode;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_CALLBACKDLG_H__17205A2F_6BF2_4B1F_B566_A9680000B91F__INCLUDED_)
