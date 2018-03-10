// ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ModuleDlg.h"
#include <lm.h>

#include <VnBase.h>
#include "UserName.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg dialog


DWORD EnumNodes(char *nodeNames)
{
   LPSERVER_INFO_101 pBuf = NULL;
   LPSERVER_INFO_101 pTmpBuf;
   DWORD dwLevel = 101;
   DWORD dwPrefMaxLen = -1;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwTotalCount = 0;
   DWORD dwServerType = SV_TYPE_ALL; // all servers
   DWORD dwResumeHandle = 0;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;
   DWORD i;

   //
   // Call the NetServerEnum function to retrieve information
   //  for all servers, specifying information level 101.
   //
	*nodeNames=0;

	nStatus = NetServerEnum(NULL,
                           dwLevel,
                           (LPBYTE *) &pBuf,
                           dwPrefMaxLen,
                           &dwEntriesRead,
                           &dwTotalEntries,
                           dwServerType,
                           NULL,
                           &dwResumeHandle);
	if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
		if ((pTmpBuf = pBuf) != NULL) {
			for (i = 0; i < dwEntriesRead; i++) {
				if (pTmpBuf == NULL) {
					fprintf(stderr, "An access violation has occurred\n");
					break;
				}

				nodeNames += sprintf(nodeNames,"%S", pTmpBuf->sv101_name) + 1;

				pTmpBuf++;
				dwTotalCount++;
			}
			*nodeNames=0;
		 // Display a warning if all available entries were
		 //  not enumerated, print the number actually 
		 //  enumerated, and the total number available.

			if (nStatus == ERROR_MORE_DATA) {
				fprintf(stderr, "\nMore entries available!!!\n");
				fprintf(stderr, "Total entries: %d", dwTotalEntries);
			}

		}
	}
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);

	if (pBuf != NULL)
		NetApiBufferFree(pBuf);

	return 0;
}



CModuleDlg::CModuleDlg(IVidSrcCfg *vidSrcCfg)
	: CDialog(CModuleDlg::IDD, NULL)
{
	//{{AFX_DATA_INIT(CModuleDlg)
	m_strConfigFileName = _T("");
	m_NodeName = _T("");
	m_DnsNodeName = _T("");
	//}}AFX_DATA_INIT

	m_vidSrcCfg = vidSrcCfg;
	DWORD nameSize=MAX_PATH;
	GetComputerName(m_thisNodeName,&nameSize);

}


void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModuleDlg)
	DDX_Control(pDX, IDC_NODE_LIST, m_ctrlNodeList);
	DDX_Control(pDX, IDC_MODULE_LIST, m_ctrlModuleList);
	DDX_Control(pDX, IDC_SELECT_CONFIG_FILE, m_buttonSelConfigFile);
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Text(pDX, IDC_CONFIG_FILENAME, m_strConfigFileName);
	DDX_LBString(pDX, IDC_NODE_LIST, m_NodeName);
	DDX_Text(pDX, IDC_DNS_NODE, m_DnsNodeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModuleDlg, CDialog)
	//{{AFX_MSG_MAP(CModuleDlg)
	ON_LBN_SELCHANGE(IDC_MODULE_LIST, OnSelchangeModuleList)
	ON_BN_CLICKED(IDC_SELECT_CONFIG_FILE, OnSelectConfigFile)
	ON_LBN_SELCHANGE(IDC_NODE_LIST, OnSelChangeNodeList)
	ON_BN_CLICKED(IDC_ENTER_NODE, OnEnterNode)
	ON_BN_CLICKED(IDC_SET_USER, OnSetUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModuleDlg message handlers

void CModuleDlg::UpdateVideoSrcList()
{
	DWORD wNumMods;
	VSPROPS props;
    HRESULT hr=S_OK;
	m_ctrlModuleList.ResetContent();
	
	hr = m_vidSrcCfg->AddDetectedVideoSrcs(m_curNode,"VnIfcDrv.dll",0);
	if (hr==S_OK)
		hr = m_vidSrcCfg->GetEnumVideoSrc(m_curNode,0,&props);
	switch (hr) {
	case S_OK:
		break;
	case E_ACCESSDENIED:
	case HRESULT_FROM_WIN32(RPC_S_SERVER_UNAVAILABLE):
		CUserName dlg(this,m_curNode);
		
		if (dlg.DoModal() == IDOK) {
			VSAUTHIDENTITY user;
			user.Domain	= dlg.m_Domain;
			user.Password = dlg.m_password;
			user.User = dlg.m_UserName;
			m_vidSrcCfg->SetUser(m_curNode,&user);
			hr = m_vidSrcCfg->GetEnumVideoSrc(m_curNode,0,&props);
		}
		break;
	}
	
	
	if (hr==S_OK) {
		for (wNumMods=0; wNumMods < CFG_MAX_NUM_MODS; wNumMods++) {
			if (m_vidSrcCfg->GetEnumVideoSrc(m_curNode,wNumMods,&props) != S_OK)
				break;
			m_ctrlModuleList.AddString(props.installedName);
		}
	}
}


BOOL CModuleDlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	
	char nodeNames[8000];

	strcpy(m_curNode,m_NodeName.GetBuffer(80));
	m_NodeName.ReleaseBuffer();
	EnumNodes(nodeNames);
	if (nodeNames[0]) {
		for (i=0;nodeNames[i];i+=strlen(nodeNames+i)+1) {
			m_ctrlNodeList.AddString(nodeNames+i);
		}
	}
	else {
		m_ctrlNodeList.AddString(m_thisNodeName);
	}

	int nodeIndex = m_ctrlNodeList.FindStringExact(-1,m_thisNodeName);
	if (nodeIndex == LB_ERR) {
		m_ctrlNodeList.AddString(m_thisNodeName);
		nodeIndex = m_ctrlNodeList.FindStringExact(-1,m_thisNodeName);
	}

	// ... and set the currently selected item to match the current camera
	if (nodeIndex != LB_ERR)
		m_ctrlNodeList.SetCurSel(nodeIndex);	
	else
		m_ctrlNodeList.SetCurSel(0);	

	m_ctrlNodeList.GetText(m_ctrlNodeList.GetCurSel(), m_curNode);

	UpdateVideoSrcList();

	
	// m_buttonSelConfigFile.EnableWindow(FALSE);
	m_buttonOK.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CModuleDlg::OnSelchangeModuleList() 
{
	m_buttonOK.EnableWindow();
	m_ctrlModuleList.GetText(m_ctrlModuleList.GetCurSel(), m_fullModName);
	VnGetVidSrcNameCmpts(m_fullModName, NULL, m_strModName, &m_modSeqNum);
}


void CModuleDlg::OnOK() 
{
	VSPARAM parm;
	UpdateData(TRUE);
	m_ctrlModuleList.GetText(m_ctrlModuleList.GetCurSel(), m_fullModName);

	char *szConfigFileName;

	if (m_strConfigFileName.IsEmpty()) {
		szConfigFileName = NULL;
	}
	else {
		szConfigFileName = (char *) ((LPCTSTR) m_strConfigFileName);
	}

	parm.parmName = VS_CONFIG_FILE_PARM_NAME;
	parm.parmVal = szConfigFileName;


	m_VideoSrcIsLocal = strcmpi(m_curNode,m_thisNodeName) == 0;

	m_vidSrcCfg->SyncSysTime(m_curNode);

	if (m_vidSrcCfg->CreateVideoSrc(m_curNode, m_fullModName, 1,&parm,&m_pICap) != S_OK) {
		::MessageBox(NULL,"Unable to open selected image capture module.",
		"No Module",MB_OK);
		m_pICap = NULL;
	}
	else {
		EndDialog(IDOK);
	}
}


void CModuleDlg::OnSelectConfigFile() 
{
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);

	CFileDialog dlg(TRUE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					"Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDOK) {
		m_strConfigFileName	= dlg.GetPathName();
	}

	UpdateData(FALSE);
}


IVideoSrc *CModuleDlg::GetModule()
{
	return m_pICap;
}



void CModuleDlg::OnSelChangeNodeList() 
{
	m_ctrlNodeList.GetText(m_ctrlNodeList.GetCurSel(), m_curNode);
	UpdateVideoSrcList();	
}

void CModuleDlg::OnEnterNode() 
{
	UpdateData(TRUE);
	strcpy(m_curNode,m_DnsNodeName.GetBuffer(80));
	m_DnsNodeName.ReleaseBuffer();
	UpdateVideoSrcList();	
	
}

void CModuleDlg::OnSetUser() 
{
	CUserName dlg(this,m_curNode);
	
	if (dlg.DoModal() == IDOK) {
		VSAUTHIDENTITY user;
		user.Domain	= dlg.m_Domain;
		user.Password = dlg.m_password;
		user.User = dlg.m_UserName;
		m_vidSrcCfg->SetUser(m_curNode,&user);
	}
	
}
