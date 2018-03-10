/******************************************************************************
 *
 * MODULE   
 *		IntrCbak.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IntrCbak.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:27a $
 *
 * ABSTRACT  
 *		IFC interface of the CIntrCallback class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 2000 (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

// IntrCbak.h: interface for the CIntrCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTRCBAK_H__E54906A3_D68A_11D4_B164_00105A0F576C__INCLUDED_)
#define AFX_INTRCBAK_H__E54906A3_D68A_11D4_B164_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <Iobject.h>

#ifdef __cplusplus

class IFC_EXT_API CIntrCallback;

#else

typedef DWORD CIntrCallback;

#endif

typedef CIntrCallback *PCIntrCallback;
typedef void (*pIntrCallBackFunc)(void *pParam);


#include <Module.h>

#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CIntrCallback : public CIobject  
{
public:
	CIntrCallback(pCModule pMod, IFC_INTREVENT iEvent, pIntrCallBackFunc func, LPVOID pParam);

	virtual ~CIntrCallback();

	DWORD GetExceptionCode(LPVOID *ExceptionAddress=NULL);

	friend DWORD WINAPI IntrCallbackThread(LPVOID owner);
	CInterrupt  *m_Intr;

private:
	DWORD ThreadFunc();
	DWORD ExceptFilter(LPEXCEPTION_POINTERS exceptPtr);

	pCModule	m_pMod;
	IFC_INTREVENT	m_iEvent;
	HANDLE m_shutdownEvent;
	HANDLE m_hthread;
	pIntrCallBackFunc m_cbFunc;
	LPVOID m_pParam;
	DWORD m_iErrorCode;
	LPVOID m_ExceptionAddress;
};

#endif


#ifdef __cplusplus
extern "C" {
#endif

PCIntrCallback IFCCALL IfxCreateIntrCallback(pCModule pMod, IFC_INTREVENT iEvent, pIntrCallBackFunc func, LPVOID pParam);
void IFCCALL IfxDeleteIntrCallback(PCIntrCallback hCallback);


#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_INTRCBAK_H__E54906A3_D68A_11D4_B164_00105A0F576C__INCLUDED_)
