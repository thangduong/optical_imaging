//{{AFX_INCLUDES()
#include "iticonfig.h"
//}}AFX_INCLUDES
#if !defined(AFX_CONFIG_H__E07D3031_D9AA_11D3_A03D_00A0C959E73E__INCLUDED_)
#define AFX_CONFIG_H__E07D3031_D9AA_11D3_A03D_00A0C959E73E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Config.h : header file
//
#include "seqsnapv.h"

/////////////////////////////////////////////////////////////////////////////
// CConfig dialog

class CConfigOcx : public CDialog
{
// Construction
public:
	CConfigOcx(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigOcx)
	enum { IDD = IDD_CONFIG };
	CITIConfig	m_ITIConfigCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigOcx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSeqsnapView* m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CConfigOcx)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetParamIticonfigctrl1(short paramID, double value, long index);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//void IFCCALL	callback(ACQ_PARAMS_TYPE paramID, double value,DWORD index);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIG_H__E07D3031_D9AA_11D3_A03D_00A0C959E73E__INCLUDED_)
