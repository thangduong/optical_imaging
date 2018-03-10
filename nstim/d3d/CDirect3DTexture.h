// CDirect3DTexture.h: interface for the CDirect3DTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DTEXTURE_H__AB48C5C8_ECB4_4272_B1AF_DABB2D9A5A0E__INCLUDED_)
#define AFX_CDIRECT3DTEXTURE_H__AB48C5C8_ECB4_4272_B1AF_DABB2D9A5A0E__INCLUDED_

#include <d3dx9.h>
#include "CSmartPtr.h"
#include "CDirect3DSurface.h"


class CDirect3DTexture  
{
	CSmartPtr<IDirect3DTexture9> m_Direct3DTexture;
public:
	CDirect3DTexture();
	CDirect3DTexture(IDirect3DTexture9* other) { m_Direct3DTexture = other; }
	CDirect3DTexture(CSmartPtr<IDirect3DTexture9> other) { m_Direct3DTexture = other; }
	CDirect3DTexture(const CDirect3DTexture& other) { (*this) = other; }
	virtual ~CDirect3DTexture();

	bool IsNull() { return m_Direct3DTexture.IsNull(); }

	CDirect3DSurface GetSurface(int level) { 
		IDirect3DSurface9* pSurf = 0;
		m_Direct3DTexture->GetSurfaceLevel(level, &pSurf);
		CDirect3DSurface result = pSurf;
		if (pSurf)
			pSurf->Release();
		return result;
	}
	IDirect3DTexture9* GetDirect3DTexture() {
		return m_Direct3DTexture.GetPtr();
	}
	CSmartPtr<IDirect3DTexture9> operator->() {
		return m_Direct3DTexture;
	}
};

#endif // !defined(AFX_CDIRECT3DTEXTURE_H__AB48C5C8_ECB4_4272_B1AF_DABB2D9A5A0E__INCLUDED_)
