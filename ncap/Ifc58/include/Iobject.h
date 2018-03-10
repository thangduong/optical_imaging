/******************************************************************************
 *
 * MODULE   
 *		Iobject.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Iobject.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/29/04 5:09p $
 *
 * ABSTRACT  
 *		IFC interface of the CIobject class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IOBJECT_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_IOBJECT_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>

struct CIRuntimeClass;          // object type information


typedef const char *LPCSTR;
typedef unsigned int UINT;

#if defined __cplusplus && !defined NOIFCLINK

// auto_ptr-esque template for arrays of items too big for the stack
template <class T> class ScopedObj {
public:
	ScopedObj();
	void MakeD(int i);
	~ScopedObj();
   T *d;
};


template <class T>
ScopedObj<T>::ScopedObj() {
    d=NULL;
};

template <class T>
void ScopedObj<T>::MakeD(int i) {
    d=new T[i];
};

template <class T>
ScopedObj<T>::~ScopedObj() {
	if (d)
		delete d;
};

#define SCOPEOBJ(typ,numEles,var)\
		ScopedObj<typ> __scopeobj##var;\
		__scopeobj##var.MakeD(numEles);\
		typ *var= __scopeobj##var.d




class IFC_EXT_API CIobject;

struct CIRuntimeClass
{
// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CIobject* (IFCAPI* m_pfnCreateObject)(); // NULL => abstract class
	CIRuntimeClass* m_pBaseClass;

// Operations
	CIobject* CreateObject();
	BOOL IsDerivedFrom(const CIRuntimeClass* pBaseClass) const;

// Implementation

	// CIRuntimeClass objects linked together in simple list
	CIRuntimeClass* m_pNextClass;       // linked list of registered classes
};

/////////////////////////////////////////////////////////////////////////////
// class CIobject is the root of all compliant objects


class IFC_EXT_API CIobject
{
public:

// Object model (types, destruction, allocation)
	virtual CIRuntimeClass* GetRuntimeClass() const;
	virtual ~CIobject();  // virtual destructors are necessary

#ifdef new
#define _IFC_SAVE_NEW_
#undef new
#endif
	void* IFCAPI operator new(size_t nSize);
	void* IFCAPI operator new(size_t nSize,void* p);
	void  IFCAPI operator delete(void* p);
#if _MSC_VER >= 1200
	void IFCAPI operator delete(void* p, void* pPlace);
#endif

	// for file name/line number tracking using DEBUG_NEW
	void* IFCAPI operator new(size_t nSize, LPCSTR lpszFileName, int nLine);

#if _MSC_VER >= 1200
	void IFCAPI operator delete(void* p, LPCSTR lpszFileName, int nLine);
#endif

#if defined(_IFC_SAVE_NEW_) && defined(_DEBUG) && defined(DEBUG_NEW)
#define new DEBUG_NEW
#endif
#ifdef _IFC_SAVE_NEW_
#undef _IFC_SAVE_NEW_
#endif


	// Disable the copy constructor and assignment by default so you will get
	//   compiler errors instead of unexpected behaviour if you pass objects
	//   by value or assign objects.
protected:
	CIobject();
private:
	CIobject(const CIobject& objectSrc);              // no implementation
	void operator=(const CIobject& objectSrc);       // no implementation

// Attributes
public:
	BOOL IsKindOf(const CIRuntimeClass* pClass) const;



// Implementation
public:
	static const  CIRuntimeClass classCIobject;
};
#endif


// Helper macros
#define IFC_RUNTIME_CLASS(class_name) ((CIRuntimeClass*)(&class_name::class##class_name))



//////////////////////////////////////////////////////////////////////////////
// Helper macros for declaring CIRuntimeClass compatible classes

#define IFC_DECLARE_DYNAMIC(class_name) \
public: \
	static const  CIRuntimeClass class##class_name; \
	virtual CIRuntimeClass* GetRuntimeClass() const; \



// not serializable, but dynamically constructable
#define IFC_DECLARE_DYNCREATE(class_name) \
	IFC_DECLARE_DYNAMIC(class_name) \
	static CIobject* IFCAPI CreateObject();




#define IFC_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const  CIRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			IFC_RUNTIME_CLASS(base_class_name), NULL }; \
	CIRuntimeClass* class_name::GetRuntimeClass() const \
		{ return IFC_RUNTIME_CLASS(class_name); } \



#define IFC_IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CIobject* IFCAPI class_name::CreateObject() \
		{ return new class_name; } \
	IFC_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)



#define IFC_IMPLEMENT_RUNTIMECLASS_BRT(class_name, base_class_rt, wSchema, pfnNew) \
	const  CIRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			(CIRuntimeClass*)base_class_rt, NULL }; \
	CIRuntimeClass* class_name::GetRuntimeClass() const \
		{ return IFC_RUNTIME_CLASS(class_name); } \


#define IFC_IMPLEMENT_DYNCREATE_BRT(class_name, base_class_rt) \
	CIobject* IFCAPI class_name::CreateObject() \
		{ return new class_name; } \
	IFC_IMPLEMENT_RUNTIMECLASS_BRT(class_name, base_class_rt, 0xFFFF, \
		class_name::CreateObject)






#endif // !defined(AFX_IOBJECT_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
