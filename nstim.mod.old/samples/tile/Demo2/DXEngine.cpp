#include "DXEngine.h"

// initializes a direct draw struct, basically zeros it and sets the dwSize field
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }

DXEngine::DXEngine() {
};

void DXEngine::Init(HWND WinHandle, HINSTANCE AppHandle, int nx, int ny, int nbpp, int nWindowed) {
	// Allocate Variables
	MainWindow = WinHandle;
	Application = AppHandle;
	ScreenWidth = nx;
	ScreenHeight = ny;
	BitDepth = nbpp;
	Windowed = nWindowed;
};

DXEngine::~DXEngine() {
	// Shutdown Direct3D
	if (Viewport) Viewport->Release();
	if (Direct3D) Direct3D->Release();

	// Shutdown DirectDraw
	if (Clipper) {
		Clipper->Release();
	};
	if (WindowClipper) {
		WindowClipper->Release();
	};
	if (BBuffer) {
		BBuffer->Release();
	};
	if (Primary) {
		Primary->Release();
	};
	if (DirectDraw) {
		DirectDraw->Release();
	};
};

void DXEngine::InitDirectX() {
	// Initialise DirectDraw
	InitDirectDraw();

	// Initialise Direct3D
	InitDirect3D();

	// Hide the mouse cursor if we aren't running in a window
	if (!Windowed) {
		ShowCursor(FALSE);
	};

	// Seed the random number generator
	srand(GetTickCount());
};

void DXEngine::SetClientParams(int nx, int ny) {
	WindowClientX0 = nx;
	WindowClientY0 = ny;
}

void DXEngine::InitDirectDraw() {
	// Set some variables to NULL for the sake of safety
	Clipper = NULL;
	WindowClipper = NULL;
	DirectDraw = NULL;
	Primary = NULL;
	BBuffer = NULL;

	// Temporary variable used to get DirectDraw 6
	LPDIRECTDRAW lpddTemp = NULL;

	// Get DirectDraw 1
	if (FAILED(DirectDrawCreate(NULL,&lpddTemp,NULL))) {
		// Unable to init basic DirectDraw
		ReportError("Unable to initialise basic DirectDraw Object");
		exit(10);
	};

	// Get latest DirectDraw (4 as of DirectX 6)
	if (FAILED(lpddTemp->QueryInterface(IID_IDirectDraw4,(LPVOID *)&DirectDraw))) {
		// Unable to upgrade DirectDraw
		ReportError("Unable to upgrade to recent DirectDraw");
		exit(10);
	};

	// Set Cooperation level, based on Window/Fullscreen
	if (Windowed) {
		// Windowed apps like DDSCL_NORMAL
		if (FAILED(DirectDraw->SetCooperativeLevel(MainWindow,DDSCL_NORMAL))) {
			// Cooperation failed
			ReportError("Failed to cooperate (windowed mode) with Windows");
			exit(10);
		};
	} else {
		// Fullscreen apps (16bpp) should have more
		if (FAILED(DirectDraw->SetCooperativeLevel(MainWindow,DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT | DDSCL_FPUSETUP))) {
			// Cooperation failed
			ReportError("Failed to cooperate (fullscreen mode) with Windows");
			exit(10);
		};
	};

// Create the desired screen mode. 16 bpp fails to 24 when necessary.
	if (!Windowed) { //changing screen mode when windowed is retarted!
		if (FAILED(DirectDraw->SetDisplayMode(ScreenWidth,ScreenHeight,BitDepth,0,0))) {
			// Screen mode failed
			ReportError("Couldn't get 16bpp, trying 24");
			
			if (BitDepth == 16) {
				BitDepth = 24;
				if (FAILED(DirectDraw->SetDisplayMode(ScreenWidth,ScreenHeight,BitDepth,0,0))) {
					ReportError("No 24bpp either.");
					exit(10);
				};
			} else {
				// No screen. Sorry!
				ReportError("Screen initialisation failed horribly. Don't use 8 bpp.");
				exit(10);
			};
		};
	};

	// Blank the Surface Description
	memset(&SurfaceDescription,0,sizeof(SurfaceDescription));
	SurfaceDescription.dwSize = sizeof(SurfaceDescription);

	// If its windowed, we don't want a complex Primary surface - otherwise,
	// we do.

	if (!Windowed) {
		// Fullscreen mode
		SurfaceDescription.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		SurfaceDescription.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE  | DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_3DDEVICE;
   
		// set the backbuffer count to 0 for windowed mode
		// 1 for fullscreen mode, 2 for triple buffering
		SurfaceDescription.dwBackBufferCount = 1;
	} else {
		// Windowed mode
		SurfaceDescription.dwFlags = DDSD_CAPS;
		SurfaceDescription.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_3DDEVICE;
	   // set the backbuffer count to 0 for windowed mode
		// 1 for fullscreen mode, 2 for triple buffering
		SurfaceDescription.dwBackBufferCount = 0;
	};
	
	// Create the Primary Surface
	DirectDraw->CreateSurface(&SurfaceDescription,&Primary,NULL);

	// Get the pixel format (555/565)
	DDPIXELFORMAT ddpf;
	DDRAW_INIT_STRUCT(ddpf);
	Primary->GetPixelFormat(&ddpf);
	PixelFormat = ddpf.dwRGBBitCount;

	// Get a backbuffer if its a full screen mode
	if (!Windowed) {
		SurfaceDescription.dwFlags = DDSD_CAPS;
		SurfaceDescription.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER | DDSCAPS_3DDEVICE;
		SurfaceDescription.dwBackBufferCount = 1;
 
		if (FAILED(Primary->GetAttachedSurface(&SurfaceDescription.ddsCaps,&BBuffer))) {
			// No back buffer is possible
			ReportError("Double buffering isn't possible.");
			exit(10);
		};
	} else {
		BBuffer = CreateSurface(ScreenWidth,ScreenHeight,DDSCAPS_3DDEVICE,0);
	};

	// Clear primary and secondary surfaces
	if (Windowed) {
		FillSurface(BBuffer,0,NULL);
	} else {
		FillSurface(BBuffer,0,NULL);
		FillSurface(Primary,0,NULL);
	};

	// Set software clipping region
	ClipMinX = 0;
	ClipMaxX = ScreenWidth -1;
	ClipMinY = 0;
	ClipMaxY = ScreenHeight -1;

	// Setup a clipper for the backbuffer/window
	RECT ScreenRect = {0,0,ScreenWidth,ScreenHeight};
	Clipper = AttachClipper(BBuffer,1,&ScreenRect);

	if (Windowed) {
		if (FAILED(DirectDraw->CreateClipper(0,&WindowClipper,NULL))) {
			// Clipper creation failed
			ReportError("Failed to create a clipper");
			exit(10);
		};
		if (FAILED(WindowClipper->SetHWnd(0, MainWindow))) {
			// Clipper creation failed
			ReportError("Failed to attach clipper to window");
			exit(10);
		};

		if (FAILED(Primary->SetClipper(WindowClipper))) {
			// Clipper creation failed
			ReportError("Failed to set the clipper on the primary buffer");
			exit(10);
		};
   };
}

LPDIRECTDRAWCLIPPER DXEngine::AttachClipper(LPDIRECTDRAWSURFACE4 surface, int RectCount, LPRECT ClipList)
{
	int Count;
	LPDIRECTDRAWCLIPPER Clipper;
	LPRGNDATA RegionData;

	// We need a clipper object to play with

	if (FAILED(DirectDraw->CreateClipper(0,&Clipper,NULL))) {
		// Clipper creation failed
		return NULL;
	};

	// Create the clip list
	RegionData = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+RectCount*sizeof(RECT));
	memcpy(RegionData->Buffer, ClipList, sizeof(RECT)*RectCount);

	// Setup the header fields
	RegionData->rdh.dwSize          = sizeof(RGNDATAHEADER);
	RegionData->rdh.iType           = RDH_RECTANGLES;
	RegionData->rdh.nCount          = RectCount;
	RegionData->rdh.nRgnSize        = RectCount*sizeof(RECT);

	RegionData->rdh.rcBound.left    =  64000;
	RegionData->rdh.rcBound.top     =  64000;
	RegionData->rdh.rcBound.right   = -64000;
	RegionData->rdh.rcBound.bottom  = -64000;

	// Find bounds of all clipping regions
	for (Count = 0; Count < RectCount; Count++) {
		// test if the next rectangle unioned with the current bound is larger
		if (ClipList[Count].left < RegionData->rdh.rcBound.left)
			RegionData->rdh.rcBound.left = ClipList[Count].left;

		if (ClipList[Count].right > RegionData->rdh.rcBound.right)
			RegionData->rdh.rcBound.right = ClipList[Count].right;

		if (ClipList[Count].top < RegionData->rdh.rcBound.top)
			RegionData->rdh.rcBound.top = ClipList[Count].top;

		if (ClipList[Count].bottom > RegionData->rdh.rcBound.bottom)
			RegionData->rdh.rcBound.bottom = ClipList[Count].bottom;
	};

	// Set the clip list
	if (FAILED(Clipper->SetClipList(RegionData,0))) {
		// Clip list set failed
		free(RegionData);
		return(NULL);
	};

	// Attach the clipper to the surface
	if (FAILED(surface->SetClipper(Clipper))) {
		// Attachment failed
		free(RegionData);
		return(NULL);
	};

	// It worked!
	free(RegionData);
	return Clipper;
};

// Create an offscreen surface

LPDIRECTDRAWSURFACE4 DXEngine::CreateSurface(int width, int height, int mem_flags, USHORT colour_key_value)
{
	DDSURFACEDESC2 TempDescription;
	LPDIRECTDRAWSURFACE4 Surface;

	// Set appropriate values to the surface description
	memset(&TempDescription,0,sizeof(TempDescription));
	TempDescription.dwSize = sizeof(TempDescription);
	TempDescription.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	// Set size
	TempDescription.dwWidth = width;
	TempDescription.dwHeight = height;

	// Set the type
	TempDescription.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;

	// Create the surface
	if (FAILED(DirectDraw->CreateSurface(&TempDescription,&Surface,NULL))) {
		// That failed.
		ReportError("Surface creation failed!");
		exit(10);
		return NULL;
	};

	// Set the colour key to whatever was passed
	DDCOLORKEY ColourKey;
	ColourKey.dwColorSpaceLowValue = colour_key_value;
	ColourKey.dwColorSpaceHighValue = colour_key_value;

	// Set the colour key for source blitting
	Surface->SetColorKey(DDCKEY_SRCBLT,&ColourKey);

	// Return the surface
	return Surface;
}

void DXEngine::FillSurface(LPDIRECTDRAWSURFACE4 lpdds, USHORT colour, RECT * client)
{
	DDBLTFX BlitFX;

	// Clear the structure
	DDRAW_INIT_STRUCT(BlitFX);
	BlitFX.dwFillColor = colour;
	lpdds->Blt(client,NULL,NULL,DDBLT_COLORFILL | DDBLT_WAIT,&BlitFX);
}

void DXEngine::InitDirect3D() {
// Initialise Direct3D
	D3DFINDDEVICESEARCH search;
	D3DFINDDEVICERESULT result;

	if (FAILED(DirectDraw->QueryInterface(IID_IDirect3D3, (LPVOID *)&Direct3D))) {
		// Unable to find Direct3D
		ReportError("Direct3D Query Failed");
	};

	// Search for Direct3D devices
	memset(&search,0,sizeof(search));
	search.dwSize = sizeof(search);
	//search.dwFlags = D3DFDS_HARDWARE || D3DFDS_SOFTWARE;
	search.bHardware = 1;
	
	memset(&result,0,sizeof(result));
	result.dwSize = sizeof(result);
	if (FAILED(Direct3D->FindDevice(&search,&result))) {
		// Unable to find a 3D device
		ReportError("3D Hardware Not Found!");
		exit(10);
	};

	// Create a device
	if (FAILED(Direct3D->CreateDevice(IID_IDirect3DHALDevice,BBuffer,&D3DDevice,NULL))) {
		ReportError("Failed to create a HAL device, trying MMX.");
		
		if (FAILED(Direct3D->CreateDevice(IID_IDirect3DMMXDevice,BBuffer,&D3DDevice,NULL))) {
			ReportError("Failed to create an MMX device, trying RGB");
		
			if (FAILED(Direct3D->CreateDevice(IID_IDirect3DRGBDevice,BBuffer,&D3DDevice,NULL))) {
				ReportError("Failed to create an RGB device, trying RAMP. Icky.");
			
				if (FAILED(Direct3D->CreateDevice(IID_IDirect3DRampDevice,BBuffer,&D3DDevice,NULL))) {
					ReportError("No Direct3D Devices are available");
					exit(10);
				};
			};

		};
	};

	// Create a viewpoint
	memset(&Viewdata,0,sizeof(Viewdata));
	Viewdata.dwSize = sizeof(Viewdata);
	Viewdata.dwWidth = ScreenWidth;
	Viewdata.dwHeight = ScreenHeight;
	Viewdata.dvClipX = -1.0f;
	Viewdata.dvClipWidth = 2.0f;
	Viewdata.dvClipY = 1.0f;
	Viewdata.dvClipHeight = 2.0f;
	Viewdata.dvMinZ = -10.0f;
	Viewdata.dvMaxZ = 25.0f;

	// Create the viewport
	if (FAILED(Direct3D->CreateViewport(&Viewport,NULL))) {
		ReportError("Failed to create a viewport");
	};
	if (FAILED(D3DDevice->AddViewport(Viewport))) {
		ReportError("Failed to add a viewport");
	};
	if (FAILED(Viewport->SetViewport2(&Viewdata))) {
		ReportError("Failed to set Viewport data");
	};

	// This isn't strictly necessary - but I've found it can crash if I
	// don't put this here. Odd.
	D3DDevice->SetCurrentViewport(Viewport);
};

void DXEngine::ReportError(char * text) {
	MessageBox(MainWindow,text,"Engine Problems",MB_OK);
}

void DXEngine::Flip()
{
	// Flip pages
	if (!Windowed) {
		while(FAILED(Primary->Flip(NULL,DDFLIP_WAIT)));
	} else {
		RECT dest;

		// get the window's rectangle in screen coordinates
		GetWindowRect(MainWindow, &dest);
		dest.left += WindowClientX0;
		dest.top += WindowClientY0;
		dest.right = dest.left + ScreenWidth;
		dest.bottom = dest.top + ScreenHeight;

		if (FAILED(Primary->Blt(&dest, BBuffer, NULL, DDBLT_WAIT,NULL))) {
			// Unable to blit, wonder why?
			ReportError("Blit failed");
			exit(10);
		};
	};
}
