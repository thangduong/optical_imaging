// CDirect3DDevice.h: interface for the CDirect3DDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DDEVICE_H__5C7A38C4_4CDC_49D3_A02A_C0CF35A2AA0A__INCLUDED_)
#define AFX_CDIRECT3DDEVICE_H__5C7A38C4_4CDC_49D3_A02A_C0CF35A2AA0A__INCLUDED_

#include <d3dx9.h>
#include "CSmartPtr.h"
#include "CDirect3DSurface.h"
#include "CDirect3DTexture.h"
#include "CDirect3DVertexBuffer.h"

class CDirect3DDevice  
{
	CSmartPtr<IDirect3DDevice9> m_Direct3DDevice;
public:
	CDirect3DDevice();
	CDirect3DDevice(IDirect3DDevice9* other) { m_Direct3DDevice = other; }
	CDirect3DDevice(CSmartPtr<IDirect3DDevice9> other) { m_Direct3DDevice = other; }
	CDirect3DDevice(const CDirect3DDevice& other) { (*this) = other; }
	virtual ~CDirect3DDevice();

	CDirect3DDevice& operator=(const CDirect3DDevice& other) {
		m_Direct3DDevice = other.m_Direct3DDevice;
		return (*this);
	}

	CDirect3DDevice& operator=(IDirect3DDevice9* other) {
		m_Direct3DDevice = other;
		return (*this);
	}

	CSmartPtr<IDirect3DDevice9> operator->() {
		return m_Direct3DDevice;
	}

	IDirect3DDevice9* GetDirect3DDevice() {
		return m_Direct3DDevice.GetPtr();
	}

	bool IsNull() { return m_Direct3DDevice.IsNull(); }

	CDirect3DSurface CreateSurface(int width, int height, D3DFORMAT format, D3DPOOL pool);
	CDirect3DTexture CreateTexture(int width, int height, int level, DWORD usage, D3DFORMAT format, D3DPOOL pool);

	CDirect3DSurface GetBackBuffer(UINT iSwapChain, UINT BackBuffer, D3DBACKBUFFER_TYPE Type) {
	    IDirect3DSurface9 *pBackBuffer = 0;
		m_Direct3DDevice->GetBackBuffer(iSwapChain, BackBuffer, Type, &pBackBuffer);
		CDirect3DSurface result = pBackBuffer;
		if (pBackBuffer)
			pBackBuffer->Release();
		return result;
	}

	CDirect3DVertexBuffer CreateVertexBuffer(UINT length, DWORD usage, DWORD fvf, D3DPOOL pool);
};

#endif // !defined(AFX_CDIRECT3DDEVICE_H__5C7A38C4_4CDC_49D3_A02A_C0CF35A2AA0A__INCLUDED_)
