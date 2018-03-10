//------------------------------------------------------------------------------
//
//  APPLICATION:    PC2-Vision Parallel I/O Port
//
//  FILE:           IFC_PC2V_Parallel_IODlg.h
//
//  BIRTH DATE:     August 2003
//
//  LANGUAGE:       C++
//
//  LIBRARIES:      -MFC (Visual C++ V6.0)
//                  -IFC V5.6 (SP3)
//
//  OS:             Windows XP (Win32)
//
//  PLATFORM:       IA-32 CPU (Pentium)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2V_PARALLEL_IODLG_H__F75EE955_2C62_4D4F_A45E_C8D12E5E6068__INCLUDED_)
#define AFX_IFC_PC2V_PARALLEL_IODLG_H__F75EE955_2C62_4D4F_A45E_C8D12E5E6068__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//------------------------------
//          Constants
//------------------------------

#define     APP_BASIC_TITLE     _T("Parallel IO")

#define     TIMER_GUI           10

#define     BIT_NUMBER          8




class CIFC_PC2V_Parallel_IODlg : public CDialog
{

public:

	CIFC_PC2V_Parallel_IODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIFC_PC2V_Parallel_IODlg)
	enum { IDD = IDD_IFC_PC2V_PARALLEL_IO_DIALOG };
	CButton	m_CheckOutHighZ;
	CButton	m_RadioInRising;
	CButton	m_RadioOutLow;
	CEdit	m_EditInValue;
	CEdit	m_EditOutValue;
	CButton	m_RadioIntRising;
	CButton	m_RadioInFalling;
	CEdit	m_EditInterruptCount;
	CButton	m_CheckOutStrobed;
	CButton	m_CheckInStrobed;
	CStatic	m_StaticInBit4;
	CStatic	m_StaticInBit3;
	CStatic	m_StaticInBit5;
	CStatic	m_StaticInBit2;
	CStatic	m_StaticInBit6;
	CStatic	m_StaticInBit1;
	CStatic	m_StaticInBit7;
	CStatic	m_StaticInBit0;
	CStatic	m_StaticOutBit4;
	CStatic	m_StaticOutBit3;
	CStatic	m_StaticOutBit5;
	CStatic	m_StaticOutBit2;
	CStatic	m_StaticOutBit6;
	CStatic	m_StaticOutBit1;
	CStatic	m_StaticOutBit7;
	CStatic	m_StaticOutBit0;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_Parallel_IODlg)
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

    BOOL GetWindowPosition(HWND hWnd, LPRECT lpRect);

    void DrawIObits(void);
    void DrawOutputBitHigh(DWORD dwBitIndex);
    void DrawOutputBitLow(DWORD dwBitIndex);

    void DrawInputBitHigh(DWORD dwBitIndex);
    void DrawInputBitLow(DWORD dwBitIndex);

    BOOL ReadInputPortBit(DWORD dwBitIndex, DWORD dwBitValue);
    void SetOutputPortBit(DWORD dwBitIndex, DWORD dwBitValue);
    void SetOutputPortByte(char cByteValue);

    static void MyInterruptCallback_INP(void *pContext);

    // Generated message map functions
	//{{AFX_MSG(CIFC_PC2V_Parallel_IODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnCheckInputStrobe();
	afx_msg void OnCheckOutputStrobe();
	afx_msg void OnButtonTrap();
	afx_msg void OnRadioInterruptFallingEdge();
	afx_msg void OnRadioInterruptRisingEdge();
	afx_msg void OnRadioInputStrobeFalling();
	afx_msg void OnRadioInputStrobeRising();
    afx_msg void OnRadioOutputStrobeMode(UINT RadioID);
	afx_msg void OnButtonReadInput();
	afx_msg void OnButtonSetOutput();
	afx_msg void OnCheckOutputHiz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

    CICapMod        *m_pBrdMod;             // Ptr 2 PCVision2 board capture module
    PCIntrCallback  m_pIntCallback_INP;

    BOOL    m_bInterruptRisingEdge;
    DWORD   m_dwInterruptCounter;

    BOOL    m_bInputStrobed;
    BOOL    m_bInStrobeFallingEdge;

    BOOL    m_bOutputStrobed;
    BOOL    m_bOutputHiZ;
    BOOL    m_bOutStrobeLow;

    HWND    m_ahOutBitLight[BIT_NUMBER];
    HWND    m_ahInBitLight[BIT_NUMBER];

    unsigned char   m_ucInputPort;
    unsigned char   m_ucOutputPort;

    BOOL    m_bAppClosing;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_PARALLEL_IODLG_H__F75EE955_2C62_4D4F_A45E_C8D12E5E6068__INCLUDED_)
