// CDirect3DVertexBuffer.h: interface for the CDirect3DVertexBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DVERTEXBUFFER_H__4A620BB3_D994_4059_B534_F5E4BD1E6CBD__INCLUDED_)
#define AFX_CDIRECT3DVERTEXBUFFER_H__4A620BB3_D994_4059_B534_F5E4BD1E6CBD__INCLUDED_

#include <d3dx9.h>
#include "CSmartPtr.h"

class CDirect3DVertexBuffer  
{
	CSmartPtr<IDirect3DVertexBuffer9> m_Direct3DVertexBuffer;
public:
	CDirect3DVertexBuffer();
	CDirect3DVertexBuffer(IDirect3DVertexBuffer9* other) { m_Direct3DVertexBuffer = other; }
	CDirect3DVertexBuffer(CSmartPtr<IDirect3DVertexBuffer9> other) { m_Direct3DVertexBuffer = other; }
	CDirect3DVertexBuffer(const CDirect3DVertexBuffer& other) { (*this) = other; }
	virtual ~CDirect3DVertexBuffer();

	bool IsNull() { return m_Direct3DVertexBuffer.IsNull(); }

	IDirect3DVertexBuffer9* GetDirect3DVertexBuffer() {
		return m_Direct3DVertexBuffer.GetPtr();
	}
	CSmartPtr<IDirect3DVertexBuffer9> operator->() {
		return m_Direct3DVertexBuffer;
	}

};

#endif // !defined(AFX_CDIRECT3DVERTEXBUFFER_H__4A620BB3_D994_4059_B534_F5E4BD1E6CBD__INCLUDED_)
