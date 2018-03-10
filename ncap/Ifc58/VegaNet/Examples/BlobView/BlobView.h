// BlobView.h : main header file for the BLOBVIEW application
//

#if !defined(AFX_BLOBVIEW_H__AD5EF087_01EC_11D5_B181_00105A0F576C__INCLUDED_)
#define AFX_BLOBVIEW_H__AD5EF087_01EC_11D5_B181_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <VnVidSrc.h> 

/////////////////////////////////////////////////////////////////////////////
// CBlobViewApp:
// See BlobView.cpp for the implementation of this class
//

class CBlobViewApp : public CWinApp
{
public:
	CBlobViewApp();
	~CBlobViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlobViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	IVidSrcCfg *m_vidSrcCfg;
	//{{AFX_MSG(CBlobViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBVIEW_H__AD5EF087_01EC_11D5_B181_00105A0F576C__INCLUDED_)
