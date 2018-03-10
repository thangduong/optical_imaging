// CNStimLeechAtom.h: interface for the CNStimLeechAtom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMLEECHATOM_H__CDF468A4_8180_45D7_95AD_C6F22F521DB2__INCLUDED_)
#define AFX_CNSTIMLEECHATOM_H__CDF468A4_8180_45D7_95AD_C6F22F521DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimAtom.h"
#include "CString.h"
#include "CNStimStringPatchParam.h"

struct LeechParamCtrlItem {
	CString name;
	CString value;
	INStimParam* pParam;
};

class CNStimLeechAtom : public CNStimAtom  
{
	CNStimStringPatchParam m_HostName;
	INStimAtom* m_pHostAtom;
	CList<LeechParamCtrlItem*, LeechParamCtrlItem*> m_LeechParamList;
public:
	CNStimLeechAtom();
	virtual ~CNStimLeechAtom();
	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) {
		POSITION pos = m_LeechParamList.GetHeadPosition();
		while (pos) {
			LeechParamCtrlItem* pCurItem = m_LeechParamList.GetNext(pos);
			if (pCurItem) {
				pCurItem->pParam->SetParamString((unsigned char*)pCurItem->value.GetData());
			}
		}
		m_pHostAtom->Exec(pEngine);
		return S_OK;
	}
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { 
		return S_OK;
	}
	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { 
		pEngine->FindAtom((unsigned char*)m_HostName.GetParamDataPtr(), &m_pHostAtom);
		POSITION pos = m_LeechParamList.GetHeadPosition();
		while (pos) {
			LeechParamCtrlItem* pCurItem = m_LeechParamList.GetNext(pos);
			if (pCurItem) {
				m_pHostAtom->FindParam((unsigned char*)pCurItem->name.GetData(), &pCurItem->pParam);
			}
		}
		return S_OK; 
	}
	virtual HRESULT __stdcall SetParam(unsigned char* pParamName, unsigned char* pParamValue) {
		if (strcmpi((char*)pParamName, "host") == 0) {
			m_HostName.SetParamString(pParamValue);
		}
		else {
			LeechParamCtrlItem* pItem = new LeechParamCtrlItem;
			pItem->name = (char*)pParamName;
			pItem->value = (char*)pParamValue;
			pItem->pParam = 0;
			m_LeechParamList.AddTail(pItem);
		}
		return S_OK;
	}
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)"leech"; return S_OK; }

};

#endif // !defined(AFX_CNSTIMLEECHATOM_H__CDF468A4_8180_45D7_95AD_C6F22F521DB2__INCLUDED_)
