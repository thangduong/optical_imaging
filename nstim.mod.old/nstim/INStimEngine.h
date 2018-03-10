/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 20 13:48:10 2005
 */
/* Compiler settings for .\INStimEngine.idl:
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

#ifndef __INStimEngine_h__
#define __INStimEngine_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimEngine_FWD_DEFINED__
#define __INStimEngine_FWD_DEFINED__
typedef interface INStimEngine INStimEngine;
#endif 	/* __INStimEngine_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "INStimAtom.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimEngine_0000 */
/* [local] */ 


interface IDirect3DDevice9;
#if 0
struct  _D3DVIEWPORT9
    {
    DWORD X;
    DWORD Y;
    DWORD Width;
    DWORD Height;
    float MinZ;
    float MaxZ;
    };
#endif
#define	GE_IDLE			0
#define	GE_PAUSE		1
#define	GE_STIMULATING	2
#define	GE_SIMULATING	3
#define	GE_PREVIEW		4
#if 0
// Bogus definition used to make MIDL compiler happy
typedef long IDirect3DDevice9;

#endif


extern RPC_IF_HANDLE __MIDL_itf_INStimEngine_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimEngine_0000_v0_0_s_ifspec;

#ifndef __INStimEngine_INTERFACE_DEFINED__
#define __INStimEngine_INTERFACE_DEFINED__

/* interface INStimEngine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C107E66-B05A-4641-A6DC-4B45757A3FB1")
    INStimEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirect3DDevice( 
            IDirect3DDevice9 __RPC_FAR *__RPC_FAR *pDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetState( 
            DWORD state) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            DWORD __RPC_FAR *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddAtom( 
            INStimAtom __RPC_FAR *pAtom) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindAtom( 
            unsigned char __RPC_FAR *pName,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAtomCount( 
            int __RPC_FAR *pAtomCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAtom( 
            int iAtomIndex,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stimulate( 
            DWORD numFrames,
            unsigned char __RPC_FAR *stimName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Simulate( 
            DWORD numFrames,
            unsigned char __RPC_FAR *stimName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddSequenceMarker( 
            int frameMarker,
            int type,
            unsigned char __RPC_FAR *patchName,
            DWORD list,
            int order) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearAtom( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearSequence( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameRate( 
            double __RPC_FAR *frameRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBkColor( 
            unsigned long __RPC_FAR *pBkColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBkColor( 
            unsigned long bkColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ApplyViewport( 
            struct _D3DVIEWPORT9 __RPC_FAR *pViewport) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewportCenter( 
            int __RPC_FAR *x,
            int __RPC_FAR *y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetViewportCenter( 
            int x,
            int y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Snap( 
            const unsigned char __RPC_FAR *filename) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimEngine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimEngine __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            INStimEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDirect3DDevice )( 
            INStimEngine __RPC_FAR * This,
            IDirect3DDevice9 __RPC_FAR *__RPC_FAR *pDevice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetState )( 
            INStimEngine __RPC_FAR * This,
            DWORD state);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            INStimEngine __RPC_FAR * This,
            DWORD __RPC_FAR *pState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            INStimEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddAtom )( 
            INStimEngine __RPC_FAR * This,
            INStimAtom __RPC_FAR *pAtom);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindAtom )( 
            INStimEngine __RPC_FAR * This,
            unsigned char __RPC_FAR *pName,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAtomCount )( 
            INStimEngine __RPC_FAR * This,
            int __RPC_FAR *pAtomCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAtom )( 
            INStimEngine __RPC_FAR * This,
            int iAtomIndex,
            INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stimulate )( 
            INStimEngine __RPC_FAR * This,
            DWORD numFrames,
            unsigned char __RPC_FAR *stimName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Simulate )( 
            INStimEngine __RPC_FAR * This,
            DWORD numFrames,
            unsigned char __RPC_FAR *stimName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSequenceMarker )( 
            INStimEngine __RPC_FAR * This,
            int frameMarker,
            int type,
            unsigned char __RPC_FAR *patchName,
            DWORD list,
            int order);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearAtom )( 
            INStimEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearSequence )( 
            INStimEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFrameRate )( 
            INStimEngine __RPC_FAR * This,
            double __RPC_FAR *frameRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBkColor )( 
            INStimEngine __RPC_FAR * This,
            unsigned long __RPC_FAR *pBkColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBkColor )( 
            INStimEngine __RPC_FAR * This,
            unsigned long bkColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ApplyViewport )( 
            INStimEngine __RPC_FAR * This,
            struct _D3DVIEWPORT9 __RPC_FAR *pViewport);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetViewportCenter )( 
            INStimEngine __RPC_FAR * This,
            int __RPC_FAR *x,
            int __RPC_FAR *y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetViewportCenter )( 
            INStimEngine __RPC_FAR * This,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Snap )( 
            INStimEngine __RPC_FAR * This,
            const unsigned char __RPC_FAR *filename);
        
        END_INTERFACE
    } INStimEngineVtbl;

    interface INStimEngine
    {
        CONST_VTBL struct INStimEngineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimEngine_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define INStimEngine_GetDirect3DDevice(This,pDevice)	\
    (This)->lpVtbl -> GetDirect3DDevice(This,pDevice)

#define INStimEngine_SetState(This,state)	\
    (This)->lpVtbl -> SetState(This,state)

#define INStimEngine_GetState(This,pState)	\
    (This)->lpVtbl -> GetState(This,pState)

#define INStimEngine_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define INStimEngine_AddAtom(This,pAtom)	\
    (This)->lpVtbl -> AddAtom(This,pAtom)

#define INStimEngine_FindAtom(This,pName,ppAtom)	\
    (This)->lpVtbl -> FindAtom(This,pName,ppAtom)

#define INStimEngine_GetAtomCount(This,pAtomCount)	\
    (This)->lpVtbl -> GetAtomCount(This,pAtomCount)

#define INStimEngine_GetAtom(This,iAtomIndex,ppAtom)	\
    (This)->lpVtbl -> GetAtom(This,iAtomIndex,ppAtom)

#define INStimEngine_Stimulate(This,numFrames,stimName)	\
    (This)->lpVtbl -> Stimulate(This,numFrames,stimName)

#define INStimEngine_Simulate(This,numFrames,stimName)	\
    (This)->lpVtbl -> Simulate(This,numFrames,stimName)

#define INStimEngine_AddSequenceMarker(This,frameMarker,type,patchName,list,order)	\
    (This)->lpVtbl -> AddSequenceMarker(This,frameMarker,type,patchName,list,order)

#define INStimEngine_ClearAtom(This)	\
    (This)->lpVtbl -> ClearAtom(This)

#define INStimEngine_ClearSequence(This)	\
    (This)->lpVtbl -> ClearSequence(This)

#define INStimEngine_GetFrameRate(This,frameRate)	\
    (This)->lpVtbl -> GetFrameRate(This,frameRate)

#define INStimEngine_GetBkColor(This,pBkColor)	\
    (This)->lpVtbl -> GetBkColor(This,pBkColor)

#define INStimEngine_SetBkColor(This,bkColor)	\
    (This)->lpVtbl -> SetBkColor(This,bkColor)

#define INStimEngine_ApplyViewport(This,pViewport)	\
    (This)->lpVtbl -> ApplyViewport(This,pViewport)

#define INStimEngine_GetViewportCenter(This,x,y)	\
    (This)->lpVtbl -> GetViewportCenter(This,x,y)

#define INStimEngine_SetViewportCenter(This,x,y)	\
    (This)->lpVtbl -> SetViewportCenter(This,x,y)

#define INStimEngine_Snap(This,filename)	\
    (This)->lpVtbl -> Snap(This,filename)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimEngine_Run_Proxy( 
    INStimEngine __RPC_FAR * This);


void __RPC_STUB INStimEngine_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetDirect3DDevice_Proxy( 
    INStimEngine __RPC_FAR * This,
    IDirect3DDevice9 __RPC_FAR *__RPC_FAR *pDevice);


void __RPC_STUB INStimEngine_GetDirect3DDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_SetState_Proxy( 
    INStimEngine __RPC_FAR * This,
    DWORD state);


void __RPC_STUB INStimEngine_SetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetState_Proxy( 
    INStimEngine __RPC_FAR * This,
    DWORD __RPC_FAR *pState);


void __RPC_STUB INStimEngine_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_Stop_Proxy( 
    INStimEngine __RPC_FAR * This);


void __RPC_STUB INStimEngine_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_AddAtom_Proxy( 
    INStimEngine __RPC_FAR * This,
    INStimAtom __RPC_FAR *pAtom);


void __RPC_STUB INStimEngine_AddAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_FindAtom_Proxy( 
    INStimEngine __RPC_FAR * This,
    unsigned char __RPC_FAR *pName,
    INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);


void __RPC_STUB INStimEngine_FindAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetAtomCount_Proxy( 
    INStimEngine __RPC_FAR * This,
    int __RPC_FAR *pAtomCount);


void __RPC_STUB INStimEngine_GetAtomCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetAtom_Proxy( 
    INStimEngine __RPC_FAR * This,
    int iAtomIndex,
    INStimAtom __RPC_FAR *__RPC_FAR *ppAtom);


void __RPC_STUB INStimEngine_GetAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_Stimulate_Proxy( 
    INStimEngine __RPC_FAR * This,
    DWORD numFrames,
    unsigned char __RPC_FAR *stimName);


void __RPC_STUB INStimEngine_Stimulate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_Simulate_Proxy( 
    INStimEngine __RPC_FAR * This,
    DWORD numFrames,
    unsigned char __RPC_FAR *stimName);


void __RPC_STUB INStimEngine_Simulate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_AddSequenceMarker_Proxy( 
    INStimEngine __RPC_FAR * This,
    int frameMarker,
    int type,
    unsigned char __RPC_FAR *patchName,
    DWORD list,
    int order);


void __RPC_STUB INStimEngine_AddSequenceMarker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_ClearAtom_Proxy( 
    INStimEngine __RPC_FAR * This);


void __RPC_STUB INStimEngine_ClearAtom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_ClearSequence_Proxy( 
    INStimEngine __RPC_FAR * This);


void __RPC_STUB INStimEngine_ClearSequence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetFrameRate_Proxy( 
    INStimEngine __RPC_FAR * This,
    double __RPC_FAR *frameRate);


void __RPC_STUB INStimEngine_GetFrameRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetBkColor_Proxy( 
    INStimEngine __RPC_FAR * This,
    unsigned long __RPC_FAR *pBkColor);


void __RPC_STUB INStimEngine_GetBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_SetBkColor_Proxy( 
    INStimEngine __RPC_FAR * This,
    unsigned long bkColor);


void __RPC_STUB INStimEngine_SetBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_ApplyViewport_Proxy( 
    INStimEngine __RPC_FAR * This,
    struct _D3DVIEWPORT9 __RPC_FAR *pViewport);


void __RPC_STUB INStimEngine_ApplyViewport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_GetViewportCenter_Proxy( 
    INStimEngine __RPC_FAR * This,
    int __RPC_FAR *x,
    int __RPC_FAR *y);


void __RPC_STUB INStimEngine_GetViewportCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_SetViewportCenter_Proxy( 
    INStimEngine __RPC_FAR * This,
    int x,
    int y);


void __RPC_STUB INStimEngine_SetViewportCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimEngine_Snap_Proxy( 
    INStimEngine __RPC_FAR * This,
    const unsigned char __RPC_FAR *filename);


void __RPC_STUB INStimEngine_Snap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimEngine_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
