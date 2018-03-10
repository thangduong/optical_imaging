// CLinePlot.h: interface for the CLinePlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLINEPLOT_H__D78C6E68_30ED_4961_A46D_CD0A2331211B__INCLUDED_)
#define AFX_CLINEPLOT_H__D78C6E68_30ED_4961_A46D_CD0A2331211B__INCLUDED_

#include "CPrevWnd.h"

class CLinePlot : public CPrevWnd  
{
public:
	CLinePlot();
	virtual ~CLinePlot();

	virtual void Show(short* pData);
};

#endif // !defined(AFX_CLINEPLOT_H__D78C6E68_30ED_4961_A46D_CD0A2331211B__INCLUDED_)
