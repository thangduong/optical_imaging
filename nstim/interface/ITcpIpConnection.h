/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:47 2006
 */
/* Compiler settings for .\ITcpIpConnection.idl:
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

#ifndef __ITcpIpConnection_h__
#define __ITcpIpConnection_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITcpIpConnection_FWD_DEFINED__
#define __ITcpIpConnection_FWD_DEFINED__
typedef interface ITcpIpConnection ITcpIpConnection;
#endif 	/* __ITcpIpConnection_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "IPort.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITcpIpConnection_INTERFACE_DEFINED__
#define __ITcpIpConnection_INTERFACE_DEFINED__

/* interface ITcpIpConnection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITcpIpConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FAFFAAD-598D-4020-8C5E-9791F319FA1F")
    ITcpIpConnection : public IPort
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Test( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITcpIpConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITcpIpConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITcpIpConnection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITcpIpConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ITcpIpConnection __RPC_FAR * This,
            const unsigned char __RPC_FAR *name);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            ITcpIpConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOpen )( 
            ITcpIpConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            ITcpIpConnection __RPC_FAR * This,
            const unsigned char __RPC_FAR *pData,
            unsigned long dwDataSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            ITcpIpConnection __RPC_FAR * This,
            IPortCallback __RPC_FAR *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterCallback )( 
            ITcpIpConnection __RPC_FAR * This,
            IPortCallback __RPC_FAR *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test )( 
            ITcpIpConnection __RPC_FAR * This);
        
        END_INTERFACE
    } ITcpIpConnectionVtbl;

    interface ITcpIpConnection
    {
        CONST_VTBL struct ITcpIpConnectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITcpIpConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITcpIpConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITcpIpConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITcpIpConnection_Open(This,name)	\
    (This)->lpVtbl -> Open(This,name)

#define ITcpIpConnection_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define ITcpIpConnection_IsOpen(This)	\
    (This)->lpVtbl -> IsOpen(This)

#define ITcpIpConnection_Send(This,pData,dwDataSize)	\
    (This)->lpVtbl -> Send(This,pData,dwDataSize)

#define ITcpIpConnection_RegisterCallback(This,pCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,pCallback)

#define ITcpIpConnection_UnregisterCallback(This,pCallback)	\
    (This)->lpVtbl -> UnregisterCallback(This,pCallback)


#define ITcpIpConnection_Test(This)	\
    (This)->lpVtbl -> Test(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITcpIpConnection_Test_Proxy( 
    ITcpIpConnection __RPC_FAR * This);


void __RPC_STUB ITcpIpConnection_Test_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITcpIpConnection_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
