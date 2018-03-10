/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 06 15:32:10 2005
 */
/* Compiler settings for .\INStimApp.idl:
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

#ifndef __INStimApp_h__
#define __INStimApp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimApp_FWD_DEFINED__
#define __INStimApp_FWD_DEFINED__
typedef interface INStimApp INStimApp;
#endif 	/* __INStimApp_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "INStimAtom.h"
#include "INStimCmdEngine.h"
#include "INStimProfile.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimApp_0000 */
/* [local] */ 







extern RPC_IF_HANDLE __MIDL_itf_INStimApp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimApp_0000_v0_0_s_ifspec;

#ifndef __INStimApp_INTERFACE_DEFINED__
#define __INStimApp_INTERFACE_DEFINED__

/* interface INStimApp */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A1B847C-B96B-4f96-AE47-EDB1473D65A0")
    INStimApp : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateAtom( 
            unsigned char __RPC_FAR *pPatchType,
            INStimAtom __RPC_FAR *__RPC_FAR *ppPatch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGraphicsEngine( 
            INStimEngine __RPC_FAR *__RPC_FAR *ppGraphicsEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCommandEngine( 
            INStimCmdEngine __RPC_FAR *__RPC_FAR *ppCmdEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProfile( 
            INStimProfile __RPC_FAR *__RPC_FAR *ppProfile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAtom )( 
            INStimApp __RPC_FAR * This,
            unsigned char __RPC_FAR *pPatchType,
            INStimAtom __RPC_FAR *__RPC_FAR *ppPatch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGraphicsEngine )( 
            INStimApp __RPC_FAR * This,
            INStimEngine __RPC_FAR *__RPC_FAR *ppGraphicsEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommandEngine )( 
            INStimApp __RPC_FAR * This,
            INStimCmdEngine __RPC_FAR *__RPC_FAR *ppCmdEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfile )( 
            INStimApp __RPC_FAR * This,
            INStimProfile __RPC_FAR *__RPC_FAR *ppProfile);
        
        END_INTERFACE
    } INStimAppVtbl;

    interface INStimApp
    {
        CONST_VTBL struct INStimAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimApp_CreateAtom(This,pPatchType,ppPatch)	\
    (This)->lpVtbl -> CreateAtom(This,pPatchType,ppPatch)

#define INStimApp_GetGraphicsEngine(This,ppGraphicsEngine)	\
    (This)->lpVtbl -> GetGraphicsEngine(This,ppGraphicsEngine)

#define INStimApp_GetCommandEngine(This,ppCmdEngine)	\
    (This)->lpVtbl -> GetCommandEngine(This,ppCmdEngine)

#define INStimApp_GetProfile(This,ppProfile)	\
    (This)->lpVtbl -> GetProfile(This,ppProfile)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimApp_CreateAtom_Proxy( 
    INStimApp __RPC_FAR * This,
    unsigned char __RPC_FAR *pPatchType,
    INStimAtom __RPC_FAR *__RPC_FAR *ppPatch);


void __RPC_STUB INStimApp_CreateAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimApp_GetGraphicsEngine_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimEngine __RPC_FAR *__RPC_FAR *ppGraphicsEngine);


void __RPC_STUB INStimApp_GetGraphicsEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimApp_GetCommandEngine_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimCmdEngine __RPC_FAR *__RPC_FAR *ppCmdEngine);


void __RPC_STUB INStimApp_GetCommandEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimApp_GetProfile_Proxy( 
    INStimApp __RPC_FAR * This,
    INStimProfile __RPC_FAR *__RPC_FAR *ppProfile);


void __RPC_STUB INStimApp_GetProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimApp_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
