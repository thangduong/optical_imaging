// ConfigureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "direct.h"
#include "configurator.h"
#include "ConfigureDlg.h"
#include "CameraMgrDlg.h"
#include "NewCameraDlg.h"
#include "ConfiguratorDoc.h"
#include "ConfiguratorView.h"
#include "GroupProp.h"
#include "NotAppl.h"
#include "RuleEdit.h"

#include <ifc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TWIPS_PER_INCH 1440

typedef enum {transparent, dark_red, dark_green, dark_yellow, dark_blue, dark_magenta, dark_cyan, light_gray1,
			  money_green, sky_blue, cream, light_gray2, medium_gray, red, green, yellow, blue, magenta, cyan, white} STATIC_COLOR;


/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg dialog


CConfigureDlg::CConfigureDlg(CConfiguratorView *pParent, PCICapMod pICap)
	: CDialog(CConfigureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigureDlg)
	m_strEditParamVal = _T("");
	m_strComboParamVal = _T("");
	m_ShowSubgroups = TRUE;
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	m_pICap = pICap;
	m_pCamera = m_pICap->GetCam(IFC_ACTIVE_CAMERA_FLAG);
	m_portNum = m_pCamera->GetPortNum();
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
	ON_BN_CLICKED(IDC_RULE_EDITOR, OnRuleEditor)
	ON_NOTIFY(NM_DBLCLK, IDC_PGRP_TREE, OnDblclkPgrpTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg message handlers



// Defines How many columns are visible at once. Can scroll columns.
#define FLEXGRID_NUMBER_OF_VISIBLE_COLUMNS 2


void CConfigureDlg::AddParamGroupsToTree(HTREEITEM parentTreeItem, IFC_PARAM_GROUP_TYPE parentGroupID)
{
	TV_INSERTSTRUCT TreeCtrlItem;
	HTREEITEM hItem;
	IFC_PARAM_GROUP_PROPS groupProps;
	IFC_PARAM_GROUP_TYPE gid;
	ACQ_PARAMS_TYPE pid;
	for (gid=m_pCamera->GetFirstParamGroup(parentGroupID); gid != IFC_LAST_SUPPORT_PGRP; gid=m_pCamera->GetNextParamGroup(gid) ) {
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
		for ( pid=m_pCamera->GetFirstParam(groupProps.groupMask,FALSE); pid != IFC_LAST_SUP_PARAM; pid=m_pCamera->GetNextParam(pid,groupProps.groupMask,FALSE) ) {

		}
	}
}





BOOL CConfigureDlg::OnInitDialog() 
{
	WORD i;
	CConfiguratorApp *thisApp = (CConfiguratorApp *) AfxGetApp();
	CDialog::OnInitDialog();
	
	m_MSFlexGridParams.SetCols(IFC_MAX_PARAM_ARRAY_DIM + 1);

	LoadCameraList();
	
	m_pCamera->Freeze();
	m_pCamera->Grab();

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

	for ( i = 0; i < IFC_MAX_PARAM_ARRAY_DIM + 1; i++)
	{
		m_MSFlexGridParams.SetColWidth(i, iColWidth);
	}

	// Currently, this is never changed from FALSE, so it's not really used but we
	// leave it in case we decide to use it in the future.
	m_bParamsReadOnly = FALSE;

	m_buttonCopyCam.EnableWindow(FALSE);

	CICamera *cam;
	for ( i = 0; cam=m_pICap->GetCam(i) ; i++) {
		char portName[100];
		char camPortName[40];
		sprintf(portName,"Port %d  %s",i,m_pICap->GetCamPortName(i,camPortName));
		m_cbPortList.AddString(portName);
	}
	m_cbPortList.SetCurSel(m_portNum);

	GenerateParamGroupTree();


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
	m_listBoxCameras.ResetContent();
	char *sz = m_pICap->GetFirstCamType();
	while(sz)
	{
		m_listBoxCameras.AddString(sz);
		sz = m_pICap->GetNextCamType();
	}
	// Get the name of the currently active camera
	CAM_ATTR camAttr;
	m_pCamera->GetAttr(&camAttr);
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
	CNewCameraDlg dlg(NULL, m_pICap);
	int nResult = dlg.DoModal();

	if (nResult == IDOK)
	{
		CString strNewCameraName;
		dlg.GetCamName(strNewCameraName);
		m_pICap->AddCameraType(strNewCameraName.GetBuffer(128), m_strExistingCamSel.GetBuffer(128));
		m_strExistingCamSel.ReleaseBuffer();
		strNewCameraName.ReleaseBuffer();
		int iSel = m_listBoxCameras.AddString(strNewCameraName);
		m_listBoxCameras.SetCurSel(iSel);
		m_strExistingCamSel = strNewCameraName;
		LoadParamsList(strNewCameraName);
	}
}


void CConfigureDlg::GenerateParamGroupTree() 
{
	TV_INSERTSTRUCT TreeCtrlItem;

	m_ParamTree.DeleteAllItems();
	TreeCtrlItem.hParent = TVI_ROOT;
	TreeCtrlItem.hInsertAfter = TVI_LAST;
	TreeCtrlItem.item.mask = TVIF_TEXT | TVIF_PARAM;
	TreeCtrlItem.item.pszText = m_pICap->ModName();
	TreeCtrlItem.item.lParam = IFC_PGRP_TOP_LEVEL;
	HTREEITEM hTreeItem1 = m_ParamTree.InsertItem(&TreeCtrlItem);
	if (m_pParent->m_currentSelectedGroup==IFC_PGRP_TOP_LEVEL)
		m_ParamTree.SelectItem(hTreeItem1);
	AddParamGroupsToTree(hTreeItem1,IFC_PGRP_TOP_LEVEL);

	SavePGroupTreeState();
}


void CConfigureDlg::LoadParamsList(const CString &CamDefName)
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;

	CloseEdit();

	m_pCamera->Freeze();
	if (parent->m_pImgConn) {
		delete parent->m_pImgConn;
		parent->m_pImgConn = NULL;
	}

	m_MSFlexGridParams.Clear();

	// Set column labels.

	m_MSFlexGridParams.SetRow(0);
	m_MSFlexGridParams.SetCol(0);
	m_MSFlexGridParams.SetText("Parameter");

	WORD i;
	CString str;

	for (i = 0; i < IFC_MAX_PARAM_ARRAY_DIM; i++)
	{
		str.Format("Value[%d]", i);
		m_MSFlexGridParams.SetCol(i + 1);
		m_MSFlexGridParams.SetText(str);
	}

	// Fill in grid with parameters from camera definition.

	str = CamDefName;
	m_pCamera->SetCameraType(str.GetBuffer(128));
	IFC_PARAM_GROUP_PROPS GroupProps;
	m_pCamera->GetGroupProperties(m_pParent->m_currentSelectedGroup,&GroupProps);

	DWORD ParamGroupsMask = GroupProps.groupMask;


	DWORD parmIndex = 0;
	m_iCurSelParam = 0;
	m_curParamID = m_pCamera->GetFirstParam(ParamGroupsMask,m_ShowSubgroups);
	double dVal;
	short nRow;

	while (m_curParamID != IFC_LAST_SUP_PARAM)
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
			dVal = m_pCamera->GetAcqParam( m_curParamID, i);
			m_pCamera->ParamValToString(m_curParamID, dVal, str.GetBuffer(128));
			str.ReleaseBuffer();
			m_MSFlexGridParams.SetCol(i + 1);
			m_MSFlexGridParams.SetText(str);
			if ((m_curParmCaps.dwCapFlags&IFC_PARAMCAP_READ_ONLY)
				|| !m_pCamera->ParamIsApplicable(m_curParamID)) {
				m_MSFlexGridParams.SetCellBackColor(0x808080);
				m_MSFlexGridParams.SetCellForeColor(0xffffff);
			}

		}

		m_iCurSelParam++;

		m_curParamID = m_pCamera->GetNextParam(m_curParamID,ParamGroupsMask,m_ShowSubgroups);
	}

	CAM_ATTR camAttrib;
	m_pCamera->GetAttr(&camAttrib);
	DWORD imgConnFlag=0;
	if ( m_pCamera->GetAcqParam(P_PIXEL_COLOR) == IFC_YCRCB )	{ 
		imgConnFlag |= IFC_YCRCB_SINK;
	}

	if (m_pCamera->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED || strcmp(m_pICap->ModName(),"P2V")==0
		|| strcmp(m_pICap->ModName(),"CL2")==0 
		|| strcmp(m_pICap->ModName(),"X64")==0 
		)
		parent->m_pImgConn = new CImgConn(m_pCamera, m_pParent->m_hWnd,IFC_LIVE_IMAGE | imgConnFlag,ICAP_INTR_EOF);
	else
		parent->m_pImgConn = new CImgConn(m_pCamera, m_pParent->m_hWnd,IFC_LIVE_IMAGE | imgConnFlag,ICAP_INTR_VB);
	if (imgConnFlag & IFC_YCRCB_SINK) {
		parent->m_pImgConn->GetSink()->SetDestColorKey(dark_yellow);
	}

	if ( (strcmp(m_pICap->ModName(),"CL2")==0 
		|| strcmp(m_pICap->ModName(),"X64")==0 )
		&& camAttrib.dwBitsPerPixel > 8 && camAttrib.dwBitsPerPixel <= 16
		) {
		
		parent->m_pImgConn->GetSrc()->SetOptions(IFC_IMGSRC_OPT_PIX_LEAST_SIG);
	}

	m_pCamera->Grab();

}


void CConfigureDlg::ChDirToCamDb() 
{
    CString strCamDbDir = CString(getenv("IFCCNF")) + "\\user";
	_chdir(strCamDbDir);
}


void CConfigureDlg::OnReadCamFiles() 
{
	ChDirToCamDb();

	CCameraMgrDlg dlg(TRUE, "txt", NULL,OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					  "Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDCANCEL && (dlg.m_Canceled || !dlg.m_bAllFiles) )
		return;

	POSITION pos;

	if (dlg.m_bFilesAsLists)
	{
		// Currently, if the user selected more than one file
		// we just use the name of the first file as the file.
		// This file should contain a list of filenames - one
		// per line.
		pos = dlg.GetStartPosition();

		if (pos == NULL)
			return;

		m_pICap->ProcessCameraFileList(dlg.GetNextPathName(pos));
	}
	else
	{
		CString strFilePath;

		if (dlg.m_bAllFiles)
		{
			char szDir[_MAX_DRIVE + _MAX_DIR];
			strcpy(szDir, dlg.GetPath(strFilePath));
			m_pICap->ProcessCameraFilesInDir(szDir, dlg.m_bRecursive);
		}
		else
		{
			pos = dlg.GetStartPosition();

			if (pos == NULL)
				return;

			while (pos)
			{
				strFilePath = dlg.GetNextPathName(pos);
				m_pICap->ProcessCamerasInConfigFile(strFilePath);
			}
		}
	}

	m_portNum = m_cbPortList.GetCurSel();	
	m_pCamera = m_pICap->GetCam(m_portNum);
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

	if (dlg.DoModal() == IDOK)
	{
		// ::MessageBox(NULL, "It is possible to create duplicate camera names. Continue?",
		//			 "Save Camera Definition",  MB_YESNO);

		m_pICap->WriteConfigFile(dlg.GetPathName(), m_strExistingCamSel);
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
	char ReasonNotApplicable[MAX_PARAM_APPLICABLE_LEN];
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
	
	m_curParamID = m_MSFlexGridParams.GetRowData(m_MSFlexGridParams.GetRow());
	
	// Don't confuse this with the row index in the grid. This is the value
	// array index for parameters that support an array of values. All values
	// in such arrays are displayed accross the row - in each column.
	m_dwParamValIndex = m_MSFlexGridParams.GetCol() - 1;
	
	CWnd *pWnd;
	IFC_PARAM_CAPS paramCaps;
	m_pCamera->GetParamCaps(m_curParamID,&paramCaps);
	if (paramCaps.dwCapFlags&IFC_PARAMCAP_READ_ONLY) {
		::MessageBox(NULL,"This parameter is read only.",
		"Read Only",MB_OK);
		return;
		
	}
	if (!m_pCamera->ParamIsApplicable(m_curParamID,m_dwParamValIndex,ReasonNotApplicable)) {
		CNotAppl dlg(this,(CString)paramCaps.paramName + " is not currently applicable because:",ReasonNotApplicable);
		dlg.DoModal();	
	}
	if (m_pCamera->QueryUIParamUpdate(dVal,m_curParamID,0,this)) {
		NewParamRefresh(dVal);
		return;
	}
	if (paramCaps.paramType == IFC_ENUM_TYPE) {
		IFC_ENUM_ARG enumArg;
		BOOL bHasArgs = m_pCamera->GetFirstEnumArg(m_curParamID, &enumArg);
		
		// Put value in combo box and add choices (if any) to combo box
		// list.
		m_comboBoxParamVal.ResetContent();
		m_strComboParamVal = m_MSFlexGridParams.GetText();
		
		while (bHasArgs)
		{
			m_comboBoxParamVal.AddString(enumArg.argName);
			bHasArgs = m_pCamera->GetNextEnumArg(m_curParamID, &enumArg);
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
	m_pCamera->Freeze();
	if (parent->m_pImgConn) {
		delete parent->m_pImgConn;
		parent->m_pImgConn = NULL;
	}
	m_pCamera->SetAcqParam( m_curParamID, dVal,m_dwParamValIndex );
	m_pCamera->EvaluateRules();
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

	double dVal = m_pCamera->ParamStringToVal(m_curParamID, strNewVal);
	NewParamRefresh(dVal);

}


void CConfigureDlg::OnSelchangePortList() 
{
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	m_pCamera->Freeze();
	if (parent->m_pImgConn) {
		delete parent->m_pImgConn;
		parent->m_pImgConn = NULL;
	}

	m_portNum = m_cbPortList.GetCurSel();	
	m_pCamera = m_pICap->GetCam(m_portNum);
	m_pICap->SetActiveCamera(m_pCamera);
	LoadCameraList();	
	GenerateParamGroupTree();
}


void CConfigureDlg::OnSaveUserCfg() 
{
	CloseEdit();
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);

	CFileDialog dlg(FALSE, "txt", NULL, OFN_HIDEREADONLY |  OFN_OVERWRITEPROMPT,
					"Config Files (*.txt)|*.txt||");

	if (dlg.DoModal() == IDOK)
	{
		// ::MessageBox(NULL, "It is possible to create duplicate camera names. Continue?",
		//			 "Save Camera Definition",  MB_YESNO);

		m_pICap->WriteConfigFile(dlg.GetPathName(),IFC_CFG_CURRENT_CAMERA);
	}
	
}

void CConfigureDlg::OnReadUserCfg() 
{
    CString strCamDbDir = CString(getenv("IFCCNF"));
	_chdir(strCamDbDir);
	CCameraMgrDlg dlg(TRUE, "txt", NULL,OFN_HIDEREADONLY ,
					  "Config Files (*.txt)|*.txt||",NULL,TRUE);

	if (dlg.DoModal() != IDOK)
		return;
	
	CConfiguratorView *parent=(CConfiguratorView*)m_pParent;
	m_pCamera->Freeze();
	if (parent->m_pImgConn) {
		delete parent->m_pImgConn;
		parent->m_pImgConn = NULL;
	}

	m_pICap->ReadUserConfigFile(dlg.GetPathName());
	m_pCamera = m_pICap->GetCam(m_portNum);
	LoadCameraList();
	
}

void CConfigureDlg::OnSelchangedPgrpTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_pParent->m_currentSelectedGroup = (IFC_PARAM_GROUP_TYPE)pNMTreeView->itemNew.lParam;
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

	popMenu.LoadMenu(nMenuID);

	CPoint posMouse;
	GetCursorPos(&posMouse);

	if (!m_pCamera->ParamGroupEditDlgExist(m_rClickGroup))
		popMenu.GetSubMenu(0)->EnableMenuItem(ID_GROUPMENU_EDITDIALOG,MF_GRAYED);

	if (m_pCamera->GroupIsApplicable(m_rClickGroup))
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
	m_rClickGroup = (IFC_PARAM_GROUP_TYPE)item.lParam;
	DoPopupMenu(IDR_MENU_GRP);
	
	*pResult = 0;
}


void CConfigureDlg::OnGroupMenuEditDialog() 
{
	m_pCamera->DoParamGroupEditDialog(m_rClickGroup,this);	
}


void CConfigureDlg::OnGroupMenuProperties() 
{
	CGroupProp dlg(this);
	dlg.DoModal();
}


void CConfigureDlg::OnGroupMenuApplicability() 
{
	char ReasonNotApplicable[MAX_PARAM_APPLICABLE_LEN];
	IFC_PARAM_GROUP_PROPS groupProps;

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

void CConfigureDlg::OnRuleEditor() 
{
	CRuleEdit dlg(this);
	int nResult = dlg.DoModal();

	if (nResult == IDOK) {

	}		
}

void CConfigureDlg::OnDblclkPgrpTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
