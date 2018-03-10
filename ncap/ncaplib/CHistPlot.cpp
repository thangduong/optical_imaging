// CHistPlot.cpp: implementation of the CHistPlot class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CHistPlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistPlot::CHistPlot()
{
	m_pHist = 0;
	m_iLastTextUpdate = -1;
}

CHistPlot::~CHistPlot()
{
	delete m_pHist;
}


void CHistPlot::Show(short* pData) {

	if (m_pBackImgData) {
		HDC dc = GetDC(m_hWnd);
		HDC hbd = CreateCompatibleDC(0);

		int mv = -1;
		if (pData) {
			if (m_pHist == 0) {
				m_pHist = new int[bmi.bmiHeader.biWidth];
			}
			int n = 4096 / bmi.bmiHeader.biHeight;
			// copy data over!
			mv = 0;
			memset(m_pHist, 0, bmi.bmiHeader.biWidth*sizeof(int));
			for (int i = 0; i < bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight; i++) {
				int loc = pData[i] / n;
				if (loc >= bmi.bmiHeader.biWidth)
					loc = bmi.bmiHeader.biWidth-1;

				m_pHist[loc]++;
				if (m_pHist[loc] > mv) {
					mv = m_pHist[loc];
				}
			}

			for (int x = 0; x < bmi.bmiHeader.biWidth; x++) {
				int v = (m_pHist[x] * 256) / mv;
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

		if (mv >= 0) {
			if ((GetTickCount() - m_iLastTextUpdate) > 500) {
				m_iMax = mv;
				m_iLastTextUpdate = GetTickCount();
			}
			else {
				mv = m_iMax;
			}
			char mtext[512];
			SetBkColor(dc, 0x808080);
			sprintf(mtext, "max = %d", mv);
			TextOut(dc, 0, 0, mtext, strlen(mtext));
		}

		ReleaseDC(m_hWnd, dc);
	}
}

