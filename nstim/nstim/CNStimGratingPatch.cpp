// CNStimGratingPatch.cpp: implementation of the CNStimGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimGratingPatch.h"
#include "CDirect3DDevice.h"
#include "CNStimFloatPatchParam.h"
#include <stdio.h>
#include "CNStimEngine.h"

char* CNStimGratingPatch::m_pPatchType = "grating";
float* CNStimGratingPatch::sineTable = 0;
float* CNStimGratingPatch::cosineTable = 0;
bool CNStimGratingPatch::lutInitialized = false;


#define pi	3.1415926535
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimGratingPatch::CNStimGratingPatch()
{
	if (!lutInitialized) {
		sineTable = new float[360*LUT_RESOLUTION];
		cosineTable = new float[360*LUT_RESOLUTION];
		for (int i = 0; i < 360*LUT_RESOLUTION; i++) {
			sineTable[i] = (sin(pi*(double)i/(LUT_RESOLUTION*180)));
			cosineTable[i] = (cos(pi*(double)i/(LUT_RESOLUTION*180)));
		}
		lutInitialized = true;
	}

	CNStimIntPatchParam* pIntParam;
	CNStimFloatPatchParam* pFloatParam;
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Width");
	m_pWidth = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Height");
	m_pHeight = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Shape");
	m_pShape = pIntParam->GetParamDataPtr();
	(*m_pShape) = 1;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"SpatialFrequency");
	m_pSfPixPerCycle = pFloatParam->GetParamDataPtr();
	(*m_pSfPixPerCycle) = 50.0;
	pFloatParam->SetUnit("ppc");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Alpha");
	m_pAlpha = pIntParam->GetParamDataPtr();
	(*m_pAlpha) = 255;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"BiDir");
	m_pBiDir = pIntParam->GetParamDataPtr();
	(*m_pBiDir) = 0;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Type");
	m_pType = pIntParam->GetParamDataPtr();
	(*m_pType) = 0;


	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"SpatialPhase");
	m_pSpatialPhase = pFloatParam->GetParamDataPtr();
	(*m_pSpatialPhase) = 0;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"TemporalFrequency");
	m_pTfCycPerSec = pFloatParam->GetParamDataPtr();
	(*m_pTfCycPerSec) = 4;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"TextureOrientation");
	m_pBlitAngle3 = pFloatParam->GetParamDataPtr();
	(*m_pBlitAngle3) = 0;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"Contrast");
	m_pContrast = pFloatParam->GetParamDataPtr();
	(*m_pContrast) = 127;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"Luminance");
	m_pLuminance = pFloatParam->GetParamDataPtr();
	(*m_pLuminance) = 127.5;
	

	m_iNumFrames = 0;
	m_iCurrentFrame = 0;
	m_iIncDir = 1;
#ifdef _DEBUG
	char dbgMsg[512];
	sprintf(dbgMsg, "creating CNStimPatchGrating %s\r\n", m_pName);
	OutputDebugString(dbgMsg);
#endif
	m_pEngine = 0;
	m_pDevice = 0;
	biDirCtr = 1;
}

CNStimGratingPatch::~CNStimGratingPatch()
{
	if (m_pDevice)
		m_pDevice->Release();
	if (m_pEngine)
		m_pEngine->Release();
#ifdef _DEBUG
	char dbgMsg[512];
	sprintf(dbgMsg, "deleting CNStimPatchGrating %s\r\n", m_pName);
	OutputDebugString(dbgMsg);
#endif
}

HRESULT __stdcall CNStimGratingPatch::AdvanceFrame(int numFrames)
{
	if ((*m_pBiDir))
	{
		for (int i = 0; i < numFrames; i++) {
			m_CurPhase = m_CurPhase + (double)m_iIncDir*((double)1/m_FramesPerSec)*(*m_pTfCycPerSec);
			if (m_CurPhase > 1.0)/*(double)(*m_pBiDir))*/ {
				// NOTE: old code has 1 in place of (*m_pBiDir)
				if (biDirCtr == (*m_pBiDir)) {
					m_CurPhase = (2.0)-m_CurPhase;
					m_iIncDir = -m_iIncDir;
					biDirCtr = 1;
				}
				else {
					biDirCtr++;
					m_CurPhase = m_CurPhase-1.0;
				}
			}
			else if (m_CurPhase < 0) {
				if (biDirCtr == (*m_pBiDir)) {
					m_CurPhase = -m_CurPhase;
					m_iIncDir = -m_iIncDir;
					biDirCtr = 1;
				}
				else {
					biDirCtr++;
					m_CurPhase = m_CurPhase+1.0;
				}
			}
#ifdef _DEBUG
	char dbgMsg[512];
	sprintf(dbgMsg, "frame %d inc=%d phase = %0.2f\r\n", i, m_iIncDir, m_CurPhase);
	OutputDebugString(dbgMsg);
#endif
		}
/*
		m_iCurrentFrame = (m_iCurrentFrame+m_iIncDir*numFrames);
		do {

		if (m_iCurrentFrame <= 0) {
			m_iIncDir = 1;
			m_iCurrentFrame = -m_iCurrentFrame;
		}
		else if (m_iCurrentFrame >= (*m_pBiDir)*m_iNumFrames) {
			m_iIncDir = -1;
			m_iCurrentFrame = (((*m_pBiDir)*2)*m_iNumFrames - m_iCurrentFrame - 1);
		}
		}
		while ((m_iCurrentFrame < 0) || ((m_iCurrentFrame >= (*m_pBiDir)*m_iNumFrames)));
		*/
	}
	else
	{
		m_CurPhase = m_CurPhase + ((double)numFrames/m_FramesPerSec)*(*m_pTfCycPerSec);
		if (m_CurPhase > 1.0) {
			m_CurPhase = m_CurPhase - floor(m_CurPhase);
		}
//		m_iCurrentFrame = (m_iCurrentFrame+numFrames)%(m_iNumFrames);
	}
//	m_iCurrentFrame = (m_iCurrentFrame+numFrames)%(m_iNumFrames);
	return S_OK;
}

// Our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    FLOAT rhw;
    FLOAT tu, tv;   // The texture coordinates
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)

HRESULT __stdcall CNStimGratingPatch::Draw(INStimEngine* pEngine)
{
/*	
	int iFrameShift = 
		((int)(((m_iCurrentFrame%m_iNumFrames) * (*m_pSfPixPerCycle) / m_iNumFrames) + 
		((*m_pSpatialPhase)*(*m_pSfPixPerCycle))/360))%(*m_pSfPixPerCycle);
		*/

	int iFrameShift;
	if ((*m_pType)==0) {
		double dFrameShift = ((*m_pSfPixPerCycle)*(m_CurPhase - 0.5));
		iFrameShift = (int)dFrameShift;
		if (dFrameShift > 0) {
			if ((dFrameShift - floor(dFrameShift)) > 0.5)
				iFrameShift++;
		}
		else {
			if ((dFrameShift - floor(dFrameShift)) < 0.5)
				iFrameShift--;
		}
	}
	else if ((*m_pType)==1) {

		double dFrameShift;
		if (m_CurPhase >= .5) 
			dFrameShift = ((*m_pSfPixPerCycle)*0.5);
		else
			dFrameShift = 0;

		iFrameShift = (int)dFrameShift;
		if ((dFrameShift - floor(dFrameShift)) > 0.5)
			iFrameShift++;
	}
	else if ((*m_pType)==2) {
		iFrameShift = 0;
	}
	int theta0 = ((int)((*m_pBlitAngle)*LUT_RESOLUTION));
	int theta2 = ((int)((*m_pBlitAngle3)*LUT_RESOLUTION));

	ct0 = cosineTable[theta0];
	st0 = sineTable[theta0];
	ct2 = cosineTable[theta2];
	st2 = sineTable[theta2];

	CUSTOMVERTEX* verts = 0;
	m_VertexBuffer->Lock(0, 0, (void**)(&verts), 0);

	float aleft;
	float atop;
	float aright;
	float abottom;
	
	int vpCX, vpCY;

	pEngine->GetViewportCenter(&vpCX, &vpCY);
	vpCX = vpCX + (*m_pCenterX);
	vpCY = vpCY + (*m_pCenterY);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// From back buffer to front buffer
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	verts[0].x = left0  * ct0 - top0 * st0     + vpCX; 
	verts[0].y = left0  * st0 + top0 * ct0     + vpCY;
	verts[1].x = right0 * ct0 - top0 * st0     + vpCX; 
	verts[1].y = right0 * st0 + top0 * ct0     + vpCY;
	verts[2].x = left0  * ct0 - bottom0 * st0  + vpCX; 
	verts[2].y = left0  * st0 + bottom0 * ct0  + vpCY;
	verts[3].x = right0 * ct0 - bottom0 * st0  + vpCX; 
	verts[3].y = right0 * st0 + bottom0 * ct0  + vpCY; 
/*
	verts[2].x = left0  * ct0 - top0 * st0     + vpCX; 
	verts[2].y = left0  * st0 + top0 * ct0     + vpCY;
	verts[0].x = right0 * ct0 - top0 * st0     + vpCX; 
	verts[0].y = right0 * st0 + top0 * ct0     + vpCY;
	verts[3].x = left0  * ct0 - bottom0 * st0  + vpCX; 
	verts[3].y = left0  * st0 + bottom0 * ct0  + vpCY;
	verts[1].x = right0 * ct0 - bottom0 * st0  + vpCX; 
	verts[1].y = right0 * st0 + bottom0 * ct0  + vpCY; 
*/

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// From grating to back buffer
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	aleft = iFrameShift-(*m_pSfPixPerCycle)/2-m_iGratingBuffWidth/2;
	aright = aleft + m_iGratingBuffWidth;
	atop = -m_iGratingBuffHeight;
	abottom = atop+m_iGratingBuffHeight;

	verts[4 + 0].x =  aleft * ct2  - atop * st2     + xTrans;
	verts[4 + 0].y =  aleft * st2  + atop * ct2     + yTrans;
	verts[4 + 1].x =  aright * ct2 - atop * st2     + xTrans; 
	verts[4 + 1].y =  aright * st2 + atop * ct2     + yTrans;
	verts[4 + 2].x =  aleft * ct2  - abottom * st2  + xTrans;
	verts[4 + 2].y =  aleft * st2  + abottom * ct2  + yTrans;
	verts[4 + 3].x =  aright * ct2 - abottom * st2  + xTrans; 
	verts[4 + 3].y =  aright * st2 + abottom * ct2  + yTrans;

	atop = 0;
	abottom = atop+m_iGratingBuffHeight;

	verts[8 + 0].x =  aleft * ct2  - abottom * st2  + xTrans;
	verts[8 + 0].y =  aleft * st2  + abottom * ct2  + yTrans;
	verts[8 + 1].x =  aright * ct2 - abottom * st2  + xTrans; 
	verts[8 + 1].y =  aright * st2 + abottom * ct2  + yTrans;

	m_VertexBuffer->Unlock();


	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// BLITTING CODE
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);

	IDirect3DTexture9* tex;
    LPDIRECT3DSURFACE9 pRTOld = NULL;		// old render target
	LPDIRECT3DSURFACE9 pDSOld = NULL;		// old depth stensil
	IDirect3DSurface9* pds;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set up the device first
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	HRESULT hr;
	hr = pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetStreamSource(0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );

	// Change target to our on personal back buffer
	hr = m_BackBuff->GetSurfaceLevel(0,&pds);
    hr = pDevice->GetRenderTarget(0, &pRTOld );
	hr = pDevice->GetDepthStencilSurface(&pDSOld);
	hr = pDevice->SetRenderTarget(0, pds);
	hr = pDevice->SetDepthStencilSurface(0);
	pds->Release();

	// Now we want to change the alpha of the local back buffer while keeping the 
	// RGB components the same by adding a map of appropriate alpha and zero RGB
	tex = m_GratingBuff.GetDirect3DTexture();
	pDevice->SetTexture(0, tex);

	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_DESTALPHA);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 4);

	// Finally, render onto the screen.  In this stage, we use alpha blending
	// to blend the src onto the screen
	hr = pDevice->SetRenderTarget( 0, pRTOld); 
	hr = pDevice->SetDepthStencilSurface(pDSOld);

	tex = m_BackBuff.GetDirect3DTexture();
	hr = pDevice->SetTexture(0, tex);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	hr = pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	AdvanceFrame(1);
	return S_OK;
}

HRESULT __stdcall CNStimGratingPatch::Init(INStimEngine* pEngine)
{
	CNStimPatch::Init(pEngine);

	if (m_pEngine)
		m_pEngine->Release();
	m_pEngine = pEngine;
	m_pEngine->AddRef();

	if (m_pDevice)
		m_pDevice->Release();
	m_pDevice = 0;
	pEngine->GetDirect3DDevice(&m_pDevice);
	CDirect3DDevice Device = m_pDevice;
	if (m_pDevice)
	{

		CDirect3DSurface surf;
		int wnb;
		int hnb;
		char* temp;
		int x, y;

		D3DLOCKED_RECT lr;
		if ((*m_pTfCycPerSec) > 0) {
			double framerate;
			pEngine->GetFrameRate(&framerate);
			m_iNumFrames = framerate / (*m_pTfCycPerSec);
		}
		else {
			m_iNumFrames = 1;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		// create grating buffer
		////////////////////////////////////////////////////////////////////////////////////////////////////

		m_iGratingBuffWidth = sqrt(2)*max(*m_pWidth, *m_pHeight)+(*m_pSfPixPerCycle);
		m_iGratingBuffHeight = sqrt(2)*max(*m_pWidth, *m_pHeight)+(*m_pSfPixPerCycle);
		wnb = 1; hnb = 1;
		while (m_iGratingBuffWidth > (1<<wnb))
			wnb++;
		while (m_iGratingBuffHeight > (1<<hnb))
			hnb++;

		m_iGratingBuffWidth = (1<<wnb);
		m_iGratingBuffHeight = (1<<(hnb-1));

		surf = Device.CreateSurface(m_iGratingBuffWidth,m_iGratingBuffHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
		surf->LockRect(&lr,0,0);
		temp = (char*)lr.pBits;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		// draw the grating onto temp
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		for (y = 0; y < (m_iGratingBuffHeight); y++)
		{
			for (x = 0; x < (m_iGratingBuffWidth); x++) {
				int sineIdx = ((double)x * 2 * 180 / (double)(*m_pSfPixPerCycle)) * LUT_RESOLUTION;
				sineIdx = sineIdx % (LUT_RESOLUTION*360);
				double sine = sineTable[sineIdx]; 
				int v;
				if (sine > 0)
					v = (int)floor(sine*(*m_pContrast) + (*m_pLuminance) + .5);
				else
					v = (int)floor(sine*(*m_pContrast) + (*m_pLuminance) - .5);
				if (v < 0)
					v = 0;
				if (v > 255)
					v = 255;
				((DWORD*)temp)[x] = v + (v << 8) + (v << 16) + (0xff<<24);
			}
			temp = temp + lr.Pitch;
		}
		surf->UnlockRect();

		m_GratingBuff = Device.CreateTexture(m_iGratingBuffWidth, m_iGratingBuffHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_GratingBuff.IsNull()) {
			IDirect3DSurface9* pds;
			m_GratingBuff->GetSurfaceLevel(0,&pds);
			HRESULT hr= Device->UpdateSurface(surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}
		else
			MessageBeep(-1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		// create back buffer
		////////////////////////////////////////////////////////////////////////////////////////////////////
		m_iBackBuffWidth = (*m_pWidth);//max(*m_pWidth, *m_pHeight)+(*m_pSfPixPerCycle);
		m_iBackBuffHeight = (*m_pHeight);// max(*m_pWidth, *m_pHeight)+(*m_pSfPixPerCycle);
		wnb = 1; hnb = 1;
		while (m_iBackBuffWidth > (1<<wnb))
			wnb++;
		while (m_iBackBuffHeight > (1<<hnb))
			hnb++;

		m_iBackBuffWidth = (1<<wnb);
		m_iBackBuffHeight = (1<<hnb);

		surf = Device.CreateSurface(m_iBackBuffWidth,m_iBackBuffHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
		surf->LockRect(&lr,0,0);
		temp = (char*)lr.pBits;
		
//		memset(temp, 0, lr.Pitch*m_iBackBuffHeight);
		// draw the grating onto temp
		if ((*m_pShape) == 1) {
			// draw a circle here!  it's a square right now!
			int startx = (m_iBackBuffWidth - (*m_pWidth))/2;
			int starty = (m_iBackBuffHeight - (*m_pHeight))/2;
			temp = temp + lr.Pitch * starty;
			double xv, yv;
			double w2 = (*m_pWidth)*(*m_pWidth)/4, 
				h2 = (*m_pHeight)*(*m_pHeight)/4;
			// square shape, so no rasterization required
			for (y = starty; y < starty+(*m_pHeight); y++)
			{
				yv = y - starty - (*m_pHeight)/2;
				for (int x = startx; x < (*m_pWidth)+startx; x++) {
					xv = x - startx - (*m_pWidth)/2;

					if ((xv*xv*h2+yv*yv*w2) <= w2*h2)
						((DWORD*)temp)[x] = ((*m_pAlpha)<<24);
				}

				temp = temp + lr.Pitch;
			}
		}
		else
		{
			int startx = (m_iBackBuffWidth - (*m_pWidth))/2;
			int starty = (m_iBackBuffHeight - (*m_pHeight))/2;
			temp = temp + lr.Pitch * starty;
			// square shape, so no rasterization required
			for (y = starty; y < starty+(*m_pHeight); y++)
			{
				for (int x = startx; x < (*m_pWidth)+startx; x++)
					((DWORD*)temp)[x] = ((*m_pAlpha)<<24);// + 0xffffff;

				temp = temp + lr.Pitch;
			}
		}

		surf->UnlockRect();

		m_BackBuff = Device.CreateTexture(m_iBackBuffWidth, m_iBackBuffHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_BackBuff.IsNull()) {
			IDirect3DSurface9* pds;
			m_BackBuff->GetSurfaceLevel(0,&pds);
			HRESULT hr= Device->UpdateSurface(surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}
		else
			MessageBeep(-1);

#define	NVERTICES		12
		m_VertexBuffer = Device.CreateVertexBuffer(NVERTICES*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT);

		float z = 0;
		float rhw = 1;//1.0f / (z * 990.0f + 10.0f);

		float theta = 0;

		CUSTOMVERTEX* verts = 0;
		m_VertexBuffer->Lock(0, 0, (void**)&(verts), 0);

		verts[0].z = z; 
		verts[0].tu = 0; 
		verts[0].tv = 0;
		verts[0].rhw = rhw;
		verts[1].z = z; 
		verts[1].tu = 1; 
		verts[1].tv = 0;
		verts[1].rhw = rhw;
		verts[2].z = z; 
		verts[2].tu = 0; 
		verts[2].tv = 1;
		verts[2].rhw = rhw;
		verts[3].z = z; 
		verts[3].tu = 1; 
		verts[3].tv = 1;
		verts[3].rhw = rhw;

		verts[4 + 0].z = z; 
		verts[4 + 0].tu = 0; 
		verts[4 + 0].tv = 0;
		verts[4 + 0].rhw = rhw;
		verts[4 + 1].z = z; 
		verts[4 + 1].tu = 1; 
		verts[4 + 1].tv = 0;
		verts[4 + 1].rhw = rhw;
		verts[4 + 2].z = z; 
		verts[4 + 2].tu = 0; 
		verts[4 + 2].tv = 1;
		verts[4 + 2].rhw = rhw;
		verts[4 + 3].z = z; 
		verts[4 + 3].tu = 1; 
		verts[4 + 3].tv = 1;
		verts[4 + 3].rhw = rhw;

		
		verts[8 + 0].z = z; 
		verts[8 + 0].tu = 0; 
		verts[8 + 0].tv = 0;
		verts[8 + 0].rhw = rhw;
		verts[8 + 1].z = z; 
		verts[8 + 1].tu = 1; 
		verts[8 + 1].tv = 0;
		verts[8 + 1].rhw = rhw;
		verts[8 + 2].z = z; 
		verts[8 + 2].tu = 0; 
		verts[8 + 2].tv = 1;
		verts[8 + 2].rhw = rhw;
		verts[8 + 3].z = z; 
		verts[8 + 3].tu = 1; 
		verts[8 + 3].tv = 1;
		verts[8 + 3].rhw = rhw;

		m_VertexBuffer->Unlock();


		left0 = -(float)(m_iBackBuffWidth) / 2;
		top0 = -(float)(m_iBackBuffHeight) / 2;
		right0 = left0 + (m_iBackBuffWidth)-1;
		bottom0 = top0 + (m_iBackBuffHeight)-1;

		xTrans = (m_iBackBuffWidth)/2;
		yTrans = (m_iBackBuffHeight)/2;
//	float left1, top1, right1, bottom1;
//	float left2, top2, right2, bottom2;
		Reset(pEngine);

	}
	return S_OK;
}

HRESULT __stdcall CNStimGratingPatch::Reset(INStimEngine* pEngine)  {
	CNStimPatch::Reset(pEngine);
	m_CurPhase = 0;
	pEngine->GetFrameRate(&m_FramesPerSec);
	if ((*m_pTfCycPerSec) > 0) {
		double framerate;
		pEngine->GetFrameRate(&framerate);
		m_iNumFrames = framerate / (*m_pTfCycPerSec);
	}
	else {
		m_iNumFrames = 1;
	}
	m_iCurrentFrame = 0;
	m_iIncDir = 1;
	biDirCtr = 1;
	return S_OK;
}

HRESULT __stdcall CNStimGratingPatch::SetParam(unsigned char* pParamName, unsigned char* pParamValue) {
	CNStimPatch::SetParam(pParamName, pParamValue);

	if ((*m_pBlitAngle3)<0)
		(*m_pBlitAngle3) = (*m_pBlitAngle3)+360;
	if ((*m_pBlitAngle3)>=360) {
		(*m_pBlitAngle3) = (*m_pBlitAngle3)-360*((int)((*m_pBlitAngle3)/360));
	}
	if ((strcmpi((char*)pParamName, "Width") == 0) ||
		(strcmpi((char*)pParamName, "Height") == 0) ||
		(strcmpi((char*)pParamName, "Alpha") == 0) ||
		(strcmpi((char*)pParamName, "Shape") == 0) ||
		(strcmpi((char*)pParamName, "Contrast") == 0) ||
		(strcmpi((char*)pParamName, "SpatialFrequency") == 0) )
	{
		if (m_pEngine)
			Init(m_pEngine);
	}
	return S_OK;
}
