// SimpleDlg.h : header file
//
//{{AFX_INCLUDES()
#include "VnExplorer.h"
//}}AFX_INCLUDES

#if !defined(AFX_SIMPLEDLG_H__A1E8D220_0522_4868_897D_F13EEE78DEAF__INCLUDED_)
#define AFX_SIMPLEDLG_H__A1E8D220_0522_4868_897D_F13EEE78DEAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DisplayCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleDlg dialog

class CSimpleDlg : public CDialog
{
// Construction
public:
	CSimpleDlg(CWnd* pParent = NULL);	// standard constructor
	~CSimpleDlg();

// Dialog Data
	//{{AFX_DATA(CSimpleDlg)
	enum { IDD = IDD_SIMPLE_DIALOG };
	CButton	m_DragTraceButton;
	CStatic	m_yStatic;
	CStatic	m_xStatic;
	CStatic	m_OldItemStatic;
	CStatic	m_LocalStatic;
	CStatic	m_ModName;
	CVnExplorer	m_VnExplorerCtrl;
	CString	m_CurrentEvent;
	CString	m_ItemText;
	CString	m_xValue;
	CString	m_yValue;
	CString	m_FlagText;
	CString	m_OldItemText;
	BOOL	m_bDrag;
	BOOL	m_bDragTrace;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimpleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnAttachVideoSource(long hItem, short bIsLocal);
	afx_msg void OnDetachVideoSource(long hItem, short bIsLocal);
	afx_msg void OnItemExpanded(long hItem, long nAction);
	afx_msg void OnSelectChanged(long hItemNew, long hItemOld, long nAction);
	afx_msg void OnLeftClicked(long x, long y);
	afx_msg void OnRightClicked(long x, long y);
	afx_msg void OnBeginDrag(short nDrag, long hItem, long x, long y, long lParam);
	afx_msg void OnDragMove(short nDrag, long x, long y);
	afx_msg void OnEndDrag(short nDrag, long x, long y);
	afx_msg void OnDragEnable();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	long m_hAttachedVideoSource;
	void InitValues();
	CString FlagToText(UINT uFlags);
	IVidSrcCfg* m_VidSrcCfg;
	CDisplayCtrl m_DisplayCtrl;
	BOOL RegisterCtrl(LPTSTR strCtrlName);
	BOOL IsCtrlRegistered(CLSID clsid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEDLG_H__A1E8D220_0522_4868_897D_F13EEE78DEAF__INCLUDED_)
