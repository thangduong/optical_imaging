/******************************************************************************
 *
 * MODULE   
 *		Iobject.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/VnObject.h $
 *		$Revision: 1.1 $
 *		$Modtime: 3/16/01 9:53a $
 *
 * ABSTRACT  
 *		IFC interface of the CVnObject class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_VnObject_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_VnObject_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <VnVar.h>
#include <vidsrct.h>



struct CVsRuntimeClass;          // object type information


typedef const char *LPCSTR;
typedef unsigned int UINT;

#ifdef __cplusplus

// auto_ptr-esque template for arrays of items too big for the stack
template <class T> class VScopedObj {
public:
	VScopedObj();
	MakeD(int i);
	~VScopedObj();
   T *d;
};


template <class T>
VScopedObj<T>::VScopedObj() {
    d=NULL;
};

template <class T>
VScopedObj<T>::MakeD(int i) {
    d=new T[i];
};

template <class T>
VScopedObj<T>::~VScopedObj() {
	if (d)
		delete d;
};

#define VSCOPEOBJ(typ,numEles,var)\
		VScopedObj<typ> __scopeobj##var;\
		__scopeobj##var.MakeD(numEles);\
		typ *var= __scopeobj##var.d




class IVSV_EXT_API CVnObject;

struct CVsRuntimeClass
{
// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CVnObject* (IVSAPI* m_pfnCreateObject)(); // NULL => abstract class
	CVsRuntimeClass* m_pBaseClass;

// Operations
	CVnObject* CreateObject();
	BOOL IsDerivedFrom(const CVsRuntimeClass* pBaseClass) const;

// Implementation

	// CVsRuntimeClass objects linked together in simple list
	CVsRuntimeClass* m_pNextClass;       // linked list of registered classes
};

/////////////////////////////////////////////////////////////////////////////
// class CVnObject is the root of all compliant objects


class IVSV_EXT_API CVnObject
{
public:

// Object model (types, destruction, allocation)
	virtual CVsRuntimeClass* GetRuntimeClass() const;
	virtual ~CVnObject();  // virtual destructors are necessary

#ifdef new
#define _VS_SAVE_NEW_
#undef new
#endif
	void* IVSAPI operator new(size_t nSize);
	void* IVSAPI operator new(size_t nSize,void* p);
	void  IVSAPI operator delete(void* p);
#if _MSC_VER >= 1200
	void IVSAPI operator delete(void* p, void* pPlace);
#endif

	// for file name/line number tracking using DEBUG_NEW
	void* IVSAPI operator new(size_t nSize, LPCSTR lpszFileName, int nLine);

#if _MSC_VER >= 1200
	void IVSAPI operator delete(void* p, LPCSTR lpszFileName, int nLine);
#endif

#if defined(_VS_SAVE_NEW_) && defined(_DEBUG) && defined(DEBUG_NEW)
#define new DEBUG_NEW
#endif
#ifdef _VS_SAVE_NEW_
#undef _VS_SAVE_NEW_
#endif


	// Disable the copy constructor and assignment by default so you will get
	//   compiler errors instead of unexpected behaviour if you pass objects
	//   by value or assign objects.
protected:
	CVnObject();
private:
	CVnObject(const CVnObject& objectSrc);              // no implementation
	void operator=(const CVnObject& objectSrc);       // no implementation

// Attributes
public:
	BOOL IsKindOf(const CVsRuntimeClass* pClass) const;



// Implementation
public:
	static const  CVsRuntimeClass classCVnObject;
};
#endif


// Helper macros
#define VS_RUNTIME_CLASS(class_name) ((CVsRuntimeClass*)(&class_name::class##class_name))



//////////////////////////////////////////////////////////////////////////////
// Helper macros for declaring CVsRuntimeClass compatible classes

#define VS_DECLARE_DYNAMIC(class_name) \
public: \
	static const  CVsRuntimeClass class##class_name; \
	virtual CVsRuntimeClass* GetRuntimeClass() const; \



// not serializable, but dynamically constructable
#define VS_DECLARE_DYNCREATE(class_name) \
	VS_DECLARE_DYNAMIC(class_name) \
	static CVnObject* IVSAPI CreateObject();




#define VS_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	const  CVsRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			VS_RUNTIME_CLASS(base_class_name), NULL }; \
	CVsRuntimeClass* class_name::GetRuntimeClass() const \
		{ return VS_RUNTIME_CLASS(class_name); } \



#define VS_IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CVnObject* IVSAPI class_name::CreateObject() \
		{ return new class_name; } \
	VS_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)






#endif // !defined(AFX_IOBJECT_H__962D5A82_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
