/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Oct 09 02:15:02 2005
 */
/* Compiler settings for .\INStimPatch.idl:
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

#ifndef __INStimPatch_h__
#define __INStimPatch_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimPatch_FWD_DEFINED__
#define __INStimPatch_FWD_DEFINED__
typedef interface INStimPatch INStimPatch;
#endif 	/* __INStimPatch_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "INStimParam.h"
#include "INStimAtom.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimPatch_0000 */
/* [local] */ 



#define	PBT_COPY			0
#define	PBT_PAUSE			1
#define	PBT_STIMULATING		2


extern RPC_IF_HANDLE __MIDL_itf_INStimPatch_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimPatch_0000_v0_0_s_ifspec;

#ifndef __INStimPatch_INTERFACE_DEFINED__
#define __INStimPatch_INTERFACE_DEFINED__

/* interface INStimPatch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimPatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("361D250C-71E8-4f27-86FA-487CD3C6017A")
    INStimPatch : public INStimAtom
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AdvanceFrame( 
            int numFrames) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Init( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindParam( 
            unsigned char __RPC_FAR *param,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCenterX( 
            int __RPC_FAR *centerX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCenterY( 
            int __RPC_FAR *centerY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            INStimEngine __RPC_FAR *pEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCenterX( 
            int centerX) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCenterY( 
            int centerY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBlitType( 
            int blitType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBlitType( 
            int __RPC_FAR *pBlitType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBlitAngle( 
            float __RPC_FAR *pAngle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBlitAngle( 
            float angle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            unsigned char __RPC_FAR *__RPC_FAR *ppType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            unsigned char __RPC_FAR *__RPC_FAR *ppName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            unsigned char __RPC_FAR *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsPatch( 
            unsigned char __RPC_FAR *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamCount( 
            int __RPC_FAR *pParamCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParam( 
            int index,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimPatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimPatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimPatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimPatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdvanceFrame )( 
            INStimPatch __RPC_FAR * This,
            int numFrames);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Exec )( 
            INStimPatch __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            INStimPatch __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindParam )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *param,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            INStimPatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAtom )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamCount )( 
            INStimPatch __RPC_FAR * This,
            int __RPC_FAR *pParamCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParam )( 
            INStimPatch __RPC_FAR * This,
            int index,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParam )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *pParamName,
            unsigned char __RPC_FAR *pParamValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdvanceFrame )( 
            INStimPatch __RPC_FAR * This,
            int numFrames);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            INStimPatch __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            INStimPatch __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindParam )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *param,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCenterX )( 
            INStimPatch __RPC_FAR * This,
            int __RPC_FAR *centerX);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCenterY )( 
            INStimPatch __RPC_FAR * This,
            int __RPC_FAR *centerY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            INStimPatch __RPC_FAR * This,
            INStimEngine __RPC_FAR *pEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCenterX )( 
            INStimPatch __RPC_FAR * This,
            int centerX);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCenterY )( 
            INStimPatch __RPC_FAR * This,
            int centerY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBlitType )( 
            INStimPatch __RPC_FAR * This,
            int blitType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBlitType )( 
            INStimPatch __RPC_FAR * This,
            int __RPC_FAR *pBlitType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBlitAngle )( 
            INStimPatch __RPC_FAR * This,
            float __RPC_FAR *pAngle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBlitAngle )( 
            INStimPatch __RPC_FAR * This,
            float angle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPatch )( 
            INStimPatch __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamCount )( 
            INStimPatch __RPC_FAR * This,
            int __RPC_FAR *pParamCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParam )( 
            INStimPatch __RPC_FAR * This,
            int index,
            INStimParam __RPC_FAR *__RPC_FAR *ppParam);
        
        END_INTERFACE
    } INStimPatchVtbl;

    interface INStimPatch
    {
        CONST_VTBL struct INStimPatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimPatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimPatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimPatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimPatch_AdvanceFrame(This,numFrames)	\
    (This)->lpVtbl -> AdvanceFrame(This,numFrames)

#define INStimPatch_Exec(This,pEngine)	\
    (This)->lpVtbl -> Exec(This,pEngine)

#define INStimPatch_Init(This,pEngine)	\
    (This)->lpVtbl -> Init(This,pEngine)

#define INStimPatch_FindParam(This,param,ppParam)	\
    (This)->lpVtbl -> FindParam(This,param,ppParam)

#define INStimPatch_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define INStimPatch_GetType(This,ppType)	\
    (This)->lpVtbl -> GetType(This,ppType)

#define INStimPatch_GetName(This,ppName)	\
    (This)->lpVtbl -> GetName(This,ppName)

#define INStimPatch_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define INStimPatch_IsAtom(This,pName)	\
    (This)->lpVtbl -> IsAtom(This,pName)

#define INStimPatch_GetParamCount(This,pParamCount)	\
    (This)->lpVtbl -> GetParamCount(This,pParamCount)

#define INStimPatch_GetParam(This,index,ppParam)	\
    (This)->lpVtbl -> GetParam(This,index,ppParam)

#define INStimPatch_SetParam(This,pParamName,pParamValue)	\
    (This)->lpVtbl -> SetParam(This,pParamName,pParamValue)


#define INStimPatch_AdvanceFrame(This,numFrames)	\
    (This)->lpVtbl -> AdvanceFrame(This,numFrames)

#define INStimPatch_Draw(This,pEngine)	\
    (This)->lpVtbl -> Draw(This,pEngine)

#define INStimPatch_Init(This,pEngine)	\
    (This)->lpVtbl -> Init(This,pEngine)

#define INStimPatch_FindParam(This,param,ppParam)	\
    (This)->lpVtbl -> FindParam(This,param,ppParam)

#define INStimPatch_GetCenterX(This,centerX)	\
    (This)->lpVtbl -> GetCenterX(This,centerX)

#define INStimPatch_GetCenterY(This,centerY)	\
    (This)->lpVtbl -> GetCenterY(This,centerY)

#define INStimPatch_Reset(This,pEngine)	\
    (This)->lpVtbl -> Reset(This,pEngine)

#define INStimPatch_SetCenterX(This,centerX)	\
    (This)->lpVtbl -> SetCenterX(This,centerX)

#define INStimPatch_SetCenterY(This,centerY)	\
    (This)->lpVtbl -> SetCenterY(This,centerY)

#define INStimPatch_SetBlitType(This,blitType)	\
    (This)->lpVtbl -> SetBlitType(This,blitType)

#define INStimPatch_GetBlitType(This,pBlitType)	\
    (This)->lpVtbl -> GetBlitType(This,pBlitType)

#define INStimPatch_GetBlitAngle(This,pAngle)	\
    (This)->lpVtbl -> GetBlitAngle(This,pAngle)

#define INStimPatch_SetBlitAngle(This,angle)	\
    (This)->lpVtbl -> SetBlitAngle(This,angle)

#define INStimPatch_GetType(This,ppType)	\
    (This)->lpVtbl -> GetType(This,ppType)

#define INStimPatch_GetName(This,ppName)	\
    (This)->lpVtbl -> GetName(This,ppName)

#define INStimPatch_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define INStimPatch_IsPatch(This,pName)	\
    (This)->lpVtbl -> IsPatch(This,pName)

#define INStimPatch_GetParamCount(This,pParamCount)	\
    (This)->lpVtbl -> GetParamCount(This,pParamCount)

#define INStimPatch_GetParam(This,index,ppParam)	\
    (This)->lpVtbl -> GetParam(This,index,ppParam)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimPatch_AdvanceFrame_Proxy( 
    INStimPatch __RPC_FAR * This,
    int numFrames);


void __RPC_STUB INStimPatch_AdvanceFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_Draw_Proxy( 
    INStimPatch __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimPatch_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_Init_Proxy( 
    INStimPatch __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimPatch_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_FindParam_Proxy( 
    INStimPatch __RPC_FAR * This,
    unsigned char __RPC_FAR *param,
    INStimParam __RPC_FAR *__RPC_FAR *ppParam);


void __RPC_STUB INStimPatch_FindParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetCenterX_Proxy( 
    INStimPatch __RPC_FAR * This,
    int __RPC_FAR *centerX);


void __RPC_STUB INStimPatch_GetCenterX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetCenterY_Proxy( 
    INStimPatch __RPC_FAR * This,
    int __RPC_FAR *centerY);


void __RPC_STUB INStimPatch_GetCenterY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_Reset_Proxy( 
    INStimPatch __RPC_FAR * This,
    INStimEngine __RPC_FAR *pEngine);


void __RPC_STUB INStimPatch_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_SetCenterX_Proxy( 
    INStimPatch __RPC_FAR * This,
    int centerX);


void __RPC_STUB INStimPatch_SetCenterX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_SetCenterY_Proxy( 
    INStimPatch __RPC_FAR * This,
    int centerY);


void __RPC_STUB INStimPatch_SetCenterY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_SetBlitType_Proxy( 
    INStimPatch __RPC_FAR * This,
    int blitType);


void __RPC_STUB INStimPatch_SetBlitType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetBlitType_Proxy( 
    INStimPatch __RPC_FAR * This,
    int __RPC_FAR *pBlitType);


void __RPC_STUB INStimPatch_GetBlitType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetBlitAngle_Proxy( 
    INStimPatch __RPC_FAR * This,
    float __RPC_FAR *pAngle);


void __RPC_STUB INStimPatch_GetBlitAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_SetBlitAngle_Proxy( 
    INStimPatch __RPC_FAR * This,
    float angle);


void __RPC_STUB INStimPatch_SetBlitAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetType_Proxy( 
    INStimPatch __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppType);


void __RPC_STUB INStimPatch_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetName_Proxy( 
    INStimPatch __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppName);


void __RPC_STUB INStimPatch_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_SetName_Proxy( 
    INStimPatch __RPC_FAR * This,
    unsigned char __RPC_FAR *pName);


void __RPC_STUB INStimPatch_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_IsPatch_Proxy( 
    INStimPatch __RPC_FAR * This,
    unsigned char __RPC_FAR *pName);


void __RPC_STUB INStimPatch_IsPatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetParamCount_Proxy( 
    INStimPatch __RPC_FAR * This,
    int __RPC_FAR *pParamCount);


void __RPC_STUB INStimPatch_GetParamCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimPatch_GetParam_Proxy( 
    INStimPatch __RPC_FAR * This,
    int index,
    INStimParam __RPC_FAR *__RPC_FAR *ppParam);


void __RPC_STUB INStimPatch_GetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimPatch_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
