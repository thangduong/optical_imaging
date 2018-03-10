// CDirect3D.h: interface for the CDirect3D class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CDIRECT3D_H
#define CDIRECT3D_H

#include <d3dx9.h>
#include "CSmartPtr.h"

class CDirect3D  
{
	CSmartPtr<IDirect3D9> m_Direct3D;


public:
	CDirect3D();
	CDirect3D(const CDirect3D& other) { (*this) = other; }
	virtual ~CDirect3D();


	bool Init();

	IDirect3D9* GetDirect3D() const {
		return m_Direct3D.GetPtr();
	}

	CDirect3D& operator=(const CDirect3D& other) {
		m_Direct3D = other.m_Direct3D;
		return (*this);
	}

	CDirect3D& operator=(IDirect3D9* other) {
		m_Direct3D = other;
		return (*this);
	}

	CSmartPtr<IDirect3D9> operator->() const {
		return m_Direct3D;
	}

	bool IsNull() { return m_Direct3D.IsNull(); }

};

#endif
