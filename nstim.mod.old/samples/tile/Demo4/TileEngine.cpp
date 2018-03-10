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
	ScrollXOffset = 0;
	Direction = 0;

	// Make the Demo Map
	MakeDemoMap();
};

void CEngine :: GameMain() {
	// GameMain represents the main program loop

	// Scroll Bounce - move right until you approach the edge,
	// and then go back the other way, ad infinitum
	if (Direction == 0) {
		ScrollXOffset--;
		if (ScrollXOffset < 1) {
			ScrollX++;
			ScrollXOffset = 63;
			if (ScrollX > 20) Direction = 1;
		};
	} else {
		ScrollXOffset++;
		if (ScrollXOffset > 63) {
			ScrollX--;
			ScrollXOffset = 0;
			if (ScrollX < 1) Direction = 0;
		};

	};

	Demo4Render(ScrollX,5,ScrollXOffset,0);

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
// Demo 4 rendering code
//
// Height-mapped, lit, textured scrolling landscape. Is it not nifty?

void CEngine::Demo4Render(int WorldX, int WorldY, int OffsetX, int OffsetY) {
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
	
	WhereY = WorldY;
	WhereX = WorldX;
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
			Vertex[0].sy = ScreenY+16 + OffsetY - Map[WhereX][WhereY].VertexHeight[0];
			Vertex[1].sx = ScreenX+32 + OffsetX;
			Vertex[1].sy = ScreenY + OffsetY  - Map[WhereX][WhereY].VertexHeight[1];
			Vertex[2].sx = ScreenX+32 + OffsetX;
			Vertex[2].sy = ScreenY+32 + OffsetY  - Map[WhereX][WhereY].VertexHeight[2];
			Vertex[3].sx = ScreenX+64 + OffsetX;
			Vertex[3].sy = ScreenY+16 + OffsetY  - Map[WhereX][WhereY].VertexHeight[3];
			
			Vertex[0].color = Map[WhereX][WhereY].VertexColor[0];
			Vertex[1].color = Map[WhereX][WhereY].VertexColor[1];
			Vertex[2].color = Map[WhereX][WhereY].VertexColor[2];
			Vertex[3].color = Map[WhereX][WhereY].VertexColor[3];
			
			// Set the texture
			D3DDevice->SetTexture(0,SampleTexture->Texture);

			// Call DrawPrimitive to render the quad
			D3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,Vertex,4,D3DDP_WAIT);

			// Make sure locations are correct
			ScreenX+=64;
			WhereX++;
		};
		
		WhereY++; // Move down the map
		WhereX = WorldX; // Start the next scanline
		ScreenY+=16; // Add half a tile height
	};
	
	// End the scene; some drivers won't have rendered ANYTHING until this called!
	D3DDevice->EndScene();
};

void CEngine::MakeDemoMap() {
	int x,y;
	int DeltaX; // Multiplier
	int Value; // Used to calculate height
	D3DCOLOR Color; // Used to calculate vertex shading
	float Percentage; // ditto

	for (y=2; y<62; y++) {
		for (x=2; x<62; x++) {
			DeltaX = 1-(y % 2); // 1 for even, 0 for odd
			Value = rand()%10;
			if (y == 20) Value = 10; // I want a flat walkway!
			if (y == 21) Value = 10; // I want a flat walkway!
			Percentage = (float)Value/10.0f;
			Color = D3DRGB(Percentage,Percentage,Percentage);

			// This tile's west most vertex
			Map[x][y].VertexHeight[0] = Value;
			Map[x][y].VertexColor[0] = Color;

			// SW tile's northern vertex
			Map[x-DeltaX][y+1].VertexHeight[1] = Value;
			Map[x-DeltaX][y+1].VertexColor[1] = Color;

			// NW tile's southern vertex
			Map[x-DeltaX][y-1].VertexHeight[2] = Value;
			Map[x-DeltaX][y-1].VertexColor[2] = Color;

			// West Tile's East most vertex
			Map[x-1][y].VertexHeight[3] = Value;
			Map[x-1][y].VertexColor[3] = Color;

			Map[x][y].Texture = (x % 2);
		};
	};
};