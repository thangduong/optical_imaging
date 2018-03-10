// VnVar.h: interface for the CVnVar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VNVAR_H__6BB208F6_72D8_11D4_B132_00105A0F576C__INCLUDED_)
#define AFX_VNVAR_H__6BB208F6_72D8_11D4_B132_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#ifdef __midl 
import "oaidl.idl";

#else
#include <oaidl.h>
#include <tchar.h>

#endif

#define MAX_VSSTR_CHARS 80

typedef  CHAR VSSTR[MAX_VSSTR_CHARS]; 

typedef struct  U_VNVARIANT {
	LONG          lVal;         /* VT_I4                */
	DOUBLE        dblVal;       /* VT_R8                */
	VSSTR		  strVal;		/* VT_LPSTR				*/
} U_VNVARIANT;


typedef struct VNVARIANT {
	int vt;
	U_VNVARIANT u;
} VNVARIANT;




typedef VNVARIANT * LPVNVARIANT;



typedef struct SVSSTR {
	VSSTR s;
} SVSSTR;


//#include <vidsrct.h>



#define VS_UNION(X, Y)   ((X)->u.Y)
#define VS_UI1(X)         VS_UNION(X, bVal)
#define VS_I2(X)          VS_UNION(X, iVal)
#define VS_I4(X)          VS_UNION(X, lVal)
#define VS_R4(X)          VS_UNION(X, fltVal)
#define VS_R8(X)          VS_UNION(X, dblVal)
#define VS_I1(X)          VS_UNION(X, cVal)
#define VS_UI2(X)         VS_UNION(X, uiVal)
#define VS_UI4(X)         VS_UNION(X, ulVal)
#define VS_INT(X)         VS_UNION(X, intVal)
#define VS_UINT(X)        VS_UNION(X, uintVal)


#ifdef __midl 

#define MIDL_STRING [string]
typedef BYTE CHAR;

#else

#define MIDL_STRING 

#endif


#if defined(__midl) || !defined(__cplusplus)

//typedef BYTE CVSStr[MAX_VSSTR_CHARS];
typedef SVSSTR CVSStr;
typedef VNVARIANT CVnVar;


#define IVSV_EXT_API

#else


#ifdef IVS_IMPORT_ONLY
#define IVSV_EXT_API  __declspec(dllimport)
#else
#define IVSV_EXT_API  __declspec(dllexport)
#endif

class IVSV_EXT_API CVSStr : public ::SVSSTR
{
public:
	CVSStr();
	~CVSStr();

	CVSStr(TCHAR *str);
	CVSStr(const CVSStr& Src);

	operator TCHAR*() const;			// Extracts a char* 

	CVSStr& operator=(const TCHAR* pSrc);			// Assign a VT_LPSTR
#ifdef  UNICODE                     // r_winnt
	CVSStr& operator=(const char* pSrc);		
#endif

	bool operator==(const CVSStr& varSrc) const;
	bool operator==(const TCHAR* pSrc) const;

	bool operator!=(const CVSStr& varSrc) const;
	bool operator!=(const TCHAR* pSrc) const;


};


// Default constructor
//
inline CVSStr::CVSStr()
{
	s[0]=0;
}

inline CVSStr::~CVSStr()
{

}

// Construct a CVnVar from a const VNVARIANT&
//
inline CVSStr::CVSStr(const CVSStr& Src) 
{
	_tcscpy((TCHAR*)s,(TCHAR*)Src.s);
}


inline CVSStr::operator TCHAR *() const 
{
	return (TCHAR*)s;
}


inline CVSStr& CVSStr::operator=(const TCHAR* pSrc) 
{
	if (pSrc && _tcsclen(pSrc) < (MAX_VSSTR_CHARS-1) ) {
		_tcscpy((TCHAR*)s,pSrc);
	}

	return *this;
}

#ifdef  UNICODE                     // r_winnt

inline CVSStr& CVSStr::operator=(const char* pSrc) 
{
	if (pSrc && strlen(pSrc) < (MAX_VSSTR_CHARS-1) ) {
		swprintf((TCHAR*)s,L"%S",pSrc);
	}
	return *this;
}
#endif

inline bool CVSStr::operator==(const CVSStr& varSrc) const
{
	return (_tcscmp((TCHAR*)s,(TCHAR*)varSrc.s) == 0);
}

inline bool CVSStr::operator==(const TCHAR* pSrc) const
{
	return (_tcscmp((TCHAR*)s,pSrc) == 0);
}


inline bool CVSStr::operator!=(const CVSStr& varSrc) const
{
	return (_tcscmp((TCHAR*)s,(TCHAR*)varSrc.s) != 0);
}

inline bool CVSStr::operator!=(const TCHAR* pSrc) const
{
	return (_tcscmp((TCHAR*)s,pSrc) != 0);
}




class IVSV_EXT_API CVnVar  : public ::VNVARIANT
{
public:
	CVnVar();

	CVnVar(const VNVARIANT& varSrc);
	CVnVar(const VNVARIANT* pSrc);
	CVnVar(const CVnVar& varSrc);

	CVnVar(VNVARIANT& varSrc, bool fCopy);			// Attach VNVARIANT if !fCopy

	CVnVar(long lSrc, VARTYPE vtSrc = VT_I4);		// Creates a VT_I4
	CVnVar(double dblSrc, VARTYPE vtSrc = VT_R8);	// Creates a VT_R8
	CVnVar(const TCHAR* pSrc);						// Creates a VT_LPSTR
	CVnVar(bool bSrc) throw();										// Creates a VT_BOOL
	CVnVar(BYTE bSrc) throw();										// Creates a VT_UI1

	// Destructor
	//
	~CVnVar();

	// Extractors
	//
	operator long() const;			// Extracts a long from a VT_I4
	operator float() const;			// Extracts a float from a VT_R4
	operator double() const;			// Extracts a double from a VT_R8
	operator bool() const;			// Extracts a bool from a VT_BOOL
	operator TCHAR*() const;			// Extracts a char* from a VT_LPSTR
	operator BYTE() const;			// Extracts a BTYE (unsigned char) from a VT_UI1
	
	// Assignment operations
	//
	CVnVar& operator=(const VNVARIANT& varSrc);
	CVnVar& operator=(const VNVARIANT* pSrc);
	CVnVar& operator=(const CVnVar& varSrc);

//	CVnVar& operator=(short sSrc);				// Assign a VT_I2, or a VT_BOOL
//	CVnVar& operator=(long lSrc);					// Assign a VT_I4
//	CVnVar& operator=(float fltSrc);				// Assign a VT_R4
	CVnVar& operator=(double dblSrc);				// Assign a VT_R8
	CVnVar& operator=(const TCHAR* pSrc);			// Assign a VT_LPSTR
// 	CVnVar& operator=(bool bSrc);					// Assign a VT_BOOL
//	CVnVar& operator=(BYTE bSrc);					// Assign a VT_UI1

	// Comparison operations
	//
	bool operator==(const VNVARIANT& varSrc) const;
	bool operator==(const VNVARIANT* pSrc) const;

	bool operator!=(const VNVARIANT& varSrc) const;
	bool operator!=(const VNVARIANT* pSrc) const;

	void ChangeType(VARTYPE vartype, const CVnVar* pSrc = NULL);
	void Clear();

	void Attach(VNVARIANT& varSrc);
	VNVARIANT Detach();

};

inline InitVnVariant( CVnVar *o)
{
	memset(o,0,sizeof(CVnVar));
	o->vt= VT_LPSTR;
}

inline void VnVariantCopy( VNVARIANT *dst,VNVARIANT *src) 
{
	memcpy(dst,src,sizeof(VNVARIANT));
}

inline void VnVariantError(DWORD error)
{
	::MessageBox(NULL,TEXT("VnVariantError"),TEXT("VnVariantError"),MB_OK);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Constructors
//
//////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
//
inline CVnVar::CVnVar() throw()
{
	InitVnVariant(this);
}

// Construct a CVnVar from a const VNVARIANT&
//
inline CVnVar::CVnVar(const VNVARIANT& varSrc) 
{
	InitVnVariant(this);
	VnVariantCopy(this, const_cast<VNVARIANT*>(&varSrc));
}

// Construct a CVnVar from a const VNVARIANT*
//
inline CVnVar::CVnVar(const VNVARIANT* pSrc) 
{
	InitVnVariant(this);
	VnVariantCopy(this, const_cast<VNVARIANT*>(pSrc));
}

// Construct a CVnVar from a const CVnVar&
//
inline CVnVar::CVnVar(const CVnVar& varSrc) 
{
	InitVnVariant(this);
	VnVariantCopy(this, const_cast<VNVARIANT*>(static_cast<const VNVARIANT*>(&varSrc)));
}

// Construct a CVnVar from a VNVARIANT&.  If fCopy is FALSE, give control of
// data to the CVnVar without doing a VariantCopy.
//
inline CVnVar::CVnVar(VNVARIANT& varSrc, bool fCopy) 
{
	if (fCopy) {
		InitVnVariant(this);
		VnVariantCopy(this, &varSrc);
	} else {
		memcpy(this, &varSrc, sizeof(varSrc));
		V_VT(&varSrc) = VT_EMPTY;
	}
}


// Construct either a VT_I4 VNVARIANT, a VT_BOOL VNVARIANT, or a
// VT_ERROR VNVARIANT from a long (the default is VT_I4)
//
inline CVnVar::CVnVar(long lSrc, VARTYPE vtSrc) 
{
	if (vtSrc != VT_I4) {
		VnVariantError(E_INVALIDARG);
	}

	V_VT(this) = VT_I4;
	VS_I4(this) = lSrc;
}


// Construct either a VT_R8 VNVARIANT, or a VT_DATE VNVARIANT from
// a double (the default is VT_R8)
//
inline CVnVar::CVnVar(double dblSrc, VARTYPE vtSrc) 
{
	if ((vtSrc != VT_R8) && (vtSrc != VT_DATE)) {
		VnVariantError(E_INVALIDARG);
	}

		V_VT(this) = VT_R8;
		VS_R8(this) = dblSrc;
}



// Construct a VT_LPSTR VNVARIANT from a const TCHAR*
//
inline CVnVar::CVnVar(const TCHAR* pSrc) 
{
	V_VT(this) = VT_LPSTR;


	if (pSrc && _tcsclen(pSrc) > (MAX_VSSTR_CHARS-1) ) {
		VnVariantError(E_OUTOFMEMORY);
	}
	else
		_tcscpy((TCHAR*)u.strVal,pSrc);
}







inline CVnVar::~CVnVar()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Extractors
//
//////////////////////////////////////////////////////////////////////////////////////////


// Extracts a VT_I4 into a long
//
inline CVnVar::operator long() const 
{
	if (V_VT(this) == VT_I4) {
		return VS_I4(this); 
	}

	CVnVar varDest;

	varDest.ChangeType(VT_I4, this);

	return VS_I4(&varDest);
}


// Extracts a VT_R8 into a double
//
inline CVnVar::operator double() const 
{
	if (V_VT(this) == VT_R8) {
		return VS_R8(this); 
	}

	CVnVar varDest;

	varDest.ChangeType(VT_R8, this);

	return VS_R8(&varDest);
}








inline CVnVar::operator TCHAR *() const 
{
	if (V_VT(this) == VT_LPSTR) {
		return (TCHAR*)u.strVal;
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// Assignment operations
//
//////////////////////////////////////////////////////////////////////////////////////////

// Assign a const VNVARIANT& (::VariantCopy handles everything)
//
inline CVnVar& CVnVar::operator=(const VNVARIANT& varSrc) 
{
	VnVariantCopy(this, const_cast<VNVARIANT*>(&varSrc));

	return *this;
}

// Assign a const VNVARIANT* (::VariantCopy handles everything)
//
inline CVnVar& CVnVar::operator=(const VNVARIANT* pSrc) 
{
	VnVariantCopy(this, const_cast<VNVARIANT*>(pSrc));

	return *this;
}

// Assign a const CVnVar& (::VariantCopy handles everything)
//
inline CVnVar& CVnVar::operator=(const CVnVar& varSrc) 
{
	VnVariantCopy(this, const_cast<VNVARIANT*>(static_cast<const VNVARIANT*>(&varSrc)));

	return *this;
}

// Assign a short creating either VT_I2 VNVARIANT or a 
// VT_BOOL VNVARIANT (VT_I2 is the default)
//

/*
inline CVnVar& CVnVar::operator=(short sSrc) 
{
	if (V_VT(this) == VT_I2) {
		VS_I2(this) = sSrc;
	}
	else {
		// Clear the VNVARIANT and create a VT_I2
		//

		V_VT(this) = VT_I2;
		VS_I2(this) = sSrc;
	}

	return *this;
}
*/

// Assign a long creating either VT_I4 VNVARIANT, a VT_ERROR VNVARIANT
// or a VT_BOOL VNVARIANT (VT_I4 is the default)
//

/*
inline CVnVar& CVnVar::operator=(long lSrc) 
{
	if (V_VT(this) == VT_I4) {
		VS_I4(this) = lSrc;
	}
	else {
		// Clear the VNVARIANT and create a VT_I4
		//
		Clear();

		V_VT(this) = VT_I4;
		VS_I4(this) = lSrc;
	}

	return *this;
}
*/

// Assign a float creating a VT_R4 VNVARIANT 
//

/*
inline CVnVar& CVnVar::operator=(float fltSrc) 
{
	if (V_VT(this) != VT_R4) {
		// Clear the VNVARIANT and create a VT_R4
		//
		Clear();

		V_VT(this) = VT_R4;
	}

	VS_R4(this) = fltSrc;

	return *this;
}
*/

// Assign a double creating either a VT_R8 VNVARIANT, or a VT_DATE
// VNVARIANT (VT_R8 is the default)
//
inline CVnVar& CVnVar::operator=(double dblSrc) 
{
	if (V_VT(this) == VT_R8) {
		VS_R8(this) = dblSrc;
	}
	else {
		// Clear the VNVARIANT and create a VT_R8
		//
		Clear();

		V_VT(this) = VT_R8;
		VS_R8(this) = dblSrc;
	}

	return *this;
}



// Assign a const char* creating a VT_LPSTR VNVARIANT
//
inline CVnVar& CVnVar::operator=(const TCHAR* pSrc) 
{
	// Clear the VNVARIANT (This will SysFreeString() any previous occupant)
	//
	Clear();

	V_VT(this) = VT_LPSTR;


	if (pSrc && _tcsclen(pSrc) > (MAX_VSSTR_CHARS-1) ) {
		VnVariantError(E_OUTOFMEMORY);
	}
	else {
		if (!pSrc)
			u.strVal[0]=0;
		else
			_tcscpy((TCHAR*)u.strVal,pSrc);
	}

	return *this;
}


// Assign a bool creating a VT_BOOL VNVARIANT 
//

/*
inline CVnVar& CVnVar::operator=(bool bSrc) 
{
	if (V_VT(this) == VT_I4) {
		VS_I4(this) = bSrc ? 1:0;
	}
	else {
		// Clear the VNVARIANT and create a VT_I4
		//
		Clear();

		V_VT(this) = VT_I4;
		VS_I4(this) = bSrc ? 1:0;
	}

	return *this;
}
*/



// Assign a BTYE (unsigned char) creating a VT_UI1 VNVARIANT
//

/*
inline CVnVar& CVnVar::operator=(BYTE bSrc) 
{
	if (V_VT(this) != VT_UI1) {
		// Clear the VNVARIANT and create a VT_UI1
		//
		Clear();

		V_VT(this) = VT_UI1;
	}

	VS_UI1(this) = bSrc;

	return *this;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////
//
// Comparison operations
//
//////////////////////////////////////////////////////////////////////////////////////////

// Compare a CVnVar against a const VNVARIANT& for equality
//
inline bool CVnVar::operator==(const VNVARIANT& varSrc) const throw()
{
	return *this == &varSrc;
}

// Compare a CVnVar against a const VNVARIANT* for equality
//
inline bool CVnVar::operator==(const VNVARIANT* pSrc) const throw()
{
	if (this == pSrc) {
		return true;
	}

	//
	// Variants not equal if types don't match
	//
	if (V_VT(this) != V_VT(pSrc)) {
		return false;
	}

	//
	// Check type specific values
	//
	switch (V_VT(this)) {
		case VT_EMPTY:
		case VT_NULL:
			return true;


		case VT_I4:
			return VS_I4(this) == VS_I4(pSrc);


		case VT_R8:
			return VS_R8(this) == VS_R8(pSrc);




		default:
			VnVariantError(E_INVALIDARG);
			// fall through
	}

	return false;
}

// Compare a CVnVar against a const VNVARIANT& for in-equality
//
inline bool CVnVar::operator!=(const VNVARIANT& varSrc) const throw()
{
	return !(*this == &varSrc);
}

// Compare a CVnVar against a const VNVARIANT* for in-equality
//
inline bool CVnVar::operator!=(const VNVARIANT* pSrc) const throw()
{
	return !(*this == pSrc);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Low-level operations
//
//////////////////////////////////////////////////////////////////////////////////////////

// Clear the CVnVar
//
inline void CVnVar::Clear() 
{
	InitVnVariant(this);
}





inline void CVnVar::Attach(VNVARIANT& varSrc) 
{
	//
	// Free up previous VNVARIANT
	//
	Clear();

	//
	// Give control of data to CVnVar
	//
	memcpy(this, &varSrc, sizeof(varSrc));
	V_VT(&varSrc) = VT_EMPTY;
}

inline VNVARIANT CVnVar::Detach() 
{
	VNVARIANT varResult = *this;
	V_VT(this) = VT_EMPTY;

	return varResult;
}






#endif


#endif // !defined(AFX_VNVAR_H__6BB208F6_72D8_11D4_B132_00105A0F576C__INCLUDED_)
