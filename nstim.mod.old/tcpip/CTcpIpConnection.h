#ifndef CTCPIPCONNECTION_H
#define CTCPIPCONNECTION_H

#include "ITcpIpConnection.h"
#include "IPortCallback.h"
#include <Winsock.h>

#ifndef _T
#define	_T(x)	(x)
#endif

struct CallbackListNode
{
	IPortCallback* pCallback;
	CallbackListNode* pNext;
};

class CTcpIpConnection : public ITcpIpConnection
{
	friend class CTcpIpServer;
private:
	static long m_lNumSockets;

	sockaddr_in m_SockAddr;
	SOCKET m_hSocket;
	unsigned long m_cRefCnt;
	bool m_bSocketConnected;


	CallbackListNode* m_pCallbackListHead;
	CallbackListNode* m_pCallbackListTail;
	HANDLE m_hCallbackListMutex;

	static DWORD __stdcall StaticThreadFunc(void* user);
	void CycleSocket();

	void ForwardEvent(DWORD event, DWORD param1, DWORD param2);
protected:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// local implementation (unexposed...)
	////////////////////////////////////////////////////////////////////////////////////////////////////
	DWORD ThreadFunc();
public:
	CTcpIpConnection();
	virtual ~CTcpIpConnection();


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	ITcpIpConnection
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall Test() { return E_FAIL; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IPort
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall Open(const unsigned char __RPC_FAR *name);
	virtual HRESULT __stdcall Close();
	virtual HRESULT __stdcall IsOpen();
	virtual HRESULT __stdcall RegisterCallback(IPortCallback __RPC_FAR *pCallback);
	virtual HRESULT __stdcall UnregisterCallback(IPortCallback __RPC_FAR *pCallback);
	virtual HRESULT __stdcall Send(const unsigned char __RPC_FAR *pData, unsigned long dwDataSize);


	////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IUnknown
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* pObj);
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
};


#endif