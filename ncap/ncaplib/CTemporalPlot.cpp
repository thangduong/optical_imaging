// CTemporalPlot.cpp: implementation of the CTemporalPlot class.
//
//////////////////////////////////////////////////////////////////////

#include "CTemporalPlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTemporalPlot::CTemporalPlot()
{
	m_iMemSize = 0;
	m_pTempTrace = 0;
	m_iCurLoc = 0;
}

CTemporalPlot::~CTemporalPlot()
{
	delete m_pTempTrace;
}

void CTemporalPlot::Show(short* pData) {

	if (m_pBackImgData) {
		HDC dc = GetDC(m_hWnd);
		HDC hbd = CreateCompatibleDC(0);

		int mv = -1;
		if (pData) {
			if (m_pTempTrace == 0) {
				m_iMemSize = bmi.bmiHeader.biWidth;
				m_pTempTrace = new short[m_iMemSize];
			}

			m_pTempTrace[m_iCurLoc++] = pData[128*bmi.bmiHeader.biWidth+128];
			m_iCurLoc = (m_iCurLoc % m_iMemSize);


			int loc = m_iCurLoc + 1;
			loc = (loc % m_iMemSize);
			for (int x = 0; x < bmi.bmiHeader.biWidth; x++) {
				int v = (m_pTempTrace[loc] * 256) / 4096;
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
				loc++;
				loc = (loc % m_iMemSize);
			}

		}

		SelectObject(hbd, m_hBackImg);
		BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
		DeleteDC(hbd);
		ReleaseDC(m_hWnd, dc);
	}
}