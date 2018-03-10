// CNStimSequence	Stimulation sequence
//
//
// REVISION HISTORY
//
//	10/6/2005		Thang	Added this header
//							Working on adding sequence of atoms instead of just patches
//
//	10/20/2005		Thang	Added iOrder and code to handle it
//								iOrder basically allows the script to control how
//								patches are ordered if they have equal frame #
//							
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMSEQUENCE_H__E7D18E13_C972_416B_94C4_4E39E61BAC13__INCLUDED_)
#define AFX_CNSTIMSEQUENCE_H__E7D18E13_C972_416B_94C4_4E39E61BAC13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3dx9.h>
#include "CString.h"
#include "CList.h"
#include "INStimAtom.h"

// SM = sequence marker
#define	SM_START			0
#define	SM_STOP				1


struct NStimSequenceItemParam {
	CString ParamName;
	CString ParamValue;
};

struct NStimSequenceMarker {
	int iFrameMarker;
	int iOrder;							// if two sequence markers have the same frame, this determins which goes first
	int Type;			
	CString AtomName;
	CList<NStimSequenceItemParam, NStimSequenceItemParam> ParamList;
};

struct ResetElement {
	INStimAtom* pAtom;
	NStimSequenceMarker* pMarker;
};

// This structure is what the engine gets.
struct NStimSequencePresentAtom {
	INStimAtom* pAtom;
	int iOrder;
};

class CNStimCompiledSequenceMarker {
	int m_iFrameMarker;
	CList<NStimSequencePresentAtom,NStimSequencePresentAtom> m_AtomList;
	CList<ResetElement, ResetElement> m_ResetAtomList;
public:
	CNStimCompiledSequenceMarker() {
	}
	virtual ~CNStimCompiledSequenceMarker() {
		while (!m_AtomList.IsEmpty())
			m_AtomList.RemoveHead().pAtom->Release();
	}

	int GetFrameMarker() { return m_iFrameMarker; }
	void SetFrameMarker(int FrameMarker) { m_iFrameMarker = FrameMarker; }
	void AddAtom(INStimAtom* pAtom, int iOrder) { 
		pAtom->AddRef(); 
		NStimSequencePresentAtom PresentAtom;
		PresentAtom.iOrder = iOrder;
		PresentAtom.pAtom = pAtom;
		POSITION pos = m_AtomList.GetHeadPosition();
		POSITION insertPos = 0;
		while (pos) {
			POSITION oldPos = pos;
			if (m_AtomList.GetNext(pos).iOrder >= iOrder) {
				insertPos = pos;
				break;
			}
		}
		if (insertPos)
			m_AtomList.InsertBefore(insertPos, PresentAtom);
		else
			m_AtomList.AddTail(PresentAtom);
	}
//	void AddResetAtom(INStimAtom* pAtom) { pAtom->AddRef(); m_ResetAtomList.AddTail(pAtom); }
	void AddResetAtom(ResetElement elt) { m_ResetAtomList.AddTail(elt); }
	CList<NStimSequencePresentAtom,NStimSequencePresentAtom>* GetAtomList() {
		return &m_AtomList;
	}
	void ApplyReset(INStimEngine* pEngine) { 
		POSITION pos = m_ResetAtomList.GetHeadPosition();
		while (pos)
		{
			ResetElement elt;
			elt = m_ResetAtomList.GetNext(pos);
			POSITION pos = elt.pMarker->ParamList.GetHeadPosition();
			while (pos) {
				NStimSequenceItemParam sp = elt.pMarker->ParamList.GetNext(pos);
				elt.pAtom->SetParam((unsigned char*)sp.ParamName.GetData(), (unsigned char*)sp.ParamValue.GetData());
			}
			elt.pAtom->Reset(pEngine);
		}
	}
};

class CNStimSequence  
{
	CList<NStimSequenceMarker*,NStimSequenceMarker*> m_SequenceMarkers;
	CNStimCompiledSequenceMarker* pSeq;
	int m_iNumCompiledMarkers;
	POSITION m_pCurMarkerPos;
	CList<CNStimCompiledSequenceMarker*,CNStimCompiledSequenceMarker*> m_CompiledMarkers;
	bool m_bSequenceDone;
	bool m_bSequenceStarted;
public:
	CNStimSequence();
	virtual ~CNStimSequence();

	void Reset();		// reset so we can restart
	void Compile(INStimEngine* pEngine);
	void AddSequenceMarker(int frameMarker, int type, unsigned char* patchName, CList<NStimSequenceItemParam,NStimSequenceItemParam>* ParamList, int order);
	void AddSequenceMarker(int frameMarker, int type, unsigned char* patchName, int order);
	void GetAtomList(int frame, CList<NStimSequencePresentAtom*,NStimSequencePresentAtom*>** ppList, INStimEngine* pEngine);
	void Clear();		// clears all sequence info
	void GetSequenceMarkerCount(int* pCount) {
		(*pCount) = m_SequenceMarkers.GetCount();
	}
	void GetSequenceMarker(int index, NStimSequenceMarker** ppMarker) {
		POSITION pos = m_SequenceMarkers.FindIndex(index);
		(*ppMarker) = m_SequenceMarkers.GetAt(pos);
	}
};

#endif // !defined(AFX_CNSTIMSEQUENCE_H__E7D18E13_C972_416B_94C4_4E39E61BAC13__INCLUDED_)
