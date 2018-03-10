/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:47 2006
 */
/* Compiler settings for .\IPortServerCallback.idl:
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

#ifndef __IPortServerCallback_h__
#define __IPortServerCallback_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPortServerCallback_FWD_DEFINED__
#define __IPortServerCallback_FWD_DEFINED__
typedef interface IPortServerCallback IPortServerCallback;
#endif 	/* __IPortServerCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_IPortServerCallback_0000 */
/* [local] */ 

#define	PSE_ON_CONNECT		0
#define	PSE_SERVER_START	1
#define	PSE_SERVER_STOP		2


extern RPC_IF_HANDLE __MIDL_itf_IPortServerCallback_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IPortServerCallback_0000_v0_0_s_ifspec;

#ifndef __IPortServerCallback_INTERFACE_DEFINED__
#define __IPortServerCallback_INTERFACE_DEFINED__

/* interface IPortServerCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPortServerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F197538F-094E-49f3-8517-A2BB41B8697E")
    IPortServerCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPortEvent( 
            IUnknown __RPC_FAR *caller,
            DWORD event,
            DWORD param1,
            DWORD param2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortServerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPortServerCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPortServerCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPortServerCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPortEvent )( 
            IPortServerCallback __RPC_FAR * This,
            IUnknown __RPC_FAR *caller,
            DWORD event,
            DWORD param1,
            DWORD param2);
        
        END_INTERFACE
    } IPortServerCallbackVtbl;

    interface IPortServerCallback
    {
        CONST_VTBL struct IPortServerCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPortServerCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPortServerCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPortServerCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPortServerCallback_OnPortEvent(This,caller,event,param1,param2)	\
    (This)->lpVtbl -> OnPortEvent(This,caller,event,param1,param2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPortServerCallback_OnPortEvent_Proxy( 
    IPortServerCallback __RPC_FAR * This,
    IUnknown __RPC_FAR *caller,
    DWORD event,
    DWORD param1,
    DWORD param2);


void __RPC_STUB IPortServerCallback_OnPortEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPortServerCallback_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
