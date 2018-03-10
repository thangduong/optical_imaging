// CSmsyncDlg.h : header file
//

#if !defined(AFX_CSMSYNCDLG_H__3F9371DD_0010_43B3_A790_570860533490__INCLUDED_)
#define AFX_CSMSYNCDLG_H__3F9371DD_0010_43B3_A790_570860533490__INCLUDED_

#include <winsock.h>
#include "IPortServerCallback.h"
#include "IPortCallback.h"
#include "IPort.h"
#include "CTcpIpServer.h"
#include "CList.h"
#include "CIniFile.h"
#include "CScCap.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push,1)
struct DSFHdr {
	unsigned long magic;
	unsigned long samplingRate;
	unsigned short lowChan;
	unsigned short highChan;
	unsigned long numBytesToSkip;
	float threshold;
};
#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CSmsyncDlg dialog

class CSmsyncDlg : public CDialog, public IPortServerCallback, public IPortCallback, IScCapReceiver
{
	bool m_bInAdcProcess;
	long m_iCount;
	int numChan;
	CTcpIpServer m_Server;
	CList<IPort*, IPort*> m_PortList;
	int m_iCmdBufferSize;
	char* m_pCmdBuffer;
	int m_iCmdBufferMark;
	CIniFile m_IniFile;
	int fbaseCount;
	DWORD port;
	CScCap m_spikeCoderCap;
	char spFilePath[512];
	char spFilePath2[512];
	unsigned long stimOnPosition;
	int scCorrection;

	FILE* m_spkOut;
// Construction
public:
	CSmsyncDlg(CWnd* pParent = NULL);	// standard constructor

	void ProcessAdcData();
	void StartFile();
	void StopFile();

	virtual void OnSpike(int chan, int id, int junk, unsigned long time);
	virtual void OnDp(int chan, unsigned long time);

	virtual HRESULT __stdcall OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2);

	virtual HRESULT __stdcall Test() { return S_OK; }

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

	void OnCommand(IPort* pPort, char* pCmd, int len);
// Dialog Data
	//{{AFX_DATA(CSmsyncDlg)
	enum { IDD = IDD_SMSYNC_DIALOG };
	CButton	m_Bitc7;
	CButton	m_Bitc6;
	CButton	m_Bitc5;
	CButton	m_Bitc4;
	CButton	m_Bitc3;
	CButton	m_Bitc2;
	CButton	m_Bitc1;
	CButton	m_Bitc0;
	CButton	m_Bit7;
	CButton	m_Bit6;
	CButton	m_Bit5;
	CButton	m_Bit4;
	CButton	m_Bit3;
	CButton	m_Bit2;
	CButton	m_Bit1;
	CButton	m_Bit0;
	CStatic	m_Status;
	CButton	m_StopBtn;
	CButton	m_GoBtn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmsyncDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void SaveCfg();

	HICON m_hIcon;
	FILE* fp;
	bool bStoring;

	int fileIndex;
	char fileBase[512];
	char fileDir[512];
	char filePath[512];

	int boardId;
	short lastStatus;
	long lastCount;
	long lastIndex;
	int chanState[16];
	int chanStateChangeTime[16];
	float threshold;
	
	bool bRunning;

	long samplingRate;
	void* hWinBuff;
	unsigned long lowChan;
	unsigned long highChan;
	unsigned long numPoints;
	int iRange;


	// this is the tick count -- it restarts for new data file
	unsigned long sampleCntr;	// this value can't exceed 0xffffff.  it wraps over if exceeds.


	// Generated message map functions
	//{{AFX_MSG(CSmsyncDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGo();
	afx_msg void OnDestroy();
	afx_msg void OnStop();
	afx_msg void OnClose();
	afx_msg void OnFileExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSMSYNCDLG_H__3F9371DD_0010_43B3_A790_570860533490__INCLUDED_)
