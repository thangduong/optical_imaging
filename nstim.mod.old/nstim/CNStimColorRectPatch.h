// CNStimColorRectPatch.h: interface for the CNStimColorRectPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMCOLORRECTPATCH_H__12100985_4EDD_4A81_83C3_B1EFC2CF23A4__INCLUDED_)
#define AFX_CNSTIMCOLORRECTPATCH_H__12100985_4EDD_4A81_83C3_B1EFC2CF23A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatch.h"
#include "CDirect3DSurface.h"

class CNStimColorRectPatch : public CNStimPatch  
{
	int* m_pWidth;
	int* m_pHeight;
	int* m_pColor;
public:
	CNStimColorRectPatch();
	virtual ~CNStimColorRectPatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames);
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine);
	virtual HRESULT __stdcall Init(INStimEngine* pEngine);

};

#endif // !defined(AFX_CNSTIMCOLORRECTPATCH_H__12100985_4EDD_4A81_83C3_B1EFC2CF23A4__INCLUDED_)
