// CNStimTestGratingPatch.cpp: implementation of the CNStimTestGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimTestGratingPatch.h"
#include "CDirect3DDevice.h"
#include "CNStimFloatPatchParam.h"

char* CNStimTestGratingPatch::m_pPatchType = "tgrating";


#define pi	3.1415926535
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimTestGratingPatch::CNStimTestGratingPatch()
{
	CNStimIntPatchParam* pIntParam;
	CNStimFloatPatchParam* pFloatParam;
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Width");
	m_pWidth = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Height");
	m_pHeight = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Shape");
	m_pShape = pIntParam->GetParamDataPtr();
	(*m_pShape) = 1;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"SpatialFrequency");
	m_pSfPixPerCycle = pIntParam->GetParamDataPtr();
	(*m_pSfPixPerCycle) = 50;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Alpha");
	m_pAlpha = pIntParam->GetParamDataPtr();
	(*m_pAlpha) = 255;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"BiDir");
	m_pBiDir = pIntParam->GetParamDataPtr();
	(*m_pBiDir) = 0;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"SpatialPhase");
	m_pSpatialPhase = pFloatParam->GetParamDataPtr();
	(*m_pSpatialPhase) = 0;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"TemporalFrequency");
	m_pTfCycPerSec = pFloatParam->GetParamDataPtr();
	(*m_pTfCycPerSec) = 4;

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"BlitAngle2");
	m_pBlitAngle2 = pFloatParam->GetParamDataPtr();
	(*m_pBlitAngle2) = 0;

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
}

CNStimTestGratingPatch::~CNStimTestGratingPatch()
{
}

HRESULT __stdcall CNStimTestGratingPatch::AdvanceFrame(int numFrames)
{
	if ((*m_pBiDir))
	{
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
	}
	else
	{
		m_iCurrentFrame = (m_iCurrentFrame+numFrames)%(m_iNumFrames);
	}
//	m_iCurrentFrame = (m_iCurrentFrame+numFrames)%(m_iNumFrames);
	return S_OK;
}

// Our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    FLOAT rhw;
//    DWORD color;
    FLOAT tu, tv;   // The texture coordinates
};
#include "CNStimEngine.h"
//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW	| D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)
#include <stdio.h>
HRESULT __stdcall CNStimTestGratingPatch::Draw(INStimEngine* pEngine)
{
	int iFrame = (m_iCurrentFrame)%(m_iNumFrames);
/*char junk[512];

	if (((CNStimEngine*)pEngine)->m_iState == GE_STIMULATING) {
	sprintf(junk, "patch %s iFrame = %d m_iNumFrames = %d\r\n", m_pName, iFrame, m_iNumFrames);
	OutputDebugString(junk);
	}
*/
	int texWidth = (*m_pSfPixPerCycle);
	int iFrameShift = (int)((iFrame * texWidth / m_iNumFrames) + ((*m_pSpatialPhase)*texWidth)/360);
	void* pVbData = 0;
	m_VertexBuffer->Lock(0, 0, &pVbData, 0);
	CUSTOMVERTEX* verts = (CUSTOMVERTEX*)pVbData;

		float aleft   = +iFrameShift-(float)(m_iBackBuffWidth) / 2 - texWidth;
		float atop    = -(float)(m_iBackBuffHeight) / 2 ;
		float aright  = aleft + (m_iBackBuffWidth)-1;
		float abottom = atop + (m_iBackBuffHeight)-1;

		int i =0;
	double theta0 = ((float)(*m_pBlitAngle)*pi)/180;
	double theta1 = ((float)(*m_pBlitAngle2)*pi)/180;

	int vpCX, vpCY;
	pEngine->GetViewportCenter(&vpCX, &vpCY);

	verts[3*i + 0].x = aleft * cos(theta0) - atop * sin(theta0) + (*m_pCenterX) + vpCX; verts[3*i + 0].y = aleft * sin(theta0) + atop * cos(theta0)+ (*m_pCenterY) + vpCY;
	verts[3*i + 1].x = aright * cos(theta0) - atop * sin(theta0) + (*m_pCenterX) + vpCX ; verts[3*i + 1].y = aright * sin(theta0) + atop * cos(theta0)+ (*m_pCenterY) + vpCY;
	verts[3*i + 2].x = aleft * cos(theta0) - abottom * sin(theta0) + (*m_pCenterX) + vpCX ; verts[3*i + 2].y = aleft * sin(theta0) + abottom * cos(theta0)+ (*m_pCenterY) + vpCY;
	verts[3*i + 3].x = aright * cos(theta0) - abottom * sin(theta0) + (*m_pCenterX) + vpCX ; verts[3*i + 3].y = aright * sin(theta0) + abottom * cos(theta0)+ (*m_pCenterY) + vpCY; 
	i = 2;

	float xTrans = (-((float)iFrameShift)+texWidth);//*cos(0);
	float yTrans = 0;//-((float)iFrameShift+texWidth)*sin(0);
	aleft = -(*m_pWidth)/2;
	aright = aleft + (*m_pWidth);
	atop = -(*m_pHeight)/2;
	abottom = atop+(*m_pHeight);
	verts[3*i + 0].x = aleft * cos(theta1) - atop * sin(theta1) + xTrans + (m_iBackBuffWidth)/2; verts[3*i + 0].y = aleft * sin(theta1) + atop * cos(theta1) + yTrans + (m_iBackBuffHeight)/2;
	verts[3*i + 1].x = aright * cos(theta1) - atop * sin(theta1) + xTrans + (m_iBackBuffWidth)/2 ; verts[3*i + 1].y = aright * sin(theta1) + atop * cos(theta1) + yTrans + (m_iBackBuffHeight)/2;
	verts[3*i + 2].x = aleft * cos(theta1) - abottom * sin(theta1) + xTrans + (m_iBackBuffWidth)/2 ; verts[3*i + 2].y = aleft * sin(theta1) + abottom * cos(theta1) + yTrans + (m_iBackBuffHeight)/2;
	verts[3*i + 3].x = aright * cos(theta1) - abottom * sin(theta1) + xTrans + (m_iBackBuffWidth)/2 ; verts[3*i + 3].y = aright * sin(theta1) + abottom * cos(theta1) + yTrans + (m_iBackBuffHeight)/2;

	m_VertexBuffer->Unlock();


	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	IDirect3DTexture9* oneCycle = m_OneCycle.GetDirect3DTexture();
	CDirect3DDevice Device = pDevice;

	IDirect3DTexture9* tex = m_OneCycle.GetDirect3DTexture();
	HRESULT hr;
    LPDIRECT3DSURFACE9 pRTOld = NULL;
	IDirect3DSurface9* pds;
	hr = m_BackBuff->GetSurfaceLevel(0,&pds);

    hr = pDevice->GetRenderTarget( 0, &pRTOld );
	hr = pDevice->SetRenderTarget( 0, pds);
	pds->Release();

/*

	D3DXMATRIX matWorld;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matRotation;
	D3DXMATRIX projMatrix;

	//	float v = 100*((float)(rand()  % 100))/ 100;
    D3DXMatrixTranslation( &matTranslation, 0.0f, 0.0f, 0.0f );
    matWorld = matTranslation;
	D3DXMATRIX test;
    hr = pDevice->GetTransform( D3DTS_WORLD, &test );
    hr = pDevice->GetTransform( D3DTS_PROJECTION, &test );
    hr = pDevice->GetTransform( D3DTS_VIEW , &test );
//    hr = pDevice->SetTransform( D3DTS_WORLD, &matWorld );
   // hr = pDevice->SetTransform( D3DTS_VIEW, &matWorld );
   // hr = pDevice->SetTransform( D3DTS_PROJECTION, &matWorld );
    hr = pDevice->GetTransform( D3DTS_WORLD, &test );

*/

/*
	// First, draw the grating onto the back buffer
	pDevice->SetTexture(0, tex);
    hr = pDevice->SetStreamSource( 0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );
    hr = pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLENDALPHA,  D3DBLEND_ZERO);
	hr = pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);  

    hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 12, (2*nx*ny));

	// Now we want to change the alpha of the local back buffer while keeping the 
	// RGB components the same by using separate alpha blending.
	tex = m_ShapeMap.GetDirect3DTexture();
	pDevice->SetTexture(0, tex);

	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLENDALPHA,  D3DBLEND_ONE);
	hr = pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);  
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 6, 2 );

	// Finally, render onto the screen.  In this stage, we use alpha blending
	// to blend the src onto the screen
	hr = pDevice->SetRenderTarget( 0, pRTOld); 
	tex = m_BackBuff.GetDirect3DTexture();
	hr = pDevice->SetTexture(0, tex);
	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    hr = pDevice->SetStreamSource( 0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );
	hr = pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    hr = pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
*/
	// NEW CODE DOESN"T REQUIRE SEPARATE BLENDING

	// First, draw the grating onto the back buffer
	pDevice->SetTexture(0, tex);
    hr = pDevice->SetStreamSource( 0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );
    hr = pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);  

    hr = pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 12, (2*nx*ny));

	// Now we want to change the alpha of the local back buffer while keeping the 
	// RGB components the same by adding a map of appropriate alpha and zero RGB
	tex = m_ShapeMap.GetDirect3DTexture();
	pDevice->SetTexture(0, tex);

	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ONE);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);  
	pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 6, 2 );

	// Finally, render onto the screen.  In this stage, we use alpha blending
	// to blend the src onto the screen
	hr = pDevice->SetRenderTarget( 0, pRTOld); 
	tex = m_BackBuff.GetDirect3DTexture();
//	tex = m_ShapeMap.GetDirect3DTexture();
	hr = pDevice->SetTexture(0, tex);
	hr = pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	hr = pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    hr = pDevice->SetStreamSource( 0, m_VertexBuffer.GetDirect3DVertexBuffer(), 0, sizeof(CUSTOMVERTEX) );
	hr = pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
    hr = pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	// move to next frame
	AdvanceFrame(1);
	return S_OK;
}

HRESULT __stdcall CNStimTestGratingPatch::Init(INStimEngine* pEngine)
{
	CNStimPatch::Init(pEngine);

	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	CDirect3DDevice Device = pDevice;
	if (pDevice)
	{

		pDevice->Release();

		int texWidth = (*m_pSfPixPerCycle);
		int texHeight = 4;

		int wnb = 1, wnh = 1;
		while (texWidth > (1<<wnb))
			wnb++;
		texWidth = (1<<wnb);

		CDirect3DSurface surf = Device.CreateSurface(texWidth,texHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);

		D3DLOCKED_RECT lr;

		surf->LockRect(&lr,0,0);
		char* temp = (char*)lr.pBits;


		// draw the grating onto temp
		for (int y = 0; y < texHeight; y++)
		{
			for (int x = 0; x < texWidth; x++)
			{ 
				int dx = (x - texWidth / 2);
				int dy = (y - texHeight / 2);
				double sine = sin((double)x * 2 * pi / (double)(*m_pSfPixPerCycle));
				int v;
				if (sine > 0)
					v = (int)floor(sine*(*m_pContrast) + (*m_pLuminance) + .5);
				else
					v = (int)floor(sine*(*m_pContrast) + (*m_pLuminance) - .5);
				((DWORD*)temp)[x] = v + (v << 8) + (v << 16);//+(0x000000ff << 24);
			}
			temp = temp + lr.Pitch;
		}
		surf->UnlockRect();
		
		m_OneCycle = Device.CreateTexture(texWidth,texHeight,0,D3DUSAGE_AUTOGENMIPMAP,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_OneCycle.IsNull()) {
			IDirect3DSurface9* pds;
			m_OneCycle->GetSurfaceLevel(0,&pds);
			HRESULT hr= Device->UpdateSurface(surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}
		else
			MessageBeep(-1);


		m_iShapeWidth = (*m_pWidth);
		m_iShapeHeight = (*m_pHeight);
		wnb = 1; wnh = 1;
		while (m_iShapeWidth > (1<<wnb))
			wnb++;
		while (m_iShapeHeight > (1<<wnh))
			wnh++;

		m_iShapeWidth = (1<<wnb);
		m_iShapeHeight = (1<<wnh);


		surf = Device.CreateSurface(m_iShapeWidth, m_iShapeHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
//		surf = Device.CreateSurface((*m_pWidth),(*m_pHeight),D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);

		surf->LockRect(&lr,0,0);
		temp = (char*)lr.pBits;

		memset(temp, 0, lr.Pitch*m_iShapeHeight);

		if ((*m_pShape) == 1) {
			// eliptical shape.  rasterize a circle
			if ((*m_pHeight) < (*m_pWidth)) {
				// traverse in the x direction
			}
			else {
				// traverse in the y direction
				char* top;
				char* bottom;
				int w = (*m_pWidth);
				int h = (*m_pHeight);
				int d = (h*h+4*w*w-2*w*h*h)*10;
				int yfp = 0;
				int xfp = (w-1)*10/2;		// fixed pt math
				if (w%2) {
					top = temp + lr.Pitch * ((*m_pHeight)/2);
					bottom = top + lr.Pitch;
				}
				else {
					top = temp + lr.Pitch * ((*m_pHeight)/2);
					bottom = top;
				}
				while (xfp*h*h >= w*w*yfp) {// (yfp < ((*m_pHeight)/2)*10) {
					if (d < 0) {
						d = d + 4*(2*yfp-3*10)*w*w;
					}
					else {
						// d >= 0
						d = d + (4*h*h*(-2*xfp+4*10)+4*w*w*(2*yfp-3*10));
						xfp = xfp - 10;
					}
					for (int x = (w * 10/2 - xfp)/10; x < (w * 10/2 + xfp)/10; x++) {
						((DWORD*)top)[x] = ((*m_pAlpha)<<24);// + 0xffffff;
						((DWORD*)bottom)[x] = ((*m_pAlpha)<<24);// + 0xffffff;
					}
					// rasterize the points from -x to x with y = y
					yfp = yfp + 10;
					top = top - lr.Pitch;
					bottom = bottom + lr.Pitch;
				}

				xfp = 0;
				yfp = (h-1)*10/2;
				if (w%2) {
					top = temp + 4*(w/2);
					bottom = temp + 4*((w/2)+1);
				}
				else {
					top = temp + 4*(w/2);
					bottom = temp + 4*((w/2));
				}

				while (xfp*h*h <= w*w*yfp) {// (yfp < ((*m_pHeight)/2)*10) {
					if (d < 0) {
						d = d + 4*(2*xfp-3*10)*h*h;
					}
					else {
						// d >= 0
						d = d + (4*w*w*(-2*yfp+4*10)+4*h*h*(2*xfp-3*10));
						yfp = yfp - 10;
					}
					for (int y = (h * 10/2 - yfp)/10; y < (h * 10/2 + yfp)/10; y++) {
						((DWORD*)(top+y*lr.Pitch))[0] = ((*m_pAlpha)<<24);// + 0xffffff;
						((DWORD*)(bottom+y*lr.Pitch))[0] = ((*m_pAlpha)<<24);// + 0xffffff;
					}
					// rasterize the points from -x to x with y = y
					xfp = xfp + 10;
					top = top - 4;
					bottom = bottom + 4;
				}
			}
		}
		else
		{
			// square shape, so no rasterization required
			for (y = 0; y < (*m_pHeight); y++)
			{
				for (int x = 0; x < (*m_pWidth); x++)
					((DWORD*)temp)[x] = ((*m_pAlpha)<<24);// + 0xffffff;

				temp = temp + lr.Pitch;
			}
		}
		surf->UnlockRect();
		m_ShapeMap = Device.CreateTexture(m_iShapeWidth, m_iShapeHeight,0,D3DUSAGE_AUTOGENMIPMAP,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
//		m_ShapeMap = Device.CreateTexture((*m_pWidth),(*m_pHeight),1,D3DUSAGE_AUTOGENMIPMAP,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_ShapeMap.IsNull()) {
			IDirect3DSurface9* pds;
			m_ShapeMap->GetSurfaceLevel(0,&pds);
			HRESULT hr= Device->UpdateSurface(surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}
		else
			MessageBeep(-1);

		m_iBackBuffWidth = max(*m_pWidth, *m_pHeight)+3*texWidth;
		m_iBackBuffHeight = max(*m_pWidth, *m_pHeight)+3*texWidth;
		wnb = 1; wnh = 1;
		while (m_iBackBuffWidth > (1<<wnb))
			wnb++;
		while (m_iBackBuffHeight > (1<<wnh))
			wnh++;

		m_iBackBuffWidth = (1<<wnb);
		m_iBackBuffHeight = (1<<wnh);

		surf = Device.CreateSurface(m_iBackBuffWidth,m_iBackBuffHeight,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
		surf->LockRect(&lr,0,0);
		temp = (char*)lr.pBits;
		
		// draw the grating onto temp
		for (y = 0; y < (*m_pHeight); y++)
		{
			memset(temp, 0, (*m_pWidth)*4);
			temp = temp + lr.Pitch;
		}
		surf->UnlockRect();

		m_BackBuff = Device.CreateTexture(m_iBackBuffWidth, m_iBackBuffHeight,1,D3DUSAGE_AUTOGENMIPMAP|D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT);
		if (!m_BackBuff.IsNull()) {
			IDirect3DSurface9* pds;
			m_BackBuff->GetSurfaceLevel(0,&pds);
			HRESULT hr= Device->UpdateSurface(surf.GetDirect3DSurface(), 0, pds, 0);
			pds->Release();
		}
		else
			MessageBeep(-1);

		nx = (int)ceil((double)(m_iBackBuffWidth) / texWidth) + 2;
		ny = (int)ceil((double)(m_iBackBuffHeight) / texHeight);

		m_VertexBuffer = Device.CreateVertexBuffer((6*nx*ny+12)*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT);
		void* pVbData = 0;
		m_VertexBuffer->Lock(0, 0, &pVbData, 0);

		float left   = 0;//-((iFrame * texWidth) / m_iNumFrames);
		float top    = 0; // + (*m_pCenterY) - (*m_pHeight);
		float z = 0;
		float right  = left + texWidth;
		float bottom = top + texHeight;
		DWORD col = 0xffffffff;
		float rhw = 1;//1.0f / (z * 990.0f + 10.0f);

		float theta = 0;

		CUSTOMVERTEX* verts = new CUSTOMVERTEX[nx*ny*6+12];
		int i = 0;

		float aleft   = -(float)(*m_pWidth) / 2 + (*m_pCenterX) ;
		float atop    = -(float)(*m_pHeight) / 2 + (*m_pCenterY) ;
		float aright  = aleft + (*m_pWidth) - 1;
		float abottom = atop + (*m_pHeight) - 1;
		
			verts[3*i + 0].x = aleft; verts[3*i + 0].y = atop; verts[3*i + 0].z = z; verts[3*i + 0].tu = 0; verts[3*i + 0].tv = 0;
			verts[3*i + 1].x = aright; verts[3*i + 1].y = atop; verts[3*i + 1].z = z; verts[3*i + 1].tu = 1; verts[3*i + 1].tv = 0;
			verts[3*i + 2].x = aleft; verts[3*i + 2].y = abottom; verts[3*i + 2].z = z; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 1;
			verts[3*i + 3].x = aright; verts[3*i + 3].y = abottom; verts[3*i + 3].z = z; verts[3*i + 3].tu = 1; verts[3*i + 3].tv = 1;
			verts[3*i + 0].rhw = rhw;
			verts[3*i + 1].rhw = rhw;
			verts[3*i + 2].rhw = rhw;
			verts[3*i + 3].rhw = rhw;

			i = 2;
			verts[3*i + 0].x = 0;               verts[3*i + 0].y = 0;                verts[3*i + 0].z = z; verts[3*i + 0].tu = 0; verts[3*i + 0].tv = 0;
			verts[3*i + 1].x = (*m_pWidth)-1/**/; verts[3*i + 1].y = 0;                verts[3*i + 1].z = z; verts[3*i + 1].tu = 1; verts[3*i + 1].tv = 0;
			verts[3*i + 2].x = 0;               verts[3*i + 2].y = (*m_pHeight)-1/**/; verts[3*i + 2].z = z; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 1;
			verts[3*i + 3].x = (*m_pWidth)-1/**/; verts[3*i + 3].y = (*m_pHeight)-1/**/; verts[3*i + 3].z = z; verts[3*i + 3].tu = 1; verts[3*i + 3].tv = 1;
			verts[3*i + 0].rhw = rhw;
			verts[3*i + 1].rhw = rhw;
			verts[3*i + 2].rhw = rhw;
			verts[3*i + 3].rhw = rhw;

/*
 verts[3*i + 0].color = col; 
 verts[3*i + 1].color = col; 
 verts[3*i + 2].color = col; 
 verts[3*i + 3].color = col; 
*/


			//verts[3*i + 1].x = aleft; verts[3*i + 1].y = abottom; verts[3*i + 1].z = z; verts[3*i + 1].rhw = rhw; verts[3*i + 1].color = col; verts[3*i + 1].tu = 0; verts[3*i + 1].tv = 1;
			//verts[3*i + 2].x = aleft; verts[3*i + 2].y = atop; verts[3*i + 2].z = z; verts[3*i + 2].rhw = rhw; verts[3*i + 2].color = col; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 0;
				i = i + 2;
		
		for (int x = 0; x < nx; x++) {
			for (int y = 0; y < ny; y++) {

			verts[3*i + 0].x = left + texWidth * x; verts[3*i + 0].y = top + texHeight * y; verts[3*i + 0].z = z; verts[3*i + 0].tu = 0; verts[3*i + 0].tv = 0;
			verts[3*i + 1].x = right + texWidth * x; verts[3*i + 1].y = top + texHeight * y; verts[3*i + 1].z = z; verts[3*i + 1].tu = (float)(*m_pSfPixPerCycle)/texWidth; verts[3*i + 1].tv = 0;
			verts[3*i + 2].x = right + texWidth * x; verts[3*i + 2].y = bottom + texHeight * y; verts[3*i + 2].z = z; verts[3*i + 2].tu = (float)(*m_pSfPixPerCycle)/texWidth; verts[3*i + 2].tv = 1;
			verts[3*i + 0].rhw = rhw; 
			verts[3*i + 1].rhw = rhw; 
			verts[3*i + 2].rhw = rhw; 
/*
verts[3*i + 0].color = col; 
verts[3*i + 1].color = col; 
verts[3*i + 2].color = col; 
*/

				i = i + 1;

			verts[3*i + 0].x = right + texWidth * x; verts[3*i + 0].y = bottom + texHeight * y; verts[3*i + 0].z = z; verts[3*i + 0].tu = (float)(*m_pSfPixPerCycle)/texWidth; verts[3*i + 0].tv = 1;
			verts[3*i + 1].x = left + texWidth * x; verts[3*i + 1].y = bottom + texHeight * y; verts[3*i + 1].z = z; verts[3*i + 1].tu = 0; verts[3*i + 1].tv = 1;
			verts[3*i + 2].x = left + texWidth * x; verts[3*i + 2].y = top + texHeight * y; verts[3*i + 2].z = z; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 0;
			verts[3*i + 0].rhw = rhw; 
			verts[3*i + 1].rhw = rhw; 
			verts[3*i + 2].rhw = rhw; 
			/**/
				i = i + 1;

			}
		}
/*
			verts[3*i + 0].x = aleft; verts[3*i + 0].y = atop; verts[3*i + 0].z = z; verts[3*i + 0].rhw = rhw; verts[3*i + 0].color = col; verts[3*i + 0].tu = 0; verts[3*i + 0].tv = 0;
			verts[3*i + 1].x = aright; verts[3*i + 1].y = atop; verts[3*i + 1].z = z; verts[3*i + 1].rhw = rhw; verts[3*i + 1].color = col; verts[3*i + 1].tu = 1; verts[3*i + 1].tv = 0;
			verts[3*i + 2].x = aleft; verts[3*i + 2].y = abottom; verts[3*i + 2].z = z; verts[3*i + 2].rhw = rhw; verts[3*i + 2].color = col; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 1;
			verts[3*i + 3].x = aright; verts[3*i + 3].y = abottom; verts[3*i + 3].z = z; verts[3*i + 3].rhw = rhw; verts[3*i + 3].color = col; verts[3*i + 3].tu = 1; verts[3*i + 3].tv = 1;
			//verts[3*i + 1].x = aleft; verts[3*i + 1].y = abottom; verts[3*i + 1].z = z; verts[3*i + 1].rhw = rhw; verts[3*i + 1].color = col; verts[3*i + 1].tu = 0; verts[3*i + 1].tv = 1;
			//verts[3*i + 2].x = aleft; verts[3*i + 2].y = atop; verts[3*i + 2].z = z; verts[3*i + 2].rhw = rhw; verts[3*i + 2].color = col; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 0;
				i = i + 2;
		
		for (int x = 0; x < nx; x++) {
			for (int y = 0; y < ny; y++) {

			verts[3*i + 0].x = left + texWidth * x; verts[3*i + 0].y = top + texHeight * y; verts[3*i + 0].z = z; verts[3*i + 0].rhw = rhw; verts[3*i + 0].color = col; verts[3*i + 0].tu = 0; verts[3*i + 0].tv = 0;
			verts[3*i + 1].x = right + texWidth * x; verts[3*i + 1].y = top + texHeight * y; verts[3*i + 1].z = z; verts[3*i + 1].rhw = rhw; verts[3*i + 1].color = col; verts[3*i + 1].tu = 1; verts[3*i + 1].tv = 0;
			verts[3*i + 2].x = right + texWidth * x; verts[3*i + 2].y = bottom + texHeight * y; verts[3*i + 2].z = z; verts[3*i + 2].rhw = rhw; verts[3*i + 2].color = col; verts[3*i + 2].tu = 1; verts[3*i + 2].tv = 1;

				i = i + 1;

			verts[3*i + 0].x = right + texWidth * x; verts[3*i + 0].y = bottom + texHeight * y; verts[3*i + 0].z = z; verts[3*i + 0].rhw = rhw; verts[3*i + 0].color = col; verts[3*i + 0].tu = 1; verts[3*i + 0].tv = 1;
			verts[3*i + 1].x = left + texWidth * x; verts[3*i + 1].y = bottom + texHeight * y; verts[3*i + 1].z = z; verts[3*i + 1].rhw = rhw; verts[3*i + 1].color = col; verts[3*i + 1].tu = 0; verts[3*i + 1].tv = 1;
			verts[3*i + 2].x = left + texWidth * x; verts[3*i + 2].y = top + texHeight * y; verts[3*i + 2].z = z; verts[3*i + 2].rhw = rhw; verts[3*i + 2].color = col; verts[3*i + 2].tu = 0; verts[3*i + 2].tv = 0;
				i = i + 1;

			}
		}
*/
			memcpy(pVbData, verts, (6*nx*ny+12)*sizeof(CUSTOMVERTEX));

		delete [] verts;
		m_VertexBuffer->Unlock();

	}
	return S_OK;
}

HRESULT __stdcall CNStimTestGratingPatch::Reset(INStimEngine* pEngine)  {
	CNStimPatch::Reset(pEngine);
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
	return S_OK;
}