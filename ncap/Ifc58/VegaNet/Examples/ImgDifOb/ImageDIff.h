	
// ImageDIff.h : Declaration of the CImageDIff

#ifndef __IMAGEDIFF_H_
#define __IMAGEDIFF_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageDIff
class ATL_NO_VTABLE CImageDIff : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CImageDIff, &CLSID_ImageDIff>,
	public IDispatchImpl<IImageDIff, &IID_IImageDIff, &LIBID_IMGDIFOBLib>
{
public:
	CImageDIff()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IMAGEDIFF)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageDIff)
	COM_INTERFACE_ENTRY(IImageDIff)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// IImageDIff
public:
	STDMETHOD(ThreadFunction)(HCProcThread threadObj);
};

#endif //__IMAGEDIFF_H_
