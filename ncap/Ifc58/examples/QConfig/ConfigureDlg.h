//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONFIGUREDLG_H__6F4D17E6_CCFD_11D2_B533_00A0C99ACB20__INCLUDED_)
#define AFX_CONFIGUREDLG_H__6F4D17E6_CCFD_11D2_B533_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigureDlg.h : header file
//

#include "ConfiguratorView.h"


typedef struct _CFG_TREE_STATE_NODE CFG_TREE_STATE_NODE;

struct _CFG_TREE_STATE_NODE {
	DWORD state;
	CFG_TREE_STATE_NODE *firstChild;
	CFG_TREE_STATE_NODE *nextSibling;
};


/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg dialog

class CConfigureDlg : public CDialog
{
// Construction
public:
	void DeleteChildrenStates(CFG_TREE_STATE_NODE *parentNode);
	void DeletePGroupStateTree();
	BOOL AddChildrenStates(HTREEITEM hParentItem, CFG_TREE_STATE_NODE *parentNode);
	BOOL SavePGroupTreeState();
	void CloseEdit();
	void LoadParamsList(const CString &CamDefName);
	void LoadCameraList();
	CConfigureDlg(CConfiguratorView* pParent = NULL, PCICapMod pICap = NULL);
	void GridEdit(short FAR* KeyAscii);
	void ChDirToCamDb();
	void NewParamRefresh(double dVal);
	void GenerateParamGroupTree();



// Dialog Data
	//{{AFX_DATA(CConfigureDlg)
	enum { IDD = IDD_CONFIGURE };
	CButton	m_ctlLibrMode;
	CTreeCtrl	m_ParamTree;
	CComboBox	m_cbPortList;
	CButton	m_buttonCopyCam;
	CButton	m_buttonSave;
	CEdit	m_editParamVal;
	CComboBox	m_comboBoxParamVal;
	CListBox	m_listBoxCameras;
	CMSFlexGrid	m_MSFlexGridParams;
	CString	m_strEditParamVal;
	CString	m_strComboParamVal;
	BOOL	m_ShowSubgroups;
	//}}AFX_DATA

	IFC_PARAM_GROUP_TYPE m_rClickGroup;
	CICamera *m_pCamera;
	PCICapMod m_pICap;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void AddParamGroupsToTree(HTREEITEM parentTreeItem, IFC_PARAM_GROUP_TYPE parentGroupID);
	void DoPopupMenu(UINT nMenuID);


	// Generated message map functions
	//{{AFX_MSG(CConfigureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReadCamFiles();
	afx_msg void OnSelchangeCameraList();
	afx_msg void OnLeaveCellMsflexgridParams();
	afx_msg void OnEnterCellMsflexgridParams();
	afx_msg void OnDblClickMsflexgridParams();
	afx_msg void OnKeyPressMsflexgridParams(short FAR* KeyAscii);
	afx_msg void OnScrollMsflexgridParams();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonCopyCamera();
	afx_msg void OnSelchangePortList();
	afx_msg void OnSaveUserCfg();
	afx_msg void OnReadUserCfg();
	afx_msg void OnSelchangedPgrpTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIncSubgroup();
	afx_msg void OnRclickPgrpTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGroupMenuEditDialog();
	afx_msg void OnGroupMenuProperties();
	afx_msg void OnGroupMenuApplicability();
	afx_msg void OnLibrMode();
	afx_msg void OnRuleEditor();
	afx_msg void OnDblclkPgrpTree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CString m_strExistingCamSel;
	IFC_PARAM_CAPS m_curParmCaps;
	ACQ_PARAMS_TYPE m_curParamID;
	WORD m_wCurArrayDim;
	int m_iCurSelParam;
	CConfiguratorView *m_pParent;
	int		m_portNum;
	HTREEITEM  m_ItemSel;

	CFG_TREE_STATE_NODE *m_SavedTreeState;

	// Index of value if parameter supports an array of values. 0 otherwise.
	DWORD m_dwParamValIndex;		

	CString m_strParamBaseName;		// Parameter name without array index specifier.
	BOOL m_bParamsReadOnly;
	int m_iXPixelsPerInch;
	int m_iYPixelsPerInch;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGUREDLG_H__6F4D17E6_CCFD_11D2_B533_00A0C99ACB20__INCLUDED_)
