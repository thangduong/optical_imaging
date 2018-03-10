//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_BasicHardOverlayDlg.h
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

#if !defined(AFX_IFC_PC2V_BASICHARDOVERLAYDLG_H__23A73B3C_D11B_4D0C_8D15_726F9F4252EE__INCLUDED_)
#define AFX_IFC_PC2V_BASICHARDOVERLAYDLG_H__23A73B3C_D11B_4D0C_8D15_726F9F4252EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//------------------------------
//          Constants
//------------------------------

#define APP_BASIC_TITLE     _T("IFC PC2V Basic Hard Overlay")

#define TIMER_STAT          10
#define TIMER_GUI           20
#define TIMER_DRAW          30


#define KEY_COLOR           RGB(0,1,0xFF)
//------------------------------------------
// NOTE : The keying color must not be in
//        the range 0-9 or 246-255 when
//        calling SetDestColorKey().
//------------------------------------------




class CIFC_PC2V_BasicHardOverlayDlg : public CDialog
{

public:

	CIFC_PC2V_BasicHardOverlayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_BasicHardOverlayDlg)
	enum { IDD = IDD_IFC_PC2V_BASICHARDOVERLAY_DIALOG };
	CButton	m_ButtonTrigger;
	CButton	m_ButtonCamSelect;
	CButton	m_ButtonFreeze;
	CButton	m_ButtonSnap;
	CButton	m_ButtonGrab;
	CEdit	m_EditCameraType;
	CEdit	m_EditFrameRate;
	CEdit	m_EditCurrentPort;
	CStatic	m_StaticDisplay;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_BasicHardOverlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	HICON m_hIcon;

    void ReleaseAll(void);

    BOOL InitIFC_Capture(void);
    void ReleaseIFC_Capture(void);

    CImgConn * InitIFC_ImageConnection(HWND hWnd);
    void ReleaseIFC_ImageConnection(void);

    void SetPortAndCamType(DWORD dwActivePort, char *pszCamType);

    void ClearDisplay(void);
    void FillDisplayWithKeyColor(void);
    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);
    void ShowStatistics(void); 
    void UpdateButtons(void);

    void DrawWindowBorder(HWND hWnd);
    void DrawTextTopLeft(void);
    void DrawTextBottomRight(void);
    void DrawTextCentered(void);

	// Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_BasicHardOverlayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCam();
	afx_msg void OnButtonFreeze();
	afx_msg void OnButtonGrab();
	afx_msg void OnButtonSnap();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnButtonTrap();
	afx_msg void OnButtonTrigger();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod    *m_pBrdMod;   // Ptr array 2 PCVision2 board capture modules
    CICamera    *m_pCam;
    HIFCGRAB    m_GrabID;

    CImgSrc     *m_pImgSrc;
    CImgSink    *m_pSinkTemplate;
    CImgConn    *m_pImageConnection;

    DWORD       m_dwCamSizeX;      // Camera frame X size for each module
    DWORD       m_dwCamSizeY;      // Camera frame Y size for each module
    DWORD       m_dwFrameCounter;
    DWORD       m_dwOnPaintCounter;
    DWORD       m_dwLastOnPaintCounter;
    DWORD       m_dwGuiCounter;

    BOOL        m_bIsGrabbing;
    BOOL        m_bClearDisplay;
    BOOL        m_bTriggerMode;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_BASICHARDOVERLAYDLG_H__23A73B3C_D11B_4D0C_8D15_726F9F4252EE__INCLUDED_)
