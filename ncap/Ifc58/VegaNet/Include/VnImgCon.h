/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 10 11:23:04 2004
 */
/* Compiler settings for D:\Ifc4201\VegaNet\include\VnImgCon.idl:
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

#ifndef __VnImgCon_h__
#define __VnImgCon_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IImgNode_FWD_DEFINED__
#define __IImgNode_FWD_DEFINED__
typedef interface IImgNode IImgNode;
#endif 	/* __IImgNode_FWD_DEFINED__ */


#ifndef __IImgDisplay_FWD_DEFINED__
#define __IImgDisplay_FWD_DEFINED__
typedef interface IImgDisplay IImgDisplay;
#endif 	/* __IImgDisplay_FWD_DEFINED__ */


#ifndef __IProcNode_FWD_DEFINED__
#define __IProcNode_FWD_DEFINED__
typedef interface IProcNode IProcNode;
#endif 	/* __IProcNode_FWD_DEFINED__ */


#ifndef __IVideoStream_FWD_DEFINED__
#define __IVideoStream_FWD_DEFINED__
typedef interface IVideoStream IVideoStream;
#endif 	/* __IVideoStream_FWD_DEFINED__ */


#ifndef __IFileNode_FWD_DEFINED__
#define __IFileNode_FWD_DEFINED__
typedef interface IFileNode IFileNode;
#endif 	/* __IFileNode_FWD_DEFINED__ */


#ifndef __ImgNode_FWD_DEFINED__
#define __ImgNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImgNode ImgNode;
#else
typedef struct ImgNode ImgNode;
#endif /* __cplusplus */

#endif 	/* __ImgNode_FWD_DEFINED__ */


#ifndef __ImgDisplay_FWD_DEFINED__
#define __ImgDisplay_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImgDisplay ImgDisplay;
#else
typedef struct ImgDisplay ImgDisplay;
#endif /* __cplusplus */

#endif 	/* __ImgDisplay_FWD_DEFINED__ */


#ifndef __ProcNode_FWD_DEFINED__
#define __ProcNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class ProcNode ProcNode;
#else
typedef struct ProcNode ProcNode;
#endif /* __cplusplus */

#endif 	/* __ProcNode_FWD_DEFINED__ */


#ifndef __VideoStream_FWD_DEFINED__
#define __VideoStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoStream VideoStream;
#else
typedef struct VideoStream VideoStream;
#endif /* __cplusplus */

#endif 	/* __VideoStream_FWD_DEFINED__ */


#ifndef __FileNode_FWD_DEFINED__
#define __FileNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileNode FileNode;
#else
typedef struct FileNode FileNode;
#endif /* __cplusplus */

#endif 	/* __FileNode_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "vidsrct.h"
#include "VnVidSrc.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IImgNode_INTERFACE_DEFINED__
#define __IImgNode_INTERFACE_DEFINED__

/* interface IImgNode */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IImgNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB5D3F04-CC44-11D4-B15E-00105A0F576C")
    IImgNode : public IDistribOS
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachProducer( 
            /* [in] */ IDispatch __RPC_FAR *producer,
            DWORD srcOutputId,
            /* [in] */ VS_PRODUCER_ATTR __RPC_FAR *attr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachConsumer( 
            /* [in] */ IDispatch __RPC_FAR *consumer,
            /* [in] */ VS_CONSUMER_ATTR __RPC_FAR *attr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateNode( 
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDequeue( 
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DequeueByRef( 
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ pBYTE __RPC_FAR *frameAddr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DequeueByVal( 
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Detach( 
            VS_PROD_CONSMR_ID_KIND proConId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Enqueue( 
            /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
            DWORD frameSize,
            VARIANT_BOOL byRef,
            VS_FRAME_ENCODE Encode,
            HBYREFELE deRefHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseEleRef( 
            HBYREFELE deRefHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAttributes( 
            /* [out] */ VS_IMGNODE_ATTR __RPC_FAR *attr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProductionInterval( 
            /* [out] */ double __RPC_FAR *milliSecPerEnq) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearProductionInterval( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnqueueData( 
            /* [size_is][in] */ BYTE __RPC_FAR *data,
            DWORD numBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DequeueData( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *numBytes,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FlushData( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FlushImages( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnqueuePayload( 
            /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
            DWORD frameSize,
            VARIANT_BOOL byRef,
            VS_FRAME_ENCODE Encode,
            HBYREFELE deRefHandle,
            /* [size_is][in] */ BYTE __RPC_FAR *userPayload,
            DWORD payloadNumBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DequeueByRefPayload( 
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ pBYTE __RPC_FAR *frameAddr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent,
            /* [out] */ BYTE __RPC_FAR *userPayload,
            /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DequeueByValPayload( 
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent,
            /* [size_is][out] */ BYTE __RPC_FAR *userPayload,
            /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsActivated( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProducer( 
            /* [out] */ LPDISPATCH __RPC_FAR *producer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetQueuePolicy( 
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddDirectDerefHandler( 
            VS_DIRECT_DEREF_FUNC handler,
            pBYTE p1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImgNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImgNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImgNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerThread )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerThread )( 
            IImgNode __RPC_FAR * This,
            HSERVERTHREAD hSrvThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServer )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServerBlk )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMessage )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ HVSMESSAGE __RPC_FAR *hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IImgNode __RPC_FAR * This,
            HVSMESSAGE hMessage,
            /* [size_is][in] */ BYTE __RPC_FAR *message,
            /* [in] */ DWORD numMessageBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessage )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMessage )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitAnyMessage )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ DWORD numMsgs,
            /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
            /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlk )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVar )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysMsgQ )( 
            IImgNode __RPC_FAR * This,
            HVSMESSAGE hSysMsgQ,
            DWORD hRpcServer,
            HVSEVENT serverShutdownEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlkAsync )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVarAsync )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerEvent )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ HVSEVENT __RPC_FAR *event,
            /* [in] */ VARIANT_BOOL bManualReset,
            /* [in] */ VARIANT_BOOL bInitialState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerEvent )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessageOrEvents )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            /* [in] */ DWORD waitTimeMilliSec,
            /* [in] */ DWORD numEvents,
            /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
            /* [out] */ DWORD __RPC_FAR *waitResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetServerEvent )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseOs )( 
            IImgNode __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileCopy )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR srcFileName,
            VS_FILESYS_DOMAIN_TYPE srcDomain,
            /* [string] */ LPSTR dstFileName,
            VS_FILESYS_DOMAIN_TYPE dstDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeRpc )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
            /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
            /* [in] */ DWORD stkBlkSize,
            /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
            /* [in] */ DWORD refParamNumBytes,
            /* [out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterRpcDll )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDerivedIID )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *derivedIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            IImgNode __RPC_FAR * This,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterServer )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR serverDllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCallerLocal )( 
            IImgNode __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            DWORD processId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AttachProducer )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *producer,
            DWORD srcOutputId,
            /* [in] */ VS_PRODUCER_ATTR __RPC_FAR *attr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AttachConsumer )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *consumer,
            /* [in] */ VS_CONSUMER_ATTR __RPC_FAR *attr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateNode )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDequeue )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DequeueByRef )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ pBYTE __RPC_FAR *frameAddr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DequeueByVal )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Detach )( 
            IImgNode __RPC_FAR * This,
            VS_PROD_CONSMR_ID_KIND proConId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enqueue )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
            DWORD frameSize,
            VARIANT_BOOL byRef,
            VS_FRAME_ENCODE Encode,
            HBYREFELE deRefHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseEleRef )( 
            IImgNode __RPC_FAR * This,
            HBYREFELE deRefHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttributes )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_IMGNODE_ATTR __RPC_FAR *attr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IImgNode __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProductionInterval )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *milliSecPerEnq);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearProductionInterval )( 
            IImgNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnqueueData )( 
            IImgNode __RPC_FAR * This,
            /* [size_is][in] */ BYTE __RPC_FAR *data,
            DWORD numBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DequeueData )( 
            IImgNode __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *numBytes,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlushData )( 
            IImgNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlushImages )( 
            IImgNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnqueuePayload )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
            DWORD frameSize,
            VARIANT_BOOL byRef,
            VS_FRAME_ENCODE Encode,
            HBYREFELE deRefHandle,
            /* [size_is][in] */ BYTE __RPC_FAR *userPayload,
            DWORD payloadNumBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DequeueByRefPayload )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [out] */ pBYTE __RPC_FAR *frameAddr,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent,
            /* [out] */ BYTE __RPC_FAR *userPayload,
            /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DequeueByValPayload )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
            /* [in] */ DWORD bytesAvailable,
            /* [out] */ DWORD __RPC_FAR *frameSize,
            /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
            DWORD waitMilliSecs,
            HVSEVENT preemptEvent,
            /* [size_is][out] */ BYTE __RPC_FAR *userPayload,
            /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsActivated )( 
            IImgNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProducer )( 
            IImgNode __RPC_FAR * This,
            /* [out] */ LPDISPATCH __RPC_FAR *producer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetQueuePolicy )( 
            IImgNode __RPC_FAR * This,
            /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDirectDerefHandler )( 
            IImgNode __RPC_FAR * This,
            VS_DIRECT_DEREF_FUNC handler,
            pBYTE p1);
        
        END_INTERFACE
    } IImgNodeVtbl;

    interface IImgNode
    {
        CONST_VTBL struct IImgNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImgNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImgNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImgNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImgNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImgNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImgNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImgNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImgNode_CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)

#define IImgNode_DeleteServerThread(This,hSrvThread)	\
    (This)->lpVtbl -> DeleteServerThread(This,hSrvThread)

#define IImgNode_InvokeServer(This,dllName,funcName,retVal)	\
    (This)->lpVtbl -> InvokeServer(This,dllName,funcName,retVal)

#define IImgNode_InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)	\
    (This)->lpVtbl -> InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)

#define IImgNode_CreateMessage(This,hMessage)	\
    (This)->lpVtbl -> CreateMessage(This,hMessage)

#define IImgNode_SendMessage(This,hMessage,message,numMessageBytes)	\
    (This)->lpVtbl -> SendMessage(This,hMessage,message,numMessageBytes)

#define IImgNode_WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IImgNode_DeleteMessage(This,hMessage)	\
    (This)->lpVtbl -> DeleteMessage(This,hMessage)

#define IImgNode_WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IImgNode_InvokeClientBlk(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlk(This,funcName,paramBlock,numParamBytes)

#define IImgNode_InvokeClientVar(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVar(This,funcName,numParams,params)

#define IImgNode_SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)	\
    (This)->lpVtbl -> SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)

#define IImgNode_InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)

#define IImgNode_InvokeClientVarAsync(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVarAsync(This,funcName,numParams,params)

#define IImgNode_CreateServerEvent(This,event,bManualReset,bInitialState)	\
    (This)->lpVtbl -> CreateServerEvent(This,event,bManualReset,bInitialState)

#define IImgNode_DeleteServerEvent(This,event)	\
    (This)->lpVtbl -> DeleteServerEvent(This,event)

#define IImgNode_WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)	\
    (This)->lpVtbl -> WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)

#define IImgNode_SetServerEvent(This,event)	\
    (This)->lpVtbl -> SetServerEvent(This,event)

#define IImgNode_CloseOs(This,dwFlags)	\
    (This)->lpVtbl -> CloseOs(This,dwFlags)

#define IImgNode_FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)	\
    (This)->lpVtbl -> FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)

#define IImgNode_InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)	\
    (This)->lpVtbl -> InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)

#define IImgNode_RegisterRpcDll(This,dllName)	\
    (This)->lpVtbl -> RegisterRpcDll(This,dllName)

#define IImgNode_GetDerivedIID(This,derivedIID)	\
    (This)->lpVtbl -> GetDerivedIID(This,derivedIID)

#define IImgNode_CreateObject(This,rclsid,riid,obj)	\
    (This)->lpVtbl -> CreateObject(This,rclsid,riid,obj)

#define IImgNode_RegisterServer(This,serverDllName)	\
    (This)->lpVtbl -> RegisterServer(This,serverDllName)

#define IImgNode_IsCallerLocal(This,nodeName,processId)	\
    (This)->lpVtbl -> IsCallerLocal(This,nodeName,processId)


#define IImgNode_AttachProducer(This,producer,srcOutputId,attr)	\
    (This)->lpVtbl -> AttachProducer(This,producer,srcOutputId,attr)

#define IImgNode_AttachConsumer(This,consumer,attr)	\
    (This)->lpVtbl -> AttachConsumer(This,consumer,attr)

#define IImgNode_ActivateNode(This,attr)	\
    (This)->lpVtbl -> ActivateNode(This,attr)

#define IImgNode_QueryDequeue(This,imgAttr,frameSize,Encode)	\
    (This)->lpVtbl -> QueryDequeue(This,imgAttr,frameSize,Encode)

#define IImgNode_DequeueByRef(This,imgAttr,frameAddr,frameSize,Encode,deRefEle,waitMilliSecs,preemptEvent)	\
    (This)->lpVtbl -> DequeueByRef(This,imgAttr,frameAddr,frameSize,Encode,deRefEle,waitMilliSecs,preemptEvent)

#define IImgNode_DequeueByVal(This,imgAttr,frameDest,bytesAvailable,frameSize,Encode,waitMilliSecs,preemptEvent)	\
    (This)->lpVtbl -> DequeueByVal(This,imgAttr,frameDest,bytesAvailable,frameSize,Encode,waitMilliSecs,preemptEvent)

#define IImgNode_Detach(This,proConId)	\
    (This)->lpVtbl -> Detach(This,proConId)

#define IImgNode_Enqueue(This,imgAttr,frameAddr,frameSize,byRef,Encode,deRefHandle)	\
    (This)->lpVtbl -> Enqueue(This,imgAttr,frameAddr,frameSize,byRef,Encode,deRefHandle)

#define IImgNode_ReleaseEleRef(This,deRefHandle)	\
    (This)->lpVtbl -> ReleaseEleRef(This,deRefHandle)

#define IImgNode_GetAttributes(This,attr)	\
    (This)->lpVtbl -> GetAttributes(This,attr)

#define IImgNode_Close(This,dwFlags)	\
    (This)->lpVtbl -> Close(This,dwFlags)

#define IImgNode_GetProductionInterval(This,milliSecPerEnq)	\
    (This)->lpVtbl -> GetProductionInterval(This,milliSecPerEnq)

#define IImgNode_ClearProductionInterval(This)	\
    (This)->lpVtbl -> ClearProductionInterval(This)

#define IImgNode_EnqueueData(This,data,numBytes)	\
    (This)->lpVtbl -> EnqueueData(This,data,numBytes)

#define IImgNode_DequeueData(This,dest,bytesAvailable,numBytes,waitMilliSecs,preemptEvent)	\
    (This)->lpVtbl -> DequeueData(This,dest,bytesAvailable,numBytes,waitMilliSecs,preemptEvent)

#define IImgNode_FlushData(This)	\
    (This)->lpVtbl -> FlushData(This)

#define IImgNode_FlushImages(This)	\
    (This)->lpVtbl -> FlushImages(This)

#define IImgNode_EnqueuePayload(This,imgAttr,frameAddr,frameSize,byRef,Encode,deRefHandle,userPayload,payloadNumBytes)	\
    (This)->lpVtbl -> EnqueuePayload(This,imgAttr,frameAddr,frameSize,byRef,Encode,deRefHandle,userPayload,payloadNumBytes)

#define IImgNode_DequeueByRefPayload(This,imgAttr,frameAddr,frameSize,Encode,deRefEle,waitMilliSecs,preemptEvent,userPayload,payloadNumBytes)	\
    (This)->lpVtbl -> DequeueByRefPayload(This,imgAttr,frameAddr,frameSize,Encode,deRefEle,waitMilliSecs,preemptEvent,userPayload,payloadNumBytes)

#define IImgNode_DequeueByValPayload(This,imgAttr,frameDest,bytesAvailable,frameSize,Encode,waitMilliSecs,preemptEvent,userPayload,payloadNumBytes)	\
    (This)->lpVtbl -> DequeueByValPayload(This,imgAttr,frameDest,bytesAvailable,frameSize,Encode,waitMilliSecs,preemptEvent,userPayload,payloadNumBytes)

#define IImgNode_IsActivated(This)	\
    (This)->lpVtbl -> IsActivated(This)

#define IImgNode_GetProducer(This,producer)	\
    (This)->lpVtbl -> GetProducer(This,producer)

#define IImgNode_SetQueuePolicy(This,attr)	\
    (This)->lpVtbl -> SetQueuePolicy(This,attr)

#define IImgNode_AddDirectDerefHandler(This,handler,p1)	\
    (This)->lpVtbl -> AddDirectDerefHandler(This,handler,p1)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_AttachProducer_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *producer,
    DWORD srcOutputId,
    /* [in] */ VS_PRODUCER_ATTR __RPC_FAR *attr);


void __RPC_STUB IImgNode_AttachProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_AttachConsumer_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *consumer,
    /* [in] */ VS_CONSUMER_ATTR __RPC_FAR *attr);


void __RPC_STUB IImgNode_AttachConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_ActivateNode_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);


void __RPC_STUB IImgNode_ActivateNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_QueryDequeue_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [out] */ DWORD __RPC_FAR *frameSize,
    /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode);


void __RPC_STUB IImgNode_QueryDequeue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_DequeueByRef_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [out] */ pBYTE __RPC_FAR *frameAddr,
    /* [out] */ DWORD __RPC_FAR *frameSize,
    /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
    /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
    DWORD waitMilliSecs,
    HVSEVENT preemptEvent);


void __RPC_STUB IImgNode_DequeueByRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_DequeueByVal_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
    /* [in] */ DWORD bytesAvailable,
    /* [out] */ DWORD __RPC_FAR *frameSize,
    /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
    DWORD waitMilliSecs,
    HVSEVENT preemptEvent);


void __RPC_STUB IImgNode_DequeueByVal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_Detach_Proxy( 
    IImgNode __RPC_FAR * This,
    VS_PROD_CONSMR_ID_KIND proConId);


void __RPC_STUB IImgNode_Detach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_Enqueue_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
    DWORD frameSize,
    VARIANT_BOOL byRef,
    VS_FRAME_ENCODE Encode,
    HBYREFELE deRefHandle);


void __RPC_STUB IImgNode_Enqueue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_ReleaseEleRef_Proxy( 
    IImgNode __RPC_FAR * This,
    HBYREFELE deRefHandle);


void __RPC_STUB IImgNode_ReleaseEleRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_GetAttributes_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_IMGNODE_ATTR __RPC_FAR *attr);


void __RPC_STUB IImgNode_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_Close_Proxy( 
    IImgNode __RPC_FAR * This,
    DWORD dwFlags);


void __RPC_STUB IImgNode_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_GetProductionInterval_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *milliSecPerEnq);


void __RPC_STUB IImgNode_GetProductionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_ClearProductionInterval_Proxy( 
    IImgNode __RPC_FAR * This);


void __RPC_STUB IImgNode_ClearProductionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_EnqueueData_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [size_is][in] */ BYTE __RPC_FAR *data,
    DWORD numBytes);


void __RPC_STUB IImgNode_EnqueueData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_DequeueData_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *dest,
    /* [in] */ DWORD bytesAvailable,
    /* [out] */ DWORD __RPC_FAR *numBytes,
    DWORD waitMilliSecs,
    HVSEVENT preemptEvent);


void __RPC_STUB IImgNode_DequeueData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_FlushData_Proxy( 
    IImgNode __RPC_FAR * This);


void __RPC_STUB IImgNode_FlushData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_FlushImages_Proxy( 
    IImgNode __RPC_FAR * This);


void __RPC_STUB IImgNode_FlushImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_EnqueuePayload_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [size_is][in] */ BYTE __RPC_FAR *frameAddr,
    DWORD frameSize,
    VARIANT_BOOL byRef,
    VS_FRAME_ENCODE Encode,
    HBYREFELE deRefHandle,
    /* [size_is][in] */ BYTE __RPC_FAR *userPayload,
    DWORD payloadNumBytes);


void __RPC_STUB IImgNode_EnqueuePayload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_DequeueByRefPayload_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [out] */ pBYTE __RPC_FAR *frameAddr,
    /* [out] */ DWORD __RPC_FAR *frameSize,
    /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
    /* [out] */ HBYREFELE __RPC_FAR *deRefEle,
    DWORD waitMilliSecs,
    HVSEVENT preemptEvent,
    /* [out] */ BYTE __RPC_FAR *userPayload,
    /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes);


void __RPC_STUB IImgNode_DequeueByRefPayload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_DequeueByValPayload_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ VS_INODE_IMG_ATTR __RPC_FAR *imgAttr,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *frameDest,
    /* [in] */ DWORD bytesAvailable,
    /* [out] */ DWORD __RPC_FAR *frameSize,
    /* [out] */ VS_FRAME_ENCODE __RPC_FAR *Encode,
    DWORD waitMilliSecs,
    HVSEVENT preemptEvent,
    /* [size_is][out] */ BYTE __RPC_FAR *userPayload,
    /* [out][in] */ DWORD __RPC_FAR *payloadNumBytes);


void __RPC_STUB IImgNode_DequeueByValPayload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_IsActivated_Proxy( 
    IImgNode __RPC_FAR * This);


void __RPC_STUB IImgNode_IsActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_GetProducer_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [out] */ LPDISPATCH __RPC_FAR *producer);


void __RPC_STUB IImgNode_GetProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_SetQueuePolicy_Proxy( 
    IImgNode __RPC_FAR * This,
    /* [in] */ VS_INODE_QMNG_ATTR __RPC_FAR *attr);


void __RPC_STUB IImgNode_SetQueuePolicy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgNode_AddDirectDerefHandler_Proxy( 
    IImgNode __RPC_FAR * This,
    VS_DIRECT_DEREF_FUNC handler,
    pBYTE p1);


void __RPC_STUB IImgNode_AddDirectDerefHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImgNode_INTERFACE_DEFINED__ */


#ifndef __IImgDisplay_INTERFACE_DEFINED__
#define __IImgDisplay_INTERFACE_DEFINED__

/* interface IImgDisplay */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IImgDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA5097A0-E567-11D4-B16B-00105A0F576C")
    IImgDisplay : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDetachConsumer( 
            IDispatch __RPC_FAR *node) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateConsumer( 
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsumeFrom( 
            LPDISPATCH imgNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDisplay( 
            VS_HWND hwnd,
            DWORD Flags,
            DWORD NodeProcFunc,
            BYTE __RPC_FAR *pArg) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetOverlayDC( 
            /* [out] */ VS_HDC __RPC_FAR *overlayDC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseOverlayDC( 
            VS_HDC overlayDC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableOverlay( 
            VARIANT_BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMaxStretch( 
            /* [retval][out] */ DWORD __RPC_FAR *maxStretch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMinStretch( 
            /* [retval][out] */ DWORD __RPC_FAR *minStretch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSinkAoiPos( 
            DWORD wxAoiStart,
            DWORD wyAoiStart) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetZoom( 
            double ZoomX,
            double ZoomY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResizeWindow( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDestColorKey( 
            DWORD dwNewColorKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVideoSrcDisplay( 
            IVideoSrc __RPC_FAR *pVidSrc,
            VS_HWND hwnd,
            DWORD Flags,
            /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EOF,
            /* [defaultvalue] */ int iScale = 1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBuffDisplay( 
            BYTE __RPC_FAR *pImgBuffer,
            DWORD wWidth,
            DWORD wHeight,
            DWORD wImgBitsPP,
            VS_HWND hwnd,
            VS_COLOR eColor,
            DWORD Flags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBufferAddr( 
            BYTE __RPC_FAR *buffer) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartLiveImage( 
            IVideoSrc __RPC_FAR *vidSrc,
            /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent = VS_ICAP_INTR_EOF,
            /* [defaultvalue] */ WORD InterruptScale = 1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopLiveImage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSrcAoiPos( 
            DWORD wxAoiStart,
            DWORD wyAoiStart) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRemapColor( 
            int iFirstIndex,
            int iLastIndex,
            COLORREF RemapColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImgNode( 
            /* [out] */ IImgNode __RPC_FAR *__RPC_FAR *imgNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDestColorKey( 
            COLORREF __RPC_FAR *color) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTransform( 
            VS_TRANSFORM_TYPE eTransform) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImgDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImgDisplay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImgDisplay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImgDisplay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImgDisplay __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImgDisplay __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImgDisplay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImgDisplay __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachConsumer )( 
            IImgDisplay __RPC_FAR * This,
            IDispatch __RPC_FAR *node);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateConsumer )( 
            IImgDisplay __RPC_FAR * This,
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConsumeFrom )( 
            IImgDisplay __RPC_FAR * This,
            LPDISPATCH imgNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDisplay )( 
            IImgDisplay __RPC_FAR * This,
            VS_HWND hwnd,
            DWORD Flags,
            DWORD NodeProcFunc,
            BYTE __RPC_FAR *pArg);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IImgDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOverlayDC )( 
            IImgDisplay __RPC_FAR * This,
            /* [out] */ VS_HDC __RPC_FAR *overlayDC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseOverlayDC )( 
            IImgDisplay __RPC_FAR * This,
            VS_HDC overlayDC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableOverlay )( 
            IImgDisplay __RPC_FAR * This,
            VARIANT_BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxStretch )( 
            IImgDisplay __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *maxStretch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMinStretch )( 
            IImgDisplay __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *minStretch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSinkAoiPos )( 
            IImgDisplay __RPC_FAR * This,
            DWORD wxAoiStart,
            DWORD wyAoiStart);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoom )( 
            IImgDisplay __RPC_FAR * This,
            double ZoomX,
            double ZoomY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResizeWindow )( 
            IImgDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDestColorKey )( 
            IImgDisplay __RPC_FAR * This,
            DWORD dwNewColorKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVideoSrcDisplay )( 
            IImgDisplay __RPC_FAR * This,
            IVideoSrc __RPC_FAR *pVidSrc,
            VS_HWND hwnd,
            DWORD Flags,
            /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent,
            /* [defaultvalue] */ int iScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IImgDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateBuffDisplay )( 
            IImgDisplay __RPC_FAR * This,
            BYTE __RPC_FAR *pImgBuffer,
            DWORD wWidth,
            DWORD wHeight,
            DWORD wImgBitsPP,
            VS_HWND hwnd,
            VS_COLOR eColor,
            DWORD Flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBufferAddr )( 
            IImgDisplay __RPC_FAR * This,
            BYTE __RPC_FAR *buffer);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartLiveImage )( 
            IImgDisplay __RPC_FAR * This,
            IVideoSrc __RPC_FAR *vidSrc,
            /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent,
            /* [defaultvalue] */ WORD InterruptScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopLiveImage )( 
            IImgDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSrcAoiPos )( 
            IImgDisplay __RPC_FAR * This,
            DWORD wxAoiStart,
            DWORD wyAoiStart);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRemapColor )( 
            IImgDisplay __RPC_FAR * This,
            int iFirstIndex,
            int iLastIndex,
            COLORREF RemapColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImgNode )( 
            IImgDisplay __RPC_FAR * This,
            /* [out] */ IImgNode __RPC_FAR *__RPC_FAR *imgNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestColorKey )( 
            IImgDisplay __RPC_FAR * This,
            COLORREF __RPC_FAR *color);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransform )( 
            IImgDisplay __RPC_FAR * This,
            VS_TRANSFORM_TYPE eTransform);
        
        END_INTERFACE
    } IImgDisplayVtbl;

    interface IImgDisplay
    {
        CONST_VTBL struct IImgDisplayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImgDisplay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImgDisplay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImgDisplay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImgDisplay_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImgDisplay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImgDisplay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImgDisplay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImgDisplay_NotifyDetachConsumer(This,node)	\
    (This)->lpVtbl -> NotifyDetachConsumer(This,node)

#define IImgDisplay_ActivateConsumer(This,deQKind,areRemote)	\
    (This)->lpVtbl -> ActivateConsumer(This,deQKind,areRemote)

#define IImgDisplay_ConsumeFrom(This,imgNode)	\
    (This)->lpVtbl -> ConsumeFrom(This,imgNode)

#define IImgDisplay_CreateDisplay(This,hwnd,Flags,NodeProcFunc,pArg)	\
    (This)->lpVtbl -> CreateDisplay(This,hwnd,Flags,NodeProcFunc,pArg)

#define IImgDisplay_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IImgDisplay_GetOverlayDC(This,overlayDC)	\
    (This)->lpVtbl -> GetOverlayDC(This,overlayDC)

#define IImgDisplay_ReleaseOverlayDC(This,overlayDC)	\
    (This)->lpVtbl -> ReleaseOverlayDC(This,overlayDC)

#define IImgDisplay_EnableOverlay(This,bEnable)	\
    (This)->lpVtbl -> EnableOverlay(This,bEnable)

#define IImgDisplay_GetMaxStretch(This,maxStretch)	\
    (This)->lpVtbl -> GetMaxStretch(This,maxStretch)

#define IImgDisplay_GetMinStretch(This,minStretch)	\
    (This)->lpVtbl -> GetMinStretch(This,minStretch)

#define IImgDisplay_SetSinkAoiPos(This,wxAoiStart,wyAoiStart)	\
    (This)->lpVtbl -> SetSinkAoiPos(This,wxAoiStart,wyAoiStart)

#define IImgDisplay_SetZoom(This,ZoomX,ZoomY)	\
    (This)->lpVtbl -> SetZoom(This,ZoomX,ZoomY)

#define IImgDisplay_ResizeWindow(This)	\
    (This)->lpVtbl -> ResizeWindow(This)

#define IImgDisplay_SetDestColorKey(This,dwNewColorKey)	\
    (This)->lpVtbl -> SetDestColorKey(This,dwNewColorKey)

#define IImgDisplay_CreateVideoSrcDisplay(This,pVidSrc,hwnd,Flags,intrEvent,iScale)	\
    (This)->lpVtbl -> CreateVideoSrcDisplay(This,pVidSrc,hwnd,Flags,intrEvent,iScale)

#define IImgDisplay_Display(This)	\
    (This)->lpVtbl -> Display(This)

#define IImgDisplay_CreateBuffDisplay(This,pImgBuffer,wWidth,wHeight,wImgBitsPP,hwnd,eColor,Flags)	\
    (This)->lpVtbl -> CreateBuffDisplay(This,pImgBuffer,wWidth,wHeight,wImgBitsPP,hwnd,eColor,Flags)

#define IImgDisplay_SetBufferAddr(This,buffer)	\
    (This)->lpVtbl -> SetBufferAddr(This,buffer)

#define IImgDisplay_StartLiveImage(This,vidSrc,intrEvent,InterruptScale)	\
    (This)->lpVtbl -> StartLiveImage(This,vidSrc,intrEvent,InterruptScale)

#define IImgDisplay_StopLiveImage(This)	\
    (This)->lpVtbl -> StopLiveImage(This)

#define IImgDisplay_SetSrcAoiPos(This,wxAoiStart,wyAoiStart)	\
    (This)->lpVtbl -> SetSrcAoiPos(This,wxAoiStart,wyAoiStart)

#define IImgDisplay_SetRemapColor(This,iFirstIndex,iLastIndex,RemapColor)	\
    (This)->lpVtbl -> SetRemapColor(This,iFirstIndex,iLastIndex,RemapColor)

#define IImgDisplay_GetImgNode(This,imgNode)	\
    (This)->lpVtbl -> GetImgNode(This,imgNode)

#define IImgDisplay_GetDestColorKey(This,color)	\
    (This)->lpVtbl -> GetDestColorKey(This,color)

#define IImgDisplay_SetTransform(This,eTransform)	\
    (This)->lpVtbl -> SetTransform(This,eTransform)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_NotifyDetachConsumer_Proxy( 
    IImgDisplay __RPC_FAR * This,
    IDispatch __RPC_FAR *node);


void __RPC_STUB IImgDisplay_NotifyDetachConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_ActivateConsumer_Proxy( 
    IImgDisplay __RPC_FAR * This,
    VS_REF_VAL_KIND deQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IImgDisplay_ActivateConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_ConsumeFrom_Proxy( 
    IImgDisplay __RPC_FAR * This,
    LPDISPATCH imgNode);


void __RPC_STUB IImgDisplay_ConsumeFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_CreateDisplay_Proxy( 
    IImgDisplay __RPC_FAR * This,
    VS_HWND hwnd,
    DWORD Flags,
    DWORD NodeProcFunc,
    BYTE __RPC_FAR *pArg);


void __RPC_STUB IImgDisplay_CreateDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_Close_Proxy( 
    IImgDisplay __RPC_FAR * This);


void __RPC_STUB IImgDisplay_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_GetOverlayDC_Proxy( 
    IImgDisplay __RPC_FAR * This,
    /* [out] */ VS_HDC __RPC_FAR *overlayDC);


void __RPC_STUB IImgDisplay_GetOverlayDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_ReleaseOverlayDC_Proxy( 
    IImgDisplay __RPC_FAR * This,
    VS_HDC overlayDC);


void __RPC_STUB IImgDisplay_ReleaseOverlayDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_EnableOverlay_Proxy( 
    IImgDisplay __RPC_FAR * This,
    VARIANT_BOOL bEnable);


void __RPC_STUB IImgDisplay_EnableOverlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_GetMaxStretch_Proxy( 
    IImgDisplay __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *maxStretch);


void __RPC_STUB IImgDisplay_GetMaxStretch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_GetMinStretch_Proxy( 
    IImgDisplay __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *minStretch);


void __RPC_STUB IImgDisplay_GetMinStretch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetSinkAoiPos_Proxy( 
    IImgDisplay __RPC_FAR * This,
    DWORD wxAoiStart,
    DWORD wyAoiStart);


void __RPC_STUB IImgDisplay_SetSinkAoiPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetZoom_Proxy( 
    IImgDisplay __RPC_FAR * This,
    double ZoomX,
    double ZoomY);


void __RPC_STUB IImgDisplay_SetZoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_ResizeWindow_Proxy( 
    IImgDisplay __RPC_FAR * This);


void __RPC_STUB IImgDisplay_ResizeWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetDestColorKey_Proxy( 
    IImgDisplay __RPC_FAR * This,
    DWORD dwNewColorKey);


void __RPC_STUB IImgDisplay_SetDestColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_CreateVideoSrcDisplay_Proxy( 
    IImgDisplay __RPC_FAR * This,
    IVideoSrc __RPC_FAR *pVidSrc,
    VS_HWND hwnd,
    DWORD Flags,
    /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent,
    /* [defaultvalue] */ int iScale);


void __RPC_STUB IImgDisplay_CreateVideoSrcDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_Display_Proxy( 
    IImgDisplay __RPC_FAR * This);


void __RPC_STUB IImgDisplay_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_CreateBuffDisplay_Proxy( 
    IImgDisplay __RPC_FAR * This,
    BYTE __RPC_FAR *pImgBuffer,
    DWORD wWidth,
    DWORD wHeight,
    DWORD wImgBitsPP,
    VS_HWND hwnd,
    VS_COLOR eColor,
    DWORD Flags);


void __RPC_STUB IImgDisplay_CreateBuffDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetBufferAddr_Proxy( 
    IImgDisplay __RPC_FAR * This,
    BYTE __RPC_FAR *buffer);


void __RPC_STUB IImgDisplay_SetBufferAddr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_StartLiveImage_Proxy( 
    IImgDisplay __RPC_FAR * This,
    IVideoSrc __RPC_FAR *vidSrc,
    /* [defaultvalue] */ VS_ICAP_INTR_EVENT intrEvent,
    /* [defaultvalue] */ WORD InterruptScale);


void __RPC_STUB IImgDisplay_StartLiveImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_StopLiveImage_Proxy( 
    IImgDisplay __RPC_FAR * This);


void __RPC_STUB IImgDisplay_StopLiveImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetSrcAoiPos_Proxy( 
    IImgDisplay __RPC_FAR * This,
    DWORD wxAoiStart,
    DWORD wyAoiStart);


void __RPC_STUB IImgDisplay_SetSrcAoiPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetRemapColor_Proxy( 
    IImgDisplay __RPC_FAR * This,
    int iFirstIndex,
    int iLastIndex,
    COLORREF RemapColor);


void __RPC_STUB IImgDisplay_SetRemapColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_GetImgNode_Proxy( 
    IImgDisplay __RPC_FAR * This,
    /* [out] */ IImgNode __RPC_FAR *__RPC_FAR *imgNode);


void __RPC_STUB IImgDisplay_GetImgNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_GetDestColorKey_Proxy( 
    IImgDisplay __RPC_FAR * This,
    COLORREF __RPC_FAR *color);


void __RPC_STUB IImgDisplay_GetDestColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImgDisplay_SetTransform_Proxy( 
    IImgDisplay __RPC_FAR * This,
    VS_TRANSFORM_TYPE eTransform);


void __RPC_STUB IImgDisplay_SetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImgDisplay_INTERFACE_DEFINED__ */


#ifndef __IProcNode_INTERFACE_DEFINED__
#define __IProcNode_INTERFACE_DEFINED__

/* interface IProcNode */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IProcNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CFAE486-F149-11D4-B16E-00105A0F576C")
    IProcNode : public IDistribOS
    {
    public:
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseEleRef( 
            DWORD srcOutputId,
            HBYREFELE deRefHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDetachConsumer( 
            IDispatch __RPC_FAR *node) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateConsumer( 
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsumeFrom( 
            LPDISPATCH imgNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateThread( 
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteThread( 
            HPROCESSTHREAD hSrvThread) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVideoSrc( 
            IVideoSrc __RPC_FAR *videoSrc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectOutputTo( 
            DWORD OutputId,
            IDispatch __RPC_FAR *sink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateClientObjThread( 
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [size_is][in] */ IDispatch __RPC_FAR *__RPC_FAR *userObjs,
            DWORD numUserObjs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateServerObjThread( 
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectOutput( 
            DWORD OutputId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoSource( 
            /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOutputQueuePolicy( 
            DWORD outputId,
            VS_INODE_QMNG_ATTR __RPC_FAR *attr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProcNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IProcNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IProcNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerThread )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HSERVERTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerThread )( 
            IProcNode __RPC_FAR * This,
            HSERVERTHREAD hSrvThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServer )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeServerBlk )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [out] */ DWORD __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMessage )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HVSMESSAGE __RPC_FAR *hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IProcNode __RPC_FAR * This,
            HVSMESSAGE hMessage,
            /* [size_is][in] */ BYTE __RPC_FAR *message,
            /* [in] */ DWORD numMessageBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessage )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteMessage )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitAnyMessage )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ DWORD numMsgs,
            /* [size_is][in] */ HVSMESSAGE __RPC_FAR *hMessages,
            /* [out] */ HVSMESSAGE __RPC_FAR *rcvMsg,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            DWORD waitTimeMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlk )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][out][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVar )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][out][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysMsgQ )( 
            IProcNode __RPC_FAR * This,
            HVSMESSAGE hSysMsgQ,
            DWORD hRpcServer,
            HVSEVENT serverShutdownEvent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientBlkAsync )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeClientVarAsync )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR funcName,
            /* [in] */ DWORD numParams,
            /* [size_is][in] */ VSPARAM __RPC_FAR params[  ]);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerEvent )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HVSEVENT __RPC_FAR *event,
            /* [in] */ VARIANT_BOOL bManualReset,
            /* [in] */ VARIANT_BOOL bInitialState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteServerEvent )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitMessageOrEvents )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ HVSMESSAGE hMessage,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *message,
            /* [out] */ DWORD __RPC_FAR *numMessageBytes,
            /* [in] */ DWORD bytesAvailable,
            /* [in] */ DWORD waitTimeMilliSec,
            /* [in] */ DWORD numEvents,
            /* [size_is][in] */ HVSEVENT __RPC_FAR *events,
            /* [out] */ DWORD __RPC_FAR *waitResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetServerEvent )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ HVSEVENT event);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseOs )( 
            IProcNode __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileCopy )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR srcFileName,
            VS_FILESYS_DOMAIN_TYPE srcDomain,
            /* [string] */ LPSTR dstFileName,
            VS_FILESYS_DOMAIN_TYPE dstDomain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeRpc )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ VS_RPC_INVOKE_STRUCT __RPC_FAR *desc,
            /* [size_is][in] */ DWORD __RPC_FAR *stkBlk,
            /* [in] */ DWORD stkBlkSize,
            /* [size_is][out][in] */ BYTE __RPC_FAR *refParams,
            /* [in] */ DWORD refParamNumBytes,
            /* [out] */ double __RPC_FAR *retVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterRpcDll )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR dllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDerivedIID )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *derivedIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            IProcNode __RPC_FAR * This,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterServer )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR serverDllName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCallerLocal )( 
            IProcNode __RPC_FAR * This,
            /* [string] */ LPSTR nodeName,
            DWORD processId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProduceTo )( 
            IProcNode __RPC_FAR * This,
            /* [in] */ LPDISPATCH imgNode,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachProducer )( 
            IProcNode __RPC_FAR * This,
            IDispatch __RPC_FAR *node,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateProducer )( 
            IProcNode __RPC_FAR * This,
            DWORD srcOutputId,
            VS_REF_VAL_KIND enQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseEleRef )( 
            IProcNode __RPC_FAR * This,
            DWORD srcOutputId,
            HBYREFELE deRefHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachConsumer )( 
            IProcNode __RPC_FAR * This,
            IDispatch __RPC_FAR *node);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateConsumer )( 
            IProcNode __RPC_FAR * This,
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConsumeFrom )( 
            IProcNode __RPC_FAR * This,
            LPDISPATCH imgNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IProcNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateThread )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteThread )( 
            IProcNode __RPC_FAR * This,
            HPROCESSTHREAD hSrvThread);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoSrc )( 
            IProcNode __RPC_FAR * This,
            IVideoSrc __RPC_FAR *videoSrc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectOutputTo )( 
            IProcNode __RPC_FAR * This,
            DWORD OutputId,
            IDispatch __RPC_FAR *sink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateClientObjThread )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            /* [string] */ LPSTR dllName,
            /* [string] */ LPSTR funcName,
            /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
            /* [in] */ DWORD numParamBytes,
            /* [size_is][in] */ IDispatch __RPC_FAR *__RPC_FAR *userObjs,
            DWORD numUserObjs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateServerObjThread )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
            REFCLSID rclsid,
            REFIID riid,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectOutput )( 
            IProcNode __RPC_FAR * This,
            DWORD OutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoSource )( 
            IProcNode __RPC_FAR * This,
            /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputQueuePolicy )( 
            IProcNode __RPC_FAR * This,
            DWORD outputId,
            VS_INODE_QMNG_ATTR __RPC_FAR *attr);
        
        END_INTERFACE
    } IProcNodeVtbl;

    interface IProcNode
    {
        CONST_VTBL struct IProcNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IProcNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IProcNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IProcNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IProcNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IProcNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IProcNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IProcNode_CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> CreateServerThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)

#define IProcNode_DeleteServerThread(This,hSrvThread)	\
    (This)->lpVtbl -> DeleteServerThread(This,hSrvThread)

#define IProcNode_InvokeServer(This,dllName,funcName,retVal)	\
    (This)->lpVtbl -> InvokeServer(This,dllName,funcName,retVal)

#define IProcNode_InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)	\
    (This)->lpVtbl -> InvokeServerBlk(This,dllName,funcName,paramBlock,numParamBytes,retVal)

#define IProcNode_CreateMessage(This,hMessage)	\
    (This)->lpVtbl -> CreateMessage(This,hMessage)

#define IProcNode_SendMessage(This,hMessage,message,numMessageBytes)	\
    (This)->lpVtbl -> SendMessage(This,hMessage,message,numMessageBytes)

#define IProcNode_WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitMessage(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IProcNode_DeleteMessage(This,hMessage)	\
    (This)->lpVtbl -> DeleteMessage(This,hMessage)

#define IProcNode_WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)	\
    (This)->lpVtbl -> WaitAnyMessage(This,numMsgs,hMessages,rcvMsg,message,numMessageBytes,bytesAvailable,waitTimeMilliSec)

#define IProcNode_InvokeClientBlk(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlk(This,funcName,paramBlock,numParamBytes)

#define IProcNode_InvokeClientVar(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVar(This,funcName,numParams,params)

#define IProcNode_SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)	\
    (This)->lpVtbl -> SetSysMsgQ(This,hSysMsgQ,hRpcServer,serverShutdownEvent)

#define IProcNode_InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> InvokeClientBlkAsync(This,funcName,paramBlock,numParamBytes)

#define IProcNode_InvokeClientVarAsync(This,funcName,numParams,params)	\
    (This)->lpVtbl -> InvokeClientVarAsync(This,funcName,numParams,params)

#define IProcNode_CreateServerEvent(This,event,bManualReset,bInitialState)	\
    (This)->lpVtbl -> CreateServerEvent(This,event,bManualReset,bInitialState)

#define IProcNode_DeleteServerEvent(This,event)	\
    (This)->lpVtbl -> DeleteServerEvent(This,event)

#define IProcNode_WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)	\
    (This)->lpVtbl -> WaitMessageOrEvents(This,hMessage,message,numMessageBytes,bytesAvailable,waitTimeMilliSec,numEvents,events,waitResult)

#define IProcNode_SetServerEvent(This,event)	\
    (This)->lpVtbl -> SetServerEvent(This,event)

#define IProcNode_CloseOs(This,dwFlags)	\
    (This)->lpVtbl -> CloseOs(This,dwFlags)

#define IProcNode_FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)	\
    (This)->lpVtbl -> FileCopy(This,srcFileName,srcDomain,dstFileName,dstDomain)

#define IProcNode_InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)	\
    (This)->lpVtbl -> InvokeRpc(This,desc,stkBlk,stkBlkSize,refParams,refParamNumBytes,retVal)

#define IProcNode_RegisterRpcDll(This,dllName)	\
    (This)->lpVtbl -> RegisterRpcDll(This,dllName)

#define IProcNode_GetDerivedIID(This,derivedIID)	\
    (This)->lpVtbl -> GetDerivedIID(This,derivedIID)

#define IProcNode_CreateObject(This,rclsid,riid,obj)	\
    (This)->lpVtbl -> CreateObject(This,rclsid,riid,obj)

#define IProcNode_RegisterServer(This,serverDllName)	\
    (This)->lpVtbl -> RegisterServer(This,serverDllName)

#define IProcNode_IsCallerLocal(This,nodeName,processId)	\
    (This)->lpVtbl -> IsCallerLocal(This,nodeName,processId)


#define IProcNode_ProduceTo(This,imgNode,srcOutputId)	\
    (This)->lpVtbl -> ProduceTo(This,imgNode,srcOutputId)

#define IProcNode_NotifyDetachProducer(This,node,srcOutputId)	\
    (This)->lpVtbl -> NotifyDetachProducer(This,node,srcOutputId)

#define IProcNode_ActivateProducer(This,srcOutputId,enQKind,areRemote)	\
    (This)->lpVtbl -> ActivateProducer(This,srcOutputId,enQKind,areRemote)

#define IProcNode_ReleaseEleRef(This,srcOutputId,deRefHandle)	\
    (This)->lpVtbl -> ReleaseEleRef(This,srcOutputId,deRefHandle)

#define IProcNode_NotifyDetachConsumer(This,node)	\
    (This)->lpVtbl -> NotifyDetachConsumer(This,node)

#define IProcNode_ActivateConsumer(This,deQKind,areRemote)	\
    (This)->lpVtbl -> ActivateConsumer(This,deQKind,areRemote)

#define IProcNode_ConsumeFrom(This,imgNode)	\
    (This)->lpVtbl -> ConsumeFrom(This,imgNode)

#define IProcNode_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IProcNode_CreateThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)	\
    (This)->lpVtbl -> CreateThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes)

#define IProcNode_DeleteThread(This,hSrvThread)	\
    (This)->lpVtbl -> DeleteThread(This,hSrvThread)

#define IProcNode_SetVideoSrc(This,videoSrc)	\
    (This)->lpVtbl -> SetVideoSrc(This,videoSrc)

#define IProcNode_ConnectOutputTo(This,OutputId,sink)	\
    (This)->lpVtbl -> ConnectOutputTo(This,OutputId,sink)

#define IProcNode_CreateClientObjThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes,userObjs,numUserObjs)	\
    (This)->lpVtbl -> CreateClientObjThread(This,hSrvThread,dllName,funcName,paramBlock,numParamBytes,userObjs,numUserObjs)

#define IProcNode_CreateServerObjThread(This,hSrvThread,rclsid,riid,obj)	\
    (This)->lpVtbl -> CreateServerObjThread(This,hSrvThread,rclsid,riid,obj)

#define IProcNode_DisconnectOutput(This,OutputId)	\
    (This)->lpVtbl -> DisconnectOutput(This,OutputId)

#define IProcNode_GetVideoSource(This,videoSrc)	\
    (This)->lpVtbl -> GetVideoSource(This,videoSrc)

#define IProcNode_SetOutputQueuePolicy(This,outputId,attr)	\
    (This)->lpVtbl -> SetOutputQueuePolicy(This,outputId,attr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ProduceTo_Proxy( 
    IProcNode __RPC_FAR * This,
    /* [in] */ LPDISPATCH imgNode,
    DWORD srcOutputId);


void __RPC_STUB IProcNode_ProduceTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_NotifyDetachProducer_Proxy( 
    IProcNode __RPC_FAR * This,
    IDispatch __RPC_FAR *node,
    DWORD srcOutputId);


void __RPC_STUB IProcNode_NotifyDetachProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ActivateProducer_Proxy( 
    IProcNode __RPC_FAR * This,
    DWORD srcOutputId,
    VS_REF_VAL_KIND enQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IProcNode_ActivateProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ReleaseEleRef_Proxy( 
    IProcNode __RPC_FAR * This,
    DWORD srcOutputId,
    HBYREFELE deRefHandle);


void __RPC_STUB IProcNode_ReleaseEleRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_NotifyDetachConsumer_Proxy( 
    IProcNode __RPC_FAR * This,
    IDispatch __RPC_FAR *node);


void __RPC_STUB IProcNode_NotifyDetachConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ActivateConsumer_Proxy( 
    IProcNode __RPC_FAR * This,
    VS_REF_VAL_KIND deQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IProcNode_ActivateConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ConsumeFrom_Proxy( 
    IProcNode __RPC_FAR * This,
    LPDISPATCH imgNode);


void __RPC_STUB IProcNode_ConsumeFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_Close_Proxy( 
    IProcNode __RPC_FAR * This);


void __RPC_STUB IProcNode_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_CreateThread_Proxy( 
    IProcNode __RPC_FAR * This,
    /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
    /* [string] */ LPSTR dllName,
    /* [string] */ LPSTR funcName,
    /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes);


void __RPC_STUB IProcNode_CreateThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_DeleteThread_Proxy( 
    IProcNode __RPC_FAR * This,
    HPROCESSTHREAD hSrvThread);


void __RPC_STUB IProcNode_DeleteThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_SetVideoSrc_Proxy( 
    IProcNode __RPC_FAR * This,
    IVideoSrc __RPC_FAR *videoSrc);


void __RPC_STUB IProcNode_SetVideoSrc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_ConnectOutputTo_Proxy( 
    IProcNode __RPC_FAR * This,
    DWORD OutputId,
    IDispatch __RPC_FAR *sink);


void __RPC_STUB IProcNode_ConnectOutputTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_CreateClientObjThread_Proxy( 
    IProcNode __RPC_FAR * This,
    /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
    /* [string] */ LPSTR dllName,
    /* [string] */ LPSTR funcName,
    /* [size_is][in] */ BYTE __RPC_FAR *paramBlock,
    /* [in] */ DWORD numParamBytes,
    /* [size_is][in] */ IDispatch __RPC_FAR *__RPC_FAR *userObjs,
    DWORD numUserObjs);


void __RPC_STUB IProcNode_CreateClientObjThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_CreateServerObjThread_Proxy( 
    IProcNode __RPC_FAR * This,
    /* [out] */ HPROCESSTHREAD __RPC_FAR *hSrvThread,
    REFCLSID rclsid,
    REFIID riid,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *obj);


void __RPC_STUB IProcNode_CreateServerObjThread_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_DisconnectOutput_Proxy( 
    IProcNode __RPC_FAR * This,
    DWORD OutputId);


void __RPC_STUB IProcNode_DisconnectOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_GetVideoSource_Proxy( 
    IProcNode __RPC_FAR * This,
    /* [out] */ IVideoSrc __RPC_FAR *__RPC_FAR *videoSrc);


void __RPC_STUB IProcNode_GetVideoSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IProcNode_SetOutputQueuePolicy_Proxy( 
    IProcNode __RPC_FAR * This,
    DWORD outputId,
    VS_INODE_QMNG_ATTR __RPC_FAR *attr);


void __RPC_STUB IProcNode_SetOutputQueuePolicy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProcNode_INTERFACE_DEFINED__ */


#ifndef __IVideoStream_INTERFACE_DEFINED__
#define __IVideoStream_INTERFACE_DEFINED__

/* interface IVideoStream */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVideoStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8037116-08D8-11D5-B183-00105A0F576C")
    IVideoStream : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectOutputTo( 
            IDispatch __RPC_FAR *sink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetClientObject( 
            HVIDSTREAM clientvStream) = 0;
        
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
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseEleRef( 
            DWORD srcOutputId,
            HBYREFELE deRefHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( 
            DWORD dwFlags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitStreamFrame( 
            BYTE __RPC_FAR *dest,
            PVS_STREAM_FRAME_ATTR frameAttr,
            DWORD milliseconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVideoStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVideoStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVideoStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVideoStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectOutputTo )( 
            IVideoStream __RPC_FAR * This,
            IDispatch __RPC_FAR *sink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetClientObject )( 
            IVideoStream __RPC_FAR * This,
            HVIDSTREAM clientvStream);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProduceTo )( 
            IVideoStream __RPC_FAR * This,
            /* [in] */ LPDISPATCH imgNode,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachProducer )( 
            IVideoStream __RPC_FAR * This,
            IDispatch __RPC_FAR *node,
            DWORD srcOutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateProducer )( 
            IVideoStream __RPC_FAR * This,
            DWORD srcOutputId,
            VS_REF_VAL_KIND enQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseEleRef )( 
            IVideoStream __RPC_FAR * This,
            DWORD srcOutputId,
            HBYREFELE deRefHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IVideoStream __RPC_FAR * This,
            DWORD dwFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitStreamFrame )( 
            IVideoStream __RPC_FAR * This,
            BYTE __RPC_FAR *dest,
            PVS_STREAM_FRAME_ATTR frameAttr,
            DWORD milliseconds);
        
        END_INTERFACE
    } IVideoStreamVtbl;

    interface IVideoStream
    {
        CONST_VTBL struct IVideoStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoStream_ConnectOutputTo(This,sink)	\
    (This)->lpVtbl -> ConnectOutputTo(This,sink)

#define IVideoStream_SetClientObject(This,clientvStream)	\
    (This)->lpVtbl -> SetClientObject(This,clientvStream)

#define IVideoStream_ProduceTo(This,imgNode,srcOutputId)	\
    (This)->lpVtbl -> ProduceTo(This,imgNode,srcOutputId)

#define IVideoStream_NotifyDetachProducer(This,node,srcOutputId)	\
    (This)->lpVtbl -> NotifyDetachProducer(This,node,srcOutputId)

#define IVideoStream_ActivateProducer(This,srcOutputId,enQKind,areRemote)	\
    (This)->lpVtbl -> ActivateProducer(This,srcOutputId,enQKind,areRemote)

#define IVideoStream_ReleaseEleRef(This,srcOutputId,deRefHandle)	\
    (This)->lpVtbl -> ReleaseEleRef(This,srcOutputId,deRefHandle)

#define IVideoStream_Close(This,dwFlags)	\
    (This)->lpVtbl -> Close(This,dwFlags)

#define IVideoStream_WaitStreamFrame(This,dest,frameAttr,milliseconds)	\
    (This)->lpVtbl -> WaitStreamFrame(This,dest,frameAttr,milliseconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_ConnectOutputTo_Proxy( 
    IVideoStream __RPC_FAR * This,
    IDispatch __RPC_FAR *sink);


void __RPC_STUB IVideoStream_ConnectOutputTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_SetClientObject_Proxy( 
    IVideoStream __RPC_FAR * This,
    HVIDSTREAM clientvStream);


void __RPC_STUB IVideoStream_SetClientObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_ProduceTo_Proxy( 
    IVideoStream __RPC_FAR * This,
    /* [in] */ LPDISPATCH imgNode,
    DWORD srcOutputId);


void __RPC_STUB IVideoStream_ProduceTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_NotifyDetachProducer_Proxy( 
    IVideoStream __RPC_FAR * This,
    IDispatch __RPC_FAR *node,
    DWORD srcOutputId);


void __RPC_STUB IVideoStream_NotifyDetachProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_ActivateProducer_Proxy( 
    IVideoStream __RPC_FAR * This,
    DWORD srcOutputId,
    VS_REF_VAL_KIND enQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IVideoStream_ActivateProducer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_ReleaseEleRef_Proxy( 
    IVideoStream __RPC_FAR * This,
    DWORD srcOutputId,
    HBYREFELE deRefHandle);


void __RPC_STUB IVideoStream_ReleaseEleRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_Close_Proxy( 
    IVideoStream __RPC_FAR * This,
    DWORD dwFlags);


void __RPC_STUB IVideoStream_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoStream_WaitStreamFrame_Proxy( 
    IVideoStream __RPC_FAR * This,
    BYTE __RPC_FAR *dest,
    PVS_STREAM_FRAME_ATTR frameAttr,
    DWORD milliseconds);


void __RPC_STUB IVideoStream_WaitStreamFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoStream_INTERFACE_DEFINED__ */


#ifndef __IFileNode_INTERFACE_DEFINED__
#define __IFileNode_INTERFACE_DEFINED__

/* interface IFileNode */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFileNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5938B66-9344-11D5-B1EC-00105A0F576C")
    IFileNode : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartWrite( 
            /* [string] */ LPSTR fileName,
            VS_FRAME_ENCODE Encode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopWrite( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartRead( 
            /* [string] */ LPSTR fileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopRead( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ThreadFunction( 
            HCProcThread threadObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetProcNode( 
            IProcNode __RPC_FAR *procNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectOutputTo( 
            DWORD OutputId,
            IDispatch __RPC_FAR *sink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyDetachConsumer( 
            IDispatch __RPC_FAR *node) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateConsumer( 
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConsumeFrom( 
            LPDISPATCH imgNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRec( 
            DWORD rec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRec( 
            /* [out] */ DWORD __RPC_FAR *rec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadIsComplete( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartRandomRead( 
            /* [string] */ LPSTR fileName,
            /* [out] */ DWORD __RPC_FAR *numFrames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadRandom( 
            DWORD frameNum) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWriteQuality( 
            int quality) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectOutput( 
            DWORD OutputId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSaveStats( 
            /* [out] */ DWORD __RPC_FAR *numFramesSaved,
            /* [out] */ DWORD __RPC_FAR *numFramesAcquired) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReadRate( 
            double framesPerSecond) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartReadFrom( 
            LPSTR fileName,
            DWORD startIndex,
            int readIndexAdjust) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetReadFilePos( 
            DWORD __RPC_FAR *readIndex,
            DWORD __RPC_FAR *fileNumFrames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartWriteEx( 
            LPSTR fileName,
            VS_FRAME_ENCODE Encode,
            FN_SOUND_DESC __RPC_FAR *sound,
            GUID __RPC_FAR *pSndDeviceGuid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVolume( 
            LONG lVolume) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVolume( 
            /* [out] */ LONG __RPC_FAR *plVolume) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRecordParam( 
            VS_RECORD_PARM paramID,
            double value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartWriteAVI( 
            /* [string] */ LPSTR fileName,
            VS_AVICOMPRESSOPTIONS __RPC_FAR *options,
            FN_SOUND_DESC __RPC_FAR *sound,
            GUID __RPC_FAR *pSndDeviceGuid,
            DWORD flags) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBayer( 
            VS_BAYER_FILTER_TYPE filter,
            VS_BAYER_EXT_ATTR __RPC_FAR *bayerExtAttr,
            DWORD options) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFileNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFileNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFileNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFileNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFileNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFileNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFileNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartWrite )( 
            IFileNode __RPC_FAR * This,
            /* [string] */ LPSTR fileName,
            VS_FRAME_ENCODE Encode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopWrite )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartRead )( 
            IFileNode __RPC_FAR * This,
            /* [string] */ LPSTR fileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopRead )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ThreadFunction )( 
            IFileNode __RPC_FAR * This,
            HCProcThread threadObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProcNode )( 
            IFileNode __RPC_FAR * This,
            IProcNode __RPC_FAR *procNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectOutputTo )( 
            IFileNode __RPC_FAR * This,
            DWORD OutputId,
            IDispatch __RPC_FAR *sink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyDetachConsumer )( 
            IFileNode __RPC_FAR * This,
            IDispatch __RPC_FAR *node);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateConsumer )( 
            IFileNode __RPC_FAR * This,
            VS_REF_VAL_KIND deQKind,
            VARIANT_BOOL areRemote);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConsumeFrom )( 
            IFileNode __RPC_FAR * This,
            LPDISPATCH imgNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRec )( 
            IFileNode __RPC_FAR * This,
            DWORD rec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRec )( 
            IFileNode __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *rec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadIsComplete )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartRandomRead )( 
            IFileNode __RPC_FAR * This,
            /* [string] */ LPSTR fileName,
            /* [out] */ DWORD __RPC_FAR *numFrames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadRandom )( 
            IFileNode __RPC_FAR * This,
            DWORD frameNum);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWriteQuality )( 
            IFileNode __RPC_FAR * This,
            int quality);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectOutput )( 
            IFileNode __RPC_FAR * This,
            DWORD OutputId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSaveStats )( 
            IFileNode __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *numFramesSaved,
            /* [out] */ DWORD __RPC_FAR *numFramesAcquired);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReadRate )( 
            IFileNode __RPC_FAR * This,
            double framesPerSecond);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartReadFrom )( 
            IFileNode __RPC_FAR * This,
            LPSTR fileName,
            DWORD startIndex,
            int readIndexAdjust);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReadFilePos )( 
            IFileNode __RPC_FAR * This,
            DWORD __RPC_FAR *readIndex,
            DWORD __RPC_FAR *fileNumFrames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartWriteEx )( 
            IFileNode __RPC_FAR * This,
            LPSTR fileName,
            VS_FRAME_ENCODE Encode,
            FN_SOUND_DESC __RPC_FAR *sound,
            GUID __RPC_FAR *pSndDeviceGuid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IFileNode __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVolume )( 
            IFileNode __RPC_FAR * This,
            LONG lVolume);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVolume )( 
            IFileNode __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *plVolume);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRecordParam )( 
            IFileNode __RPC_FAR * This,
            VS_RECORD_PARM paramID,
            double value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartWriteAVI )( 
            IFileNode __RPC_FAR * This,
            /* [string] */ LPSTR fileName,
            VS_AVICOMPRESSOPTIONS __RPC_FAR *options,
            FN_SOUND_DESC __RPC_FAR *sound,
            GUID __RPC_FAR *pSndDeviceGuid,
            DWORD flags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBayer )( 
            IFileNode __RPC_FAR * This,
            VS_BAYER_FILTER_TYPE filter,
            VS_BAYER_EXT_ATTR __RPC_FAR *bayerExtAttr,
            DWORD options);
        
        END_INTERFACE
    } IFileNodeVtbl;

    interface IFileNode
    {
        CONST_VTBL struct IFileNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFileNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFileNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFileNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFileNode_StartWrite(This,fileName,Encode)	\
    (This)->lpVtbl -> StartWrite(This,fileName,Encode)

#define IFileNode_StopWrite(This)	\
    (This)->lpVtbl -> StopWrite(This)

#define IFileNode_StartRead(This,fileName)	\
    (This)->lpVtbl -> StartRead(This,fileName)

#define IFileNode_StopRead(This)	\
    (This)->lpVtbl -> StopRead(This)

#define IFileNode_ThreadFunction(This,threadObj)	\
    (This)->lpVtbl -> ThreadFunction(This,threadObj)

#define IFileNode_SetProcNode(This,procNode)	\
    (This)->lpVtbl -> SetProcNode(This,procNode)

#define IFileNode_ConnectOutputTo(This,OutputId,sink)	\
    (This)->lpVtbl -> ConnectOutputTo(This,OutputId,sink)

#define IFileNode_NotifyDetachConsumer(This,node)	\
    (This)->lpVtbl -> NotifyDetachConsumer(This,node)

#define IFileNode_ActivateConsumer(This,deQKind,areRemote)	\
    (This)->lpVtbl -> ActivateConsumer(This,deQKind,areRemote)

#define IFileNode_ConsumeFrom(This,imgNode)	\
    (This)->lpVtbl -> ConsumeFrom(This,imgNode)

#define IFileNode_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IFileNode_SetRec(This,rec)	\
    (This)->lpVtbl -> SetRec(This,rec)

#define IFileNode_GetRec(This,rec)	\
    (This)->lpVtbl -> GetRec(This,rec)

#define IFileNode_ReadIsComplete(This)	\
    (This)->lpVtbl -> ReadIsComplete(This)

#define IFileNode_StartRandomRead(This,fileName,numFrames)	\
    (This)->lpVtbl -> StartRandomRead(This,fileName,numFrames)

#define IFileNode_ReadRandom(This,frameNum)	\
    (This)->lpVtbl -> ReadRandom(This,frameNum)

#define IFileNode_SetWriteQuality(This,quality)	\
    (This)->lpVtbl -> SetWriteQuality(This,quality)

#define IFileNode_DisconnectOutput(This,OutputId)	\
    (This)->lpVtbl -> DisconnectOutput(This,OutputId)

#define IFileNode_GetSaveStats(This,numFramesSaved,numFramesAcquired)	\
    (This)->lpVtbl -> GetSaveStats(This,numFramesSaved,numFramesAcquired)

#define IFileNode_SetReadRate(This,framesPerSecond)	\
    (This)->lpVtbl -> SetReadRate(This,framesPerSecond)

#define IFileNode_StartReadFrom(This,fileName,startIndex,readIndexAdjust)	\
    (This)->lpVtbl -> StartReadFrom(This,fileName,startIndex,readIndexAdjust)

#define IFileNode_GetReadFilePos(This,readIndex,fileNumFrames)	\
    (This)->lpVtbl -> GetReadFilePos(This,readIndex,fileNumFrames)

#define IFileNode_StartWriteEx(This,fileName,Encode,sound,pSndDeviceGuid)	\
    (This)->lpVtbl -> StartWriteEx(This,fileName,Encode,sound,pSndDeviceGuid)

#define IFileNode_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IFileNode_Resume(This)	\
    (This)->lpVtbl -> Resume(This)

#define IFileNode_SetVolume(This,lVolume)	\
    (This)->lpVtbl -> SetVolume(This,lVolume)

#define IFileNode_GetVolume(This,plVolume)	\
    (This)->lpVtbl -> GetVolume(This,plVolume)

#define IFileNode_SetRecordParam(This,paramID,value)	\
    (This)->lpVtbl -> SetRecordParam(This,paramID,value)

#define IFileNode_StartWriteAVI(This,fileName,options,sound,pSndDeviceGuid,flags)	\
    (This)->lpVtbl -> StartWriteAVI(This,fileName,options,sound,pSndDeviceGuid,flags)

#define IFileNode_SetBayer(This,filter,bayerExtAttr,options)	\
    (This)->lpVtbl -> SetBayer(This,filter,bayerExtAttr,options)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartWrite_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [string] */ LPSTR fileName,
    VS_FRAME_ENCODE Encode);


void __RPC_STUB IFileNode_StartWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StopWrite_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_StopWrite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartRead_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [string] */ LPSTR fileName);


void __RPC_STUB IFileNode_StartRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StopRead_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_StopRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ThreadFunction_Proxy( 
    IFileNode __RPC_FAR * This,
    HCProcThread threadObj);


void __RPC_STUB IFileNode_ThreadFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetProcNode_Proxy( 
    IFileNode __RPC_FAR * This,
    IProcNode __RPC_FAR *procNode);


void __RPC_STUB IFileNode_SetProcNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ConnectOutputTo_Proxy( 
    IFileNode __RPC_FAR * This,
    DWORD OutputId,
    IDispatch __RPC_FAR *sink);


void __RPC_STUB IFileNode_ConnectOutputTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_NotifyDetachConsumer_Proxy( 
    IFileNode __RPC_FAR * This,
    IDispatch __RPC_FAR *node);


void __RPC_STUB IFileNode_NotifyDetachConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ActivateConsumer_Proxy( 
    IFileNode __RPC_FAR * This,
    VS_REF_VAL_KIND deQKind,
    VARIANT_BOOL areRemote);


void __RPC_STUB IFileNode_ActivateConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ConsumeFrom_Proxy( 
    IFileNode __RPC_FAR * This,
    LPDISPATCH imgNode);


void __RPC_STUB IFileNode_ConsumeFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_Close_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetRec_Proxy( 
    IFileNode __RPC_FAR * This,
    DWORD rec);


void __RPC_STUB IFileNode_SetRec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_GetRec_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *rec);


void __RPC_STUB IFileNode_GetRec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ReadIsComplete_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_ReadIsComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartRandomRead_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [string] */ LPSTR fileName,
    /* [out] */ DWORD __RPC_FAR *numFrames);


void __RPC_STUB IFileNode_StartRandomRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_ReadRandom_Proxy( 
    IFileNode __RPC_FAR * This,
    DWORD frameNum);


void __RPC_STUB IFileNode_ReadRandom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetWriteQuality_Proxy( 
    IFileNode __RPC_FAR * This,
    int quality);


void __RPC_STUB IFileNode_SetWriteQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_DisconnectOutput_Proxy( 
    IFileNode __RPC_FAR * This,
    DWORD OutputId);


void __RPC_STUB IFileNode_DisconnectOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_GetSaveStats_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *numFramesSaved,
    /* [out] */ DWORD __RPC_FAR *numFramesAcquired);


void __RPC_STUB IFileNode_GetSaveStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetReadRate_Proxy( 
    IFileNode __RPC_FAR * This,
    double framesPerSecond);


void __RPC_STUB IFileNode_SetReadRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartReadFrom_Proxy( 
    IFileNode __RPC_FAR * This,
    LPSTR fileName,
    DWORD startIndex,
    int readIndexAdjust);


void __RPC_STUB IFileNode_StartReadFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_GetReadFilePos_Proxy( 
    IFileNode __RPC_FAR * This,
    DWORD __RPC_FAR *readIndex,
    DWORD __RPC_FAR *fileNumFrames);


void __RPC_STUB IFileNode_GetReadFilePos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartWriteEx_Proxy( 
    IFileNode __RPC_FAR * This,
    LPSTR fileName,
    VS_FRAME_ENCODE Encode,
    FN_SOUND_DESC __RPC_FAR *sound,
    GUID __RPC_FAR *pSndDeviceGuid);


void __RPC_STUB IFileNode_StartWriteEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_Pause_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_Resume_Proxy( 
    IFileNode __RPC_FAR * This);


void __RPC_STUB IFileNode_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetVolume_Proxy( 
    IFileNode __RPC_FAR * This,
    LONG lVolume);


void __RPC_STUB IFileNode_SetVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_GetVolume_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [out] */ LONG __RPC_FAR *plVolume);


void __RPC_STUB IFileNode_GetVolume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetRecordParam_Proxy( 
    IFileNode __RPC_FAR * This,
    VS_RECORD_PARM paramID,
    double value);


void __RPC_STUB IFileNode_SetRecordParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_StartWriteAVI_Proxy( 
    IFileNode __RPC_FAR * This,
    /* [string] */ LPSTR fileName,
    VS_AVICOMPRESSOPTIONS __RPC_FAR *options,
    FN_SOUND_DESC __RPC_FAR *sound,
    GUID __RPC_FAR *pSndDeviceGuid,
    DWORD flags);


void __RPC_STUB IFileNode_StartWriteAVI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IFileNode_SetBayer_Proxy( 
    IFileNode __RPC_FAR * This,
    VS_BAYER_FILTER_TYPE filter,
    VS_BAYER_EXT_ATTR __RPC_FAR *bayerExtAttr,
    DWORD options);


void __RPC_STUB IFileNode_SetBayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileNode_INTERFACE_DEFINED__ */



#ifndef __VNIMGCONLib_LIBRARY_DEFINED__
#define __VNIMGCONLib_LIBRARY_DEFINED__

/* library VNIMGCONLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VNIMGCONLib;

EXTERN_C const CLSID CLSID_ImgNode;

#ifdef __cplusplus

class DECLSPEC_UUID("DB5D3F05-CC44-11D4-B15E-00105A0F576C")
ImgNode;
#endif

EXTERN_C const CLSID CLSID_ImgDisplay;

#ifdef __cplusplus

class DECLSPEC_UUID("CA5097A1-E567-11D4-B16B-00105A0F576C")
ImgDisplay;
#endif

EXTERN_C const CLSID CLSID_ProcNode;

#ifdef __cplusplus

class DECLSPEC_UUID("5CFAE487-F149-11D4-B16E-00105A0F576C")
ProcNode;
#endif

EXTERN_C const CLSID CLSID_VideoStream;

#ifdef __cplusplus

class DECLSPEC_UUID("A8037117-08D8-11D5-B183-00105A0F576C")
VideoStream;
#endif

EXTERN_C const CLSID CLSID_FileNode;

#ifdef __cplusplus

class DECLSPEC_UUID("B5938B67-9344-11D5-B1EC-00105A0F576C")
FileNode;
#endif
#endif /* __VNIMGCONLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
