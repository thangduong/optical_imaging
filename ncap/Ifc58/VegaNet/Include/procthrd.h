/******************************************************************************
 *
 * MODULE
 *    ProcThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/include/procthrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 10/09/01 10:32a $
 *
 * ABSTRACT
 *    
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PROCTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_PROCTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vidsrct.h> 
#include <VnObject.h>
#include <VnBase.h>
#include <VnOS.h>

#define MAX_NUM_PROCNODE_OUTPUTS 6

#define MAX_NUM_PROCNODE_USER_OBJS 8

#define MAX_NUM_ENQUEUED_OUTPUTS 3


typedef struct {
	PIImgNode produceToNode;
	VS_REF_VAL_KIND enQKind;
	BOOL consumerIsRemote;
} PROCNODE_OUTPUT;

struct IProcNode;

class CProcThread;
class CProcNode;

#define VS_OBJ_THREAD_FUNC_POP_COUNT 4
typedef DWORD (IVSAPI *VS_PROC_THREAD_FUNC)(CProcThread *threadObj);
typedef void (IVSAPI *VS_PROC_THREAD_DEREF_FUNC)(CProcThread *threadObj, DWORD OutputId, HBYREFELE deRefHandle);


typedef struct _PROCT_DEREF_ELE PROCT_DEREF_ELE;
struct _PROCT_DEREF_ELE {
	VS_REF_VAL_KIND refKind;
	BYTE *framePtr;
	HBYREFELE qDeRefEle;
	PROCT_DEREF_ELE *next;
	BYTE	data[4];
};


typedef struct _PROCT_DEREF_UNIT PROCT_DEREF_UNIT;
struct _PROCT_DEREF_UNIT {
	HBYREFELE DeRefEle;
	DWORD refCount;
	PROCT_DEREF_UNIT *next;
};


class IVSV_EXT_API CProcThread : public CVnObject
{
public:
	CProcThread(CProcNode *procNode,CVSInvokeDesc *threadFunc, IDispatch **userObjs=NULL, DWORD numUserObjs=0,IDispatch *serverEntryObj=NULL);
	CProcThread(CProcNode *procNode,LPSTR dllName, LPSTR funcName, BYTE *paramBlock, DWORD numParamBytes, IDispatch **userObjs=NULL, DWORD numUserObjs=0,IDispatch *serverEntryObj=NULL);
	// Note: object created is always local to server
	// isLocalToClient TRUE means client and server are on the same node
	virtual ~CProcThread();

	virtual BOOL WaitNewImage(VS_INODE_IMG_ATTR *imgAttr, pBYTE *frameAddr, DWORD waitMilliSecs, HVSEVENT preemptEvent=0 , BYTE *userPayload=NULL, DWORD *payloadNumBytes=NULL);
	virtual void ReleaseImage( BYTE *frameAddr);

	virtual BOOL Enqueue(DWORD OutputId,VS_INODE_IMG_ATTR *imgAttr,BYTE *frameAddr,VS_FRAME_ENCODE remoteUseEncode,HBYREFELE deRefHandle, BYTE *userPayload=NULL, DWORD payloadNumBytes=0);

	virtual void SetDeRefHandler(VS_PROC_THREAD_DEREF_FUNC derefFunc); // must be called at beginning of UserThread function

	virtual HVSEVENT CreateInputEvent(BOOL bManualReset, BOOL bInitialState);
	virtual void DeleteInputEvent(HVSEVENT event);
	virtual void SetInputEvent(HVSEVENT event);

	// preemptEvent must be an event created by a call to CProcThread::CreateInputEvent
	virtual HRESULT WaitNewData(BYTE *dest, DWORD bytesAvailable, DWORD *numBytes, DWORD waitMilliSecs, HVSEVENT preemptEvent);
	virtual BOOL EnqueueData(DWORD OutputId, BYTE *data, DWORD numBytes);

	virtual void FlushInputs(void);
	virtual IVideoSrc *GetVideoSrc();
	virtual IDistribOS *GetDistribOs();

	virtual BYTE *GetUserData(DWORD *dataLen=NULL);

	virtual IDispatch *GetUserObject(DWORD objIndex=0);
	virtual HVSEVENT GetShutdownInputEvent();
	virtual BOOL WaitInputConnected(DWORD waitMilliSecs);


	BOOL CreateProcessThread(void);
	BOOL UpdateOutput(DWORD OutputId);
	BOOL UpdateInput(void);

	void UpdateOutputConnection(DWORD OutputId);
	void UpdateInputConnection(void);


	CProcNode *m_procNode;
	volatile BOOLEAN m_shutdown;
	HANDLE m_shutdownEvent;	// fired when a thread shutdown requested
	HANDLE m_InputConnectedEvent;	// fired when the node input is connected

	HVSEVENT m_shutdownInputEvent; // fired when a thread shutdown requested, usable in WaitNewData, WaitNewImage
	int m_error;

	HANDLE m_hthread;
	DWORD ThreadProc(void);

private:
	friend class CProcNode;

	BYTE *m_inParamBlock;
	DWORD m_inParamByteCount;
	void NotifyDetachConsumer(IDispatch *node);
	void NotifyDetachProducer(IDispatch *node, DWORD srcOutputId);
	BOOL ReleaseEleRef(DWORD OutputId, HBYREFELE deRefHandle);
	PIImgNode m_produceToNodes[MAX_NUM_PROCNODE_OUTPUTS];
	PIImgNode m_inputNode;
	IVideoSrc *m_pVidSrc;

	VS_IMGNODE_ATTR m_inputNodeAttr;
	VS_IMGNODE_ATTR m_produceNodeAttr[MAX_NUM_PROCNODE_OUTPUTS];

	IStream *m_pOutStmPtr[MAX_NUM_PROCNODE_OUTPUTS];
	IStream *m_pInStrPtr;
	IStream *m_bVsStrPtr;

	VS_PROC_THREAD_FUNC m_threadFunc;
	DWORD m_lastInputSize;
	CVnOS m_os;
	HANDLE m_pMutex;
	PROCT_DEREF_ELE *m_activeRoot;
	VS_PROC_THREAD_DEREF_FUNC m_derefFunc;
	PROCT_DEREF_UNIT *m_outstandingDerefs;
	PROCT_DEREF_UNIT *m_freeDerefs;
	DWORD m_numUserObjs;

	LPDISPATCH m_userObjs[MAX_NUM_PROCNODE_USER_OBJS];
	LPDISPATCH m_threadedUserObjs[MAX_NUM_PROCNODE_USER_OBJS];
	IStream *m_userObjStmPtr[MAX_NUM_PROCNODE_USER_OBJS];

	IDispatch *m_serverEntryObj;

	DWORD m_numEnqueuedOutputs[MAX_NUM_PROCNODE_OUTPUTS];
};

#endif // !defined(AFX_OBJTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
