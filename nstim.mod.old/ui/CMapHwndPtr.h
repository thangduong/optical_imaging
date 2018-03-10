#ifndef CMAPHWNDPTR_H
#define CMAPHWNDPTR_H

#include <windows.h>
#include "CList.h"

class CMapHwndPtr  
{
private:
	struct Node
	{
		HWND hwnd;
		void* ptr;
	};

	// slow implementation.  redo with hash table.
	// this, however, should suffice for a small table.
	// it shouldn't be a problem to redo though.
	CList<Node, const Node&> m_NodeList;
public:
	CMapHwndPtr();
	virtual ~CMapHwndPtr();

	void* Map(HWND hwnd);
	void AddPair(HWND hwnd, void* ptr);
	void Remove(HWND hwnd);
//	void Remove(void* ptr);
};

#endif
