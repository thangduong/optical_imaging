// CDirect3D.cpp: implementation of the CDirect3D class.
//
//////////////////////////////////////////////////////////////////////

#include "CDirect3D.h"
#include "debug.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirect3D::CDirect3D()
{
	CoInitialize(NULL);

}

CDirect3D::~CDirect3D()
{

}

bool CDirect3D::Init()
{
	IDirect3D9* pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pDirect3D == 0) {
		MessageBox(0, "can't create directx 9", "error", 0);
		ExitProcess(-1);
	}
	m_Direct3D = pDirect3D;
	int v = pDirect3D->Release();

	if (m_Direct3D.IsNull()) {
		debug.WriteDbgLine("CDirect3D", "Init() : Direct3DCreate9 returned NULL");
	}

	return !m_Direct3D.IsNull();
}

