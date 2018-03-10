// CTemporalPlot.h: interface for the CTemporalPlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_)
#define AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPrevWnd.h"

class CTemporalPlot : public CPrevWnd  
{
	short* m_pTempTrace;
	int m_iMemSize;
	int m_iCurLoc;
public:
	CTemporalPlot();
	virtual ~CTemporalPlot();

	virtual void Show(short* pData);

};

#endif // !defined(AFX_CTEMPORALPLOT_H__58B44CD0_577F_4AB9_8443_6EAE069E8488__INCLUDED_)
