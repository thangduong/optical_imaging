// CameraMgrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "CameraMgrDlg.h"
#include <afxdlgs.h>
#include <Dlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraMgrDlg dialog

/*
If you derive a new class from CFileDialog, you can use a message map to handle
any messages. To extend the default message handling, derive a class from CWnd,
add a message map to the new class, and provide member functions for the new
messages. You do not need to provide a hook function to customize the dialog box.
*/

IMPLEMENT_DYNAMIC(CCameraMgrDlg, CFileDialog)


CCameraMgrDlg::CCameraMgrDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd,BOOL UserCfg) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

	m_ofn.Flags |= OFN_ENABLETEMPLATE | OFN_EXPLORER | OFN_ALLOWMULTISELECT
							 | OFN_ENABLEHOOK;

	m_ofn.hInstance = AfxGetResourceHandle();
	m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_MANAGE_CAMERAS);
	m_ofn.lpstrTitle = "Extract Cameras From Configuration Files";

	//{{AFX_DATA_INIT(CCameraMgrDlg)
	m_bRecursive = FALSE;
	m_bAllFiles = FALSE;
	m_bFilesAsLists = FALSE;

	//}}AFX_DATA_INIT
	m_Canceled = FALSE;
	m_UserCfg = UserCfg;

}

void CCameraMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CFileDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraMgrDlg)
	DDX_Control(pDX, IDC_RECURSIVE, m_buttonRecursive);
	DDX_Control(pDX, IDC_FILES_AS_LISTS, m_buttonFilesAsLists);
	DDX_Control(pDX, IDC_ALL_FILES, m_buttonAllFiles);
	DDX_Check(pDX, IDC_RECURSIVE, m_bRecursive);
	DDX_Check(pDX, IDC_ALL_FILES, m_bAllFiles);
	DDX_Check(pDX, IDC_FILES_AS_LISTS, m_bFilesAsLists);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraMgrDlg, CFileDialog)
	//{{AFX_MSG_MAP(CCameraMgrDlg)
	ON_BN_CLICKED(IDC_RECURSIVE, OnRecursive)
	ON_BN_CLICKED(IDC_ALL_FILES, OnAllFiles)
	ON_BN_CLICKED(IDC_FILES_AS_LISTS, OnFilesAsLists)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraMgrDlg message handlers

BOOL CCameraMgrDlg::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	if (m_UserCfg) {
		m_buttonRecursive.EnableWindow(FALSE);
		m_buttonAllFiles.EnableWindow(FALSE);	
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCameraMgrDlg::OnRecursive() 
{
	UpdateData();

	if (m_bRecursive)
	{
		// If the user is selecting all files recursively then we select
		// the "All Files" and deselect the "Files as Lists" checkboxes.
		// When "Files as Lists" is selected the user of this dialog
		// treats the contents of the selected file as a list of other
		// files. We only support one file for that mode.
		m_bAllFiles = TRUE;
		m_bFilesAsLists = FALSE;
	}
	else
	{
		// If the user is deselecting recursive then we deselect the 
		// "All Files" checkbox. The "Files as Lists" checkbox is
		// already disabled.
		m_bAllFiles = FALSE;
	}

	SelectAll(m_bAllFiles);
	UpdateData(FALSE);
}

void CCameraMgrDlg::OnAllFiles() 
{
	UpdateData();

	if (m_bAllFiles)
	{
		// If the user is selecting all files then we deselect
		// "Files as Lists" checkbox. When "Files as Lists" is
		// selected the user of this dialog treats the contents
		// of the selected file as a list of other files. We
		// only support one file for that mode.
		m_bFilesAsLists = FALSE;
	}
	else
	{
		// If the user is deselecting the "All Files" option then we 
		// deselect the "Recursive" checkbox. The "Files as Lists"
		// checkbox is already disabled.
		m_bRecursive = FALSE;
	}

	SelectAll(m_bAllFiles);
	UpdateData(FALSE);
}


void CCameraMgrDlg::OnFilesAsLists() 
{
	UpdateData();

	if (m_bFilesAsLists)
	{
		m_bRecursive = m_bAllFiles = FALSE;
		SelectAll(FALSE);
		UpdateData(FALSE);
	}
}

void CCameraMgrDlg::SelectAll(BOOL bState)
{
	CWnd* pWnd;

	pWnd = GetParent()->GetDlgItem(lst2);

	if (pWnd == NULL)
	  return;

	CListCtrl* wndLst1 = (CListCtrl*)(pWnd->GetDlgItem(1));

	int i = wndLst1->GetItemCount();
	UINT nState = LVIS_SELECTED | LVIS_DROPHILITED;

	CString strPath;

	CString strFullName;
	CFileFind fileFinder;

	while (i--)
	{
		if (bState)
		{
			// Selecting so don't select dirs unless recursive.

			if (m_bRecursive)
			{
				wndLst1->SetItemState(i, nState, nState);
			}
			else
			{
				strFullName = m_strCurPath + "\\" + wndLst1->GetItemText(i, 0);

				if (fileFinder.FindFile(strFullName))
				{
					fileFinder.FindNextFile();

					if (!fileFinder.IsDirectory() || m_bRecursive)
					{
						wndLst1->SetItemState(i, nState, nState);
					}
				}
			}
		}
		else
		{
			// Deselecting so deselect all.
			wndLst1->SetItemState(i, 0, nState);
		}

		wndLst1->Update(i);
	}
}

CString CCameraMgrDlg::GetPath(CString &strPath)
{
	strPath = m_strCurPath;
	return strPath;
}

void CCameraMgrDlg::OnFolderChange()
{
	m_strCurPath = GetFolderPath();
}


void CCameraMgrDlg::OnCancel( )
{
	m_Canceled = TRUE;
	CFileDialog::OnCancel();


}
