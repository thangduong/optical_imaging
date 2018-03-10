// Record.h : main header file for the RECORD application
//

#if !defined(AFX_RECORD_H__DD858F17_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
#define AFX_RECORD_H__DD858F17_962D_11D5_B1ED_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <VnBase.h>
#include <VnVidSrc.h> 
#include <VnImgCon.h> 
typedef interface IImageDIff IImageDIff;

/////////////////////////////////////////////////////////////////////////////
// CRecordApp:
// See Record.cpp for the implementation of this class
//

class CRecordApp : public CWinApp
{
public:
	CRecordApp();
	~CRecordApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	IVidSrcCfg *m_vidSrcCfg;
	BOOL m_VideoSrcIsLocal;
	IVideoSrc *m_pICap;
	char m_vidSrcNodeName[80];

	char m_vnmFileName[120];

	PIProcNode m_splitNode;
	HNODESPLITTER m_hImgSplit;
	IFileNode *m_FileNode;
	BOOL m_RecordDeltaOnly;

	PIProcNode m_ImgProc;		// Image processing node
	HPROCESSTHREAD m_hSrvThread; // Handle to a thread inside the image process node
	IImageDIff *m_MyProcessObj;


	//{{AFX_MSG(CRecordApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORD_H__DD858F17_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
