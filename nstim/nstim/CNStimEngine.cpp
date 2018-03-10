////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNStimEngine	Code for stimulation graphics engine
//
// REVISION HISTORY
//
//	10/2/2005	Thang		- added this header
//							- added code for viewport manipulation.  not sure if it works yet
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CNStimEngine.h"
#include "debug.h"
#include <d3d9.h>
#include <d3d9types.h>

CNStimEngine* CNStimEngine::m_pTheStimEngine = 0;

struct ViewportItem {
	struct _D3DVIEWPORT9 Viewport;
	char* pName;
	ViewportItem* pNext;
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimEngine::CNStimEngine() : m_iCount(1)
{

	m_pTheStimEngine = this;

	m_bShouldStop = false;
	m_hStateChangeEvent = CreateEvent(0, false, false, 0);
	m_hStateChangedEvent = CreateEvent(0, false, false, 0);
	m_iStateParam = 0;

	m_BkColor = 0x808080;

	// VIEWPORT code
//	m_pFirstVp = 0;
//	m_pLastVp = 0;
	m_ViewportCenterX = m_ViewportCenterY = 0;
	// END VIEWPORT cope


	m_pSequencer = new CNStimSequence;
}

CNStimEngine::~CNStimEngine()
{
	delete m_pSequencer;
	CloseHandle(m_hStateChangeEvent);
}

void CNStimEngine::PrepareDeviceFor2D()
{
	// Turn off culling, so we see the front and back of primitives
//	m_Direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Enable alpha blended transparency.
/*	HRESULT hr = m_Direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = m_Direct3DDevice->SetRenderState(
		D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	hr = m_Direct3DDevice->SetRenderState(
		D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
*/
	// Allow modulation of the texture's and diffuse colour's alpha.
	// By default, the texture and diffuse colour's RGB are modulated.
	// This lets us create transparency and tinting effects by setting 
	// the (diffuse) colour in Blit().
/*	for (int i = 0; i < 8; i++ ) {
	m_Direct3DDevice->SetTextureStageState(
		i, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_Direct3DDevice->SetTextureStageState(
		i, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_Direct3DDevice->SetTextureStageState(
		i, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	}
//   m_Direct3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
   //m_Direct3DDevice->SetVertexShader(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
*/
	m_Direct3DDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
	m_Direct3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	m_Direct3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
}



ULONG __stdcall CNStimEngine::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimEngine::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimEngine)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else if (iid == IID_IUnknown)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	return hr;
}

ULONG __stdcall CNStimEngine::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}


bool CNStimEngine::Init(const CSmartPtr<INStimProfile>& Profile) 
{
	bool bResult = false;
	m_Profile = Profile;
	if (m_Direct3D.Init())
	{
		int iWidth, iHeight;
		if (m_Profile->IsFullscreen() != S_FALSE)
		{
			int framerate;
			m_Profile->GetFullscreenResolution(&iWidth, &iHeight, &framerate);
			bResult = m_Direct3DWnd.CreateFullscreen(m_Direct3D, "NStimEngine", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 50, 50, iWidth, iHeight, D3DFMT_A8R8G8B8, framerate);
			m_Direct3DDevice = m_Direct3DWnd.m_Direct3DDevice;
			m_DisplayMode.Width = iWidth;
			m_DisplayMode.Height = iHeight;
			m_DisplayMode.RefreshRate = framerate;
			m_DisplayMode.Format = (enum _D3DFORMAT)0;
		}
		else
		{
			m_Profile->GetWindowedResolution(&iWidth, &iHeight);
			bResult = m_Direct3DWnd.Create(m_Direct3D, "NStimEngine", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, iWidth, iHeight);
			m_Direct3DDevice = m_Direct3DWnd.m_Direct3DDevice;
			m_Direct3DDevice->GetDisplayMode(0,&m_DisplayMode);
			m_DisplayMode.Width = iWidth;
			m_DisplayMode.Height = iHeight;
		}
		if (!bResult) {
			MessageBox(m_Direct3DWnd.GetHwnd(), "Can't create Direct3D Window.  Bailing out.", "ERROR", MB_ICONERROR);
			return false;
		}

		int port;
		Profile->GetLptSyncPortInfo(&port, &m_iPreFrameBit, &m_iPostFrameBit, &m_iStimOnStrobeBit, &m_iFrameDropBit);
		m_LptPort.Init();
		m_LptPort.SetPortNum(port);
		m_LptPort.SetPortVal(0);
		m_WholeScreenVp.X = 0;
		m_WholeScreenVp.Y = 0;
		m_WholeScreenVp.Width = iWidth;
		m_WholeScreenVp.Height = iHeight;
		m_WholeScreenVp.MinZ = 0;
		m_WholeScreenVp.MaxZ = 1;

		// initialize the gamma ramp
		FILE* fp = fopen("default.lut", "rb");
		if (fp)  {
			fread(ramp.red, 256, 2, fp);
			fread(ramp.green, 256, 2, fp);
			fread(ramp.blue, 256, 2, fp);
			fclose(fp);
		}
		else {
			for (int i = 0; i < 256; i++) {
				ramp.red[i] = i << 8;
				ramp.green[i] = i << 8;
				ramp.blue[i] = i << 8;
			}
		}
		m_Direct3DDevice->SetGammaRamp(0,D3DSGR_NO_CALIBRATION,&ramp);
	}
	return bResult;
}

HRESULT __stdcall CNStimEngine::SetState(DWORD state)
{
	m_iLastState = m_iState;
	m_iState = state;
	SetEvent(m_hStateChangeEvent);
	WaitForSingleObject(m_hStateChangedEvent, INFINITE);
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetState(DWORD* pState)
{
	if (pState)
		(*pState) = m_iState;
	return S_OK;
}


HRESULT __stdcall CNStimEngine::Stop()
{
	m_bShouldStop = true;
	SetEvent(m_hStateChangeEvent);
	WaitForSingleObject(m_hStateChangedEvent, INFINITE);
	return S_OK;
}

HRESULT __stdcall CNStimEngine::Snap(const unsigned char* filename) {	
	// now save
	IDirect3DSurface9* pBkSurf = 0;
	
	m_Direct3DDevice->GetRenderTarget(0,&pBkSurf);
	D3DSURFACE_DESC BkSurfDesc;
	pBkSurf->GetDesc(&BkSurfDesc);
	
	
	
	CDirect3DSurface surf = m_Direct3DDevice.CreateSurface(BkSurfDesc.Width,BkSurfDesc.Height,BkSurfDesc.Format,D3DPOOL_SYSTEMMEM);
	
	HRESULT hr = m_Direct3DDevice->GetRenderTargetData(pBkSurf, surf.GetDirect3DSurface());
	pBkSurf->Release();

	D3DLOCKED_RECT lr;
	surf->LockRect(&lr,0,0);
	FILE* fp = fopen((char*)filename, "wb");
	
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	memset(&bfh,0,sizeof(bfh));
	memset(&bih, 0, sizeof(bih));
	bfh.bfType = 0x4d42;    // 0x42 = "B" 0x4d = "M"
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + BkSurfDesc.Height*BkSurfDesc.Width*3 + sizeof(BITMAPINFOHEADER);
	bfh.bfOffBits = (DWORD)   sizeof(BITMAPFILEHEADER) +
	                          sizeof(BITMAPINFOHEADER);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	
	bih.biBitCount = 24;
	bih.biClrImportant = 0;
	bih.biClrUsed = 0;
	bih.biCompression = BI_RGB;
	bih.biHeight = BkSurfDesc.Height;
	bih.biWidth = BkSurfDesc.Width;
	bih.biSize = sizeof(bih);
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biPlanes = 1;
	
	char* temp = new char[3*bih.biHeight*bih.biWidth];
	char* src = (char*)lr.pBits;
	char* dest = temp + 3*(bih.biHeight-1) * bih.biWidth;
	for (int y = 0; y < bih.biHeight; y++) {
	
		 if (BkSurfDesc.Format == D3DFMT_R5G6B5) {
			 for (int x = 0; x < bih.biWidth; x++) {
				dest[x*3 + 0] = ((((WORD*)src)[x]&0x1f) << 3);
				dest[x*3 + 1] = (((((WORD*)src)[x]&0x3e0) >> 5)<<2);
				dest[x*3 + 2] = (((((WORD*)src)[x]&0xf800) >> 11)<<3);
			 }
		 } else if ((BkSurfDesc.Format == D3DFMT_A8R8G8B8)||(BkSurfDesc.Format == D3DFMT_X8R8G8B8)) {
			 for (int x = 0; x < bih.biWidth; x++) {
			 	dest[x*3 + 0] = src[x*4+0];
				dest[x*3 + 1] = src[x*4+1];
				dest[x*3 + 2] = src[x*4+2];
				if ((src[x*4+0] > 130) ||
					(src[x*4+1] > 130) ||
					(src[x*4+2] > 130) ||
					(src[x*4+3] > 130)) {
					DebugBreak();
				}
			 }
		 }
		 src = src + lr.Pitch;
		 dest = dest - 3 * bih.biWidth;
	 }
	
	 fwrite(&bfh,sizeof(bfh),1,fp);
	 fwrite(&bih, sizeof(bih),1,fp);
	
	fwrite(temp, bih.biWidth*bih.biHeight, 3, fp);
	fclose(fp);
	delete [] temp;
	
		
	surf->UnlockRect();
	
	return S_OK;
}

HRESULT __stdcall CNStimEngine::CalibFramerate(int NFRAMES) {
	if (NFRAMES==0)
		NFRAMES = 500;
	// determine the number of ticks per frame (by roughly averaging N frames)
	// TODO: refine this code!
	LARGE_INTEGER start, end;
	int numFrames = 0;
	QueryPerformanceCounter(&end);
	int PREFRAME = 100;
	int POSTFRAME = 100;
	LARGE_INTEGER junk[2000];
	for (int i = 0; i < (NFRAMES+1+PREFRAME+POSTFRAME); i++) {

		m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE((float)(i%255)/255,(float)(i%255)/255,(float)(i%255)/255,1.0f), 0.0f, 0 );
		m_LptPort.ToggleBit(m_iPreFrameBit);
		m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );
		start = end;
		QueryPerformanceCounter(&end);

		if (i>0) {
			LARGE_INTEGER diff;
			diff.QuadPart = end.QuadPart - start.QuadPart;

			if ((i>PREFRAME) && (i<=NFRAMES+1+PREFRAME)) {
				TicksPerFrame += diff.QuadPart;
				junk[numFrames] = end;
				numFrames++;
				
			}
		}
	
	}
	m_dFramerate = ((double)Frequency.QuadPart*(double)numFrames/(double)TicksPerFrame);
	TicksPerFrame /= numFrames;

	HalfTicksPerFrame = TicksPerFrame / 2;

	char filename[512];
	char logPath[512];
	m_Profile->GetLogPath((unsigned char*)logPath);
	sprintf(filename, "%s\\framerate.calibration.txt", logPath);
	FILE* fp = fopen(filename, "wb");
	fprintf(fp, "freq = %08x,%08x\r\n", Frequency.LowPart, Frequency.HighPart);
	for (int q = 0; q < numFrames; q++) {
		fprintf(fp, "%08x,%08x\r\n", junk[q].LowPart, junk[q].HighPart);
	}
	fprintf(fp, "m_dFramerate = %0.10f\r\n", m_dFramerate);
	fprintf(fp, "TicksPerFrame = %x\r\n", TicksPerFrame);
	fclose(fp);
	return S_OK;
}

HRESULT __stdcall CNStimEngine::Run()
{
	if (m_Profile->ShouldHideCursor()==S_OK)
		ShowCursor(FALSE);

	int priority;
	m_Profile->GetGraphicsEngineThreadPriority(&priority);
	SetThreadPriority(GetCurrentThread(), priority);

	int iFrameCounter = 0;
	bool done = false;
	IDirect3DSwapChain9* sc;
	m_Direct3DDevice->GetSwapChain(0,&sc);
//	D3DRASTER_STATUS rs;
	m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,1.0f), 0.0f, 0 );
	m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );
	m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,1.0f), 0.0f, 0 );

	PrepareDeviceFor2D();

	LARGE_INTEGER Counter;
	LARGE_INTEGER Prev;
//	LARGE_INTEGER ProfStart, ProfEnd;
	Frequency.QuadPart = 0;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Counter);

	TicksPerFrame = 0;

	// determine the number of ticks per frame (by roughly averaging N frames)
	// TODO: refine this code!
//	LARGE_INTEGER start, end;
//	QueryPerformanceCounter(&end);
	CalibFramerate(500);

#define	N					1024
	m_iStateParam = 60*30;
	m_iState = GE_IDLE;//GE_STIMULATING;//GE_IDLE;
	m_iRunNumber = 0;
	while (!m_bShouldStop)
	{
		m_LptPort.SetPortVal(0);
		if (m_iState == GE_PAUSE)
		{
			WaitForSingleObject(m_hStateChangeEvent, INFINITE);
			SetEvent(m_hStateChangedEvent);
		}
		else if (m_iState == GE_STIMULATING)
		{
			bool interrupted = false;			
			CList<INStimAtom*,INStimAtom*>* pTempAtomList = 0;//&m_AtomList;

			INStimAtom* pAtom;

			m_pSequencer->Compile(this);

			POSITION plhp = m_AtomList.GetHeadPosition();
			while (plhp) {
				m_AtomList.GetNext(plhp)->Reset(this);
			}

#define	PREPERIOD				-5

			LARGE_INTEGER* log = new LARGE_INTEGER[m_iStateParam+60-PREPERIOD];
			int* drawingTime = new int[m_iStateParam+60-PREPERIOD];
			int* presentTime = new int[m_iStateParam+60-PREPERIOD];
			int* fcl = new int[m_iStateParam+60-PREPERIOD];
			memset(log, 0, (m_iStateParam+60-PREPERIOD)*sizeof(log[0]));
			memset(fcl, 0, (m_iStateParam+60-PREPERIOD)*sizeof(fcl[0]));
			memset(drawingTime, 0, (m_iStateParam+60-PREPERIOD)*sizeof(drawingTime[0]));
			memset(presentTime, 0, (m_iStateParam+60-PREPERIOD)*sizeof(presentTime[0]));

			int iFrameCount = PREPERIOD;
			int framesPassed = 1;
			LARGE_INTEGER PreDraw;
			LARGE_INTEGER PrePresent;
			QueryPerformanceCounter(&Prev);
			while ((iFrameCount < m_iStateParam) && (!interrupted))
			{
				QueryPerformanceCounter(&PreDraw);

				m_pSequencer->GetAtomList(iFrameCount, &pTempAtomList, this);
				m_Direct3DDevice->SetViewport(&m_WholeScreenVp);
				m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
											m_BkColor/* 0x808080 /*framesPassed*50*/, 0.0f, 0 );
				if (pTempAtomList)
				{
					// toggle frame drop bit
					if (framesPassed > 1) {
						m_LptPort.ToggleBit(m_iFrameDropBit);
					}

					// compensate for lost frames
					while (framesPassed > 0) {
						POSITION pos = pTempAtomList->GetHeadPosition();
						while (pos)
						{
							pAtom = pTempAtomList->GetNext(pos);
							pAtom->AdvanceFrame(1);
						}
						iFrameCount+=1; framesPassed--;
						m_pSequencer->GetAtomList(iFrameCount, &pTempAtomList, this);
					}

					m_Direct3DDevice->BeginScene();
					POSITION pos = pTempAtomList->GetHeadPosition();
					while (pos)
					{
						pAtom = pTempAtomList->GetNext(pos);
						pAtom->Exec(this);
					}
					m_Direct3DDevice->EndScene();
				}
				QueryPerformanceCounter(&Counter);
				PreDraw.QuadPart = Counter.QuadPart-PreDraw.QuadPart;
				drawingTime[iFrameCount-PREPERIOD] = PreDraw.LowPart;
		
				m_LptPort.ToggleBit(m_iPreFrameBit);

				QueryPerformanceCounter(&PrePresent);

				m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );

				QueryPerformanceCounter(&Counter);

				PrePresent.QuadPart = Counter.QuadPart - PrePresent.QuadPart;
				presentTime[iFrameCount-PREPERIOD] = PrePresent.LowPart;

				Prev.QuadPart = Counter.QuadPart-Prev.QuadPart;
				framesPassed = (Prev.QuadPart+HalfTicksPerFrame) / TicksPerFrame;

				if (iFrameCount == 0)
					m_LptPort.SetBit(m_iStimOnStrobeBit, 1);
				log[iFrameCount-PREPERIOD] = Prev;
				fcl[iFrameCount-PREPERIOD] = framesPassed;
				Prev=Counter;
				framesPassed--;

				m_LptPort.ToggleBit(m_iPostFrameBit);
		
				iFrameCount+=1;

				interrupted = (WaitForSingleObject(m_hStateChangeEvent,0)==WAIT_OBJECT_0) ? true : false;
			}
			m_LptPort.SetBit(m_iStimOnStrobeBit, 0);
			if (!interrupted)
				m_iState = m_iLastState;
			else {
				SetEvent(m_hStateChangedEvent);
			}

			char logfile[512];
			if (strlen(m_StimName) > 0) 
				sprintf(logfile, "nstim_timing_%s.log", m_StimName);
			else
				sprintf(logfile, "run%d.log", m_iRunNumber++);
			debug.WriteDbgLine(logfile, "freq = %x", Frequency.QuadPart);
			debug.WriteDbgLine(logfile, "PREPERIOD = %d", PREPERIOD);
			debug.WriteDbgLine(logfile, "Ticks per frame = %x", TicksPerFrame);
			debug.WriteDbgLine(logfile, "frame	frmSkipped	ticksPassed		drawingTime");
			for (int i = 0; i < (iFrameCount - PREPERIOD); i++) 
				debug.WriteDbgLine(logfile, "%d	%d		%d	%d	%d	%d", i, fcl[i], 
				   log[i].LowPart, log[i].HighPart, 
					drawingTime[i], presentTime[i]);
			debug.Purge(logfile);
			delete [] log;
		}
		else if (m_iState == GE_SIMULATING)
		{
			bool interrupted = false;			
			CList<INStimAtom*,INStimAtom*>* pTempAtomList = 0;//&m_AtomList;

			INStimAtom* pAtom;

			m_pSequencer->Compile(this);

			POSITION plhp = m_AtomList.GetHeadPosition();
			while (plhp) {
				m_AtomList.GetNext(plhp)->Reset(this);
			}

#define	PREPERIOD				-5

			int iFrameCount = PREPERIOD;
			char filename[512];
			char logPath[512];
			m_Profile->GetLogPath((unsigned char*)logPath);
			sprintf(filename, "%s\\%s", logPath, m_StimName);
			CreateDirectory(filename, 0);
			while ((iFrameCount < m_iStateParam) && (!interrupted))
			{
				iFrameCount+=1;

				m_pSequencer->GetAtomList(iFrameCount, &pTempAtomList, this);
				m_Direct3DDevice->SetViewport(&m_WholeScreenVp);
				m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
											m_BkColor/* 0x808080 /*framesPassed*50*/, 0.0f, 0 );
				if (pTempAtomList)
				{
					m_Direct3DDevice->BeginScene();
					POSITION pos = pTempAtomList->GetHeadPosition();
					while (pos)
					{
						pAtom = pTempAtomList->GetNext(pos);
						if (FAILED(pAtom->Exec(this)))
						{
							// something's wrong
						}
					}
					m_Direct3DDevice->EndScene();
				}
				sprintf(filename, "%s\\%s\\%s.%04d.bmp", logPath, m_StimName, m_StimName, iFrameCount-PREPERIOD);
				Snap((unsigned char*)filename);

				interrupted = (WaitForSingleObject(m_hStateChangeEvent,0)==WAIT_OBJECT_0) ? true : false;
			}
			if (!interrupted)
				m_iState = m_iLastState;
			else {
				SetEvent(m_hStateChangedEvent);
			}
		}
		else// if (m_iState == GE_PREVIEW) 
		{
			// idling
			MSG msg;
			int iLogCounter = 0;
			int framesPassed = 1;
			INStimAtom* pAtom;
			LARGE_INTEGER* log = new LARGE_INTEGER[N];
			memset(log, 0, N*sizeof(log[0]));
			CList<INStimAtom*,INStimAtom*>* pTempAtomList = &m_AtomList;
			while (WaitForSingleObject(m_hStateChangeEvent,0)==WAIT_TIMEOUT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT)
					{
						m_bShouldStop = true;
						break;
					}

					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}


				m_Direct3DDevice->SetViewport(&m_WholeScreenVp);
				m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET,// | D3DCLEAR_ZBUFFER,
											 m_BkColor /*framesPassed*50*/, 0.0f, 0 );
				if (pTempAtomList)
				{
					if ((--framesPassed) > 0)
					{
						// frame dropped
						m_LptPort.ToggleBit(m_iFrameDropBit);

						POSITION pos = pTempAtomList->GetHeadPosition();
						while (pos)
						{
							pAtom = pTempAtomList->GetNext(pos);
							pAtom->AdvanceFrame(framesPassed);
						}
					}

					m_Direct3DDevice->BeginScene();
					POSITION pos = pTempAtomList->GetHeadPosition();
					while (pos)
					{
						pAtom = pTempAtomList->GetNext(pos);
						if (pAtom->Preview() == S_OK) {
							if (FAILED(pAtom->Exec(this)))
							{
								// something's wrong
							}
						}
					}
					m_Direct3DDevice->EndScene();
				}
		
				// wait for vertical retrace before presenting
/*				do {
					sc->GetRasterStatus(&rs);
				} while (!rs.InVBlank);
*/
				m_LptPort.ToggleBit(m_iPreFrameBit);
				m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );

				QueryPerformanceCounter(&Counter);
				Prev.QuadPart = Counter.QuadPart-Prev.QuadPart;
				framesPassed = (Prev.QuadPart) / TicksPerFrame;
				log[iLogCounter] = Prev; iLogCounter=((iLogCounter+1)%N);
				Prev=Counter;

				m_LptPort.ToggleBit(m_iPostFrameBit);
		
				// wait until the frame is displayed
/*				do {
					sc->GetRasterStatus(&rs);
				} while (rs.InVBlank);
*/				// send out the LPT signal
			}

			debug.WriteDbgLine("timelog.txt", "freq = %x", Frequency.QuadPart);
			for (int i = 0; i < N; i++) 
				debug.WriteDbgLine("timelog.txt", "%x", log[i].QuadPart);
			delete [] log;
			SetEvent(m_hStateChangedEvent);
		}
/*		else
		{
			// idling
			MSG msg;
			int iLogCounter = 0;
			m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
										 m_BkColor , 1.0f, 0 );
			m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );
			while (WaitForSingleObject(m_hStateChangeEvent,0)==WAIT_TIMEOUT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT)
					{
						m_bShouldStop = true;
						break;
					}

					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			SetEvent(m_hStateChangedEvent);
		}
		*/
	}
	
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);

	if (m_Profile->ShouldHideCursor()==S_OK)
		ShowCursor(TRUE);
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetDirect3DDevice(IDirect3DDevice9** pDevice)
{
	if (pDevice)
	{
		(*pDevice) = m_Direct3DDevice.GetDirect3DDevice();
		(*pDevice)->AddRef();
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::AddAtom(INStimAtom* pAtom)
{
	pAtom->AddRef();
	m_AtomList.AddTail(pAtom);

/*	POSITION p = m_AtomList.GetHeadPosition();
	while (p)
	{
		char* temp;
		INStimAtom* pp = m_AtomList.GetNext(p);
		pp->GetName((unsigned char**)&temp);
		OutputDebugString(temp);
	}
	OutputDebugString("\r\n");
	*/
	return S_OK;
}

HRESULT __stdcall CNStimEngine::RemoveAtom(INStimAtom* pAtom)
{
	POSITION pos = m_AtomList.GetHeadPosition();
	while (pos)
	{
		POSITION oldPos = pos;
		if (pAtom == m_AtomList.GetNext(pos))
		{
			pAtom->Release();
			m_AtomList.RemoveAt(oldPos);
		}
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::FindAtom(unsigned char* pName, INStimAtom** ppAtom)
{
/*	POSITION p = m_AtomList.GetHeadPosition();
	while (p)
	{
		char* temp;
		INStimAtom* pp = m_AtomList.GetNext(p);
		pp->GetName((unsigned char**)&temp);
		OutputDebugString(temp);
	}
	OutputDebugString("\r\n");
	*/
	POSITION pos = m_AtomList.GetHeadPosition();
	(*ppAtom) = 0;
	while (pos)
	{
		INStimAtom* pCurAtom = m_AtomList.GetNext(pos);
		if (pCurAtom->IsAtom(pName) == S_OK)
			(*ppAtom) = pCurAtom;
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetAtomCount(int* pAtomCount)
{
	(*pAtomCount) = m_AtomList.GetCount();
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetAtom(int iAtomIndex, INStimAtom** ppAtom)
{
	POSITION pos = m_AtomList.FindIndex(iAtomIndex);
	if (pos)
		(*ppAtom) = m_AtomList.GetAt(pos);

	return S_OK;
}


HRESULT __stdcall CNStimEngine::ClearAtom() {
	while (!m_AtomList.IsEmpty()) {
		m_AtomList.RemoveHead()->Release();
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::ClearSequence() {
	m_pSequencer->Clear();
	return S_OK;
}

// VIEWPORT manipulation code
/*
HRESULT __stdcall CNStimEngine::AddViewport(unsigned char* pName, struct _D3DVIEWPORT9* pViewport) {
	ViewportItem* pCurItem = new ViewportItem;
	memcpy(&(pCurItem->Viewport), pViewport, sizeof(*pViewport));
	pCurItem->pName = new char[strlen((char*)pName)+1];
	strcpy(pCurItem->pName, (char*)pName);
	pCurItem->pNext = 0;

	if (m_pFirstVp == 0) {
		m_pFirstVp = m_pLastVp = pCurItem;
	}
	else {
		m_pLastVp->pNext = pCurItem;
		m_pLastVp = pCurItem;
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::FindViewport(unsigned char* pName, int* pIndex) {
	ViewportItem* pCurItem = m_pFirstVp;
	if (pIndex)
		(*pIndex) = -1;
	int curIndex = 0;
	while (pCurItem) {
		if (strcmpi(pCurItem->pName, (char*)pName) == 0) {
			if (pIndex)
				(*pIndex) = curIndex;
			break;
		}
		else {
			curIndex++;
			pCurItem = pCurItem->pNext;
		}
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetViewport(int index, unsigned char** pName, struct _D3DVIEWPORT9* pViewport) {
	ViewportItem* pCurItem = m_pFirstVp;
	while (pCurItem && (index > 0)) {
		pCurItem = pCurItem->pNext;
	}
	if (pCurItem) {
		if (pName) {
			(*pName) = (unsigned char*)pCurItem->pName; 
		}
		if (pViewport) {
			memcpy(pViewport, &(pCurItem->Viewport), sizeof(pCurItem->Viewport));
		}
	}
	else {
		if (pName) {
			(*pName) = 0;
		}
		if (pViewport) {
			memset(pViewport, 0, sizeof(*pViewport));
		}
	}
	
	return S_OK;
}

HRESULT __stdcall CNStimEngine::SelectViewport(int index) {
	ViewportItem* pCurItem = m_pFirstVp;
	while (pCurItem && (index > 0)) {
		pCurItem = pCurItem->pNext;
		index--;
	}
	if (pCurItem) {
		m_pCurrentVp = pCurItem;
		m_Direct3DDevice->SetViewport(&(pCurItem->Viewport));
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::SelectViewportByName(unsigned char* pName) {
	ViewportItem* pCurItem = m_pFirstVp;
	while (pCurItem) {
		if (strcmpi(pCurItem->pName, (char*)pName) == 0) {
			break;
		}
		else {
			pCurItem = pCurItem->pNext;
		}
	}
	if (pCurItem) {
		m_pCurrentVp = pCurItem;
		m_Direct3DDevice->SetViewport(&(pCurItem->Viewport));
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::GetCurrentViewport(unsigned char** pName, struct _D3DVIEWPORT9* pViewport) {
	if (pName) {
		(*pName) = (unsigned char*)m_pCurrentVp->pName;
	}
	if (pViewport) {
		memcpy(pViewport, &(m_pCurrentVp->Viewport), sizeof(*pViewport));
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::DeleteViewport(int index) {
	ViewportItem* pCurItem = m_pFirstVp;
	ViewportItem* pBefore = 0;
	while (pCurItem && (index > 0)) {
		pBefore = pCurItem;
		pCurItem = pCurItem->pNext;
		index--;
	}
	if (pCurItem) {
		if (pBefore) {
			pBefore->pNext = pCurItem->pNext;
		}
		else {
			m_pFirstVp = pCurItem->pNext;
		}

		delete [] pCurItem->pName;
		delete pCurItem;
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::DeleteViewportByName(unsigned char* pName) {
	ViewportItem* pCurItem = m_pFirstVp;
	ViewportItem* pBefore = 0;
	while (pCurItem) {
		if (strcmpi(pCurItem->pName, (char*)pName) == 0) {
			break;
		}
		else {
			pBefore = pCurItem;
			pCurItem = pCurItem->pNext;
		}
	}
	if (pCurItem) {
		if (pBefore) {
			pBefore->pNext = pCurItem->pNext;
		}
		else {
			m_pFirstVp = pCurItem->pNext;
		}

		delete [] pCurItem->pName;
		delete pCurItem;
	}
	return S_OK;
}

HRESULT __stdcall CNStimEngine::CountViewport(int* pCount) {
	if (pCount) {
		(*pCount) = 0;
		ViewportItem* pCurItem = m_pFirstVp;
		while (pCurItem) {
			pCurItem = pCurItem->pNext;
			(*pCount)++;
		}
	}
	return S_OK;
}
*/

HRESULT CNStimEngine::ApplyViewport(struct _D3DVIEWPORT9* pViewport)  {
	return m_Direct3DDevice->SetViewport(pViewport);
}

// END VIEWPORT code
