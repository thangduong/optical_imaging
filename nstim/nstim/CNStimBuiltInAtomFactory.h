// CNStimAtomFactory.h: interface for the CNStimAtomFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMAtomFACTORY_H__196F445E_A169_4D25_9C0C_29D8F8276CCA__INCLUDED_)
#define AFX_CNSTIMAtomFACTORY_H__196F445E_A169_4D25_9C0C_29D8F8276CCA__INCLUDED_

#include <d3dx9.h>
#include "INStimAtomFactory.h"
#include "CNStimGratingPatch.h"

class CNStimBuiltInAtomFactory : public INStimAtomFactory  
{
	long m_iCount;
public:
	CNStimBuiltInAtomFactory();
	virtual ~CNStimBuiltInAtomFactory();

	virtual HRESULT __stdcall IsValidAtomType(unsigned char* AtomType);
	virtual HRESULT __stdcall CreateAtom(unsigned char* AtomType, INStimAtom** ppAtom);

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif

