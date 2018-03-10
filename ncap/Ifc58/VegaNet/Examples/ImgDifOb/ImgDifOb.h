/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 07 08:33:26 2004
 */
/* Compiler settings for D:\Ifc4201\VegaNet\Examples\ImgDifOb\ImgDifOb.idl:
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

#ifndef __ImgDifOb_h__
#define __ImgDifOb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IImageDIff_FWD_DEFINED__
#define __IImageDIff_FWD_DEFINED__
typedef interface IImageDIff IImageDIff;
#endif 	/* __IImageDIff_FWD_DEFINED__ */


#ifndef __ImageDIff_FWD_DEFINED__
#define __ImageDIff_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageDIff ImageDIff;
#else
typedef struct ImageDIff ImageDIff;
#endif /* __cplusplus */

#endif 	/* __ImageDIff_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "vidsrct.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IImageDIff_INTERFACE_DEFINED__
#define __IImageDIff_INTERFACE_DEFINED__

/* interface IImageDIff */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IImageDIff;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00CDBE91-5607-11D6-B243-00105A0F576C")
    IImageDIff : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ThreadFunction( 
            HCProcThread threadObj) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageDIffVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageDIff __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageDIff __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageDIff __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImageDIff __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImageDIff __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImageDIff __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImageDIff __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ThreadFunction )( 
            IImageDIff __RPC_FAR * This,
            HCProcThread threadObj);
        
        END_INTERFACE
    } IImageDIffVtbl;

    interface IImageDIff
    {
        CONST_VTBL struct IImageDIffVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageDIff_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageDIff_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageDIff_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageDIff_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImageDIff_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImageDIff_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImageDIff_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImageDIff_ThreadFunction(This,threadObj)	\
    (This)->lpVtbl -> ThreadFunction(This,threadObj)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageDIff_ThreadFunction_Proxy( 
    IImageDIff __RPC_FAR * This,
    HCProcThread threadObj);


void __RPC_STUB IImageDIff_ThreadFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageDIff_INTERFACE_DEFINED__ */



#ifndef __IMGDIFOBLib_LIBRARY_DEFINED__
#define __IMGDIFOBLib_LIBRARY_DEFINED__

/* library IMGDIFOBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMGDIFOBLib;

EXTERN_C const CLSID CLSID_ImageDIff;

#ifdef __cplusplus

class DECLSPEC_UUID("00CDBE92-5607-11D6-B243-00105A0F576C")
ImageDIff;
#endif
#endif /* __IMGDIFOBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
