/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 10 11:23:57 2004
 */
/* Compiler settings for D:\Ifc4201\VegaNet\include\VnVidSrc.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __VnVidSrc_h__
#define __VnVidSrc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDistribOS_FWD_DEFINED__
#define __IDistribOS_FWD_DEFINED__
typedef interface IDistribOS IDistribOS;
#endif 	/* __IDistribOS_FWD_DEFINED__ */


#ifndef __IVideoSrc_FWD_DEFINED__
#define __IVideoSrc_FWD_DEFINED__
typedef interface IVideoSrc IVideoSrc;
#endif 	/* __IVideoSrc_FWD_DEFINED__ */


#ifndef __IVidSrcCfg_FWD_DEFINED__
#define __IVidSrcCfg_FWD_DEFINED__
typedef interface IVidSrcCfg IVidSrcCfg;
#endif 	/* __IVidSrcCfg_FWD_DEFINED__ */


#ifndef __VideoSrc_FWD_DEFINED__
#define __VideoSrc_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoSrc VideoSrc;
#else
typedef struct VideoSrc VideoSrc;
#endif /* __cplusplus */

#endif 	/* __VideoSrc_FWD_DEFINED__ */


#ifndef __VidSrcCfg_FWD_DEFINED__
#define __VidSrcCfg_FWD_DEFINED__

#ifdef __cplusplus
typedef class VidSrcCfg VidSrcCfg;
#else
typedef struct VidSrcCfg VidSrcCfg;
#endif /* __cplusplus */

#endif 	/* __VidSrcCfg_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "vidsrct.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDistribOS_INTERFACE_DEFINED__
#define __IDistribOS_INTERFACE_DEFINED__

/* interface IDistribOS */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDistribOS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C396993-C9E7-11D4-B15D-00105A0F576C")
    IDistribOS : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateServerThread( 
            /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteServerThread( 
            HSERVERTHREAD hSrvThread) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeServer( 
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [out] */ DWORD __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeServerBlk( 
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [out] */ DWORD __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateMessage( 
            /* [out] */ HVSMESSAGE __RPC_FAR *hMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendMessage( 
            HVSMESSAGE hMessage,
            /* [size_is][in] */ BYTE __RPC_FAR *message,
            /* [in] */ DWORD numMessageBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitMessage( 
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteMessage( 
            /* [in] */ HVSMESSAGE hMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitAnyMessage( 
            /* [in] */ DWORD numMsgs,
            /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
            /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeClientBlk( 
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeClientVar( 
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSysMsgQ( 
            HVSMESSAGE hSysMsgQ,
            DWORD hRpcServer,
            HVSEVENT serverShutdownEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeClientBlkAsync( 
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeClientVarAsync( 
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateServerEvent( 
            /* [out] */ HVSEVENT __RPC_FAR *event,
            /* [in] */ VARIANT_BOOL bManualReset,
            /* [in] */ VARIANT_BOOL bInitialState) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteServerEvent( 
            /* [in] */ HVSEVENT event) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitMessageOrEvents( 
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            /* [in] */ DWORD waitTimeMilliSec,
            /* [in] */ DWORD numEvents,
            /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
            /* [out] */ DWORD __RPC_FAR *waitResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetServerEvent( 
            /* [in] */ HVSEVENT event) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseOs( 
            DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileCopy( 
            /* [string] */ LPSTR srcFileName,
            VS_FILESYS_DOMAIN_TYPE srcDomain,
            /* [string] */ LPSTR dstFileName,
            VS_FILESYS_DOMAIN_TYPE dstDomain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvokeRpc( 
            /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
            /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
            /* [in] */ DWORD stkBlkSize,
            /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
            /* [in] */ DWORD refParamNumBytes,
            /* [out] */ double __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterRpcDll( 
            /* [string] */ LPSTR dllName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDerivedIID( 
            /* [out] */ IID __RPC_FAR *derivedIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterServer( 
            /* [string] */ LPSTR serverDllName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsCallerLocal( 
            /* [string] */ LPSTR nodeName,
            DWORD processId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDistribOSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDistribOS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDistribOS __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDistribOS __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerThread )( 
            IDistribOS __RPC_FAR * This,
            /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerThread )( 
            IDistribOS __RPC_FAR * This,
            HSERVERTHREAD hSrvThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServer )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServerBlk )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMessage )( 
            IDistribOS __RPC_FAR * This,
            /* [out] */ HVSMESSAGE __RPC_FAR *hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IDistribOS __RPC_FAR * This,
            HVSMESSAGE hMessage,
            /* [size_is][in] */ BYTE __RPC_FAR *message,
            /* [in] */ DWORD numMessageBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessage )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMessage )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitAnyMessage )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ DWORD numMsgs,
            /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
            /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlk )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVar )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysMsgQ )( 
            IDistribOS __RPC_FAR * This,
            HVSMESSAGE hSysMsgQ,
            DWORD hRpcServer,
            HVSEVENT serverShutdownEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlkAsync )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVarAsync )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerEvent )( 
            IDistribOS __RPC_FAR * This,
            /* [out] */ HVSEVENT __RPC_FAR *event,
            /* [in] */ VARIANT_BOOL bManualReset,
            /* [in] */ VARIANT_BOOL bInitialState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerEvent )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessageOrEvents )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            /* [in] */ DWORD waitTimeMilliSec,
            /* [in] */ DWORD numEvents,
            /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
            /* [out] */ DWORD __RPC_FAR *waitResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetServerEvent )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseOs )( 
            IDistribOS __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileCopy )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR srcFileName,
            VS_FILESYS_DOMAIN_TYPE srcDomain,
            /* [string] */ LPSTR dstFileName,
            VS_FILESYS_DOMAIN_TYPE dstDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeRpc )( 
            IDistribOS __RPC_FAR * This,
            /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
            /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
            /* [in] */ DWORD stkBlkSize,
            /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
            /* [in] */ DWORD refParamNumBytes,
            /* [out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterRpcDll )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR dllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDerivedIID )( 
            IDistribOS __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *derivedIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            IDistribOS __RPC_FAR * This,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterServer )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR serverDllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCallerLocal )( 
            IDistribOS __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            DWORD processId);
        
        END_INTERFACE
    } IDistribOSVtbl;

    interface IDistribOS
    {
        CONST_VTBL struct IDistribOSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistribOS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDistribOS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDistribOS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDistribOS_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDistribOS_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDistribOS_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDistribOS_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDistribOS_CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)

#define IDistribOS_DeleteServerThread(This,hSrvThread)	\
    (This)->lpVtbl -> DeleteServerThread(This,hSrvThread)

#define IDistribOS_InvokeServer(This,dllName,funcName,retVal)	\
    (This)->lpVtbl -> InvokeServer(This,dllName,funcName,retVal)

#define IDistribOS_InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)	\
    (This)->lpVtbl -> InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)

#define IDistribOS_CreateMessage(This,hMessage)	\
    (This)->lpVtbl -> CreateMessage(This,hMessage)

#define IDistribOS_SendMessage(This,hMessage,message,numMessageBytes)	\
    (This)->lpVtbl -> SendMessage(This,hMessage,message,numMessageBytes)

#define IDistribOS_WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IDistribOS_DeleteMessage(This,hMessage)	\
    (This)->lpVtbl -> DeleteMessage(This,hMessage)

#define IDistribOS_WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IDistribOS_InvokeClientBlk(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlk(This,funcName,paramBlock,numParamBytes)

#define IDistribOS_InvokeClientVar(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVar(This,funcName,numParams,params)

#define IDistribOS_SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)	\
    (This)->lpVtbl -> SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)

#define IDistribOS_InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)

#define IDistribOS_InvokeClientVarAsync(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVarAsync(This,funcName,numParams,params)

#define IDistribOS_CreateServerEvent(This,event,bManualReset,bInitialState)	\
    (This)->lpVtbl -> CreateServerEvent(This,event,bManualReset,bInitialState)

#define IDistribOS_DeleteServerEvent(This,event)	\
    (This)->lpVtbl -> DeleteServerEvent(This,event)

#define IDistribOS_WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)	\
    (This)->lpVtbl -> WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)

#define IDistribOS_SetServerEvent(This,event)	\
    (This)->lpVtbl -> SetServerEvent(This,event)

#define IDistribOS_CloseOs(This,dwFlags)	\
    (This)->lpVtbl -> CloseOs(This,dwFlags)

#define IDistribOS_FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)	\
    (This)->lpVtbl -> FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)

#define IDistribOS_InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)	\
    (This)->lpVtbl -> InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)

#define IDistribOS_RegisterRpcDll(This,dllName)	\
    (This)->lpVtbl -> RegisterRpcDll(This,dllName)

#define IDistribOS_GetDerivedIID(This,derivedIID)	\
    (This)->lpVtbl -> GetDerivedIID(This,derivedIID)

#define IDistribOS_CreateObject(This,rclsid,riid,obj)	\
    (This)->lpVtbl -> CreateObject(This,rclsid,riid,obj)

#define IDistribOS_RegisterServer(This,serverDllName)	\
    (This)->lpVtbl -> RegisterServer(This,serverDllName)

#define IDistribOS_IsCallerLocal(This,nodeName,processId)	\
    (This)->lpVtbl -> IsCallerLocal(This,nodeName,processId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_CreateServerThread_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
    /* [string] */ LPSTR dllName,
    /* [string] */ LPSTR funcName,
    /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes);


void __RPC_STUB IDistribOS_CreateServerThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_DeleteServerThread_Proxy( 
    IDistribOS __RPC_FAR * This,
    HSERVERTHREAD hSrvThread);


void __RPC_STUB IDistribOS_DeleteServerThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeServer_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR dllName,
    /* [string] */ LPSTR funcName,
    /* [out] */ DWORD __RPC_FAR *retVal);


void __RPC_STUB IDistribOS_InvokeServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeServerBlk_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR dllName,
    /* [string] */ LPSTR funcName,
    /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes,
    /* [out] */ DWORD __RPC_FAR *retVal);


void __RPC_STUB IDistribOS_InvokeServerBlk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_CreateMessage_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [out] */ HVSMESSAGE __RPC_FAR *hMessage);


void __RPC_STUB IDistribOS_CreateMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_SendMessage_Proxy( 
    IDistribOS __RPC_FAR * This,
    HVSMESSAGE hMessage,
    /* [size_is][in] */ BYTE __RPC_FAR *message,
    /* [in] */ DWORD numMessageBytes);


void __RPC_STUB IDistribOS_SendMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_WaitMessage_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ HVSMESSAGE hMessage,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
    /* [out] */ DWORD __RPC_FAR *numMessageBytes,
    /* [in] */ DWORD bytesAvailable,
    DWORD waitTimeMilliSec);


void __RPC_STUB IDistribOS_WaitMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_DeleteMessage_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ HVSMESSAGE hMessage);


void __RPC_STUB IDistribOS_DeleteMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_WaitAnyMessage_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ DWORD numMsgs,
    /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
    /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
    /* [out] */ DWORD __RPC_FAR *numMessageBytes,
    /* [in] */ DWORD bytesAvailable,
    DWORD waitTimeMilliSec);


void __RPC_STUB IDistribOS_WaitAnyMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeClientBlk_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR funcName,
    /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes);


void __RPC_STUB IDistribOS_InvokeClientBlk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeClientVar_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR funcName,
    /* [in] */ DWORD numParams,
    /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]);


void __RPC_STUB IDistribOS_InvokeClientVar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_SetSysMsgQ_Proxy( 
    IDistribOS __RPC_FAR * This,
    HVSMESSAGE hSysMsgQ,
    DWORD hRpcServer,
    HVSEVENT serverShutdownEvent);


void __RPC_STUB IDistribOS_SetSysMsgQ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeClientBlkAsync_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR funcName,
    /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes);


void __RPC_STUB IDistribOS_InvokeClientBlkAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeClientVarAsync_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR funcName,
    /* [in] */ DWORD numParams,
    /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]);


void __RPC_STUB IDistribOS_InvokeClientVarAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_CreateServerEvent_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [out] */ HVSEVENT __RPC_FAR *event,
    /* [in] */ VARIANT_BOOL bManualReset,
    /* [in] */ VARIANT_BOOL bInitialState);


void __RPC_STUB IDistribOS_CreateServerEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_DeleteServerEvent_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ HVSEVENT event);


void __RPC_STUB IDistribOS_DeleteServerEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_WaitMessageOrEvents_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ HVSMESSAGE hMessage,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
    /* [out] */ DWORD __RPC_FAR *numMessageBytes,
    /* [in] */ DWORD bytesAvailable,
    /* [in] */ DWORD waitTimeMilliSec,
    /* [in] */ DWORD numEvents,
    /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
    /* [out] */ DWORD __RPC_FAR *waitResult);


void __RPC_STUB IDistribOS_WaitMessageOrEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_SetServerEvent_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ HVSEVENT event);


void __RPC_STUB IDistribOS_SetServerEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_CloseOs_Proxy( 
    IDistribOS __RPC_FAR * This,
    DWORD dwFlags);


void __RPC_STUB IDistribOS_CloseOs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_FileCopy_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR srcFileName,
    VS_FILESYS_DOMAIN_TYPE srcDomain,
    /* [string] */ LPSTR dstFileName,
    VS_FILESYS_DOMAIN_TYPE dstDomain);


void __RPC_STUB IDistribOS_FileCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_InvokeRpc_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
    /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
    /* [in] */ DWORD stkBlkSize,
    /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
    /* [in] */ DWORD refParamNumBytes,
    /* [out] */ double __RPC_FAR *retVal);


void __RPC_STUB IDistribOS_InvokeRpc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_RegisterRpcDll_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR dllName);


void __RPC_STUB IDistribOS_RegisterRpcDll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_GetDerivedIID_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [out] */ IID __RPC_FAR *derivedIID);


void __RPC_STUB IDistribOS_GetDerivedIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_CreateObject_Proxy( 
    IDistribOS __RPC_FAR * This,
    REFCLSID rclsid,
    REFIID riid,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);


void __RPC_STUB IDistribOS_CreateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_RegisterServer_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR serverDllName);


void __RPC_STUB IDistribOS_RegisterServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDistribOS_IsCallerLocal_Proxy( 
    IDistribOS __RPC_FAR * This,
    /* [string] */ LPSTR nodeName,
    DWORD processId);


void __RPC_STUB IDistribOS_IsCallerLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDistribOS_INTERFACE_DEFINED__ */


#ifndef __IVideoSrc_INTERFACE_DEFINED__
#define __IVideoSrc_INTERFACE_DEFINED__

/* interface IVideoSrc */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVideoSrc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B2FC362-775F-11D4-B132-00105A0F576C")
    IVideoSrc : public IDistribOS
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [string] */ LPSTR videoSrcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
            /* [in] */ VARIANT_BOOL isLocal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfigFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConfigFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabWaitFrameRead( 
            /* [in] */ DWORD grabID,
            VS_FRAME_ENCODE encodeKind,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *bytesRead,
            int FrameSeqNum,
            DWORD milliseconds,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *extAttr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Freeze( 
            /* [defaultvalue] */ DWORD grabID = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateInterruptObject( 
            VS_ICAP_INTR_EVENT intrEvent,
            VARIANT_BOOL eventSetting,
            /* [retval][out] */ HVSINTERRUPT __RPC_FAR *hIntrObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AcqParamSupported( 
            VS_ACQ_PARAMS_TYPE paramID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAcqParam( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ double __RPC_FAR *value,
            /* [defaultvalue] */ DWORD index = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAcqParam( 
            VS_ACQ_PARAMS_TYPE paramID,
            double value,
            /* [defaultvalue] */ DWORD index = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParamCaps( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ PVS_PARAM_CAPS lpParamCaps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstParam( 
            DWORD paramGroupMask,
            VARIANT_BOOL includeChildGroups,
            /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *firstParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextParam( 
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD paramGroupMask,
            VARIANT_BOOL includeChildGroups,
            /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *nextParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstParamGroup( 
            VS_PARAM_GROUP_TYPE parentGroupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *firstParmGrp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextParamGroup( 
            VS_PARAM_GROUP_TYPE groupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *nextParmGrp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGroupProperties( 
            VS_PARAM_GROUP_TYPE groupID,
            /* [out] */ PVS_PARAM_GROUP_PROPS lpGroupProps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParentGroup( 
            VS_PARAM_GROUP_TYPE childGroupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *parentGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstEnumArg( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ VS_ENUM_ARG __RPC_FAR *arg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextEnumArg( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out][in] */ VS_ENUM_ARG __RPC_FAR *arg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsArgSupported( 
            VS_ACQ_PARAMS_TYPE paramID,
            double arg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClosestArgSupported( 
            VS_ACQ_PARAMS_TYPE paramID,
            double arg,
            /* [retval][out] */ double __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArgName( 
            VS_ACQ_PARAMS_TYPE paramID,
            double dArg,
            /* [string][out][in] */ LPSTR argName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetArgValue( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [string] */ LPSTR szArgName,
            /* [retval][out] */ double __RPC_FAR *argVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLutFunction( 
            VS_LUTID_TYPE lutID,
            VSLUTFUNC func,
            DWORD __RPC_FAR *constants,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadLutByteBuf( 
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [size_is][out] */ BYTE __RPC_FAR *buf,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_FULL_WORD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteLutByteBuf( 
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [size_is][in] */ BYTE __RPC_FAR *buf,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_FULL_WORD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteLutToFile( 
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [string] */ LPSTR szFileName,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_FULL_WORD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadLutFromFile( 
            VS_LUTID_TYPE lutID,
            /* [string] */ LPSTR szFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadLutLoc( 
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            VS_LUT_PORTION_TYPE lutPortion,
            /* [retval][out] */ DWORD __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteLutLoc( 
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD val,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_FULL_WORD) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LinearizeLut( 
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FloodLUT( 
            VS_LUTID_TYPE lutID,
            DWORD val,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvertLut( 
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ThresholdLut( 
            VS_LUTID_TYPE lutID,
            const DWORD dwThreshold,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetLut( 
            VS_LUTID_TYPE lutID,
            const long lOffset,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BitReverseLinearLut( 
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion = VS_LUT_INTELLI_WIDTH) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RgbToHsiLUT( 
            VS_LUTID_TYPE lutID,
            VS_LUT_PORTION_TYPE lutPortion) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLUTCaps( 
            /* [out] */ LPVS_LUTCAP caps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLutPathPage( 
            VS_LUTID_TYPE lutID,
            VS_LUT_PIX_SIZE_TYPE pxSize,
            DWORD pageNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLutHostPage( 
            VS_LUTID_TYPE lutID,
            VS_LUT_PIX_SIZE_TYPE pxSize,
            DWORD pageNum,
            VARIANT_BOOL leftJustify) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowGen( 
            int x,
            int y,
            int dx,
            int dy) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCameraType( 
            /* [string] */ LPSTR camName,
            /* [defaultvalue] */ VARIANT_BOOL updateHW = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextCamType( 
            /* [out][in][string] */ LPSTR nextCamType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstCamType( 
            /* [out][in][string] */ LPSTR firstCamType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabOn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabMultiDest( 
            /* [out] */ HVSGRAB __RPC_FAR *grabID,
            DWORD dwOptions,
            /* [size_is][in] */ pBYTE __RPC_FAR dests[  ],
            int ringNumFrames,
            int totalNumFrames,
            /* [defaultvalue] */ int x = 0,
            /* [defaultvalue] */ int y = 0,
            /* [defaultvalue] */ int dx = 0,
            /* [defaultvalue] */ int dy = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabAoi( 
            /* [out] */ HVSGRAB __RPC_FAR *grabID,
            DWORD dwOptions,
            DWORD dest,
            int ringNumFrames,
            int totalNumFrames,
            /* [in] */ LPVS_AOI_DESC aoiDesc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabLock( 
            HVSGRAB grabID,
            int seqNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabRelease( 
            HVSGRAB grabID,
            int seqNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabWaitFrame( 
            HVSGRAB grabID,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *frameAddr,
            int FrameSeqNum,
            DWORD milliseconds,
            VARIANT_BOOL lock,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DecodeFrame( 
            BYTE __RPC_FAR *src,
            DWORD numSrcBytes,
            VS_FRAME_ENCODE frameEncode,
            DWORD dx,
            DWORD dy,
            VS_COLOR color,
            DWORD bitsPerPixel,
            BYTE __RPC_FAR *dest) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabGetExtAttr( 
            HVSGRAB grabID,
            int seqNum,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Snap( 
            /* [size_is][out] */ pBYTE dest,
            DWORD bytesPerFrame,
            /* [defaultvalue] */ int x = 0,
            /* [defaultvalue] */ int y = 0,
            /* [defaultvalue] */ int dx = 0,
            /* [defaultvalue] */ int dy = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SeqSnap( 
            /* [size_is][out] */ pBYTE dest,
            DWORD bytesPerFrame,
            int numFrames,
            /* [defaultvalue] */ int x = 0,
            /* [defaultvalue] */ int y = 0,
            /* [defaultvalue] */ int dx = 0,
            /* [defaultvalue] */ int dy = 0,
            /* [defaultvalue] */ DWORD dwMilliseconds = -1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetZoom( 
            float xZoom,
            float yZoom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetZoomCaps( 
            /* [out] */ LPVS_ZOOMCAP lpCaps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadArea( 
            int x,
            int y,
            int dx,
            int dy,
            /* [size_is][out] */ BYTE __RPC_FAR *destadr,
            /* [defaultvalue] */ DWORD dest_dx = 0,
            /* [defaultvalue] */ DWORD readOptions = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LineReverseRead( 
            int x,
            int y,
            int dx,
            int dy,
            int destlinebytes,
            /* [size_is][out] */ BYTE __RPC_FAR *destadr,
            /* [defaultvalue] */ DWORD readOptions = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadDestPitchArea( 
            int x,
            int y,
            int dx,
            int dy,
            int destlinebytes,
            DWORD physdest,
            /* [defaultvalue] */ DWORD readOptions = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAttr( 
            /* [out] */ LPVS_CAM_ATTR lpAttr,
            /* [defaultvalue] */ VARIANT_BOOL zoomCorrected = TRUE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReadColorRemap( 
            VARIANT_BOOL bEnabled) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadReg( 
            REGID reg,
            /* [retval][out] */ DWORD __RPC_FAR *regVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteReg( 
            REGID reg,
            DWORD val) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParamValToString( 
            VS_ACQ_PARAMS_TYPE paramID,
            double dVal,
            /* [string][out][in] */ LPSTR szResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParamStringToVal( 
            VS_ACQ_PARAMS_TYPE paramID,
            /* [string] */ LPSTR szVal,
            /* [retval][out] */ double __RPC_FAR *retVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUIParamUpdate( 
            /* [out][in] */ double __RPC_FAR *dVal,
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParamGroupEditDlgExist( 
            VS_PARAM_GROUP_TYPE GroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoParamGroupEditDialog( 
            VS_PARAM_GROUP_TYPE GroupID,
            VS_ACQ_PARAMS_TYPE focalParam) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParamIsApplicable( 
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD index,
            /* [string][out][in] */ LPSTR ReasonNotApplicable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GroupIsApplicable( 
            VS_PARAM_GROUP_TYPE groupID,
            /* [string][out][in] */ LPSTR ReasonNotApplicable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PrintParamAttributes( 
            VS_ACQ_PARAMS_TYPE paramID,
            VS_PARAM_GROUP_TYPE parentGroupID,
            /* [string] */ LPSTR file) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CameraIsReserved( 
            /* [string] */ LPSTR camName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TransformSupported( 
            VS_TRANSFORM_TYPE eTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTransform( 
            VS_TRANSFORM_TYPE eTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentTransform( 
            /* [retval][out] */ VS_TRANSFORM_TYPE __RPC_FAR *currentTransform) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryUICameraType( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPortNum( 
            /* [retval][out] */ DWORD __RPC_FAR *portNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProps( 
            /* [out] */ VSPROPS __RPC_FAR *props) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPortNum( 
            DWORD portNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNumPorts( 
            /* [retval][out] */ DWORD __RPC_FAR *numPorts) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddCameraType( 
            LPSTR strNewCamName,
            LPSTR strExistCamName,
            /* [retval][out] */ DWORD __RPC_FAR *defHhandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Grab( 
            /* [out] */ ULONG __RPC_FAR *grabID,
            /* [in] */ DWORD dwOptions,
            DWORD dest,
            int ringNumFrames,
            int totalNumFrames,
            /* [defaultvalue] */ int x = 0,
            /* [defaultvalue] */ int y = 0,
            /* [defaultvalue] */ int dx = 0,
            /* [defaultvalue] */ int dy = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVideoStream( 
            PVS_STREAM_PARAMS params,
            /* [retval][out] */ HVIDSTREAMSRV __RPC_FAR *vidStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteVideoStream( 
            HVIDSTREAMSRV vidStream) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitStreamPacket( 
            HVIDSTREAMSRV srvStream,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *bytesRead,
            DWORD milliseconds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDriverHandle( 
            /* [retval][out] */ DWORD __RPC_FAR *handle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteCameraFile( 
            /* [string] */ LPSTR cameraFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain,
            /* [string] */ LPSTR cameraName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadCamerasInFile( 
            /* [string] */ LPSTR cameraFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadUserConfigFile( 
            /* [string] */ LPSTR configFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteUserConfigFile( 
            /* [string] */ LPSTR configFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectOutputTo( 
            DWORD OutputId,
            IDispatch __RPC_FAR *sink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ProduceTo( 
            /* [in] */ LPDISPATCH imgNode,
            DWORD srcOutputId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDetachProducer( 
            IDispatch __RPC_FAR *node,
            DWORD srcOutputId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateProducer( 
            DWORD srcOutputId,
            VS_REF_VAL_KIND enQKind,
            VARIANT_BOOL areRemote) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GrabToImgNode( 
            VS_FRAME_ENCODE remoteUseEncode,
            DWORD dwOptions,
            int NumFrames,
            /* [defaultvalue] */ int x = 0,
            /* [defaultvalue] */ int y = 0,
            /* [defaultvalue] */ int dx = 0,
            /* [defaultvalue] */ int dy = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FreezeImgNode( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseEleRef( 
            DWORD srcOutputId,
            HBYREFELE deRefHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitInterrupt( 
            HVSINTERRUPT hIntrObj,
            DWORD milliSeconds) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInterruptObject( 
            HVSINTERRUPT hIntrObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearInterrupt( 
            HVSINTERRUPT hIntrObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetReadCaps( 
            /* [out] */ VS_READCAP __RPC_FAR *lpCaps) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [defaultvalue] */ DWORD dwFlags = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OutportStrobeVal( 
            VS_LEVEL_TYPE val,
            /* [defaultvalue] */ DWORD channelNum = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OutportVal( 
            DWORD val,
            DWORD channelNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InportMode( 
            BOOL strobed,
            VS_EDGE_TYPE latchEdge,
            /* [defaultvalue] */ DWORD channelNum = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InportVal( 
            DWORD channelNum,
            DWORD __RPC_FAR *valRead) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InportInterruptPolarity( 
            VS_EDGE_TYPE intrEdge,
            /* [defaultvalue] */ DWORD channelNum = 0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOutputNode( 
            /* [out] */ LPDISPATCH __RPC_FAR *imgNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockObject( 
            VARIANT_BOOL lock) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectOutput( 
            DWORD OutputId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOutputQueuePolicy( 
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoSrcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoSrc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoSrc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerThread )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerThread )( 
            IVideoSrc __RPC_FAR * This,
            HSERVERTHREAD hSrvThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServer )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServerBlk )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMessage )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ HVSMESSAGE __RPC_FAR *hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IVideoSrc __RPC_FAR * This,
            HVSMESSAGE hMessage,
            /* [size_is][in] */ BYTE __RPC_FAR *message,
            /* [in] */ DWORD numMessageBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessage )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMessage )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitAnyMessage )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ DWORD numMsgs,
            /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
            /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlk )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVar )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysMsgQ )( 
            IVideoSrc __RPC_FAR * This,
            HVSMESSAGE hSysMsgQ,
            DWORD hRpcServer,
            HVSEVENT serverShutdownEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlkAsync )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVarAsync )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerEvent )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ HVSEVENT __RPC_FAR *event,
            /* [in] */ VARIANT_BOOL bManualReset,
            /* [in] */ VARIANT_BOOL bInitialState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerEvent )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessageOrEvents )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            /* [in] */ DWORD waitTimeMilliSec,
            /* [in] */ DWORD numEvents,
            /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
            /* [out] */ DWORD __RPC_FAR *waitResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetServerEvent )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseOs )( 
            IVideoSrc __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileCopy )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR srcFileName,
            VS_FILESYS_DOMAIN_TYPE srcDomain,
            /* [string] */ LPSTR dstFileName,
            VS_FILESYS_DOMAIN_TYPE dstDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeRpc )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
            /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
            /* [in] */ DWORD stkBlkSize,
            /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
            /* [in] */ DWORD refParamNumBytes,
            /* [out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterRpcDll )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR dllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDerivedIID )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *derivedIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            IVideoSrc __RPC_FAR * This,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterServer )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR serverDllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCallerLocal )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            DWORD processId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR videoSrcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
            /* [in] */ VARIANT_BOOL isLocal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfigFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConfigFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabWaitFrameRead )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ DWORD grabID,
            VS_FRAME_ENCODE encodeKind,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *bytesRead,
            int FrameSeqNum,
            DWORD milliseconds,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *extAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Freeze )( 
            IVideoSrc __RPC_FAR * This,
            /* [defaultvalue] */ DWORD grabID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInterruptObject )( 
            IVideoSrc __RPC_FAR * This,
            VS_ICAP_INTR_EVENT intrEvent,
            VARIANT_BOOL eventSetting,
            /* [retval][out] */ HVSINTERRUPT __RPC_FAR *hIntrObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AcqParamSupported )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAcqParam )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ double __RPC_FAR *value,
            /* [defaultvalue] */ DWORD index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAcqParam )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            double value,
            /* [defaultvalue] */ DWORD index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamCaps )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ PVS_PARAM_CAPS lpParamCaps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstParam )( 
            IVideoSrc __RPC_FAR * This,
            DWORD paramGroupMask,
            VARIANT_BOOL includeChildGroups,
            /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *firstParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextParam )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD paramGroupMask,
            VARIANT_BOOL includeChildGroups,
            /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *nextParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstParamGroup )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE parentGroupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *firstParmGrp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextParamGroup )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE groupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *nextParmGrp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGroupProperties )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE groupID,
            /* [out] */ PVS_PARAM_GROUP_PROPS lpGroupProps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentGroup )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE childGroupID,
            /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *parentGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstEnumArg )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out] */ VS_ENUM_ARG __RPC_FAR *arg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextEnumArg )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [out][in] */ VS_ENUM_ARG __RPC_FAR *arg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsArgSupported )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            double arg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClosestArgSupported )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            double arg,
            /* [retval][out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArgName )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            double dArg,
            /* [string][out][in] */ LPSTR argName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArgValue )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [string] */ LPSTR szArgName,
            /* [retval][out] */ double __RPC_FAR *argVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLutFunction )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            VSLUTFUNC func,
            DWORD __RPC_FAR *constants,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadLutByteBuf )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [size_is][out] */ BYTE __RPC_FAR *buf,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteLutByteBuf )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [size_is][in] */ BYTE __RPC_FAR *buf,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteLutToFile )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD numEntries,
            /* [string] */ LPSTR szFileName,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadLutFromFile )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            /* [string] */ LPSTR szFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadLutLoc )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            VS_LUT_PORTION_TYPE lutPortion,
            /* [retval][out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteLutLoc )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD lutAdr,
            DWORD val,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LinearizeLut )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FloodLUT )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            DWORD val,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvertLut )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ThresholdLut )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            const DWORD dwThreshold,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetLut )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            const long lOffset,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BitReverseLinearLut )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RgbToHsiLUT )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            VS_LUT_PORTION_TYPE lutPortion);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLUTCaps )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ LPVS_LUTCAP caps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLutPathPage )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            VS_LUT_PIX_SIZE_TYPE pxSize,
            DWORD pageNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLutHostPage )( 
            IVideoSrc __RPC_FAR * This,
            VS_LUTID_TYPE lutID,
            VS_LUT_PIX_SIZE_TYPE pxSize,
            DWORD pageNum,
            VARIANT_BOOL leftJustify);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWindowGen )( 
            IVideoSrc __RPC_FAR * This,
            int x,
            int y,
            int dx,
            int dy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraType )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR camName,
            /* [defaultvalue] */ VARIANT_BOOL updateHW);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextCamType )( 
            IVideoSrc __RPC_FAR * This,
            /* [out][in][string] */ LPSTR nextCamType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstCamType )( 
            IVideoSrc __RPC_FAR * This,
            /* [out][in][string] */ LPSTR firstCamType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabOn )( 
            IVideoSrc __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabMultiDest )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ HVSGRAB __RPC_FAR *grabID,
            DWORD dwOptions,
            /* [size_is][in] */ pBYTE __RPC_FAR dests[  ],
            int ringNumFrames,
            int totalNumFrames,
            /* [defaultvalue] */ int x,
            /* [defaultvalue] */ int y,
            /* [defaultvalue] */ int dx,
            /* [defaultvalue] */ int dy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabAoi )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ HVSGRAB __RPC_FAR *grabID,
            DWORD dwOptions,
            DWORD dest,
            int ringNumFrames,
            int totalNumFrames,
            /* [in] */ LPVS_AOI_DESC aoiDesc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabLock )( 
            IVideoSrc __RPC_FAR * This,
            HVSGRAB grabID,
            int seqNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabRelease )( 
            IVideoSrc __RPC_FAR * This,
            HVSGRAB grabID,
            int seqNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabWaitFrame )( 
            IVideoSrc __RPC_FAR * This,
            HVSGRAB grabID,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *frameAddr,
            int FrameSeqNum,
            DWORD milliseconds,
            VARIANT_BOOL lock,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DecodeFrame )( 
            IVideoSrc __RPC_FAR * This,
            BYTE __RPC_FAR *src,
            DWORD numSrcBytes,
            VS_FRAME_ENCODE frameEncode,
            DWORD dx,
            DWORD dy,
            VS_COLOR color,
            DWORD bitsPerPixel,
            BYTE __RPC_FAR *dest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabGetExtAttr )( 
            IVideoSrc __RPC_FAR * This,
            HVSGRAB grabID,
            int seqNum,
            /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Snap )( 
            IVideoSrc __RPC_FAR * This,
            /* [size_is][out] */ pBYTE dest,
            DWORD bytesPerFrame,
            /* [defaultvalue] */ int x,
            /* [defaultvalue] */ int y,
            /* [defaultvalue] */ int dx,
            /* [defaultvalue] */ int dy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SeqSnap )( 
            IVideoSrc __RPC_FAR * This,
            /* [size_is][out] */ pBYTE dest,
            DWORD bytesPerFrame,
            int numFrames,
            /* [defaultvalue] */ int x,
            /* [defaultvalue] */ int y,
            /* [defaultvalue] */ int dx,
            /* [defaultvalue] */ int dy,
            /* [defaultvalue] */ DWORD dwMilliseconds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoom )( 
            IVideoSrc __RPC_FAR * This,
            float xZoom,
            float yZoom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZoomCaps )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ LPVS_ZOOMCAP lpCaps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadArea )( 
            IVideoSrc __RPC_FAR * This,
            int x,
            int y,
            int dx,
            int dy,
            /* [size_is][out] */ BYTE __RPC_FAR *destadr,
            /* [defaultvalue] */ DWORD dest_dx,
            /* [defaultvalue] */ DWORD readOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LineReverseRead )( 
            IVideoSrc __RPC_FAR * This,
            int x,
            int y,
            int dx,
            int dy,
            int destlinebytes,
            /* [size_is][out] */ BYTE __RPC_FAR *destadr,
            /* [defaultvalue] */ DWORD readOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadDestPitchArea )( 
            IVideoSrc __RPC_FAR * This,
            int x,
            int y,
            int dx,
            int dy,
            int destlinebytes,
            DWORD physdest,
            /* [defaultvalue] */ DWORD readOptions);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttr )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ LPVS_CAM_ATTR lpAttr,
            /* [defaultvalue] */ VARIANT_BOOL zoomCorrected);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReadColorRemap )( 
            IVideoSrc __RPC_FAR * This,
            VARIANT_BOOL bEnabled);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadReg )( 
            IVideoSrc __RPC_FAR * This,
            REGID reg,
            /* [retval][out] */ DWORD __RPC_FAR *regVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteReg )( 
            IVideoSrc __RPC_FAR * This,
            REGID reg,
            DWORD val);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParamValToString )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            double dVal,
            /* [string][out][in] */ LPSTR szResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParamStringToVal )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            /* [string] */ LPSTR szVal,
            /* [retval][out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryUIParamUpdate )( 
            IVideoSrc __RPC_FAR * This,
            /* [out][in] */ double __RPC_FAR *dVal,
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParamGroupEditDlgExist )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE GroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoParamGroupEditDialog )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE GroupID,
            VS_ACQ_PARAMS_TYPE focalParam);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParamIsApplicable )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            DWORD index,
            /* [string][out][in] */ LPSTR ReasonNotApplicable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GroupIsApplicable )( 
            IVideoSrc __RPC_FAR * This,
            VS_PARAM_GROUP_TYPE groupID,
            /* [string][out][in] */ LPSTR ReasonNotApplicable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrintParamAttributes )( 
            IVideoSrc __RPC_FAR * This,
            VS_ACQ_PARAMS_TYPE paramID,
            VS_PARAM_GROUP_TYPE parentGroupID,
            /* [string] */ LPSTR file);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CameraIsReserved )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR camName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransformSupported )( 
            IVideoSrc __RPC_FAR * This,
            VS_TRANSFORM_TYPE eTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransform )( 
            IVideoSrc __RPC_FAR * This,
            VS_TRANSFORM_TYPE eTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentTransform )( 
            IVideoSrc __RPC_FAR * This,
            /* [retval][out] */ VS_TRANSFORM_TYPE __RPC_FAR *currentTransform);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryUICameraType )( 
            IVideoSrc __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPortNum )( 
            IVideoSrc __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *portNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProps )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ VSPROPS __RPC_FAR *props);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPortNum )( 
            IVideoSrc __RPC_FAR * This,
            DWORD portNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumPorts )( 
            IVideoSrc __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *numPorts);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCameraType )( 
            IVideoSrc __RPC_FAR * This,
            LPSTR strNewCamName,
            LPSTR strExistCamName,
            /* [retval][out] */ DWORD __RPC_FAR *defHhandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Grab )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *grabID,
            /* [in] */ DWORD dwOptions,
            DWORD dest,
            int ringNumFrames,
            int totalNumFrames,
            /* [defaultvalue] */ int x,
            /* [defaultvalue] */ int y,
            /* [defaultvalue] */ int dx,
            /* [defaultvalue] */ int dy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVideoStream )( 
            IVideoSrc __RPC_FAR * This,
            PVS_STREAM_PARAMS params,
            /* [retval][out] */ HVIDSTREAMSRV __RPC_FAR *vidStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteVideoStream )( 
            IVideoSrc __RPC_FAR * This,
            HVIDSTREAMSRV vidStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitStreamPacket )( 
            IVideoSrc __RPC_FAR * This,
            HVIDSTREAMSRV srvStream,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *bytesRead,
            DWORD milliseconds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDriverHandle )( 
            IVideoSrc __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *handle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteCameraFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR cameraFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain,
            /* [string] */ LPSTR cameraName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadCamerasInFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR cameraFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadUserConfigFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR configFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteUserConfigFile )( 
            IVideoSrc __RPC_FAR * This,
            /* [string] */ LPSTR configFileName,
            VS_FILESYS_DOMAIN_TYPE fileSysDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectOutputTo )( 
            IVideoSrc __RPC_FAR * This,
            DWORD OutputId,
            IDispatch __RPC_FAR *sink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProduceTo )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ LPDISPATCH imgNode,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachProducer )( 
            IVideoSrc __RPC_FAR * This,
            IDispatch __RPC_FAR *node,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateProducer )( 
            IVideoSrc __RPC_FAR * This,
            DWORD srcOutputId,
            VS_REF_VAL_KIND enQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabToImgNode )( 
            IVideoSrc __RPC_FAR * This,
            VS_FRAME_ENCODE remoteUseEncode,
            DWORD dwOptions,
            int NumFrames,
            /* [defaultvalue] */ int x,
            /* [defaultvalue] */ int y,
            /* [defaultvalue] */ int dx,
            /* [defaultvalue] */ int dy);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreezeImgNode )( 
            IVideoSrc __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseEleRef )( 
            IVideoSrc __RPC_FAR * This,
            DWORD srcOutputId,
            HBYREFELE deRefHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitInterrupt )( 
            IVideoSrc __RPC_FAR * This,
            HVSINTERRUPT hIntrObj,
            DWORD milliSeconds);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteInterruptObject )( 
            IVideoSrc __RPC_FAR * This,
            HVSINTERRUPT hIntrObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearInterrupt )( 
            IVideoSrc __RPC_FAR * This,
            HVSINTERRUPT hIntrObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReadCaps )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ VS_READCAP __RPC_FAR *lpCaps);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IVideoSrc __RPC_FAR * This,
            /* [defaultvalue] */ DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OutportStrobeVal )( 
            IVideoSrc __RPC_FAR * This,
            VS_LEVEL_TYPE val,
            /* [defaultvalue] */ DWORD channelNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OutportVal )( 
            IVideoSrc __RPC_FAR * This,
            DWORD val,
            DWORD channelNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InportMode )( 
            IVideoSrc __RPC_FAR * This,
            BOOL strobed,
            VS_EDGE_TYPE latchEdge,
            /* [defaultvalue] */ DWORD channelNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InportVal )( 
            IVideoSrc __RPC_FAR * This,
            DWORD channelNum,
            DWORD __RPC_FAR *valRead);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InportInterruptPolarity )( 
            IVideoSrc __RPC_FAR * This,
            VS_EDGE_TYPE intrEdge,
            /* [defaultvalue] */ DWORD channelNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputNode )( 
            IVideoSrc __RPC_FAR * This,
            /* [out] */ LPDISPATCH __RPC_FAR *imgNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockObject )( 
            IVideoSrc __RPC_FAR * This,
            VARIANT_BOOL lock);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectOutput )( 
            IVideoSrc __RPC_FAR * This,
            DWORD OutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputQueuePolicy )( 
            IVideoSrc __RPC_FAR * This,
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);
        
        END_INTERFACE
    } IVideoSrcVtbl;

    interface IVideoSrc
    {
        CONST_VTBL struct IVideoSrcVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoSrc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoSrc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoSrc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoSrc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoSrc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoSrc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoSrc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoSrc_CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)

#define IVideoSrc_DeleteServerThread(This,hSrvThread)	\
    (This)->lpVtbl -> DeleteServerThread(This,hSrvThread)

#define IVideoSrc_InvokeServer(This,dllName,funcName,retVal)	\
    (This)->lpVtbl -> InvokeServer(This,dllName,funcName,retVal)

#define IVideoSrc_InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)	\
    (This)->lpVtbl -> InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)

#define IVideoSrc_CreateMessage(This,hMessage)	\
    (This)->lpVtbl -> CreateMessage(This,hMessage)

#define IVideoSrc_SendMessage(This,hMessage,message,numMessageBytes)	\
    (This)->lpVtbl -> SendMessage(This,hMessage,message,numMessageBytes)

#define IVideoSrc_WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IVideoSrc_DeleteMessage(This,hMessage)	\
    (This)->lpVtbl -> DeleteMessage(This,hMessage)

#define IVideoSrc_WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IVideoSrc_InvokeClientBlk(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlk(This,funcName,paramBlock,numParamBytes)

#define IVideoSrc_InvokeClientVar(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVar(This,funcName,numParams,params)

#define IVideoSrc_SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)	\
    (This)->lpVtbl -> SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)

#define IVideoSrc_InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)

#define IVideoSrc_InvokeClientVarAsync(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVarAsync(This,funcName,numParams,params)

#define IVideoSrc_CreateServerEvent(This,event,bManualReset,bInitialState)	\
    (This)->lpVtbl -> CreateServerEvent(This,event,bManualReset,bInitialState)

#define IVideoSrc_DeleteServerEvent(This,event)	\
    (This)->lpVtbl -> DeleteServerEvent(This,event)

#define IVideoSrc_WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)	\
    (This)->lpVtbl -> WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)

#define IVideoSrc_SetServerEvent(This,event)	\
    (This)->lpVtbl -> SetServerEvent(This,event)

#define IVideoSrc_CloseOs(This,dwFlags)	\
    (This)->lpVtbl -> CloseOs(This,dwFlags)

#define IVideoSrc_FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)	\
    (This)->lpVtbl -> FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)

#define IVideoSrc_InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)	\
    (This)->lpVtbl -> InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)

#define IVideoSrc_RegisterRpcDll(This,dllName)	\
    (This)->lpVtbl -> RegisterRpcDll(This,dllName)

#define IVideoSrc_GetDerivedIID(This,derivedIID)	\
    (This)->lpVtbl -> GetDerivedIID(This,derivedIID)

#define IVideoSrc_CreateObject(This,rclsid,riid,obj)	\
    (This)->lpVtbl -> CreateObject(This,rclsid,riid,obj)

#define IVideoSrc_RegisterServer(This,serverDllName)	\
    (This)->lpVtbl -> RegisterServer(This,serverDllName)

#define IVideoSrc_IsCallerLocal(This,nodeName,processId)	\
    (This)->lpVtbl -> IsCallerLocal(This,nodeName,processId)


#define IVideoSrc_Connect(This,videoSrcName,numParams,params,isLocal)	\
    (This)->lpVtbl -> Connect(This,videoSrcName,numParams,params,isLocal)

#define IVideoSrc_get_ConfigFile(This,pVal)	\
    (This)->lpVtbl -> get_ConfigFile(This,pVal)

#define IVideoSrc_put_ConfigFile(This,newVal)	\
    (This)->lpVtbl -> put_ConfigFile(This,newVal)

#define IVideoSrc_GrabWaitFrameRead(This,grabID,encodeKind,dest,bytesAvailable,bytesRead,FrameSeqNum,milliseconds,extAttr)	\
    (This)->lpVtbl -> GrabWaitFrameRead(This,grabID,encodeKind,dest,bytesAvailable,bytesRead,FrameSeqNum,milliseconds,extAttr)

#define IVideoSrc_Freeze(This,grabID)	\
    (This)->lpVtbl -> Freeze(This,grabID)

#define IVideoSrc_CreateInterruptObject(This,intrEvent,eventSetting,hIntrObj)	\
    (This)->lpVtbl -> CreateInterruptObject(This,intrEvent,eventSetting,hIntrObj)

#define IVideoSrc_AcqParamSupported(This,paramID)	\
    (This)->lpVtbl -> AcqParamSupported(This,paramID)

#define IVideoSrc_GetAcqParam(This,paramID,value,index)	\
    (This)->lpVtbl -> GetAcqParam(This,paramID,value,index)

#define IVideoSrc_SetAcqParam(This,paramID,value,index)	\
    (This)->lpVtbl -> SetAcqParam(This,paramID,value,index)

#define IVideoSrc_GetParamCaps(This,paramID,lpParamCaps)	\
    (This)->lpVtbl -> GetParamCaps(This,paramID,lpParamCaps)

#define IVideoSrc_GetFirstParam(This,paramGroupMask,includeChildGroups,firstParam)	\
    (This)->lpVtbl -> GetFirstParam(This,paramGroupMask,includeChildGroups,firstParam)

#define IVideoSrc_GetNextParam(This,paramID,paramGroupMask,includeChildGroups,nextParam)	\
    (This)->lpVtbl -> GetNextParam(This,paramID,paramGroupMask,includeChildGroups,nextParam)

#define IVideoSrc_GetFirstParamGroup(This,parentGroupID,firstParmGrp)	\
    (This)->lpVtbl -> GetFirstParamGroup(This,parentGroupID,firstParmGrp)

#define IVideoSrc_GetNextParamGroup(This,groupID,nextParmGrp)	\
    (This)->lpVtbl -> GetNextParamGroup(This,groupID,nextParmGrp)

#define IVideoSrc_GetGroupProperties(This,groupID,lpGroupProps)	\
    (This)->lpVtbl -> GetGroupProperties(This,groupID,lpGroupProps)

#define IVideoSrc_GetParentGroup(This,childGroupID,parentGroupID)	\
    (This)->lpVtbl -> GetParentGroup(This,childGroupID,parentGroupID)

#define IVideoSrc_GetFirstEnumArg(This,paramID,arg)	\
    (This)->lpVtbl -> GetFirstEnumArg(This,paramID,arg)

#define IVideoSrc_GetNextEnumArg(This,paramID,arg)	\
    (This)->lpVtbl -> GetNextEnumArg(This,paramID,arg)

#define IVideoSrc_IsArgSupported(This,paramID,arg)	\
    (This)->lpVtbl -> IsArgSupported(This,paramID,arg)

#define IVideoSrc_ClosestArgSupported(This,paramID,arg,retVal)	\
    (This)->lpVtbl -> ClosestArgSupported(This,paramID,arg,retVal)

#define IVideoSrc_GetArgName(This,paramID,dArg,argName)	\
    (This)->lpVtbl -> GetArgName(This,paramID,dArg,argName)

#define IVideoSrc_GetArgValue(This,paramID,szArgName,argVal)	\
    (This)->lpVtbl -> GetArgValue(This,paramID,szArgName,argVal)

#define IVideoSrc_SetLutFunction(This,lutID,func,constants,lutPortion)	\
    (This)->lpVtbl -> SetLutFunction(This,lutID,func,constants,lutPortion)

#define IVideoSrc_ReadLutByteBuf(This,lutID,lutAdr,numEntries,buf,lutPortion)	\
    (This)->lpVtbl -> ReadLutByteBuf(This,lutID,lutAdr,numEntries,buf,lutPortion)

#define IVideoSrc_WriteLutByteBuf(This,lutID,lutAdr,numEntries,buf,lutPortion)	\
    (This)->lpVtbl -> WriteLutByteBuf(This,lutID,lutAdr,numEntries,buf,lutPortion)

#define IVideoSrc_WriteLutToFile(This,lutID,lutAdr,numEntries,szFileName,lutPortion)	\
    (This)->lpVtbl -> WriteLutToFile(This,lutID,lutAdr,numEntries,szFileName,lutPortion)

#define IVideoSrc_LoadLutFromFile(This,lutID,szFileName)	\
    (This)->lpVtbl -> LoadLutFromFile(This,lutID,szFileName)

#define IVideoSrc_ReadLutLoc(This,lutID,lutAdr,lutPortion,retVal)	\
    (This)->lpVtbl -> ReadLutLoc(This,lutID,lutAdr,lutPortion,retVal)

#define IVideoSrc_WriteLutLoc(This,lutID,lutAdr,val,lutPortion)	\
    (This)->lpVtbl -> WriteLutLoc(This,lutID,lutAdr,val,lutPortion)

#define IVideoSrc_LinearizeLut(This,lutID,lutPortion)	\
    (This)->lpVtbl -> LinearizeLut(This,lutID,lutPortion)

#define IVideoSrc_FloodLUT(This,lutID,val,lutPortion)	\
    (This)->lpVtbl -> FloodLUT(This,lutID,val,lutPortion)

#define IVideoSrc_InvertLut(This,lutID,lutPortion)	\
    (This)->lpVtbl -> InvertLut(This,lutID,lutPortion)

#define IVideoSrc_ThresholdLut(This,lutID,dwThreshold,lutPortion)	\
    (This)->lpVtbl -> ThresholdLut(This,lutID,dwThreshold,lutPortion)

#define IVideoSrc_OffsetLut(This,lutID,lOffset,lutPortion)	\
    (This)->lpVtbl -> OffsetLut(This,lutID,lOffset,lutPortion)

#define IVideoSrc_BitReverseLinearLut(This,lutID,lutPortion)	\
    (This)->lpVtbl -> BitReverseLinearLut(This,lutID,lutPortion)

#define IVideoSrc_RgbToHsiLUT(This,lutID,lutPortion)	\
    (This)->lpVtbl -> RgbToHsiLUT(This,lutID,lutPortion)

#define IVideoSrc_GetLUTCaps(This,caps)	\
    (This)->lpVtbl -> GetLUTCaps(This,caps)

#define IVideoSrc_SetLutPathPage(This,lutID,pxSize,pageNum)	\
    (This)->lpVtbl -> SetLutPathPage(This,lutID,pxSize,pageNum)

#define IVideoSrc_SetLutHostPage(This,lutID,pxSize,pageNum,leftJustify)	\
    (This)->lpVtbl -> SetLutHostPage(This,lutID,pxSize,pageNum,leftJustify)

#define IVideoSrc_SetWindowGen(This,x,y,dx,dy)	\
    (This)->lpVtbl -> SetWindowGen(This,x,y,dx,dy)

#define IVideoSrc_SetCameraType(This,camName,updateHW)	\
    (This)->lpVtbl -> SetCameraType(This,camName,updateHW)

#define IVideoSrc_GetNextCamType(This,nextCamType)	\
    (This)->lpVtbl -> GetNextCamType(This,nextCamType)

#define IVideoSrc_GetFirstCamType(This,firstCamType)	\
    (This)->lpVtbl -> GetFirstCamType(This,firstCamType)

#define IVideoSrc_GrabOn(This)	\
    (This)->lpVtbl -> GrabOn(This)

#define IVideoSrc_GrabMultiDest(This,grabID,dwOptions,dests,ringNumFrames,totalNumFrames,x,y,dx,dy)	\
    (This)->lpVtbl -> GrabMultiDest(This,grabID,dwOptions,dests,ringNumFrames,totalNumFrames,x,y,dx,dy)

#define IVideoSrc_GrabAoi(This,grabID,dwOptions,dest,ringNumFrames,totalNumFrames,aoiDesc)	\
    (This)->lpVtbl -> GrabAoi(This,grabID,dwOptions,dest,ringNumFrames,totalNumFrames,aoiDesc)

#define IVideoSrc_GrabLock(This,grabID,seqNum)	\
    (This)->lpVtbl -> GrabLock(This,grabID,seqNum)

#define IVideoSrc_GrabRelease(This,grabID,seqNum)	\
    (This)->lpVtbl -> GrabRelease(This,grabID,seqNum)

#define IVideoSrc_GrabWaitFrame(This,grabID,frameAddr,FrameSeqNum,milliseconds,lock,ExtendedAttr)	\
    (This)->lpVtbl -> GrabWaitFrame(This,grabID,frameAddr,FrameSeqNum,milliseconds,lock,ExtendedAttr)

#define IVideoSrc_DecodeFrame(This,src,numSrcBytes,frameEncode,dx,dy,color,bitsPerPixel,dest)	\
    (This)->lpVtbl -> DecodeFrame(This,src,numSrcBytes,frameEncode,dx,dy,color,bitsPerPixel,dest)

#define IVideoSrc_GrabGetExtAttr(This,grabID,seqNum,ExtendedAttr)	\
    (This)->lpVtbl -> GrabGetExtAttr(This,grabID,seqNum,ExtendedAttr)

#define IVideoSrc_Snap(This,dest,bytesPerFrame,x,y,dx,dy)	\
    (This)->lpVtbl -> Snap(This,dest,bytesPerFrame,x,y,dx,dy)

#define IVideoSrc_SeqSnap(This,dest,bytesPerFrame,numFrames,x,y,dx,dy,dwMilliseconds)	\
    (This)->lpVtbl -> SeqSnap(This,dest,bytesPerFrame,numFrames,x,y,dx,dy,dwMilliseconds)

#define IVideoSrc_SetZoom(This,xZoom,yZoom)	\
    (This)->lpVtbl -> SetZoom(This,xZoom,yZoom)

#define IVideoSrc_GetZoomCaps(This,lpCaps)	\
    (This)->lpVtbl -> GetZoomCaps(This,lpCaps)

#define IVideoSrc_ReadArea(This,x,y,dx,dy,destadr,dest_dx,readOptions)	\
    (This)->lpVtbl -> ReadArea(This,x,y,dx,dy,destadr,dest_dx,readOptions)

#define IVideoSrc_LineReverseRead(This,x,y,dx,dy,destlinebytes,destadr,readOptions)	\
    (This)->lpVtbl -> LineReverseRead(This,x,y,dx,dy,destlinebytes,destadr,readOptions)

#define IVideoSrc_ReadDestPitchArea(This,x,y,dx,dy,destlinebytes,physdest,readOptions)	\
    (This)->lpVtbl -> ReadDestPitchArea(This,x,y,dx,dy,destlinebytes,physdest,readOptions)

#define IVideoSrc_GetAttr(This,lpAttr,zoomCorrected)	\
    (This)->lpVtbl -> GetAttr(This,lpAttr,zoomCorrected)

#define IVideoSrc_SetReadColorRemap(This,bEnabled)	\
    (This)->lpVtbl -> SetReadColorRemap(This,bEnabled)

#define IVideoSrc_ReadReg(This,reg,regVal)	\
    (This)->lpVtbl -> ReadReg(This,reg,regVal)

#define IVideoSrc_WriteReg(This,reg,val)	\
    (This)->lpVtbl -> WriteReg(This,reg,val)

#define IVideoSrc_ParamValToString(This,paramID,dVal,szResult)	\
    (This)->lpVtbl -> ParamValToString(This,paramID,dVal,szResult)

#define IVideoSrc_ParamStringToVal(This,paramID,szVal,retVal)	\
    (This)->lpVtbl -> ParamStringToVal(This,paramID,szVal,retVal)

#define IVideoSrc_QueryUIParamUpdate(This,dVal,paramID,index)	\
    (This)->lpVtbl -> QueryUIParamUpdate(This,dVal,paramID,index)

#define IVideoSrc_ParamGroupEditDlgExist(This,GroupID)	\
    (This)->lpVtbl -> ParamGroupEditDlgExist(This,GroupID)

#define IVideoSrc_DoParamGroupEditDialog(This,GroupID,focalParam)	\
    (This)->lpVtbl -> DoParamGroupEditDialog(This,GroupID,focalParam)

#define IVideoSrc_ParamIsApplicable(This,paramID,index,ReasonNotApplicable)	\
    (This)->lpVtbl -> ParamIsApplicable(This,paramID,index,ReasonNotApplicable)

#define IVideoSrc_GroupIsApplicable(This,groupID,ReasonNotApplicable)	\
    (This)->lpVtbl -> GroupIsApplicable(This,groupID,ReasonNotApplicable)

#define IVideoSrc_PrintParamAttributes(This,paramID,parentGroupID,file)	\
    (This)->lpVtbl -> PrintParamAttributes(This,paramID,parentGroupID,file)

#define IVideoSrc_CameraIsReserved(This,camName)	\
    (This)->lpVtbl -> CameraIsReserved(This,camName)

#define IVideoSrc_TransformSupported(This,eTransform)	\
    (This)->lpVtbl -> TransformSupported(This,eTransform)

#define IVideoSrc_SetTransform(This,eTransform)	\
    (This)->lpVtbl -> SetTransform(This,eTransform)

#define IVideoSrc_GetCurrentTransform(This,currentTransform)	\
    (This)->lpVtbl -> GetCurrentTransform(This,currentTransform)

#define IVideoSrc_QueryUICameraType(This)	\
    (This)->lpVtbl -> QueryUICameraType(This)

#define IVideoSrc_GetPortNum(This,portNum)	\
    (This)->lpVtbl -> GetPortNum(This,portNum)

#define IVideoSrc_GetProps(This,props)	\
    (This)->lpVtbl -> GetProps(This,props)

#define IVideoSrc_SetPortNum(This,portNum)	\
    (This)->lpVtbl -> SetPortNum(This,portNum)

#define IVideoSrc_GetNumPorts(This,numPorts)	\
    (This)->lpVtbl -> GetNumPorts(This,numPorts)

#define IVideoSrc_AddCameraType(This,strNewCamName,strExistCamName,defHhandle)	\
    (This)->lpVtbl -> AddCameraType(This,strNewCamName,strExistCamName,defHhandle)

#define IVideoSrc_Grab(This,grabID,dwOptions,dest,ringNumFrames,totalNumFrames,x,y,dx,dy)	\
    (This)->lpVtbl -> Grab(This,grabID,dwOptions,dest,ringNumFrames,totalNumFrames,x,y,dx,dy)

#define IVideoSrc_CreateVideoStream(This,params,vidStream)	\
    (This)->lpVtbl -> CreateVideoStream(This,params,vidStream)

#define IVideoSrc_DeleteVideoStream(This,vidStream)	\
    (This)->lpVtbl -> DeleteVideoStream(This,vidStream)

#define IVideoSrc_WaitStreamPacket(This,srvStream,dest,bytesAvailable,bytesRead,milliseconds)	\
    (This)->lpVtbl -> WaitStreamPacket(This,srvStream,dest,bytesAvailable,bytesRead,milliseconds)

#define IVideoSrc_GetDriverHandle(This,handle)	\
    (This)->lpVtbl -> GetDriverHandle(This,handle)

#define IVideoSrc_WriteCameraFile(This,cameraFileName,fileSysDomain,cameraName)	\
    (This)->lpVtbl -> WriteCameraFile(This,cameraFileName,fileSysDomain,cameraName)

#define IVideoSrc_ReadCamerasInFile(This,cameraFileName,fileSysDomain)	\
    (This)->lpVtbl -> ReadCamerasInFile(This,cameraFileName,fileSysDomain)

#define IVideoSrc_ReadUserConfigFile(This,configFileName,fileSysDomain)	\
    (This)->lpVtbl -> ReadUserConfigFile(This,configFileName,fileSysDomain)

#define IVideoSrc_WriteUserConfigFile(This,configFileName,fileSysDomain)	\
    (This)->lpVtbl -> WriteUserConfigFile(This,configFileName,fileSysDomain)

#define IVideoSrc_ConnectOutputTo(This,OutputId,sink)	\
    (This)->lpVtbl -> ConnectOutputTo(This,OutputId,sink)

#define IVideoSrc_ProduceTo(This,imgNode,srcOutputId)	\
    (This)->lpVtbl -> ProduceTo(This,imgNode,srcOutputId)

#define IVideoSrc_NotifyDetachProducer(This,node,srcOutputId)	\
    (This)->lpVtbl -> NotifyDetachProducer(This,node,srcOutputId)

#define IVideoSrc_ActivateProducer(This,srcOutputId,enQKind,areRemote)	\
    (This)->lpVtbl -> ActivateProducer(This,srcOutputId,enQKind,areRemote)

#define IVideoSrc_GrabToImgNode(This,remoteUseEncode,dwOptions,NumFrames,x,y,dx,dy)	\
    (This)->lpVtbl -> GrabToImgNode(This,remoteUseEncode,dwOptions,NumFrames,x,y,dx,dy)

#define IVideoSrc_FreezeImgNode(This)	\
    (This)->lpVtbl -> FreezeImgNode(This)

#define IVideoSrc_ReleaseEleRef(This,srcOutputId,deRefHandle)	\
    (This)->lpVtbl -> ReleaseEleRef(This,srcOutputId,deRefHandle)

#define IVideoSrc_WaitInterrupt(This,hIntrObj,milliSeconds)	\
    (This)->lpVtbl -> WaitInterrupt(This,hIntrObj,milliSeconds)

#define IVideoSrc_DeleteInterruptObject(This,hIntrObj)	\
    (This)->lpVtbl -> DeleteInterruptObject(This,hIntrObj)

#define IVideoSrc_ClearInterrupt(This,hIntrObj)	\
    (This)->lpVtbl -> ClearInterrupt(This,hIntrObj)

#define IVideoSrc_GetReadCaps(This,lpCaps)	\
    (This)->lpVtbl -> GetReadCaps(This,lpCaps)

#define IVideoSrc_Close(This,dwFlags)	\
    (This)->lpVtbl -> Close(This,dwFlags)

#define IVideoSrc_OutportStrobeVal(This,val,channelNum)	\
    (This)->lpVtbl -> OutportStrobeVal(This,val,channelNum)

#define IVideoSrc_OutportVal(This,val,channelNum)	\
    (This)->lpVtbl -> OutportVal(This,val,channelNum)

#define IVideoSrc_InportMode(This,strobed,latchEdge,channelNum)	\
    (This)->lpVtbl -> InportMode(This,strobed,latchEdge,channelNum)

#define IVideoSrc_InportVal(This,channelNum,valRead)	\
    (This)->lpVtbl -> InportVal(This,channelNum,valRead)

#define IVideoSrc_InportInterruptPolarity(This,intrEdge,channelNum)	\
    (This)->lpVtbl -> InportInterruptPolarity(This,intrEdge,channelNum)

#define IVideoSrc_GetOutputNode(This,imgNode)	\
    (This)->lpVtbl -> GetOutputNode(This,imgNode)

#define IVideoSrc_LockObject(This,lock)	\
    (This)->lpVtbl -> LockObject(This,lock)

#define IVideoSrc_DisconnectOutput(This,OutputId)	\
    (This)->lpVtbl -> DisconnectOutput(This,OutputId)

#define IVideoSrc_SetOutputQueuePolicy(This,attr)	\
    (This)->lpVtbl -> SetOutputQueuePolicy(This,attr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_Connect_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR videoSrcName,
    /* [in] */ DWORD numParams,
    /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
    /* [in] */ VARIANT_BOOL isLocal);


void __RPC_STUB IVideoSrc_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoSrc_get_ConfigFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IVideoSrc_get_ConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoSrc_put_ConfigFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IVideoSrc_put_ConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabWaitFrameRead_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [in] */ DWORD grabID,
    VS_FRAME_ENCODE encodeKind,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
    /* [in] */ DWORD bytesAvailable,
    /* [out] */ DWORD __RPC_FAR *bytesRead,
    int FrameSeqNum,
    DWORD milliseconds,
    /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *extAttr);


void __RPC_STUB IVideoSrc_GrabWaitFrameRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_Freeze_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [defaultvalue] */ DWORD grabID);


void __RPC_STUB IVideoSrc_Freeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_CreateInterruptObject_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ICAP_INTR_EVENT intrEvent,
    VARIANT_BOOL eventSetting,
    /* [retval][out] */ HVSINTERRUPT __RPC_FAR *hIntrObj);


void __RPC_STUB IVideoSrc_CreateInterruptObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_AcqParamSupported_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID);


void __RPC_STUB IVideoSrc_AcqParamSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetAcqParam_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [out] */ double __RPC_FAR *value,
    /* [defaultvalue] */ DWORD index);


void __RPC_STUB IVideoSrc_GetAcqParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetAcqParam_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    double value,
    /* [defaultvalue] */ DWORD index);


void __RPC_STUB IVideoSrc_SetAcqParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetParamCaps_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [out] */ PVS_PARAM_CAPS lpParamCaps);


void __RPC_STUB IVideoSrc_GetParamCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetFirstParam_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD paramGroupMask,
    VARIANT_BOOL includeChildGroups,
    /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *firstParam);


void __RPC_STUB IVideoSrc_GetFirstParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetNextParam_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    DWORD paramGroupMask,
    VARIANT_BOOL includeChildGroups,
    /* [retval][out] */ VS_ACQ_PARAMS_TYPE __RPC_FAR *nextParam);


void __RPC_STUB IVideoSrc_GetNextParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetFirstParamGroup_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE parentGroupID,
    /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *firstParmGrp);


void __RPC_STUB IVideoSrc_GetFirstParamGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetNextParamGroup_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE groupID,
    /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *nextParmGrp);


void __RPC_STUB IVideoSrc_GetNextParamGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetGroupProperties_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE groupID,
    /* [out] */ PVS_PARAM_GROUP_PROPS lpGroupProps);


void __RPC_STUB IVideoSrc_GetGroupProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetParentGroup_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE childGroupID,
    /* [retval][out] */ VS_PARAM_GROUP_TYPE __RPC_FAR *parentGroupID);


void __RPC_STUB IVideoSrc_GetParentGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetFirstEnumArg_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [out] */ VS_ENUM_ARG __RPC_FAR *arg);


void __RPC_STUB IVideoSrc_GetFirstEnumArg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetNextEnumArg_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [out][in] */ VS_ENUM_ARG __RPC_FAR *arg);


void __RPC_STUB IVideoSrc_GetNextEnumArg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_IsArgSupported_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    double arg);


void __RPC_STUB IVideoSrc_IsArgSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ClosestArgSupported_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    double arg,
    /* [retval][out] */ double __RPC_FAR *retVal);


void __RPC_STUB IVideoSrc_ClosestArgSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetArgName_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    double dArg,
    /* [string][out][in] */ LPSTR argName);


void __RPC_STUB IVideoSrc_GetArgName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetArgValue_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [string] */ LPSTR szArgName,
    /* [retval][out] */ double __RPC_FAR *argVal);


void __RPC_STUB IVideoSrc_GetArgValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetLutFunction_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    VSLUTFUNC func,
    DWORD __RPC_FAR *constants,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_SetLutFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadLutByteBuf_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD lutAdr,
    DWORD numEntries,
    /* [size_is][out] */ BYTE __RPC_FAR *buf,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_ReadLutByteBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteLutByteBuf_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD lutAdr,
    DWORD numEntries,
    /* [size_is][in] */ BYTE __RPC_FAR *buf,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_WriteLutByteBuf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteLutToFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD lutAdr,
    DWORD numEntries,
    /* [string] */ LPSTR szFileName,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_WriteLutToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_LoadLutFromFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    /* [string] */ LPSTR szFileName);


void __RPC_STUB IVideoSrc_LoadLutFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadLutLoc_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD lutAdr,
    VS_LUT_PORTION_TYPE lutPortion,
    /* [retval][out] */ DWORD __RPC_FAR *retVal);


void __RPC_STUB IVideoSrc_ReadLutLoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteLutLoc_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD lutAdr,
    DWORD val,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_WriteLutLoc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_LinearizeLut_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_LinearizeLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_FloodLUT_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    DWORD val,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_FloodLUT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_InvertLut_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_InvertLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ThresholdLut_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    const DWORD dwThreshold,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_ThresholdLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_OffsetLut_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    const long lOffset,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_OffsetLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_BitReverseLinearLut_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    /* [defaultvalue] */ VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_BitReverseLinearLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_RgbToHsiLUT_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    VS_LUT_PORTION_TYPE lutPortion);


void __RPC_STUB IVideoSrc_RgbToHsiLUT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetLUTCaps_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ LPVS_LUTCAP caps);


void __RPC_STUB IVideoSrc_GetLUTCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetLutPathPage_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    VS_LUT_PIX_SIZE_TYPE pxSize,
    DWORD pageNum);


void __RPC_STUB IVideoSrc_SetLutPathPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetLutHostPage_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LUTID_TYPE lutID,
    VS_LUT_PIX_SIZE_TYPE pxSize,
    DWORD pageNum,
    VARIANT_BOOL leftJustify);


void __RPC_STUB IVideoSrc_SetLutHostPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetWindowGen_Proxy( 
    IVideoSrc __RPC_FAR * This,
    int x,
    int y,
    int dx,
    int dy);


void __RPC_STUB IVideoSrc_SetWindowGen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetCameraType_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR camName,
    /* [defaultvalue] */ VARIANT_BOOL updateHW);


void __RPC_STUB IVideoSrc_SetCameraType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetNextCamType_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out][in][string] */ LPSTR nextCamType);


void __RPC_STUB IVideoSrc_GetNextCamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetFirstCamType_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out][in][string] */ LPSTR firstCamType);


void __RPC_STUB IVideoSrc_GetFirstCamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabOn_Proxy( 
    IVideoSrc __RPC_FAR * This);


void __RPC_STUB IVideoSrc_GrabOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabMultiDest_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ HVSGRAB __RPC_FAR *grabID,
    DWORD dwOptions,
    /* [size_is][in] */ pBYTE __RPC_FAR dests[  ],
    int ringNumFrames,
    int totalNumFrames,
    /* [defaultvalue] */ int x,
    /* [defaultvalue] */ int y,
    /* [defaultvalue] */ int dx,
    /* [defaultvalue] */ int dy);


void __RPC_STUB IVideoSrc_GrabMultiDest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabAoi_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ HVSGRAB __RPC_FAR *grabID,
    DWORD dwOptions,
    DWORD dest,
    int ringNumFrames,
    int totalNumFrames,
    /* [in] */ LPVS_AOI_DESC aoiDesc);


void __RPC_STUB IVideoSrc_GrabAoi_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabLock_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSGRAB grabID,
    int seqNum);


void __RPC_STUB IVideoSrc_GrabLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabRelease_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSGRAB grabID,
    int seqNum);


void __RPC_STUB IVideoSrc_GrabRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabWaitFrame_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSGRAB grabID,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *frameAddr,
    int FrameSeqNum,
    DWORD milliseconds,
    VARIANT_BOOL lock,
    /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr);


void __RPC_STUB IVideoSrc_GrabWaitFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_DecodeFrame_Proxy( 
    IVideoSrc __RPC_FAR * This,
    BYTE __RPC_FAR *src,
    DWORD numSrcBytes,
    VS_FRAME_ENCODE frameEncode,
    DWORD dx,
    DWORD dy,
    VS_COLOR color,
    DWORD bitsPerPixel,
    BYTE __RPC_FAR *dest);


void __RPC_STUB IVideoSrc_DecodeFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabGetExtAttr_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSGRAB grabID,
    int seqNum,
    /* [out] */ VS_GRAB_EXT_ATTR __RPC_FAR *ExtendedAttr);


void __RPC_STUB IVideoSrc_GrabGetExtAttr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_Snap_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [size_is][out] */ pBYTE dest,
    DWORD bytesPerFrame,
    /* [defaultvalue] */ int x,
    /* [defaultvalue] */ int y,
    /* [defaultvalue] */ int dx,
    /* [defaultvalue] */ int dy);


void __RPC_STUB IVideoSrc_Snap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SeqSnap_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [size_is][out] */ pBYTE dest,
    DWORD bytesPerFrame,
    int numFrames,
    /* [defaultvalue] */ int x,
    /* [defaultvalue] */ int y,
    /* [defaultvalue] */ int dx,
    /* [defaultvalue] */ int dy,
    /* [defaultvalue] */ DWORD dwMilliseconds);


void __RPC_STUB IVideoSrc_SeqSnap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetZoom_Proxy( 
    IVideoSrc __RPC_FAR * This,
    float xZoom,
    float yZoom);


void __RPC_STUB IVideoSrc_SetZoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetZoomCaps_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ LPVS_ZOOMCAP lpCaps);


void __RPC_STUB IVideoSrc_GetZoomCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadArea_Proxy( 
    IVideoSrc __RPC_FAR * This,
    int x,
    int y,
    int dx,
    int dy,
    /* [size_is][out] */ BYTE __RPC_FAR *destadr,
    /* [defaultvalue] */ DWORD dest_dx,
    /* [defaultvalue] */ DWORD readOptions);


void __RPC_STUB IVideoSrc_ReadArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_LineReverseRead_Proxy( 
    IVideoSrc __RPC_FAR * This,
    int x,
    int y,
    int dx,
    int dy,
    int destlinebytes,
    /* [size_is][out] */ BYTE __RPC_FAR *destadr,
    /* [defaultvalue] */ DWORD readOptions);


void __RPC_STUB IVideoSrc_LineReverseRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadDestPitchArea_Proxy( 
    IVideoSrc __RPC_FAR * This,
    int x,
    int y,
    int dx,
    int dy,
    int destlinebytes,
    DWORD physdest,
    /* [defaultvalue] */ DWORD readOptions);


void __RPC_STUB IVideoSrc_ReadDestPitchArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetAttr_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ LPVS_CAM_ATTR lpAttr,
    /* [defaultvalue] */ VARIANT_BOOL zoomCorrected);


void __RPC_STUB IVideoSrc_GetAttr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetReadColorRemap_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VARIANT_BOOL bEnabled);


void __RPC_STUB IVideoSrc_SetReadColorRemap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadReg_Proxy( 
    IVideoSrc __RPC_FAR * This,
    REGID reg,
    /* [retval][out] */ DWORD __RPC_FAR *regVal);


void __RPC_STUB IVideoSrc_ReadReg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteReg_Proxy( 
    IVideoSrc __RPC_FAR * This,
    REGID reg,
    DWORD val);


void __RPC_STUB IVideoSrc_WriteReg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ParamValToString_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    double dVal,
    /* [string][out][in] */ LPSTR szResult);


void __RPC_STUB IVideoSrc_ParamValToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ParamStringToVal_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    /* [string] */ LPSTR szVal,
    /* [retval][out] */ double __RPC_FAR *retVal);


void __RPC_STUB IVideoSrc_ParamStringToVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_QueryUIParamUpdate_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out][in] */ double __RPC_FAR *dVal,
    VS_ACQ_PARAMS_TYPE paramID,
    DWORD index);


void __RPC_STUB IVideoSrc_QueryUIParamUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ParamGroupEditDlgExist_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE GroupID);


void __RPC_STUB IVideoSrc_ParamGroupEditDlgExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_DoParamGroupEditDialog_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE GroupID,
    VS_ACQ_PARAMS_TYPE focalParam);


void __RPC_STUB IVideoSrc_DoParamGroupEditDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ParamIsApplicable_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    DWORD index,
    /* [string][out][in] */ LPSTR ReasonNotApplicable);


void __RPC_STUB IVideoSrc_ParamIsApplicable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GroupIsApplicable_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_PARAM_GROUP_TYPE groupID,
    /* [string][out][in] */ LPSTR ReasonNotApplicable);


void __RPC_STUB IVideoSrc_GroupIsApplicable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_PrintParamAttributes_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_ACQ_PARAMS_TYPE paramID,
    VS_PARAM_GROUP_TYPE parentGroupID,
    /* [string] */ LPSTR file);


void __RPC_STUB IVideoSrc_PrintParamAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_CameraIsReserved_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR camName);


void __RPC_STUB IVideoSrc_CameraIsReserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_TransformSupported_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_TRANSFORM_TYPE eTransform);


void __RPC_STUB IVideoSrc_TransformSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetTransform_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_TRANSFORM_TYPE eTransform);


void __RPC_STUB IVideoSrc_SetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetCurrentTransform_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [retval][out] */ VS_TRANSFORM_TYPE __RPC_FAR *currentTransform);


void __RPC_STUB IVideoSrc_GetCurrentTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_QueryUICameraType_Proxy( 
    IVideoSrc __RPC_FAR * This);


void __RPC_STUB IVideoSrc_QueryUICameraType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetPortNum_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *portNum);


void __RPC_STUB IVideoSrc_GetPortNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetProps_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ VSPROPS __RPC_FAR *props);


void __RPC_STUB IVideoSrc_GetProps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetPortNum_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD portNum);


void __RPC_STUB IVideoSrc_SetPortNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetNumPorts_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *numPorts);


void __RPC_STUB IVideoSrc_GetNumPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_AddCameraType_Proxy( 
    IVideoSrc __RPC_FAR * This,
    LPSTR strNewCamName,
    LPSTR strExistCamName,
    /* [retval][out] */ DWORD __RPC_FAR *defHhandle);


void __RPC_STUB IVideoSrc_AddCameraType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_Grab_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *grabID,
    /* [in] */ DWORD dwOptions,
    DWORD dest,
    int ringNumFrames,
    int totalNumFrames,
    /* [defaultvalue] */ int x,
    /* [defaultvalue] */ int y,
    /* [defaultvalue] */ int dx,
    /* [defaultvalue] */ int dy);


void __RPC_STUB IVideoSrc_Grab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_CreateVideoStream_Proxy( 
    IVideoSrc __RPC_FAR * This,
    PVS_STREAM_PARAMS params,
    /* [retval][out] */ HVIDSTREAMSRV __RPC_FAR *vidStream);


void __RPC_STUB IVideoSrc_CreateVideoStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_DeleteVideoStream_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVIDSTREAMSRV vidStream);


void __RPC_STUB IVideoSrc_DeleteVideoStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WaitStreamPacket_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVIDSTREAMSRV srvStream,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
    /* [in] */ DWORD bytesAvailable,
    /* [out] */ DWORD __RPC_FAR *bytesRead,
    DWORD milliseconds);


void __RPC_STUB IVideoSrc_WaitStreamPacket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetDriverHandle_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *handle);


void __RPC_STUB IVideoSrc_GetDriverHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteCameraFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR cameraFileName,
    VS_FILESYS_DOMAIN_TYPE fileSysDomain,
    /* [string] */ LPSTR cameraName);


void __RPC_STUB IVideoSrc_WriteCameraFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadCamerasInFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR cameraFileName,
    VS_FILESYS_DOMAIN_TYPE fileSysDomain);


void __RPC_STUB IVideoSrc_ReadCamerasInFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReadUserConfigFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR configFileName,
    VS_FILESYS_DOMAIN_TYPE fileSysDomain);


void __RPC_STUB IVideoSrc_ReadUserConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WriteUserConfigFile_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [string] */ LPSTR configFileName,
    VS_FILESYS_DOMAIN_TYPE fileSysDomain);


void __RPC_STUB IVideoSrc_WriteUserConfigFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ConnectOutputTo_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD OutputId,
    IDispatch __RPC_FAR *sink);


void __RPC_STUB IVideoSrc_ConnectOutputTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ProduceTo_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [in] */ LPDISPATCH imgNode,
    DWORD srcOutputId);


void __RPC_STUB IVideoSrc_ProduceTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_NotifyDetachProducer_Proxy( 
    IVideoSrc __RPC_FAR * This,
    IDispatch __RPC_FAR *node,
    DWORD srcOutputId);


void __RPC_STUB IVideoSrc_NotifyDetachProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ActivateProducer_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD srcOutputId,
    VS_REF_VAL_KIND enQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IVideoSrc_ActivateProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GrabToImgNode_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_FRAME_ENCODE remoteUseEncode,
    DWORD dwOptions,
    int NumFrames,
    /* [defaultvalue] */ int x,
    /* [defaultvalue] */ int y,
    /* [defaultvalue] */ int dx,
    /* [defaultvalue] */ int dy);


void __RPC_STUB IVideoSrc_GrabToImgNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_FreezeImgNode_Proxy( 
    IVideoSrc __RPC_FAR * This);


void __RPC_STUB IVideoSrc_FreezeImgNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ReleaseEleRef_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD srcOutputId,
    HBYREFELE deRefHandle);


void __RPC_STUB IVideoSrc_ReleaseEleRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_WaitInterrupt_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSINTERRUPT hIntrObj,
    DWORD milliSeconds);


void __RPC_STUB IVideoSrc_WaitInterrupt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_DeleteInterruptObject_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSINTERRUPT hIntrObj);


void __RPC_STUB IVideoSrc_DeleteInterruptObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_ClearInterrupt_Proxy( 
    IVideoSrc __RPC_FAR * This,
    HVSINTERRUPT hIntrObj);


void __RPC_STUB IVideoSrc_ClearInterrupt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetReadCaps_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ VS_READCAP __RPC_FAR *lpCaps);


void __RPC_STUB IVideoSrc_GetReadCaps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_Close_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [defaultvalue] */ DWORD dwFlags);


void __RPC_STUB IVideoSrc_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_OutportStrobeVal_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_LEVEL_TYPE val,
    /* [defaultvalue] */ DWORD channelNum);


void __RPC_STUB IVideoSrc_OutportStrobeVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_OutportVal_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD val,
    DWORD channelNum);


void __RPC_STUB IVideoSrc_OutportVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_InportMode_Proxy( 
    IVideoSrc __RPC_FAR * This,
    BOOL strobed,
    VS_EDGE_TYPE latchEdge,
    /* [defaultvalue] */ DWORD channelNum);


void __RPC_STUB IVideoSrc_InportMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_InportVal_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD channelNum,
    DWORD __RPC_FAR *valRead);


void __RPC_STUB IVideoSrc_InportVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_InportInterruptPolarity_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VS_EDGE_TYPE intrEdge,
    /* [defaultvalue] */ DWORD channelNum);


void __RPC_STUB IVideoSrc_InportInterruptPolarity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_GetOutputNode_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [out] */ LPDISPATCH __RPC_FAR *imgNode);


void __RPC_STUB IVideoSrc_GetOutputNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_LockObject_Proxy( 
    IVideoSrc __RPC_FAR * This,
    VARIANT_BOOL lock);


void __RPC_STUB IVideoSrc_LockObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_DisconnectOutput_Proxy( 
    IVideoSrc __RPC_FAR * This,
    DWORD OutputId);


void __RPC_STUB IVideoSrc_DisconnectOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoSrc_SetOutputQueuePolicy_Proxy( 
    IVideoSrc __RPC_FAR * This,
    /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);


void __RPC_STUB IVideoSrc_SetOutputQueuePolicy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoSrc_INTERFACE_DEFINED__ */


#ifndef __IVidSrcCfg_INTERFACE_DEFINED__
#define __IVidSrcCfg_INTERFACE_DEFINED__

/* interface IVidSrcCfg */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVidSrcCfg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4593FCF6-040B-11D5-B181-00105A0F576C")
    IVidSrcCfg : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEnumVideoSrc( 
            /* [string] */ LPSTR nodeName,
            /* [in] */ DWORD index,
            /* [out][in] */ VSPROPS __RPC_FAR *props) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVideoSrc( 
            /* [string] */ LPSTR nodeName,
            /* [string] */ LPSTR videoSrcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
            /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetUser( 
            /* [string] */ LPSTR nodeName,
            /* [out][in] */ VSAUTHIDENTITY __RPC_FAR *user) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastError( 
            /* [out] */ DWORD __RPC_FAR *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDetectedVideoSrcs( 
            /* [string] */ LPSTR nodeName,
            /* [string] */ LPSTR driverDllName,
            DWORD options) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SyncSysTime( 
            /* [string] */ LPSTR nodeName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSysTimeMilliSecs( 
            /* [retval][out] */ ULONGLONG __RPC_FAR *sysTimeMillisecs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSysTimeMilliSecs( 
            /* [in] */ ULONGLONG sysTimeMillisecs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AdjustSysTimeMilliSecs( 
            /* [in] */ LONGLONG numMillisecsAdj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVidSrcCfgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVidSrcCfg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVidSrcCfg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnumVideoSrc )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            /* [in] */ DWORD index,
            /* [out][in] */ VSPROPS __RPC_FAR *props);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVideoSrc )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            /* [string] */ LPSTR videoSrcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
            /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUser )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            /* [out][in] */ VSAUTHIDENTITY __RPC_FAR *user);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLastError )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *error);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDetectedVideoSrcs )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            /* [string] */ LPSTR driverDllName,
            DWORD options);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SyncSysTime )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [string] */ LPSTR nodeName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSysTimeMilliSecs )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [retval][out] */ ULONGLONG __RPC_FAR *sysTimeMillisecs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysTimeMilliSecs )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ ULONGLONG sysTimeMillisecs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdjustSysTimeMilliSecs )( 
            IVidSrcCfg __RPC_FAR * This,
            /* [in] */ LONGLONG numMillisecsAdj);
        
        END_INTERFACE
    } IVidSrcCfgVtbl;

    interface IVidSrcCfg
    {
        CONST_VTBL struct IVidSrcCfgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVidSrcCfg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVidSrcCfg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVidSrcCfg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVidSrcCfg_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVidSrcCfg_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVidSrcCfg_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVidSrcCfg_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVidSrcCfg_GetEnumVideoSrc(This,nodeName,index,props)	\
    (This)->lpVtbl -> GetEnumVideoSrc(This,nodeName,index,props)

#define IVidSrcCfg_CreateVideoSrc(This,nodeName,videoSrcName,numParams,params,videoSrc)	\
    (This)->lpVtbl -> CreateVideoSrc(This,nodeName,videoSrcName,numParams,params,videoSrc)

#define IVidSrcCfg_SetUser(This,nodeName,user)	\
    (This)->lpVtbl -> SetUser(This,nodeName,user)

#define IVidSrcCfg_GetLastError(This,error)	\
    (This)->lpVtbl -> GetLastError(This,error)

#define IVidSrcCfg_AddDetectedVideoSrcs(This,nodeName,driverDllName,options)	\
    (This)->lpVtbl -> AddDetectedVideoSrcs(This,nodeName,driverDllName,options)

#define IVidSrcCfg_SyncSysTime(This,nodeName)	\
    (This)->lpVtbl -> SyncSysTime(This,nodeName)

#define IVidSrcCfg_GetSysTimeMilliSecs(This,sysTimeMillisecs)	\
    (This)->lpVtbl -> GetSysTimeMilliSecs(This,sysTimeMillisecs)

#define IVidSrcCfg_SetSysTimeMilliSecs(This,sysTimeMillisecs)	\
    (This)->lpVtbl -> SetSysTimeMilliSecs(This,sysTimeMillisecs)

#define IVidSrcCfg_AdjustSysTimeMilliSecs(This,numMillisecsAdj)	\
    (This)->lpVtbl -> AdjustSysTimeMilliSecs(This,numMillisecsAdj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_GetEnumVideoSrc_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [string] */ LPSTR nodeName,
    /* [in] */ DWORD index,
    /* [out][in] */ VSPROPS __RPC_FAR *props);


void __RPC_STUB IVidSrcCfg_GetEnumVideoSrc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_CreateVideoSrc_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [string] */ LPSTR nodeName,
    /* [string] */ LPSTR videoSrcName,
    /* [in] */ DWORD numParams,
    /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ],
    /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc);


void __RPC_STUB IVidSrcCfg_CreateVideoSrc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_SetUser_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [string] */ LPSTR nodeName,
    /* [out][in] */ VSAUTHIDENTITY __RPC_FAR *user);


void __RPC_STUB IVidSrcCfg_SetUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_GetLastError_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *error);


void __RPC_STUB IVidSrcCfg_GetLastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_AddDetectedVideoSrcs_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [string] */ LPSTR nodeName,
    /* [string] */ LPSTR driverDllName,
    DWORD options);


void __RPC_STUB IVidSrcCfg_AddDetectedVideoSrcs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_SyncSysTime_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [string] */ LPSTR nodeName);


void __RPC_STUB IVidSrcCfg_SyncSysTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_GetSysTimeMilliSecs_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [retval][out] */ ULONGLONG __RPC_FAR *sysTimeMillisecs);


void __RPC_STUB IVidSrcCfg_GetSysTimeMilliSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_SetSysTimeMilliSecs_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [in] */ ULONGLONG sysTimeMillisecs);


void __RPC_STUB IVidSrcCfg_SetSysTimeMilliSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVidSrcCfg_AdjustSysTimeMilliSecs_Proxy( 
    IVidSrcCfg __RPC_FAR * This,
    /* [in] */ LONGLONG numMillisecsAdj);


void __RPC_STUB IVidSrcCfg_AdjustSysTimeMilliSecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVidSrcCfg_INTERFACE_DEFINED__ */



#ifndef __VNVIDSRCLib_LIBRARY_DEFINED__
#define __VNVIDSRCLib_LIBRARY_DEFINED__

/* library VNVIDSRCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VNVIDSRCLib;

EXTERN_C const CLSID CLSID_VideoSrc;

#ifdef __cplusplus

class DECLSPEC_UUID("5B2FC363-775F-11D4-B132-00105A0F576C")
VideoSrc;
#endif

EXTERN_C const CLSID CLSID_VidSrcCfg;

#ifdef __cplusplus

class DECLSPEC_UUID("4593FCF7-040B-11D5-B181-00105A0F576C")
VidSrcCfg;
#endif
#endif /* __VNVIDSRCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
