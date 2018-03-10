// CDirect3DDevice.cpp: implementation of the CDirect3DDevice class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "CDirect3DDevice.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirect3DDevice::CDirect3DDevice()
{

}

CDirect3DDevice::~CDirect3DDevice()
{

}

CDirect3DSurface CDirect3DDevice::CreateSurface(int width, int height, D3DFORMAT format, D3DPOOL pool)
{
	IDirect3DSurface9* pSurface = NULL;
	m_Direct3DDevice->CreateOffscreenPlainSurface(width, height, format, pool, &pSurface, NULL);
	CDirect3DSurface result = (pSurface);
	if (pSurface)
		pSurface->Release();
	return result;
}

CDirect3DTexture CDirect3DDevice::CreateTexture(int width, int height, int level, DWORD usage, D3DFORMAT format, D3DPOOL pool)
{
#ifdef _DEBUG
	char dbgMsg[512];
	sprintf(dbgMsg, "CDirect3DDevice::CreateTexture: width = %d height = %d level = %d usage = %d format = %d pool = %d",
			width, height, level, usage, format, pool);
	OutputDebugString(dbgMsg);
#endif
	IDirect3DTexture9* pTexture = NULL;
	HRESULT hr = m_Direct3DDevice->CreateTexture(width, height, level, usage, format, pool, &pTexture, NULL);
#ifdef _DEBUG
	if (FAILED(hr)) {
		switch(hr) {
		case D3DERR_INVALIDCALL:
			OutputDebugString("CDirect3DDevice::CreateTexture: D3DERR_INVALIDCALL\r\n");
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			OutputDebugString("CDirect3DDevice::CreateTexture: D3DERR_OUTOFVIDEOMEMORY\r\n");
			break;
		case E_OUTOFMEMORY:
			OutputDebugString("CDirect3DDevice::CreateTexture: E_OUTOFMEMORY\r\n");
			break;
		case D3D_OK:
			OutputDebugString("CDirect3DDevice::CreateTexture: seems ok\r\n");
			break;
		case D3DOK_NOAUTOGEN:
			OutputDebugString("CDirect3DDevice::CreateTexture: no mipmap\r\n");
			break;
		default:
			OutputDebugString("CDirect3DDevice::CreateTexture: failed with unknown error\r\n");
		}
	}
	else
		OutputDebugString("create texture successful\r\n");
	char temp[512];
	sprintf(temp, "texture = %08X\r\n", pTexture);
	OutputDebugString(temp);
#endif
	CDirect3DTexture result = (pTexture);
	if (pTexture)
		pTexture->Release();
	return result;
}

CDirect3DVertexBuffer CDirect3DDevice::CreateVertexBuffer(UINT length, DWORD usage, DWORD fvf, D3DPOOL pool)
{
	CDirect3DVertexBuffer result;
	IDirect3DVertexBuffer9* pVb = 0;
	HRESULT hr = m_Direct3DDevice->CreateVertexBuffer(length, usage, fvf, pool, &pVb, 0);
	result = pVb;
	return result;
}

