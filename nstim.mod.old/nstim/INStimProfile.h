/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Oct 02 22:20:14 2005
 */
/* Compiler settings for .\INStimProfile.idl:
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

#ifndef __INStimProfile_h__
#define __INStimProfile_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimProfile_FWD_DEFINED__
#define __INStimProfile_FWD_DEFINED__
typedef interface INStimProfile INStimProfile;
#endif 	/* __INStimProfile_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INStimProfile_INTERFACE_DEFINED__
#define __INStimProfile_INTERFACE_DEFINED__

/* interface INStimProfile */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85D85EAD-4839-4085-93D3-30C8B3DF8262")
    INStimProfile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsFullscreen( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTcpIpCmdPort( 
            DWORD __RPC_FAR *pPort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTcpIpBindAddress( 
            unsigned char __RPC_FAR *__RPC_FAR *pBindAddr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapXCoordinate( 
            const unsigned char __RPC_FAR *pData,
            int __RPC_FAR *pXCoord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapYCoordinate( 
            const unsigned char __RPC_FAR *pData,
            int __RPC_FAR *pYCoord) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShouldHideCursor( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLptSyncPortInfo( 
            int __RPC_FAR *pPortNum,
            int __RPC_FAR *pPreFrame,
            int __RPC_FAR *pPostFrame,
            int __RPC_FAR *pStimOnStrobeBit,
            int __RPC_FAR *pFrameDropBit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGraphicsEngineThreadPriority( 
            int __RPC_FAR *pPriority) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWindowedResolution( 
            int __RPC_FAR *pWidth,
            int __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFullscreenResolution( 
            int __RPC_FAR *pWidth,
            int __RPC_FAR *pHeight,
            int __RPC_FAR *pFramerate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsFullscreen )( 
            INStimProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTcpIpCmdPort )( 
            INStimProfile __RPC_FAR * This,
            DWORD __RPC_FAR *pPort);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTcpIpBindAddress )( 
            INStimProfile __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *pBindAddr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapXCoordinate )( 
            INStimProfile __RPC_FAR * This,
            const unsigned char __RPC_FAR *pData,
            int __RPC_FAR *pXCoord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapYCoordinate )( 
            INStimProfile __RPC_FAR * This,
            const unsigned char __RPC_FAR *pData,
            int __RPC_FAR *pYCoord);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShouldHideCursor )( 
            INStimProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLptSyncPortInfo )( 
            INStimProfile __RPC_FAR * This,
            int __RPC_FAR *pPortNum,
            int __RPC_FAR *pPreFrame,
            int __RPC_FAR *pPostFrame,
            int __RPC_FAR *pStimOnStrobeBit,
            int __RPC_FAR *pFrameDropBit);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGraphicsEngineThreadPriority )( 
            INStimProfile __RPC_FAR * This,
            int __RPC_FAR *pPriority);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowedResolution )( 
            INStimProfile __RPC_FAR * This,
            int __RPC_FAR *pWidth,
            int __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFullscreenResolution )( 
            INStimProfile __RPC_FAR * This,
            int __RPC_FAR *pWidth,
            int __RPC_FAR *pHeight,
            int __RPC_FAR *pFramerate);
        
        END_INTERFACE
    } INStimProfileVtbl;

    interface INStimProfile
    {
        CONST_VTBL struct INStimProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimProfile_IsFullscreen(This)	\
    (This)->lpVtbl -> IsFullscreen(This)

#define INStimProfile_GetTcpIpCmdPort(This,pPort)	\
    (This)->lpVtbl -> GetTcpIpCmdPort(This,pPort)

#define INStimProfile_GetTcpIpBindAddress(This,pBindAddr)	\
    (This)->lpVtbl -> GetTcpIpBindAddress(This,pBindAddr)

#define INStimProfile_MapXCoordinate(This,pData,pXCoord)	\
    (This)->lpVtbl -> MapXCoordinate(This,pData,pXCoord)

#define INStimProfile_MapYCoordinate(This,pData,pYCoord)	\
    (This)->lpVtbl -> MapYCoordinate(This,pData,pYCoord)

#define INStimProfile_ShouldHideCursor(This)	\
    (This)->lpVtbl -> ShouldHideCursor(This)

#define INStimProfile_GetLptSyncPortInfo(This,pPortNum,pPreFrame,pPostFrame,pStimOnStrobeBit,pFrameDropBit)	\
    (This)->lpVtbl -> GetLptSyncPortInfo(This,pPortNum,pPreFrame,pPostFrame,pStimOnStrobeBit,pFrameDropBit)

#define INStimProfile_GetGraphicsEngineThreadPriority(This,pPriority)	\
    (This)->lpVtbl -> GetGraphicsEngineThreadPriority(This,pPriority)

#define INStimProfile_GetWindowedResolution(This,pWidth,pHeight)	\
    (This)->lpVtbl -> GetWindowedResolution(This,pWidth,pHeight)

#define INStimProfile_GetFullscreenResolution(This,pWidth,pHeight,pFramerate)	\
    (This)->lpVtbl -> GetFullscreenResolution(This,pWidth,pHeight,pFramerate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimProfile_IsFullscreen_Proxy( 
    INStimProfile __RPC_FAR * This);


void __RPC_STUB INStimProfile_IsFullscreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetTcpIpCmdPort_Proxy( 
    INStimProfile __RPC_FAR * This,
    DWORD __RPC_FAR *pPort);


void __RPC_STUB INStimProfile_GetTcpIpCmdPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetTcpIpBindAddress_Proxy( 
    INStimProfile __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *pBindAddr);


void __RPC_STUB INStimProfile_GetTcpIpBindAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_MapXCoordinate_Proxy( 
    INStimProfile __RPC_FAR * This,
    const unsigned char __RPC_FAR *pData,
    int __RPC_FAR *pXCoord);


void __RPC_STUB INStimProfile_MapXCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_MapYCoordinate_Proxy( 
    INStimProfile __RPC_FAR * This,
    const unsigned char __RPC_FAR *pData,
    int __RPC_FAR *pYCoord);


void __RPC_STUB INStimProfile_MapYCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_ShouldHideCursor_Proxy( 
    INStimProfile __RPC_FAR * This);


void __RPC_STUB INStimProfile_ShouldHideCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetLptSyncPortInfo_Proxy( 
    INStimProfile __RPC_FAR * This,
    int __RPC_FAR *pPortNum,
    int __RPC_FAR *pPreFrame,
    int __RPC_FAR *pPostFrame,
    int __RPC_FAR *pStimOnStrobeBit,
    int __RPC_FAR *pFrameDropBit);


void __RPC_STUB INStimProfile_GetLptSyncPortInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetGraphicsEngineThreadPriority_Proxy( 
    INStimProfile __RPC_FAR * This,
    int __RPC_FAR *pPriority);


void __RPC_STUB INStimProfile_GetGraphicsEngineThreadPriority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetWindowedResolution_Proxy( 
    INStimProfile __RPC_FAR * This,
    int __RPC_FAR *pWidth,
    int __RPC_FAR *pHeight);


void __RPC_STUB INStimProfile_GetWindowedResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimProfile_GetFullscreenResolution_Proxy( 
    INStimProfile __RPC_FAR * This,
    int __RPC_FAR *pWidth,
    int __RPC_FAR *pHeight,
    int __RPC_FAR *pFramerate);


void __RPC_STUB INStimProfile_GetFullscreenResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimProfile_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
