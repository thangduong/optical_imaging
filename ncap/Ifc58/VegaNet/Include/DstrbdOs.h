// DstrbdOs.h: interface for the CDistributedOs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSTRBDOS_H__5AFB34B3_C9F0_11D4_B15D_00105A0F576C__INCLUDED_)
#define AFX_DSTRBDOS_H__5AFB34B3_C9F0_11D4_B15D_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VnObject.h>
#include <VnBase.h>
#include <VnVarLst.h>
#include <objthrd.h>
#include <VnMesage.h>
#include <VnRpcHnd.h>


typedef struct {
	DWORD dwThreadId;
	HVSMESSAGE msgQueue;
	HVSMESSAGE retQueue;
	DWORD hRpcServer;
	BOOL inCall;
	DWORD lastCallTime;
} VS_THREAD_REC,*PVS_THREAD_REC;

#define VS_MAX_THREAD_RECS 10


class IVSV_EXT_API CDistributedOs : public CVnObject  
{
public:
	CDistributedOs(IDistribOS *dosObj);
	virtual ~CDistributedOs();

	STDMETHOD(RegisterServer)(/*[string]*/ LPSTR serverDllName);
	STDMETHOD(RegisterRpcDll)(/*[string]*/ LPSTR dllName);
	STDMETHOD(InvokeRpc)(/*[in]*/VS_RPC_INVOKE_STRUCT *desc,  /*[in,size_is(stkBlkSize)]*/ DWORD *stkBlk, /*[in]*/DWORD stkBlkSize, /*[in,out,size_is(refParamNumBytes)]*/BYTE *refParams, /*[in]*/DWORD refParamNumBytes, /*[out]*/double *retVal);
	STDMETHOD(FileCopy)(/*[string]*/ LPSTR srcFileName, VS_FILESYS_DOMAIN_TYPE srcDomain, /*[string]*/ LPSTR dstFileName, VS_FILESYS_DOMAIN_TYPE dstDomain);
	STDMETHOD(CloseOs)(DWORD dwFlags);
	STDMETHOD(SetServerEvent)(/*[in]*/HVSEVENT event);
	STDMETHOD(WaitMessageOrEvents)(/*[in]*/HVSMESSAGE hMessage,/*[out,size_is(bytesAvailable),length_is(*numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,/*[in]*/DWORD waitTimeMilliSec,/*[in]*/DWORD numEvents,/*[in,size_is(numEvents)]*/HVSEVENT *events,/*[out]*/ DWORD *waitResult);
	STDMETHOD(DeleteServerEvent)(/*[in]*/HVSEVENT event);
	STDMETHOD(CreateServerEvent)(/*[out]*/HVSEVENT *event,VARIANT_BOOL bManualReset, VARIANT_BOOL bInitialState);
	void DeleteClientRpcServer(HVSMESSAGE retQueue, DWORD hRpcServer);
	STDMETHOD(InvokeClientVarAsync)(/*[string]*/ LPSTR funcName,/*[in]*/ DWORD numParams,/*[in,out,size_is(numParams)]*/ VSPARAM params[]);
	STDMETHOD(InvokeClientBlkAsync)(LPSTR funcName, BYTE *paramBlock, DWORD numParamBytes);
	PVS_THREAD_REC GetThreadsRpcQueue();
	STDMETHOD(SetSysMsgQ)(HVSMESSAGE hSysMsgQ, DWORD hRpcServer, HVSEVENT serverShutdownEvent);
	STDMETHOD(InvokeClientVar)(/*[string]*/ LPSTR funcName,/*[in]*/ DWORD numParams,/*[in,out,size_is(numParams)]*/ VSPARAM params[]);
	STDMETHOD(InvokeClientBlk)(/*[string]*/ LPSTR funcName,/*[in,out,size_is(numParamBytes)]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes);
	STDMETHOD(WaitAnyMessage)(/*[in]*/DWORD numMsgs,/*[in,size_is(numMsgs)]*/HVSMESSAGE *hMessages,/*[out]*/HVSMESSAGE *rcvMsg,/*[out,size_is(bytesAvailable),length_is(*numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,DWORD waitTimeMilliSec);
	STDMETHOD(DeleteMessage)(/*[in]*/HVSMESSAGE hMessage);
	STDMETHOD(WaitMessage)(/*[in]*/HVSMESSAGE hMessage,/*[out,size_is(numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,DWORD waitTimeMilliSec);
	STDMETHOD(SendMessage)(HVSMESSAGE hMessage,/*[in,size_is(numMessageBytes)]*/BYTE *message,/*[in]*/DWORD numMessageBytes);
	STDMETHOD(CreateMessage)(/*[out]*/HVSMESSAGE *hMessage);
	STDMETHOD(InvokeServerBlk)(/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,/*[in,out]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes,DWORD *retVal);
	STDMETHOD(InvokeServer)(/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,DWORD *retVal);
	STDMETHOD(DeleteServerThread)(HSERVERTHREAD hSrvThread);
	STDMETHOD(CreateServerThread)(HSERVERTHREAD *hSrvThread,/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,/*[in]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes);
	STDMETHOD(CreateObject)(REFCLSID rclsid,REFIID riid,/*[out]*/LPDISPATCH *obj);
	STDMETHOD(IsCallerLocal)(/*[string]*/ LPSTR nodeName, DWORD processId);


	BOOL m_isLocal;
private:
	HVSMESSAGE m_hSysMsgQ;
	DWORD m_hRpcServer;
	HVSEVENT m_sysRpcServerShutdownEvent;
	VS_THREAD_REC m_clientThreadRec[VS_MAX_THREAD_RECS];
	HANDLE m_threadRecMutex;

	CObjThread *m_serverThreads[VS_MAX_THREAD_RECS];
	CVnOS m_os;
	IDistribOS *m_dosObj;

};


template <class T, const IID* piid, const GUID* plibid = &CComModule::m_libid, WORD wMajor = 1,
WORD wMinor = 0, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IDistributedOsImpl : public T
{
public:
	typedef tihclass _tihclass;

	IDistributedOsImpl()
	{
		m_dstrbOs = new CDistributedOs(this);
	}

	~IDistributedOsImpl()
	{
		m_dstrbOs->CloseOs(0);
		delete m_dstrbOs;
	}


	STDMETHOD(GetDerivedIID)(/*[out]*/IID *derivedIID)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		*derivedIID = *_tih.m_pguid;
		return S_OK;
	}			

	STDMETHOD(RegisterRpcDll)(/*[string]*/ LPSTR dllName)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->RegisterRpcDll(dllName);
	}

	STDMETHOD(RegisterServer)(/*[string]*/ LPSTR serverDllName)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->RegisterServer(serverDllName);
	}


	STDMETHOD(InvokeRpc)(/*[in]*/VS_RPC_INVOKE_STRUCT *desc,  /*[in,size_is(stkBlkSize)]*/ DWORD *stkBlk, /*[in]*/DWORD stkBlkSize, /*[in,out,size_is(refParamNumBytes)]*/BYTE *refParams, /*[in]*/DWORD refParamNumBytes, /*[out]*/double *retVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeRpc(desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal);
	}



	STDMETHOD(FileCopy)(/*[string]*/ LPSTR srcFileName, VS_FILESYS_DOMAIN_TYPE srcDomain, /*[string]*/ LPSTR dstFileName, VS_FILESYS_DOMAIN_TYPE dstDomain)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->FileCopy(srcFileName,srcDomain,dstFileName,dstDomain);
	}


	STDMETHOD(CloseOs)(DWORD dwFlags)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->CloseOs(dwFlags);
	}

	STDMETHOD(SetServerEvent)(/*[in]*/HVSEVENT event)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->SetServerEvent(event);
	}

	STDMETHOD(WaitMessageOrEvents)(/*[in]*/HVSMESSAGE hMessage,/*[out,size_is(bytesAvailable),length_is(*numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,/*[in]*/DWORD waitTimeMilliSec,/*[in]*/DWORD numEvents,/*[in,size_is(numEvents)]*/HVSEVENT *events,/*[out]*/ DWORD *waitResult)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->WaitMessageOrEvents(hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult);
	}

	STDMETHOD(DeleteServerEvent)(/*[in]*/HVSEVENT event)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->DeleteServerEvent(event);
	}

	STDMETHOD(CreateServerEvent)(/*[out]*/HVSEVENT *event,VARIANT_BOOL bManualReset, VARIANT_BOOL bInitialState)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->CreateServerEvent(event,bManualReset,bInitialState);
	}

	STDMETHOD(InvokeClientVarAsync)(/*[string]*/ LPSTR funcName,/*[in]*/ DWORD numParams,/*[in,out,size_is(numParams)]*/ VSPARAM params[])
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeClientVarAsync(funcName,numParams,params);
	}

	STDMETHOD(InvokeClientBlkAsync)(LPSTR funcName, BYTE *paramBlock, DWORD numParamBytes)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeClientBlkAsync(funcName,paramBlock,numParamBytes);
	}

	STDMETHOD(SetSysMsgQ)(HVSMESSAGE hSysMsgQ, DWORD hRpcServer, HVSEVENT serverShutdownEvent)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->SetSysMsgQ(hSysMsgQ,hRpcServer,serverShutdownEvent);
	}

	STDMETHOD(InvokeClientVar)(/*[string]*/ LPSTR funcName,/*[in]*/ DWORD numParams,/*[in,out,size_is(numParams)]*/ VSPARAM params[])
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeClientVar(funcName,numParams,params);
	}

	STDMETHOD(InvokeClientBlk)(/*[string]*/ LPSTR funcName,/*[in,out,size_is(numParamBytes)]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeClientBlk(funcName,paramBlock,numParamBytes);
	}

	STDMETHOD(WaitAnyMessage)(/*[in]*/DWORD numMsgs,/*[in,size_is(numMsgs)]*/HVSMESSAGE *hMessages,/*[out]*/HVSMESSAGE *rcvMsg,/*[out,size_is(bytesAvailable),length_is(*numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,DWORD waitTimeMilliSec)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->WaitAnyMessage(numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec);
	}

	STDMETHOD(DeleteMessage)(/*[in]*/HVSMESSAGE hMessage)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->DeleteMessage( hMessage);
	}

	STDMETHOD(WaitMessage)(/*[in]*/HVSMESSAGE hMessage,/*[out,size_is(numMessageBytes)]*/BYTE *message,/*[out]*/DWORD *numMessageBytes,/*[in]*/DWORD bytesAvailable,DWORD waitTimeMilliSec)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->WaitMessage( hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec);
	}

	STDMETHOD(SendMessage)(HVSMESSAGE hMessage,/*[in,size_is(numMessageBytes)]*/BYTE *message,/*[in]*/DWORD numMessageBytes)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->SendMessage( hMessage,message,numMessageBytes);
	}

	STDMETHOD(CreateMessage)(/*[out]*/HVSMESSAGE *hMessage)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->CreateMessage( hMessage);
	}

	STDMETHOD(InvokeServerBlk)(/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,/*[in,out]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes,DWORD *retVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeServerBlk( dllName,funcName,paramBlock,numParamBytes,retVal );
	}

	STDMETHOD(InvokeServer)(/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,DWORD *retVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->InvokeServer( dllName,funcName,retVal );
	}


	STDMETHOD(DeleteServerThread)(HSERVERTHREAD hSrvThread)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->DeleteServerThread( hSrvThread );
	}

	STDMETHOD(CreateServerThread)(HSERVERTHREAD *hSrvThread,/*[string]*/ LPSTR dllName,/*[string]*/ LPSTR funcName,/*[in]*/BYTE *paramBlock,/*[in]*/DWORD numParamBytes)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->CreateServerThread( hSrvThread,dllName,funcName,paramBlock, numParamBytes);
	}

	STDMETHOD(CreateObject)(REFCLSID rclsid,REFIID riid,/*[out]*/LPDISPATCH *obj)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->CreateObject( rclsid,riid,obj);
	}

	STDMETHOD(IsCallerLocal)(/*[string]*/ LPSTR nodeName, DWORD processId)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		return m_dstrbOs->IsCallerLocal(nodeName,processId);
	}

protected:
	static _tihclass _tih;

	CDistributedOs *m_dstrbOs;

};


template <class T, const IID* piid, const GUID* plibid, WORD wMajor, WORD wMinor, class tihclass>
IDistributedOsImpl<T, piid, plibid, wMajor, wMinor, tihclass>::_tihclass
IDistributedOsImpl<T, piid, plibid, wMajor, wMinor, tihclass>::_tih =
{piid, plibid, wMajor, wMinor, NULL, 0, NULL, 0};



#endif // !defined(AFX_DSTRBDOS_H__5AFB34B3_C9F0_11D4_B15D_00105A0F576C__INCLUDED_)
