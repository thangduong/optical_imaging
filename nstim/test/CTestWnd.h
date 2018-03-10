// CTestWnd.h: interface for the CTestWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTESTWND_H__78931F05_6EBC_4914_BE1D_3238D26402F3__INCLUDED_)
#define AFX_CTESTWND_H__78931F05_6EBC_4914_BE1D_3238D26402F3__INCLUDED_

#include "CDirect3DWnd.h"

class CTestWnd : public CDirect3DWnd  
{
public:
	CTestWnd();
	virtual ~CTestWnd();
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !defined(AFX_CTESTWND_H__78931F05_6EBC_4914_BE1D_3238D26402F3__INCLUDED_)
