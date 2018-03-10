// CNCapCmdEngine.h: interface for the CNCapCmdEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CNCAPCMDENGINE_H
#define CNCAPCMDENGINE_H

#include "CNCapProfile.h"
#include "IPortServerCallback.h"
#include "IPortCallback.h"
#include "IPort.h"
#include "CTcpIpServer.h"
#include "CList.h"
#include "CNCapProfile.h"
#include "CNCapEngine.h"

class CNCapCmdEngine : 
	public IPortServerCallback, 
	public IPortCallback  
{
	long m_iCount;
	CTcpIpServer m_Server;
	CList<IPort*, IPort*> m_PortList;
	int m_iCmdBufferSize;
	char* m_pCmdBuffer;
	int m_iCmdBufferMark;
	CNCapEngine* m_pEngine;
	CNCapProfile* m_pProfile;

	void OnCommand(IPort* pPort, char* pCmd, int len);
public:
	CNCapCmdEngine();
	virtual ~CNCapCmdEngine();


	bool Init(CNCapProfile* pProfile, CNCapEngine* pEngine);

	virtual HRESULT __stdcall OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2);

	virtual HRESULT __stdcall Test() { return S_OK; }

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

};

#endif
