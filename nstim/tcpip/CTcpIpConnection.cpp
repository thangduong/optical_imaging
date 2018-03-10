#include <string.h>
#include "CTcpIpConnection.h"

long CTcpIpConnection::m_lNumSockets = 0;

void CTcpIpConnection::CycleSocket()
{
	// TODO: enter critical section here...
	closesocket(m_hSocket);
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_hSocket == INVALID_SOCKET)
		MessageBox(NULL, _T("Can't create a socket handle"), _T("CTcpIpConnection::CycleSocket"), MB_ICONERROR);
}

void CTcpIpConnection::ForwardEvent(DWORD event, DWORD param1, DWORD param2)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		CallbackListNode* pNode = m_pCallbackListHead;
		while (pNode)
		{
			pNode->pCallback->OnPortEvent(this, event, param1, param2);
			pNode = pNode->pNext;
		}
		ReleaseMutex(m_hCallbackListMutex);
	}
}


CTcpIpConnection::CTcpIpConnection() :
	m_cRefCnt(1)
{
	// this isn't very tight.., there can be a fall through, but we won't worry about that for now
	if (InterlockedIncrement(&m_lNumSockets) == 1)
	{
		// initialize WSA
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
 
		wVersionRequested = MAKEWORD( 1, 1 );
 
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
		 /* Tell the user that we could not find a usable */
		 /* WinSock DLL.   */
			MessageBox(NULL, _T("WSA Startup failed"), _T("CTcpIpConnection::CTcpIpConnection"), MB_ICONERROR);
		}
 
		/* Confirm that the WinSock DLL supports 1.1.*/
		/* Note that if the DLL supports versions greater */
		/* than 1.1 in addition to 1.1, it will still return */
		/* 1.1 in wVersion since that is the version we */
		/* requested.   */
 
		if ( LOBYTE( wsaData.wVersion ) != 1 ||
			HIBYTE( wsaData.wVersion ) != 1 ) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.   */
			WSACleanup( );
			return; 
		}
 
		/* The WinSock DLL is acceptable. Proceed. */
 	}

	m_bSocketConnected = false;
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hSocket == INVALID_SOCKET)
		MessageBox(NULL, _T("Can't create a socket handle"), _T("CTcpIpConnection::CTcpIpConnection"), MB_ICONERROR);


	m_pCallbackListHead = NULL;
	m_pCallbackListTail = NULL;


	m_hCallbackListMutex = CreateMutex(NULL, false, NULL);

}


CTcpIpConnection::~CTcpIpConnection()
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		while (m_pCallbackListHead)
		{
			CallbackListNode* pNode = m_pCallbackListHead;
			m_pCallbackListHead = m_pCallbackListHead->pNext;

			pNode->pCallback->Release();
			delete pNode;
		}
	}

	if (SUCCEEDED(IsOpen()))
		Close();
	closesocket(m_hSocket);
	CloseHandle(m_hCallbackListMutex);

	if (InterlockedDecrement(&m_lNumSockets) == 0)
		WSACleanup();
}

DWORD __stdcall CTcpIpConnection::StaticThreadFunc(void* user)
{
	CTcpIpConnection* pThis = (CTcpIpConnection*)user;
	if (pThis)
		return pThis->ThreadFunc();
	else
		return -1;
}

DWORD CTcpIpConnection::ThreadFunc()
{
	fd_set read;

	int iSelectResult;
	bool bDone = false;

	ForwardEvent(PE_PORT_OPENED, 0, 0);

	while (!bDone)
	{
		FD_ZERO(&read);
		FD_SET(m_hSocket, &read);
		iSelectResult = select(0, &read, NULL, NULL, NULL);

		if (FD_ISSET(m_hSocket, &read))
		{
 			long ulPendingSize = 0;
			if ((ioctlsocket(m_hSocket, FIONREAD, (DWORD*)&ulPendingSize) == SOCKET_ERROR) ||
				(ulPendingSize == 0))
			{
				shutdown(m_hSocket, 0);
				m_bSocketConnected = false;
				CycleSocket();
				bDone = true;
				// TODO: propagate an event saying connection is close
			}
			else
			{
//				DEBUGMSG(true, (_T("ulPendingSize = %d\n"), ulPendingSize));
				char* buff = new char[ulPendingSize];
				DWORD bytesReceived = recv(m_hSocket, buff, ulPendingSize, 0);
				ForwardEvent(PE_DATA_ARRIVED, (DWORD)buff, bytesReceived); //(DWORD)ulPendingSize);

				/*
#ifdef DEBUG
				TCHAR* tcbuff = new TCHAR[ulPendingSize+1];
				for (int i = 0; i < ulPendingSize; i++)
					tcbuff[i] = (TCHAR)buff[i];
				tcbuff[ulPendingSize] = 0;
				DEBUGMSG(true, (tcbuff));
				delete [] tcbuff;
#endif
				*/
				delete [] buff;
			}
		}
		else
		{
			bDone = true;
		}
	}
	ForwardEvent(PE_PORT_CLOSED, 0, 0);
#ifdef DEBUGMSG
	DEBUGMSG(true, (_T("receive thread exiting\n")));
#endif
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//	IPort Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT __stdcall CTcpIpConnection::Open(const unsigned char __RPC_FAR *name)
{
	if (FAILED(IsOpen()))
	{
		if (strlen((const char*)name) > 511)
		{
			MessageBox(NULL, _T("Port name is too long"), _T("CTcpIpConnection::Open"), MB_ICONERROR);
			return E_FAIL;
		}

		char addr[512];
		char* port = NULL;

		strcpy(addr, (const char*)name);
		for (unsigned i = 0; i < strlen(addr); i++)
		{
			if (addr[i] == ':')
			{
				addr[i] = 0;
				port = &addr[i+1];
				break;
			}
		}

		if (port == NULL)
		{
			MessageBox(NULL, _T("Port name invalid (must be in the form <IP/Name>:<port>)"), _T("CTcpIpConnection::Open"), MB_ICONERROR);
			return E_FAIL;
		}

		memset(&m_SockAddr, 0, sizeof(m_SockAddr));
		m_SockAddr.sin_addr.S_un.S_addr = inet_addr(addr);

		LPHOSTENT pHost;

		if (m_SockAddr.sin_addr.S_un.S_addr == INADDR_NONE)
		{
			pHost = gethostbyname(addr);
			if (pHost)
				m_SockAddr.sin_addr.S_un.S_addr = *(DWORD*)(*pHost->h_addr_list);
		}

		m_SockAddr.sin_port = htons(atoi(port));
		m_SockAddr.sin_family = AF_INET;
		
		if (connect(m_hSocket, (sockaddr*)&m_SockAddr, sizeof(m_SockAddr)) == SOCKET_ERROR)
			return E_FAIL;
		else
		{
			m_bSocketConnected = true;
			// TODO: finalize this code...
			DWORD tid;
			CreateThread(NULL, 0, StaticThreadFunc, this, 0, &tid);
			return S_OK;
		}
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CTcpIpConnection::Close()
{
	HRESULT hResult = E_FAIL;
	if (SUCCEEDED(IsOpen()))
	{
		shutdown(m_hSocket, 0);
		CycleSocket();
		m_bSocketConnected = false;
	}
	return S_OK;
}

HRESULT __stdcall CTcpIpConnection::IsOpen()
{
	return m_bSocketConnected ? S_OK : E_FAIL;
}

HRESULT __stdcall CTcpIpConnection::RegisterCallback(IPortCallback __RPC_FAR *pCallback)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		// make sure it's not already in the list (bad data struct and searc algo, but ah...)
		bool bIsInList = false;
		CallbackListNode* pNode = m_pCallbackListHead;
		while (pNode)
		{
			if (pNode->pCallback == pCallback)
			{
				bIsInList = true;
				break;
			}
			pNode = pNode->pNext;
		}

		if (!bIsInList)
		{
			pNode = new CallbackListNode;
			pNode->pCallback = pCallback;
			pNode->pCallback->AddRef();
			pNode->pNext = NULL;
			if (m_pCallbackListHead)
			{
				m_pCallbackListTail->pNext = pNode;
				m_pCallbackListTail = pNode;
			}
			else
			{
				m_pCallbackListHead = m_pCallbackListTail = pNode;
			}
		}
		ReleaseMutex(m_hCallbackListMutex);
	}
	return S_OK;
}

HRESULT __stdcall CTcpIpConnection::UnregisterCallback(IPortCallback __RPC_FAR *pCallback)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		bool bIsInList = false;
		CallbackListNode* pNode = m_pCallbackListHead;
		CallbackListNode* pNodeBefore = NULL;
		while (pNode)
		{
			if (pNode->pCallback == pCallback)
			{
				bIsInList = true;
				break;
			}
			pNodeBefore = pNode;
			pNode = pNode->pNext;
		}
		if (bIsInList)
		{
			if (!((pNode == m_pCallbackListHead) || (pNode == m_pCallbackListTail)))
			{
				pNodeBefore->pNext = pNode->pNext;
			}
			else
			{
				if (pNode == m_pCallbackListHead)
				{
					m_pCallbackListHead = pNode->pNext;
				}
				if (pNode == m_pCallbackListTail)
				{
					m_pCallbackListTail = pNodeBefore;
				}
			}

			pNode->pCallback->Release();
			delete pNode;
		}
		ReleaseMutex(m_hCallbackListMutex);
	}
	return S_OK;
}

HRESULT __stdcall CTcpIpConnection::Send(const unsigned char __RPC_FAR *pData, unsigned long dwDataSize)
{
	HRESULT hResult = E_FAIL;
	if (SUCCEEDED(IsOpen()))
		hResult = ((unsigned long)send(m_hSocket, (char*)pData, dwDataSize, 0) == dwDataSize) ? S_OK : E_FAIL;
	return hResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//	IUnknown Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT __stdcall CTcpIpConnection::QueryInterface(REFIID iid, LPVOID* pObj)
{
	(*pObj) = NULL;
	if (iid == IID_IUnknown)
	{
		(*pObj) = static_cast<IUnknown*>(this);
	}
	else if (iid == IID_IPort)
	{
		(*pObj) = static_cast<IPort*>(this);
	}
	else if (iid == IID_ITcpIpConnection)
	{
		(*pObj) = static_cast<ITcpIpConnection*>(this);
	}
	if (*pObj)
	{
		((IUnknown*)(*pObj))->AddRef();
		return S_OK;
	}
	else 
		return E_NOINTERFACE;
}


ULONG __stdcall CTcpIpConnection::AddRef()
{
	return InterlockedIncrement((long*)&m_cRefCnt);
}


ULONG __stdcall CTcpIpConnection::Release()
{
	if (InterlockedDecrement((long*)&m_cRefCnt) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_cRefCnt;
}

