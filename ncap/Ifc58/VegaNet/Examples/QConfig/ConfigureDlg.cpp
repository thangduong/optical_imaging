// ConfigureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "configurator.h"
#include "ConfigureDlg.h"
#include "NewCameraDlg.h"
#include "ConfiguratorDoc.h"
#include "ConfiguratorView.h"
#include "GroupProp.h"
#include "NotAppl.h"

#include "OLESTD.H"
#include <VnVidSrc.h> 
#include <pcdigt.h>
#include <pcplust.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TWIPS_PER_INCH 1440


/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg dialog


CConfigureDlg::CConfigureDlg(CConfiguratorView *pParent, IVideoSrc *pICap)
	: CDialog(CConfigureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigureDlg)
	m_strEditParamVal = _T("");
	m_strComboParamVal = _T("");
	m_ShowSubgroups = TRUE;
	//}}AFX_DATA_INIT
	m_portNum = 0;
	m_pParent = pParent;
	m_pCamera = pICap;
	m_SavedTreeState = NULL;

}


void CConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigureDlg)
	DDX_Control(pDX, IDC_LIBR_MODE, m_ctlLibrMode);
	DDX_Control(pDX, IDC_PGRP_TREE, m_ParamTree);
	DDX_Control(pDX, IDC_PORT_LIST, m_cbPortList);
	DDX_Control(pDX, IDC_BUTTON_COPY_CAMERA, m_buttonCopyCam);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_buttonSave);
	DDX_Control(pDX, IDC_EDIT_PARAM_VAL, m_editParamVal);
	DDX_Control(pDX, IDC_COMBO_PARAM_VAL, m_comboBoxParamVal);
	DDX_Control(pDX, IDC_CAMERA_LIST, m_listBoxCameras);
	DDX_Control(pDX, IDC_MSFLEXGRID_PARAMS, m_MSFlexGridParams);
	DDX_Text(pDX, IDC_EDIT_PARAM_VAL, m_strEditParamVal);
	DDX_CBString(pDX, IDC_COMBO_PARAM_VAL, m_strComboParamVal);
	DDX_Check(pDX, IDC_INC_SUBGROUP, m_ShowSubgroups);
	//}}AFX_DATA_MAP
	
	if( pDX->m_bSaveAndValidate ) {

	}
	else {

	}
}




BEGIN_MESSAGE_MAP(CConfigureDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigureDlg)
	ON_BN_CLICKED(IDC_READ_CAM_FILES, OnReadCamFiles)
	ON_LBN_SELCHANGE(IDC_CAMERA_LIST, OnSelchangeCameraList)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_COPY_CAMERA, OnButtonCopyCamera)
	ON_CBN_SELCHANGE(IDC_PORT_LIST, OnSelchangePortList)
	ON_BN_CLICKED(IDC_SAVE_USER_CFG, OnSaveUserCfg)
	ON_BN_CLICKED(IDC_READ_USER_CFG, OnReadUserCfg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_PGRP_TREE, OnSelchangedPgrpTree)
	ON_BN_CLICKED(IDC_INC_SUBGROUP, OnIncSubgroup)
	ON_NOTIFY(NM_RCLICK, IDC_PGRP_TREE, OnRclickPgrpTree)
	ON_COMMAND(ID_GROUPMENU_EDITDIALOG, OnGroupMenuEditDialog)
	ON_COMMAND(ID_GROUPMENU_PROPERTIES, OnGroupMenuProperties)
	ON_COMMAND(ID_GROUPMENU_APPLICABILITY, OnGroupMenuApplicability)
	ON_BN_CLICKED(IDC_LIBR_MODE, OnLibrMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg message handlers



// Defines How many columns are visible at once. Can scroll columns.
#define FLEXGRID_NUMBER_OF_VISIBLE_COLUMNS 2


void CConfigureDlg::AddParamGroupsToTree(HTREEITEM parentTreeItem, VS_PARAM_GROUP_TYPE parentGroupID)
{
	TV_INSERTSTRUCT TreeCtrlItem;
	HTREEITEM hItem;
	VS_PARAM_GROUP_PROPS groupProps;
	VS_PARAM_GROUP_TYPE gid;
	VS_ACQ_PARAMS_TYPE pid;
	for (m_pCamera->GetFirstParamGroup(parentGroupID,&gid); gid != VS_LAST_SUPPORT_PGRP; m_pCamera->GetNextParamGroup(gid,&gid) ) {
		m_pCamera->GetGroupProperties(gid,&groupProps);

		TreeCtrlItem.hInsertAfter = TVI_LAST;
		TreeCtrlItem.item.mask = TVIF_TEXT | TVIF_PARAM;
		TreeCtrlItem.hParent = parentTreeItem;
		TreeCtrlItem.item.pszText = groupProps.presentationName;
		TreeCtrlItem.item.lParam = gid;
		hItem=m_ParamTree.InsertItem(&TreeCtrlItem);
		if (gid==m_pParent->m_currentSelectedGroup)
			m_ParamTree.SelectItem(hItem);

		AddParamGroupsToTree(hItem,gid);
		m_ParamTree.Expand(hItem,TVE_EXPAND);
		for ( m_pCamera->GetFirstParam(groupProps.groupMask,FALSE,&pid); pid != VS_LAST_SUP_PARAM; m_pCamera->GetNextParam(pid,groupProps.groupMask,FALSE,&pid) ) {

		}
	}
}





BOOL CConfigureDlg::OnInitDialog() 
{
	WORD i;
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	CDialog::OnInitDialog();
	VSPROPS props;
	m_pCamera->GetProps(&props);
	
	m_MSFlexGridParams.SetCols(VS_MAX_PARAM_ARRAY_DIM + 1);

	LoadCameraList();
	
//	m_pCamera->Freeze(0);
//	m_pCamera->GrabOn();

	CRect rectGrid;
	m_MSFlexGridParams.GetClientRect(&rectGrid);
	int iColWidth = rectGrid.Width() / FLEXGRID_NUMBER_OF_VISIBLE_COLUMNS;

	// Convert pixels to twips to set the column width.
	// We purposefully don't combine TWIPS_PER_INCH and
	// m_iXPixelsPerInch to make one factor since
	// a non-integer result would get truncated.
	// We avoid this and other truncation (rounding) problems 
	// by multiplying by one factor before dividing by the
	// other.
	// Eg. (8 * 10) / 20 = 80 / 20 = 4.
	//     But 8 * (10 / 20) = 8 * 0 = 0. Due to rounding of .5 to 0.

	CDC *pDC = GetDC();
    m_iXPixelsPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
    m_iYPixelsPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
    ReleaseDC(pDC);

	iColWidth *= TWIPS_PER_INCH;
	iColWidth /= m_iXPixelsPerInch;

	for ( i = 0; i < VS_MAX_PARAM_ARRAY_DIM + 1; i++)
	{
		m_MSFlexGridParams.SetColWidth(i, iColWidth);
	}

	// Currently, this is never changed from FALSE, so it's not really used but we
	// leave it in case we decide to use it in the future.
	m_bParamsReadOnly = FALSE;

	m_buttonCopyCam.EnableWindow(FALSE);

	DWORD numPorts;
	m_pCamera->GetNumPorts(&numPorts);
	for ( i = 0; i < numPorts ; i++) {
		char *portName="Port 0";
		portName[5]='0'+i;
		m_cbPortList.AddString(portName);
	}
	m_cbPortList.SetCurSel(0);


	TV_INSERTSTRUCT TreeCtrlItem;

	TreeCtrlItem.hParent = TVI_ROOT;
	TreeCtrlItem.hInsertAfter = TVI_LAST;
	TreeCtrlItem.item.mask = TVIF_TEXT | TVIF_PARAM;
	TreeCtrlItem.item.pszText = props.installedName;
	TreeCtrlItem.item.lParam = VS_PGRP_TOP_LEVEL;
	HTREEITEM hTreeItem1 = m_ParamTree.InsertItem(&TreeCtrlItem);
	if (m_pParent->m_currentSelectedGroup==VS_PGRP_TOP_LEVEL)
		m_ParamTree.SelectItem(hTreeItem1);
	AddParamGroupsToTree(hTreeItem1,VS_PGRP_TOP_LEVEL);

	SavePGroupTreeState();

	if (thisApp->m_LibrarianModeEnabled)
		m_ctlLibrMode.SetWindowText("Librarian Mode On");
	else
		m_ctlLibrMode.SetWindowText("Librarian Mode Off");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CConfigureDlg::LoadCameraList()
{
	// Populate listbox with names of all Camera types
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	m_listBoxCameras.ResetContent();
	HRESULT status;
	char sz[200];
	if (parent) {
		parent->DeleteDisplay();
	}
	status = m_pCamera->GetFirstCamType(sz);
	while(status==S_OK) {
		m_listBoxCameras.AddString(sz);
		status = m_pCamera->GetNextCamType(sz);
	}
	// Get the name of the currently active camera
	VS_CAM_ATTR camAttr;
	m_pCamera->GetAttr(&camAttr,TRUE);
	int camIndex = m_listBoxCameras.FindStringExact(-1,camAttr.camName);
	// ... and set the currently selected item to match the current camera
	if (camIndex != LB_ERR)
		m_listBoxCameras.SetCurSel(camIndex);	
	else
		m_listBoxCameras.SetCurSel(0);	
	m_strExistingCamSel = camAttr.camName;


	LoadParamsList(m_strExistingCamSel);

}

void CConfigureDlg::OnSelchangeCameraList() 
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	// The user has selected a camera in the
	// list so enable the copy button.
	m_buttonCopyCam.EnableWindow();


	int iSel = m_listBoxCameras.GetCurSel();
	m_listBoxCameras.GetText(iSel, m_strExistingCamSel);
	LoadParamsList(m_strExistingCamSel);
	
}

void CConfigureDlg::OnButtonCopyCamera() 
{
	CNewCameraDlg dlg(NULL, m_pCamera);
	DWORD newCamHnd;
	int nResult = dlg.DoModal();

	if (nResult == IDOK)
	{
		CString strNewCameraName;
		dlg.GetCamName(strNewCameraName);
		m_pCamera->AddCameraType(strNewCameraName.GetBuffer(128), m_strExistingCamSel.GetBuffer(128),&newCamHnd);
		m_strExistingCamSel.ReleaseBuffer();
		strNewCameraName.ReleaseBuffer();
		int iSel = m_listBoxCameras.AddString(strNewCameraName);
		m_listBoxCameras.SetCurSel(iSel);
		m_strExistingCamSel = strNewCameraName;
		LoadParamsList(strNewCameraName);
	}
}

void CConfigureDlg::LoadParamsList(const CString &CamDefName)
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;

	CloseEdit();

	if (parent) {
		parent->DeleteDisplay();
	}
	m_pCamera->Freeze(0);

	m_MSFlexGridParams.Clear();

	// Set column labels.

	m_MSFlexGridParams.SetRow(0);
	m_MSFlexGridParams.SetCol(0);
	m_MSFlexGridParams.SetText("Parameter");

	WORD i;
	CString str;

	for (i = 0; i < VS_MAX_PARAM_ARRAY_DIM; i++)
	{
		str.Format("Value[%d]", i);
		m_MSFlexGridParams.SetCol(i + 1);
		m_MSFlexGridParams.SetText(str);
	}

	// Fill in grid with parameters from camera definition.

	str = CamDefName;
	m_pCamera->SetCameraType(str.GetBuffer(128),TRUE);
	VS_PARAM_GROUP_PROPS GroupProps;
	m_pCamera->GetGroupProperties(m_pParent->m_currentSelectedGroup,&GroupProps);

	DWORD ParamGroupsMask = GroupProps.groupMask;


	DWORD parmIndex = 0;
	m_iCurSelParam = 0;
	m_pCamera->GetFirstParam(ParamGroupsMask,m_ShowSubgroups,&m_curParamID);
	double dVal;
	short nRow;
	char reasonNotAppl[240];
	
	while (m_curParamID != VS_LAST_SUP_PARAM)
	{
		m_pCamera->GetParamCaps(m_curParamID, &m_curParmCaps);

		nRow = m_iCurSelParam + 1;

		if (m_MSFlexGridParams.GetRows() <= nRow)
		{
			// If we ran out of rows, add several so we don't need to keep 
			// adding one at a time.

			COleVariant	v;

			for (i = nRow; i < nRow + ((m_MSFlexGridParams.GetRows()<20)?20:5); i++)
			{
				v = (short) i;
				m_MSFlexGridParams.AddItem("", v);
			}
		}

		m_MSFlexGridParams.SetRow(nRow);
		m_MSFlexGridParams.SetCol(0);
		m_MSFlexGridParams.SetText(m_curParmCaps.presentationName);

		// We associate paramID with the item so that when the user later
		// selects an item we know which parameter it is.
		m_MSFlexGridParams.SetRowData(nRow, m_curParamID);

		for (i = 0; i < m_curParmCaps.dwArrayDim; i++)
		{
			m_pCamera->GetAcqParam( m_curParamID,&dVal, i);
			m_pCamera->ParamValToString(m_curParamID, dVal, str.GetBuffer(128));
			str.ReleaseBuffer();
			m_MSFlexGridParams.SetCol(i + 1);
			m_MSFlexGridParams.SetText(str);
			if ((m_curParmCaps.dwCapFlags&VS_PARAMCAP_READ_ONLY)
				|| m_pCamera->ParamIsApplicable(m_curParamID,0,reasonNotAppl) == S_FALSE) {
				m_MSFlexGridParams.SetCellBackColor(0x808080);
				m_MSFlexGridParams.SetCellForeColor(0xffffff);
			}

		}

		m_iCurSelParam++;

		m_pCamera->GetNextParam(m_curParamID,ParamGroupsMask,m_ShowSubgroups,&m_curParamID);
	}
	parent->CreateDisplay();


}


void CConfigureDlg::ChDirToCamDb() 
{
    CString strCamDbDir = CString(getenv("IFCCNF")) + "\\user";
	_chdir(strCamDbDir);
}


void CConfigureDlg::OnReadCamFiles() 
{
	ChDirToCamDb();
	
	CFileDialog dlg(TRUE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
		"Config Files (*.txt)|*.txt||");
	
	if (dlg.DoModal() == IDCANCEL )
		return;
	
	POSITION pos;
	
	CString strFilePath;
	
	pos = dlg.GetStartPosition();
	
	if (pos == NULL)
		return;
	
	while (pos) {
		strFilePath = dlg.GetNextPathName(pos);
		m_pCamera->ReadCamerasInFile(strFilePath.GetBuffer(128),VS_FILESYS_CLIENT);
		strFilePath.ReleaseBuffer();
	}
	
	m_portNum = m_cbPortList.GetCurSel();	
	m_pCamera->SetPortNum(m_portNum);
	LoadCameraList();
}

void CConfigureDlg::OnButtonSave()
{
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	if (m_pCamera && m_pCamera->CameraIsReserved((char*)(LPCTSTR)m_strExistingCamSel)
		&& !thisApp->m_LibrarianModeEnabled) {
		if (::MessageBox(NULL,"This Camera is a Factory installed read only definition."
			" Do you want to make a user copy of the camera and then save it?",
		"Read Only",MB_YESNO) == IDYES)
			OnButtonCopyCamera();
		else
			return;
	}


	CloseEdit();
	ChDirToCamDb();

	CFileDialog dlg(FALSE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					"Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDOK) {
		m_pCamera->WriteCameraFile(dlg.GetPathName().GetBuffer(256),VS_FILESYS_CLIENT, m_strExistingCamSel.GetBuffer(256));
		m_strExistingCamSel.ReleaseBuffer();
	}
}


BEGIN_EVENTSINK_MAP(CConfigureDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CConfigureDlg)
	ON_EVENT(CConfigureDlg, IDC_MSFLEXGRID_PARAMS, 72 /* LeaveCell */, OnLeaveCellMsflexgridParams, VTS_NONE)
	ON_EVENT(CConfigureDlg, IDC_MSFLEXGRID_PARAMS, 71 /* EnterCell */, OnEnterCellMsflexgridParams, VTS_NONE)
	ON_EVENT(CConfigureDlg, IDC_MSFLEXGRID_PARAMS, -601 /* DblClick */, OnDblClickMsflexgridParams, VTS_NONE)
	ON_EVENT(CConfigureDlg, IDC_MSFLEXGRID_PARAMS, -603 /* KeyPress */, OnKeyPressMsflexgridParams, VTS_PI2)
	ON_EVENT(CConfigureDlg, IDC_MSFLEXGRID_PARAMS, 73 /* Scroll */, OnScrollMsflexgridParams, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CConfigureDlg::OnDblClickMsflexgridParams() 
{
	GridEdit((short *) " ");	
}

void CConfigureDlg::OnKeyPressMsflexgridParams(short FAR* KeyAscii) 
{
	GridEdit(KeyAscii);
}

void CConfigureDlg::GridEdit(short FAR* KeyAscii)
{
	char ReasonNotApplicable[VS_MAX_PARAM_APPLICABLE_LEN];
	double dVal;
	if (m_bParamsReadOnly)
		return;
	
	UpdateData();
	CRect rectGrid;
	
	// The MFC Window functions always deal with pixels which
	// are the screen device coordinates.
	m_MSFlexGridParams.GetWindowRect(&rectGrid);
	ScreenToClient(&rectGrid);
	
	// The Active X Control CMSFlexGrid uses twips for coordinate units so
	// we must convert these to pixels. There are 1440 twips per inch. This
	// information and the number of pixels per inch for the device enable
	// us to do the conversion.
	
	int iCellLeft   = (m_MSFlexGridParams.GetCellLeft()   * m_iXPixelsPerInch) / TWIPS_PER_INCH;
	int iCellTop    = (m_MSFlexGridParams.GetCellTop()    * m_iYPixelsPerInch) / TWIPS_PER_INCH;
	int iCellWidth  = (m_MSFlexGridParams.GetCellWidth()  * m_iXPixelsPerInch) / TWIPS_PER_INCH;
	int iCellHeight = (m_MSFlexGridParams.GetCellHeight() * m_iYPixelsPerInch) / TWIPS_PER_INCH;
	
	int iEditLeft   = rectGrid.TopLeft().x + iCellLeft;
	int iEditTop    = rectGrid.TopLeft().y + iCellTop;
	
	m_curParamID = (VS_ACQ_PARAMS_TYPE)m_MSFlexGridParams.GetRowData(m_MSFlexGridParams.GetRow());
	
	// Don't confuse this with the row index in the grid. This is the value
	// array index for parameters that support an array of values. All values
	// in such arrays are displayed accross the row - in each column.
	m_dwParamValIndex = m_MSFlexGridParams.GetCol() - 1;
	
	CWnd *pWnd;
	VS_PARAM_CAPS paramCaps;
	m_pCamera->GetParamCaps(m_curParamID,&paramCaps);
	if (paramCaps.dwCapFlags&VS_PARAMCAP_READ_ONLY) {
		::MessageBox(NULL,"This parameter is read only.",
		"Read Only",MB_OK);
		return;
		
	}
	if (m_pCamera->ParamIsApplicable(m_curParamID,m_dwParamValIndex,ReasonNotApplicable) == S_FALSE) {
		CNotAppl dlg(this,(CString)paramCaps.paramName + " is not currently applicable because:",ReasonNotApplicable);
		dlg.DoModal();	
	}
	if (m_pCamera->QueryUIParamUpdate(&dVal,m_curParamID,0)==S_OK) {
		NewParamRefresh(dVal);
		return;
	}
	if (paramCaps.paramType == VS_ENUM_TYPE) {
		VS_ENUM_ARG enumArg;
		BOOL bHasArgs = m_pCamera->GetFirstEnumArg(m_curParamID, &enumArg) == S_OK;
		
		// Put value in combo box and add choices (if any) to combo box
		// list.
		m_comboBoxParamVal.ResetContent();
		m_strComboParamVal = m_MSFlexGridParams.GetText();
		
		while (bHasArgs)
		{
			m_comboBoxParamVal.AddString(enumArg.argName);
			bHasArgs = m_pCamera->GetNextEnumArg(m_curParamID, &enumArg) == S_OK;
		}
		
		pWnd = &m_comboBoxParamVal;
	}
	else
	{
		if (*KeyAscii >= 0 && *KeyAscii <= (short) ' ')
		{
			m_strEditParamVal = m_MSFlexGridParams.GetText();
			m_editParamVal.SetSel(0, 0);
		}
		else
		{
			m_strEditParamVal = (char *) KeyAscii;
			m_editParamVal.SetSel(1, 1);
		}
		
		pWnd = &m_editParamVal;
	}
	BOOL test = pWnd->SetWindowPos(NULL, iEditLeft, iEditTop,
		iCellWidth, iCellHeight,
		SWP_SHOWWINDOW /* | SWP_NOZORDER */);
	
	pWnd->ShowWindow(SW_SHOW);
	pWnd->SetFocus();
	UpdateData(FALSE);
}



void CConfigureDlg::OnLeaveCellMsflexgridParams() 
{
	CloseEdit();
}

void CConfigureDlg::OnEnterCellMsflexgridParams() 
{
	// This handles the case of a user leaving the grid control while editing
	// and returning to the grid from another control.
	CloseEdit();
}

void CConfigureDlg::OnScrollMsflexgridParams() 
{
	CloseEdit();
}

void CConfigureDlg::NewParamRefresh(double dVal)
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	if (parent) {
		parent->DeleteDisplay();
	}
	m_pCamera->Freeze(0);
	m_pCamera->SetAcqParam( m_curParamID, dVal,m_dwParamValIndex );

	LoadParamsList(m_strExistingCamSel);
}


void CConfigureDlg::CloseEdit()
{
	UpdateData();

	CString strNewVal;

	if (m_editParamVal.IsWindowVisible())
	{
		strNewVal = m_strEditParamVal;
		m_editParamVal.ShowWindow(SW_HIDE);
	}
	else if (m_comboBoxParamVal.IsWindowVisible())
	{
		strNewVal = m_strComboParamVal;
		m_comboBoxParamVal.ShowWindow(SW_HIDE);
	}
	else
	{
		return;
	}

	double dVal;
	m_pCamera->ParamStringToVal(m_curParamID, strNewVal.GetBuffer(128),&dVal);
	strNewVal.ReleaseBuffer();
	NewParamRefresh(dVal);

}


void CConfigureDlg::OnSelchangePortList() 
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	if (parent) {
		parent->DeleteDisplay();
	}

	m_pCamera->Freeze(0);

	m_portNum = m_cbPortList.GetCurSel();	
	m_pCamera->SetPortNum(m_portNum);
	LoadCameraList();	
}


void CConfigureDlg::OnSaveUserCfg() 
{
	CloseEdit();
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);

	CFileDialog dlg(FALSE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					"Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDOK) {
		m_pCamera->WriteUserConfigFile(dlg.GetPathName().GetBuffer(256),VS_FILESYS_CLIENT);
	}
	
}

void CConfigureDlg::OnReadUserCfg() 
{
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);

	CFileDialog dlg(TRUE, "txt", NULL,OFN_HIDEREADONLY ,
					  "Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() != IDOK)
		return;
	
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	if (parent) {
		parent->DeleteDisplay();
	}
	m_pCamera->Freeze(0);

	CString fName=dlg.GetPathName();

	m_pCamera->ReadUserConfigFile(fName.GetBuffer(256),VS_FILESYS_CLIENT);
	m_pCamera->SetPortNum(m_portNum);
	LoadCameraList();
	
}

void CConfigureDlg::OnSelchangedPgrpTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_pParent->m_currentSelectedGroup = (VS_PARAM_GROUP_TYPE)pNMTreeView->itemNew.lParam;
	LoadParamsList(m_strExistingCamSel);
	
	*pResult = 0;
}


void CConfigureDlg::OnIncSubgroup() 
{
	LoadParamsList(m_strExistingCamSel);	
}


void CConfigureDlg::DoPopupMenu(UINT nMenuID)
{
	CMenu popMenu;
	char reasonNotAppl[120]={0,};

	popMenu.LoadMenu(nMenuID);

	CPoint posMouse;
	GetCursorPos(&posMouse);

	if (!m_pCamera->ParamGroupEditDlgExist(m_rClickGroup))
		popMenu.GetSubMenu(0)->EnableMenuItem(ID_GROUPMENU_EDITDIALOG,MF_GRAYED);

	if (m_pCamera->GroupIsApplicable(m_rClickGroup,reasonNotAppl) == S_OK)
		popMenu.GetSubMenu(0)->EnableMenuItem(ID_GROUPMENU_APPLICABILITY,MF_GRAYED);

	popMenu.GetSubMenu(0)->TrackPopupMenu(0,posMouse.x,posMouse.y,this);
}


void CConfigureDlg::OnRclickPgrpTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	UINT nFlags;
	CPoint curPoint;

	GetCursorPos(&curPoint);
	m_ParamTree.ScreenToClient(&curPoint);
	m_ItemSel = m_ParamTree.HitTest(curPoint, &nFlags);
	if (!m_ItemSel)
		return;
	TVITEM item;
	item.hItem = m_ItemSel;
	m_ParamTree.GetItem(&item);
	m_rClickGroup = (VS_PARAM_GROUP_TYPE)item.lParam;
	DoPopupMenu(IDR_MENU_GRP);
	
	*pResult = 0;
}


void CConfigureDlg::OnGroupMenuEditDialog() 
{
	m_pCamera->DoParamGroupEditDialog(m_rClickGroup,VSP_ALL_CAM_PARAMS_ID);	
}


void CConfigureDlg::OnGroupMenuProperties() 
{
	CGroupProp dlg(this);
	dlg.DoModal();
}


void CConfigureDlg::OnGroupMenuApplicability() 
{
	char ReasonNotApplicable[VS_MAX_PARAM_APPLICABLE_LEN];
	VS_PARAM_GROUP_PROPS groupProps;

	m_pCamera->GroupIsApplicable(m_rClickGroup,ReasonNotApplicable);
	m_pCamera->GetGroupProperties(m_rClickGroup,&groupProps);

	CNotAppl dlg(this,(CString)groupProps.groupName + " is not currently applicable because:",ReasonNotApplicable);
	dlg.DoModal();	
}

void CConfigureDlg::OnLibrMode() 
{
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	thisApp->m_LibrarianModeEnabled = !thisApp->m_LibrarianModeEnabled;	
	if (thisApp->m_LibrarianModeEnabled)
		m_ctlLibrMode.SetWindowText("Librarian Mode On");
	else
		m_ctlLibrMode.SetWindowText("Librarian Mode Off");

}





BOOL CConfigureDlg::SavePGroupTreeState()
{
	HTREEITEM hItem=m_ParamTree.GetRootItem();
	if (!hItem)
		return FALSE;
	DeletePGroupStateTree();
	m_SavedTreeState = new CFG_TREE_STATE_NODE;
	m_SavedTreeState->state = m_ParamTree.GetItemState(hItem, TVIS_EXPANDED);
	m_SavedTreeState->firstChild = NULL;
	m_SavedTreeState->nextSibling = NULL;
	AddChildrenStates(hItem,m_SavedTreeState);
	return TRUE;
}


BOOL CConfigureDlg::AddChildrenStates(HTREEITEM hParentItem, CFG_TREE_STATE_NODE *parentNode)
{
	CFG_TREE_STATE_NODE *node;
	CFG_TREE_STATE_NODE *olderSibling=NULL;
	HTREEITEM hItem;

	if (m_ParamTree.ItemHasChildren(hParentItem)) {
		hItem = m_ParamTree.GetChildItem(hParentItem);
		
		while (hItem) {
			node = new CFG_TREE_STATE_NODE;
			if (!parentNode->firstChild)
				parentNode->firstChild = node;
			node->state = m_ParamTree.GetItemState(hItem, TVIS_EXPANDED);
			node->firstChild = NULL;
			node->nextSibling = NULL;
			if (olderSibling)
				olderSibling->nextSibling = node;
			AddChildrenStates(hItem,node);
			olderSibling = node;
			hItem = m_ParamTree.GetNextItem(hItem, TVGN_NEXT);
		}
		return TRUE;
	}
	else {
		return FALSE;
	}
	
}

void CConfigureDlg::DeletePGroupStateTree()
{
	if (m_SavedTreeState) {
		DeleteChildrenStates(m_SavedTreeState);
		delete m_SavedTreeState;
		m_SavedTreeState = NULL;
	}
}

void CConfigureDlg::DeleteChildrenStates(CFG_TREE_STATE_NODE *parentNode)
{
	CFG_TREE_STATE_NODE *node;
	CFG_TREE_STATE_NODE *NextChild;
	if (parentNode) {
		for (node=parentNode->firstChild;node;node=NextChild) {
			DeleteChildrenStates(node);
			NextChild = node->nextSibling;
			delete node;
		}
	}
}
