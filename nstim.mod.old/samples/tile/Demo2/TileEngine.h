/////////////////////////////////////////////////////////////////////
// TileEngine.h 
//
// Headers for TileEngine class and supporting structures.
// TileEngine inherits DirectX functionality from its parent, and
// contains JUST the code required for the tile demonstration.
/////////////////////////////////////////////////////////////////////

#include "DXEngine.h"
#include "textures.h"

class CEngine : public DXEngine {
public:
	int ScrollX;
	CTexture *SampleTexture;

	CEngine();
	~CEngine();
	CEngine(HWND WinHandle, HINSTANCE AppHandle, int nx, int ny, int nbpp, int nWindowed);
	virtual void GameInit();
	virtual void GameMain();
	virtual void GameDone();

	void Demo2Render(int OffsetX, int OffsetY);
};