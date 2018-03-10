//-----------------------------------------------------------------------------
// Direct3D Sprite Drawing Demo
//
// This demo accompanies the GameDev (www.gamedev.net) article:
//
//   Dissecting Sprites in Direct3D
//
// It contains code and example usage for the described functions. 
// and illustrates the bugs in
//
//   1. Microsoft's ID3DXSprite
//   2. Dunlop's blit function  [ see BlitX() ]
//
// Note: "- 1" has been commented out at various points to
//       illustrate the inclusive/exclusive documentation error.
//
// Author:  R. Parker (parkmuse@hotmail.com)
// Version: 1.1
// Created: 10 March 2002
//
// The graphics in "sprites.bmp" were created by Ari Feldman
// (www.arifeldman.com).
//-----------------------------------------------------------------------------

#include <d3d8.h>
#include <d3dx8tex.h>
#include <dxerr8.h>

// Uncomment the next line to turn on DirectX debugging info
//#define DEBUG

#if defined(DEBUG)
	#define DXTEST(expr) \
	if (FAILED(expr))    \
	{                    \
		DXTrace(__FILE__, __LINE__, expr, #expr, TRUE); \
		throw expr;                                     \
	}
#else
	#define DXTEST(expr) expr
#endif


//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
const int WIN_WIDTH = 320, WIN_HEIGHT = 240; // Dimensions of the window
const int SPRITE_WIDTH = 32, SPRITE_HEIGHT = 40;
const int NUM_SPRITES = 3;

LPDIRECT3D8       g_lpD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE8 g_lpD3DDevice = NULL; // Our rendering device

LPDIRECT3DTEXTURE8 g_lpTextures[NUM_SPRITES];


//-----------------------------------------------------------------------------
// Transformed, lit vertex
//-----------------------------------------------------------------------------
struct D3DTLVERTEX
{
	float    x, y, z; // Position
	float    rhw;     // Reciprocal of homogeneous w
	D3DCOLOR colour;  // Vertex colour
	float    tu, tv;  // Texture coordinates
};
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;


//-----------------------------------------------------------------------------
// Builds a transformation matrix from the arguments.
//
// pOut     - The result of this operation.
// pCentre  - The centre of scaling and rotation.
// pScaling - The scaling vector.
// angle    - The angle of rotation in radians.
//-----------------------------------------------------------------------------
D3DMATRIX* BuildMatrix(D3DMATRIX* pOut, 
                       D3DXVECTOR2* centre, 
                       D3DXVECTOR2* scaling, 
                       float angle)
{
	D3DXMATRIX matrices[5];

	D3DXMatrixTranslation(&matrices[0], -centre->x, -centre->y, 0);
	D3DXMatrixScaling(&matrices[1], scaling->x, scaling->y, 1);
	D3DXMatrixIdentity(&matrices[2]);
	D3DXMatrixIdentity(&matrices[3]);
	D3DXMatrixRotationZ(&matrices[2], angle);
	D3DXMatrixTranslation(&matrices[3], centre->x, centre->y, 0);

	matrices[4] = matrices[0] * matrices[1] * matrices[2] * matrices[3];
	*pOut = matrices[4];

	return pOut;
}

//-----------------------------------------------------------------------------
// Transform the points in vertices[] according to the arguments
//
// pCentre  - The centre of scaling and rotation.
// pScaling - Scaling vector.
// angle    - Angle of rotation in radians.
//-----------------------------------------------------------------------------
void TransformVertices(D3DTLVERTEX vertices[], 
                       D3DXVECTOR2* pCentre, 
                       D3DXVECTOR2* pScaling, 
                       float angle)
{
	D3DXMATRIX matTransf, matVerts, matNew;

	BuildMatrix(&matTransf, pCentre, pScaling, angle);

	int cr;
	for (cr = 0; cr < 4; cr++)
	{
		// 4 vertices fit nicely into a 4x4 matrix --
		// Put each vertex point into a matrix row.
		matVerts(cr, 0) = vertices[cr].x;
		matVerts(cr, 1) = vertices[cr].y;
		matVerts(cr, 2) = vertices[cr].z;
		matVerts(cr, 3) = 1.0f;  // the scaling factor, w
	}

	// Reuse D3D matrix multiplication code to transform our 
	// vertices.
	matNew = matVerts * matTransf;

	for (cr = 0; cr < 4; cr++)
	{
		// Retrieve the newly transformed points.
		vertices[cr].x = matNew(cr, 0);
		vertices[cr].y = matNew(cr, 1);
		vertices[cr].z = matNew(cr, 2);
	}
}

//-----------------------------------------------------------------------------
// Draws a textured quad (sprite).
//
// pTexture - The source texture used for the sprite.
// pDest    - Draw sprite at these screen coordinates.
// pCenter  - Centre of scaling and rotation, relative to pDest.
// pScaling - Scaling vector. If NULL, it is treated as identity.
// angle    - Angle of rotation in radians.
// colour   - The RGB and alpha channels are modulated by this value. Use 
//            0xFFFFFFFF for a standard blit.
//-----------------------------------------------------------------------------
void Blit(LPDIRECT3DTEXTURE8 pTexture, 
          POINT* pDest, 
          D3DXVECTOR2* pCentre, 
          D3DXVECTOR2* pScaling = NULL, 
          float angle = 0, 
          D3DCOLOR colour = 0xFFFFFFFF)
{
	D3DSURFACE_DESC surfDesc;
	DXTEST( pTexture->GetLevelDesc(0, &surfDesc) );

	float left   = (float)pDest->x;
	float top    = (float)pDest->y;
	float right  = left + surfDesc.Width; // - 1;
	float bottom = top + surfDesc.Height; // - 1;

	const float z = 0.0f, rhw = 1.0f;
	D3DTLVERTEX vertices[4] =
	{
		// x, y, z, rhw, colour, tu, tv
		{ left,  top,    z, rhw, colour, 0, 0 },
		{ right, top,    z, rhw, colour, 1, 0 },
		{ right, bottom, z, rhw, colour, 1, 1 },
		{ left,  bottom, z, rhw, colour, 0, 1 }
	};

	D3DXVECTOR2 centre, scaling;

	centre.x = (float)pDest->x + pCentre->x;
	centre.y = (float)pDest->y + pCentre->y;
	pCentre = &centre; // Don't want to modify the argument passed in.

	if (pScaling == NULL) // Use identity: no scaling performed.
	{
		scaling.x = scaling.y = 1;
		pScaling = &scaling;
	}

	TransformVertices(vertices, pCentre, pScaling, angle);

	// Draw the sprite
	DXTEST( g_lpD3DDevice->SetTexture(0, pTexture) );
	DXTEST( g_lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, 
	                                       vertices, sizeof(D3DTLVERTEX)) );
}

//-----------------------------------------------------------------------------
// Modified version of Robert Dunlop's BlitRect() from
// http://www.mvps.org/directx/articles/blit3d.htm
//
// Changes are:
//
//  1. Replaced arguments: left, top, right, and bottom with pDest. Simpler.
//  2. Added ex argument for testing purposes.
//  3. Used a different method of initialising the vertices.
//
//
// lpSrc - The source texture used for the sprite.
// pDest - Draw sprite at these screen coordinates.
// col   - The RGB and alpha channels are modulated by this value.
// z     - The depth of the rectangle, in the range of 0.0 to 1.0.
// ex    - Amount to extend rectangle by. 0.5 is the recommended.
//-----------------------------------------------------------------------------
void BlitX(LPDIRECT3DTEXTURE8 lpSrc, POINT* pDest, 
           D3DCOLOR col, float z, float ex)
{
	D3DSURFACE_DESC surfDesc;
	DXTEST( lpSrc->GetLevelDesc(0, &surfDesc) );

	float left   = (float)pDest->x;
	float top    = (float)pDest->y;
	float right  = left + surfDesc.Width - 1;
	float bottom = top + surfDesc.Height - 1;

	float rhw = 1.0f / (z * 990.0f + 10.0f);

	D3DTLVERTEX verts[4] =
	{
		// x, y, z, rhw, colour, tu, tv
		{ left  - ex, top    - ex, z, rhw, col, 0, 0 },
		{ right + ex, top    - ex, z, rhw, col, 1, 0 },
		{ right + ex, bottom + ex, z, rhw, col, 1, 1 },
		{ left  - ex, bottom + ex, z, rhw, col, 0, 1 }
	};

	DXTEST( g_lpD3DDevice->SetTexture(0, lpSrc) );
	DXTEST( g_lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 
		2, verts, sizeof(D3DTLVERTEX)) );
}

//-----------------------------------------------------------------------------
// Sets up Direct3D for blitting.
//-----------------------------------------------------------------------------
void InitBlit()
{
	// Turn off culling, so we see the front and back of primitives
	DXTEST( g_lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE) );

	// Enable alpha blended transparency.
	DXTEST( g_lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE) );
	DXTEST( g_lpD3DDevice->SetRenderState(
		D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA) );
	DXTEST( g_lpD3DDevice->SetRenderState(
		D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA) );

	// Allow modulation of the texture's and diffuse colour's alpha.
	// By default, the texture and diffuse colour's RGB are modulated.
	// This lets us create transparency and tinting effects by setting 
	// the (diffuse) colour in Blit().
	DXTEST( g_lpD3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAOP, D3DTOP_MODULATE) );
	DXTEST( g_lpD3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE) );
	DXTEST( g_lpD3DDevice->SetTextureStageState(
		0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE) );

	DXTEST( g_lpD3DDevice->SetVertexShader(D3DFVF_TLVERTEX) );
}

//-----------------------------------------------------------------------------
// Creates a surface from the specified graphics file.
//
//  ppSurface  - The created surface object.
//  szFileName - The bitmap file name.
//  colourKey  - The transparent colour. Opaque black by default.
//-----------------------------------------------------------------------------
void CreateSurfaceFromFile(LPDIRECT3DSURFACE8* ppSurface, char szFileName[], 
                           D3DCOLOR colourKey = 0xFF000000)
{
	const D3DFORMAT SURFACE_FORMAT = D3DFMT_A1R5G5B5;

	LPDIRECT3DSURFACE8 pSurface;
	D3DXIMAGE_INFO srcInfo;    // Optional
	PALETTEENTRY palette[256]; // Optional

	// A quick hack to get the size of the image into srcInfo.
	DXTEST( g_lpD3DDevice->CreateImageSurface(1, 1, 
		SURFACE_FORMAT, &pSurface) );
	DXTEST( D3DXLoadSurfaceFromFile(pSurface, NULL, NULL, szFileName, 
		NULL, D3DX_FILTER_NONE, 0, &srcInfo) );
	pSurface->Release();

	// Create a surface to hold the entire file
	DXTEST( g_lpD3DDevice->CreateImageSurface(srcInfo.Width, srcInfo.Height, 
		SURFACE_FORMAT, ppSurface) );
	pSurface = *ppSurface;

	// The default colour key is 0xFF000000 (opaque black). Magenta 
	// (0xFFFF00FF) is another common colour used for transparency.
	DXTEST( D3DXLoadSurfaceFromFile(pSurface, palette, NULL, szFileName, 
		NULL, D3DX_FILTER_NONE, colourKey, &srcInfo) );
}

//-----------------------------------------------------------------------------
// Creates a texture from a region of the surface.
//
// pSurface  - the source surface.
// pSrcRect  - portion of the source surface to create the texture from.
// ppTexture - the created texture object.
//-----------------------------------------------------------------------------
void CreateTextureFromSurface(LPDIRECT3DSURFACE8 pSurface, RECT* pSrcRect,
                              LPDIRECT3DTEXTURE8* ppTexture)
{
	int width  = pSrcRect->right - pSrcRect->left; // + 1;
	int height = pSrcRect->bottom - pSrcRect->top; // + 1;
	D3DSURFACE_DESC surfDesc;
	DXTEST( pSurface->GetDesc(&surfDesc) );
	DXTEST( D3DXCreateTexture(g_lpD3DDevice, width, height, 
		1, 0, surfDesc.Format, D3DPOOL_DEFAULT, ppTexture) );

	// Retrieve the surface image of the texture.
	LPDIRECT3DSURFACE8 pTexSurface;
	LPDIRECT3DTEXTURE8 pTexture = *ppTexture;
	DXTEST( pTexture->GetLevelDesc(0, &surfDesc) );
	DXTEST( pTexture->GetSurfaceLevel(0, &pTexSurface) );

	// Create a clean surface to clear the texture with.
	LPDIRECT3DSURFACE8 pCleanSurface;
	D3DLOCKED_RECT lockRect;
	DXTEST( g_lpD3DDevice->CreateImageSurface(
		surfDesc.Width, surfDesc.Height, surfDesc.Format, &pCleanSurface) );
	DXTEST( pCleanSurface->LockRect(&lockRect, NULL, 0) );
	memset((BYTE*)lockRect.pBits, 0, surfDesc.Height * lockRect.Pitch);
	DXTEST( pCleanSurface->UnlockRect() );

	DXTEST( g_lpD3DDevice->CopyRects(pCleanSurface, NULL, 0, 
		pTexSurface, NULL) );
	pCleanSurface->Release();

	// Copy the image to the texture.
	POINT destPoint = { 0, 0 };
	DXTEST( g_lpD3DDevice->CopyRects(pSurface, pSrcRect, 1, 
		pTexSurface, &destPoint) );
	pTexSurface->Release();

	/*
	// The following srcRect should clear the texture.
	RECT srcRect = { 0, 0, surfDesc.Width - 1, surfDesc.Height - 1 };

	// But the right and bottom edges are not clean.
	// Instead you have to use the following srcRect.
	RECT srcRect = { 0, 0, surfDesc.Width, surfDesc.Height };

	POINT destPoint = { 0, 0 };
	g_lpD3DDevice->CopyRects(pCleanSurface, &srcRect, 1, pTexSurface, &destPoint);

	// Thankfully, there's an easier way: use NULL for srcRect and
	// destPoint. See above.
	*/
}

//-----------------------------------------------------------------------------
// Draws the scene.
//-----------------------------------------------------------------------------
void Render()
{
	DXTEST( g_lpD3DDevice->Clear(0, NULL, 
		D3DCLEAR_TARGET, 0xFF008080, 1.0f, 0) );
	DXTEST( g_lpD3DDevice->BeginScene() );

	//------------------------------------------------------

	// Draw sprite 1.
	LPD3DXSPRITE lpD3DSprite;
	D3DXCreateSprite(g_lpD3DDevice, &lpD3DSprite);
	lpD3DSprite->Begin();
	D3DXVECTOR2 translation(80, 32);
	lpD3DSprite->Draw(g_lpTextures[0], NULL, NULL, NULL, 0, &translation, 0xFFFFFFFF);
	lpD3DSprite->End();
	lpD3DSprite->Release();

	//------------------------------------------------------

	InitBlit();

	// Set up Blit and BlitX parameters.
	POINT destPoint = { 144, 32 };
	D3DXVECTOR2 centre(SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);
	D3DXVECTOR2 scaling(1.0f, 1.0f);
	float angle = 0;
	D3DCOLOR colour = 0xFFFFFFFF;

	// Draw sprites 2 and 3.
	BlitX(g_lpTextures[0], &destPoint, colour, 0, 0);
	destPoint.x += 64;
	BlitX(g_lpTextures[0], &destPoint, colour, 0, 0.5f);

	//------------------------------------------------------

	// Draw bottom sprites (3 to 6).
	destPoint.x = 80;
	destPoint.y += 80;
	Blit(g_lpTextures[0], &destPoint, &centre, &scaling, angle, colour);
	destPoint.x += 64;

	scaling.x = -1.0f; scaling.y = 2.4f;
	Blit(g_lpTextures[1], &destPoint, &centre, &scaling, angle, colour);
	destPoint.x += 64;

	scaling.x = scaling.y = 1.0f;
	angle = 1;
	colour = 0xFFFF80FF;
	Blit(g_lpTextures[2], &destPoint, &centre, &scaling, angle, colour);

	DXTEST( g_lpD3DDevice->EndScene() );
	DXTEST( g_lpD3DDevice->Present(NULL, NULL, NULL, NULL) );
}

//-----------------------------------------------------------------------------
// Initialise global variables.
//-----------------------------------------------------------------------------
void InitVars(HWND hWnd)
{
	for (int index = 0; index < NUM_SPRITES; index++)
	{
		g_lpTextures[index] = NULL;
	}

	// Create the D3D object, which is needed to create the D3DDevice.
	g_lpD3D = Direct3DCreate8(D3D_SDK_VERSION);

	// Get the current desktop display mode
	D3DDISPLAYMODE d3ddm;
	DXTEST( g_lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) );

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;

	DXTEST( g_lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_lpD3DDevice) );

	// Initialise the textures.
	LPDIRECT3DSURFACE8 lpSurface;
	RECT srcRect = { 0, 0, SPRITE_WIDTH, SPRITE_HEIGHT };

	// The srcRect should be { 0, 0, SPRITE_WIDTH - 1, SPRITE_HEIGHT - 1 }

	CreateSurfaceFromFile(&lpSurface, "sprites.bmp");
	for (index = 0; index < NUM_SPRITES; index++)
	{
		CreateTextureFromSurface(lpSurface, &srcRect, &g_lpTextures[index]);
		srcRect.left  += SPRITE_WIDTH;
		srcRect.right += SPRITE_WIDTH;
	}
	lpSurface->Release();
}

//-----------------------------------------------------------------------------
// Cleanup global variables.
//-----------------------------------------------------------------------------
void Cleanup()
{
	// Needed to prevent a memory leak. See documentation for SetTexture().
	g_lpD3DDevice->SetTexture(0, NULL);

	for (int index = 0; index < NUM_SPRITES; index++)
	{
		if (g_lpTextures[index] != NULL)
			g_lpTextures[index]->Release();
	}
	if (g_lpD3DDevice != NULL)
		g_lpD3DDevice->Release();
	if (g_lpD3D != NULL)
		g_lpD3D->Release();
}

//-----------------------------------------------------------------------------
// The window's message handler.
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	const char szWinName[] = "Blitting in Direct3D";

	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL, 
		szWinName, NULL
	};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(szWinName, szWinName, 
	                         WS_OVERLAPPEDWINDOW, 
	                         100, 100, WIN_WIDTH, WIN_HEIGHT,
	                         GetDesktopWindow(), NULL, wc.hInstance, NULL);
	try
	{
		InitVars(hWnd);

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		MSG msg; 
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch (HRESULT)
	{
		// An unexpected error has occurred.
	}

	// Clean up everything and exit the app
	Cleanup();
	UnregisterClass(szWinName, wc.hInstance);

	return 0;
}
