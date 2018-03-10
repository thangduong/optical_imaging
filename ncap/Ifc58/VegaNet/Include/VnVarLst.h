// VnVarLst.h: interface for the CVnVarList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VNVARLST_H__3F0938B6_7F3A_11D4_B13F_00105A0F576C__INCLUDED_)
#define AFX_VNVARLST_H__3F0938B6_7F3A_11D4_B13F_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vidsrct.h>


class IVS_EXT_API CVnVarList
{
public:
	CVnVarList();

	CVnVarList(VSPARAM *list,DWORD *numItems,DWORD maxNumItems);

	virtual ~CVnVarList();

	VSPARAM *FindItem(LPCTSTR key);

	BOOL RemoveItem(LPCTSTR key);

	CVnVar& operator[](LPCTSTR key);

#ifdef  UNICODE           
	CVnVar& operator[](LPCSTR key);
#endif


private:
	VSPARAM *m_list;
	DWORD *m_numItems;
	DWORD m_maxNumItems;
	CVnVar m_nullItem;
};



template <class T>
class CVSList
{

	typedef struct {
		T x;
		CVSStr key;
	} _VsTItem;

public:

	CVSList(DWORD maxNumItems=20,BOOL zeroInit=FALSE);

	virtual ~CVSList();

	_VsTItem *FindItem(LPCTSTR key);

	BOOL RemoveItem(LPCTSTR key);

	void ClearList(void);

	DWORD NumElements(void);

	T& operator[](LPCTSTR key);

#ifdef  UNICODE                     // r_winnt
	T& operator[](LPCSTR key);
#endif

private:
	_VsTItem *m_list;
	DWORD m_numItems;
	DWORD m_maxNumItems;
	T m_nullItem;
};


template <class T>
CVSList<T>::CVSList(DWORD maxNumItems,BOOL zeroInit)
{
	DWORD i;
	m_list = new _VsTItem[maxNumItems];
	if (zeroInit) {
		for (i=0; i < maxNumItems; i++) 
			memset(&m_list[i].x,0,sizeof(_VsTItem) );
	}
	m_numItems = 0;
	m_maxNumItems = maxNumItems;
	memset(&m_nullItem,0,sizeof(T));	
}


template <class T>
CVSList<T>::~CVSList()
{
	delete [] m_list;
}


template <class T>
CVSList<T>::_VsTItem *CVSList<T>::FindItem(LPCTSTR key)
{
	DWORD i;
	if (!m_list)
		return NULL;
	for (i=0; i < m_numItems; i++)
		if (m_list[i].key == key)
			return &m_list[i];
	return NULL;
}


template <class T>
T& CVSList<T>::operator[](LPCTSTR key)
{
	_VsTItem *item;
	if (item=FindItem(key))
		return item->x;
	if (m_numItems < m_maxNumItems) {
		// Add item with this key
		item = &m_list[m_numItems];
		m_numItems++;
		item->key=key;
		return item->x;		
	}
	return m_nullItem;
}

#ifdef  UNICODE                     // r_winnt
template <class T>
T& CVSList<T>::operator[](LPCSTR key)
{
	_VsTItem *item;
	WCHAR wKey[80];
	swprintf(wKey,L"%S",key);
	if (item=FindItem(wKey))
		return item->x;
	if (m_numItems < m_maxNumItems) {
		// Add item with this key
		item = &m_list[m_numItems];
		m_numItems++;
		item->key=wKey;
		return item->x;		
	}
	return m_nullItem;
}

#endif

template <class T>
BOOL CVSList<T>::RemoveItem(LPCTSTR key)
{
	DWORD i;
	if (!m_list)
		return FALSE;
	for (i=0; i < m_numItems; i++) {
		if (m_list[i].key == key)
			break;
	}
	if (i < m_numItems) {
		m_numItems--;
		for ( ; i < m_numItems; i++)
			m_list[i] = m_list[i+1];
		return TRUE;
	}
	return FALSE;
}


template <class T>
void CVSList<T>::ClearList(void)
{
	m_numItems = 0;
}


template <class T>
DWORD CVSList<T>::NumElements(void)
{
	return m_numItems;
}


















#endif // !defined(AFX_VNVARLST_H__3F0938B6_7F3A_11D4_B13F_00105A0F576C__INCLUDED_)
