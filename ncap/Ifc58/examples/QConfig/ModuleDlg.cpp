// ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "ModuleDlg.h"

#include <ifc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog


CModuleDlg::CModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModuleDlg)
	m_strConfigFileName = _T("");
	m_VmodSeqNum = 0;
	m_SelVModName = _T("");
	//}}AFX_DATA_INIT
}


void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModuleDlg)
	DDX_Control(pDX, IDC_VMODULE_LIST, m_ctrlVModuleList);
	DDX_Control(pDX, IDC_MODULE_LIST, m_ctrlModuleList);
	DDX_Control(pDX, IDC_SELECT_CONFIG_FILE, m_buttonSelConfigFile);
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Text(pDX, IDC_CONFIG_FILENAME, m_strConfigFileName);
	DDX_Text(pDX, IDC_VMOD_SEQNUM, m_VmodSeqNum);
	DDV_MinMaxUInt(pDX, m_VmodSeqNum, 0, 7);
	DDX_LBString(pDX, IDC_VMODULE_LIST, m_SelVModName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CModuleDlg)
	ON_LBN_SELCHANGE(IDC_MODULE_LIST, OnSelchangeModuleList)
	ON_BN_CLICKED(IDC_SELECT_CONFIG_FILE, OnSelectConfigFile)
	ON_BN_CLICKED(IDOPENVMOD, OnOpenVmod)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg message handlers

BOOL CModuleDlg::OnInitDialog() 
{
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	CITIMods topo;
	int i;
	CDialog::OnInitDialog();
	HICAPENUM modNode;
	
	ITI_PARENT_MOD *pICap;
	WORD wNumMods = 0;
	char VModName[40];


	for (wNumMods=0, pICap=topo.GetFirst(); pICap  ; pICap=topo.GetNext() )
	{
		char modName[80];
		for (i=0; i < CFG_MAX_NUM_MODS;i++) {
			if (!strcmp(pICap->fullName,thisApp->m_ModNames[i]) && thisApp->m_ModSeqNum[i] == (int)pICap->seqNum)
				break;
		}
		if (i == CFG_MAX_NUM_MODS) {
			sprintf(modName,"%s  %01d",pICap->fullName,pICap->seqNum);
			m_ctrlModuleList.AddString(modName);
			wNumMods++;
		}
	}

	for (modNode=IfxGetFirstCaptureModName(VModName); modNode  ; modNode=IfxGetNextCaptureModName(modNode,VModName )) {
		m_ctrlVModuleList.AddString(VModName);
	}
	
	// m_buttonSelConfigFile.EnableWindow(FALSE);
	m_buttonOK.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModuleDlg::OnSelchangeModuleList() 
{
	m_buttonOK.EnableWindow();
	char fullModName[80];
	m_ctrlModuleList.GetText(m_ctrlModuleList.GetCurSel(), fullModName);
	sscanf(fullModName,"%s  %01d",m_strModName,&m_modSeqNum);
}

void CModuleDlg::OnOK() 
{
	UpdateData(TRUE);
//	m_ctrlModuleList.GetText(m_ctrlModuleList.GetCurSel(), m_strModName);

	char *szConfigFileName;

	if (m_strConfigFileName.IsEmpty())
	{
		szConfigFileName = NULL;
	}
	else
	{
		szConfigFileName = (char *) ((LPCTSTR) m_strConfigFileName);
	}

	if ((m_pICap = IfxCreateCaptureModule( m_strModName, m_modSeqNum,
										  szConfigFileName))
										  == NULL)
	{
		::MessageBox(NULL,"Unable to open selected image capture module.",
		"No Module",MB_OK);
	}
	else
	{
		EndDialog(IDOK);
	}
	if (!szConfigFileName && m_pICap) {
		m_pICap->ProcessCameraFilesInDir("camdb",TRUE);
	}
}

void CModuleDlg::OnSelectConfigFile() 
{
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);

	CFileDialog dlg(TRUE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					"Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDOK)
	{
		m_strConfigFileName	= dlg.GetPathName();
	}

	UpdateData(FALSE);
}


PCICapMod CModuleDlg::GetModule()
{
	return m_pICap;
}

void CModuleDlg::OnOpenVmod() 
{
	UpdateData(TRUE);

	char *szConfigFileName;
	char DModNames[40]={0,};

	if (m_strConfigFileName.IsEmpty())
		szConfigFileName = NULL;
	else
		szConfigFileName = (char *) ((LPCTSTR) m_strConfigFileName);
	if (m_SelVModName == "ICP" || m_SelVModName == "PCVision")
		strcpy(DModNames,"AM-V");

	if ((m_pICap = (PCICapMod)IfxCreateVirtualParentModule( (char *) ((LPCTSTR)m_SelVModName), m_VmodSeqNum,
										  szConfigFileName,DModNames))
										  == NULL)
	{
		::MessageBox(NULL,"Unable to open selected virtual image capture module.",
		"No Module",MB_OK);
	}
	else
	{
		EndDialog(IDOK);
	}
	if (!szConfigFileName && m_pICap) {
		m_pICap->ProcessCameraFilesInDir("camdb",TRUE);
	}
	
}
