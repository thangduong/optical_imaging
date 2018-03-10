// CImgviewerDlg.h : header file
//

#if !defined(AFX_CIMGVIEWERDLG_H__CF8CC0F3_FD76_483D_B29E_15A1ADFD34A2__INCLUDED_)
#define AFX_CIMGVIEWERDLG_H__CF8CC0F3_FD76_483D_B29E_15A1ADFD34A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImgviewerDlg dialog

class CImgviewerDlg : public CDialog
{
protected:
	HBITMAP m_hBackImg;
	char* m_pBackImgData;
	BITMAPINFO bmi;
// Construction
public:
	const char* initialFilename;
	CImgviewerDlg(CWnd* pParent = NULL);	// standard constructor
	void Show(short* pData);
	void OpenFile(const char* filename);

// Dialog Data
	//{{AFX_DATA(CImgviewerDlg)
	enum { IDD = IDD_IMGVIEWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgviewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImgviewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileQuit();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIMGVIEWERDLG_H__CF8CC0F3_FD76_483D_B29E_15A1ADFD34A2__INCLUDED_)
