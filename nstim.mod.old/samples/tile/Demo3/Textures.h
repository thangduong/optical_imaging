#ifndef TEXTURE
#define TEXTURE

#include <ddraw.h>
#include <d3d.h>
#include "DXEngine.h"

class CTexture {
public:
	LPDIRECTDRAWSURFACE4 Surface;	// DirectDraw Texture
	LPDIRECT3DTEXTURE2 Texture;		// Direct3D Texture
	int Width, Height;

	CTexture();
	~CTexture();
	void LoadTexture(char * filename, LPDIRECT3DDEVICE3 D3DDevice, LPDIRECTDRAW4 DirectDraw);
};
#endif