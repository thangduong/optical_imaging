// CFreqPlot.h: interface for the CFreqPlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFREQPLOT_H__19607279_E744_463A_AB30_0115ED85DDC0__INCLUDED_)
#define AFX_CFREQPLOT_H__19607279_E744_463A_AB30_0115ED85DDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPrevWnd.h"

class CFreqPlot : public CPrevWnd  
{
public:
	CFreqPlot();
	virtual ~CFreqPlot();
	virtual void Show(short* pData);

};

#endif // !defined(AFX_CFREQPLOT_H__19607279_E744_463A_AB30_0115ED85DDC0__INCLUDED_)
