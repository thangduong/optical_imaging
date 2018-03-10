#ifndef CWINAPP_H
#define CWINAPP_H

#include <windows.h>
#include "CMapHwndPtr.h"

class CWnd;
class CDialog;

class CWinApp  
{
public:
	CWinApp(HINSTANCE hInstance = NULL, HINSTANCE hPrevInstance = NULL,
		LPSTR lpCmdLine = NULL, int nShowCmd = 0);
	virtual ~CWinApp();

	void SetParam(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nShowCmd);


	// inheritable functions
	virtual bool Init();
	virtual void MessagePump();
	virtual int Cleanup();

	void ShowBusyCursor();
	void HideBusyCursor();



	// these functions need HINSTANCE
	HMENU LoadMenu(LPCTSTR lpMenuName);
	HICON LoadIcon(LPCTSTR lpIconName);
	HBITMAP LoadBitmap(LPCTSTR lpBitmapName);
	HCURSOR LoadCursor(LPCTSTR lpCursorName);

	CWnd* FindWindow(HWND hWnd);
	CDialog* FindDialog(HWND hWnd);


	void AddWnd(HWND hwnd, CWnd* pWnd);
	void RemoveWnd(HWND hwnd);
	CWnd* GetWnd(HWND hwnd);

	HINSTANCE GetHinstance();

	// window callback (the window callback for this app)
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// dialog stuff
	void AddDialog(HWND hwnd, CDialog* pDlg);
	void RemoveDialog(HWND hwnd);
	CDialog* GetDialog(HWND hwnd);
	static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// singleton pattern
	static CWinApp* GetApp();
private:
	static CWinApp* m_pTheApp;
	CMapHwndPtr m_WndMap;
	CMapHwndPtr m_DlgMap;
	HINSTANCE m_hInstance;
};

#endif
