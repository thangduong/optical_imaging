// CNStimBinaryNoisePatch.cpp: implementation of the CNStimBinaryNoisePatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimBinaryNoisePatch.h"
#include "CDirect3DDevice.h"
#include "CNStimIntPatchParam.h"
#include "CNStimBitArrayPatchParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
// Our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    FLOAT rhw;
    DWORD color;
    FLOAT tu, tv;   // The texture coordinates

	CUSTOMVERTEX()  { }

	CUSTOMVERTEX(FLOAT ax, FLOAT ay, FLOAT az, FLOAT arhw, DWORD ac, FLOAT atu, FLOAT atv) {
		x = ax; y =ay; z = az; rhw = arhw; color = ac; tu = atu; tv = atv;
	}
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
*/
#define	pi	3.1415926535
CNStimBinaryNoisePatch::CNStimBinaryNoisePatch()
{
	m_StimMark = 0;
	CNStimIntPatchParam* pIntParam;

	m_pData = new CNStimBitArrayPatchParam; m_ParamList.AddTail(m_pData);
	m_pData->SetParamName((unsigned char*)"data");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"ngridx");
	m_pNGridX = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"ngridy");
	m_pNGridY = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"gridwidth");
	m_pGridWidth = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"gridheight");
	m_pGridHeight = pIntParam->GetParamDataPtr();


	m_pGridLoc = 0;
}

CNStimBinaryNoisePatch::~CNStimBinaryNoisePatch()
{
	if (m_pGridLoc)
		delete [] m_pGridLoc;
}

HRESULT __stdcall CNStimBinaryNoisePatch::AdvanceFrame(int numFrames) {
	m_StimMark += (*m_pNGridX)*(*m_pNGridY)*numFrames;
	return S_OK;
}

HRESULT __stdcall CNStimBinaryNoisePatch::Draw(INStimEngine* pEngine) {
	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	IDirect3DTexture9* tex = 0;
	DWORD size;
	unsigned char* data;
	m_pData->GetRawData(&data);
	m_pData->GetSize(&size);

	int r;
	int idx;
	for (int i = 0; i < (*m_pNGridX)*(*m_pNGridY); i++) {

		idx = (i+m_StimMark)%size;
		if (idx < size)
			r = data[idx];
		else 
			r = 0;
//		r = (rand()%255);
/*		if (r > 128)
			tex = m_LumTex[255].GetDirect3DTexture();
		else
			tex = m_LumTex[0].GetDirect3DTexture(); */
		r = (r << 16) + (r << 8) + r;
//	pDevice->SetTexture(0, tex);
  //  pDevice->SetStreamSource( 0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );
    //pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    //pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, i, 2 );

		pDevice->Clear( 1, &m_pGridLoc[i], D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
								 r, 1.0f, 0 );

	}

	AdvanceFrame(1);
	return S_OK;
}
HRESULT __stdcall CNStimBinaryNoisePatch::Init(INStimEngine* pEngine) {
	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	CDirect3DDevice Device = pDevice;
	if (pDevice)
	{
		pDevice->Release();


		float left, top, bottom, right;
		DWORD col = 0xffffffff;
		float rhw = 1;//1.0f / (z * 990.0f + 10.0f);
		float theta = 0;//(float)(((float)(*m_pBlitAngle)*pi)/180);

		int x,y;
		m_pGridLoc = new D3DRECT[(*m_pNGridX)*(*m_pNGridY)];
		int i = 0;
		for (x = 0; x < (*m_pNGridX); x++) {
			for (y = 0; y < (*m_pNGridY); y++) {
				left = (float)((x - (*m_pNGridX)/2) * (*m_pGridWidth) + (*m_pCenterX));
				top = (float)((y - (*m_pNGridY)/2) * (*m_pGridHeight) + (*m_pCenterY));
				right = left + (*m_pGridWidth);
				bottom = top + (*m_pGridHeight);

				m_pGridLoc[i].x1 = left * cos(theta) - top * sin(theta);
				m_pGridLoc[i].y1 = left * sin(theta) + top * cos(theta);
				m_pGridLoc[i].x2 = right * cos(theta) - bottom * sin(theta);
				m_pGridLoc[i].y2 = right * sin(theta) + bottom * cos(theta);

				i++;
			}
		}

	}
	return S_OK;
}
