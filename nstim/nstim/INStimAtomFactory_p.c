/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:54 2006
 */
/* Compiler settings for .\INStimAtomFactory.idl:
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


#include "INStimAtomFactory.h"

#define TYPE_FORMAT_STRING_SIZE   29                                
#define PROC_FORMAT_STRING_SIZE   17                                

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


/* Standard interface: __MIDL_itf_INStimAtomFactory_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: INStimAtomFactory, ver. 0.0,
   GUID={0xEAB0C76D,0x96D8,0x4b08,{0x9C,0xD6,0x26,0x49,0x86,0x7A,0xF3,0x4B}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE INStimAtomFactory_IsValidAtomType_Proxy( 
    INStimAtomFactory __RPC_FAR * This,
    unsigned char __RPC_FAR *AtomType)
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
        
        
        
        if(!AtomType)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 1U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( unsigned char __RPC_FAR * )_StubMsg.Buffer)++ = *AtomType;
            
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

void __RPC_STUB INStimAtomFactory_IsValidAtomType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    unsigned char __RPC_FAR *AtomType;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( unsigned char __RPC_FAR * )AtomType = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        AtomType = ( unsigned char __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( unsigned char  );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimAtomFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> IsValidAtomType((INStimAtomFactory *) ((CStdStubBuffer *)This)->pvServerObject,AtomType);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE INStimAtomFactory_CreateAtom_Proxy( 
    INStimAtomFactory __RPC_FAR * This,
    unsigned char __RPC_FAR *AtomType,
    INStimAtom __RPC_FAR *__RPC_FAR *ppAtom)
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
        
        
        
        if(!AtomType)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppAtom)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 1U + 0U;
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppAtom,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( unsigned char __RPC_FAR * )_StubMsg.Buffer)++ = *AtomType;
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppAtom,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
            
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

void __RPC_STUB INStimAtomFactory_CreateAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    unsigned char __RPC_FAR *AtomType;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    INStimAtom __RPC_FAR *__RPC_FAR *ppAtom;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( unsigned char __RPC_FAR * )AtomType = 0;
    ( INStimAtom __RPC_FAR *__RPC_FAR * )ppAtom = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        AtomType = ( unsigned char __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( unsigned char  );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppAtom,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((INStimAtomFactory*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> CreateAtom(
              (INStimAtomFactory *) ((CStdStubBuffer *)This)->pvServerObject,
              AtomType,
              ppAtom);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppAtom,
                        &__MIDL_TypeFormatString.Format[6] );
        
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

const CINTERFACE_PROXY_VTABLE(5) _INStimAtomFactoryProxyVtbl = 
{
    &IID_INStimAtomFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    INStimAtomFactory_IsValidAtomType_Proxy ,
    INStimAtomFactory_CreateAtom_Proxy
};


static const PRPC_STUB_FUNCTION INStimAtomFactory_table[] =
{
    INStimAtomFactory_IsValidAtomType_Stub,
    INStimAtomFactory_CreateAtom_Stub
};

const CInterfaceStubVtbl _INStimAtomFactoryStubVtbl =
{
    &IID_INStimAtomFactory,
    0,
    5,
    &INStimAtomFactory_table[-3],
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
/*  4 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 10 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 12 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/* 14 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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

			0x0
        }
    };

const CInterfaceProxyVtbl * _INStimAtomFactory_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_INStimAtomFactoryProxyVtbl,
    0
};

const CInterfaceStubVtbl * _INStimAtomFactory_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_INStimAtomFactoryStubVtbl,
    0
};

PCInterfaceName const _INStimAtomFactory_InterfaceNamesList[] = 
{
    "INStimAtomFactory",
    0
};


#define _INStimAtomFactory_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _INStimAtomFactory, pIID, n)

int __stdcall _INStimAtomFactory_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_INStimAtomFactory_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo INStimAtomFactory_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _INStimAtomFactory_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _INStimAtomFactory_StubVtblList,
    (const PCInterfaceName * ) & _INStimAtomFactory_InterfaceNamesList,
    0, // no delegation
    & _INStimAtomFactory_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
