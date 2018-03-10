// CNStimAtom.h: interface for the CNStimAtom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMATOM_H__3DE6D5EF_0093_4A28_93E0_6414E7A28262__INCLUDED_)
#define AFX_CNSTIMATOM_H__3DE6D5EF_0093_4A28_93E0_6414E7A28262__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CList.h"
#include "INStimAtom.h"
#include <stdio.h>

class CNStimAtom : public INStimAtom  
{
	long m_iCount;
protected:
	CList<INStimParam*,INStimParam*> m_ParamList;
	char* m_pName;
	bool m_bPreview;
public:
	CNStimAtom();
	virtual ~CNStimAtom();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames) { return S_OK; }
	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { return S_OK; }
	virtual HRESULT __stdcall FindParam(unsigned char* param, INStimParam** ppParam) { 
		POSITION pos = m_ParamList.GetHeadPosition();
		char* pName;
		while (pos)
		{
			INStimParam* pParam = m_ParamList.GetNext(pos);
			pParam->GetParamName((unsigned char**)&pName);
			if (strcmpi((char*)pName, (char*)param) == 0)
			{
				(*ppParam) = pParam;
				break;
			}
		}
		return S_OK; 
	}

	virtual HRESULT __stdcall GetName(unsigned char** ppName) {
		if (ppName)
			(*ppName) = (unsigned char*)m_pName;
		return S_OK;
	}

	virtual HRESULT __stdcall SetName(unsigned char* pName) {
		delete m_pName;
		m_pName = new char[strlen((char*)pName)+1];
		strcpy(m_pName, (char*)pName);
		return S_OK;
	}

	virtual HRESULT __stdcall IsAtom(unsigned char* pName) {
		if (strcmpi((char*)pName, m_pName) == 0)
		{
			return S_OK;
		}
		else
			return S_FALSE;
	}

	virtual HRESULT __stdcall Preview() {
		if (m_bPreview)
			return S_OK;
		else
			return S_FALSE;
	}
	virtual HRESULT __stdcall SetPreview(int shouldPreview) {
		m_bPreview = shouldPreview ? true : false;
		return S_OK;
	}



	virtual HRESULT __stdcall GetParamCount(int* pParamCount);
	virtual HRESULT __stdcall GetParam(int index, INStimParam** ppParam);

	
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { return S_OK; }
	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

	// stuff for atoms
	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) = 0;

	virtual HRESULT __stdcall SetParam(unsigned char* pParamName, unsigned char* pParamValue) {
		POSITION pos = m_ParamList.GetHeadPosition();
		while (pos) {
			INStimParam* pCurParam = m_ParamList.GetNext(pos);
			unsigned char* outname;
			pCurParam->GetParamName(&outname);
			if (strcmpi((char*)pParamName, (char*)outname) == 0) {
				pCurParam->SetParamString(pParamValue);
			}
		}
		return S_OK;
	}
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)"generic atom"; return S_OK; }
	virtual HRESULT __stdcall List(IPort* pPort) { return S_OK; }

	virtual HRESULT __stdcall GetDefiningString(char* buff, int buffSize) {
		bool done = false;
		int mySize = 0;
		char temp[512];
		char* type;
		GetType((unsigned char**)&type);
		sprintf(temp, "%s %s { ", type, m_pName);
		if (strlen(temp) < buffSize) {
			strcpy(buff, temp);

			POSITION pos = m_ParamList.GetHeadPosition();
			char* name;
			while ((pos != 0) & (!done)) {
				INStimParam* pParam = m_ParamList.GetNext(pos);
				pParam->GetParamName((unsigned char**)&name);
//				sprintf(temp, "%s = %s", 
			}
		}
		return S_OK;
	}
};

#endif // !defined(AFX_CNSTIMATOM_H__3DE6D5EF_0093_4A28_93E0_6414E7A28262__INCLUDED_)
