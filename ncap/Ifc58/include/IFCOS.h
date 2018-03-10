/******************************************************************************
 *
 * MODULE   
 *		IFCOS.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IFCOS.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/30/04 9:57a $
 *
 * ABSTRACT  
 *		IFC interface of the CIFCOS class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IFCOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
#define AFX_IFCOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <windows.h>
#include <Iobject.h>

#ifdef UNDER_CE

#define OS_NO_STREAMS

#endif

typedef DWORD IFCINTR_ID;

typedef int (*pfCONSOLEHDLR)(const char *, va_list);

typedef DWORD OS_pid_t;
typedef DWORD OS_thread_tid;
typedef HANDLE OS_sem_t;
typedef HANDLE OS_thread_t;
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
	OS_SEM_AVAILABLE,           // not owned
	OS_SEM_TAKEN            // owned
} OS_SEM_STATE;


#define IFC_SCAT_EXTRA_ENTRIES 10

typedef struct {
    DWORD   Size;
    DWORD   Linear;
    WORD    Selector;
    WORD    Reserved;
    DWORD    Avail;
    DWORD    Used;
    DWORD   r0phys;
    DWORD   r0size;
    DWORD   r1phys;
    DWORD   r1size;
} IFC_EDDS;

typedef IFC_EDDS *pIFC_EDDS;

#ifndef isWin95
#ifndef _WIN32_WCE
#define isWin95() (GetVersion() & 0x80000000)
#else
#define isWin95() (0)
#endif
#endif

#include <Intrupt.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CIFCOS : public CIobject  
{
public:
	void DeviceUnmap(OSHANDLE hdriver,DWORD LinearAddr);
	DWORD DeviceMap(OSHANDLE hdriver,DWORD PhysAddr, DWORD Length);
	int WriteConsole(const char *format, ...);
	int WriteConsole(const char * fmt, va_list marker);
	void InitConsole();

	CIFCOS();
	virtual ~CIFCOS();

	OSHANDLE OpenDeviceHandle(char *device_name, int seqnum);
	void CloseDeviceHandle(OSHANDLE hDriver);
	void CheckFileConsistency();
	BOOL ThreadCreate(OS_thread_t *thread,DWORD stack_size,pOS_thread_func thread_func,OS_thread_parm arg);
	OS_sem_t SemaphoreCreate(OS_SEM_STATE state, LPTSTR name);
	BOOL WaitSemaphore(OS_sem_t sem, DWORD dwMilliseconds );
	BOOL GiveSemaphore(OS_sem_t sem);
	BOOL DeleteSemaphore(OS_sem_t sem);
	OS_sem_t SemaphoreCountCreate( LONG lInitialCount, LONG lMaximumCount, LPTSTR name);

	OSHANDLE MutexCreate(BOOL bInitialOwner, LPTSTR lpName, BOOL &AlreadyExisted);
	BOOL AcquireMutex(OSHANDLE mutex, DWORD dwMilliseconds );
	BOOL ReleaseMutex(OSHANDLE mutex);
	BOOL DeleteMutex(OSHANDLE mutex);

	static DWORD GetSystimeMillisecs(void);
	static double GetSystimeMicrosecs(void);
	BOOL InterruptDisconnect(IFCINTR_ID intrID);
	IFCINTR_ID InterruptConnect(OSHANDLE hDriver,IFC_INTREVENT intrEvent);
	void InterruptDisconnectAll(OSHANDLE hDriver, DWORD pid );
	short InterruptWait(IFCINTR_ID intrID);
	static BOOL GatherLockRegion( OSHANDLE hDriver, BYTE *adr, pIFC_EDDS desc);
	static BOOL GatherLockDesc( OSHANDLE hDriver,pIFC_EDDS desc);
	static BOOL GatherUnlockRegion(OSHANDLE hDriver, pIFC_EDDS desc);


	static OSHANDLE OpenServiceHandle(void);
};


class IFC_EXT_API CrtHandleCloser : public CIobject  
{
public:

	CrtHandleCloser(OSHANDLE &handle) 
	{
		m_handle = handle;
	};

	~CrtHandleCloser() 
	{
		if (m_handle && m_handle != INVALID_HANDLE_VALUE) {
			CloseHandle(m_handle);
			m_handle = NULL;
		}
	};
private:
	OSHANDLE m_handle;
};

#define AUTO_CLOSE_HANDLE(h)  CrtHandleCloser __autocloser_##h(h);


class IFC_EXT_API CMutexHold : public CIobject  
{
public:

	CMutexHold(OSHANDLE mutex, DWORD dwMilliseconds) 
	{
		m_mutex = mutex;
		m_gotMutex=m_os.AcquireMutex(m_mutex,dwMilliseconds);
	};

	~CMutexHold() 
	{
		if (m_gotMutex)
			m_os.ReleaseMutex(m_mutex);
	};
private:
	CIFCOS m_os;
	OSHANDLE m_mutex;
	BOOL m_gotMutex;
};


#endif

void IFCCALL IfxSetConsoleHandler(pfCONSOLEHDLR handler);


typedef struct _IFC_PERF_INFO
{
	LONGLONG   IsrPerfCounterTotal;
	LONG	numInterrupts;
} IFC_PERF_INFO, *PIFC_PERF_INFO;

BOOL IFCCALL IfxQueryDriverPerformance(HANDLE h_driver, PIFC_PERF_INFO pInfo );


FARPROC IFCAPI IfxGetProcAddress(HMODULE hModule,LPCSTR lpProcName,DWORD popCount);

pSTRING IFCCALL IfxGetVersion(pSTRING version);


#define IFC_DLL_FIXUP_REF_FUNC	 ((DWORD)IfxSetConsoleHandler)


#endif // !defined(AFX_IFCOS_H__E554E632_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
