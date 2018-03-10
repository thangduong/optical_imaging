/*//////////////////////////////////////////////////////////////////////////////

///////////////////////////////REVISION HISTORY/////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

4/12/2001
Thang Duong
		Added this revision history

5/26/2001
Thang Duong
		Added ~CList() because if that's not there, then there's a memory leak
			because if list has a lot of elements and it goes out of scope
			then the nodes get dangly.

4/1/2002
Thang Duong
		Added #ifndef _MSC_VER (if using MFC, then don't use this)
//////////////////////////////////////////////////////////////////////////////*/
/*
CList.h
	final CList template.
10/01/2000
*/

#ifndef CLIST_H
#define CLIST_H

// if we're using MFC, then don't define this class
#ifndef _MFC_VER

#ifdef _DEBUG
#include <iostream.h>
#include <assert.h>
#ifndef ASSERT
#define	ASSERT(x)	assert(x)
#endif
#else
#ifndef ASSERT
#define	ASSERT(x)
#endif
#endif

#ifndef NULL
#define	NULL		0
#endif

#ifndef POSITION
#define	POSITION	void*

#endif

template <class TYPE, class ARG_TYPE>
class CListNode
{
	TYPE m_Data;
	CListNode<TYPE, ARG_TYPE>* m_pNext;
	CListNode<TYPE, ARG_TYPE>* m_pPrev;
public:
	CListNode(ARG_TYPE Data)
	{
		m_Data = Data;
		m_pNext = m_pPrev = NULL;
	}
	~CListNode()
	{
		// unlink on delete
		Unlink();
	}
	inline void Unlink()
	{
		if (m_pNext)
			m_pNext->m_pPrev = m_pPrev;
		if (m_pPrev)
			m_pPrev->m_pNext = m_pNext;
	}
	inline void LinkBefore(CListNode<TYPE, ARG_TYPE>* pAfter)
	{
		// link this before pAfter
		// so when done, this->m_pNext == pAfter holds
		Unlink();
		if (pAfter)
		{
			m_pNext = pAfter;
			m_pPrev = pAfter->m_pPrev;
			if (pAfter->m_pPrev)
				pAfter->m_pPrev->m_pNext = this;
			pAfter->m_pPrev = this;
		}
	}
	inline void LinkAfter(CListNode<TYPE, ARG_TYPE>* pBefore)
	{
		// link this after pBefore
		// so when done, this->m_pPrev == pBefore holds
		if (pBefore)
		{
			m_pPrev = pBefore;
			m_pNext = pBefore->m_pNext;
			if (pBefore->m_pNext)
				pBefore->m_pNext->m_pPrev = this;
			pBefore->m_pNext = this;
		}
	}
	inline CListNode<TYPE, ARG_TYPE>* GetNext() const
	{
		return m_pNext;
	}
	inline CListNode<TYPE, ARG_TYPE>* GetPrev()
	{
		return m_pPrev;
	}
	inline TYPE GetData() const
	{
		return m_Data;
	}
	inline TYPE& GetData()
	{
		return m_Data;
	}
	inline void SetData(ARG_TYPE newData)
	{
		m_Data = newData;
	}
};

template <class TYPE, class ARG_TYPE>
class CList
{
	CListNode<TYPE, ARG_TYPE>* m_pHead;
	CListNode<TYPE, ARG_TYPE>* m_pTail;
public:
	CList(int iBlockSize = 0)
	{
	// no blocksize support yet
		m_pHead = m_pTail = NULL;
	}
	virtual ~CList(void)
	{
		RemoveAll();
	}
	POSITION GetHeadPosition()
	{
		return m_pHead;
	}
	POSITION GetTailPosition()
	{
		return m_pTail;
	}
	TYPE GetHead() const
	{
		ASSERT(m_pHead != NULL);
		return m_pHead->GetData();
	}
	TYPE& GetHead()
	{
		ASSERT(m_pHead != NULL);
		return m_pHead->GetData();
	}
	TYPE& GetTail()
	{
		ASSERT(m_pTail != NULL);
		return m_pTail->GetData();
	}
	TYPE GetTail() const
	{
		ASSERT(m_pTail != NULL);
		return m_pTail->GetData();
	}
	int GetCount() const
	{
		int iCount = 0;
		CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (pNode)
		{
			pNode = pNode->GetNext();
			iCount++;
		}
		return iCount;
	}	
	POSITION AddHead(ARG_TYPE newElement)
	{
		CListNode<TYPE, ARG_TYPE>* pNode = AllocNode(newElement);
		if (m_pHead == NULL)
		{
			m_pHead = pNode;
			m_pTail = pNode;
		}
		else
		{
			pNode->LinkBefore(m_pHead);
			m_pHead = pNode;			
		}
		return pNode;
	}
	TYPE& GetPrev(POSITION& rPosition)
	{
		ASSERT(rPosition != NULL);
		/*
#ifdef _TDDEBUG
	// validate rPosition
		CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (rPosition != (POSITION)pNode)
			pNode = pNode->GetNext();
		ASSERT(rPosition == (POSITION)pNode);
#endif
		*/
		TYPE& rResult = ((CListNode<TYPE, ARG_TYPE>*)rPosition)->GetData();
		rPosition = (POSITION)(((CListNode<TYPE, ARG_TYPE>*)rPosition)->GetPrev());
		return rResult;
	}
	TYPE GetPrev(POSITION& rPosition) const
	{
		return GetPrev(rPosition);
	}
	TYPE& GetNext(POSITION& rPosition)
	{
		/*
		ASSERT(rPosition != NULL);
#ifdef _TDDEBUG
	// validate rPosition
		CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (rPosition != (POSITION)pNode)
			pNode = pNode->GetNext();
		ASSERT(rPosition == (POSITION)pNode);
#endif
		*/
		TYPE& rResult = ((CListNode<TYPE, ARG_TYPE>*)rPosition)->GetData();
		rPosition = (POSITION)(((CListNode<TYPE, ARG_TYPE>*)rPosition)->GetNext());
		return rResult;
	}
	TYPE GetNext(POSITION& rPosition) const
	{
		return GetPrev(rPosition);
	}
	void AddHead(CList<TYPE, ARG_TYPE>* x)
	{
		if (newList)
		{
			POSITION Pos = newList->GetTailPosition();
			while (Pos)
				AddHead(newList->GetPrev(Pos));
		} 
	}
	POSITION AddTail(ARG_TYPE newElement)
	{
		CListNode<TYPE, ARG_TYPE>* pNode = AllocNode(newElement);
		if (m_pHead == NULL)
		{
			m_pHead = pNode;
			m_pTail = pNode;
		}
		else
		{
			pNode->LinkAfter(m_pTail);
			m_pTail = pNode;			
		}
		return pNode;
	}
	void AddTail(CList<TYPE, ARG_TYPE>* newList)
	{
		if (newList)
		{
			POSITION Pos = newList->GetHeadPosition();
			while (Pos)
				AddHead(newList->GetNext(Pos));
		} 
	}
	POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const
	{
//		ASSERT(!IsValidPosition(startAfter));

	const CListNode<TYPE, ARG_TYPE>* pNode = (const CListNode<TYPE, ARG_TYPE>*)startAfter;
		if (pNode == NULL)
			pNode = m_pHead;
		while ((pNode != NULL) && (pNode->GetData() != searchValue))
			pNode = pNode->GetNext();
		return pNode;
	}
	POSITION FindIndex(int Index) const
	{
		const CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (pNode && (Index > 0))
		{
			pNode = pNode->GetNext();
			Index--;
		}
		return (void*)pNode;
	}
	TYPE& GetAt(POSITION position)
	{
//		ASSERT(!IsValidPosition(position));
		return ((CListNode<TYPE, ARG_TYPE>*)position)->GetData();
	}
	TYPE GetAt(POSITION position) const
	{
//		ASSERT(!IsValidPosition(position));

		return ((const CListNode<TYPE, ARG_TYPE>*)position)->GetData();
	}
	POSITION InsertAfter(POSITION position, ARG_TYPE newElement)
	{
//		ASSERT(IsValidPosition(position));
		CListNode<TYPE, ARG_TYPE>* pNode = new CListNode<TYPE, ARG_TYPE>(newElement);
		pNode->LinkAfter((CListNode<TYPE, ARG_TYPE>*)position);
		if (position == (POSITION)m_pTail)
		{
			m_pTail = pNode;
		}
		return pNode;
	}
	POSITION InsertBefore(POSITION position, ARG_TYPE newElement)
	{
//		ASSERT(IsValidPosition(position));
		CListNode<TYPE, ARG_TYPE>* pNode = new CListNode<TYPE, ARG_TYPE>(newElement);
		pNode->LinkBefore((CListNode<TYPE, ARG_TYPE>*)position);
		if (position == (POSITION)m_pHead)
		{
			m_pHead = pNode;
		}
		return pNode;		
	}
	bool IsEmpty() const
	{
		return (m_pHead == m_pTail) && (m_pHead == NULL);
	}	

	void RemoveAt(POSITION position)
	{
//		ASSERT(IsValidPosition(position));
		CListNode<TYPE, ARG_TYPE>* pNode = (CListNode<TYPE, ARG_TYPE>*)position;
		if (pNode)
		{
			if (pNode == m_pHead)
				m_pHead = pNode->GetNext();
			if (pNode == m_pTail)
				m_pTail = pNode->GetPrev();

		// note pNode automatically unlinks on delete
			delete pNode;
		}
	}

	TYPE RemoveHead()
	{
		ASSERT(m_pHead != NULL);
		TYPE Head = m_pHead->GetData();
		RemoveAt(m_pHead);
		return Head;
	}

	TYPE RemoveTail()
	{
		ASSERT(m_pTail != NULL);
		TYPE Tail = m_pTail->GetData();
		RemoveAt(m_pTail);
		return Tail;
	}

	void RemoveAll()
	{
		while (!IsEmpty())
			RemoveHead();
	}

	void SetAt(POSITION position, ARG_TYPE newElement)
	{
//		ASSERT(!IsValidPosition(position));
		CListNode<TYPE, ARG_TYPE>* pNode = (CListNode<TYPE, ARG_TYPE>*)position;
		if (pNode)
		{
			pNode->SetData(newElement);
		}		
	}

/*
	bool IsValidPosition(POSITION Pos)
	{
		bool bResult = false;
		CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (!bResult & (pNode != NULL))
		{
			bResult = (Pos == (POSITION)pNode);
			pNode = pNode->GetNext();
		}
		return bResult;
	}
*/
#ifdef _TDDEBUG
	void DebugOut()
	{
		CListNode<TYPE, ARG_TYPE>* pNode = m_pHead;
		while (pNode)
		{
			printf("%d\n", pNode->GetData());
			pNode = pNode->GetNext();			
		}
	}

	// AllocNode made like this to allow for block allocation
	// debug method will be modified and 
	// made release when code is completely finalized

	CListNode<TYPE, ARG_TYPE>* AllocNode(ARG_TYPE nodeData)
	{
		return new CListNode<TYPE, ARG_TYPE>(nodeData);
	}
#else
	CListNode<TYPE, ARG_TYPE>* AllocNode(ARG_TYPE nodeData)
	{
		return new CListNode<TYPE, ARG_TYPE>(nodeData);
	}
#endif
};

#else
#include <afxtempl.h>
#endif

#endif

