#include "textures.h"
#include <stdio.h>
#define _RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 6) + ((r & 31) << 11))

/////////////////////////////////////////////////////////////////////////////
// Texture Management Routines
/////////////////////////////////////////////////////////////////////////////

CTexture::CTexture() {
	Width = 64;
	Height = 32;
};

HRESULT CALLBACK EnumTextures( LPDDPIXELFORMAT DDPixelFormat, LPVOID pDDDesiredPixelFormat )  
{  
    if( DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS && DDPixelFormat->dwRGBBitCount == 16 )  
    {  
        if( DDPixelFormat->dwRGBAlphaBitMask == 1 || DDPixelFormat->dwRGBAlphaBitMask == 0x8000 )  
        {  
            memcpy( pDDDesiredPixelFormat, DDPixelFormat, sizeof(DDPIXELFORMAT) );  
            return D3DENUMRET_CANCEL;  
        }  
    }  
    return D3DENUMRET_OK;  
}


// There is an easier way to load textures, I just didn't think of it in time!
void CTexture::LoadTexture(char * filename, LPDIRECT3DDEVICE3 D3DDevice, LPDIRECTDRAW4 DirectDraw) {
	
	DDPIXELFORMAT TexturePixelFormat;

	if (FAILED(D3DDevice->EnumTextureFormats(( LPD3DENUMPIXELFORMATSCALLBACK )EnumTextures, ( void* )&TexturePixelFormat))) {
		exit(10);
	};


	DDSURFACEDESC2 Desc;  
	ZeroMemory( &Desc, sizeof( DDSURFACEDESC2 ));  
	Desc.dwSize = sizeof( Desc );  
	Desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_CKSRCBLT;  
	Desc.dwWidth = Width;  
	Desc.dwHeight = Height;  
	Desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;  
	Desc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;  
	Desc.ddpfPixelFormat = TexturePixelFormat;
	Desc.ddckCKSrcBlt.dwColorSpaceHighValue = _RGB16BIT565(255,0,255);
	Desc.ddckCKSrcBlt.dwColorSpaceLowValue = _RGB16BIT565(255,0,255);
	
	DirectDraw->CreateSurface( &Desc, &Surface, 0 );  
	Surface->QueryInterface( IID_IDirect3DTexture2, ( void **)&Texture );

	HBITMAP hBM;  
	BITMAP BM;  
	HDC hDCImage, hDC;  
	
	hBM = ( HBITMAP ) LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	if (hBM == NULL) {
		exit(10);
	};
	
	GetObject( hBM, sizeof( BM ), &BM );  
	
	hDCImage = CreateCompatibleDC( NULL );  
	SelectObject( hDCImage, hBM );  
	
	if( SUCCEEDED( Surface->GetDC( &hDC )))  
	{  
		BitBlt( hDC, 0, 0, Width, Height, hDCImage, 0, 0, SRCCOPY );  
		Surface->ReleaseDC( hDC );  
	} else {
		exit(10);
	};
	
	DeleteDC( hDCImage );  
	DeleteObject( hBM );
};

CTexture::~CTexture() {
	Texture->Release();
	Surface->Release();
};
