/******************************************************************************
 *
 * MODULE   
 *		Intrupt.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Intrupt.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:27a $
 *
 * ABSTRACT  
 *		IFC interface of the CInterrupt class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_INTRUPT_H__18E849E2_9655_11D1_AE73_00A0C959E757__INCLUDED_)
#define AFX_INTRUPT_H__18E849E2_9655_11D1_AE73_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
typedef DWORD IFC_INTREVENT;
#define IFC_INTREVENT_INVALID 0xfffffffful

typedef struct _CINTERRUPT_LIST_ITEM CINTERRUPT_LIST_ITEM,*PCINTERRUPT_LIST_ITEM;

struct _CINTERRUPT_LIST_ITEM {
	pCInterrupt item;
	PCINTERRUPT_LIST_ITEM next;

};

#include <register.h>
#include <module.h>
#include <ifcos.h>




typedef enum {
	IFC_INTR_TIMED_OUT,
	IFC_INTR_SIGNALED,
	IFC_EVENT1_SIGNALED,
	IFC_EVENT2_SIGNALED,
	IFC_EVENT3_SIGNALED,
	IFC_INTR_ERR_NOT_EVENT_SETTING
} IFC_INTR_WAIT_TYPE;


		 



#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CInterrupt : public CIobject
{
public:
	BOOL Connected();
	static LPTSTR MakeIntrSemaName(pCModule mod,IFC_INTREVENT intrEvent,char *semaName);
	virtual BOOL Clear(void);
	virtual BOOL Wait(DWORD dwMilliseconds);
	virtual IFC_INTR_WAIT_TYPE WaitIntrOrEventSet(DWORD dwMilliseconds, OS_event_t event1=NULL, OS_event_t event2=NULL, OS_event_t event3=NULL);
	CInterrupt(pCModule mod,IFC_INTREVENT intrEvent,BOOL eventSetting=TRUE);
	void Rearm(void);
	HANDLE EventHandle(void);
	IFC_INTREVENT InterruptEvent(void);
	virtual ~CInterrupt();

private:
	pCModule m_mod;
	IFC_INTREVENT m_intrEvent;
	IFCINTR_ID m_hInterrupt;
	HANDLE m_hEvent;
};


extern "C" pCInterrupt	IFCCALL IfxCreateInterrupt(pCModule mod,IFC_INTREVENT intrEvent);

#else

pCInterrupt	IFCCALL IfxCreateInterrupt(pCModule mod,IFC_INTREVENT intrEvent);

#endif	// __cplusplus



#endif // !defined(AFX_INTRUPT_H__18E849E2_9655_11D1_AE73_00A0C959E757__INCLUDED_)
