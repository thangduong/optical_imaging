// CLUTPreviewWnd.h: interface for the CLUTPreviewWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLUTPreviewWnd_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_)
#define AFX_CLUTPreviewWnd_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_

#include "CPrevWnd.h"

class CLUTPreviewWnd : public CPrevWnd  
{
	DWORD lut[1<<12];
public:
	CLUTPreviewWnd();
	virtual ~CLUTPreviewWnd();
	virtual bool Create(LPCTSTR lpWindowName, DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CWnd* pParent = 0, HMENU hMenu = 0) {
		return CPrevWnd::Create(lpWindowName, dwExStyle, dwStyle, x, y, nWidth+64, nHeight, pParent, hMenu);
	}

	virtual void Show(short* pData);
};

#endif // !defined(AFX_CLUTPreviewWnd_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_)
