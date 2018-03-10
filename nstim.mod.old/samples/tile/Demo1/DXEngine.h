/////////////////////////////////////////////////////////////////////
// DXEngine.h
//
// DXEngine is quite a big class I use as a base class for DirectX projects.
// It includes a lot of functionality that is made available to child classes.
// This is a cut-down version for the tutorial. The full version also 
// includes DirectInput, DirectMusic, DirectSound and a number of DirectDraw 
// drawing utilities.
//
// This isn't exactly the paragon of OO design, but it works. :-)
/////////////////////////////////////////////////////////////////////


#ifndef DXENGINE
#define DXENGINE

#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <d3d.h>

// basic unsigned types
typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;
typedef unsigned int   QUAD;
typedef unsigned int   UINT;


class DXEngine {
public:

	// Constructor - takes all the information you need to initialise DirectX
	DXEngine();

	// Generic Error Reporting Tool - normally I dump these to a text file
	void ReportError(char * text);

	// Window Description
	int Windowed;
	int BitDepth;
	int ScreenHeight;
	int ScreenWidth;
	HINSTANCE Application;
	HWND MainWindow;
	int WindowClientY0;
	int WindowClientX0;
	void SetClientParams(int nx, int ny);

	// Initialisation routine. Not in the constructor because I want it to
	// be called as appropriate from any layer of child objects without burdening
	// any later constructors.
	void Init(HWND WinHandle, HINSTANCE AppHandle, int nx, int ny, int nbpp, int nWindowed);

	// Destructor - cleans up behind itself
	~DXEngine();

	// DirectX initialisation function
	void InitDirectX();

	// Virtual functions - you have to instantiate these in child objects
	virtual void GameInit()=0;
	virtual void GameMain()=0;
	virtual void GameDone()=0;

	////////////////////////
	// DirectDraw Variables

	// DirectDraw Interface
	LPDIRECTDRAW4 DirectDraw;

	// Clipping
	LPDIRECTDRAWCLIPPER Clipper;
	LPDIRECTDRAWCLIPPER WindowClipper;
	int ClipMaxY;
	int ClipMinY;
	int ClipMaxX;
	int ClipMinX;

	// Surfaces
	LPDIRECTDRAWSURFACE4 Primary;
	LPDIRECTDRAWSURFACE4 BBuffer;
	DDSURFACEDESC2 SurfaceDescription;
	int PixelFormat;

	///////////////////////
	// DirectDraw Functions

	void InitDirectDraw();
	LPDIRECTDRAWSURFACE4 CreateSurface(int width,int height, int mem_flags, USHORT colour_key_value);
	LPDIRECTDRAWCLIPPER AttachClipper(LPDIRECTDRAWSURFACE4 surface, int RectCount, LPRECT ClipList);
	void FillSurface(LPDIRECTDRAWSURFACE4 lpdds, USHORT colour, RECT * client);
	void Flip();

	///////////////////////
	// Direct3D Variables
	LPDIRECT3DVIEWPORT3 Viewport;
	D3DVIEWPORT2 Viewdata;
	LPDIRECT3DDEVICE3 D3DDevice;
	LPDIRECT3D3 Direct3D;

	///////////////////////
	// Direct3D Functions
	void InitDirect3D();

};
#endif