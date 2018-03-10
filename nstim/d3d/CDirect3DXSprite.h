// CDirect3DXSprite.h: interface for the CDirect3DXSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DXSPRITE_H__00909C80_5E70_44B1_81F9_67E5E43B3C5D__INCLUDED_)
#define AFX_CDIRECT3DXSPRITE_H__00909C80_5E70_44B1_81F9_67E5E43B3C5D__INCLUDED_

#include <d3dx9.h>

class CDirect3DXSprite  
{
	ID3DXSprite* m_pDirect3DXSprite;
public:
	CDirect3DXSprite();
	CDirect3DXSprite(ID3DXSprite* other) { m_pDirect3DXSprite = 0; (*this) = other; }
	CDirect3DXSprite(const CDirect3DXSprite& other) { (*this) = other; }
	virtual ~CDirect3DXSprite();

	bool IsNull() { return m_pDirect3DXSprite == 0; }
	
	CDirect3DXSprite& operator=(ID3DXSprite* other) 
	{ 
		if (m_pDirect3DXSprite)
		{
			m_pDirect3DXSprite->Release();
			m_pDirect3DXSprite = 0;
		}

		m_pDirect3DXSprite = other;
		m_pDirect3DXSprite->AddRef();

		return (*this);
	}
	CDirect3DXSprite& operator=(const CDirect3DXSprite& other) 
	{ 
		(*this) = other.m_pDirect3DXSprite;
		return (*this);
	}
	ID3DXSprite* operator->() {
		return m_pDirect3DXSprite;
	}

};

#endif // !defined(AFX_CDIRECT3DXSPRITE_H__00909C80_5E70_44B1_81F9_67E5E43B3C5D__INCLUDED_)
