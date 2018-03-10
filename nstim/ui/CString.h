// CString.h: interface for the CString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSTRING_H__911F75D0_816B_4C6D_89D0_4A5D5FC5CE24__INCLUDED_)
#define AFX_CSTRING_H__911F75D0_816B_4C6D_89D0_4A5D5FC5CE24__INCLUDED_

#include <windows.h>

class CString  
{
	TCHAR* m_pData;
public:
	CString(TCHAR* pOther = NULL);
	CString(const CString& other);
	virtual ~CString();

	CString& operator=(const TCHAR* pOther);
	CString& operator=(const CString& other);

	TCHAR* GetData();
	const TCHAR* GetData() const;
};

#endif // !defined(AFX_CSTRING_H__911F75D0_816B_4C6D_89D0_4A5D5FC5CE24__INCLUDED_)
