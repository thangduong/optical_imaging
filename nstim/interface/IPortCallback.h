/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:48 2006
 */
/* Compiler settings for .\IPortCallback.idl:
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

#ifndef __IPortCallback_h__
#define __IPortCallback_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPortCallback_FWD_DEFINED__
#define __IPortCallback_FWD_DEFINED__
typedef interface IPortCallback IPortCallback;
#endif 	/* __IPortCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_IPortCallback_0000 */
/* [local] */ 

#define	PE_DATA_ARRIVED		0
#define	PE_PORT_OPENED		1
#define	PE_PORT_CLOSED		2


extern RPC_IF_HANDLE __MIDL_itf_IPortCallback_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IPortCallback_0000_v0_0_s_ifspec;

#ifndef __IPortCallback_INTERFACE_DEFINED__
#define __IPortCallback_INTERFACE_DEFINED__

/* interface IPortCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPortCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1709F049-59F6-479d-BB0B-C910D57C0633")
    IPortCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPortEvent( 
            IUnknown __RPC_FAR *caller,
            DWORD event,
            DWORD param1,
            DWORD param2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPortCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPortCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPortCallback __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPortEvent )( 
            IPortCallback __RPC_FAR * This,
            IUnknown __RPC_FAR *caller,
            DWORD event,
            DWORD param1,
            DWORD param2);
        
        END_INTERFACE
    } IPortCallbackVtbl;

    interface IPortCallback
    {
        CONST_VTBL struct IPortCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPortCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPortCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPortCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPortCallback_OnPortEvent(This,caller,event,param1,param2)	\
    (This)->lpVtbl -> OnPortEvent(This,caller,event,param1,param2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPortCallback_OnPortEvent_Proxy( 
    IPortCallback __RPC_FAR * This,
    IUnknown __RPC_FAR *caller,
    DWORD event,
    DWORD param1,
    DWORD param2);


void __RPC_STUB IPortCallback_OnPortEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPortCallback_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
