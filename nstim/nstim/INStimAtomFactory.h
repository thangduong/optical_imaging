/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:54 2006
 */
/* Compiler settings for .\INStimAtomFactory.idl:
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

#ifndef __INStimAtomFactory_h__
#define __INStimAtomFactory_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimAtomFactory_FWD_DEFINED__
#define __INStimAtomFactory_FWD_DEFINED__
typedef interface INStimAtomFactory INStimAtomFactory;
#endif 	/* __INStimAtomFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "INStimAtom.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimAtomFactory_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_INStimAtomFactory_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimAtomFactory_0000_v0_0_s_ifspec;

#ifndef __INStimAtomFactory_INTERFACE_DEFINED__
#define __INStimAtomFactory_INTERFACE_DEFINED__

/* interface INStimAtomFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimAtomFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EAB0C76D-96D8-4b08-9CD6-2649867AF34B")
    INStimAtomFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsValidAtomType( 
            unsigned char __RPC_FAR *AtomType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateAtom( 
            unsigned char __RPC_FAR *AtomType,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimAtomFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimAtomFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimAtomFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimAtomFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidAtomType )( 
            INStimAtomFactory __RPC_FAR * This,
            unsigned char __RPC_FAR *AtomType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateAtom )( 
            INStimAtomFactory __RPC_FAR * This,
            unsigned char __RPC_FAR *AtomType,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);
        
        END_INTERFACE
    } INStimAtomFactoryVtbl;

    interface INStimAtomFactory
    {
        CONST_VTBL struct INStimAtomFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimAtomFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimAtomFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimAtomFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimAtomFactory_IsValidAtomType(This,AtomType)	\
    (This)->lpVtbl -> IsValidAtomType(This,AtomType)

#define INStimAtomFactory_CreateAtom(This,AtomType,ppAtom)	\
    (This)->lpVtbl -> CreateAtom(This,AtomType,ppAtom)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimAtomFactory_IsValidAtomType_Proxy( 
    INStimAtomFactory __RPC_FAR * This,
    unsigned char __RPC_FAR *AtomType);


void __RPC_STUB INStimAtomFactory_IsValidAtomType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtomFactory_CreateAtom_Proxy( 
    INStimAtomFactory __RPC_FAR * This,
    unsigned char __RPC_FAR *AtomType,
    INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);


void __RPC_STUB INStimAtomFactory_CreateAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimAtomFactory_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
