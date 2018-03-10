// CLUTPreviewWnd.cpp: implementation of the CLUTPreviewWnd class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CLUTPreviewWnd.h"
#include "CWinApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLUTPreviewWnd::CLUTPreviewWnd()
{
	m_pBackImgData = 0;
	int i = 0;
	for (i = 0; i < sizeof(lut)/sizeof(lut[1]); i++) {
		int j = i >> 4;
		lut[i] = (j) + (j<<8) + (j<<16) + (j<<24);
	}
	/*
	for (i = 16; i < ((1<<12)-16-2); i++)
		lut[i] = 0x80808080;
	for (i = ((1<<12)-256*3); i < ((1<<12)-1); i++) 
		lut[i] = 0xff;
	for (i = ((1<<12)-256*2); i < ((1<<12)-1); i++) 
		lut[i] = 0xff00;
	for (i = ((1<<12)-256); i < ((1<<12)-1); i++) 
		lut[i] = 0xff0000;
	for (i = ((1<<12)-16-2); i < ((1<<12)-1); i++) 
		lut[i] = 0xfffffff;
		*/
}

CLUTPreviewWnd::~CLUTPreviewWnd()
{

}

void CLUTPreviewWnd::Show(short* pData) {

	if (m_pBackImgData) {
		HDC dc = GetDC(m_hWnd);
		HDC hbd = CreateCompatibleDC(0);

		if (pData) {
			// copy data over!
			char* pOut = m_pBackImgData;
			int idx = 0;
			for (int y = 0; y < bmi.bmiHeader.biHeight; y++) {
				for (int x = 0; x < bmi.bmiHeader.biWidth; x++) {
					if (x < (bmi.bmiHeader.biWidth-64))
					{
						memcpy(pOut, &lut[(pData[idx]&0xfff)], 3);
						idx++;
					}
					else {
						int loc = 15 - ((bmi.bmiHeader.biWidth-x-1)/4);
						int col = loc;
						int lutLoc = col * bmi.bmiHeader.biHeight + y;
						memcpy(pOut, &lut[lutLoc], 3);
					}
					pOut += 3;
				}
			}
		}

		SelectObject(hbd, m_hBackImg);
		BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
		DeleteDC(hbd);
		ReleaseDC(m_hWnd, dc);
	}
}

