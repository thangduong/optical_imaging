// dxtex.h : main header file for the dxtex application
//

#if !defined(AFX_DXTX_H__712C53C7_D63B_11D1_A8B5_00C04FC2DC22__INCLUDED_)
#define AFX_DXTX_H__712C53C7_D63B_11D1_A8B5_00C04FC2DC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#ifndef ReleasePpo
	#define ReleasePpo(ppo) \
		if (*(ppo) != NULL) \
		{ \
			(*(ppo))->Release(); \
			*(ppo) = NULL; \
		} \
		else (VOID)0
#endif

/////////////////////////////////////////////////////////////////////////////
// CdxtexDocManager:
// I override this class to customize DoPromptFileName to allow importing of
// BMPs as well as DDSs into CdxtexDocs.
//
class CdxtexDocManager : public CDocManager
{
public:
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);
};

/////////////////////////////////////////////////////////////////////////////
// CdxtexCommandLineInfo:
// I override this class to handle custom command-line options
//
class CdxtexCommandLineInfo : public CCommandLineInfo
{
public:
	CString m_strFileNameAlpha;
	CString m_strFileNameSave;
	D3DFORMAT m_fmt;
	BOOL m_bAlphaComing;
	BOOL m_bMipMap;

	CdxtexCommandLineInfo::CdxtexCommandLineInfo(VOID);
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);

};

/////////////////////////////////////////////////////////////////////////////
// CdxtexApp:
// See dxtex.cpp for the implementation of this class
//

class CdxtexApp : public CWinApp
{
public:
	CdxtexApp();
	virtual ~CdxtexApp();
	LPDIRECT3D9 Pd3d(VOID) { return m_pd3d; }
	LPDIRECT3DDEVICE9 Pd3ddev(VOID) { return m_pd3ddev; }
    BOOL HandlePossibleLostDevice(VOID);
    VOID DeviceIsLost(VOID) { m_bDeviceLost = TRUE; }
    HRESULT InvalidateDeviceObjects(VOID);
    HRESULT RestoreDeviceObjects(VOID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CdxtexApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CdxtexApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPDIRECT3D9 m_pd3d;
	LPDIRECT3DDEVICE9 m_pd3ddev;
    BOOL m_bDeviceLost;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXTX_H__712C53C7_D63B_11D1_A8B5_00C04FC2DC22__INCLUDED_)
