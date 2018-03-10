/******************************************************************************
 *
 * MODULE
 *    ObjThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/include/objthrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 10/09/01 9:48a $
 *
 * ABSTRACT
 *    
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_OBJTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_OBJTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vidsrct.h> 
#include <VnObject.h>

class CObjThread;

#define VS_OBJ_THREAD_FUNC_POP_COUNT 4
typedef DWORD (IVSAPI *VS_OBJ_THREAD_FUNC)(CObjThread *threadObj);

class IVSV_EXT_API CObjThread : public CVnObject
{
public:
	CObjThread(IDistribOS *pObj,LPSTR dllName, LPSTR funcName, BYTE *paramBlock, DWORD numParamBytes,BOOL ObjIsLocalToClient=FALSE);
	// Note: object created is always local to server
	// isLocalToClient TRUE means client and server are on the same node
	virtual ~CObjThread();

	IDistribOS *m_pVidSrc;
	volatile BOOLEAN m_shutdown;
	HANDLE m_shutdownEvent;	// fired when a thread shutdown requested
	BYTE *m_inParamBlock;
	DWORD m_inParamByteCount;
	DWORD ThreadProc(void);

	HANDLE m_hthread;
	BOOL m_isLocal;
private:
	IStream *m_pStmPtr;

	VS_OBJ_THREAD_FUNC m_threadFunc;

};

#endif // !defined(AFX_OBJTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
