/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 06 15:32:10 2005
 */
/* Compiler settings for .\INStimApp.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "INStimApp.h"

#define TYPE_FORMAT_STRING_SIZE   95                                
#define PROC_FORMAT_STRING_SIZE   29                                

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_INStimApp_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INStimApp, ver. 0.0,
   GUID={0x7A1B847C,0xB96B,0x4f96,{0xAE,0x47,0xED,0xB1,0x47,0x3D,0x65,0xA0}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE INStimApp_CreateAtom_Proxy( 
    INStimApp __RPC_FAR * This,
    unsigned char __RPC_FAR *pPatchType,
    INStimAtom __RPC_FAR *__RPC_FAR *ppPatch)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!pPatchType)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppPatch)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 1U + 0U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppPatch,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( unsigned char __RPC_FAR * )_StubMsg.Buffer)++ = *pPatchType;
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppPatch,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB INStimApp_CreateAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *pPatchType;
    INStimAtom __RPC_FAR *__RPC_FAR *ppPatch;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( unsigned char __RPC_FAR * )pPatchType = 0;
    ( INStimAtom __RPC_FAR *__RPC_FAR * )ppPatch = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        pPatchType = ( unsigned char __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( unsigned char  );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppPatch,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimApp*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateAtom(
              (INStimApp *) ((CStdStubBuffer *)This)->pvServerObject,
              pPatchType,
              ppPatch);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppPatch,
                        &__MIDL_TypeFormatString.Format[6] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE INStimApp_GetGraphicsEngine_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimEngine __RPC_FAR *__RPC_FAR *ppGraphicsEngine)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!ppGraphicsEngine)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppGraphicsEngine,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppGraphicsEngine,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB INStimApp_GetGraphicsEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    INStimEngine __RPC_FAR *__RPC_FAR *ppGraphicsEngine;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( INStimEngine __RPC_FAR *__RPC_FAR * )ppGraphicsEngine = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppGraphicsEngine,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimApp*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetGraphicsEngine((INStimApp *) ((CStdStubBuffer *)This)->pvServerObject,ppGraphicsEngine);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppGraphicsEngine,
                        &__MIDL_TypeFormatString.Format[28] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE INStimApp_GetCommandEngine_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimCmdEngine __RPC_FAR *__RPC_FAR *ppCmdEngine)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        if(!ppCmdEngine)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppCmdEngine,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[50] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppCmdEngine,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[50] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[16] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB INStimApp_GetCommandEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    INStimCmdEngine __RPC_FAR *__RPC_FAR *ppCmdEngine;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( INStimCmdEngine __RPC_FAR *__RPC_FAR * )ppCmdEngine = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[16] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppCmdEngine,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[50],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimApp*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetCommandEngine((INStimApp *) ((CStdStubBuffer *)This)->pvServerObject,ppCmdEngine);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppCmdEngine,
                        &__MIDL_TypeFormatString.Format[50] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE INStimApp_GetProfile_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimProfile __RPC_FAR *__RPC_FAR *ppProfile)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        if(!ppProfile)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppProfile,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppProfile,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB INStimApp_GetProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    INStimProfile __RPC_FAR *__RPC_FAR *ppProfile;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( INStimProfile __RPC_FAR *__RPC_FAR * )ppProfile = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppProfile,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimApp*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetProfile((INStimApp *) ((CStdStubBuffer *)This)->pvServerObject,ppProfile);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppProfile,
                        &__MIDL_TypeFormatString.Format[72] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

const CINTERFACE_PROXY_VTABLE(7) _INStimAppProxyVtbl = 
{
    &IID_INStimApp,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    INStimApp_CreateAtom_Proxy ,
    INStimApp_GetGraphicsEngine_Proxy ,
    INStimApp_GetCommandEngine_Proxy ,
    INStimApp_GetProfile_Proxy
};


static const PRPC_STUB_FUNCTION INStimApp_table[] =
{
    INStimApp_CreateAtom_Stub,
    INStimApp_GetGraphicsEngine_Stub,
    INStimApp_GetCommandEngine_Stub,
    INStimApp_GetProfile_Stub
};

const CInterfaceStubVtbl _INStimAppStubVtbl =
{
    &IID_INStimApp,
    0,
    7,
    &INStimApp_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/*  8 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 10 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 12 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 14 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 16 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 18 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */
/* 20 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 22 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 24 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0xee1fe002 ),	/* -299900926 */
/* 16 */	NdrFcShort( 0x5b82 ),	/* 23426 */
/* 18 */	NdrFcShort( 0x435e ),	/* 17246 */
/* 20 */	0xb1,		/* 177 */
			0x43,		/* 67 */
/* 22 */	0xdb,		/* 219 */
			0xa4,		/* 164 */
/* 24 */	0x9f,		/* 159 */
			0x2c,		/* 44 */
/* 26 */	0xf1,		/* 241 */
			0x8b,		/* 139 */
/* 28 */	
			0x11, 0x10,	/* FC_RP */
/* 30 */	NdrFcShort( 0x2 ),	/* Offset= 2 (32) */
/* 32 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 34 */	NdrFcLong( 0x3c107e66 ),	/* 1007713894 */
/* 38 */	NdrFcShort( 0xb05a ),	/* -20390 */
/* 40 */	NdrFcShort( 0x4641 ),	/* 17985 */
/* 42 */	0xa6,		/* 166 */
			0xdc,		/* 220 */
/* 44 */	0x4b,		/* 75 */
			0x45,		/* 69 */
/* 46 */	0x75,		/* 117 */
			0x7a,		/* 122 */
/* 48 */	0x3f,		/* 63 */
			0xb1,		/* 177 */
/* 50 */	
			0x11, 0x10,	/* FC_RP */
/* 52 */	NdrFcShort( 0x2 ),	/* Offset= 2 (54) */
/* 54 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 56 */	NdrFcLong( 0x8ea6019a ),	/* -1901723238 */
/* 60 */	NdrFcShort( 0x3fb3 ),	/* 16307 */
/* 62 */	NdrFcShort( 0x447c ),	/* 17532 */
/* 64 */	0xb2,		/* 178 */
			0xa1,		/* 161 */
/* 66 */	0xf2,		/* 242 */
			0x5e,		/* 94 */
/* 68 */	0x65,		/* 101 */
			0x49,		/* 73 */
/* 70 */	0x72,		/* 114 */
			0xb7,		/* 183 */
/* 72 */	
			0x11, 0x10,	/* FC_RP */
/* 74 */	NdrFcShort( 0x2 ),	/* Offset= 2 (76) */
/* 76 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 78 */	NdrFcLong( 0x85d85ead ),	/* -2049417555 */
/* 82 */	NdrFcShort( 0x4839 ),	/* 18489 */
/* 84 */	NdrFcShort( 0x4085 ),	/* 16517 */
/* 86 */	0x93,		/* 147 */
			0xd3,		/* 211 */
/* 88 */	0x30,		/* 48 */
			0xc8,		/* 200 */
/* 90 */	0xb3,		/* 179 */
			0xdf,		/* 223 */
/* 92 */	0x82,		/* 130 */
			0x62,		/* 98 */

			0x0
        }
    };

const CInterfaceProxyVtbl * _INStimApp_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INStimAppProxyVtbl,
    0
};

const CInterfaceStubVtbl * _INStimApp_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INStimAppStubVtbl,
    0
};

PCInterfaceName const _INStimApp_InterfaceNamesList[] = 
{
    "INStimApp",
    0
};


#define _INStimApp_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _INStimApp, pIID, n)

int __stdcall _INStimApp_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_INStimApp_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo INStimApp_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _INStimApp_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _INStimApp_StubVtblList,
    (const PCInterfaceName * ) & _INStimApp_InterfaceNamesList,
    0, // no delegation
    & _INStimApp_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
