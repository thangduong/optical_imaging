// RuleEdit.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "RuleEdit.h"
#include "ConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleEdit dialog


CRuleEdit::CRuleEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuleEdit)
	m_conditionParamVal = _T("");
	m_currentCondition = _T("");
	m_currentRule = _T("");
	m_cmdByte0 = 0;
	//}}AFX_DATA_INIT
	m_parent = (CConfigureDlg*)pParent;
	m_pICap = m_parent->m_pICap;
	m_pCamera = m_parent->m_pCamera;

	m_curParamID = m_pCamera->GetFirstParam();
	m_pCamera->GetParamCaps(m_curParamID, &m_curParmCaps);
	m_rule.numConditions = 0;
	m_rule.next = NULL;
	m_rule.ruleStr[0] = 0;
	m_rule.numRuleBytes = 0;

}


void CRuleEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleEdit)
	DDX_Control(pDX, IDC_CMD_BYTE0, m_byt0Ctl);
	DDX_Control(pDX, IDC_COND_VAL, m_paramValList);
	DDX_Control(pDX, IDC_COND_PARAMID, m_paramIdList);
	DDX_Control(pDX, IDC_RULE_LIST, m_ruleList);
	DDX_Control(pDX, IDC_CONDITION_LIST, m_conditionList);
	DDX_CBString(pDX, IDC_COND_VAL, m_conditionParamVal);
	DDX_LBString(pDX, IDC_CONDITION_LIST, m_currentCondition);
	DDX_LBString(pDX, IDC_RULE_LIST, m_currentRule);
	DDX_Text(pDX, IDC_CMD_BYTE0, m_cmdByte0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleEdit, CDialog)
	//{{AFX_MSG_MAP(CRuleEdit)
	ON_BN_CLICKED(IDC_ADD_CONDITION, OnAddCondition)
	ON_BN_CLICKED(IDC_ADD_RULE, OnAddRule)
	ON_CBN_SELENDOK(IDC_COND_PARAMID, OnSelendokCondParamid)
	ON_BN_CLICKED(IDC_CLEAR_CONDS, OnClearConditions)
	ON_BN_CLICKED(IDC_DEL_CONDITION, OnDeleteCondition)
	ON_BN_CLICKED(IDC_DEL_RULE, OnDelRule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleEdit message handlers

void CRuleEdit::OnAddCondition() 
{
	int i;
	char condition[180];
	UpdateData();

	m_curParamID = m_paramIdList.GetItemData(m_paramIdList.GetCurSel());
	m_pCamera->GetParamCaps(m_curParamID, &m_curParmCaps);
	char *paramValStr = m_conditionParamVal.GetBuffer(128);
	sprintf(condition,"%s = %s", m_curParmCaps.paramName,paramValStr);
	if (m_rule.numConditions < IFC_MAX_PARMS_IN_RULE) {
		i = m_conditionList.AddString(condition);
		m_paramIdList.SetItemData(i,m_rule.numConditions);
		m_rule.conditions[m_rule.numConditions].paramID = m_curParamID;
		m_rule.conditions[m_rule.numConditions++].paramVal[0] = m_pCamera->ParamStringToVal(m_curParamID, paramValStr);
	}	
	m_conditionParamVal.ReleaseBuffer();
}


void CRuleEdit::OnAddRule() 
{
	CEdit	*bytCtl;
	CString str((char)' ',80);       
	int i;
	CAM_ATTR attr;
	PIFC_UART_RULE rule;
	if (m_rule.numConditions == 0) {
		if(::MessageBox(NULL,"There are no conditions currently entered, Do you wish to add a rule with no conditions?","Add Unconditional Rule",MB_YESNO) == IDNO)
			return;
	}
	m_pCamera->GetAttr(&attr);
	for (i=0; i < IFC_MAX_RULE_STR_LEN && i < 9; i++) {
		bytCtl = (CEdit*)GetDlgItem(IDC_CMD_BYTE0+i);
		bytCtl->GetWindowText(str);
		if (str == "") break;
		if (i==0)
			bytCtl->SetWindowText("0");
		else
			bytCtl->SetWindowText("");
		m_rule.ruleStr[i] = atoi(str);
	}
	if (i==1 && m_rule.ruleStr[0] == 0)
		m_rule.numRuleBytes = 0;	
	else
		m_rule.numRuleBytes = i;	
	rule = m_pICap->AddRule(attr.camName,&m_rule);
	AddRuleStr(rule);

	m_rule.numConditions = 0;
	m_rule.next = NULL;
	m_rule.ruleStr[0] = 0;
	m_rule.numRuleBytes = 0;
	m_conditionList.ResetContent();

}


void CRuleEdit::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


BOOL SetTestPattern(CICamera*cam,BOOL turnOn)
{
	BYTE turnOffCmd[] = {2,0xa1,1,0,0xa0,3};
	BYTE turnOnCmd[] =  {2,0xa1,1,1,0xa1,3};

	cam->SetAcqParam(P_COM_PORT_NAME , (DWORD)"COM2");
	cam->SetAcqParam(P_COM_PORT_BYTESIZE , IFC_COM_8BITS);
	cam->SetAcqParam(P_COM_PORT_BAUDRATE , IFC_BAUD_9600);
	cam->SetAcqParam(P_COM_PORT_PARITY , IFC_NOPARITY);
	cam->SetAcqParam(P_COM_PORT_STOPBITS , IFC_ONESTOPBIT);

	if (turnOn)
		return cam->WriteUartCommand(turnOnCmd,6);
	else
		return cam->WriteUartCommand(turnOffCmd,6);

}

BOOL CRuleEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i;
	char editStr[100];
	double paramVal;
	CAM_ATTR attr;
	m_pCamera->GetAttr(&attr);

	UpdateData();
	m_paramIdList.ResetContent();
	m_curParamID = m_pCamera->GetFirstParam();
	for (;m_curParamID != IFC_LAST_SUP_PARAM;) {
		m_pCamera->GetParamCaps(m_curParamID, &m_curParmCaps);
		i = m_paramIdList.AddString(m_curParmCaps.paramName);
		m_paramIdList.SetItemData(i,m_curParmCaps.param);
		m_curParamID = m_pCamera->GetNextParam(m_curParamID);
	}
	m_curParamID = m_pCamera->GetFirstParam();
	m_paramIdList.SetCurSel(0);
	m_curParamID = m_paramIdList.GetItemData(m_paramIdList.GetCurSel());
	paramVal = m_pCamera->GetAcqParam(m_curParamID);
	m_conditionParamVal = m_pCamera->ParamValToString(m_curParamID,paramVal,editStr);


	PIFC_UART_RULE rule;
	for (rule=m_pICap->GetNextRule(attr.camName,NULL); rule; rule=m_pICap->GetNextRule(attr.camName,rule) ) {
		AddRuleStr(rule);
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CRuleEdit::OnSelendokCondParamid() 
{
	int i;
	double paramVal;
	char editStr[100];
	UpdateData();
	m_curParamID = m_paramIdList.GetItemData(m_paramIdList.GetCurSel());
	m_pCamera->GetParamCaps(m_curParamID, &m_curParmCaps);
	paramVal = m_pCamera->GetAcqParam(m_curParamID);
	m_paramValList.ResetContent();
	if (m_curParmCaps.paramType == IFC_ENUM_TYPE) {
		IFC_ENUM_ARG enumArg;
		BOOL bHasArgs = m_pCamera->GetFirstEnumArg(m_curParamID, &enumArg);
				
		while (bHasArgs) {
			i = m_paramValList.AddString(enumArg.argName);
			if ( paramVal == enumArg.argValue) {
				m_paramValList.SetCurSel(i);
				m_conditionParamVal = enumArg.argName;
			}
			bHasArgs = m_pCamera->GetNextEnumArg(m_curParamID, &enumArg);
		}
		
	}
	else {
		m_conditionParamVal = m_pCamera->ParamValToString(m_curParamID,paramVal,editStr);

	}

	UpdateData(FALSE);	
}



void CRuleEdit::AddRuleStr(PIFC_UART_RULE rule)
{
	int i,idx;
	char ruleStr[200]={0,};
	IFC_PARAM_CAPS parmCaps;
	char tStr[80];
	for (i=0; i < (int)rule->numConditions; i++) {
		if (i!=0) strcat(ruleStr," & ");
		m_pCamera->GetParamCaps(rule->conditions[i].paramID, &parmCaps);
		strcat(ruleStr,parmCaps.paramName);
		strcat(ruleStr,"=");
		strcat(ruleStr,m_pCamera->ParamValToString(rule->conditions[i].paramID,rule->conditions[i].paramVal[0],tStr));
	}
	strcat(ruleStr,"  >> (");
	for (i=0; i < (int)rule->numRuleBytes; i++) {
		sprintf(tStr," %d ",rule->ruleStr[i] );
		strcat(	ruleStr,tStr);
	}
	strcat(ruleStr,")");

	idx = m_ruleList.AddString(ruleStr);
	m_ruleList.SetItemData(idx,(DWORD)rule);
}


void CRuleEdit::OnClearConditions() 
{
	m_rule.numConditions = 0;
	m_conditionList.ResetContent();
	
}

void CRuleEdit::OnDeleteCondition() 
{
	int i,idx;
	IFC_PARAM_CAPS parmCaps;
	char condition[180];
	char tStr[100];
	idx = m_conditionList.GetCurSel();	
	if (idx >= 0) {
		for (i = m_conditionList.GetItemData(idx); i < (int)(m_rule.numConditions-1); i++) {
			m_rule.conditions[i].paramID = m_rule.conditions[i+1].paramID;
			m_rule.conditions[i].paramVal[0] = m_rule.conditions[i+1].paramVal[0];
		}
		m_rule.numConditions--;
		
		m_conditionList.ResetContent();

		for (i=0; i < (int)m_rule.numConditions; i++) {
			m_pCamera->GetParamCaps(m_rule.conditions[i].paramID, &parmCaps);
			m_pCamera->ParamValToString(m_rule.conditions[i].paramID,m_rule.conditions[i].paramVal[0],tStr);
			sprintf(condition,"%s = %s", parmCaps.paramName,tStr);
			idx = m_conditionList.AddString(condition);
			m_conditionList.SetItemData(idx,i);
		}
		
	}		
}

void CRuleEdit::OnDelRule() 
{
	PIFC_UART_RULE rule;
	int idx;
	CAM_ATTR attr;
	m_pCamera->GetAttr(&attr);
	idx = m_ruleList.GetCurSel();	
	if (idx >= 0) {
		rule = (PIFC_UART_RULE)m_ruleList.GetItemData(idx);
		m_ruleList.DeleteString(idx);
		m_pICap->DeleteRule(attr.camName,rule);
	}		
}
