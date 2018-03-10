/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Oct 02 22:20:15 2005
 */
/* Compiler settings for .\INStimCmdEngine.idl:
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

#ifndef __INStimCmdEngine_h__
#define __INStimCmdEngine_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimCmdEngine_FWD_DEFINED__
#define __INStimCmdEngine_FWD_DEFINED__
typedef interface INStimCmdEngine INStimCmdEngine;
#endif 	/* __INStimCmdEngine_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "IPortServerCallback.h"
#include "IPortCallback.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INStimCmdEngine_INTERFACE_DEFINED__
#define __INStimCmdEngine_INTERFACE_DEFINED__

/* interface INStimCmdEngine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimCmdEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8EA6019A-3FB3-447c-B2A1-F25E654972B7")
    INStimCmdEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Test( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimCmdEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimCmdEngine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimCmdEngine __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimCmdEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test )( 
            INStimCmdEngine __RPC_FAR * This);
        
        END_INTERFACE
    } INStimCmdEngineVtbl;

    interface INStimCmdEngine
    {
        CONST_VTBL struct INStimCmdEngineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimCmdEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimCmdEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimCmdEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimCmdEngine_Test(This)	\
    (This)->lpVtbl -> Test(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimCmdEngine_Test_Proxy( 
    INStimCmdEngine __RPC_FAR * This);


void __RPC_STUB INStimCmdEngine_Test_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimCmdEngine_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
