// CSmsyncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "smsync.h"
#include "CSmsyncDlg.h"
#include <cbw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmsyncDlg dialog
void CSmsyncDlg::SaveCfg(){
	m_IniFile.WriteInt("ADC", "Sampling Rate", samplingRate);
	m_IniFile.WriteInt("ADC", "Low Channel",lowChan); 
	m_IniFile.WriteInt("ADC", "High Channel",highChan);  
	m_IniFile.WriteInt("ADC", "Buffer Size", numPoints/((highChan - lowChan + 1) * samplingRate));
	m_IniFile.WriteInt("ADC", "BoardId", boardId);

	m_IniFile.WriteString("SETTINGS", "Data Directory", fileDir);
	m_IniFile.WriteInt("TCPIP", "Port", port);
}

CSmsyncDlg::CSmsyncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmsyncDlg::IDD, pParent), m_iCount(1), m_IniFile("smsync.ini")
{
	//{{AFX_DATA_INIT(CSmsyncDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	fbaseCount = 0;
	m_bInAdcProcess = false;
	stimOnPosition = 0;
	scCorrection = 0;
}

void CSmsyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmsyncDlg)
	DDX_Control(pDX, IDC_BITC7, m_Bitc7);
	DDX_Control(pDX, IDC_BITC6, m_Bitc6);
	DDX_Control(pDX, IDC_BITC5, m_Bitc5);
	DDX_Control(pDX, IDC_BITC4, m_Bitc4);
	DDX_Control(pDX, IDC_BITC3, m_Bitc3);
	DDX_Control(pDX, IDC_BITC2, m_Bitc2);
	DDX_Control(pDX, IDC_BITC1, m_Bitc1);
	DDX_Control(pDX, IDC_BITC0, m_Bitc0);
	DDX_Control(pDX, IDC_BIT7, m_Bit7);
	DDX_Control(pDX, IDC_BIT6, m_Bit6);
	DDX_Control(pDX, IDC_BIT5, m_Bit5);
	DDX_Control(pDX, IDC_BIT4, m_Bit4);
	DDX_Control(pDX, IDC_BIT3, m_Bit3);
	DDX_Control(pDX, IDC_BIT2, m_Bit2);
	DDX_Control(pDX, IDC_BIT1, m_Bit1);
	DDX_Control(pDX, IDC_BIT0, m_Bit0);
	DDX_Control(pDX, IDC_STATUS, m_Status);
	DDX_Control(pDX, IDC_STOP, m_StopBtn);
	DDX_Control(pDX, IDC_GO, m_GoBtn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSmsyncDlg, CDialog)
	//{{AFX_MSG_MAP(CSmsyncDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmsyncDlg message handlers

BOOL CSmsyncDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	boardId = m_IniFile.ReadInt("ADC", "BoardId");
	samplingRate = m_IniFile.ReadInt("ADC", "Sampling Rate"); //25000;			// 25k request
	lowChan = m_IniFile.ReadInt("ADC", "Low Channel"); 
	highChan = m_IniFile.ReadInt("ADC", "High Channel"); 
	int bufferSize = m_IniFile.ReadInt("ADC", "Buffer Size");;
	numPoints = (highChan - lowChan + 1) * samplingRate * bufferSize;
	hWinBuff = new char[2*numPoints];//cbWinBufAlloc(numPoints);
	bRunning = false;
	iRange = BIP10VOLTS;
	threshold = 2.5;
	for (int i = 0; i < (sizeof(chanState)/sizeof(chanState[0])); i++) {
		chanState[i] = -1;
		chanStateChangeTime[i] = 0;
	}

	fileIndex = 0;

	strcpy(fileBase, "calibx0101");
	strcpy(fileDir, m_IniFile.ReadString("SETTINGS", "Data Directory")); //"c:\\temp\\");
	sampleCntr = 0;

	fp = 0;
	bStoring = false;

	// allocate memory and junk for the ADC
	port = m_IniFile.ReadInt("TCPIP", "Port");
	char temp[512];
	bool bResult = false;
	char* pBindAddr = "0.0.0.0";
	sprintf(temp, "%s:%d", pBindAddr, port);
	m_Server.RegisterCallback(this);
	m_iCmdBufferSize = 1024*10;						// 10k buffer
	m_pCmdBuffer = new char[m_iCmdBufferSize];
	m_iCmdBufferMark = 0;
	bResult = (m_Server.Start((const unsigned char*)temp) == S_OK) ? true : false;
	numChan = (highChan - lowChan + 1);

	m_spikeCoderCap.SetCapReceiver(this);
	m_spikeCoderCap.Connect(m_IniFile.ReadString("SETTINGS", "Spike Coder"));
	m_spikeCoderCap.SendCmd("master");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmsyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmsyncDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmsyncDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSmsyncDlg::ProcessAdcData() {
	if (bRunning) {
		m_bInAdcProcess = true;
		short status;
		long curCount;
		long curIndex;
		cbGetStatus(boardId, &status, &curCount, &curIndex, AIFUNCTION);
		
//		char temp[512];
//		sprintf(temp, "lastCount = %d status = %d curCount = %d curIndex = %d\r\n", lastCount, status, curCount, curIndex);
//		OutputDebugString(temp);


		if (curCount == lastCount)  {
		}
		else if ((curCount==-1) || (curIndex==-1)) {
			TRACE("NOTHING YET\r\n");
		}
		else  {
//			TRACE(temp);
			unsigned short* pData = (unsigned short*)(hWinBuff);
			int curLoc = lastIndex;

			int chan;
			while (curLoc != curIndex) {
				chan = curLoc % numChan;
				int lastChanState = chanState[chan];
				float value;
				unsigned short x = pData[curLoc];
				cbToEngUnits(boardId, iRange, x, &value);
				chanState[chan] = value > threshold;
					
				if (lastChanState != chanState[chan]) {
					chanStateChangeTime[chan] = sampleCntr;
					switch(chan) {
					case 0:
						if (m_Bitc0.GetState())
							m_Bit0.SetState(chanState[chan]);
						stimOnPosition = sampleCntr;
						break;
					case 1:
						if (m_Bitc1.GetState())
							m_Bit1.SetState(chanState[chan]);
						break;
					case 2:
						if (m_Bitc2.GetState())
							m_Bit2.SetState(chanState[chan]);
						break;
					case 3:
						if (m_Bitc3.GetState())
							m_Bit3.SetState(chanState[chan]);
						break;
					case 4:
						if (m_Bitc4.GetState())
							m_Bit4.SetState(chanState[chan]);
						break;
					case 5:
						if (m_Bitc5.GetState())
							m_Bit5.SetState(chanState[chan]);
						break;
					case 6:
						if (m_Bitc6.GetState())
							m_Bit6.SetState(chanState[chan]);
						break;
					case 7:
						if (m_Bitc7.GetState())
							m_Bit7.SetState(chanState[chan]);
						break;
					}
					if (bStoring) {
						unsigned long valueToStore = sampleCntr + (chanState[chan] <<28) + ((unsigned long)chan << 29);
						if (fp) {
							fwrite(&valueToStore, 1, 4, fp);
							fflush(fp);
						}
					}
//					sprintf(temp, "chan %d state changed from %d to %d\r\n", chan,lastChanState, chanState[chan]);
//					TRACE(temp);
				}
				if (chan == 0) {
					sampleCntr++;
					if (sampleCntr > 0xffffff)
						sampleCntr = 0;
				}
				curLoc = curLoc + 1;
				curLoc = curLoc % numPoints;
			}
//			sprintf(temp, "%d\r\n", pData[0]);
//			TRACE(temp);
			 
			lastStatus = status;
			lastCount = curCount;
			lastIndex = curIndex;
		}
		if ((status == 0) & (bRunning))
			bRunning = false;
		m_bInAdcProcess = false;
	}
}

void CSmsyncDlg::StartFile() {
	char temp[512];
	sprintf(temp, "rawfilename%s", fileBase);
	m_spikeCoderCap.SendCmd(temp);

	sprintf(spFilePath, "%s\\%s.spk", fileDir, fileBase); 
	m_spikeCoderCap.StartCap(spFilePath);

	sprintf(spFilePath2, "%s\\%s.fspk", fileDir, fileBase); 
	m_spkOut = fopen(spFilePath2, "wb");

	m_Status.SetWindowText("Capturing");
	sprintf(filePath, "%s\\%s.sync", fileDir, fileBase); 
	fp = fopen(filePath, "wb");
	DSFHdr hdr;
	hdr.highChan = highChan;
	hdr.lowChan = lowChan;
	memcpy(&hdr.magic, "SYNC", 4);
	hdr.numBytesToSkip = 0;
	hdr.samplingRate = samplingRate;
	hdr.threshold = threshold;

	fwrite(&hdr,  1, sizeof(hdr), fp);
	for (int i = lowChan; i <= highChan; i++) {
		unsigned long valueToStore = chanStateChangeTime[i] + (chanState[i]?(1 <<28):0) + ((unsigned long)i << 29);
		if (fp) {
			fwrite(&valueToStore, 1, 4, fp);
			fflush(fp);
		}
	}
	bStoring = true;
}

void CSmsyncDlg::StopFile() {
	bStoring = false;
	FILE* fp2 = fp; fp = 0;
	fclose(fp2);
	fclose(m_spkOut);
	m_spkOut = 0;
	m_spikeCoderCap.StopCap();
	stimOnPosition = 0;
}


void CSmsyncDlg::OnGo() 
{
	m_spikeCoderCap.SendCmd("go");
	if (bRunning) {
		OnStop();
	}
	lastStatus = 0;
	lastIndex = 0;
	lastCount = 0;
	int res = cbAInScan(boardId, lowChan, highChan, numPoints, &samplingRate, iRange, hWinBuff ,BACKGROUND | CONTINUOUS);
	bRunning = true;
	m_Status.SetWindowText("Running");
	m_GoBtn.EnableWindow(FALSE);
	m_StopBtn.EnableWindow(TRUE);
}

void CSmsyncDlg::OnDestroy() 
{
	SaveCfg();
	OnStop();
	cbWinBufFree(hWinBuff);
	delete m_pCmdBuffer; 
	PostQuitMessage(0);
	CDialog::OnDestroy();
}

void CSmsyncDlg::OnStop() 
{
	if (bRunning) {
		m_spikeCoderCap.SendCmd("stop");
		if (bStoring)
			StopFile();
		m_Status.SetWindowText("Stopped");
		bRunning = false;
		cbStopBackground(boardId, AIFUNCTION);
		m_GoBtn.EnableWindow(TRUE);
		m_StopBtn.EnableWindow(FALSE);
	}
	
}

void CSmsyncDlg::OnClose() 
{
	OnStop();
	CDialog::OnClose();
	DestroyWindow();
}

void CSmsyncDlg::OnSpike(int chan, int id, int junk, unsigned long time) {
	if (bStoring) {
		time = time - scCorrection;

		// store data!
		if (m_spkOut) {
			int type = 0;
			fwrite(&type, 1, sizeof(type), m_spkOut);
			fwrite(&chan, 1, sizeof(chan), m_spkOut);
			fwrite(&id, 1, sizeof(id), m_spkOut);
			fwrite(&junk, 1, sizeof(junk), m_spkOut);
			fwrite(&time, 1, sizeof(time), m_spkOut);
		}
	}
}

void CSmsyncDlg::OnDp(int chan, unsigned long time) {
	if (bStoring) {
		while (stimOnPosition == 0){ 
			Sleep(100);
		}
		scCorrection = (int)time - (int)stimOnPosition;
		time = time - scCorrection;

		// store data!
		int junk = 0;
		int id = 0;
		if (m_spkOut) {
			int type = 1;
			fwrite(&type, 1, sizeof(type), m_spkOut);
			fwrite(&chan, 1, sizeof(chan), m_spkOut);
			fwrite(&id, 1, sizeof(id), m_spkOut);
			fwrite(&junk, 1, sizeof(junk), m_spkOut);
			fwrite(&time, 1, sizeof(time), m_spkOut);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Command processing code
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ULONG __stdcall CSmsyncDlg::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CSmsyncDlg::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;

	if (iid == IID_IPortServerCallback)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else if (iid == IID_IPortCallback)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else if (iid == IID_IUnknown)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	return hr;
}

ULONG __stdcall CSmsyncDlg::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

void CSmsyncDlg::OnCommand(IPort* pPort, char* pCmd, int len)
{
	if (pCmd == 0)
		return;
	// parse the command...
	// first, make the string lowercase
	for (int i = 0; i < len; i++)
		pCmd[i] = tolower(pCmd[i]);

	char* cmd = strtok(pCmd, " \r\n\t");
	if (cmd == 0)
		return;
	if (strcmp(cmd, "go") == 0) {
		if (!bRunning) {
			OnGo();
		}
	}
	else if (strcmp(cmd, "ping") == 0) {
		pPort->Send((unsigned char*)"pong!", 5);
	}
	else if (strcmp(cmd, "cap") == 0) {
		if (bRunning && (!bStoring)) {
			char* fbase = strtok(0, " \r\n\t");
			if (fbase)
				strcpy(fileBase, fbase);
			else 
			{
				sprintf(fileBase, "unknown-%d", fbaseCount++);
			}
			StartFile();
		}
	}
	else if (strcmp(cmd, "stopcap") == 0) {
		if (bRunning && (bStoring)) {
			StopFile();
		}
	}
	else if (strcmp(cmd, "stop") == 0) {
		if (bRunning) {
//			if (bStoring)
//				StopFile();
			OnStop();
		}
	}

	OutputDebugString(pCmd);
}

HRESULT __stdcall CSmsyncDlg::OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2)
{
	OutputDebugString("on port event\r\n");
	if (caller == &m_Server)
	{
		if (event == PSE_ON_CONNECT)
		{
			IPort* pPort = (IPort*)param1;
			pPort->AddRef();
			m_PortList.AddTail(pPort);
			pPort->RegisterCallback(this);
		}
	}
	else
	{
		if (event == PE_DATA_ARRIVED)
		{
			for (int i = 0; i < param2; i++)
			{
				m_pCmdBuffer[m_iCmdBufferMark] = (((char*)param1)[i]);
				if (m_pCmdBuffer[m_iCmdBufferMark] == '\n')
				{
					while ((m_pCmdBuffer[m_iCmdBufferMark] == '\n') ||
						(m_pCmdBuffer[m_iCmdBufferMark] == '\r'))
						m_pCmdBuffer[m_iCmdBufferMark--] = 0;
					IPort* pPort;
					caller->QueryInterface(IID_IPort, (void**)&pPort);
					OnCommand(pPort, m_pCmdBuffer, m_iCmdBufferMark);
					pPort->Release();
					m_iCmdBufferMark = 0;
				}
				else
				{
					m_iCmdBufferMark++;
					if (m_iCmdBufferMark >= m_iCmdBufferSize)
					{	// in case of overflow
						m_iCmdBufferMark = 0;	
					}
				}
			}
		}
	}

	return S_OK;
}

void CSmsyncDlg::OnFileExit() 
{
	if (bStoring)
		AfxMessageBox("Can't exit while storing data");
	else if (bRunning) 
	{
		if (MessageBoxEx(GetSafeHwnd(), "ADC is running.  Do you want to exit anyway?", "Running", MB_YESNO, 0) == IDYES) {
			OnStop();
			PostQuitMessage(0);
		}
	}
	else
		PostQuitMessage(0);
}
