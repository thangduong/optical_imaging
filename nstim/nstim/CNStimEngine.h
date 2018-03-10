////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNStimEngine		Stimulation graphics engine
//
//
//  REVISION HISTORY
//
//	10/2/2005		Thang	- added this header
//							- added viewportitem structure and some viewport manipulation code to this header
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMENGINE_H__44CD16AC_2808_48D2_9C38_35D47E039288__INCLUDED_)
#define AFX_CNSTIMENGINE_H__44CD16AC_2808_48D2_9C38_35D47E039288__INCLUDED_

#include "CDirect3D.h"
#include "CDirect3DDevice.h"
#include "CSmartPtr.h"
#include "CDirect3DWnd.h"
#include "INStimProfile.h"
#include "INStimEngine.h"
#include "CList.h"
#include "INStimAtom.h"
#include "INStimAtom.h"
#include "CNStimSequence.h"
#include "CLptPort.h"

struct ViewportItem;

class CNStimEngine : public INStimEngine
{
	static CNStimEngine* m_pTheStimEngine;
public:
	static CNStimEngine* GetStimEngine() { return m_pTheStimEngine; };

	long m_iCount;
	CDirect3D m_Direct3D;
	CDirect3DDevice m_Direct3DDevice;
	CDirect3DWnd m_Direct3DWnd;
	CSmartPtr<INStimProfile> m_Profile;
	CList<INStimAtom*,INStimAtom*> m_AtomList;

	CNStimSequence* m_pSequencer;
	D3DDISPLAYMODE m_DisplayMode;

	int m_iRunNumber;
	int m_iState;
	int m_iStateParam;
	int m_iLastState;
	bool m_bShouldStop;
	HANDLE m_hStateChangeEvent;
	HANDLE m_hStateChangedEvent;

	D3DCOLOR m_BkColor;

	char m_StimName[1024];			// for writing log files after a stimulation


	// VIEWPORT code
	/*
	ViewportItem* m_pFirstVp;
	ViewportItem* m_pCurrentVp;
	ViewportItem* m_pLastVp;
*/
	int m_ViewportCenterX;
	int m_ViewportCenterY;
	D3DVIEWPORT9 m_WholeScreenVp;
	// END VIEWPORT code

	struct _D3DGAMMARAMP ramp;

	void PrepareDeviceFor2D();


	CLPTPort m_LptPort;
	int m_iPreFrameBit;
	int m_iPostFrameBit;
	int m_iStimOnStrobeBit;
	int m_iFrameDropBit;
	

	// screen information
	double m_dFramerate;
	LARGE_INTEGER Frequency;
	__int64 TicksPerFrame;
	__int64 HalfTicksPerFrame;
public:
	CNStimEngine();
	virtual ~CNStimEngine();

	bool Init(const CSmartPtr<INStimProfile>& Profile);

	// VIEWPORT manipulation code
/*	virtual HRESULT __stdcall AddViewport(unsigned char* pName, struct _D3DVIEWPORT9* pViewport);
	virtual HRESULT __stdcall FindViewport(unsigned char* pName, int* pIndex);
	virtual HRESULT __stdcall GetViewport(int index, unsigned char** pName, struct _D3DVIEWPORT9* pViewport);
	virtual HRESULT __stdcall SelectViewport(int index);
	virtual HRESULT __stdcall SelectViewportByName(unsigned char* pName);
	virtual HRESULT __stdcall DeleteViewport(int index);
	virtual HRESULT __stdcall DeleteViewportByName(unsigned char* pName);
	virtual HRESULT __stdcall CountViewport(int* pCount);
	virtual HRESULT __stdcall GetCurrentViewport(unsigned char** pName, struct _D3DVIEWPORT9* pViewport);
//	virtual HRESULT __stdcall GetCurrentViewportCenter(int* x, int* y);
*/
	virtual HRESULT __stdcall ApplyViewport(struct _D3DVIEWPORT9* pViewport);
	virtual HRESULT __stdcall GetViewportCenter(int* x, int* y) { (*x) = m_ViewportCenterX; (*y) = m_ViewportCenterY;return S_OK; }
	virtual HRESULT __stdcall SetViewportCenter(int x, int y) { m_ViewportCenterX = x; m_ViewportCenterY = y; return S_OK; }
	// END VIEWPORT code

	virtual HRESULT __stdcall CalibFramerate(int NFRAMES);

	virtual HRESULT __stdcall Run();
	virtual HRESULT __stdcall Stop();
	virtual HRESULT __stdcall GetDirect3DDevice(IDirect3DDevice9** pDevice);
	virtual HRESULT __stdcall AddAtom(INStimAtom* pAtom);
	virtual HRESULT __stdcall RemoveAtom(INStimAtom* pAtom);
	virtual HRESULT __stdcall SetState(DWORD state);
	virtual HRESULT __stdcall GetState(DWORD* pState);
	virtual HRESULT __stdcall FindAtom(unsigned char* pName, INStimAtom** ppAtom);
	virtual HRESULT __stdcall Stimulate(DWORD numFrames, unsigned char* stimName) {
		DWORD dwState;
		if (stimName != 0)
			strcpy(m_StimName, (char*)stimName);
		else
			strcpy(m_StimName, "");

		if ((GetState(&dwState)==S_OK) && (dwState == GE_STIMULATING))
			return S_OK;			// already stimulating
		else {
			m_iStateParam = numFrames;
			return SetState(GE_STIMULATING);
		}
	}

	virtual HRESULT __stdcall Simulate(DWORD numFrames, unsigned char* stimName) {
		DWORD dwState;
		if (stimName != 0)
			strcpy(m_StimName, (char*)stimName);
		else
			strcpy(m_StimName, "");

		if ((GetState(&dwState)==S_OK) && (dwState == GE_SIMULATING))
			return S_OK;			// already stimulating
		else {
			m_iStateParam = numFrames;
			return SetState(GE_SIMULATING);
		}
	}

	virtual HRESULT __stdcall AddSequenceMarker(int frameMarker, int type, unsigned char* patchName, DWORD list, int order) {
		if (list == 0)
			m_pSequencer->AddSequenceMarker(frameMarker, type, patchName, order);
		else
			m_pSequencer->AddSequenceMarker(frameMarker, type, patchName, (CList<NStimSequenceItemParam,NStimSequenceItemParam>*)list, order);
		return S_OK;
	}
	virtual HRESULT __stdcall GetAtomCount(int* pAtomCount);
	virtual HRESULT __stdcall GetAtom(int iAtomIndex, INStimAtom** ppAtom);

	virtual HRESULT __stdcall ClearAtom();
	virtual HRESULT __stdcall ClearSequence();

	virtual HRESULT __stdcall SetBkColor(unsigned long bkColor) {
		m_BkColor = (D3DCOLOR)bkColor;
		return S_OK;
	}
	virtual HRESULT __stdcall GetBkColor(unsigned long* pBkColor) {
		if (pBkColor)
			(*pBkColor) = (unsigned long)m_BkColor;
		return S_OK;
	}

	virtual HRESULT __stdcall GetFrameRate(double* pFramerate) {
		if (pFramerate)
			(*pFramerate) = m_dFramerate;
		return S_OK;
	}

	virtual HRESULT __stdcall GetDisplayMode(struct _D3DDISPLAYMODE** pMode) {
		if (pMode) {
			(*pMode) = &m_DisplayMode;
		}
		return S_OK;
	}

	virtual HRESULT __stdcall SetGammaRampElement(int index, unsigned short r, unsigned short g, unsigned short b) {
		ramp.blue[index] = b;
		ramp.green[index] = g;
		ramp.red[index] = r;
		m_Direct3DDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION, &ramp);
		return S_OK;
	}
	virtual HRESULT __stdcall GetGammaRampElement(int index, unsigned short* r, unsigned short* g, unsigned short* b) {
		(*b) = ramp.blue[index];
		(*g) = ramp.green[index];
		(*r) = ramp.red[index];
		return S_OK;
	}

	virtual HRESULT __stdcall SetGammaRamp(struct _D3DGAMMARAMP * pRamp) {
		memcpy(&ramp, pRamp, sizeof(ramp));
		m_Direct3DDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION, pRamp);
		return S_OK;
	}
	virtual HRESULT __stdcall GetGammaRamp(struct _D3DGAMMARAMP * pRamp) {
//		m_Direct3DDevice->GetGammaRamp(0, pRamp);
		memcpy(pRamp, &ramp, sizeof(ramp));
		return S_OK;
	}

	virtual HRESULT __stdcall Snap(const unsigned char* filename);
	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif // !defined(AFX_CNSTIMENGINE_H__44CD16AC_2808_48D2_9C38_35D47E039288__INCLUDED_)
