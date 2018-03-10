// CHighContrastPreview.cpp: implementation of the CHighContrastPreview class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CHighContrastPreview.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHighContrastPreview::CHighContrastPreview()
{

}

CHighContrastPreview::~CHighContrastPreview()
{

}

void CHighContrastPreview::Show(short* pData) {
		HDC dc = GetDC(m_hWnd);
		HDC hbd = CreateCompatibleDC(0);

		unsigned int max = 0; 
		unsigned int min = 0xfff;
		if (pData) {
			// copy data over!
			char* pOut = m_pBackImgData;
			int i;
			for (i = 0; i < bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight; i++) {
				if (((unsigned)pData[i]&0xfff)>max)
					max = ((unsigned)pData[i]&0xfff);
				else {
					if (((unsigned)pData[i]&0xfff) < min)
						min = ((unsigned)pData[i]&0xfff);
				}
			}
			if (max-min>0) {
				for (i = 0; i < bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight; i++) {
					pOut[1] = pOut[2] = pOut[0] = (255*((((unsigned)pData[i]&0xfff) -min)) / (max-min));
					pOut += 3;
				}
			}
		}

		SelectObject(hbd, m_hBackImg);
		BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
		DeleteDC(hbd);

		char mtext[512];
		SetBkColor(dc, 0x808080);
		sprintf(mtext, "(min,max) = (%d,%d)", min, max);
		TextOut(dc, 0, 0, mtext, strlen(mtext));
		
		ReleaseDC(m_hWnd, dc);
}

