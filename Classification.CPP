// Classification.cpp: implementation of the CClassification class.
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

CClassification::CClassification(CStageRaceDoc* pDoc)
{
	m_pDoc = pDoc;
	m_firstClass = true;
}

CClassification::~CClassification()
{

}

bool CClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
{
	// This function is to decide how two arrivals relate to each other

	// objSubj is the arrival of which we want to know whether it is "smaller"
	// than the objSubj that was already in the list

	// The function returns true if the subject (objSubj) should be inserted
	// just "before" the test object, where "after" means further away from
	// the winner

	// First test on the ridden time (where thousandth already have been subtracted)
	if( (objTest.m_units > objSubj.m_units)
		&& (!bRankOnly) )
		return true;
	if( (objTest.m_units == objSubj.m_units)

		|| bRankOnly )
	{
		// Secondly test for the thousandth of seconds (*)
		if( (objTest.m_thousandth > objSubj.m_thousandth)
			&& m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS) && (!bRankOnly) )
			return true;

		if( (objTest.m_thousandth == objSubj.m_thousandth)
			|| !m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS) || bRankOnly )
			{
				// Thirthly test on sum of the rankings (*)
				if( (objTest.m_sumRank+objTest.m_rank > objSubj.m_sumRank+objSubj.m_rank)
					&& !m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING) && (!bRankOnly) )
					return true;

				if( (objTest.m_sumRank+objTest.m_rank == objSubj.m_sumRank+objSubj.m_rank)
					|| m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING) || bRankOnly )
				{
					// Fourthly test on the ranking in the last (always current) stage
					if( objTest.m_rank > objSubj.m_rank )
						return true;
				}
			}
	}
	return false;

	// (*) Note: these (*) tests can be overridden by user settings

	// Note: for single stage classifications you want only to sort on the ranking
	//		(the fourth test). For this the bRankOnly is used
}

void CClassification::StoreClassification()
{
	// Function to be called after every calculated stage

	// It copies the current general classification to m_store,
	// in order to be used for the next stage

	// We cannot leave general classification information in m_generalClassification
	// We would then never know whether a competitor also competed in the previous stage
	//  because we want (again) to make sure that a competitor competes in all stages!
	m_store.RemoveAll();
	
	CArrival objArrival;
	POSITION nPos = m_generalClassification.GetHeadPosition();
	while( nPos )
	{
		objArrival = m_generalClassification.GetNext( nPos );
		m_store.SetAt( objArrival.m_staNo, objArrival );
	}

	// After copying, the current stages lists can be emptied
	m_classification.RemoveAll();
	m_generalClassification.RemoveAll();

	// After the first stage the m_firstClass bit should be cleared
	//  so that the sort functions know that they're not handling the first
	//  stage in the general classification
	m_firstClass = false;

}

void CClassification::AddCompetitor(CArrival &aArr, bool bExcludeStage /*= false*/ )
{
	// This function is called by the implementation of CClassification
	//  for every competitor/arrival for every stage
	// We make sure that the particular competitor/arrival is inserted in...


	CArrival objArr( aArr );	// We make sure that all these functions do NOT
								// mess up the data from the calling functions

	// the stage classification
	DoClass( objArr );
	// the general classification
	if( bExcludeStage ) objArr.m_units = 0; // This makes it possible not to include
											// a classification into the general cl.
	DoGeneral( objArr );
}

void CClassification::DoClass(CArrival &aArr)
{
	// This function receives an arrival (aArr) and puts it into the
	//  stage classification list m_classification at the right spot

	bool ready = false; // See below

	// We iterate the ordered values list to look for matching values
	POSITION nPos = m_classification.GetHeadPosition();
	while( nPos )
	{
		CArrival aTestValue;
		aTestValue = m_classification.GetAt( nPos );

		// We consider a value matching when the following comparant is just bigger
		if( InsertHere(aTestValue,aArr,true) )
		{ 
			// If at right position, add handled value to ordered list at this point
			m_classification.InsertBefore( nPos, aArr );
			
			ready = true; // See below
			
			// Make our search stop
			nPos = NULL;
		}
		else
		{ 
			// If still not at the right position, change pointer
			m_classification.GetNext( nPos );
		}
	}

	// If not ready: the list doesn't contain any values bigger then the
	//  one we're handling (or it's empty at all), so we add the item
	//  at the end to our ordered list
	if( !nPos && !ready )
	{
		m_classification.AddTail( aArr );
	}
}

void CClassification::DoGeneral(CArrival &aArr)
{
	// This function receives an arrival (aArr) and puts it into the
	//  general classification list m_generalClassification at the right spot

	if( CalculateGeneralFromStage( &aArr ) )
	{

		// Now we put the new information (eventually added with existing)
		//  into the current general classification

		bool ready = false; // See below

		// We iterate the ordered values list to look for matching values
		POSITION nPos = m_generalClassification.GetHeadPosition();
		while( nPos )
		{
			CArrival aTestValue;
			aTestValue = m_generalClassification.GetAt( nPos );

			// We consider a value matching when the following comparant is just bigger
			if( InsertHere(aTestValue,aArr,false) )
			{ 
				// If at right position, add handled value to ordered list at this point
				m_generalClassification.InsertBefore( nPos, aArr );
				
				ready = true; // See below
				
				// Make our search stop
				nPos = NULL;
			}
			else
			{ 
				// If still not at the right position, change pointer
				m_generalClassification.GetNext( nPos );
			}
		}

		// If not ready: the list doesn't contain any values bigger then the
		//  one we're handling (or it's empty at all), so we add the item
		//  at the end to our ordered list
		if( !nPos && !ready )
		{
			m_generalClassification.AddTail( aArr );
		}
	}	
}

void CClassification::ClearAll()
{
	m_firstClass = true;
	m_store.RemoveAll();
	m_generalClassification.RemoveAll();
	m_classification.RemoveAll();
}

bool CClassification::CalculateGeneralFromStage(CArrival *pArr)
{
	// First we adjust the arrival with some re-calculated values
	pArr->m_thousandth	= pArr->m_units % 1000;
	pArr->m_units		= ((int)(pArr->m_units / 1000))*1000;
	// Subtract bonus
	pArr->m_units		= pArr->m_units - pArr->m_bonus * 1000;
	// Add penalty
	if( pArr->m_penalty)
	pArr->m_units		= pArr->m_units + pArr->m_penalty * 1000;

	CArrival objStored;
	// We check whether this arrival should be handled, so we get rid
	//  of competitors which got out of the race during one of the days
	// It's handled when: it is already handled before or it's just the
	//  first classification at all
	if ( m_store.Lookup( pArr->m_staNo, objStored ) || m_firstClass )
	{
		// If this isn't the first classification, there is existing
		//  classification information in the store member, so we add
		//  it up with the new information before we handle it
		if( m_store.Lookup( pArr->m_staNo, objStored ) )
		{
			// Need to add new one to old one, not the other way around
			// (That's just not how the particular operator+ is designed)
			(*pArr) = objStored + (*pArr);
		}
		else
		{
			// The above only adds on 2nd and following,
			// so we do the initial sumRank here
			pArr->m_sumRank = pArr->m_rank;
		}
		return true;
	}
	else
		return false;
}

/*
{
	if(m_classification.GetCount())
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_HALFSTAGE, m_pDoc, columns, m_pDoc->StagesGet(nFS,nHS)->m_stageType );

		if( m_classification.GetHead().m_units == m_classification.GetTail().m_units )
		{
			CEventItem::RemovePublicationColumn( columns, PBC_GAP );
			CEventItem::RemovePublicationColumn( columns, PBC_NEWGAP );
		}

		// Figure out if bonus and penalty columns are required
		BOOL bBonus = false;
		BOOL bPenalty = false;
		POSITION nPos = m_classification.GetHeadPosition();
		while( nPos )
		{
			CArrival objArr = m_classification.GetNext( nPos );
			if( objArr.m_bonus )
				bBonus = true;
			if( objArr.m_penalty )
				bPenalty = true;
		}
		if( !bBonus )
			CEventItem::RemovePublicationColumn( columns, PBC_BONUSES );
		if( !bPenalty )
			CEventItem::RemovePublicationColumn( columns, PBC_PENALTY );

		// Make the html document
		CHtmlDoc objHtml( CEventItem( m_pDoc, TI_HALFSTAGE, nFS, nHS ) );

		// We provide the html document with the information
		// needed to calculate the time gaps
		CArrival objArrival;
		objArrival = m_classification.GetHead();
		objHtml.m_championTime = (objArrival.m_units/1000)*1000;

		objHtml.Header(m_pDoc->StagesGet(nFS,nHS)->m_idStage.GetNo());

		// For the actual contents, we just have to iterate the
		// classification we just made
		int n = 0;
		objHtml.Label( PP_FIRSTTEN );
		objHtml.Label( PP_FIRSTFIVE );

		CArrival objNextArrival;
		bool bDraw = false;
		objArrival.m_staNo = 0;
		nPos = m_classification.GetHeadPosition();
		while( nPos )
		{
			objNextArrival = m_classification.GetNext( nPos );
			if( objArrival.m_staNo != 0 )
			{
				// We write the competitor with his ranking to the html document
				objHtml.Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					( (objArrival.m_units/1000)==(objNextArrival.m_units/1000)
						||bDraw
						||m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) )
					&& !m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWNORMAL) );
				bDraw = (objArrival.m_units/1000)==(objNextArrival.m_units/1000);

				if( ++n==5  ) objHtml.LabelEnd( PP_FIRSTFIVE );
				if(   n==10 ) objHtml.LabelEnd( PP_FIRSTTEN  );
			}
			objArrival = objNextArrival;
		}
		if( objArrival.m_staNo != 0 )
		{
			// We write the competitor with his ranking to the html document
			objHtml.Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
				( bDraw
					||!m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) )
				&& !m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWNORMAL) );
		}

		// We make a list of competitors who were behind the deadline
		CString czCutOff;
		int nNumberStarters, nNumberDroppedOut = 0, nNumberCutOff = 0;

		// Make a temporarely new classification
		// for the riders that were out of the time limit
		CClassification tempcutoff(m_pDoc);
		CArrivalList* parr = &m_pDoc->StagesGet(nFS,nHS)->m_arrival;

		DWORD nState = 0;
		while( parr->IterateSortedCut( nState, objArrival ) )
			tempcutoff.AddCompetitor( objArrival );

		// Now print it
		nPos = tempcutoff.m_classification.GetHeadPosition();
		while( nPos )
		{
			objArrival = tempcutoff.m_classification.GetNext(nPos);
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_CUTOFFS) )
			{
				if( !czCutOff.GetLength() )
					objHtml.SayText( columns, AssembleStr( TEXT("FootCutOff"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				objHtml.Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			TCHAR czBuffer[10];
			_itot( objArrival.m_staNo, czBuffer, 10 );
			if( czCutOff.GetLength() ) czCutOff += ", ";
			czCutOff += czBuffer;
			nNumberCutOff++;
		}

		// We make a list of competitors who dropped out
		CString czDroppedOut;

		if( m_pDoc->StagesGetPrev(nFS,nHS) )
		{
			DWORD nState = 0;
			while( m_pDoc->StagesGetPrev(nFS,nHS)->m_arrival.IterateSorted( nState, objArrival ) )
			{
				if( !m_pDoc->StagesGet(nFS,nHS)->m_arrival.Exist( objArrival.m_staNo )
					&& !m_pDoc->StagesGet(nFS,nHS)->m_signOuts.Exist( objArrival.m_staNo ) )
				{
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_DROPOUTS) )
					{
						if( !czDroppedOut.GetLength() )
							objHtml.SayText( columns, AssembleStr( TEXT("FootDroppOut"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						objHtml.Competitor( columns, objArrival.m_staNo );
					}

					TCHAR czBuffer[10];
					_itot( objArrival.m_staNo, czBuffer, 10 );
					if( czDroppedOut.GetLength() ) czDroppedOut += ", ";
					czDroppedOut += czBuffer;
					nNumberDroppedOut++;
				}
			}

			nNumberStarters = m_pDoc->StagesGetPrev(nFS,nHS)->m_arrival.GetCount();
			nNumberStarters -= m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount();
		}
		else
		{
			CCompetitor objCompetitor;
			for ( int i=1, nSkipMap=1;
					i<=m_pDoc->CompetitorsCount(); i++, nSkipMap++)
			{
				while ( !m_pDoc->CompetitorsExist( nSkipMap ) )
					nSkipMap++ ;
				objCompetitor = m_pDoc->CompetitorsGet( nSkipMap );

				if( !m_pDoc->StagesGet(nFS,nHS)->m_arrival.Exist( objCompetitor.m_staNo )
					&& !m_pDoc->StagesGet(nFS,nHS)->m_signOuts.Exist( objCompetitor.m_staNo ) )
				{
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_DROPOUTS) )
					{
						if( !czDroppedOut.GetLength() )
							objHtml.SayText( columns, AssembleStr( TEXT("FootDroppOut"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						objHtml.Competitor( columns, objCompetitor.m_staNo );
					}

					TCHAR czBuffer[10];
					_itot( objCompetitor.m_staNo, czBuffer, 10 );
					if( czDroppedOut.GetLength() ) czDroppedOut += ", ";
					czDroppedOut += czBuffer;
					nNumberDroppedOut++;
				}
			}

			nNumberStarters = m_pDoc->CompetitorsCount();
			nNumberStarters -= m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount();
		}

		if( !czCutOff.GetLength() ) czCutOff = "--";
		if( nNumberCutOff>5 )
		{
			TCHAR czBuffer[10];
			_itot( nNumberCutOff, czBuffer, 10 );
			czCutOff += " (="+CString(czBuffer)+")";
		}
		if( !czDroppedOut.GetLength() ) czDroppedOut = "--";
		if( nNumberDroppedOut>5 )
		{
			TCHAR czBuffer[10];
			_itot( nNumberDroppedOut, czBuffer, 10 );
			czDroppedOut += " (="+CString(czBuffer)+")";
		}
		int nNumberLeft = nNumberStarters - nNumberDroppedOut - nNumberCutOff;

		// And we finish the document
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_SIGNOUTS) )
			objHtml.Footer( columns, &m_pDoc->StagesGet(nFS,nHS)->m_signOuts, m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount(), nNumberStarters, nNumberLeft, czDroppedOut, czCutOff );
		else
			objHtml.Footer( columns, NULL, m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount(), nNumberStarters, nNumberLeft, czDroppedOut, czCutOff );
		objHtml.Finish();
	}
	else
		CHtmlDoc::MakeDummy(
			CEventItem( m_pDoc, TI_HALFSTAGE, nFS, nHS ),
			m_pDoc->StagesGet(nFS,nHS)->m_idStage.GetNo() );
}
*/

void CClassification::PublishClass(int nFS, int nHS)
{
	if(m_classification.GetCount())
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_HALFSTAGE, m_pDoc, columns, m_pDoc->StagesGet(nFS,nHS)->m_stageType );

		if( m_classification.GetHead().m_units == m_classification.GetTail().m_units )
		{
			CEventItem::RemovePublicationColumn( columns, PBC_GAP );
			CEventItem::RemovePublicationColumn( columns, PBC_NEWGAP );
		}

		// Figure out if bonus and penalty columns are required
		BOOL bBonus = false;
		BOOL bPenalty = false;
		POSITION nPos = m_classification.GetHeadPosition();
		while( nPos )
		{
			CArrival objArr = m_classification.GetNext( nPos );
			if( objArr.m_bonus )
				bBonus = true;
			if( objArr.m_penalty )
				bPenalty = true;
		}
		if( !bBonus )
			CEventItem::RemovePublicationColumn( columns, PBC_BONUSES );
		if( !bPenalty )
			CEventItem::RemovePublicationColumn( columns, PBC_PENALTY );

		// Make the html document
		CHtmlDoc* pMask1 = NULL;
		CHtmlDoc* pMask2 = NULL;
		CHtmlDoc* pMask3 = NULL;
		CHtmlDoc* pMask4 = NULL;
		CHtmlDoc* pMask5 = NULL;
		CHtmlDoc* pMask6 = NULL;
		CHtmlDoc* pMask7 = NULL;
		CHtmlDoc* pMask8 = NULL;
		CHtmlDoc* pMask9 = NULL;
		CHtmlDoc* pMask10 = NULL;

		// Make the html document
		CHtmlDoc objHtml( CEventItem( m_pDoc, TI_HALFSTAGE, nFS, nHS ) );

		// We provide the html document with the information
		// needed to calculate the time gaps
		CArrival objArrival;
		objArrival = m_classification.GetHead();
		objHtml.m_championTime = (objArrival.m_units/1000)*1000;

		objHtml.Header(m_pDoc->StagesGet(nFS,nHS)->m_idStage.GetNo());

		// For the actual contents, we just have to iterate the
		// classification we just made
		objHtml.Label( PP_FIRSTTEN );
		objHtml.Label( PP_FIRSTFIVE );

		// This is quite elaborate: stage classifications can have gaps and ex
		// equos, however for masks we will count our own rankings, and only
		// detect doubles
		int nPreviousRank = 0;
		int nAll, nMask1 = 0, nMask2 = 0, nMask3 = 0, nMask4 = 0, nMask5 = 0,
			nMask6 = 0, nMask7 = 0, nMask8 = 0, nMask9 = 0, nMask10 = 0; // Provide correct rankings for every printed arrival

		int n = 0;
		CArrival objNextArrival;
		bool bDraw = false;
		objArrival.m_staNo = 0;
		nPos = m_classification.GetHeadPosition();
		while( nPos )
		{
			objNextArrival = m_classification.GetNext( nPos );
			if( objArrival.m_staNo != 0 )
			{
				nAll = objArrival.m_rank;
				// We write the competitor with his ranking to the html document
				objHtml.Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					( (objArrival.m_units/1000)==(objNextArrival.m_units/1000)
						||bDraw
						||m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) )
					&& !m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWNORMAL) );
				bDraw = (objArrival.m_units/1000)==(objNextArrival.m_units/1000);

				if( ++n==5  ) objHtml.LabelEnd( PP_FIRSTFIVE );
				if(   n==10 ) objHtml.LabelEnd( PP_FIRSTTEN  );

				// Mask 1
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask1 )
				{
					if( !pMask1 )
					{
						pMask1 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK1STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask1->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask1->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask1stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask1++;
					}
					objArrival.m_rank = nMask1;
					// We write the competitor with his ranking to the html document
					pMask1->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 2
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask2 )
				{
					if( !pMask2 )
					{
						pMask2 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK2STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask2->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask2->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask2stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask2++;
					}
					objArrival.m_rank = nMask2;
					// We write the competitor with his ranking to the html document
					pMask2->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 3
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask3 )
				{
					if( !pMask3 )
					{
						pMask3 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK3STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask3->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask3->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask3stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask3++;
					}
					objArrival.m_rank = nMask3;
					// We write the competitor with his ranking to the html document
					pMask3->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 4
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask4 )
				{
					if( !pMask4 )
					{
						pMask4 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK4STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask4->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask4->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask4stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask4++;
					}
					objArrival.m_rank = nMask4;
					// We write the competitor with his ranking to the html document
					pMask4->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 5
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask5 )
				{
					if( !pMask5 )
					{
						pMask5 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK5STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask5->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask5->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask5stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask5++;
					}
					objArrival.m_rank = nMask5;
					// We write the competitor with his ranking to the html document
					pMask5->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 6
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask6 )
				{
					if( !pMask6 )
					{
						pMask6 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK6STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask6->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask6->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask6stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask6++;
					}
					objArrival.m_rank = nMask6;
					// We write the competitor with his ranking to the html document
					pMask6->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 7
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask7 )
				{
					if( !pMask7 )
					{
						pMask7 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK7STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask7->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask7->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask7stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask7++;
					}
					objArrival.m_rank = nMask7;
					// We write the competitor with his ranking to the html document
					pMask7->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 8
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask8 )
				{
					if( !pMask8 )
					{
						pMask8 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK8STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask8->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask8->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask8stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask8++;
					}
					objArrival.m_rank = nMask8;
					// We write the competitor with his ranking to the html document
					pMask8->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 9
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask9 )
				{
					if( !pMask9 )
					{
						pMask9 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK9STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask9->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask9->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask9stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask9++;
					}
					objArrival.m_rank = nMask9;
					// We write the competitor with his ranking to the html document
					pMask9->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}
				// Mask 10
				if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10)
					&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask10 )
				{
					if( !pMask10 )
					{
						pMask10 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK10STAGE, nFS, nHS ) );
						// We provide the html document with the information
						// needed to calculate the time gaps...
						pMask10->m_championTime = (objArrival.m_units/1000)*1000;
						// ...and to make the headers
						pMask10->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask10stage.GetNo());
					}
					// We calculate the new rank; this way ex equos still exist
					if( nPreviousRank!=nAll )
					{
						nMask10++;
					}
					objArrival.m_rank = nMask10;
					// We write the competitor with his ranking to the html document
					pMask10->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
						m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
				}

				nPreviousRank = nAll;
			}
			objArrival = objNextArrival;
		}
		if( objArrival.m_staNo != 0 )
		{
			// This is the last competitor
			nAll = objArrival.m_rank;
			// We write the competitor with his ranking to the html document
			objHtml.Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
				( bDraw
					||m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) )
				&& !m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWNORMAL) );

			// Following is a blunt copy of above!!!
			// It fixes the last competitor to miss from the masked stage classifications
			// Mask 1
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask1 )
			{
				if( !pMask1 )
				{
					pMask1 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK1STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask1->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask1->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask1stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask1++;
				}
				objArrival.m_rank = nMask1;
				// We write the competitor with his ranking to the html document
				pMask1->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 2
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask2 )
			{
				if( !pMask2 )
				{
					pMask2 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK2STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask2->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask2->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask2stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask2++;
				}
				objArrival.m_rank = nMask2;
				// We write the competitor with his ranking to the html document
				pMask2->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 3
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask3 )
			{
				if( !pMask3 )
				{
					pMask3 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK3STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask3->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask3->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask3stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask3++;
				}
				objArrival.m_rank = nMask3;
				// We write the competitor with his ranking to the html document
				pMask3->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 4
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask4 )
			{
				if( !pMask4 )
				{
					pMask4 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK4STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask4->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask4->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask4stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask4++;
				}
				objArrival.m_rank = nMask4;
				// We write the competitor with his ranking to the html document
				pMask4->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 5
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask5 )
			{
				if( !pMask5 )
				{
					pMask5 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK5STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask5->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask5->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask5stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask5++;
				}
				objArrival.m_rank = nMask5;
				// We write the competitor with his ranking to the html document
				pMask5->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 6
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask6 )
			{
				if( !pMask6 )
				{
					pMask6 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK6STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask6->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask6->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask6stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask6++;
				}
				objArrival.m_rank = nMask6;
				// We write the competitor with his ranking to the html document
				pMask6->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 7
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask7 )
			{
				if( !pMask7 )
				{
					pMask7 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK7STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask7->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask7->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask7stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask7++;
				}
				objArrival.m_rank = nMask7;
				// We write the competitor with his ranking to the html document
				pMask7->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 8
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask8 )
			{
				if( !pMask8 )
				{
					pMask8 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK8STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask8->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask8->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask8stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask8++;
				}
				objArrival.m_rank = nMask8;
				// We write the competitor with his ranking to the html document
				pMask8->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 9
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask9 )
			{
				if( !pMask9 )
				{
					pMask9 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK9STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask9->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask9->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask9stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask9++;
				}
				objArrival.m_rank = nMask9;
				// We write the competitor with his ranking to the html document
				pMask9->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
			// Mask 10
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10)
				&& m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask10 )
			{
				if( !pMask10 )
				{
					pMask10 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK10STAGE, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask10->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask10->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask10stage.GetNo());
				}
				// We calculate the new rank; this way ex equos still exist
				if( nPreviousRank!=nAll )
				{
					nMask10++;
				}
				objArrival.m_rank = nMask10;
				// We write the competitor with his ranking to the html document
				pMask10->Competitor( columns, objArrival.m_staNo, &objArrival, NULL,
					m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) );
			}
		}

		// We make a list of competitors who were behind the deadline
		CString czCutOff;
		int nNumberStarters, nNumberDroppedOut = 0, nNumberCutOff = 0;

		// Make a temporarely new classification
		// for the riders that were out of the time limit
		CClassification tempcutoff(m_pDoc);
		CArrivalList* parr = &m_pDoc->StagesGet(nFS,nHS)->m_arrival;

		DWORD nState = 0;
		while( parr->IterateSortedCut( nState, objArrival ) )
			tempcutoff.AddCompetitor( objArrival );

		// Now print it
		nPos = tempcutoff.m_classification.GetHeadPosition();
		while( nPos )
		{
			objArrival = tempcutoff.m_classification.GetNext(nPos);
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_CUTOFFS) )
			{
				if( !czCutOff.GetLength() )
					objHtml.SayText( columns, AssembleStr( TEXT("FootCutOff"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				objHtml.Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			TCHAR czBuffer[10];
			_itot( objArrival.m_staNo, czBuffer, 10 );
			if( czCutOff.GetLength() ) czCutOff += ", ";
			czCutOff += czBuffer;
			nNumberCutOff++;
		}

		// We make a list of competitors who dropped out
		CString czDroppedOut;

		if( m_pDoc->StagesGetPrev(nFS,nHS) )
		{
			DWORD nState = 0;
			while( m_pDoc->StagesGetPrev(nFS,nHS)->m_arrival.IterateSorted( nState, objArrival ) )
			{
				if( !m_pDoc->StagesGet(nFS,nHS)->m_arrival.Exist( objArrival.m_staNo )
					&& !m_pDoc->StagesGet(nFS,nHS)->m_signOuts.Exist( objArrival.m_staNo ) )
				{
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_DROPOUTS) )
					{
						if( !czDroppedOut.GetLength() )
							objHtml.SayText( columns, AssembleStr( TEXT("FootDroppOut"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						objHtml.Competitor( columns, objArrival.m_staNo );
					}

					TCHAR czBuffer[10];
					_itot( objArrival.m_staNo, czBuffer, 10 );
					if( czDroppedOut.GetLength() ) czDroppedOut += ", ";
					czDroppedOut += czBuffer;
					nNumberDroppedOut++;
				}
			}

			nNumberStarters = m_pDoc->StagesGetPrev(nFS,nHS)->m_arrival.GetCount();
			nNumberStarters -= m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount();
		}
		else
		{
			CCompetitor objCompetitor;
			for ( int i=1, nSkipMap=1;
					i<=m_pDoc->CompetitorsCount(); i++, nSkipMap++)
			{
				while ( !m_pDoc->CompetitorsExist( nSkipMap ) )
					nSkipMap++ ;
				objCompetitor = m_pDoc->CompetitorsGet( nSkipMap );

				if( !m_pDoc->StagesGet(nFS,nHS)->m_arrival.Exist( objCompetitor.m_staNo )
					&& !m_pDoc->StagesGet(nFS,nHS)->m_signOuts.Exist( objCompetitor.m_staNo ) )
				{
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_DROPOUTS) )
					{
						if( !czDroppedOut.GetLength() )
							objHtml.SayText( columns, AssembleStr( TEXT("FootDroppOut"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
						objHtml.Competitor( columns, objCompetitor.m_staNo );
					}

					TCHAR czBuffer[10];
					_itot( objCompetitor.m_staNo, czBuffer, 10 );
					if( czDroppedOut.GetLength() ) czDroppedOut += ", ";
					czDroppedOut += czBuffer;
					nNumberDroppedOut++;
				}
			}

			nNumberStarters = m_pDoc->CompetitorsCount();
			nNumberStarters -= m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount();
		}

		if( !czCutOff.GetLength() ) czCutOff = "--";
		if( nNumberCutOff>5 )
		{
			TCHAR czBuffer[10];
			_itot( nNumberCutOff, czBuffer, 10 );
			czCutOff += " (="+CString(czBuffer)+")";
		}
		if( !czDroppedOut.GetLength() ) czDroppedOut = "--";
		if( nNumberDroppedOut>5 )
		{
			TCHAR czBuffer[10];
			_itot( nNumberDroppedOut, czBuffer, 10 );
			czDroppedOut += " (="+CString(czBuffer)+")";
		}
		int nNumberLeft = nNumberStarters - nNumberDroppedOut - nNumberCutOff;

		// And we finish the document
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_SIGNOUTS) )
			objHtml.Footer( columns, &m_pDoc->StagesGet(nFS,nHS)->m_signOuts, m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount(), nNumberStarters, nNumberLeft, czDroppedOut, czCutOff );
		else
			objHtml.Footer( columns, NULL, m_pDoc->StagesGet(nFS,nHS)->m_signOuts.GetCount(), nNumberStarters, nNumberLeft, czDroppedOut, czCutOff );
		objHtml.Finish();
		// And we finish the documents
		if( pMask1 )
		{
			pMask1->Footer(columns);
			pMask1->Finish();
			delete pMask1;
		}
		if( pMask2 )
		{
			pMask2->Footer(columns);
			pMask2->Finish();
			delete pMask2;
		}
		if( pMask3 )
		{
			pMask3->Footer(columns);
			pMask3->Finish();
			delete pMask3;
		}
		if( pMask4 )
		{
			pMask4->Footer(columns);
			pMask4->Finish();
			delete pMask4;
		}
		if( pMask5 )
		{
			pMask5->Footer(columns);
			pMask5->Finish();
			delete pMask5;
		}
		if( pMask6 )
		{
			pMask6->Footer(columns);
			pMask6->Finish();
			delete pMask6;
		}
		if( pMask7 )
		{
			pMask7->Footer(columns);
			pMask7->Finish();
			delete pMask7;
		}
		if( pMask8 )
		{
			pMask8->Footer(columns);
			pMask8->Finish();
			delete pMask8;
		}
		if( pMask9 )
		{
			pMask9->Footer(columns);
			pMask9->Finish();
			delete pMask9;
		}
		if( pMask10 )
		{
			pMask10->Footer(columns);
			pMask10->Finish();
			delete pMask10;
		}
	}
	else
		CHtmlDoc::MakeDummy(
			CEventItem( m_pDoc, TI_HALFSTAGE, nFS, nHS ),
			m_pDoc->StagesGet(nFS,nHS)->m_idStage.GetNo() );
}

void CClassification::PublishGeneral(int nFS, int nHS, bool bGeneral, bool bMask1, bool bMask2, bool bMask3, bool bMask4, bool bMask5, bool bMask6, bool bMask7, bool bMask8, bool bMask9, bool bMask10 )
{
	if(m_generalClassification.GetCount())
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_CLASSGENERAL, m_pDoc, columns );

		// Make the html document
		CHtmlDoc* pAll = NULL;
		CHtmlDoc* pAllSorted = NULL;
		CHtmlDoc* pMask1 = NULL;
		CHtmlDoc* pMask2 = NULL;
		CHtmlDoc* pMask3 = NULL;
		CHtmlDoc* pMask4 = NULL;
		CHtmlDoc* pMask5 = NULL;
		CHtmlDoc* pMask6 = NULL;
		CHtmlDoc* pMask7 = NULL;
		CHtmlDoc* pMask8 = NULL;
		CHtmlDoc* pMask9 = NULL;
		CHtmlDoc* pMask10 = NULL;

		CArrivalList helperforstanosorted;
		
		// For the actual contents, we just have to iterate the
		// classification we just made
		POSITION nPos = m_generalClassification.GetHeadPosition();
		int n = 0;
		int nAll = 1, nMask1 = 1, nMask2 = 1, nMask3 = 1, nMask4 = 1, nMask5 = 1,
			nMask6 = 1, nMask7 = 1, nMask8 = 1, nMask9 = 1, nMask10 = 1; // Provide correct rankings for every printed arrival
		while( nPos )
		{
			CArrival objArrival = m_generalClassification.GetNext( nPos );

			// Main classification without masking
			if( bGeneral )
			{
				if( !pAll )
				{
					pAll = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSGENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pAll->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pAll->Header(m_pDoc->StagesGet(nFS,nHS)->m_idGeneral.GetNo());

					pAll->Label( PP_FIRSTTEN );
					pAll->Label( PP_FIRSTFIVE );
				}
				if( !pAllSorted && m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_GENERATETSTANOSORTEDGENERAL))
				{
					pAllSorted = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSSTANOSORTEDGENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pAllSorted->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pAllSorted->Header(m_pDoc->StagesGet(nFS,nHS)->m_idGeneralStaNoSorted.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nAll++;
				helperforstanosorted.Insert(objArrival);
				pAll->Competitor( columns, objArrival.m_staNo, &objArrival );

				if( ++n==5  ) pAll->LabelEnd( PP_FIRSTFIVE );
				if(   n==10 ) pAll->LabelEnd( PP_FIRSTTEN  );
			}

			// Mask 1
			if( bMask1 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask1 )
			{
				if( !pMask1 )
				{
					pMask1 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK1GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask1->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask1->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask1gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask1++;
				pMask1->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 2
			if( bMask2 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask2 )
			{
				if( !pMask2 )
				{
					pMask2 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK2GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask2->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask2->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask2gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask2++;
				pMask2->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 3
			if( bMask3 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask3 ) 
			{
				if( !pMask3 )
				{
					pMask3 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK3GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask3->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask3->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask3gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask3++;
				pMask3->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 4
			if( bMask4 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask4 )
			{
				if( !pMask4 )
				{
					pMask4 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK4GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask4->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask4->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask4gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask4++;
				pMask4->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 5
			if( bMask5 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask5 )
			{
				if( !pMask5 )
				{
					pMask5 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK5GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask5->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask5->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask5gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask5++;
				pMask5->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 6
			if( bMask6 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask6 )
			{
				if( !pMask6 )
				{
					pMask6 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK6GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask6->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask6->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask6gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask6++;
				pMask6->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 7
			if( bMask7 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask7 )
			{
				if( !pMask7 )
				{
					pMask7 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK7GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask7->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask7->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask7gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask7++;
				pMask7->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 8
			if( bMask8 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask8 )
			{
				if( !pMask8 )
				{
					pMask8 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK8GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask8->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask8->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask8gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask8++;
				pMask8->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 9
			if( bMask9 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask9 )
			{
				if( !pMask9 )
				{
					pMask9 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK9GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask9->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask9->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask9gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask9++;
				pMask9->Competitor( columns, objArrival.m_staNo, &objArrival );
			}

			// Mask 10
			if( bMask10 && m_pDoc->CompetitorsGet(objArrival.m_staNo).m_mask10 )
			{
				if( !pMask10 )
				{
					pMask10 = new CHtmlDoc( CEventItem( m_pDoc, TI_CLASSMASK10GENERAL, nFS, nHS ) );
					// We provide the html document with the information
					// needed to calculate the time gaps...
					pMask10->m_championTime = (objArrival.m_units/1000)*1000;
					// ...and to make the headers
					pMask10->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMask10gen.GetNo());
				}
				// We write the competitor with his ranking to the html document
				objArrival.m_rank = nMask10++;
				pMask10->Competitor( columns, objArrival.m_staNo, &objArrival );
			}
		}

		if( pAllSorted )
		{
			PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
			CEventItem::GetPublicationColumns( TI_CLASSSTANOSORTEDGENERAL, m_pDoc, columns );
			
			CArrival objArrival;
 			DWORD nState = 0;
			while( helperforstanosorted.IterateSorted( nState, objArrival ) )
			{
				pAllSorted->Competitor( columns, objArrival.m_staNo, &objArrival );
			}
			pAllSorted->Footer(columns);
			pAllSorted->Finish();
			delete pAllSorted;
		}
		// And we finish the documents
		if( pAll )
		{
			pAll->Footer(columns);
			pAll->Finish();
			delete pAll;
		}
		if( pMask1 )
		{
			pMask1->Footer(columns);
			pMask1->Finish();
			delete pMask1;
		}
		if( pMask2 )
		{
			pMask2->Footer(columns);
			pMask2->Finish();
			delete pMask2;
		}
		if( pMask3 )
		{
			pMask3->Footer(columns);
			pMask3->Finish();
			delete pMask3;
		}
		if( pMask4 )
		{
			pMask4->Footer(columns);
			pMask4->Finish();
			delete pMask4;
		}
		if( pMask5 )
		{
			pMask5->Footer(columns);
			pMask5->Finish();
			delete pMask5;
		}
		if( pMask6 )
		{
			pMask6->Footer(columns);
			pMask6->Finish();
			delete pMask6;
		}
		if( pMask7 )
		{
			pMask7->Footer(columns);
			pMask7->Finish();
			delete pMask7;
		}
		if( pMask8 )
		{
			pMask8->Footer(columns);
			pMask8->Finish();
			delete pMask8;
		}
		if( pMask9 )
		{
			pMask9->Footer(columns);
			pMask9->Finish();
			delete pMask9;
		}
		if( pMask10 )
		{
			pMask10->Footer(columns);
			pMask10->Finish();
			delete pMask10;
		}
	}
	else
	{
		CHtmlDoc::MakeDummy(
			CEventItem( m_pDoc, TI_CLASSGENERAL, nFS, nHS ),
			m_pDoc->StagesGet(nFS,nHS)->m_idGeneral.GetNo() );
		if( bMask1 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK1STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask1stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK1GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask1gen.GetNo() );
		}
		if( bMask2 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK2STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask2stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK2GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask2gen.GetNo() );
		}
		if( bMask3 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK3STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask3stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK3GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask3gen.GetNo() );
		}
		if( bMask4 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK4STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask4stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK4GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask4gen.GetNo() );
		}
		if( bMask5 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK5STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask5stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK5GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask5gen.GetNo() );
		}
		if( bMask6 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK6STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask6stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK6GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask6gen.GetNo() );
		}
		if( bMask7 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK7STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask7stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK7GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask7gen.GetNo() );
		}
		if( bMask8 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK8STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask8stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK8GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask8gen.GetNo() );
		}
		if( bMask9 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK9STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask9stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK9GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask9gen.GetNo() );
		}
		if( bMask10 )
		{
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK10STAGE, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask10stage.GetNo() );
			CHtmlDoc::MakeDummy(
				CEventItem( m_pDoc, TI_CLASSMASK10GENERAL, nFS, nHS ),
				m_pDoc->StagesGet(nFS,nHS)->m_idMask10gen.GetNo() );
		}
	}
}

void CClassification::ScrambleForStartingOrder()
{
	CTeam* pPrevious = NULL;
	CTeam* pCurrent = NULL;

	// If required, we correct the list
	// This means we don't want to have to consecutive riders from the same team
	// This will always be solved by searching for the first competitor down in
	//  the list with an other team (CTeam*)

	// Iterate the whole list of arrivals in the general cl.
	
	POSITION nPos = m_generalClassification.GetHeadPosition();
	while( nPos )
	{
		POSITION nPosCurrent = nPos;

		// Get the arrival
		CArrival objArrival = m_generalClassification.GetNext( nPos );
		// Get the according competitor
		CCompetitor objComp;
		objComp = m_pDoc->CompetitorsGet( objArrival.m_staNo );

		// Store this competitor's team
		pCurrent = objComp.m_pTeam;

		// Compare this competitor's team to the previous one
		// Handle teamless riders by checking if the previous team pointer wasn't NULL
		if( (pCurrent==pPrevious) && pPrevious )
		{
			// Obviously whe have to put in another competitor at this place
			// which we have to look for, somewhere down in the list
			POSITION nPosLocal = nPos;
			// Ergo, we iterate the list, while:
			//  - we haven't found another team pointer
			//  - there are items left
			while( nPosLocal && (objComp.m_pTeam==pPrevious) )
			{
				// Just keep on getting the next
				objArrival = m_generalClassification.GetNext( nPosLocal );
				// And getting the according competitor in order to check the team
				objComp = m_pDoc->CompetitorsGet( objArrival.m_staNo );
			}

			// We got here, either because we ran out of items or have found a rider
			//  from a different team
			// We want to make sure that the latter is at least the case
			if( objComp.m_pTeam!=pPrevious )
			{
				// Check where in the list we were
				if( !nPosLocal )
					// At the end of the list: get ourselfes a pointer to the last item *)
					nPosLocal = m_generalClassification.GetTailPosition();
				else
					// Anywhere else in the list: get ourselfes a pointer to the previous item *)
					m_generalClassification.GetPrev( nPosLocal );
				// Note *):	The "GetNext" used makes our pointer always be one item too far
				//			Here we compensate for that

				// Remove the 'alternative item' we found at this spot
				m_generalClassification.RemoveAt( nPosLocal );
				// And insert it just BEFORE the "second item of the same team"
				//  with which all the troubles started
				m_generalClassification.InsertBefore( nPosCurrent, objArrival );
			}
		}
		// This one obviously gives us something to look back at during the next iteration
		pPrevious = pCurrent;
	}
}

CClassification::CClassification(CClassification &cl)
{
	*this = cl;
}

CClassification& CClassification::operator =(const CClassification & cl)
{
	POSITION nPos;

	m_classification.RemoveAll();
	nPos = cl.m_classification.GetHeadPosition();
	while( nPos )
		m_classification.AddTail( (CArrival&)cl.m_classification.GetNext( nPos ) );

	m_generalClassification.RemoveAll();
	nPos = cl.m_generalClassification.GetHeadPosition();
	while( nPos )
		m_generalClassification.AddTail( (CArrival&)cl.m_generalClassification.GetNext( nPos ) );

	m_store.RemoveAll();
	WORD nKey;
	CArrival arr;
	nPos = cl.m_store.GetStartPosition();
	while( nPos )
	{
		cl.m_store.GetNextAssoc( nPos, nKey, arr );
		m_store.SetAt( nKey, arr );
	}

	m_firstClass= cl.m_firstClass;
	m_pDoc		= cl.m_pDoc;

	return *this;
}
