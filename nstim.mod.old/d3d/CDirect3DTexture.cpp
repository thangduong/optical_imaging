// CDirect3DTexture.cpp: implementation of the CDirect3DTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "CDirect3DTexture.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
int txtcnt = 0;
#endif

CDirect3DTexture::CDirect3DTexture()
{
#ifdef _DEBUG
	txtcnt++;
	char t[512];
	sprintf(t, "+tc = %d\r\n", txtcnt);
	OutputDebugString(t);
#endif
}

CDirect3DTexture::~CDirect3DTexture()
{
#ifdef _DEBUG
	txtcnt--;
	char t[512];
	sprintf(t, "-tc = %d\r\n", txtcnt);
	OutputDebugString(t);
#endif
}
