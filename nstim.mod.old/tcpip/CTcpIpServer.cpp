// CTcpIpServer.cpp: implementation of the CTcpIpServer class.
//
//////////////////////////////////////////////////////////////////////

#include "CTcpIpServer.h"
#include "CTcpIpConnection.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpIpServer::CTcpIpServer() : m_cRefCnt(1)
{
	// this isn't very tight.., there can be a fall through, but we won't worry about that for now
	if (InterlockedIncrement(&CTcpIpConnection::m_lNumSockets) == 1)
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

	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_hSocket == INVALID_SOCKET)
		MessageBox(NULL, _T("Can't create a socket handle"), _T("CTcpIpServer::CTcpIpServer"), MB_ICONERROR);


	m_pCallbackListHead = NULL;
	m_pCallbackListTail = NULL;
	m_bServerStarted = false;

	m_hCallbackListMutex = CreateMutex(NULL, false, NULL);

}

CTcpIpServer::~CTcpIpServer()
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		while (m_pCallbackListHead)
		{
			ServerCallbackListNode* pNode = m_pCallbackListHead;
			m_pCallbackListHead = m_pCallbackListHead->pNext;

			pNode->pCallback->Release();
			delete pNode;
		}
	}

	CloseHandle(m_hCallbackListMutex);


	if (InterlockedDecrement(&CTcpIpConnection::m_lNumSockets) == 0)
		WSACleanup();

}

DWORD __stdcall CTcpIpServer::StaticThreadFunc(void* user)
{
	CTcpIpServer* pThis = (CTcpIpServer*)user;
	if (pThis)
		return pThis->ThreadFunc();
	else
		return -1;
}

DWORD CTcpIpServer::ThreadFunc()
{
	CTcpIpConnection* pCon;

	bool bDone = false;

	ForwardEvent(PSE_SERVER_START, 0, 0);

	while (!bDone)
	{
		pCon = new CTcpIpConnection;
		int size = sizeof(pCon->m_SockAddr);
		pCon->m_hSocket = accept(m_hSocket, (struct sockaddr*)&(pCon->m_SockAddr), &size);
		if (pCon->m_hSocket != INVALID_SOCKET)
		{
			pCon->m_bSocketConnected = true;
			ForwardEvent(PSE_ON_CONNECT, (DWORD)pCon, 0);
			DWORD tid;
			CreateThread(NULL, 0, CTcpIpConnection::StaticThreadFunc, pCon, 0, &tid);
			pCon->Release();
		}
		else
		{
			pCon->Release();
			bDone = true;
		}
	}
	ForwardEvent(PSE_SERVER_STOP, 0, 0);
	return 0;
}


void CTcpIpServer::ForwardEvent(DWORD event, DWORD param1, DWORD param2)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		ServerCallbackListNode* pNode = m_pCallbackListHead;
		while (pNode)
		{
			pNode->pCallback->OnPortEvent(this, event, param1, param2);
			pNode = pNode->pNext;
		}
		ReleaseMutex(m_hCallbackListMutex);
	}
}

HRESULT __stdcall CTcpIpServer::RegisterCallback(IPortServerCallback* pCallback)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		// make sure it's not already in the list (bad data struct and searc algo, but ah...)
		bool bIsInList = false;
		ServerCallbackListNode* pNode = m_pCallbackListHead;
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
			pNode = new ServerCallbackListNode;
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

HRESULT __stdcall CTcpIpServer::UnregisterCallback(IPortServerCallback* pCallback)
{
	if (WaitForSingleObject(m_hCallbackListMutex, INFINITE) == WAIT_OBJECT_0)
	{
		bool bIsInList = false;
		ServerCallbackListNode* pNode = m_pCallbackListHead;
		ServerCallbackListNode* pNodeBefore = NULL;
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

HRESULT __stdcall CTcpIpServer::IsStarted()
{
	return m_bServerStarted ? S_OK : E_FAIL;
}

HRESULT __stdcall CTcpIpServer::Start(const unsigned char* name)
{
	if (FAILED(IsStarted()))
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
		
		if (bind(m_hSocket, (sockaddr*)&m_SockAddr, sizeof(m_SockAddr)) == SOCKET_ERROR)
			return E_FAIL;
		else
		{
			listen(m_hSocket, 10);
			m_bServerStarted = true;
			// TODO: finalize this code...
			DWORD tid;
			CreateThread(NULL, 0, StaticThreadFunc, this, 0, &tid);
			return S_OK;
		}
	}
	else
		return E_FAIL;
}

HRESULT __stdcall CTcpIpServer::Stop()
{
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//	IUnknown Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT __stdcall CTcpIpServer::QueryInterface(REFIID iid, LPVOID* pObj)
{
	(*pObj) = NULL;
	if (iid == IID_IUnknown)
	{
		(*pObj) = static_cast<IUnknown*>(this);
	}
	else if (iid == IID_IPortServer)
	{
		(*pObj) = static_cast<IPortServer*>(this);
	}
	else if (iid == IID_ITcpIpServer)
	{
		(*pObj) = static_cast<ITcpIpServer*>(this);
	}
	if (*pObj)
		return S_OK;
	else 
		return E_NOINTERFACE;
}


ULONG __stdcall CTcpIpServer::AddRef()
{
	return InterlockedIncrement((long*)&m_cRefCnt);
}


ULONG __stdcall CTcpIpServer::Release()
{
	if (InterlockedDecrement((long*)&m_cRefCnt) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_cRefCnt;
}

