// CString.cpp: implementation of the CString class.
//
//////////////////////////////////////////////////////////////////////

#include "CString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString::CString(TCHAR* pOther)
{
	m_pData = NULL;
	(*this) = pOther;
}

CString::CString(const CString& other)
{
	m_pData = NULL;
	(*this) = other;
}


CString::~CString()
{
	delete [] m_pData;
}

CString& CString::operator=(const TCHAR* pOther)
{
	delete [] m_pData;
	if (pOther == NULL)
		m_pData = NULL;
	else
	{
#ifdef _UNICODE
		m_pData = new TCHAR[wcslen(pOther) + 1];
		wcscpy(m_pData, pOther);
#else
		m_pData = new TCHAR[strlen(pOther) + 1];
		strcpy(m_pData, pOther);
#endif
	}
	return (*this);
}

CString& CString::operator=(const CString& other)
{
	operator=(other.m_pData);
	return (*this);
}

TCHAR* CString::GetData()
{
	return m_pData;
}

const TCHAR* CString::GetData() const
{
	return m_pData;
}

