/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Oct 09 08:35:07 2005
 */
/* Compiler settings for .\INStimParam.idl:
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

#ifndef __INStimParam_h__
#define __INStimParam_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INStimParam_FWD_DEFINED__
#define __INStimParam_FWD_DEFINED__
typedef interface INStimParam INStimParam;
#endif 	/* __INStimParam_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __INStimParam_INTERFACE_DEFINED__
#define __INStimParam_INTERFACE_DEFINED__

/* interface INStimParam */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_INStimParam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F255BC07-A99E-45e6-80C7-152997B4344F")
    INStimParam : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParamType( 
            unsigned char __RPC_FAR *__RPC_FAR *pType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamInt( 
            int __RPC_FAR *pInt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamDouble( 
            double __RPC_FAR *pDouble) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamName( 
            unsigned char __RPC_FAR *__RPC_FAR *ppName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParamInt( 
            int pInt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParamDouble( 
            double pDouble) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParamName( 
            unsigned char __RPC_FAR *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            DWORD __RPC_FAR *pSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetByte( 
            int index,
            unsigned char __RPC_FAR *pData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRawData( 
            unsigned char __RPC_FAR *__RPC_FAR *ppRawdata) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamFloat( 
            float __RPC_FAR *pFloat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParamFloat( 
            float value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParamString( 
            unsigned char __RPC_FAR *pStr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParamString( 
            unsigned char __RPC_FAR *buff,
            int buffSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INStimParamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INStimParam __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INStimParam __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INStimParam __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamType )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamInt )( 
            INStimParam __RPC_FAR * This,
            int __RPC_FAR *pInt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamDouble )( 
            INStimParam __RPC_FAR * This,
            double __RPC_FAR *pDouble);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamName )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParamInt )( 
            INStimParam __RPC_FAR * This,
            int pInt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParamDouble )( 
            INStimParam __RPC_FAR * This,
            double pDouble);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParamName )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            INStimParam __RPC_FAR * This,
            DWORD __RPC_FAR *pSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetByte )( 
            INStimParam __RPC_FAR * This,
            int index,
            unsigned char __RPC_FAR *pData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRawData )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *__RPC_FAR *ppRawdata);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamFloat )( 
            INStimParam __RPC_FAR * This,
            float __RPC_FAR *pFloat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParamFloat )( 
            INStimParam __RPC_FAR * This,
            float value);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParamString )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *pStr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParamString )( 
            INStimParam __RPC_FAR * This,
            unsigned char __RPC_FAR *buff,
            int buffSize);
        
        END_INTERFACE
    } INStimParamVtbl;

    interface INStimParam
    {
        CONST_VTBL struct INStimParamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INStimParam_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INStimParam_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INStimParam_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INStimParam_GetParamType(This,pType)	\
    (This)->lpVtbl -> GetParamType(This,pType)

#define INStimParam_GetParamInt(This,pInt)	\
    (This)->lpVtbl -> GetParamInt(This,pInt)

#define INStimParam_GetParamDouble(This,pDouble)	\
    (This)->lpVtbl -> GetParamDouble(This,pDouble)

#define INStimParam_GetParamName(This,ppName)	\
    (This)->lpVtbl -> GetParamName(This,ppName)

#define INStimParam_SetParamInt(This,pInt)	\
    (This)->lpVtbl -> SetParamInt(This,pInt)

#define INStimParam_SetParamDouble(This,pDouble)	\
    (This)->lpVtbl -> SetParamDouble(This,pDouble)

#define INStimParam_SetParamName(This,pName)	\
    (This)->lpVtbl -> SetParamName(This,pName)

#define INStimParam_GetSize(This,pSize)	\
    (This)->lpVtbl -> GetSize(This,pSize)

#define INStimParam_GetByte(This,index,pData)	\
    (This)->lpVtbl -> GetByte(This,index,pData)

#define INStimParam_GetRawData(This,ppRawdata)	\
    (This)->lpVtbl -> GetRawData(This,ppRawdata)

#define INStimParam_GetParamFloat(This,pFloat)	\
    (This)->lpVtbl -> GetParamFloat(This,pFloat)

#define INStimParam_SetParamFloat(This,value)	\
    (This)->lpVtbl -> SetParamFloat(This,value)

#define INStimParam_SetParamString(This,pStr)	\
    (This)->lpVtbl -> SetParamString(This,pStr)

#define INStimParam_GetParamString(This,buff,buffSize)	\
    (This)->lpVtbl -> GetParamString(This,buff,buffSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INStimParam_GetParamType_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *pType);


void __RPC_STUB INStimParam_GetParamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetParamInt_Proxy( 
    INStimParam __RPC_FAR * This,
    int __RPC_FAR *pInt);


void __RPC_STUB INStimParam_GetParamInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetParamDouble_Proxy( 
    INStimParam __RPC_FAR * This,
    double __RPC_FAR *pDouble);


void __RPC_STUB INStimParam_GetParamDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetParamName_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppName);


void __RPC_STUB INStimParam_GetParamName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_SetParamInt_Proxy( 
    INStimParam __RPC_FAR * This,
    int pInt);


void __RPC_STUB INStimParam_SetParamInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_SetParamDouble_Proxy( 
    INStimParam __RPC_FAR * This,
    double pDouble);


void __RPC_STUB INStimParam_SetParamDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_SetParamName_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *pName);


void __RPC_STUB INStimParam_SetParamName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetSize_Proxy( 
    INStimParam __RPC_FAR * This,
    DWORD __RPC_FAR *pSize);


void __RPC_STUB INStimParam_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetByte_Proxy( 
    INStimParam __RPC_FAR * This,
    int index,
    unsigned char __RPC_FAR *pData);


void __RPC_STUB INStimParam_GetByte_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetRawData_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *__RPC_FAR *ppRawdata);


void __RPC_STUB INStimParam_GetRawData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetParamFloat_Proxy( 
    INStimParam __RPC_FAR * This,
    float __RPC_FAR *pFloat);


void __RPC_STUB INStimParam_GetParamFloat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_SetParamFloat_Proxy( 
    INStimParam __RPC_FAR * This,
    float value);


void __RPC_STUB INStimParam_SetParamFloat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_SetParamString_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *pStr);


void __RPC_STUB INStimParam_SetParamString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INStimParam_GetParamString_Proxy( 
    INStimParam __RPC_FAR * This,
    unsigned char __RPC_FAR *buff,
    int buffSize);


void __RPC_STUB INStimParam_GetParamString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INStimParam_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
