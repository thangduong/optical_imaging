/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:53 2006
 */
/* Compiler settings for .\INStimAtom.idl:
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

#ifndef __INStimAtom_h__
#define __INStimAtom_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimAtom_FWD_DEFINED__
#define __INStimAtom_FWD_DEFINED__
typedef interface INStimAtom INStimAtom;
#endif 	/* __INStimAtom_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "IPort.h"
#include "INStimEngine.h"
#include "INStimParam.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimAtom_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_INStimAtom_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimAtom_0000_v0_0_s_ifspec;

#ifndef __INStimAtom_INTERFACE_DEFINED__
#define __INStimAtom_INTERFACE_DEFINED__

/* interface INStimAtom */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimAtom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE1FE002-5B82-435e-B143-DBA49F2CF18B")
    INStimAtom : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AdvanceFrame( 
            int numFrames) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Exec( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Init( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindParam( 
            unsigned char __RPC_FAR *param,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            unsigned char __RPC_FAR *__RPC_FAR *ppType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            unsigned char __RPC_FAR *__RPC_FAR *ppName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            unsigned char __RPC_FAR *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsAtom( 
            unsigned char __RPC_FAR *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamCount( 
            int __RPC_FAR *pParamCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParam( 
            int index,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParam( 
            unsigned char __RPC_FAR *pParamName,
            unsigned char __RPC_FAR *pParamValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE List( 
            IPort __RPC_FAR *pPort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Preview( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPreview( 
            int shouldPreview) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimAtomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimAtom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimAtom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimAtom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdvanceFrame )( 
            INStimAtom __RPC_FAR * This,
            int numFrames);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Exec )( 
            INStimAtom __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            INStimAtom __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindParam )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *param,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            INStimAtom __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAtom )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamCount )( 
            INStimAtom __RPC_FAR * This,
            int __RPC_FAR *pParamCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParam )( 
            INStimAtom __RPC_FAR * This,
            int index,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParam )( 
            INStimAtom __RPC_FAR * This,
            unsigned char __RPC_FAR *pParamName,
            unsigned char __RPC_FAR *pParamValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *List )( 
            INStimAtom __RPC_FAR * This,
            IPort __RPC_FAR *pPort);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Preview )( 
            INStimAtom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreview )( 
            INStimAtom __RPC_FAR * This,
            int shouldPreview);
        
        END_INTERFACE
    } INStimAtomVtbl;

    interface INStimAtom
    {
        CONST_VTBL struct INStimAtomVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimAtom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimAtom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimAtom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimAtom_AdvanceFrame(This,numFrames)	\
    (This)->lpVtbl -> AdvanceFrame(This,numFrames)

#define INStimAtom_Exec(This,pEngine)	\
    (This)->lpVtbl -> Exec(This,pEngine)

#define INStimAtom_Init(This,pEngine)	\
    (This)->lpVtbl -> Init(This,pEngine)

#define INStimAtom_FindParam(This,param,ppParam)	\
    (This)->lpVtbl -> FindParam(This,param,ppParam)

#define INStimAtom_Reset(This,pEngine)	\
    (This)->lpVtbl -> Reset(This,pEngine)

#define INStimAtom_GetType(This,ppType)	\
    (This)->lpVtbl -> GetType(This,ppType)

#define INStimAtom_GetName(This,ppName)	\
    (This)->lpVtbl -> GetName(This,ppName)

#define INStimAtom_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define INStimAtom_IsAtom(This,pName)	\
    (This)->lpVtbl -> IsAtom(This,pName)

#define INStimAtom_GetParamCount(This,pParamCount)	\
    (This)->lpVtbl -> GetParamCount(This,pParamCount)

#define INStimAtom_GetParam(This,index,ppParam)	\
    (This)->lpVtbl -> GetParam(This,index,ppParam)

#define INStimAtom_SetParam(This,pParamName,pParamValue)	\
    (This)->lpVtbl -> SetParam(This,pParamName,pParamValue)

#define INStimAtom_List(This,pPort)	\
    (This)->lpVtbl -> List(This,pPort)

#define INStimAtom_Preview(This)	\
    (This)->lpVtbl -> Preview(This)

#define INStimAtom_SetPreview(This,shouldPreview)	\
    (This)->lpVtbl -> SetPreview(This,shouldPreview)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimAtom_AdvanceFrame_Proxy( 
    INStimAtom __RPC_FAR * This,
    int numFrames);


void __RPC_STUB INStimAtom_AdvanceFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_Exec_Proxy( 
    INStimAtom __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimAtom_Exec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_Init_Proxy( 
    INStimAtom __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimAtom_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_FindParam_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *param,
    INStimParam __RPC_FAR *__RPC_FAR *ppParam);


void __RPC_STUB INStimAtom_FindParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_Reset_Proxy( 
    INStimAtom __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimAtom_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_GetType_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppType);


void __RPC_STUB INStimAtom_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_GetName_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppName);


void __RPC_STUB INStimAtom_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_SetName_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *pName);


void __RPC_STUB INStimAtom_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_IsAtom_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *pName);


void __RPC_STUB INStimAtom_IsAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_GetParamCount_Proxy( 
    INStimAtom __RPC_FAR * This,
    int __RPC_FAR *pParamCount);


void __RPC_STUB INStimAtom_GetParamCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_GetParam_Proxy( 
    INStimAtom __RPC_FAR * This,
    int index,
    INStimParam __RPC_FAR *__RPC_FAR *ppParam);


void __RPC_STUB INStimAtom_GetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_SetParam_Proxy( 
    INStimAtom __RPC_FAR * This,
    unsigned char __RPC_FAR *pParamName,
    unsigned char __RPC_FAR *pParamValue);


void __RPC_STUB INStimAtom_SetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_List_Proxy( 
    INStimAtom __RPC_FAR * This,
    IPort __RPC_FAR *pPort);


void __RPC_STUB INStimAtom_List_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_Preview_Proxy( 
    INStimAtom __RPC_FAR * This);


void __RPC_STUB INStimAtom_Preview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimAtom_SetPreview_Proxy( 
    INStimAtom __RPC_FAR * This,
    int shouldPreview);


void __RPC_STUB INStimAtom_SetPreview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimAtom_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
