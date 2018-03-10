// CCsfplayerDlg.h : header file
//

#if !defined(AFX_CCSFPLAYERDLG_H__EF5611F6_9C6F_4DE6_9794_C5D41D6703A2__INCLUDED_)
#define AFX_CCSFPLAYERDLG_H__EF5611F6_9C6F_4DE6_9794_C5D41D6703A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CCamStreamFile.h"

/////////////////////////////////////////////////////////////////////////////
// CCsfplayerDlg dialog

class CCsfplayerDlg : public CDialog
{
// Construction
public:
	CCsfplayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCsfplayerDlg)
	enum { IDD = IDD_CSFPLAYER_DIALOG };
	CStatic	m_FrameRate;
	CStatic	m_Frame;
	CStatic	m_Img;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCsfplayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CCamStreamFile m_Csf;
	unsigned char* m_pBmpData;
	unsigned short* m_pData;
	unsigned short* m_pFirstData;
	unsigned long pretime;
	unsigned long posttime;
	unsigned long last;
	CBitmap bmp;
	CDC bdc;
	int frame;
	int fn;
	

	int state;
	enum {
		STATE_NOFILE = 0,
		STATE_STOPPED = 1,
		STATE_PLAYING = 2
	};
	// Generated message map functions
	//{{AFX_MSG(CCsfplayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnFileQuit();
	afx_msg void OnPlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CCSFPLAYERDLG_H__EF5611F6_9C6F_4DE6_9794_C5D41D6703A2__INCLUDED_)
