// CImgPreviewWnd.h: interface for the CImgPreviewWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIMGPREVIEWWND_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_)
#define AFX_CIMGPREVIEWWND_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_

#include "CPrevWnd.h"

class CImgPreviewWnd : public CPrevWnd  
{
public:
	CImgPreviewWnd();
	virtual ~CImgPreviewWnd();

	virtual void Show(short* pData);
};

#endif // !defined(AFX_CIMGPREVIEWWND_H__C5A7A634_4C0A_4A69_B927_A996B2B422EC__INCLUDED_)
