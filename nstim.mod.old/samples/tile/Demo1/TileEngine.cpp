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

	// Set the initial scroll position to offset 0
	ScrollX = 0;
};

void CEngine :: GameMain() {
	// Normally game logic would go here.... for now
	// just make the map scroll!
	ScrollX++;
	if (ScrollX > 64) ScrollX = 0;

	// Clear the back buffer (you don't HAVE to do this)
	FillSurface(BBuffer,0,NULL);

	// GameMain represents the main program loop
	Demo1Render(ScrollX, 0);

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
};

////////////////////////////////////////////////////////////////////////////
// Demo 1 rendering code
//
// Draws an isometric grid as an untextured wireframe. This demonstrates the
// use of TLVERTEX to describe screen coordinates, as well as being a good
// example of a regular isometric rendering scheme. It also shows how
// square tiles are broken into triangles to be represented by quads.
////////////////////////////////////////////////////////////////////////////

void CEngine::Demo1Render(int OffsetX, int OffsetY) {

	int ScreenX; // Where are we currently on the screen?
	int ScreenY;
	int WhereX; // Where are we currently rendering on the map?
	int WhereY;
	D3DTLVERTEX Vertex[4]; // vertex data - see below

	/////////////////////////
	// Start the scene; analagous to the same command in OpenGL
	D3DDevice->BeginScene();
	
	/////////////////////////
	// Set some render states.
	// You can save a few cycles per frame by only doing this once, but I
	// wanted them in here for clarity.
	
	// Don't use material properties - slow and don't work properly anyway
	D3DDevice->SetLightState(D3DLIGHTSTATE_MATERIAL,NULL);

	// Tell Direct3D to use wireframe rendering
	D3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_WIREFRAME);
	
	// Set each vertex to be white
	Vertex[0].color = D3DRGB(1.0f,1.0f,1.0f);
	Vertex[1].color = D3DRGB(1.0f,1.0f,1.0f);
	Vertex[2].color = D3DRGB(1.0f,1.0f,1.0f);
	Vertex[3].color = D3DRGB(1.0f,1.0f,1.0f);
	
	WhereY = 0;
	WhereX = 0;
	ScreenY = -16;
	while (ScreenY < ScreenHeight) {
		
		// Diamond tiles require an offset; every other line is half a tile spaced
		// differently. MOD is actually a little slow on some CPUs, so speed freaks 
		// would use a lookup although its not really worth the effort for 1-2 cycles.
		if ((WhereY % 2) == 1) {
			ScreenX = -64; // Start offscreen to make scrolling easy. Clipping is quick!
		} else {
			ScreenX = -96;
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
