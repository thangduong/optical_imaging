/******************************************************************************
 *
 * MODULE
 *     IMemory.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/IMemory.h $
 *     $Revision: 1.1 $
 *     $Modtime: 12/02/03 3:28p $
 *
 * ABSTRACT
 *     IFC shared memory management functions
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2003, Coreco Imaging, Inc.  All rights reserved.
 ******************************************************************************/
// IMemory.h: interface for the CIMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMEMORY_H__DF2AA028_8970_11D4_B146_00105A0F576C__INCLUDED_)
#define AFX_IMEMORY_H__DF2AA028_8970_11D4_B146_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Iobject.h>
#include <IFCOS.h>


typedef struct _imempacket 
{
    unsigned int packet_size;     /* number of bytes        */
    struct _imempacket  *pNext;  

} IMEMPACKET;

#if defined __cplusplus && !defined NOIFCLINK

#if defined _CRTDBG_MAP_ALLOC && defined malloc

#undef   malloc
#undef   calloc
#undef   realloc
#undef   free
#define _imem_redo_map_alloc_

#endif  /* _CRTDBG_MAP_ALLOC */


class IFC_EXT_API CIMemory : public CIobject  
{
public:
	// Create a memory management object
	//	memorySize - Size of Pool of memory to be managed
	//	LocalPoolBaseOffset - Local address space base address of the memory pool
	//  MemSpaceName - Unique name by which processes share the pool
	//     if NULL then only one process uses the pool and LocalAddr need not be called to
	//		convert a returned value to an address, if non-NULL
	//		then LocalAddr must be called on the return of malloc, realloc, calloc to convert to local addresses
	//		Note what is passed into free,realloc must be the orginal value returned by malloc, realloc, or calloc
	//		
	//		Return of malloc, realloc, calloc is an offset which can be placed in a mem pool location, then retrived by another
	//		process and mapped to its address space with a call to LocalAddr
	CIMemory(int memorySize,BYTE *LocalPoolBaseOffset, char *MemSpaceName=NULL);
	virtual ~CIMemory();


	DWORD malloc(size_t size);
	DWORD calloc(size_t num, size_t size);
	DWORD realloc(DWORD packet, size_t size);
	void free(DWORD packet);
	DWORD memalign(size_t alignment, size_t size);

	void *LocalAddr(DWORD p);


private:
	void minsert(IMEMPACKET *ptr);
	void mremove(IMEMPACKET *ptr);
	void *InternalMalloc(size_t size);
	void InternalFree(void *packet);
	void *InternalRealloc(void *packet, size_t size);
	void *InternalMemAlign(size_t alignment, size_t size);

	void Enter(void);
	void Leave(void);

	void memmap();

	OSHANDLE		m_Mutex;
	// Size of the heap area
	int m_memorySize;

	DWORD *m_PoolBaseOffset;
	DWORD m_beginOffset;
	BOOL m_SingleUser;

	IMEMPACKET *m_sysFree;

};

#ifdef _imem_redo_map_alloc_

#define   malloc(s)         _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)      _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)     _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   free(p)           _free_dbg(p, _NORMAL_BLOCK)

#endif  /* _imem_redo_map_alloc_ */


#endif

#endif // !defined(AFX_IMEMORY_H__DF2AA028_8970_11D4_B146_00105A0F576C__INCLUDED_)
