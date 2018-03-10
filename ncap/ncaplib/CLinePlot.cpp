// CLinePlot.cpp: implementation of the CLinePlot class.
//
//////////////////////////////////////////////////////////////////////

#include "CLinePlot.h"
#include "CWinApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinePlot::CLinePlot()
{

}

CLinePlot::~CLinePlot()
{

}

void CLinePlot::Show(short* pData) {
	HDC dc = GetDC(m_hWnd);
	HDC hbd = CreateCompatibleDC(0);

	if (pData) {
		// copy data over!
		short* pIn = pData + 128 * bmi.bmiHeader.biWidth;
		for (int x = 0; x < bmi.bmiHeader.biWidth; x++) {
			int v = pIn[x] >> 4;
			char* pOut = m_pBackImgData + 3 * x;

			for (int y = 0; y < bmi.bmiHeader.biHeight; y++) {
				if (y < v) {
					pOut[0] = pOut[1] = pOut[2] = 0;
					pOut[1] = 64;
				}
				else {
					pOut[0] = pOut[1] = pOut[2] = 128;
				}
				pOut += bmi.bmiHeader.biWidth * 3; 
			}
		}
	}

	SelectObject(hbd, m_hBackImg);
	BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
	DeleteDC(hbd);
	ReleaseDC(m_hWnd, dc);
}

