// CNStimOIGratingPatch.cpp: implementation of the CNStimOIGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimOIGratingPatch.h"
#include "CDirect3DDevice.h"
#include "CNStimFloatPatchParam.h"
#include "CNStimEngine.h"

const char* CNStimOIGratingPatch::m_pPatchType = "OIGrating";
float* CNStimOIGratingPatch::sineTable = 0;
float* CNStimOIGratingPatch::cosineTable = 0;
bool CNStimOIGratingPatch::lutInitialized = false;


#define pi	3.1415926535

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimOIGratingPatch::CNStimOIGratingPatch()
{
	m_pCondDesc = 0;
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
	pIntParam->SetParamName((unsigned char*)"NumCond");
	m_pNumCond = pIntParam->GetParamDataPtr();

	m_pStimSeqArray = new CNStimIntArrayPatchParam; m_ParamList.AddTail(m_pStimSeqArray);
	m_pStimSeqArray->SetParamName((unsigned char*)"StimSeq");
	m_pStimSequence = m_pStimSeqArray->GetParamDataPtr();
	m_pStimSeqLen = m_pStimSeqArray->GetParamSizePtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Shape");
	m_pShape = pIntParam->GetParamDataPtr();
	
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Width");
	m_pWidth = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Height");
	m_pHeight = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");
/*
	m_pStimSeqArray = new CNStimIntArrayPatchParam;
	m_ParamList.AddTail(m_pStimSeqArray);
	m_pStimSeqArray->SetParamName((unsigned char*)"StimSequence");
	m_pStimSequence = m_pStimSeqArray->GetParamDataPtr();
	m_pStimSeqLen = m_pStimSeqArray->GetParamSizePtr();
*/
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"FramesPerCond");
	m_pFramesPerCond = pIntParam->GetParamDataPtr();
	(*m_pFramesPerCond) = 72;

/*	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"SpatialPhase");
	m_pSpatialPhase = pFloatParam->GetParamDataPtr();
	(*m_pSpatialPhase) = 0;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"TemporalFrequency");
	m_pTfCycPerSec = pFloatParam->GetParamDataPtr();
	(*m_pTfCycPerSec) = 4;
*/
	m_pEngine = 0;
	m_pDevice = 0;
	m_bCondSwitched = true;
}

CNStimOIGratingPatch::~CNStimOIGratingPatch()
{

}


HRESULT CNStimOIGratingPatch::AdvanceFrame(int numFrames) {
	for (int i = 0; i < numFrames; i++) {
		AdvanceCondFrame(&m_pCondDesc[(*m_pStimSequence)[m_iStimSeqMarker]-1]);
		m_iNumFramesInCurCond++;
		if (m_iNumFramesInCurCond >= (*m_pFramesPerCond)) {
			m_iNumFramesInCurCond = 0;
			m_bCondSwitched = true;
			m_iStimSeqMarker++;
			if (m_iStimSeqMarker >= (*m_pStimSeqLen)) {
				// done stimulating, so restart from the beginning
				m_iStimSeqMarker = 0;
			}
			ResetCond(&m_pCondDesc[(*m_pStimSequence)[m_iStimSeqMarker]-1]);
		}
	}
	return S_OK;
}

void CNStimOIGratingPatch::AdvanceCondFrame(CondDesc* pCond) {
	if ((*pCond->m_pBiDir))
	{
		pCond->m_CurPhase = pCond->m_CurPhase + (double)pCond->m_iIncDir*((double)1/m_FramesPerSec)*(*pCond->m_pTfCycPerSec);
		if (pCond->m_CurPhase > 1.0) {
			pCond->m_CurPhase = 2-pCond->m_CurPhase;
			pCond->m_iIncDir = -pCond->m_iIncDir;
		}
		else if (pCond->m_CurPhase < 0) {
			pCond->m_CurPhase = -pCond->m_CurPhase;
			pCond->m_iIncDir = -pCond->m_iIncDir;
		}
	}
	else
	{
		pCond->m_CurPhase = pCond->m_CurPhase + ((double)1/m_FramesPerSec)*(*pCond->m_pTfCycPerSec);
		if (pCond->m_CurPhase > 1.0) {
			pCond->m_CurPhase = pCond->m_CurPhase - floor(pCond->m_CurPhase);
		}
	}
	/*
	if ((*pCond->m_pBiDir))
	{
		pCond->m_iCurrentFrame = (pCond->m_iCurrentFrame+pCond->m_iIncDir);
		do {

		if (pCond->m_iCurrentFrame <= 0) {
			pCond->m_iIncDir = 1;
			pCond->m_iCurrentFrame = -pCond->m_iCurrentFrame;
		}
		else if (pCond->m_iCurrentFrame >= (*pCond->m_pBiDir)*pCond->m_iNumFrames) {
			pCond->m_iIncDir = -1;
			pCond->m_iCurrentFrame = (((*pCond->m_pBiDir)*2)*pCond->m_iNumFrames - pCond->m_iCurrentFrame - 1);
		}
		}
		while ((pCond->m_iCurrentFrame < 0) || ((pCond->m_iCurrentFrame >= (*pCond->m_pBiDir)*pCond->m_iNumFrames)));
	}
	else
	{
		pCond->m_iCurrentFrame = (pCond->m_iCurrentFrame+1)%(pCond->m_iNumFrames);
	}
	*/
}


HRESULT CNStimOIGratingPatch::Draw(INStimEngine* pEngine) {
	DrawCond(pEngine, &m_pCondDesc[(*m_pStimSequence)[m_iStimSeqMarker]-1], m_bCondSwitched);
	m_bCondSwitched = false;
	AdvanceFrame(1);
	return S_OK;
}

void CNStimOIGratingPatch::DrawCond(INStimEngine* pEngine, CondDesc* pCond, bool switchCond) {

	IDirect3DDevice9* pDevice;
	pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	if (pDevice)
	{
		int vpCX, vpCY;
		int bkCX, bkCY;
//		int iFrameShift = (int)(((((pCond->m_iCurrentFrame%pCond->m_iNumFrames) * (*pCond->m_pSfPixPerCycle) / pCond->m_iNumFrames) + 
//			((*pCond->m_pSpatialPhase)*(*pCond->m_pSfPixPerCycle))/360)));
		int iFrameShift;
		double dFrameShift = ((*pCond->m_pSfPixPerCycle)*(pCond->m_CurPhase - 0.5));
		iFrameShift = (int)dFrameShift;
		if (dFrameShift > 0) {
			if ((dFrameShift - floor(dFrameShift)) > 0.5)
				iFrameShift++;
		}
		else {
			if ((dFrameShift - floor(dFrameShift)) < 0.5)
				iFrameShift--;
		}

#ifdef _DEBUG
		char temp[512];
		sprintf(temp, "%0.2f\r\n", pCond->m_CurPhase);
		OutputDebugString(temp);
#endif

		pEngine->GetViewportCenter(&vpCX, &vpCY);
		vpCX = vpCX + (*pCond->m_pCenterX) + (*pCond->m_pXDisplacement);
		bkCX = floor((m_iBackBuffWidth - 2*(iFrameShift*pCond->m_dOrCosine))/2);
		vpCY = vpCY + (*pCond->m_pCenterY) + (*pCond->m_pYDisplacement);
		bkCY = floor((m_iBackBuffHeight - 2*(iFrameShift*pCond->m_dOrSine))/2);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// From back buffer to front buffer
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		CUSTOMVERTEX* verts = 0;
		m_VertexBuffer->Lock(0, 0, (void**)(&verts), 0);

		
		// map from back to screen
		verts[0].x = left0 + vpCX; 
		verts[0].y = top0 + vpCY;
		verts[1].x = right0 + vpCX; 
		verts[1].y = top0 + vpCY;
		verts[2].x = left0 + vpCX; 
		verts[2].y = bottom0 + vpCY;
		verts[3].x = right0 + vpCX; 
		verts[3].y = bottom0 + vpCY; 

		// map from texture to back
		verts[4].x = bkleft0 + bkCX; 
		verts[4].y = bktop0 + bkCY;
		verts[5].x = bkright0 + bkCX; 
		verts[5].y = bktop0 + bkCY;
		verts[6].x = bkleft0 + bkCX; 
		verts[6].y = bkbottom0 + bkCY;
		verts[7].x = bkright0 + bkCX; 
		verts[7].y = bkbottom0 + bkCY; 
		m_VertexBuffer->Unlock();


		IDirect3DSurface9* pds;
		LPDIRECT3DSURFACE9 pRTOld = NULL;		// old render target
		LPDIRECT3DSURFACE9 pDSOld = NULL;		// old depth stensil
		IDirect3DTexture9* tex;
		HRESULT hr;
		if (switchCond) {
			m_GratingBuff->GetSurfaceLevel(0,&pds);
			hr = pDevice->UpdateSurface(pCond->surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}

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
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

		// Finally, render onto the screen.  In this stage, we use alpha blending
		// to blend the src onto the screen
		hr = pDevice->SetRenderTarget( 0, pRTOld); 
		hr = pDevice->SetDepthStencilSurface(pDSOld);

		tex = m_BackBuff.GetDirect3DTexture();
		hr = pDevice->SetTexture(0, tex);
		hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
		hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		hr = pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}	
}

void CNStimOIGratingPatch::ResetCond(CondDesc* pCond) {
	pCond->m_CurPhase = 0;
	/*
	if ((*pCond->m_pTfCycPerSec) > 0) {
		pCond->m_iNumFrames = framerate / (*pCond->m_pTfCycPerSec);
	}
	else {
		pCond->m_iNumFrames = 1;
	}
	pCond->m_iCurrentFrame = 0;
	pCond->m_iIncDir = 1;
	*/
}

void CNStimOIGratingPatch::InitCond(INStimEngine* pEngine, CondDesc* pCond) {
	IDirect3DDevice9* pDevice;
	pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	if (pDevice)
	{
		CDirect3DDevice Device = pDevice;
		int x, y;
		D3DLOCKED_RECT lr;
		pCond->m_iGratingBuffWidth = m_iGratingBuffWidth;//(*m_pWidth) + (*pCond->m_pSfPixPerCycle);
		pCond->m_iGratingBuffHeight = m_iGratingBuffHeight;//(*m_pHeight);
		pCond->surf = Device.CreateSurface(pCond->m_iGratingBuffWidth,pCond->m_iGratingBuffHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
		pCond->surf->LockRect(&lr,0,0);
		char* temp = (char*)lr.pBits;
		pCond->m_dOrCosine = -cosineTable[(int)floor(LUT_RESOLUTION*(*pCond->m_pOrientation))];
		pCond->m_dOrSine = -sineTable[(int)floor(LUT_RESOLUTION*(*pCond->m_pOrientation))];
		////////////////////////////////////////////////////////////////////////////////////////////////////
		// draw the grating onto temp
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int v;
		double d, sineAngle, sine;
//		OutputDebugString("==========\r\n");
		for (y = 0; y < (pCond->m_iGratingBuffHeight); y++)
		{
			for (x = 0; x < (pCond->m_iGratingBuffWidth); x++) {
				d = x * pCond->m_dOrCosine + y * pCond->m_dOrSine;
				sineAngle = ((double)d * 360) / (double)(*pCond->m_pSfPixPerCycle);
				sineAngle = sineAngle + (*pCond->m_pSpatialPhase);
				while (sineAngle < 0) {
					sineAngle = sineAngle + 360;
				}
				if (sineAngle >= 360)
				{
					sineAngle = sineAngle - 360*(int)(sineAngle/360);
				}
				sine = sineTable[(int)floor(sineAngle*LUT_RESOLUTION)];
				if (sine > 0)
					v = (int)floor(sine*(*pCond->m_pContrast) + (*pCond->m_pLuminance) + .5);
				else
					v = (int)floor(sine*(*pCond->m_pContrast) + (*pCond->m_pLuminance) - .5);
				if (v < 0)
					v = 0;
				if (v > 255)
					v = 255;
				((DWORD*)temp)[x] = v + (v << 8) + (v << 16) + (0xff<<24);
			}
//			char tj[512];
//			sprintf(tj, "%0.2f, %0.2f, %0.2f, %d\r\n",d, sineAngle, sine, v);
//			OutputDebugString(tj);
			temp = temp + lr.Pitch;
		}
//		OutputDebugString("==========\r\n");
		pCond->surf->UnlockRect();

	}
}

HRESULT CNStimOIGratingPatch::Init(INStimEngine* pEngine) {
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
		pEngine->GetFrameRate(&framerate);

		CDirect3DSurface surf;
		int wnb;
		int hnb;
		char* temp;
		int x, y;
		D3DLOCKED_RECT lr;

		double maxPixPerCycle = 0;
		int i;
		for (i = 0; i < (*m_pNumCond); i++) {
			if (maxPixPerCycle < (*m_pCondDesc[i].m_pSfPixPerCycle)) {
				maxPixPerCycle = (*m_pCondDesc[i].m_pSfPixPerCycle);
			}
		}
		maxPixPerCycle += 1;
		m_iGratingBuffWidth = (*m_pWidth) + (int)maxPixPerCycle;
		m_iGratingBuffHeight = (*m_pHeight) + (int)maxPixPerCycle;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		// create grating buffer
		////////////////////////////////////////////////////////////////////////////////////////////////////
		wnb = 1; hnb = 1;
		while (m_iGratingBuffWidth > (1<<wnb))
			wnb++;
		while (m_iGratingBuffHeight > (1<<hnb))
			hnb++;

		m_iGratingBuffWidth = (1<<wnb);
		m_iGratingBuffHeight = (1<<hnb);

		m_GratingBuff = Device.CreateTexture(m_iGratingBuffWidth, m_iGratingBuffHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_GratingBuff.IsNull()) {
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

		memset(temp, 0, lr.Pitch * m_iBackBuffHeight);
		
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
						((DWORD*)temp)[x] = 0xffffffff;
					else
						((DWORD*)temp)[x] = 0;
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
					((DWORD*)temp)[x] = 0xffffffff;

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

		for (i = 0; i < (*m_pNumCond); i++) {
			InitCond(pEngine, &m_pCondDesc[i]);
		}


		///////////
#define	NVERTICES		8
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
		verts[0].x = 0;
		verts[0].y = 0;
		verts[1].z = z; 
		verts[1].tu = 1; 
		verts[1].tv = 0;
		verts[1].rhw = rhw;
		verts[1].x = (*m_pWidth);
		verts[1].y = 0;
		verts[2].z = z; 
		verts[2].tu = 0; 
		verts[2].tv = 1;
		verts[2].rhw = rhw;
		verts[2].x = 0;
		verts[2].y = (*m_pHeight);
		verts[3].z = z; 
		verts[3].tu = 1; 
		verts[3].tv = 1;
		verts[3].rhw = rhw;
		verts[3].x = (*m_pWidth);
		verts[3].y = (*m_pHeight);
		verts[4].z = z; 
		verts[4].tu = 0; 
		verts[4].tv = 0;
		verts[4].rhw = rhw;
		verts[4].x = 0;
		verts[4].y = 0;
		verts[5].z = z; 
		verts[5].tu = 1; 
		verts[5].tv = 0;
		verts[5].rhw = rhw;
		verts[5].x = (*m_pWidth);
		verts[5].y = 0;
		verts[6].z = z; 
		verts[6].tu = 0; 
		verts[6].tv = 1;
		verts[6].rhw = rhw;
		verts[6].x = 0;
		verts[6].y = (*m_pHeight);
		verts[7].z = z; 
		verts[7].tu = 1; 
		verts[7].tv = 1;
		verts[7].rhw = rhw;
		verts[7].x = (*m_pWidth);
		verts[7].y = (*m_pHeight);

		m_VertexBuffer->Unlock();
		left0 = -(float)(m_iBackBuffWidth) / 2;
		top0 = -(float)(m_iBackBuffHeight) / 2;
		right0 = left0 + (m_iBackBuffWidth)-1;
		bottom0 = top0 + (m_iBackBuffHeight)-1;
		bkleft0 = -(float)(m_iGratingBuffWidth) / 2;
		bktop0 = -(float)(m_iGratingBuffHeight) / 2;
		bkright0 = bkleft0 + (m_iGratingBuffWidth)-1;
		bkbottom0 = bktop0 + (m_iGratingBuffHeight)-1;

		Reset(pEngine);
	}
	return S_OK;
}

HRESULT CNStimOIGratingPatch::Reset(INStimEngine* pEngine) {
	CNStimPatch::Reset(pEngine);
	pEngine->GetFrameRate(&m_FramesPerSec);
	for (int i = 0; i < (*m_pNumCond); i++) {
		ResetCond(&m_pCondDesc[i]);
	}
	m_iStimSeqMarker = 0;
	m_iNumFramesInCurCond = 0;
	return S_OK;
}

HRESULT CNStimOIGratingPatch::SetParam(unsigned char* pParamName, unsigned char* pParamValue) {
	if (strcmpi((const char*)pParamName, "NumCond") == 0) {
		CNStimPatch::SetParam(pParamName, pParamValue);
		m_pCondDesc = new CondDesc[(*m_pNumCond)];
		memset(m_pCondDesc, 0, sizeof(*m_pCondDesc)*(*m_pNumCond));
		CNStimIntPatchParam* pIntParam;
		CNStimFloatPatchParam* pFloatParam;
		char paramName[512];
		for (int i = 0; i < (*m_pNumCond); i++) {
			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "SpatialFrequency_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pSfPixPerCycle = pFloatParam->GetParamDataPtr();
			pFloatParam->SetUnit("ppc");

			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "BiDir_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pBiDir = pIntParam->GetParamDataPtr();

			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "CenterX_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pCenterX = pIntParam->GetParamDataPtr();
			(*m_pCondDesc[i].m_pCenterX) = (*m_pCenterX);
			pIntParam->SetUnit("pix");

			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "CenterY_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pCenterY = pIntParam->GetParamDataPtr();
			(*m_pCondDesc[i].m_pCenterY) = (*m_pCenterY);
			pIntParam->SetUnit("pix");

			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "Alpha_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pAlpha = pIntParam->GetParamDataPtr();

			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "dx_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pXDisplacement = pIntParam->GetParamDataPtr();
			pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
			sprintf(paramName, "dy_%d", i+1);
			pIntParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pYDisplacement = pIntParam->GetParamDataPtr();
			(*m_pCondDesc[i].m_pXDisplacement) = 0;
			(*m_pCondDesc[i].m_pYDisplacement) = 0;

			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "SpatialPhase_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pSpatialPhase = pFloatParam->GetParamDataPtr();
			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "TemporalFrequency_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pTfCycPerSec = pFloatParam->GetParamDataPtr();
			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "Orientation_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pOrientation = pFloatParam->GetParamDataPtr();
			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "Contrast_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pContrast = pFloatParam->GetParamDataPtr();
			pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
			sprintf(paramName, "Luminance_%d", i+1);
			pFloatParam->SetParamName((unsigned char*)paramName);
			m_pCondDesc[i].m_pLuminance = pFloatParam->GetParamDataPtr();

		}
	}
	else 
		CNStimPatch::SetParam(pParamName, pParamValue);
	return S_OK;
}
