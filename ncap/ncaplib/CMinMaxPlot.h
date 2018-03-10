// CMinMaxPlot.h: interface for the CTemporalPlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_)
#define AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPrevWnd.h"

class CMinMaxPlot : public CPrevWnd  
{
	short* m_pTempTrace;
	int m_iMemSize;
	int m_iCurLoc;
	bool m_bIsMin;
public:
	CMinMaxPlot();
	virtual ~CMinMaxPlot();

	virtual void Show(short* pData);
	void SetMinMax(bool isMin) { m_bIsMin = isMin; }
};

#endif // !defined(AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_)
