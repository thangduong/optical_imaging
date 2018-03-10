// CDirect3DWnd.h: interface for the CDirect3DWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDIRECT3DWND_H__8A9CBCD3_EB80_4F31_BA8A_AF106CB4CC68__INCLUDED_)
#define AFX_CDIRECT3DWND_H__8A9CBCD3_EB80_4F31_BA8A_AF106CB4CC68__INCLUDED_

#include "CWnd.h"
#include "CDirect3DDevice.h"
#include "CDirect3D.h"

#define	DIRECT3DWND_CLASSNAME	"CDirect3DWnd"

class CDirect3DWnd : public CWnd  
{
public:
	CDirect3DDevice m_Direct3DDevice;
	D3DPRESENT_PARAMETERS d3dpp;

public:
	CDirect3DWnd();
	virtual ~CDirect3DWnd();

	static void RegisterClass();
	

	bool Create(const CDirect3D& Direct3D, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CDialog* pParent = NULL, HMENU hMenu = NULL); 
	bool CreateFullscreen(const CDirect3D& Direct3D, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, D3DFORMAT Format, int RefreshRate, CDialog* pParent = NULL, HMENU hMenu = NULL);

	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_CDIRECT3DWND_H__8A9CBCD3_EB80_4F31_BA8A_AF106CB4CC68__INCLUDED_)
