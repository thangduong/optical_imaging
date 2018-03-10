// CTestWnd.cpp: implementation of the CTestWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "CTestWnd.h"
#include "debug.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestWnd::CTestWnd()
{

}

CTestWnd::~CTestWnd()
{

}

LRESULT CTestWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch(uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		break;
		if (!m_Direct3DDevice.IsNull()) {
			//CDirect3DTexture s = m_Direct3DDevice.CreateTexture(50,50,0,D3DUSAGE_AUTOGENMIPMAP,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT);
#define Q  100
#define	QQ	1
			CDirect3DSurface a[Q*2];
			D3DLOCKED_RECT LockedRect;
			RECT r,r2;
			r.top = 0; r.left = 0;
			r.bottom = 100; r.right = 100;
			r2 = r;
			int p;
			for (p = 0; p < Q; p++)
			{
				a[p] = m_Direct3DDevice.CreateSurface(50,50,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT);
				debug.WriteDbgLine("myv.txt", "%d = %0.2f",  p, (double)m_Direct3DDevice->GetAvailableTextureMem()/(1024*1024));
			a[p]->LockRect(&LockedRect, NULL, D3DLOCK_DISCARD);	

			memset(LockedRect.pBits, p*2, LockedRect.Pitch*100);
			a[p]->UnlockRect();
			}
			for (p = 0; p < Q; p++)
			{
				a[p+Q] = m_Direct3DDevice.CreateSurface(200,100,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT);
				debug.WriteDbgLine("myv.txt", "%d = %0.2f",  p, (double)m_Direct3DDevice->GetAvailableTextureMem()/(1024*1024));
			a[p+Q]->LockRect(&LockedRect, NULL, D3DLOCK_DISCARD);	

			memset(LockedRect.pBits, 255-p*2, LockedRect.Pitch*100);
			a[p+Q]->UnlockRect();
			}
			CDirect3DSurface s = m_Direct3DDevice.CreateSurface(50,50,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT);
#ifdef _DEBUG
			if (s.IsNull())
				OutputDebugString("can't make surface\r\n ");
			else
				OutputDebugString("got surface\r\n");
#endif
			CDirect3DSurface ss = s;//.GetSurface(0);

#ifdef _DEBUG
			if (ss.IsNull())
				OutputDebugString("can't make surface\r\n ");
			else
				OutputDebugString("got surface\r\n");
#endif
			CDirect3DSurface bs = m_Direct3DDevice.GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO);



			m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,1.0f), 1.0f, 0 );
 			IDirect3DSwapChain9* sc;
			m_Direct3DDevice->GetSwapChain(0,&sc);
			D3DRASTER_STATUS rs;
			int N = 60;
			LARGE_INTEGER* li = new LARGE_INTEGER[N+100]; int q = 0;
//			QueryPerformanceFrequency(&li[q++]);
			IDirect3DDevice9* pD = m_Direct3DDevice.GetDirect3DDevice();
			int L = Q*2;
			for (int i = 0; i < N; i++) {
				do {
					sc->GetRasterStatus(&rs);
				} while (rs.InVBlank);
				m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );
				do {
					sc->GetRasterStatus(&rs);
				} while (!rs.InVBlank);
			QueryPerformanceCounter(&li[q++]);
			for (int l = 0; l < 160; l++) {
			r2.left += 1; r2.right += 1;
			if (r2.right > 500) {
				r2.left = 0;
				r2.right = 100;
				r2.top += 1;
				r2.bottom += 1;
			}
			HRESULT hr = m_Direct3DDevice->StretchRect(a[l%L].GetDirect3DSurface(), &r, bs.GetDirect3DSurface(), &r2, D3DTEXF_NONE);
			}
			//pD->
			}
			for (int j = 1; j < q; j++) {
				LARGE_INTEGER diff;
				diff.QuadPart = (__int64)li[j].QuadPart - (__int64)li[j-1].QuadPart;
				debug.WriteDbgLine("testwnd", "v[%d] = %d.%d:%d.%d", j, li[j].HighPart, li[j].LowPart,
					diff.HighPart, diff.LowPart);
				debug.WriteDbgLine("testwnda", "%d", diff.LowPart);
			}
		}
		break;
	}
	return CWnd::WindowProc(hwnd, uMsg, wParam, lParam);
}
