/******************************************************************************
 *
 * MODULE
 *     Vixni.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/Vixni.h $
 *     $Revision: 1.1 $
 *     $Modtime: 5/01/03 4:47p $
 *
 * ABSTRACT
 *     IFC 150/40  IFC Vixn declarations
 *
 *
 * TECHNICAL NOTES
 *      
 * Vixni.h: interface for the CVixn class.
 *      
 *
 * Copyright (c) 1997-2001, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/

#if !defined(AFX_VIXN_H__A13A8D39_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
#define AFX_VIXN_H__A13A8D39_38F8_11D2_AF52_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVixn;

#include <ifc.h>
#include <VixnSrvi.h>



typedef DWORD VIXN_REGID;

typedef enum {
	VIXN_DMOD0,				// Daughter module 0
	VIXN_DMOD1,				// Daughter module 1
	VIXN_DMOD2,				// Daughter module 2
	VIXN_PARENT_MOD=0xffff	// Motherboard module
} VIXN_MOD_ENUM;

#include <VixnElei.h>

#define if_then(c)		VixnIfThen(c); {
#define else_do			VixnElseDo();
#define endif			VixnEndif(); }

#define loop				VixnLoopBegin(); {
#define exit_loop_when(c)	VixnExitLoopWhen(c); 
#define loop_end			VixnLoopEnd(); }

#define IFC_VIXN_NONSTOP 0x7fffffff

typedef BOOL (CVixn::*PFVIXNSCHED)(void);

#define VIXN_MAX_SRVR_FUNCS 20

#define VIXN_ADHOC_MEM_SPACE 0x5fffffff

class  VIXNEXP CVixn  
{
public:
	BOOL Create(void);
	void WriteReg(VIXN_REGID regID,CVixnEle &val,VIXN_MOD_ENUM modVixn=VIXN_PARENT_MOD);
	void WriteReg(VIXN_REGID regID,DWORD val,VIXN_MOD_ENUM modVixn=VIXN_PARENT_MOD);
	CVixnEle ReadReg(VIXN_REGID regID,VIXN_MOD_ENUM modVixn=VIXN_PARENT_MOD);
	void WritePortByte(CVixnEle &portNum, CVixnEle &val);
	void WritePortByte(DWORD portNum, CVixnEle &val);
	void WritePortByte(CVixnEle &portNum, BYTE val);
	void WritePortByte(DWORD portNum, BYTE val);
	void WritePortWord(CVixnEle &portNum, CVixnEle &val);
	void WritePortWord(DWORD portNum, CVixnEle &val);
	void WritePortWord(CVixnEle &portNum, WORD val);
	void WritePortWord(DWORD portNum, WORD val);
	void WritePortDWord(CVixnEle &portNum, CVixnEle &val);
	void WritePortDWord(DWORD portNum, CVixnEle &val);
	void WritePortDWord(CVixnEle &portNum, DWORD val);
	void WritePortDWord(DWORD portNum, DWORD val);
	CVixnEle ReadPortByte(CVixnEle &portNum);
	CVixnEle ReadPortByte(DWORD portNum);
	CVixnEle ReadPortWord(CVixnEle &portNum);
	CVixnEle ReadPortWord(DWORD portNum);
	CVixnEle ReadPortDWord(CVixnEle &portNum);
	CVixnEle ReadPortDWord(DWORD portNum);

	void WriteMem(DWORD memSpace,DWORD offset,CVixnEle &val);
	void WriteMem(DWORD memSpace,CVixnEle &offset,CVixnEle &val);
	void WriteMem(DWORD memSpace,DWORD offset,DWORD val);
	void WriteMem(DWORD memSpace,CVixnEle &offset,DWORD val);
	CVixnEle ReadMem(DWORD memSpace, DWORD offset);
	CVixnEle ReadMem(DWORD memSpace, CVixnEle &offset);

	CVixnEle ReadTimeMicro(void);
	CVixnEle ReadSysTimeMicroLow(void);
	CVixnEle ReadSysTimeMicroHi(void);
	CVixnEle ReadIntrEvent(void);
	CVixn(PCParentMod mod, IFC_INTREVENT InterruptEvent,IFC_INTREVENT InterruptEvent2=IFC_INTREVENT_INVALID);
	CVixn(PCParentMod mod, double Frequency, DWORD InvokeCount);
	virtual ~CVixn();

	virtual BOOL VixnMain(void)=0;
	void Schedule(PFVIXNSCHED pfCallback,DWORD numMicroseconds);
	void Schedule(PFVIXNSCHED pfCallback,CVixnEle &numMicroseconds);

	friend class CVixnEle;

protected:

	void VixnIfThen(CVixnEle &condition);

	void VixnElseDo(void);

	void VixnEndif(void);

	// Mark a loop begining inside a server function
	void VixnLoopBegin(void);

	// Mark a loop ending inside a server function
	void VixnLoopEnd(void);

	// Mark a loop conditional exit inside a server function, loop ends when condition==TRUE
	void VixnExitLoopWhen(CVixnEle &condition);

	PVIXSRVRBLK m_CurrentServerBlock;

	BOOL		m_InsideCreate;

	PVIXSRVRBLK m_GlobalServerBlock;
	PVIXNSERVER m_ProxyServer;
	PCParentMod	m_mod;
	int			m_InterruptEvent[2];

public:
	BOOL Abandoned();
	void Resume(void);
	void Suspend(void);
private:
	static CVixn *GetCurrentVixnApp();
	DWORD RegPhysAddr(pCModule mod,VIXN_REGID regID,DWORD regFlags);
	// Handle to the server data/bytecodes block
	PVIXSRVRBLK hblock(void);
	BOOL InCreateMode(void) { return m_InsideCreate; };

	typedef enum {
		VIXN_INITIALIZING,
		ELIGIBLE_TO_EXECUTE,
		VIXN_ABANDONED
	} VIXN_STATE_ENUM;

#define VIXN_FUNC_MAX_ARGS 4

	typedef struct {
		void		*pfunc;
		DWORD		argCount;	
		PVIXSRVRBLK ServerBlock;
		VIXNSRVRELE	argElements[VIXN_FUNC_MAX_ARGS];
		VIXNSRVRELE	retElement;
		char  funcName[60];
	} VIXNFUNCDESC,*PVIXNFUNCDESC;

	VIXNFUNCDESC m_ServerFuncs[VIXN_MAX_SRVR_FUNCS];
	DWORD m_NumServerFuncs;
	DWORD m_CurrentFuncIndex;

	double m_Frequency;
	DWORD m_InvokeCount;

	VIXN_STATE_ENUM m_VixnState;
};

#endif // !defined(AFX_VIXN_H__A13A8D39_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
