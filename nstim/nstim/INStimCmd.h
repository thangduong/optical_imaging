/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 16 00:31:54 2006
 */
/* Compiler settings for .\INStimCmd.idl:
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

#ifndef __INStimCmd_h__
#define __INStimCmd_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimCmd_FWD_DEFINED__
#define __INStimCmd_FWD_DEFINED__
typedef interface INStimCmd INStimCmd;
#endif 	/* __INStimCmd_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "INStimApp.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_INStimCmd_0000 */
/* [local] */ 





extern RPC_IF_HANDLE __MIDL_itf_INStimCmd_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_INStimCmd_0000_v0_0_s_ifspec;

#ifndef __INStimCmd_INTERFACE_DEFINED__
#define __INStimCmd_INTERFACE_DEFINED__

/* interface INStimCmd */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimCmd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9DD58F94-E8DA-479c-A4A3-3198A728415D")
    INStimCmd : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsCmd( 
            unsigned char __RPC_FAR *pCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Exec( 
            unsigned char __RPC_FAR *pCmd,
            INStimApp __RPC_FAR *pApp,
            IPort __RPC_FAR *pPort) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Help( 
            unsigned char __RPC_FAR *Desc,
            INStimApp __RPC_FAR *pApp,
            IPort __RPC_FAR *pPort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimCmdVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimCmd __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimCmd __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimCmd __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCmd )( 
            INStimCmd __RPC_FAR * This,
            unsigned char __RPC_FAR *pCmd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Exec )( 
            INStimCmd __RPC_FAR * This,
            unsigned char __RPC_FAR *pCmd,
            INStimApp __RPC_FAR *pApp,
            IPort __RPC_FAR *pPort);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Help )( 
            INStimCmd __RPC_FAR * This,
            unsigned char __RPC_FAR *Desc,
            INStimApp __RPC_FAR *pApp,
            IPort __RPC_FAR *pPort);
        
        END_INTERFACE
    } INStimCmdVtbl;

    interface INStimCmd
    {
        CONST_VTBL struct INStimCmdVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimCmd_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimCmd_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimCmd_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimCmd_IsCmd(This,pCmd)	\
    (This)->lpVtbl -> IsCmd(This,pCmd)

#define INStimCmd_Exec(This,pCmd,pApp,pPort)	\
    (This)->lpVtbl -> Exec(This,pCmd,pApp,pPort)

#define INStimCmd_Help(This,Desc,pApp,pPort)	\
    (This)->lpVtbl -> Help(This,Desc,pApp,pPort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimCmd_IsCmd_Proxy( 
    INStimCmd __RPC_FAR * This,
    unsigned char __RPC_FAR *pCmd);


void __RPC_STUB INStimCmd_IsCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimCmd_Exec_Proxy( 
    INStimCmd __RPC_FAR * This,
    unsigned char __RPC_FAR *pCmd,
    INStimApp __RPC_FAR *pApp,
    IPort __RPC_FAR *pPort);


void __RPC_STUB INStimCmd_Exec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimCmd_Help_Proxy( 
    INStimCmd __RPC_FAR * This,
    unsigned char __RPC_FAR *Desc,
    INStimApp __RPC_FAR *pApp,
    IPort __RPC_FAR *pPort);


void __RPC_STUB INStimCmd_Help_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimCmd_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
