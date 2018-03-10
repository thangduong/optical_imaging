#if !defined(AFX_VNEXPLORER_H__5CAFCFC5_A1D1_4C9C_8914_35BDB4C12E2A__INCLUDED_)
#define AFX_VNEXPLORER_H__5CAFCFC5_A1D1_4C9C_8914_35BDB4C12E2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVnExplorer wrapper class

class CVnExplorer : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVnExplorer)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xb235836, 0x5a83, 0x11d5, { 0xa4, 0x69, 0x0, 0x50, 0x4, 0x5, 0x1d, 0x9b } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	BOOL GetBorderProp();
	void SetBorderProp(BOOL);
	BOOL GetHasLinesProp();
	void SetHasLinesProp(BOOL);
	BOOL GetHasButtonsProp();
	void SetHasButtonsProp(BOOL);
	BOOL GetRootLinesProp();
	void SetRootLinesProp(BOOL);
	BOOL GetEditLabelProp();
	void SetEditLabelProp(BOOL);
	BOOL GetDisDragDropProp();
	void SetDisDragDropProp(BOOL);
	BOOL GetShowSelAlways();
	void SetShowSelAlways(BOOL);
	BOOL GetCheckBoxes();
	void SetCheckBoxes(BOOL);
	BOOL GetFullRowSel();
	void SetFullRowSel(BOOL);
	BOOL GetInfoTip();
	void SetInfoTip(BOOL);
	BOOL GetScroll();
	void SetScroll(BOOL);
	BOOL GetToolTips();
	void SetToolTips(BOOL);
	BOOL GetSingleExpand();
	void SetSingleExpand(BOOL);
	BOOL GetNonEvenHeight();
	void SetNonEvenHeight(BOOL);
	BOOL GetTrackSelect();
	void SetTrackSelect(BOOL);
	BOOL GetClientEdge();
	void SetClientEdge(BOOL);
	BOOL GetStaticEdge();
	void SetStaticEdge(BOOL);
	BOOL GetModalFrame();
	void SetModalFrame(BOOL);
	BOOL GetTransparent();
	void SetTransparent(BOOL);
	BOOL GetAcceptFiles();
	void SetAcceptFiles(BOOL);
	BOOL GetRightAlignedText();
	void SetRightAlignedText(BOOL);
	BOOL GetRightToLeft();
	void SetRightToLeft(BOOL);
	BOOL GetLeftScrollBar();
	void SetLeftScrollBar(BOOL);

// Operations
public:
	long GetCount();
	long GetIndent();
	void SetIndent(long nIndent);
	long GetNextItem(long hTreeItem, long nCode);
	BOOL ItemHasChildren(long hItem);
	long GetChildItem(long hItem);
	long GetNextSiblingItem(long hItem);
	long GetPrevSiblingItem(long hItem);
	long GetParentItem(long hItem);
	long GetFirstVisibleItem();
	long GetNextVisibleItem(long hItem);
	long GetPrevVisibleItem(long hItem);
	long GetSelectedItem();
	long GetDropHilightItem();
	long GetRootItem();
	long GetItemState(long hItem, long nStateMask);
	BOOL SetItemState(long hItem, long nState, long nStateMask);
	long GetVisibleCount();
	long GetBkColor();
	long SetBkColor(long color);
	short GetItemHeight();
	short SetItemHeight(short cyHeight);
	long GetTextColor();
	long SetTextColor(long color);
	BOOL Expand(long hItem, long nCode);
	BOOL Select(long hItem, long nCode);
	BOOL SelectItem(long hItem);
	long HitTest(short x, short y, long pFlags);
	BOOL SortChildren(long hItem);
	BOOL EnsureVisible(long hItem);
	BOOL SelectDropTarget(long hItem);
	BOOL SelectSetFirstVisible(long hItem);
	BOOL SetCheck(long hItem, short bCheck);
	BOOL GetCheck(long hItem);
	short Explore(long lpVSConfig);
	void VideoSourceAttached(long hItem);
	void VideoSourceDetached(long hItem);
	CString GetItemText(long hItem);
	CString GetDomainName(long hItem);
	CString GetFullModuleName(long hItem);
	CString GetConfigFileName(long hItem);
	CString GetNodeName(long hItem);
	void BeginDrag(long lParam, short bTrackMove);
	short EndDrag();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VNEXPLORER_H__5CAFCFC5_A1D1_4C9C_8914_35BDB4C12E2A__INCLUDED_)