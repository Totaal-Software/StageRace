// AvailableList.cpp: implementation of the CAvailableList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAvailableList::CAvailableList(
	const CSignOutList*		pListSignOuts	/*=NULL*/,
	const CStaNoObjectList*	pListCompetitors/*=NULL*/,
	const CStaNoObjectList* pListMustBeOn	/*=NULL*/)
{
	m_pListSignOuts		= pListSignOuts;
	m_pListCompetitors	= pListCompetitors;
	m_pListMustBeOn		= pListMustBeOn;
}

CAvailableList::~CAvailableList()
{
}

bool CAvailableList::IterateSorted(DWORD &nState, CArrival &objArr) const
{
	if( m_pListCompetitors->IsKindOf( RUNTIME_CLASS(CArrivalList) ) )
		while( ((CArrivalList*)m_pListCompetitors)->IterateSorted( nState, objArr ) )
		{
			if( (!m_pListSignOuts || !m_pListSignOuts->Exist( objArr.m_staNo ))
					&& !((CArrivalList*)m_pListCompetitors)->IsTimeCutted( objArr.m_staNo )
					&& ( !m_pListMustBeOn || m_pListMustBeOn->Exist( objArr.m_staNo ) ) )
				return true;
		}
	else
		while( m_pListCompetitors->IterateSorted( nState, objArr ) )
		{
			if( ( !m_pListSignOuts || !m_pListSignOuts->Exist( objArr.m_staNo ) )
					&& ( !m_pListMustBeOn || m_pListMustBeOn->Exist( objArr.m_staNo ) ) )
				return true;
		}
	return false;
}

bool CAvailableList::Exist(WORD nStaNo) const
{
	return m_pListCompetitors->Exist(nStaNo)
		&& !m_pListSignOuts->Exist(nStaNo);
}

CArrival CAvailableList::GetAt(WORD nStaNo) const
{
	if( m_pListCompetitors->IsKindOf( RUNTIME_CLASS(CArrivalList) ) )
		return ((CArrivalList*)m_pListCompetitors)->GetAt(nStaNo);
	else
	{
		// Let's hope this never happen
		// as it look very useless
		CArrival arr;
		arr.m_staNo = nStaNo;
		return arr;
	}
}
