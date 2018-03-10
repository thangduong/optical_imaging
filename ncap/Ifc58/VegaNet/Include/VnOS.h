/******************************************************************************
 *
 * MODULE   
 *		IFCOS.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/VnOS.h $
 *		$Revision: 1.1 $
 *		$Modtime: 3/16/01 9:53a $
 *
 * ABSTRACT  
 *		IFC interface of the CVnOS class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 2000 (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_VnOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
#define AFX_VnOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <VnObject.h>
#include <VnVar.h>
#include <stdio.h>
#include <VnError.h>

#ifdef UNDER_CE

#define OS_NO_STREAMS

#endif

typedef DWORD IFCINTR_ID;

typedef int (*pfCONSOLEHDLR)(const char *, va_list);

typedef HANDLE OS_sem_t;
typedef HANDLE OS_event_t;
typedef LPVOID OS_thread_parm;
#define OS_THREADCALL WINAPI
typedef LPTHREAD_START_ROUTINE  pOS_thread_func;

#define OS_INVALID_SEM		INVALID_HANDLE_VALUE
#define OS_INVALID_MUTEX	INVALID_HANDLE_VALUE

#define IFC_SEMA_NAME_LEN 80
#define OS_SLASHCHAR '\\'

#define OS_get_pid()  GetCurrentProcessId()
#define OS_ALL_PROCESSES 0x0fffffff

#define OS_get_tid()  GetCurrentThreadId()
#define IFC_DEFAULT_TID      ((OS_thread_tid)0)

typedef enum {
	VnOS_SEM_AVAILABLE,           // not owned
	VnOS_SEM_TAKEN            // owned
} VnOS_SEM_STATE;


typedef struct {
    DWORD   Size;
    DWORD   Linear;
    WORD    Selector;
    WORD    Reserved;
    WORD    Avail;
    WORD    Used;
    DWORD   r0phys;
    DWORD   r0size;
    DWORD   r1phys;
    DWORD   r1size;
} VS_EDDS;

typedef VS_EDDS *LPVS_EDDS;


#ifndef isWin95
#ifndef _WIN32_WCE
#define isWin95() (GetVersion() & 0x80000000)
#else
#define isWin95() (0)
#endif
#endif


#ifdef __cplusplus
class IVSV_EXT_API CVnOS : public CVnObject  
{
public:
	int WriteConsole(const char *format, ...);
	int WriteConsole(const char * fmt, va_list marker);
	void InitConsole();

	CVnOS();
	virtual ~CVnOS();

	OS_sem_t SemaphoreCreate(VnOS_SEM_STATE state, LPTSTR name);
	BOOL WaitSemaphore(OS_sem_t sem, DWORD dwMilliseconds );
	BOOL GiveSemaphore(OS_sem_t sem);
	BOOL DeleteSemaphore(OS_sem_t sem);

	HANDLE MutexCreate(BOOL bInitialOwner, LPTSTR lpName, BOOL &AlreadyExisted);
	BOOL AcquireMutex(HANDLE mutex, DWORD dwMilliseconds );
	BOOL ReleaseMutex(HANDLE mutex);
	BOOL DeleteMutex(HANDLE mutex);

	static ULONGLONG GetSystimeMillisecs(void);
	static ULONGLONG GetSystimeMicrosecs(void);
	static DWORD GetSysElapsedMillisecs(void);
	static double GetSysElapsedMicrosecs(void);
	static ULONGLONG ElapsedMilliToSysTimeMilli(DWORD elapsedMilli);
	static ULONGLONG ElapsedMicroToSysTimeMicro(double elapsedMicro);
	static void SetSystimeMillisecs(ULONGLONG sysTimeMillisecs);

	static BOOL GatherLockRegion(  BYTE *adr, LPVS_EDDS desc);
	static BOOL GatherUnlockRegion( LPVS_EDDS desc);


	static FILE *EnvFopen(char *name, char *mode);

protected:
};
#endif

void IVSCALL VsSetConsoleHandler(pfCONSOLEHDLR handler);





#endif // !defined(AFX_IFCOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
