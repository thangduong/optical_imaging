	
// BlobAnlz.h : Declaration of the CBlobAnlz

#ifndef __BLOBANLZ_H_
#define __BLOBANLZ_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBlobAnlz
class ATL_NO_VTABLE CBlobAnlz : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CBlobAnlz, &CLSID_BlobAnlz>,
	public IDispatchImpl<IBlobAnlz, &IID_IBlobAnlz, &LIBID_BLOBOBLib>
{
public:
	CBlobAnlz();

	~CBlobAnlz();

DECLARE_REGISTRY_RESOURCEID(IDR_BLOBANLZ)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBlobAnlz)
	COM_INTERFACE_ENTRY(IBlobAnlz)
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

// IBlobAnlz

	DWORD m_minBlobArea;
	DWORD m_maxBlobArea;

public:
	STDMETHOD(SetBlobAreas)(DWORD minArea, DWORD maxArea);
	STDMETHOD(ThreadFunction)(HCProcThread threadObj);
};

#endif //__BLOBANLZ_H_
