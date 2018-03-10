/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:48 2006
 */
/* Compiler settings for .\IPort.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __IPort_h__
#define __IPort_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPort_FWD_DEFINED__
#define __IPort_FWD_DEFINED__
typedef interface IPort IPort;
#endif 	/* __IPort_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "IPortCallback.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPort_INTERFACE_DEFINED__
#define __IPort_INTERFACE_DEFINED__

/* interface IPort */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A929355-1144-4109-BE4E-975F3F6E940F")
    IPort : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Open( 
            const unsigned char __RPC_FAR *name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsOpen( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Send( 
            const unsigned char __RPC_FAR *pData,
            unsigned long dwDataSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback( 
            IPortCallback __RPC_FAR *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterCallback( 
            IPortCallback __RPC_FAR *pCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPort __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPort __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPort __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IPort __RPC_FAR * This,
            const unsigned char __RPC_FAR *name);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IPort __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOpen )( 
            IPort __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            IPort __RPC_FAR * This,
            const unsigned char __RPC_FAR *pData,
            unsigned long dwDataSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            IPort __RPC_FAR * This,
            IPortCallback __RPC_FAR *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterCallback )( 
            IPort __RPC_FAR * This,
            IPortCallback __RPC_FAR *pCallback);
        
        END_INTERFACE
    } IPortVtbl;

    interface IPort
    {
        CONST_VTBL struct IPortVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPort_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPort_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPort_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPort_Open(This,name)	\
    (This)->lpVtbl -> Open(This,name)

#define IPort_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IPort_IsOpen(This)	\
    (This)->lpVtbl -> IsOpen(This)

#define IPort_Send(This,pData,dwDataSize)	\
    (This)->lpVtbl -> Send(This,pData,dwDataSize)

#define IPort_RegisterCallback(This,pCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,pCallback)

#define IPort_UnregisterCallback(This,pCallback)	\
    (This)->lpVtbl -> UnregisterCallback(This,pCallback)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPort_Open_Proxy( 
    IPort __RPC_FAR * This,
    const unsigned char __RPC_FAR *name);


void __RPC_STUB IPort_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPort_Close_Proxy( 
    IPort __RPC_FAR * This);


void __RPC_STUB IPort_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPort_IsOpen_Proxy( 
    IPort __RPC_FAR * This);


void __RPC_STUB IPort_IsOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPort_Send_Proxy( 
    IPort __RPC_FAR * This,
    const unsigned char __RPC_FAR *pData,
    unsigned long dwDataSize);


void __RPC_STUB IPort_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPort_RegisterCallback_Proxy( 
    IPort __RPC_FAR * This,
    IPortCallback __RPC_FAR *pCallback);


void __RPC_STUB IPort_RegisterCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPort_UnregisterCallback_Proxy( 
    IPort __RPC_FAR * This,
    IPortCallback __RPC_FAR *pCallback);


void __RPC_STUB IPort_UnregisterCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPort_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
