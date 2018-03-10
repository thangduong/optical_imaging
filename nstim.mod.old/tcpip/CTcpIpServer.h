// CTcpIpServer.h: interface for the CTcpIpServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTCPIPSERVER_H__85B5E33B_8F02_4593_BF0C_12CB153CA468__INCLUDED_)
#define AFX_CTCPIPSERVER_H__85B5E33B_8F02_4593_BF0C_12CB153CA468__INCLUDED_

#include "IPortServer.h"
#include "ITcpIpServer.h"

struct ServerCallbackListNode
{
	IPortServerCallback* pCallback;
	ServerCallbackListNode* pNext;
};

class CTcpIpServer : public ITcpIpServer
{
private:
	unsigned long m_cRefCnt;
	ServerCallbackListNode* m_pCallbackListHead;
	ServerCallbackListNode* m_pCallbackListTail;
	HANDLE m_hCallbackListMutex;

	sockaddr_in m_SockAddr;
	SOCKET m_hSocket;
	bool m_bServerStarted;


	void ForwardEvent(DWORD event, DWORD param1, DWORD param2);

	
	static DWORD __stdcall StaticThreadFunc(void* user);
	DWORD ThreadFunc();

public:
	CTcpIpServer();
	virtual ~CTcpIpServer();
	
	virtual HRESULT __stdcall Test() { return S_OK; }


	virtual HRESULT __stdcall UnregisterCallback(IPortServerCallback* pCallback);
	virtual HRESULT __stdcall RegisterCallback(IPortServerCallback* pCallback);	
	virtual HRESULT __stdcall Start(const unsigned char* name);
	virtual HRESULT __stdcall Stop();
	virtual HRESULT __stdcall IsStarted();


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IUnknown
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* pObj);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();

};

#endif // !defined(AFX_CTCPIPSERVER_H__85B5E33B_8F02_4593_BF0C_12CB153CA468__INCLUDED_)
