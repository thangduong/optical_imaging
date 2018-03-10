// VnRpcHnd.h: interface for the CVsRpcHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VnRpcHnd_H__481DED43_A9A8_11D4_B155_00105A0F576C__INCLUDED_)
#define AFX_VnRpcHnd_H__481DED43_A9A8_11D4_B155_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VnVidSrc.h>
#include <VnObject.h>


typedef struct {
	LPSTR funcName;
	void *funcPtr;
	
} VS_RPC_FUNC_MAP,*PVS_RPC_FUNC_MAP;


#define VS_FMAP_ENTRY(func) {#func,func}


#ifdef __cplusplus
extern "C" {
#endif

PVS_RPC_FUNC_MAP IVSCALL VsSysRpcTable(void);

double IVSCALL VsInvokeProxy(IDistribOS *vidSrc, VS_RPC_INVOKE_STRUCT *desc);

PVOID IVSCALL VsGetFunctionPtr( LPSTR funcName,DWORD popCount);
BOOL IVSCALL VsAddRpcDll( LPSTR dllName);
void IVSCALL VsSetProxyDetectFunc(IDistribOS *vidSrc);
BOOL IVSCALL VsVideoSrcIsProxyObj(IDistribOS *vidSrc);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

BOOL IVSCALL VsAddFunctionMapTable(PVS_RPC_FUNC_MAP funcMapTable, DWORD numNewFunctions=0);



class IVSV_EXT_API CVsRpcHandler : public CVnObject
{
public:
	CVsRpcHandler( IDistribOS *clientObj, HVSMESSAGE msgQueue);
	virtual ~CVsRpcHandler();

	DWORD ThreadProc(void);

	HVSEVENT m_serverShutdownEvent;
private:

	DWORD InvokeParamBlkFunc(VS_INVOKE_PARM_BLK_FUNC func, IDistribOS *pObj,BYTE *paramBlock,DWORD numParamBytes); 
	DWORD InvokeVsParamFunc(VS_INVOKE_VSPARAM_FUNC func, IDistribOS *pObj,DWORD numParams, VSPARAM params[]); 
	HANDLE m_hthread;
	volatile BOOLEAN m_shutdown;
	HANDLE m_shutdownEvent;	// fired when a thread shutdown requested


	IDistribOS *m_clientObj;
	HVSMESSAGE m_msgQueue;
	IStream *m_pStmPtr;
	IID m_derivedIfaceId;

};

#endif




#endif // !defined(AFX_VnRpcHnd_H__481DED43_A9A8_11D4_B155_00105A0F576C__INCLUDED_)
