/////////////////////////////////////////////////////////////////////
// WinMain.cpp - minimal Win32 program
//
// This particular minimal Win32 implementation is based on Andr�
// LaMothe's code in Tricks of the Windows Game Programming Gurus.
/////////////////////////////////////////////////////////////////////

// Don't use MFC for this project
#define WIN32_LEAN_AND_MEAN 

#include <windows.h> // Basic Win32 Stuff
#include <windowsx.h> // Some useful macros reside in here
#include <mmsystem.h>
#include <ddraw.h>
#include "TileEngine.h" // Our Tile Engine

// Defines used for Window Details

/////////////////////////////////
// Defines for windows interface
/////////////////////////////////
// Note that this demo won't work too well if you change these
#define WINDOW_CLASS_NAME "WIN3DCLASS"  // class name
#define WINDOW_TITLE      "bEngine Demo"
#define WINDOW_WIDTH      800   // size of window
#define WINDOW_HEIGHT     600
#define WINDOW_BPP        16    // bitdepth of window (8,16,24 etc.)
#define WINDOWED_APP      FALSE // 0 not windowed, 1 windowed

/////////////////////////////////
// Global Variables - I try and keep them to a minimum
/////////////////////////////////

// This is the class that actually does all our work for us
// It is defined in TileEngine.cpp/TileEngine.h
CEngine *Engine;

// Vital Win32 Functions - again, pretty minimal stuff

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	// this is the main message handler of the system
	PAINTSTRUCT	ps;		   // used in WM_PAINT
	HDC			hdc;	   // handle to a device context
	
	// what is the message 
	switch(msg)
	{	
	case WM_CREATE: 
        {
			// do initialization stuff here
			return(0);
		} break;
		
    case WM_PAINT:
		{
			// start painting
			hdc = BeginPaint(hwnd,&ps);
			
			// end painting
			EndPaint(hwnd,&ps);
			return(0);
        } break;
		
	case WM_DESTROY: 
		{
			// kill the application			
			PostQuitMessage(0);
			return(0);
		} break;
		
	default:break;
		
    } // end switch
	
	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));
	
} // end WinProc

// WINMAIN ////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow) {
	// this is the winmain function
	
	WNDCLASS winclass;	// this will hold the class we create
	HWND	 hwnd;		// generic window handle
	MSG		 msg;		// generic message
	
	// first fill in the window class stucture
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; 
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	
	// register the window class
	if (!RegisterClass(&winclass))
		return(0);
	
	// create the window, note the test to see if WINDOWED_APP is
	// true to select the appropriate window flags
	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME, // class
						  WINDOW_TITLE,	 // title
						  (WINDOWED_APP ? (WS_OVERLAPPEDWINDOW) : (WS_POPUP | WS_VISIBLE)),
						  0,0,	   // x,y
						  WINDOW_WIDTH,  // width
                          WINDOW_HEIGHT, // height
						  NULL,	   // handle to parent 
						  NULL,	   // handle to menu
						  hinstance,// instance
						  NULL)))	// creation parms
						  return(0);
	
	// Pass Window Handle, Instance & Window Description to our engine
	Engine = new CEngine(hwnd,hinstance,WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_BPP,WINDOWED_APP);
	
	// resize the window so that client is really width x height
	if (Engine->Windowed)
	{
		// now resize the window, so the client area is the actual size requested
		// since there may be borders and controls if this is going to be a windowed app
		// if the app is not windowed then it won't matter
		RECT window_rect = {0,0,Engine->ScreenWidth,Engine->ScreenHeight};
		
		// make the call to adjust window_rect
		AdjustWindowRectEx(&window_rect,
			GetWindowStyle(hwnd),
			GetMenu(hwnd) != NULL,
			GetWindowExStyle(hwnd));
		
		// save the global client offsets, they are needed in DDraw_Flip()
		Engine->SetClientParams(-window_rect.left,-window_rect.top);
		
		// now resize the window with a call to MoveWindow()
		MoveWindow(hwnd,
			5, // x position
			5, // y position
			window_rect.right - window_rect.left, // width
			window_rect.bottom - window_rect.top, // height
			FALSE);
		
		// show the window, so there's no garbage on first render
		ShowWindow(hwnd, SW_SHOW);
	} // end if windowed
	
	// perform all game console specific initialization
	Engine->GameInit();
	
	// disable CTRL-ALT_DEL, ALT_TAB, comment this line out 
	// if it causes your system to crash
	SystemParametersInfo(SPI_SCREENSAVERRUNNING, TRUE, NULL, 0);
	
	// enter main event loop
	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;
			
			// translate any accelerator keys
			TranslateMessage(&msg);
			
			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
		// main game processing goes here
		Engine->GameMain();
		
	} // end while
	
	// shutdown game and release all resources
	Engine->GameDone();
	delete Engine;
	
	// enable CTRL-ALT_DEL, ALT_TAB, comment this line out 
	// if it causes your system to crash
	SystemParametersInfo(SPI_SCREENSAVERRUNNING, FALSE, NULL, 0);
	
	// return to Windows like this
	return(msg.wParam);
	
} // end WinMain