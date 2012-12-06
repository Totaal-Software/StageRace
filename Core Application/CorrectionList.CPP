// CorrectionList.cpp: implementation of the CCorrectionList class.
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

CCorrectionList::CCorrectionList()
{
	// Instantiating a new and empty list
}

CCorrectionList::CCorrectionList(const CCorrectionList &aCorrL)
{
	*this = aCorrL;
}

CCorrectionList& CCorrectionList::operator =(const CCorrectionList &aCorrL)
{
	// Empty the list
	RemoveAll();

	aCorrL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aCorrL.m_list.GetStartPosition();
	while( nPos )
	{
		CCorrection*	pCorr;
		WORD			nKey;
		// Look up every item
		aCorrL.m_list.GetNextAssoc( nPos, nKey, (CObject*&)pCorr );
		// Store a copy in the new list
		Insert( *pCorr );
	}

	aCorrL.UnlockRead();

	return *this;
}

CCorrectionList& CCorrectionList::operator =(const CArrivalList &aArrL)
{
	// Empty the list
	RemoveAll();

	aArrL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aArrL.GetStartPosition();
	while( nPos )
	{
		CArrival		aArr;
		CCorrection		aCorr;
		// Look up every item
		aArrL.Iterate( nPos, aArr );
		// Copy it
		aCorr = aArr;
		// Store a copy in the new list
		Insert( aCorr );
	}

	aArrL.UnlockRead();

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CCorrectionList::Insert(CCorrection &objCorr)
{
	CStaNoObjectList::Insert( new CCorrection(objCorr) );
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CCorrectionList::Serialize(CArchive &ar)
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
			CCorrection*	pCorr;
			WORD			nKey;
			m_list.GetNextAssoc( pos, nKey, (CObject*&)pCorr );
			pCorr->Serialize(ar);
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
			CCorrection aCorrection;
			WORD nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aCorrection.Serialize(ar);
				Insert( aCorrection );
			}
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CCorrection aCorrection;
			int nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aCorrection.Serialize(ar);
				Insert( aCorrection );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Constants/Lookup
//////////////////////////////////////////////////////////////////////

CCorrection CCorrectionList::GetAt(WORD nStaNo) const
{
	// Retrieve a particular staNo
	CCorrection *pCorr;

	LockRead();
	BOOL bExist = m_list.Lookup( nStaNo, (CObject*&)pCorr );
	UnlockRead();

	if( bExist )
		return *pCorr;
	else
		return CCorrection(); // return empty
}

bool CCorrectionList::IterateSorted(DWORD &nState, CCorrection &objCorr) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objCorr = GetAt(objStaNo.m_staNo);
		return true;
	}
	return false;
}

void CCorrectionList::Iterate( POSITION& rNextPosition, CCorrection& rValue ) const
{
	CCorrection*	pCorr;
	WORD			nKey;
	m_list.GetNextAssoc( rNextPosition, nKey, (CObject*&)pCorr );
	rValue = *pCorr;
}



