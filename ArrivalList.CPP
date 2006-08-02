// ArrivalList.cpp: implementation of the CArrivalList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEFAULT_TIMECUT 15
#define MAX_TIMECUT 75

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CArrivalList,CStaNoObjectList)

CArrivalList::CArrivalList()
{
	LockWrite();

	// Instantiating a new and empty list
	m_bTimeCut = false;
	m_nTimeCut = DEFAULT_TIMECUT;

	UnlockWrite();
}

CArrivalList::CArrivalList(const CArrivalList &aArrL)
{
	LockWrite();

	m_bTimeCut = false;
	m_nTimeCut = DEFAULT_TIMECUT;

	UnlockWrite();

	*this = aArrL;
}

CArrivalList& CArrivalList::operator =(const CArrivalList &aArrL)
{
	// Empty the list
	RemoveAll();

	Insert( aArrL );

	LockWrite();

	m_bTimeCut = aArrL.m_bTimeCut;
	m_nTimeCut = aArrL.m_nTimeCut;

	UnlockWrite();

	return *this;
}

CArrivalList& CArrivalList::operator =(const CCorrectionList &aCorrL)
{
	// Empty the list
	RemoveAll();

	Insert( aCorrL );

	LockWrite();

	m_bTimeCut = false;
	m_nTimeCut = DEFAULT_TIMECUT;

	UnlockWrite();

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CArrivalList::Insert(CArrival &objArr)
{
	CStaNoObjectList::Insert( new CArrival(objArr) );
}

void CArrivalList::Insert(const CArrivalList &aArrL)
{
	aArrL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aArrL.m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		// Look up every item
		aArrL.m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		// Store a copy in the new list
		Insert( *pArr );
	}

	aArrL.UnlockRead();
}

void CArrivalList::Insert(const CCorrectionList &aCorrL)
{
	aCorrL.LockRead();

	// Iterate the source list
	POSITION nPos;
	nPos = aCorrL.GetStartPosition();
	while( nPos )
	{
		CCorrection	aCorr;
		CArrival	aArr;
		// Look up every item
		aCorrL.Iterate( nPos, aCorr );
		// Copy it
		aArr = aCorr;
		// Store a copy in the new list
		Insert( aArr );
	}

	aCorrL.UnlockRead();
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CArrivalList::Serialize(CArchive &ar)
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
			CArrival*	pArr;
			WORD		nKey;
			m_list.GetNextAssoc( pos, nKey, (CObject*&)pArr );
			pArr->Serialize(ar);
		}

		ar << (char) m_bTimeCut;
		ar << m_nTimeCut;

		UnlockRead();
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 3000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 3.00
			CArrival aArrival;
			WORD nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aArrival.Serialize(ar);
				Insert( aArrival );
			}

			LockWrite();

			char temp;
			ar >> temp;
			ar >> m_nTimeCut;
			m_bTimeCut = temp>0;

			UnlockWrite();
		}
		else if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			CArrival aArrival;
			WORD nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aArrival.Serialize(ar);
				Insert( aArrival );
			}
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CArrival aArrival;
			int nCount;
			ar >> nCount;

			while( nCount-- )
			{
				aArrival.Serialize(ar);
				Insert( aArrival );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Constants/Lookup
//////////////////////////////////////////////////////////////////////

CArrival CArrivalList::GetAt(WORD nStaNo) const
{
	// Retrieve a particular staNo
	CArrival *pArr;
	
	LockRead();
	BOOL bExist = m_list.Lookup( nStaNo, (CObject*&)pArr );
	UnlockRead();

	if( bExist )
		return *pArr;
	else
		return CArrival(); // return empty
}

bool CArrivalList::IterateSorted(DWORD &nState, CArrival &objArr) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objArr = GetAt(objStaNo.m_staNo);
		return true;
	}
	return false;
}

bool CArrivalList::IterateSortedCut(DWORD &nState, CArrival &objArr) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objArr = GetAt(objStaNo.m_staNo);
		if( IsTimeCutted(objStaNo.m_staNo) )
			return true;
		else
			return IterateSortedCut(nState,objArr);
	}
	return false;
}

bool CArrivalList::IterateSortedUncut(DWORD &nState, CArrival &objArr) const
{
	CStaNoObject objStaNo;
	if( CStaNoObjectList::IterateSorted(nState,objStaNo) )
	{
		objArr = GetAt(objStaNo.m_staNo);
		if( !IsTimeCutted(objStaNo.m_staNo) )
			return true;
		else
			return IterateSortedUncut(nState,objArr);
	}
	return false;
}

void CArrivalList::Iterate( POSITION& rNextPosition, CArrival& rValue ) const
{
	CArrival*	pArr;
	WORD		nKey;
	m_list.GetNextAssoc( rNextPosition, nKey, (CObject*&)pArr );
	rValue = *pArr;
}

//////////////////////////////////////////////////////////////////////
// CArrivalList specific
//////////////////////////////////////////////////////////////////////

bool CArrivalList::GetAtOrder(WORD nOrder, CArrival *pArrival) const
{
	LockRead();

	POSITION nPos = m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		if( pArr->m_order == nOrder )
		{
			UnlockRead();

			*pArrival = *pArr;
			return true;
		}
	}
	UnlockRead();
	return false;
}

bool CArrivalList::GetAtTime(DWORD nUnits, CArrival *pArrival) const
{
	LockRead();

	POSITION nPos = m_list.GetStartPosition();
	CArrival* pHoldOnToArr = NULL;
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		// Retrieve one arrival
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );

		// Compare the retrieved one's time with the target time
		if( pArr->m_units <= nUnits )
		{
			if( pHoldOnToArr )
			{
				if( pHoldOnToArr->m_units < pArr->m_units )
					// If this one is bigger than one we found earlier
					// (and smaller than the target, which we checked
					// a few lines up) we take it
					pHoldOnToArr = pArr;
				else if( (pHoldOnToArr->m_units==pArr->m_units)
						&& (pHoldOnToArr->m_rank > pArr->m_rank) )
					// If this one is equal to one we found earlier
					// we take the one with the best ranking
					pHoldOnToArr = pArr;

			}
			else
				// If this is the first one we find with a smaller time
				// than the target we take it
				pHoldOnToArr = pArr;
		}
	}

	UnlockRead();

	if( pHoldOnToArr && pArrival )
	{
		*pArrival = *pHoldOnToArr;
		return true;
	}
	else
		return false;
}

bool CArrivalList::GetAtRank(WORD nRank, CArrival *pArrival) const
{
	LockRead();

	POSITION nPos = m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		if( pArr->m_rank == nRank )
		{
			UnlockRead();

			*pArrival = *pArr;
			return true;
		}
	}
	UnlockRead();
	return false;
}

void CArrivalList::AwardPoints(CMap<WORD,WORD&,WORD,WORD&> *pPointsList)
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	POSITION nPos = m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		if( !pPointsList || !pPointsList->Lookup( pArr->m_rank, pArr->m_points ) )
			pArr->m_points = 0;
	}
	UnlockWrite();
}

void CArrivalList::AwardBonuses(CMap<WORD,WORD&,WORD,WORD&> *pBonusesList)
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	POSITION nPos = m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		if( !pBonusesList || !pBonusesList->Lookup( pArr->m_rank, pArr->m_bonus ) )
			pArr->m_bonus = 0;
	}
	UnlockWrite();
}

void CArrivalList::Remove1XSeconds()
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	POSITION nPos = m_list.GetStartPosition();
	while( nPos )
	{
		CArrival*	pArr;
		WORD		nKey;
		m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );
		pArr->m_units = (pArr->m_units/1000)*1000;
	}
	UnlockWrite();
}

void CArrivalList::ApplyGroupTime(unsigned short nDelaySec)
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	WORD nCount	= m_list.GetCount();
	WORD nRank	= 1;
	DWORD nUnitsPrevious=0, nUnitsFirst=0;
	// Do this as often as there are arrivals stored
	while( nCount )
	{
		// Every time look up the matching arrivals
		// for the current rank
		POSITION nPos = m_list.GetStartPosition();
		while( nPos )
		{
			CArrival*	pArr;
			WORD		nKey;
			m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );

			// If an arrival found for the current rank
			if( pArr->m_rank == nRank )
			{
				// Look for short delays between competitors
				if(/* ( pArr->m_units - nUnitsPrevious > 0 ) & */
					( pArr->m_units - nUnitsPrevious <= (1000*nDelaySec) ) )
				{
					nUnitsPrevious = pArr->m_units;
					// If so, give them the same time
					pArr->m_units = nUnitsFirst;
				}
				else
				{
					// Update the "remember" values before the next
					// iteration only if there really is a new time
					nUnitsPrevious = pArr->m_units;
					nUnitsFirst    = pArr->m_units;
				}
				// For every matching arrival
				// we have to find one less now
				nCount--;
			}
		}
		// If all arrivals for a given rank are found
		// we proceed with the next rank figure
		nRank++;
	}
	UnlockWrite();
}

void CArrivalList::RemoveGapsRanking()
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	WORD nCount	= m_list.GetCount();
	WORD nRank	= 1;
	CList<CArrival*,CArrival*&> listOrdered;

	// First make an ordered list of arrivals
		// Do this as often as there are arrivals stored
		while( nCount )
		{
			// Every time look up the matching arrivals
			// for the current rank
			POSITION nPos = m_list.GetStartPosition();
			while( nPos )
			{
				CArrival*	pArr;
				WORD		nKey;
				m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );

				// If an arrival found for the current rank
				if( pArr->m_rank == nRank )
				{
					listOrdered.AddTail( pArr );
					// For every matching arrival
					// we have to find one less now
					nCount--;
				}
			}
			// If all arrivals for a given rank are found
			// we proceed with the next rank figure
			nRank++;
		}
	// Use the ordered list of arrivals to assign new rankings
		POSITION nPos = listOrdered.GetHeadPosition();
		nRank = 1;
		while( nPos )
			listOrdered.GetNext(nPos)->m_rank = nRank++;

	UnlockWrite();
}

void CArrivalList::RemoveGapsOrder()
{
	LockWrite(); // This is not quite true, but it might protect
	// the CArrival objects that are edited in here

	WORD nCount	= m_list.GetCount();
	WORD nOrder	= 1;
	CList<CArrival*,CArrival*&> listOrdered;

	// First make an ordered list of arrivals
		// Do this as often as there are arrivals stored
		while( nCount )
		{
			// Every time look up the matching arrivals
			// for the current rank
			POSITION nPos = m_list.GetStartPosition();
			while( nPos )
			{
				CArrival*	pArr;
				WORD		nKey;
				m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );

				// If an arrival found for the current rank
				if( pArr->m_rank == nOrder )
				{
					listOrdered.AddTail( pArr );
					// For every matching arrival
					// we have to find one less now
					nCount--;
				}
			}
			// If all arrivals for a given rank are found
			// we proceed with the next rank figure
			nOrder++;
		}
	// Use the ordered list of arrivals to assign new rankings
		POSITION nPos = listOrdered.GetHeadPosition();
		nOrder = 1;
		while( nPos )
			listOrdered.GetNext(nPos)->m_rank = nOrder++;

	UnlockWrite();
}

bool CArrivalList::CheckIntegrity(CString *cCheckResult)
{
	LockRead();

	// NOTE THAT NOT EVERY INTEGRITY ERROR REALLY HAS TO BE AN ERROR:
	//  TIME DISCREPANCIES CAN BE A CHOICE OF THE JURY ON-SITE
	//  RANK DOUBLURES CAN BE A REAL EX AEQUO
	//  AND HOLES IN THE CLASSIFICATION CAN BE RESULT OF EX AEQUOS

	// Set up a start text for the results box
	*cCheckResult = LoadStr( IDS_DIV2 )+"\r\n\r\n";

	WORD nRankPrevious=0;
	DWORD nUnitsPrevious=0;
	WORD nErrorsFound=0;

	WORD nCount	= GetCount();
	WORD nRank	= 1;
	// Do this as often as there are arrivals stored
	while( nCount )
	{
		// Every time look up the matching arrivals
		// for the current rank
		POSITION nPos = m_list.GetStartPosition();
		while( nPos )
		{
			CArrival*	pArr;
			WORD		nKey;
			m_list.GetNextAssoc( nPos, nKey, (CObject*&)pArr );

			// If an arrival found for the current rank
			if( pArr->m_rank == nRank )
			{
				// LOOK FOR RANK DUPLICATES
				if( nRankPrevious == pArr->m_rank )
				{
					// If so, print a row for the results box
					char czBuffer[10];
					_itoa( pArr->m_rank, czBuffer, 10 );
					*cCheckResult += LoadStr( IDS_DIV3 )+CString(czBuffer)+"\r\n";
					// Increment the errors count
					nErrorsFound++;

					nUnitsPrevious = 0;	// Otherwise it's very likely that we get a time error
										//  in the next iteration
				}
				else
				{
					// LOOK FOR RANKING HOLES
					if( nRankPrevious + 1 < pArr->m_rank )
					{
						// If so, print a row for the results box
						TCHAR czBuffer[10];
						_itot( pArr->m_rank, czBuffer, 10 );
						*cCheckResult += LoadStr( IDS_DIV4 )+CString(czBuffer)+"\r\n";
						// Increment the errors count
						nErrorsFound++;

						nUnitsPrevious = 0;	// Otherwise it's very likely that we get a time error
											//  in the next iteration
					}
					else
					{
						// LOOK FOR TIME DISCREPANCIES
						if( nUnitsPrevious > pArr->m_units )
						{
							// If so, print another row for the results box
							TCHAR czBuffer[10];
							_itot( nRankPrevious, czBuffer, 10 );
							*cCheckResult += LoadStr( IDS_DIV5 )+CString(czBuffer);
							_itot( pArr->m_rank, czBuffer, 10 );
							*cCheckResult += LoadStr( IDS_DIV6 )+CString(czBuffer)+"\r\n";
							// Increment the errors count
							nErrorsFound++;
						}
						// Note that this is taken in the else of the rank check
						// This is done because a time error is very likely to come when
						//  there is a rank error - we don't wanna get both
						nUnitsPrevious = pArr->m_units;
					}
				}

				// Update the "remember" values before the next iteration
				nRankPrevious = pArr->m_rank;

				// For every matching arrival
				// we have to find one less now
				nCount--;
			}
		}
		// If all arrivals for a given rank are found
		// we proceed with the next rank figure
		nRank++;
	}

	UnlockRead();

	// Print 'check completed'
	*cCheckResult += "\r\n";
	*cCheckResult += "[ "+LoadStr( IDS_DIV7 )+" ]\r\n";
	// Set up a footer text for the results box
	// saying if (and how many) errors are encountered
	if( nErrorsFound )
	{
		TCHAR czBuffer[10];
		_itot( nErrorsFound, czBuffer, 10 );

		*cCheckResult += "[ "+CString(czBuffer)+" "+LoadStr( IDS_DIV8 )+" ]\r\n";
		return FALSE;
	}
	else
	{
		*cCheckResult += "[ "+LoadStr( IDS_DIV9 )+" ]\r\n";
		return TRUE;
	}
}

bool CArrivalList::Import()
{
	// Set up the open dialog box
	CFileDialogImport aFileDlg( TRUE, TEXT("*.txt") );
	aFileDlg.m_ofn.lpstrFilter = TEXT("Alge OPTIc Results (*.txt)\0*.txt\0All files (*.*)\0*.*\0AMB ChronX Results (*.csv)\0*.csv\0Lynx FinishLynx Results (*.lif)\0*.lif\0Omega Scan'O'Vision data handling (*.txt)\0*.txt\0Omega Scan'O'Vision formatted results (*.cl)\0*.cl\0Skunkware TT*Ware Results (*.txt)\0*.txt\0Text files (*.txt; *.csv)\0*.txt;*.csv\0\0");
	CString czBoxTitle = LoadStr( IDS_DIV10 );
	aFileDlg.m_ofn.lpstrTitle = czBoxTitle;
	aFileDlg.m_ofn.Flags = aFileDlg.m_ofn.Flags | OFN_FILEMUSTEXIST;

	//Restore the selections for this dialog
	CSRRegKey reg1;
	reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
	aFileDlg.m_ofn.nFilterIndex = reg1.GetDWord( TEXT("Choose file dialog default type"), 2 );
	if( reg1.GetString( TEXT("Most recent file"), TEXT("") ).GetLength() )
		_tcscpy( aFileDlg.m_ofn.lpstrFile, reg1.GetString( TEXT("Most recent file"), TEXT("") ) );
	
	// Evaluate the open dialog box
	if ( aFileDlg.DoModal() == IDOK )
	{
		bool bProceed;
		// Get from the registry whether we should insert an extra dialog box
		CSRRegKey reg2;
		reg2.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );

		if( reg2.GetBool( TEXT("ShowImportFileCheckDialog"), true ) )
		{
			CCheckImportFile dlgChk( aFileDlg.GetPathName() );
			if( dlgChk.DoModal() == IDOK )
				bProceed = true;
			else
				bProceed = false;
		}
		else
			bProceed = true;

		if( bProceed )
		{
			// Set up temporarely data items
			CList < CArrival, CArrival& > arrivalImportListRank;
			// Create file handler
			CFile importFile; 
			CFileException fileException;

			try
			{
				// Open the chosen file
				if ( importFile.Open( aFileDlg.GetPathName(), CFile::modeRead|CFile::shareDenyNone, &fileException ) )
				{
					// We are going to copy the whole file into this CString
					CString czImportFile;

					// returncount to registrate that still data is coming out of the file
					int nReturnCount;
					// bytecount to count the number of bytes imported to prevent hangups
					int nByteCount=65536;
					// We are going to retrieve one character per cycle and hold it in czBuffer
					char czBuffer[1];

					// Get the first character
					nReturnCount = importFile.Read( &czBuffer, 1 );
					// Now get all the other characters
					while( nReturnCount && nByteCount-- )
					{
						// We add the retreived character to the string
						czImportFile = czImportFile + CString(czBuffer).Left(1);
						// And get the next one
						nReturnCount = importFile.Read( &czBuffer, 1 );
					}

					// Create the dialog which asks for which event number to import
					CImportPreview dlgImport;
					dlgImport.m_contents = czImportFile;

					switch( aFileDlg.m_ofn.nFilterIndex )
					{
						// Alge
						case  1:
							dlgImport.m_rankCol=0;
							dlgImport.m_staNoCol=1;
							dlgImport.m_timeCol=9;
							dlgImport.m_decimals=3;
							dlgImport.m_headerSize=0;
							dlgImport.m_separation=1;
							dlgImport.m_timeNotation=1;
							dlgImport.m_importType=1;
							dlgImport.m_rank=0;
							dlgImport.m_separator=0;
							bProceed = true;
							break;
						// AMB
						case  3:
							dlgImport.m_rankCol=0;
							dlgImport.m_staNoCol=1;
							dlgImport.m_timeCol=4;
							dlgImport.m_decimals=3;
							dlgImport.m_headerSize=0;
							dlgImport.m_separation=1;
							dlgImport.m_timeNotation=1;
							dlgImport.m_importType=1;
							dlgImport.m_rank=0;
							dlgImport.m_separator=1;
							bProceed = true;
							break;
						// Lynx
						case 4:
							dlgImport.m_rankCol=0;
							dlgImport.m_staNoCol=1;
							dlgImport.m_timeCol=6;
//							dlgImport.m_decimals=1;
							dlgImport.m_headerSize=1;
							dlgImport.m_rank=1;
							dlgImport.m_separation=1;
							dlgImport.m_timeNotation=0;
							dlgImport.m_separator=1;
							dlgImport.m_importType=1;
							bProceed = aFileDlg.GetSuppressPreview() || (dlgImport.DoModal() == IDOK);
							break;
						// Omega DH
						case  5:
							dlgImport.m_importType=0;
							bProceed = aFileDlg.GetSuppressPreview() || (dlgImport.DoModal() == IDOK);
							break;
						// Omega CL
						case  6:
//							dlgImport.m_rankStart=0;
//							dlgImport.m_staNoStart=6;
//							dlgImport.m_timeStart=29;
//							dlgImport.m_rankEnd=3;
//							dlgImport.m_staNoEnd=11;
//							dlgImport.m_timeEnd=40;

//							dlgImport.m_decimals=3;
//							dlgImport.m_headerSize=12;
							dlgImport.m_separation=0;
							dlgImport.m_timeNotation=0;
							dlgImport.m_importType=1;
							dlgImport.m_rank=1;
							bProceed = aFileDlg.GetSuppressPreview() || (dlgImport.DoModal() == IDOK);
							break;
						// Skunkware TT*Ware
						case 7:
							dlgImport.m_rankCol=0;
							dlgImport.m_staNoCol=2;
							dlgImport.m_timeCol=9;
							dlgImport.m_decimals=2;
							dlgImport.m_headerSize=0;
							dlgImport.m_rank=1;
							dlgImport.m_separation=1;
							dlgImport.m_timeNotation=0;
							dlgImport.m_separator=1;
							dlgImport.m_importType=1;
							bProceed = true;
							break;
						// All files
						// Text files
						default:
							bProceed = aFileDlg.GetSuppressPreview() || (dlgImport.DoModal() == IDOK);
					}
					
					if ( bProceed )
					{
						// Set an appropriate waiting cursor
						HCURSOR objOldCursor = SetCursor( LoadCursor( NULL, IDC_WAIT ) );

						// Set up temporarely data items, for every row blank/new
						CString tempRank, tempStaNo, tempTime;
						// As a result of the dialog this file will be treated as a Scan'O'Vision file
						if( dlgImport.m_importType==0 )
						{
							CString tempEvent, tempRound, tempHeat;
							int nCount = 0;
							// Continue as long as characters are coming
							while ( nCount < czImportFile.GetLength() )
							{
								// Count the data fields we're getting, per row
								// (So reset it with =0 before every new row)
								int fieldcounter=0;
								// Continue until end of row "\r"
								while ( czImportFile[nCount]!='\r' )
								{
									if ( czImportFile[nCount] == ';' )
									{
										// If we get to a field seperator,
										//  we increment the fieldcounter
										fieldcounter++;
									}
									// Add all incoming numerical characters to the
									//  appropriate temporarely strings
									if ( (czImportFile[nCount] >= '0') && (czImportFile[nCount] <= '9') )
										switch(fieldcounter)
										{
											case 0: tempEvent += czImportFile[nCount];
											break;
											case 1: tempRound += czImportFile[nCount];
											break;
											case 2: tempHeat += czImportFile[nCount];
											break;
											case 4: tempStaNo += czImportFile[nCount];
											break;
											case 7: tempTime += czImportFile[nCount];
											break;
										}
									// Get the next character
									nCount++;
								}
								// After the \r we get the \n (if there is still anything coming)
								nCount++;
								while ( (nCount<czImportFile.GetLength()) && (czImportFile[nCount]=='\n') ) nCount++;

								// Process the retrieved data when it's the correct event number
								if( ( dlgImport.m_event == _ttoi( tempEvent ) )
									&&
									( dlgImport.m_round == _ttoi( tempRound ) )
									&&
									( dlgImport.m_heat == _ttoi( tempHeat ) ) )
								{
									tempTime = "       "+tempTime;
									CArrival aArrival;
									aArrival.m_staNo	= _ttoi( tempStaNo );
									aArrival.m_units	= _ttoi( tempTime.Right(9).Left(8) );

														// Throw away the 1/10 000th seconds
														// and calculate the units
									
									// Insert the data in the arrivalImportList on rank
									POSITION skipList = arrivalImportListRank.GetHeadPosition();
									while ( skipList )
									{
										CArrival aSkipArrival;
										aSkipArrival = arrivalImportListRank.GetAt( skipList );
										// When we find a item that has a larger time then ours
										if( aSkipArrival.m_units > aArrival.m_units ) break;
										aSkipArrival = arrivalImportListRank.GetNext( skipList );
									}
									if ( skipList )
										// ... insert ours before the found one
										arrivalImportListRank.InsertBefore( skipList, aArrival );
									else
										// If nothing found: add to tail
										arrivalImportListRank.AddTail( aArrival );
								}
								tempRank = "";
								tempEvent = "";
								tempRound = "";
								tempHeat = "";
								tempStaNo = "";
								tempTime = "";
							}
						}
						else // dlgImport.m_importType==1
						{
							char cSeparator;
							switch( dlgImport.m_separator )
							{
								case 0:  cSeparator = '\t'; break;
								case 1:  cSeparator = ',' ; break;
								case 2:  cSeparator = ';' ; break;
								case 3:  cSeparator = '|' ; break;
								case 4:  cSeparator = '%' ; break;
								case 5:  cSeparator = '/' ; break;
								default: cSeparator = '\t'; break;
							}

							czImportFile = czImportFile + "\r\n";
							int nCount = 1;

							while( czImportFile.GetLength() )
							{
								// First we find the first line break
								int nOffset = czImportFile.Find( TEXT("\r\n") );
								// So we can take the first line for handling
								CString czLine = czImportFile.Mid( 0, nOffset );
								// After handling, we remove the handled line
								// including its break (therefore the +2)
								czImportFile = czImportFile.Mid( nOffset+2 );

								// We check whether this line can already be used
								if( nCount++ > dlgImport.m_headerSize )
								{
									// We make sure that the handled line is at least 80 characters long and consists of sufficient tab stops
									czLine = czLine + "                                                                                "+CString( cSeparator, 30 );

									// Take the needed data from the line handled
									if( dlgImport.m_separation==0 )
									{
										// In case of fixed columns
										tempRank	= czLine.Mid( dlgImport.m_rankStart -1, dlgImport.m_rankEnd  - (dlgImport.m_rankStart -1) );
										tempStaNo	= czLine.Mid( dlgImport.m_staNoStart-1, dlgImport.m_staNoEnd - (dlgImport.m_staNoStart-1) );
										tempTime	= czLine.Mid( dlgImport.m_timeStart -1, dlgImport.m_timeEnd  - (dlgImport.m_timeStart -1) );
									}
									else
									{
										// In case of tab separated columns
										for( int j=0; j<=max(max(dlgImport.m_staNoCol,dlgImport.m_rankCol),dlgImport.m_timeCol); j++ )
										{
int nStart(0);
// See if there are quotes in here
if( czLine.Find('\"')!=-1 )
{
	// If the quotes are preceeding the next separator
	// we need to ignore the separator
	if( czLine.Find('\"')<czLine.Find(cSeparator) )
	{
		nStart = czLine.Find('\"')+1;
		nStart = czLine.Find('\"', nStart);
	}
}

   
											if( dlgImport.m_rankCol ==j ) tempRank  = czLine.Mid( nStart, czLine.Find( cSeparator ) );
											if( dlgImport.m_staNoCol==j ) tempStaNo = czLine.Mid( nStart, czLine.Find( cSeparator ) );
											if( dlgImport.m_timeCol ==j ) tempTime  = czLine.Mid( nStart, czLine.Find( cSeparator ) );

											czLine = czLine.Mid( czLine.Find( cSeparator, nStart )+1 );
										}
									}
									// Process the retrieved data
										CArrival aArrival;
										int i;

										// We remove all characters from the strings, except for numerical
										i=0;
										while( i<tempStaNo.GetLength() )
										{
											if( tempStaNo.Mid( i ).FindOneOf(TEXT("1234567890")) )
												tempStaNo = tempStaNo.Mid( 0, i )+tempStaNo.Mid( i+1 );
											else
												i++;
										}
										aArrival.m_staNo	= _ttoi( tempStaNo );
										// We remove all characters from the strings, except for numerical
										i=0;
										while( i<tempRank.GetLength() )
										{
											if( tempRank.Mid( i ).FindOneOf(TEXT("1234567890")) )
												tempRank = tempRank.Mid( 0, i )+tempRank.Mid( i+1 );
											else
												i++;
										}
										aArrival.m_rank		= _ttoi( tempRank );
										// We remove all characters from the strings, except for numerical
										i=0;
										while( i<tempTime.GetLength() )
										{
											if( tempTime.Mid( i ).FindOneOf(TEXT("1234567890")) )
												tempTime = tempTime.Mid( 0, i )+tempTime.Mid( i+1 );
											else
												i++;
										}
										if( dlgImport.m_timeNotation==0 )
										{
											// Add decimals
											// (We take the provided decimals, add sufficient zeros, and take only the thousandths)
											aArrival.m_units	= _ttoi( CString(tempTime.Right( dlgImport.m_decimals )+TEXT("000")).Left(3) );

											// Prepare for remaining time information: remove decimals
											tempTime			= tempTime.Left( tempTime.GetLength() - dlgImport.m_decimals );
											// Add sufficient zeros, and take hmmss
											tempTime			= "00000" + tempTime;
											tempTime			= tempTime.Right( 5 );

											// Add seconds. minutes and hours
											aArrival.m_units	+= _ttoi( tempTime.Mid( 3, 2 ) ) *    1000;
											aArrival.m_units	+= _ttoi( tempTime.Mid( 1, 2 ) ) *   60000;
											aArrival.m_units	+= _ttoi( tempTime.Left(  1  ) ) * 3600000;
										}
										else
										{
											aArrival.m_units = _ttoi( tempTime );
											if( aArrival.m_units==999999999 ) aArrival.m_units=0;
										}

									if( aArrival.m_rank || (aArrival.m_units&&dlgImport.m_rank) )
									{
										// Insert the data in the arrivalImportList on rank
										POSITION skipList = arrivalImportListRank.GetHeadPosition();
										while ( skipList )
										{
											CArrival aSkipArrival;
											aSkipArrival = arrivalImportListRank.GetAt( skipList );
											// When we find a item that has a larger time then ours
											if( aSkipArrival.m_rank >  aArrival.m_rank ) break;
											if( aSkipArrival.m_rank == aArrival.m_rank )
												if( aSkipArrival.m_units > aArrival.m_units ) break;
											aSkipArrival = arrivalImportListRank.GetNext( skipList );
										}
										if ( skipList )
											// ... insert ours before the found one
											arrivalImportListRank.InsertBefore( skipList, aArrival );
										else
											// If nothing found: add to tail
											arrivalImportListRank.AddTail( aArrival );
									}
								}
							}
						}

						// MAKE AN IMPORTED LIST ON STANO FROM THE IMPORTED LIST ON RANKING
						// Note that the imported list on StaNo is empty at this point
						CArrival aArrival;
						WORD nRank=1;
						// Iterate the whole imported list on ranking
						POSITION skipList = arrivalImportListRank.GetHeadPosition();
						while ( skipList )
						{
							aArrival = arrivalImportListRank.GetNext( skipList );
							// We test whether the imported staNo is not zero
							if( aArrival.m_staNo )
							{
								// Test whether rankings have to be given
								// Rankings have to be given for all DH imports or
								// when recalculation is selected for text file imports
								if( (dlgImport.m_importType==0) || dlgImport.m_rank)
									// If it exists, give it its ranking
									aArrival.m_rank = nRank;
								// ...and store it in the imported list on StaNo
								Insert( aArrival );

								nRank++;
							}
						}

						// Arrange the selected file type in the file dialog to be stored in the registry
						LONG er;
						CSRRegKey reg3;
						er = reg3.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
						if( er == ERROR_SUCCESS )
						{
							reg3.SetString( TEXT("Most recent file"), aFileDlg.GetFileName() );
							reg3.SetDWord( TEXT("Choose file dialog default type"), aFileDlg.m_ofn.nFilterIndex );
						}

						// Remove the waiting cursor
						SetCursor( objOldCursor );

						return true;
					}
				}
				else
					MessageBox( NULL, LoadStr( IDS_MBC_10 ), LoadStr( IDS_MBT_10 ), MB_OK|MB_ICONEXCLAMATION );

			}
			catch(...)
			{
				MessageBox( NULL, LoadStr( IDS_MBC_11 ), LoadStr( IDS_MBT_11 ), MB_OK|MB_ICONEXCLAMATION );
			}
		}
	}
	return false;
}

void CArrivalList::ApplyRanks(bool bTimeTrial)
{
	LockRead();

	// List in which we store the ordered values
	CList< CArrival, CArrival& > listOrdered;

	CArrival aArrival;
	POSITION nPos = GetStartPosition();
	while( nPos )
	{
		Iterate( nPos, aArrival );

		bool ready = false; // See below

		// We iterate the ordered values list to look for matching values
		POSITION nPosSeek = listOrdered.GetTailPosition();
		while( nPosSeek )
		{
			CArrival aTestValue;
			aTestValue = listOrdered.GetAt( nPosSeek );

			// We consider a value matching when the following comparant is just smaller
			// With equal matches we look at the starting order where the highest order makes the best ranking
			if( aTestValue.m_units < aArrival.m_units || 
					( (aTestValue.m_units==aArrival.m_units) && (aTestValue.m_order>aArrival.m_order) )
				)
			{ 
				// If at right position, add handled value to ordered list at this point
				listOrdered.InsertAfter( nPosSeek, aArrival );
				
				ready = true; // See below
				
				// Make our search stop
				nPosSeek = NULL;
			}
			else
			{ 
				// If still not at the right position, change pointer
				listOrdered.GetPrev( nPosSeek );
			}
		}

		// If not ready: the list doesn't contain any values smaller then the
		//  one we're handling (or it's empty at all), so we add the first item
		//  to our ordered list
		if( !nPosSeek && !ready )
		{
			listOrdered.AddHead( aArrival );
		}
	}

	UnlockRead();

	// After making an ordered list,
	// we use this list to order our source list
	int nRank=1;
	POSITION theOrderedPos = listOrdered.GetHeadPosition();
	while( theOrderedPos )
	{
		aArrival = listOrdered.GetNext( theOrderedPos );
		aArrival.m_rank = nRank++;
		Insert( aArrival );
	}
}

void CArrivalList::ApplyTimeTrialRanks()
{
	ApplyRanks(true);
}

void CArrivalList::SetTimeCut(BYTE value)
{
	if( value )
	{
		if( value!=GetTimeCut() )
		{
			LockWrite();

			m_bTimeCut = true;
			m_nTimeCut = min(value, MAX_TIMECUT); // Set time cut at 75% maximum

			UnlockWrite();
		}
	}
	else
		ResetTimeCut();
}

void CArrivalList::ResetTimeCut()
{
	LockRead();
	if( m_bTimeCut )
	{
		UnlockRead();
		LockWrite();
		m_bTimeCut = false;
		m_nTimeCut = 0;
		UnlockWrite();
	}
	else
		UnlockRead();
}

bool CArrivalList::IsTimeCutted( WORD nStaNo ) const
{
	if( m_bTimeCut && Exist( nStaNo ) )
	{
		CArrival aArr;
		if( GetAtRank( 1, &aArr ) )
		{
			DWORD time = aArr.m_units;
			time += (time / 100)*m_nTimeCut;

			if( GetAt(nStaNo).m_units > time )
				return true;
		}
	}
	return false;
}

BYTE CArrivalList::GetTimeCut()
{
	LockRead();
	BYTE b = m_bTimeCut ? m_nTimeCut : 0;
	UnlockRead();
	return b;
}