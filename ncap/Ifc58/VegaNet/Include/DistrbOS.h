	
// DistribOS.h : Declaration of the CDistribOS

#ifndef __DISTRBOS_H_
#define __DISTRBOS_H_

#include <DstOsres.h>       // main symbols
#include <DstrbdOs.h>


/////////////////////////////////////////////////////////////////////////////
// CDistribOS
class ATL_NO_VTABLE CDistribOS : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDistribOS, &CLSID_DistribOS>,
	public IDistributedOsImpl<IDispatchImpl<IDistribOS, &IID_IDistribOS, &LIBID_VNVIDSRCLib>, &IID_IDistribOS>
{
public:
	CDistribOS() { m_pUnkMarshaler = NULL; }
	~CDistribOS() {};

DECLARE_REGISTRY_RESOURCEID(IDR_DISTRBOS)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDistribOS)
	COM_INTERFACE_ENTRY(IDistribOS)
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

// IDistribOS
public:



};

#endif //__DISTRBOS_H_
