#if !defined(AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_)
#define AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModuleDlg.h : header file
//

#include "direct.h"
#include <VnVidSrc.h> 
#include "resource.h"


#define CFG_MAX_NUM_MODS 16

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog

class CModuleDlg : public CDialog
{
// Construction
public:
	IVideoSrc *GetModule();
	CModuleDlg(	IVidSrcCfg *vidSrcCfg);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModuleDlg)
	enum { IDD = IDD_SELECTMODULE };
	CListBox	m_ctrlNodeList;
	CListBox	m_ctrlModuleList;
	CButton	m_buttonSelConfigFile;
	CButton	m_buttonOK;
	CString	m_strConfigFileName;
	CString	m_NodeName;
	CString	m_DnsNodeName;
	//}}AFX_DATA

	void UpdateVideoSrcList();

	IVideoSrc *m_pICap;
	char m_curNode[80];
	char m_fullModName[80];
	BOOL m_VideoSrcIsLocal;
    CHAR m_thisNodeName[MAX_PATH];
	IVidSrcCfg *m_vidSrcCfg;



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(CModuleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeModuleList();
	virtual void OnOK();
	afx_msg void OnSelectConfigFile();
	afx_msg void OnSelChangeNodeList();
	afx_msg void OnEnterNode();
	afx_msg void OnSetUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	char m_strModName[80];
	DWORD m_modSeqNum;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODULEDLG_H__2D109687_C82C_11D2_B531_00A0C99ACB20__INCLUDED_)
