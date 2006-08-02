// SignOutList.cpp: implementation of the CSignOutList class.
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

CSignOutList::CSignOutList()
{
	// Instantiating a new and empty list
}

CSignOutList::CSignOutList(const CSignOutList &aSignOutL)
{
	*this = aSignOutL;
}

CSignOutList& CSignOutList::operator =(const CSignOutList &aSignOutL)
{
	// Empty the list
	RemoveAll();

	aSignOutL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aSignOutL.m_list.GetStartPosition();
	while( nPos )
	{
		CSignOut*	pSignOut;
		WORD		nKey;
		// Look up every item
		aSignOutL.m_list.GetNextAssoc( nPos, nKey, (CObject*&)pSignOut );
		// Store a copy in the new list
		Insert( *pSignOut );
	}

	aSignOutL.UnlockRead();
	
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CSignOutList::Insert(CSignOut &objSignOut)
{
	CStaNoObjectList::Insert( new CSignOut(objSignOut) );
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CSignOutList::Serialize(CArchive &ar)
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
			CSignOut*	pSignOut;
			WORD		nKey;
			m_list.GetNextAssoc( pos, nKey, (CObject*&)pSignOut );
			pSignOut->Serialize(ar);
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
			CSignOut aSignOut;
			WORD nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aSignOut.Serialize(ar);
				Insert( aSignOut );
			}
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CSignOut aSignOut;
			int nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aSignOut.Serialize(ar);
				Insert( aSignOut );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Constants/Lookup
//////////////////////////////////////////////////////////////////////

CSignOut CSignOutList::GetAt(WORD nStaNo) const
{
	// Retrieve a particular staNo
	CSignOut *pSignOut;
	
	LockRead();
	BOOL bExist = m_list.Lookup( nStaNo, (CObject*&)pSignOut );
	UnlockRead();

	if( bExist )
		return *pSignOut;
	else
		return CSignOut(); // return empty
}

bool CSignOutList::IterateSorted(DWORD &nState, CSignOut &objSignOut) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objSignOut = GetAt(objStaNo.m_staNo);
		return true;
	}
	return false;
}

void CSignOutList::Iterate( POSITION& rNextPosition, CSignOut& rValue ) const
{
	CSignOut*	pSignOut;
	WORD		nKey;
	m_list.GetNextAssoc( rNextPosition, nKey, (CObject*&)pSignOut );
	rValue = *pSignOut;
}
