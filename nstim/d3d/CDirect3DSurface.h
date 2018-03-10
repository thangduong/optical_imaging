// CDirect3DSurface.h: interface for the CDirect3DSurface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DSURFACE_H__F23BEE88_65BF_4947_A0CD_70449FC28466__INCLUDED_)
#define AFX_CDIRECT3DSURFACE_H__F23BEE88_65BF_4947_A0CD_70449FC28466__INCLUDED_

#include <d3dx9.h>
#include "CSmartPtr.h"

class CDirect3DSurface  
{
	CSmartPtr<IDirect3DSurface9> m_Direct3DSurface;
public:
	CDirect3DSurface();
	CDirect3DSurface(IDirect3DSurface9* surface) { m_Direct3DSurface = surface; }
	CDirect3DSurface(CSmartPtr<IDirect3DSurface9> surface) { m_Direct3DSurface = surface; }
	CDirect3DSurface(const CDirect3DSurface& surface) { (*this) = surface; }
	virtual ~CDirect3DSurface();

	bool IsNull() { return m_Direct3DSurface.IsNull(); }


	IDirect3DSurface9* GetDirect3DSurface() {
		return m_Direct3DSurface.GetPtr();
	}

	CSmartPtr<IDirect3DSurface9> operator->() {
		return m_Direct3DSurface;
	}

};

#endif // !defined(AFX_CDIRECT3DSURFACE_H__F23BEE88_65BF_4947_A0CD_70449FC28466__INCLUDED_)
