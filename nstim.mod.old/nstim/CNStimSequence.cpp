// CNStimSequence.cpp: implementation of the CNStimSequence class.
//
//
// REVISION HISTORY
//
//	10/20/2005		Thang	Added this order
//							Added code to handle iOrder
//								iOrder basically allows the script to control how
//								patches are ordered if they have equal frame #
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CNStimSequence.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimSequence::CNStimSequence()
{
	m_iNumCompiledMarkers = 0;
	m_pCurMarkerPos = 0;
	m_bSequenceDone = false;
	m_bSequenceStarted = false;
}

CNStimSequence::~CNStimSequence()
{

	while (!m_CompiledMarkers.IsEmpty())
		delete m_CompiledMarkers.RemoveHead();
	while (!m_SequenceMarkers.IsEmpty())
		delete m_SequenceMarkers.RemoveHead();
}

void CNStimSequence::Reset()
{
	m_bSequenceDone = false;
	m_bSequenceStarted = false;	
	m_pCurMarkerPos = 0;

	while (!m_CompiledMarkers.IsEmpty())
		delete m_CompiledMarkers.RemoveHead();
}

void CNStimSequence::Compile(INStimEngine* pEngine)
{
	if (m_SequenceMarkers.IsEmpty())
		return;

	Reset();

	m_iNumCompiledMarkers = 1;

	POSITION pos = m_SequenceMarkers.GetHeadPosition();
	NStimSequenceMarker* lastMark = m_SequenceMarkers.GetNext(pos);
	CNStimCompiledSequenceMarker* pCompiledMarker;
	CList<INStimAtom*,INStimAtom*> TallyList;
	CList<ResetElement,ResetElement> ResetTallyList;
	INStimAtom* pAtom;
	ResetElement resetElt;
	while (pos)
	{
#ifdef _DEBUG
		char junk[512];
		sprintf(junk, "%s %d %d\r\n", lastMark->AtomName.GetData(), lastMark->iFrameMarker, lastMark->Type);
		OutputDebugString(junk);
#endif
		switch(lastMark->Type)
		{
		case SM_START:
			{
				pAtom = 0;
			pEngine->FindAtom((unsigned char*)lastMark->AtomName.GetData(), &pAtom);
			if (pAtom==0)
			{
				DebugBreak();
			}
			TallyList.AddTail(pAtom);
			resetElt.pAtom = pAtom;
			resetElt.pMarker = lastMark;
			ResetTallyList.AddTail(resetElt);

			}
			break;
		case SM_STOP:
			{
				POSITION cpos = TallyList.GetHeadPosition();
				while (cpos)
				{
					POSITION ppos = cpos;
					if (TallyList.GetNext(cpos)->IsAtom((unsigned char*)lastMark->AtomName.GetData()) == S_OK)
					{
						TallyList.RemoveAt(ppos);
						break;
					}
				}
			}
			break;
		}
		NStimSequenceMarker* nextMark = m_SequenceMarkers.GetNext(pos);

		if (lastMark->iFrameMarker != nextMark->iFrameMarker)
		{
			m_iNumCompiledMarkers++;

			pCompiledMarker = new CNStimCompiledSequenceMarker;
			POSITION cpos = TallyList.GetHeadPosition();
			pCompiledMarker->SetFrameMarker(lastMark->iFrameMarker);
			while (cpos)
				pCompiledMarker->AddAtom(TallyList.GetNext(cpos));
//			while (!TallyList.IsEmpty())
//				pCompiledMarker->AddAtom(TallyList.RemoveHead());

			while (!ResetTallyList.IsEmpty())
				pCompiledMarker->AddResetAtom(ResetTallyList.RemoveHead());
			m_CompiledMarkers.AddTail(pCompiledMarker);
		}

		lastMark = nextMark;
	}
		switch(lastMark->Type)
		{
		case SM_START:
			{
			pEngine->FindAtom((unsigned char*)lastMark->AtomName.GetData(), &pAtom);
			TallyList.AddTail(pAtom);
			resetElt.pAtom = pAtom;
			resetElt.pMarker = lastMark;
			ResetTallyList.AddTail(resetElt);

			}
			break;
		case SM_STOP:
			{
				POSITION cpos = TallyList.GetHeadPosition();
				while (cpos)
				{
					POSITION ppos = cpos;
					if (TallyList.GetNext(cpos)->IsAtom((unsigned char*)lastMark->AtomName.GetData()) == S_OK)
					{
						TallyList.RemoveAt(ppos);
						break;
					}
				}
			}
			break; 
		}

	pCompiledMarker = new CNStimCompiledSequenceMarker;
	pCompiledMarker->SetFrameMarker(lastMark->iFrameMarker);
	while (!TallyList.IsEmpty())
		pCompiledMarker->AddAtom(TallyList.RemoveHead());
	while (!ResetTallyList.IsEmpty())
		pCompiledMarker->AddResetAtom(ResetTallyList.RemoveHead());
	m_CompiledMarkers.AddTail(pCompiledMarker);
	
}

void CNStimSequence::AddSequenceMarker(int frameMarker, int type, unsigned char* patchName, int order)
{
	NStimSequenceMarker* sm = new NStimSequenceMarker;
	sm->iFrameMarker = frameMarker;
	sm->Type = type;
	sm->iOrder = order;
	sm->AtomName = (char*)patchName;

	bool bAdded = false;
	POSITION pos = m_SequenceMarkers.GetTailPosition();
	while (pos)
	{
		POSITION ppos = pos;
		NStimSequenceMarker* csm = m_SequenceMarkers.GetPrev(pos);
		if ((csm->iFrameMarker < sm->iFrameMarker) ||
			((csm->iFrameMarker == sm->iFrameMarker) && (csm->iOrder <= sm->iOrder)))
		{
			m_SequenceMarkers.InsertAfter(ppos, sm);
			bAdded = true;
			break;
		}
	}
	if (!bAdded)
		m_SequenceMarkers.AddHead(sm);
}

void CNStimSequence::AddSequenceMarker(int frameMarker, int type, unsigned char* patchName, CList<NStimSequenceItemParam,NStimSequenceItemParam>* ParamList, int order)
{
	NStimSequenceMarker* sm = new NStimSequenceMarker;
	sm->iFrameMarker = frameMarker;
	sm->Type = type;
	sm->AtomName = (char*)patchName;
	POSITION pos;

	// copy parameters over
	pos = ParamList->GetHeadPosition();
	while (pos) {
		sm->ParamList.AddTail(ParamList->GetNext(pos));
	}

	// insert the sequence marker so that it's in order
	// by frame number
	bool bAdded = false;
	pos = m_SequenceMarkers.GetTailPosition();
	while (pos)
	{
		POSITION ppos = pos;
		NStimSequenceMarker* csm = m_SequenceMarkers.GetPrev(pos);
		if ((csm->iFrameMarker < sm->iFrameMarker) ||
			((csm->iFrameMarker == sm->iFrameMarker) && (csm->iOrder <= sm->iOrder)))
		{
			m_SequenceMarkers.InsertAfter(ppos, sm);
			bAdded = true;
			break;
		}
	}
	if (!bAdded)
		m_SequenceMarkers.AddHead(sm);
}

void CNStimSequence::GetAtomList(int frame, CList<NStimSequencePresentAtom*,NStimSequencePresentAtom*>** ppList, INStimEngine* pEngine)
{
	if (!m_bSequenceDone) {
		if (!m_bSequenceStarted) {
			if (m_pCurMarkerPos == 0)
			{
				m_pCurMarkerPos = m_CompiledMarkers.GetHeadPosition();
				if (m_pCurMarkerPos == 0)
				{
					m_bSequenceDone = true;
					pSeq = 0;
				}
				else
				{
					pSeq = m_CompiledMarkers.GetNext(m_pCurMarkerPos);
					m_bSequenceStarted = true;
				}
			}

		}
		if (pSeq && (pSeq->GetFrameMarker() <= frame))
		{
			pSeq->ApplyReset(pEngine);
			(*ppList) = pSeq->GetAtomList();
			if (m_pCurMarkerPos)
				pSeq = m_CompiledMarkers.GetNext(m_pCurMarkerPos);
			else
			{
				pSeq = 0;
				m_bSequenceDone = true;
			}
		}
	}
}

void CNStimSequence::Clear() {
	Reset();
	while (!m_SequenceMarkers.IsEmpty())
		delete m_SequenceMarkers.RemoveHead();
}
