#include "TileEngine.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

CEngine::CEngine(HWND WinHandle, HINSTANCE AppHandle, int nx, int ny, int nbpp, int nWindowed) {
	Init(WinHandle,AppHandle,nx,ny,nbpp,nWindowed);
};

CEngine::CEngine() {
	// Default constructor. C++ requires that it exist, but in this instance its not
	// going to be used.
};

CEngine::~CEngine() {
	// Destructor
};

void CEngine :: GameInit() {
	// GameInit is called when the game is about to start
	// All Window functions have already completed

	// Isn't inheritance wonderful? This call sets up DirectDraw and Direct3D.
	InitDirectX();

	// Load the texture
	SampleTexture = new CTexture;
	SampleTexture->LoadTexture("test.bmp",D3DDevice,DirectDraw);

	// Set the scroller
	ScrollX = 0;
};

void CEngine :: GameMain() {
	// GameMain represents the main program loop

	ScrollX++;
	if (ScrollX > 63) ScrollX = 0;

	Demo3Render(ScrollX,0);

	// Flip
	Flip();

	// check of user is trying to exit
	if (KEY_DOWN(VK_ESCAPE))
    {
		PostMessage(MainWindow, WM_DESTROY,0,0);
		
	} // end if
};

void CEngine :: GameDone() {
	// Game shutdown code goes here
	delete SampleTexture;
};

////////////////////////////////////////////////////////////////////////////
// Demo 3 rendering code
//
// Textured with full lighting

void CEngine::Demo3Render(int OffsetX, int OffsetY) {
	// Parameters. WorldX and WorldY specify where in the world array to start
	// rendering (top left). OffsetX/Y is a pixel offset, used for smooth scrolling
	// All you need to do is call Render(blah) every frame.

	int ScreenX; // Where are we currently on the screen?
	int ScreenY;
	int WhereX; // Where are we currently rendering on the map?
	int WhereY;
	D3DTLVERTEX Vertex[4]; // vertex data - see below

	// Again, an optimization would be to only do this once with a
	// static variable

	// Setup texture alignment
	Vertex[0].tu = 0.0f;
	Vertex[0].tv = 0.0f;
	Vertex[1].tu = 1.0f;
	Vertex[1].tv = 0.0f;
	Vertex[2].tu = 0.0f;
	Vertex[2].tv = 1.0f;
	Vertex[3].tu = 1.0f;
	Vertex[3].tv = 1.0f;

	// Set specular up even though it isn't used
	Vertex[0].specular = D3DRGB(1.0,1.0,1.0);
	Vertex[1].specular = D3DRGB(1.0,1.0,1.0);
	Vertex[2].specular = D3DRGB(1.0,1.0,1.0);
	Vertex[3].specular = D3DRGB(1.0,1.0,1.0);

	// RHW is a pain - set a dummy value to keep D3D quiet!
	Vertex[0].rhw = 1.0f;
	Vertex[1].rhw = 1.0f;
	Vertex[2].rhw = 1.0f;
	Vertex[3].rhw = 1.0f;
	
	/////////////////////////
	// Start the scene; analagous to the same command in OpenGL
	D3DDevice->BeginScene();
	
	/////////////////////////
	// Set some render states.
	// You can save a few cycles per frame by only doing this once, but I
	// wanted them in here for clarity.
	
	// Don't use material properties - slow and don't work properly anyway
	D3DDevice->SetLightState(D3DLIGHTSTATE_MATERIAL,NULL);

	D3DDevice->SetTexture(0,SampleTexture->Texture);
	
	WhereY = 0;
	WhereX = 0;
	ScreenY = -16;
	while (ScreenY < ScreenHeight) {
		
		// Diamond tiles require an offset; every other line is half a tile spaced
		// differently. MOD is actually a little slow on some CPUs, so speed freaks 
		// would use a lookup although its not really worth the effort for 1-2 cycles.
		if ((WhereY % 2) == 1) {
			ScreenX = -64;
		} else {
			ScreenX = -94;
		};
		
		while (ScreenX < ScreenWidth) {
			// Set vertex information for the tile
			// Vertices are arranged like this:
			//          1
			//         0 3
			//          2
			// There is plenty of room to optimize these assignments
			Vertex[0].sx = ScreenX + OffsetX;
			Vertex[0].sy = ScreenY+16 + OffsetY;
			Vertex[1].sx = ScreenX+32 + OffsetX;
			Vertex[1].sy = ScreenY + OffsetY;
			Vertex[2].sx = ScreenX+32 + OffsetX;
			Vertex[2].sy = ScreenY+32 + OffsetY;
			Vertex[3].sx = ScreenX+64 + OffsetX;
			Vertex[3].sy = ScreenY+16 + OffsetY;
			
			// Randomize the vertex colours. This is tacky, but it
			// demonstrates just how powerful D3D is!
			Vertex[0].color = D3DRGB(rand()/5000,rand()/5000,rand()/5000);
			Vertex[1].color = D3DRGB(rand()/5000,rand()/5000,rand()/5000);
			Vertex[2].color = D3DRGB(rand()/5000,rand()/5000,rand()/5000);
			Vertex[3].color = D3DRGB(rand()/5000,rand()/5000,rand()/5000);
			
			// Call DrawPrimitive to render the quad
			D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,Vertex,4,D3DDP_DONOTLIGHT | D3DDP_DONOTCLIP );

			// Make sure locations are correct
			ScreenX+=64;
			WhereX++;
		};
		
		WhereY++; // Move down the map
		WhereX = 0; // Start the next scanline
		ScreenY+=16; // Add half a tile height
	};
	
	// End the scene; some drivers won't have rendered ANYTHING until this called!
	D3DDevice->EndScene();
};