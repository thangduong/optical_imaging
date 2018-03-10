/////////////////////////////////////////////////////////////////////
// TileEngine.h 
//
// Headers for TileEngine class and supporting structures.
// TileEngine inherits DirectX functionality from its parent, and
// contains JUST the code required for the tile demonstration.
/////////////////////////////////////////////////////////////////////

#include "DXEngine.h"
#include "textures.h"

class tMapNode {
public:
	int VertexHeight[4];
	D3DCOLOR VertexColor[4];
	int Texture;
};

class CEngine : public DXEngine {
public:
	CTexture *SampleTexture;
	int ScrollXOffset;
	int ScrollX;
	int Direction;

	tMapNode Map[64][64];

	CEngine();
	~CEngine();
	CEngine(HWND WinHandle, HINSTANCE AppHandle, int nx, int ny, int nbpp, int nWindowed);
	virtual void GameInit();
	virtual void GameMain();
	virtual void GameDone();
	void MakeDemoMap();

	void Demo4Render(int WorldX, int WorldY, int OffsetX, int OffsetY);
};