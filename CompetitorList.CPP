// CompetitorList.cpp: implementation of the CCompetitorList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompetitorList::CCompetitorList()
{
	// Instantiating a new and empty list
}

CCompetitorList::CCompetitorList(const CCompetitorList &aCompL)
{
	*this = aCompL;
}

CCompetitorList& CCompetitorList::operator =(const CCompetitorList &aCompL)
{
	// Empty the list
	RemoveAll();

	aCompL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aCompL.m_list.GetStartPosition();
	while( nPos )
	{
		CCompetitor*	pComp;
		WORD			nKey;
		// Look up every item
		aCompL.m_list.GetNextAssoc( nPos, nKey, (CObject*&)pComp );
		// Store a copy in the new list
		Insert( *pComp );
	}

	aCompL.UnlockRead();

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CCompetitorList::Insert(CCompetitor &objComp)
{
	CStaNoObjectList::Insert( new CCompetitor(objComp) );
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CCompetitorList::Serialize(CArchive &ar)
{
	if( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		ar << GetCount();

		LockRead();

		POSITION pos = m_list.GetStartPosition( );

		while( pos!=NULL )
		{
			CCompetitor*	pComp;
			WORD			nKey;
			m_list.GetNextAssoc( pos, nKey, (CObject*&)pComp );
			pComp->Serialize(ar);
		}

		UnlockRead();
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			CCompetitor aCompetitor;
			WORD nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aCompetitor.Serialize(ar);
				Insert( aCompetitor );
			}
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CCompetitor aCompetitor;
			int nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aCompetitor.Serialize(ar);
				Insert( aCompetitor );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Constants/Lookup
//////////////////////////////////////////////////////////////////////

CCompetitor CCompetitorList::GetAt(WORD nStaNo) const
{
	// Retrieve a particular staNo
	CCompetitor *pComp;
	LockRead();
	BOOL bExist = m_list.Lookup( nStaNo, (CObject*&)pComp );
	UnlockRead();

	if( bExist )
		return *pComp;
	else
		return CCompetitor(); // return empty
}

bool CCompetitorList::IterateSorted(DWORD &nState, CCompetitor &objComp) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objComp = GetAt(objStaNo.m_staNo);
		return true;
	}
	return false;
}

void CCompetitorList::Iterate( POSITION& rNextPosition, CCompetitor& rValue ) const
{
	CCompetitor*	pComp;
	WORD			nKey;
	m_list.GetNextAssoc( rNextPosition, nKey, (CObject*&)pComp );
	rValue = *pComp;
}
