#if !defined(AFX_BLOBDLG_H__67C7A1E3_4620_11D4_B109_00105A0F576C__INCLUDED_)
#define AFX_BLOBDLG_H__67C7A1E3_4620_11D4_B109_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlobAnlz.h : header file
//

class CBlobViewView;

/////////////////////////////////////////////////////////////////////////////
// BlobAnlz dialog

class BlobAnlz : public CDialog
{
// Construction
public:
	BlobAnlz(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BlobAnlz)
	enum { IDD = IDD_BLOB_ANAL };
	CEdit	m_ctlNumBlobs;
	CEdit	m_ctlAvgBlobArea;
	DWORD	m_AvgBlobArea;
	DWORD	m_MaxBlobArea;
	DWORD	m_minBlobArea;
	DWORD	m_NumBlobs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BlobAnlz)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	DWORD m_nTimer;
	CBlobViewView *m_parent;
protected:

	// Generated message map functions
	//{{AFX_MSG(BlobAnlz)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSetBlobParams();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBANLZ_H__67C7A1E3_4620_11D4_B109_00105A0F576C__INCLUDED_)
