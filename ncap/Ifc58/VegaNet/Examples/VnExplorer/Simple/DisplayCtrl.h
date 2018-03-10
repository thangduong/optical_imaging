#if !defined(AFX_DISPLAYCTRL_H__C91562DB_6192_44F1_9D6B_6A53DAD8868D__INCLUDED_)
#define AFX_DISPLAYCTRL_H__C91562DB_6192_44F1_9D6B_6A53DAD8868D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayCtrl.h : header file
//

#include <VnVidSrc.h> 
#include <VnImgCon.h>

/////////////////////////////////////////////////////////////////////////////
// CDisplayCtrl view

class CDisplayCtrl : public CScrollView
{
public:
	CDisplayCtrl();
	virtual ~CDisplayCtrl();

	BOOL CreateFromStatic(UINT nID, CWnd* pParent);

protected:
	DECLARE_DYNCREATE(CDisplayCtrl)

// Attributes
public:

// Operations
public:
	void SetVideoSource(IVideoSrc* pIVideoSource, BOOL bIsLocal);
	void ClearView();
	void CreateDisplay();
	void DeleteDisplay(BOOL bClose=FALSE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayCtrl)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDisplayCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// overrides to bypass MFC doc/view frame dependencies
	afx_msg void OnDestroy();
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bLocalVideoSource;
	IVideoSrc*		m_pIVideoSource;
	IImgDisplay*	m_pIImageDisplay;
	PIVideoStream	m_pIVideoStream;

	DWORD m_dwStyle;
	DWORD m_dwExStyle;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYCTRL_H__C91562DB_6192_44F1_9D6B_6A53DAD8868D__INCLUDED_)
