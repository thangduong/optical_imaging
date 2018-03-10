/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:48 2006
 */
/* Compiler settings for .\IPortServer.idl:
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

#ifndef __IPortServer_h__
#define __IPortServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPortServer_FWD_DEFINED__
#define __IPortServer_FWD_DEFINED__
typedef interface IPortServer IPortServer;
#endif 	/* __IPortServer_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "IPortServerCallback.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPortServer_INTERFACE_DEFINED__
#define __IPortServer_INTERFACE_DEFINED__

/* interface IPortServer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPortServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3956155-128E-4457-B08E-F17BC620D410")
    IPortServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UnregisterCallback( 
            IPortServerCallback __RPC_FAR *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback( 
            IPortServerCallback __RPC_FAR *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( 
            const unsigned char __RPC_FAR *info) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsStarted( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPortServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPortServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPortServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterCallback )( 
            IPortServer __RPC_FAR * This,
            IPortServerCallback __RPC_FAR *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            IPortServer __RPC_FAR * This,
            IPortServerCallback __RPC_FAR *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IPortServer __RPC_FAR * This,
            const unsigned char __RPC_FAR *info);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IPortServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStarted )( 
            IPortServer __RPC_FAR * This);
        
        END_INTERFACE
    } IPortServerVtbl;

    interface IPortServer
    {
        CONST_VTBL struct IPortServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPortServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPortServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPortServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPortServer_UnregisterCallback(This,pCallback)	\
    (This)->lpVtbl -> UnregisterCallback(This,pCallback)

#define IPortServer_RegisterCallback(This,pCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,pCallback)

#define IPortServer_Start(This,info)	\
    (This)->lpVtbl -> Start(This,info)

#define IPortServer_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IPortServer_IsStarted(This)	\
    (This)->lpVtbl -> IsStarted(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPortServer_UnregisterCallback_Proxy( 
    IPortServer __RPC_FAR * This,
    IPortServerCallback __RPC_FAR *pCallback);


void __RPC_STUB IPortServer_UnregisterCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPortServer_RegisterCallback_Proxy( 
    IPortServer __RPC_FAR * This,
    IPortServerCallback __RPC_FAR *pCallback);


void __RPC_STUB IPortServer_RegisterCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPortServer_Start_Proxy( 
    IPortServer __RPC_FAR * This,
    const unsigned char __RPC_FAR *info);


void __RPC_STUB IPortServer_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPortServer_Stop_Proxy( 
    IPortServer __RPC_FAR * This);


void __RPC_STUB IPortServer_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPortServer_IsStarted_Proxy( 
    IPortServer __RPC_FAR * This);


void __RPC_STUB IPortServer_IsStarted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPortServer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
