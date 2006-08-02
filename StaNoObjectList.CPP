// StaNoObjectList.cpp: implementation of the CStaNoObjectList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CStaNoObjectList, CObject )

CStaNoObjectList::CStaNoObjectList()
{
	// Instantiating a new and empty list

	m_bDirty = false;
	// Make thread safe
	// Note: We don't do any error checking here
	// Better do that in real life 
	// Read: "Compound Win32 Synchronization Objects" on MSDN
	m_hReaderEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
	m_hWriterMutex = CreateMutex(NULL,FALSE,NULL);
	m_iCounter = -1;
}

CStaNoObjectList::~CStaNoObjectList()
{
	RemoveAll();
	LockWrite();
	CloseHandle(m_hReaderEvent);
	CloseHandle(m_hMutex);
	CloseHandle(m_hWriterMutex);
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CStaNoObjectList::LockWrite()
{
	m_bDirty = true;

	// Claim write rights
	WaitForSingleObject(m_hWriterMutex,INFINITE);
	// Unsignal mutex (lock)
	// To see if there isn't anyone reading anymore
	// Which is arranged for at point [2]
//TRACE(TEXT("WaitForSingleObject(m_hMutex, INFINITE); // [3]            %d\n"), this);
	WaitForSingleObject(m_hMutex, INFINITE); // [3]
}

void CStaNoObjectList::UnlockWrite()
{
	// Signal mutex (unlock)
	// So that someone can start reading from point [1]
	SetEvent(m_hMutex);
	// Release write rights
	ReleaseMutex(m_hWriterMutex);
}

void CStaNoObjectList::LockRead() const
{
	// Increment the readers counter
	// Only if this is the first reader the value will be 0
	if(InterlockedIncrement((long*)&m_iCounter) == 0)
    {
		// FIRST READER DOES FOLLOWING

		// Unsignal mutex (lock)
		// To wait for a current write and to prevent future writes, see [3]
		WaitForSingleObject(m_hMutex, INFINITE); // [1]
		// Signal reader event (unlock)
		// Has been locked up to now to prevent other (later)
		// readers from going through the WaitFor... at [4]
		// while we were still waiting for m_hMutex at [1]
//TRACE(TEXT("START LockRead SetEvent(m_hReaderEvent); // [5]                %d\n"), this);
		SetEvent(m_hReaderEvent); // [5]
//TRACE(TEXT("END LockRead SetEvent(m_hReaderEvent); // [5]                %d\n"), this);
	};
	// Prevents reading if we are still waiting for the
	// main mutex in [1]
//TRACE(TEXT("START LockRead WaitForSingleObject(m_hReaderEvent,INFINITE); // [4]                %d\n"), this);
	WaitForSingleObject(m_hReaderEvent,INFINITE); // [4]
//TRACE(TEXT("END LockRead WaitForSingleObject(m_hReaderEvent,INFINITE); // [4]                %d\n"), this);
//TRACE(TEXT("LockRead INTERLOCK: m_iCounter=%d               %d\n"), m_iCounter, this);
}

void CStaNoObjectList::UnlockRead() const
{
	// Decrement the readers counter
	// Only if this is the last reader the value will be < 0
	if(InterlockedDecrement((long*)&m_iCounter) < 0)
	{
		// Unsignal reader event (lock)
		// So that no one can start reading anymore
		// Note that m_hReaderEvent is not gonna be
		// waited for (at [4]) until the second read
		// attempt after this
		// (The first read attemp will be handled accor-
		// dingly, getting m_hReaderEvent unlocked in
		// [5]. So only the second read might have to wait
		// a bit at [4].)
//TRACE(TEXT("START UnlockRead ResetEvent(m_hReaderEvent);                  %d\n"), this);
		ResetEvent(m_hReaderEvent);
//TRACE(TEXT("END UnlockRead ResetEvent(m_hReaderEvent);                  %d\n"), this);
		// Signal mutex (unlock)
		// So that possibly a write can occur again at [3]
		SetEvent(m_hMutex); // [2]
	};
//TRACE(TEXT("UnlockRead INTERLOCK: m_iCounter=%d               %d\n"), m_iCounter, this);
}

void CStaNoObjectList::Insert(CStaNoObject &objStaNo)
{
	Insert( new CStaNoObject(objStaNo) );
}

void CStaNoObjectList::RemoveAll()
{
	LockWrite();

	CObject*	pObj;
	WORD		nKey;
	// Clean up the entire list
	POSITION pos = m_list.GetStartPosition();
	while( pos )
	{
		m_list.GetNextAssoc( pos, nKey, pObj );
		delete pObj;
	}
	m_list.RemoveAll();
	m_StaNoToIndex.RemoveAll();
	m_IndexToStaNo.RemoveAll();

	UnlockWrite();
}

void CStaNoObjectList::Remove(WORD nKey, bool bSuppressLockWrite)
{
	if(!bSuppressLockWrite) LockWrite();

	// Remove a particular staNo
	CStaNoObject *pStaNoObject;
	if( m_list.Lookup( nKey, (CObject*&)pStaNoObject ) )
	{
		delete pStaNoObject;
		m_list.RemoveKey( nKey );

		// Arrange the sorting maps
		// Get the array index
		int n;
		m_StaNoToIndex.Lookup( nKey, n );
		// Remove the mapping
		m_StaNoToIndex.RemoveKey( nKey );
		// Remove the array item
		m_IndexToStaNo.RemoveAt(n);
		// Correct the remaining mappings
		for( ; n<m_IndexToStaNo.GetSize(); n++ )
			m_StaNoToIndex.SetAt(
				m_IndexToStaNo.GetAt(n),
				n );			

	}

	if(!bSuppressLockWrite) UnlockWrite();
}

//////////////////////////////////////////////////////////////////////
// Constants/Lookup
//////////////////////////////////////////////////////////////////////

WORD CStaNoObjectList::GetCount() const
{
	int ret;
	LockRead();
	ret = m_list.GetCount();
	UnlockRead();
	return ret;
}

bool CStaNoObjectList::Exist(WORD nTest) const
{
	// Tells you whether the requested
	// staNo (nTest) exists in the list
	CStaNoObject *pStaNoObject;
	bool bExist;
	LockRead();
	bExist = m_list.Lookup( nTest, (CObject*&)pStaNoObject )!=0;
	UnlockRead();
	return bExist;
}

// Old implementation
// THREAD UNSAFE!!!
// Used to iterate the whole list ordered on staNo
// nState consists of two counters used to hold on to the
// iteration information over multiple calls of this function
// A typical call of this function looks like this:
//
//	CStaNoObject aObj;
//	DWORD nState = 0;
//	while( m_listAvailable.IterateSorted( nState, aObj ) )
//		DoSomethingWithObject( &aObj );
/*
bool CStaNoObjectList::IterateSorted(DWORD &nState, CStaNoObject &objStaNo) const
{
	// Retrieve the two counters from the DWORD nState
	WORD nCount;								// Counts the number of iterations/found_items
	WORD nHashCount;							// Stores the last found item
	nCount		= (WORD)(nState >> 16);			// Consists of the number of the last item found
	nHashCount	= (WORD)(nState & 0xFFFF);		// Consist of the key value of the last item found

	// If the maximum number of items from the list has been returned
	// by this function in the past, return false to indicate that
	// the search can stop
	if( nCount == GetCount() )
		return false;

	// We start searching at previous_found+1
	nHashCount++;

	// Increment the nHashCount as long as it does not contain
	//  a staNo that can be found in this list
	CStaNoObject *pStaNoObject;
	while ( !m_list.Lookup( nHashCount, (CObject*&)pStaNoObject ) ) nHashCount++ ;
	objStaNo = *pStaNoObject;

	// We should have found something now, so the number of found_items can
	//  be incremented
	nCount++;

	// Restore the DWORD nState again
	nState = (nCount << 16) | nHashCount;

	// Return TRUE because the search should go on.
	return true;
}
*/

// New implementation
// With thread-safe strategy
bool CStaNoObjectList::IterateSorted(DWORD &nState, CStaNoObject &objStaNo) const
{
	LockRead();

	// Retrieve the two counters from the DWORD nState
	WORD nLatestStaNo;
	WORD nArrayIndex;
	nLatestStaNo	= (WORD)(nState >> 16);
	nArrayIndex		= (WORD)(nState & 0xFFFF);

	if( nState==0 )
	{
		// Initialisation iteration does nothing
	}
	else
	{
		// See if something removed before where we were
		while( (m_IndexToStaNo.GetAt( nArrayIndex )>nLatestStaNo)
			&& (nArrayIndex>=0) ) nArrayIndex--;
		
		nArrayIndex++; // We need the next one (it's iterating after all)

		while( (nArrayIndex<m_IndexToStaNo.GetSize())
			&& (m_IndexToStaNo.GetAt( nArrayIndex )<=nLatestStaNo) ) nArrayIndex++;

	}

	if( nArrayIndex >= m_IndexToStaNo.GetSize() )
		// End of list reached, nothing to proceed with
		{ UnlockRead(); return false; }

	// There is a "new" latest staNo
	nLatestStaNo = m_IndexToStaNo.GetAt(nArrayIndex);

	// Look up the object that goes with it
	CStaNoObject *pStaNoObject;
	m_list.Lookup( nLatestStaNo, (CObject*&)pStaNoObject );
	objStaNo = *pStaNoObject;

	// Restore the DWORD nState again
	nState = (nLatestStaNo << 16) | nArrayIndex;
	
	UnlockRead();

	// Return TRUE because the search should go on.
	return true;
}

// THREAD UNSAFE!!!
void CStaNoObjectList::Iterate(POSITION &rNextPosition, CStaNoObject &rValue) const
{
	CStaNoObject*	pObj;
	WORD			nKey;
	m_list.GetNextAssoc( rNextPosition, nKey, (CObject*&)pObj );
	rValue = *pObj;
}

// THREAD UNSAFE!!!
POSITION CStaNoObjectList::GetStartPosition() const
{
	POSITION n = m_list.GetStartPosition();
	return n;
}

void CStaNoObjectList::Insert(CStaNoObject *pObj)
{
	// Remove a possibly existing object with the same key
	if( Exist( pObj->m_staNo ) )
		Remove( pObj->m_staNo );

	LockWrite();

	// Store a copy of the object in the list
	m_list.SetAt( pObj->m_staNo, pObj );

	// Arrange the sorting maps
	// Look where to insert in the array
	for( int i=0; i<m_IndexToStaNo.GetSize(); i++ )
		if( m_IndexToStaNo.GetAt(i) > pObj->m_staNo )
			break;
	// Insert in the array
	m_IndexToStaNo.InsertAt( i, pObj->m_staNo );
	// Correct the remaining mappings
	for( ; i<m_IndexToStaNo.GetSize(); i++ )
		m_StaNoToIndex.SetAt(
			m_IndexToStaNo.GetAt(i),
			i );

	UnlockWrite();
}

bool CStaNoObjectList::IsDirty()
{
	bool b;
	LockRead();
	b = m_bDirty;
	UnlockRead();
	return b;
}

void CStaNoObjectList::ClearDirty()
{
	LockWrite();
	m_bDirty = false;
	UnlockWrite();
}
