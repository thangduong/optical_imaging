#ifndef CSMARTPTR_H
#define CSMARTPTR_H
#include <stdio.h>
#include <unknwn.h>

#define	IIDFromType(TYPE)	(IID_##TYPE)

template <class TYPE>
class CSmartPtr
{
private:
	TYPE* m_pType;
public:
	CSmartPtr(IUnknown* pUnknown)
	{
		m_pType = NULL;
		(*this) = pUnknown;
	}
	CSmartPtr(TYPE* pType = 0)
	{
		m_pType = NULL;
		(*this) = pType;
	}
	CSmartPtr(const CSmartPtr<TYPE>& other) {
		m_pType = NULL;
		(*this) = other;
	}

	virtual ~CSmartPtr()
	{
		if (m_pType)
		{
#ifdef _DEBUG
			int v = 
#endif
			m_pType->Release();
#ifdef _DEBUG
			char dbgMsg[512];
			sprintf(dbgMsg, "CSmartPtr releasing has %d references %08X\r\n", v, (DWORD)m_pType
				);
//			OutputDebugString(dbgMsg);
#endif
		}
	}

	IUnknown* operator=(IUnknown* pUnknown)
	{
		if (pUnknown == 0)
		{
			if (m_pType)
			{
				m_pType->Release();
				m_pType = 0;
			}
		}
		else
		{
			if (m_pType)
			{
				m_pType->Release();
				m_pType = 0;
			}
//			UUID uid = __uuidof(TYPE);
//			UUID iid2 = IID_IDirect3DDevice9;
			pUnknown->QueryInterface(__uuidof(TYPE), (void**)&m_pType);
		}

		return (IUnknown*)GetPtr();
	}

	TYPE* operator=(TYPE* pType)
	{
		if (pType == 0)
		{
			if (m_pType)
			{
				m_pType->Release();
				m_pType = 0;
			}
		}
		else
		{
			if (m_pType)
			{
				m_pType->Release();
				m_pType = 0;
			}
			m_pType = pType;
			m_pType->AddRef();
		}

		return m_pType;
	}

	CSmartPtr<TYPE>& operator=(const CSmartPtr<TYPE>& ptr) 
	{
		(*this) = (IUnknown*)ptr.m_pType;
		return (*this);
	}

	TYPE* GetPtr() const { 
		return m_pType;
	}

	TYPE* operator->() const {
		return m_pType;
	}

	const bool IsNull() const { return (m_pType == 0) ? true :false; }
};

#endif
