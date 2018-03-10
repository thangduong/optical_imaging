// VnMesage.h: interface for the CVsMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VnMesage_H__A781F5F6_A690_11D4_B154_00105A0F576C__INCLUDED_)
#define AFX_VnMesage_H__A781F5F6_A690_11D4_B154_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VnVidSrc.h>
#include <VnOS.h>

typedef struct _VSMSGUNIT VSMSGUNIT;
struct _VSMSGUNIT {
	DWORD dataLen;
	VSMSGUNIT *next;
	ULONGLONG microEnQ;
	BYTE data[4];
};

#define VS_DEF_QMAX_STORE 20
#define VA_MAX_NUM_WAIT_ANY_MSG 16

class IVSV_EXT_API CVsMessage : public CVnObject  
 
{
public:
	HRESULT WaitMessageOrEvents( BYTE *message, DWORD *numMessageBytes, DWORD bytesAvailable, DWORD waitTimeMilliSec, DWORD numEvents, HVSEVENT *events, DWORD *waitResult);
	static HRESULT WaitAnyMessage(DWORD numMsgs,CVsMessage **msgList,CVsMessage **rcvMsg,BYTE *message, DWORD *numMessageBytes, DWORD bytesAvailable, DWORD waitTimeMilliSec);
	HRESULT WaitMessage( BYTE *message, DWORD *numMessageBytes, DWORD bytesAvailable, DWORD waitTimeMilliSec);
	HRESULT SendMessage( BYTE *message, DWORD numMessageBytes);
	CVsMessage(IDistribOS *vs,DWORD maxStore=VS_DEF_QMAX_STORE);
	virtual ~CVsMessage();

	IDistribOS *m_vs;
	HANDLE m_newMessageEvent; 
	HANDLE m_messageMutex;
	CVnOS m_os;
	volatile VSMSGUNIT *m_list;
	DWORD m_maxStore;

};

#endif // !defined(AFX_VnMesage_H__A781F5F6_A690_11D4_B154_00105A0F576C__INCLUDED_)
