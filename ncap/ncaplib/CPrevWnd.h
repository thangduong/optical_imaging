// CPrevWnd.h: interface for the CPrevWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPREVWND_H__2EC5300B_624C_4A0C_AD77_E37AA23CA216__INCLUDED_)
#define AFX_CPREVWND_H__2EC5300B_624C_4A0C_AD77_E37AA23CA216__INCLUDED_

#include "CWnd.h"

#define	PREVWND_CLASSNAME	"PREVWND_CLASSNAME"

class CPrevWnd : public CWnd  
{
protected:
	HBITMAP m_hBackImg;
	char* m_pBackImgData;
	BITMAPINFO bmi;

public:
	CPrevWnd();
	virtual ~CPrevWnd();

	static void RegisterClass();

	bool Create(LPCTSTR lpWindowName, DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CWnd* pParent = 0, HMENU hMenu = 0);
	virtual void Show(short* pData);
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_CPREVWND_H__2EC5300B_624C_4A0C_AD77_E37AA23CA216__INCLUDED_)
