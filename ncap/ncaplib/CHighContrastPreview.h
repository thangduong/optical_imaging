// CHighContrastPreview.h: interface for the CHighContrastPreview class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHIGHCONTRASTPREVIEW_H__19398EDA_1FF9_484A_96D7_F7125597444C__INCLUDED_)
#define AFX_CHIGHCONTRASTPREVIEW_H__19398EDA_1FF9_484A_96D7_F7125597444C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPrevWnd.h"

class CHighContrastPreview : public CPrevWnd  
{
public:
	CHighContrastPreview();
	virtual ~CHighContrastPreview();

	virtual void Show(short* pData);
};

#endif // !defined(AFX_CHIGHCONTRASTPREVIEW_H__19398EDA_1FF9_484A_96D7_F7125597444C__INCLUDED_)
