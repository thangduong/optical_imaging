// CHistPlot.h: interface for the CHistPlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHISTPLOT_H__D7D9362A_7903_4897_9E86_993785E533C1__INCLUDED_)
#define AFX_CHISTPLOT_H__D7D9362A_7903_4897_9E86_993785E533C1__INCLUDED_

#include "CPrevWnd.h"

class CHistPlot : public CPrevWnd  
{
	int* m_pHist;
	int m_iLastTextUpdate;
	int m_iMax;
	double m_iMean;
	double m_iVar;
public:
	CHistPlot();
	virtual ~CHistPlot();

	virtual void Show(short* pData);
};

#endif // !defined(AFX_CHISTPLOT_H__D7D9362A_7903_4897_9E86_993785E533C1__INCLUDED_)
