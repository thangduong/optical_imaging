// CImgPreviewWnd.cpp: implementation of the CImgPreviewWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "CImgPreviewWnd.h"
#include "CWinApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImgPreviewWnd::CImgPreviewWnd()
{
	m_pBackImgData = 0;
}

CImgPreviewWnd::~CImgPreviewWnd()
{

}

void CImgPreviewWnd::Show(short* pData) {
	if (m_pBackImgData) {
		HDC dc = GetDC(m_hWnd);
		HDC hbd = CreateCompatibleDC(0);

		if (pData) {
			// copy data over!
			char* pOut = m_pBackImgData;
			int i;
			for (i = 0; i < bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight; i++) {
				pOut[1] = pOut[2] = pOut[0] = ((unsigned)pData[i]&0xfff)>>4;
				pOut += 3;
			}
		}

		SelectObject(hbd, m_hBackImg);
		BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
		DeleteDC(hbd);
		ReleaseDC(m_hWnd, dc);
	}
}

