// CScCap.h: interface for the CScCap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSCCAP_H__C37C8885_28CE_4DB2_815A_C26C1E06A0EE__INCLUDED_)
#define AFX_CSCCAP_H__C37C8885_28CE_4DB2_815A_C26C1E06A0EE__INCLUDED_

#include "CTcpIpConnection.h"
#include "IPortCallback.h"
#include <stdio.h>

struct IScCapReceiver {
	virtual void OnSpike(int chan, int id, int junk, unsigned long time) = 0;
	virtual void OnDp(int chan, unsigned long time) = 0;
};

// outfile format:
//	<tag> <size> <param> <param> <param>...
#define	TAG_DP		0
#define	TAG_SPIKE	1

class CScCap  : public IPortCallback
{
	CTcpIpConnection m_Connection;
	unsigned long m_cRefCnt;
	FILE* m_outFile;
	IScCapReceiver* m_pCapReceiver;
public:
	CScCap();
	virtual ~CScCap();

	bool Connect(const char* server);
	bool Disconnect();
	bool SendCmd(const char* cmd);
	bool StartCap(const char* filename);
	bool StopCap();
	void SetCapReceiver(IScCapReceiver* pReceiver);
	IScCapReceiver* GetCapReceiver();

	virtual HRESULT __stdcall OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2);
	
	// events!
	virtual void OnSpike(int chan, int id, int junk, unsigned long time);
	virtual void OnDp(int chan, unsigned long time);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IUnknown
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* pObj);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();


};

#endif // !defined(AFX_CSCCAP_H__C37C8885_28CE_4DB2_815A_C26C1E06A0EE__INCLUDED_)
