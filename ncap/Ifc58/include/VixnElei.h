/******************************************************************************
 *
 * MODULE
 *     VixnEle.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/VixnElei.h $
 *     $Revision: 1.1 $
 *     $Modtime: 8/01/02 8:45a $
 *
 * ABSTRACT
 *     IFC 150/40  IFC Vixn Element declarations
 *
 *
 * TECHNICAL NOTES
 *      
 * VixnEle.h: interface for the CVixnEle class.
 *      
 *
 * Copyright (c) 1997-1999, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/

#if !defined(AFX_VIXNELE_H__A13A8D3B_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
#define AFX_VIXNELE_H__A13A8D3B_38F8_11D2_AF52_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VIXNEXP __declspec(dllexport)

class VIXNEXP CVixnEle;
#include <ifc.h>
#include <Vixni.h>


typedef enum {
	ELE_DWORD,
	ELE_VOID_PTR, /* ptr to an unknown element - operations do not dereference this type */
} ELE_BASE_TYPE;



typedef union {
	VIXNSRVRELE e;
	DWORD d;
} CDATABASE;


class VIXNEXP CVixnExcept
{
public:
	CVixnExcept(void);
	CVixnExcept(char *errmsg,...);
};


#define VIXNVAL(e) ( (e).GetBaseVal().d )

class VIXNEXP CVixnEle  
{
public:
	CVixnEle(void);
	CVixnEle(CVixnEle &x);
	CVixnEle(const DWORD InitialVal);
	CVixnEle(CVixn *server,DWORD InitialVal);

	void init(CVixn *server,DWORD InitialVal);

	CVixnEle operator+(DWORD x);
	CVixnEle operator+(CVixnEle &x);

	CVixnEle operator-(DWORD x);
	CVixnEle operator-(CVixnEle &x);

	CVixnEle operator*(DWORD x);
	CVixnEle operator*(CVixnEle &x);

	CVixnEle operator/(DWORD x);
	CVixnEle operator/(CVixnEle &x);

	CVixnEle operator&(DWORD x);
	CVixnEle operator&(CVixnEle &x);

	CVixnEle operator|(DWORD x);
	CVixnEle operator|(CVixnEle &x);

	CVixnEle operator^(DWORD x);
	CVixnEle operator^(CVixnEle &x);

	CVixnEle operator>>(DWORD x);
	CVixnEle operator>>(CVixnEle &x);

	CVixnEle operator<<(DWORD x);
	CVixnEle operator<<(CVixnEle &x);

	CVixnEle operator&&(DWORD x);
	CVixnEle operator&&(CVixnEle &x);

	CVixnEle operator||(DWORD x);
	CVixnEle operator||(CVixnEle &x);

	CVixnEle operator%(DWORD x);
	CVixnEle operator%(CVixnEle &x);

	CVixnEle operator~();

	CVixnEle operator!();

	CVixnEle operator++(void);
	CVixnEle operator++(int);

	CVixnEle operator--(void);
	CVixnEle operator--(int);


	CVixnEle operator==(DWORD x);
	CVixnEle operator==(CVixnEle &x);

	CVixnEle operator!=(DWORD x);
	CVixnEle operator!=(CVixnEle &x);

	CVixnEle operator>=(DWORD x);
	CVixnEle operator>=(CVixnEle &x);

	CVixnEle operator>(DWORD x);
	CVixnEle operator>(CVixnEle &x);

	CVixnEle operator<=(DWORD x);
	CVixnEle operator<=(CVixnEle &x);

	CVixnEle operator<(DWORD x);
	CVixnEle operator<(CVixnEle &x);

	CVixnEle& operator=(DWORD x);
	CVixnEle& operator=(CVixnEle &x);

	CVixnEle operator+=(DWORD x);
	CVixnEle operator+=(CVixnEle &x);

	CVixnEle operator-=(DWORD x);
	CVixnEle operator-=(CVixnEle &x);

	CVixnEle operator^=(DWORD x);
	CVixnEle operator^=(CVixnEle &x);

	CVixnEle operator&=(DWORD x);
	CVixnEle operator&=(CVixnEle &x);

	CVixnEle operator|=(DWORD x);
	CVixnEle operator|=(CVixnEle &x);

	CVixnEle operator<<=(DWORD x);
	CVixnEle operator<<=(CVixnEle &x);

	CVixnEle operator>>=(DWORD x);
	CVixnEle operator>>=(CVixnEle &x);

	CVixnEle operator*=(DWORD x);
	CVixnEle operator*=(CVixnEle &x);

	CVixnEle operator/=(DWORD x);
	CVixnEle operator/=(CVixnEle &x);

	CVixnEle operator%=(DWORD x);
	CVixnEle operator%=(CVixnEle &x);

	CVixnEle GetAt(CVixnEle &x);

	CVixnEle& SetAt(DWORD x);
	void SetAt(CVixnEle &index,CVixnEle &val);

	virtual ~CVixnEle();

	CDATABASE GetBaseVal(void);

	friend class CVixn;

private:


	CVixnEle(CVixn *server,CDATABASE ele, ELE_BASE_TYPE base_type);
	CVixnEle(CVixn *server,DWORD val, ELE_BASE_TYPE base_type);

	CVixn *m_OwningServer; // detached if NULL
	ELE_BASE_TYPE m_BaseType;
	union {
		VIXNSRVRELE element;
		DWORD dval;
		DWORD *dwp;
	};

};





#endif // !defined(AFX_VIXNELE_H__A13A8D3B_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
