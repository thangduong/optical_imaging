/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 07 08:31:44 2004
 */
/* Compiler settings for D:\Ifc4201\VegaNet\Examples\BlobOb\BlobOb.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __BlobOb_h__
#define __BlobOb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBlobAnlz_FWD_DEFINED__
#define __IBlobAnlz_FWD_DEFINED__
typedef interface IBlobAnlz IBlobAnlz;
#endif 	/* __IBlobAnlz_FWD_DEFINED__ */


#ifndef __BlobAnlz_FWD_DEFINED__
#define __BlobAnlz_FWD_DEFINED__

#ifdef __cplusplus
typedef class BlobAnlz BlobAnlz;
#else
typedef struct BlobAnlz BlobAnlz;
#endif /* __cplusplus */

#endif 	/* __BlobAnlz_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "vidsrct.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBlobAnlz_INTERFACE_DEFINED__
#define __IBlobAnlz_INTERFACE_DEFINED__

/* interface IBlobAnlz */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBlobAnlz;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADC7FF13-00EA-11D5-B17A-00105A0F576C")
    IBlobAnlz : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ThreadFunction( 
            HCProcThread threadObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBlobAreas( 
            DWORD minArea,
            DWORD maxArea) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBlobAnlzVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBlobAnlz __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBlobAnlz __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBlobAnlz __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBlobAnlz __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBlobAnlz __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBlobAnlz __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBlobAnlz __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ThreadFunction )( 
            IBlobAnlz __RPC_FAR * This,
            HCProcThread threadObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBlobAreas )( 
            IBlobAnlz __RPC_FAR * This,
            DWORD minArea,
            DWORD maxArea);
        
        END_INTERFACE
    } IBlobAnlzVtbl;

    interface IBlobAnlz
    {
        CONST_VTBL struct IBlobAnlzVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBlobAnlz_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBlobAnlz_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBlobAnlz_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBlobAnlz_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBlobAnlz_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBlobAnlz_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBlobAnlz_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBlobAnlz_ThreadFunction(This,threadObj)	\
    (This)->lpVtbl -> ThreadFunction(This,threadObj)

#define IBlobAnlz_SetBlobAreas(This,minArea,maxArea)	\
    (This)->lpVtbl -> SetBlobAreas(This,minArea,maxArea)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBlobAnlz_ThreadFunction_Proxy( 
    IBlobAnlz __RPC_FAR * This,
    HCProcThread threadObj);


void __RPC_STUB IBlobAnlz_ThreadFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBlobAnlz_SetBlobAreas_Proxy( 
    IBlobAnlz __RPC_FAR * This,
    DWORD minArea,
    DWORD maxArea);


void __RPC_STUB IBlobAnlz_SetBlobAreas_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBlobAnlz_INTERFACE_DEFINED__ */



#ifndef __BLOBOBLib_LIBRARY_DEFINED__
#define __BLOBOBLib_LIBRARY_DEFINED__

/* library BLOBOBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BLOBOBLib;

EXTERN_C const CLSID CLSID_BlobAnlz;

#ifdef __cplusplus

class DECLSPEC_UUID("ADC7FF14-00EA-11D5-B17A-00105A0F576C")
BlobAnlz;
#endif
#endif /* __BLOBOBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
