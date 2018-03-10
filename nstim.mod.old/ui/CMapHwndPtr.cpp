// CMapHwndPtr.cpp: implementation of the CMapHwndPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "CMapHwndPtr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapHwndPtr::CMapHwndPtr()
{

}

CMapHwndPtr::~CMapHwndPtr()
{

}

void* CMapHwndPtr::Map(HWND hwnd)
{
	POSITION Pos = m_NodeList.GetHeadPosition();
	while (Pos)
	{
		POSITION OldPos = Pos;
		if (m_NodeList.GetNext(Pos).hwnd == hwnd)
		{
			return m_NodeList.GetAt(OldPos).ptr;
		}
	}
	return NULL;
}

void CMapHwndPtr::AddPair(HWND hwnd, void* ptr)
{
	Node temp;
	temp.hwnd = hwnd;
	temp.ptr = ptr;
	m_NodeList.AddTail(temp);
}

void CMapHwndPtr::Remove(HWND hwnd)
{
	POSITION Pos = m_NodeList.GetHeadPosition();
	while (Pos)
	{
		POSITION OldPos = Pos;
		if (m_NodeList.GetNext(Pos).hwnd == hwnd)
		{
			m_NodeList.RemoveAt(OldPos);
			break;
		}
	}
}

/*
void CMapHwndPtr::Remove(void* ptr)
{
	POSITION Pos = m_NodeList.GetHeadPosition();
	while (Pos)
	{
		POSITION OldPos = Pos;
		if (m_NodeList.GetNext(Pos).ptr == ptr)
		{
			m_NodeList.RemoveAt(OldPos);
			break;
		}
	}
}
*/

