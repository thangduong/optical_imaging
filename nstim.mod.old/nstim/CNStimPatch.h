// CNStimPatch.h: interface for the CNStimPatch class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CNSTIMPATCH_H
#define CNSTIMPATCH_H

#include <d3dx9.h>
#include <string.h>
#include "CList.h"
#include "INStimPatch.h"
#include "INStimParam.h"
#include "CNStimIntPatchParam.h"

class CNStimPatch : public INStimPatch
{
	long m_iCount;
protected:
	CList<INStimParam*,INStimParam*> m_ParamList;
//	int* m_pWidth;
//	int* m_pHeight;

	char* m_pName;
	int* m_pCenterX;
	int* m_pCenterY;
	int* m_pBlitType;
	float* m_pBlitAngle;
	char* m_pViewportName;
	INStimAtom* m_pViewport;
	

	bool m_bPreview;

//	int* m_pTemporalOffset;
//	int* m_pDuration;
public:
	CNStimPatch();
	virtual ~CNStimPatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames) { return S_OK; }
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine) { return S_OK; }
	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { 
		if (strlen(m_pViewportName) > 0) {
			m_pViewport = 0;
			pEngine->FindAtom((unsigned char*)m_pViewportName, &m_pViewport);
		}
		return S_OK; }
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
/*	virtual HRESULT __stdcall GetWidth(int* width) { return S_OK; }
	virtual HRESULT __stdcall GetHeight(int* height) { return S_OK; }
*/
	virtual HRESULT __stdcall GetCenterX(int* centerX) { return S_OK; }
	virtual HRESULT __stdcall GetCenterY(int* centerY) { return S_OK; }
//	virtual HRESULT __stdcall GetTemporalOffset(int* offset) { return S_OK; }
//	virtual HRESULT __stdcall GetDuration(int* offset) { return S_OK; }
//	virtual HRESULT __stdcall SetParam(unsigned char* param, INStimParam* ppParam);
//	virtual HRESULT __stdcall SetWidth(int width) { (*m_pWidth) = width; return S_OK; }
//	virtual HRESULT __stdcall SetHeight(int height) { (*m_pHeight) = height; return S_OK; }
	virtual HRESULT __stdcall SetCenterX(int centerX) { (*m_pCenterX) = centerX; return S_OK; }
	virtual HRESULT __stdcall SetCenterY(int centerY) { (*m_pCenterY) = centerY; return S_OK; }
//	virtual HRESULT __stdcall SetTemporalOffset(int offset) { return S_OK; }
//	virtual HRESULT __stdcall SetDuration(int offset) { return S_OK; }
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)"[patch]"; return S_OK; }
	virtual HRESULT __stdcall SetBlitType(int blitType) { (*m_pBlitType) = blitType; return S_OK; }
	virtual HRESULT __stdcall GetBlitType(int* pBlitType) { if (pBlitType) (*pBlitType) = *m_pBlitType; return S_OK; }
	virtual HRESULT __stdcall GetBlitAngle(float* pAngle) { if (pAngle) (*pAngle) = (*m_pBlitAngle); return S_OK; }
	virtual HRESULT __stdcall SetBlitAngle(float angle) { (*m_pBlitAngle) = angle; return S_OK; }

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

	virtual HRESULT __stdcall IsPatch(unsigned char* pName) {
		if (strcmpi((char*)pName, m_pName) == 0)
		{
			return S_OK;
		}
		else
			return S_FALSE;
	}



	virtual HRESULT __stdcall GetParamCount(int* pParamCount);
	virtual HRESULT __stdcall GetParam(int index, INStimParam** ppParam);

	
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { 
		if (strlen(m_pViewportName) > 0) {
			m_pViewport = 0;
			pEngine->FindAtom((unsigned char*)m_pViewportName, &m_pViewport);
		}
		return S_OK; }
//	virtual HRESULT __stdcall GetTotalFrameCount(DWORD* pCount) {  if (pCount) (*pCount) = (*m_pTemporalOffset) + (*m_pDuration) + 1; return S_OK; }
	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

	// stuff for atoms
	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) {
		if (m_pViewport)
			m_pViewport->Exec(pEngine);
		return Draw(pEngine);
	}
	virtual HRESULT __stdcall IsAtom(unsigned char* pName) {
		return IsPatch((unsigned char*)pName);
	}

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
	virtual HRESULT __stdcall List(IPort* pPort) { return S_OK; }
	virtual HRESULT __stdcall GetDefiningString(char* buff, int buffSize) {
		return S_OK;
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
};

#endif
