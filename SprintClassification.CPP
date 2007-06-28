// SprintClassification.cpp: implementation of the CSprintClassification class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Note that this class and file used to be named PointsClassification
// Changed as of 2003, 2, 0, 445
CSprintClassification::CSprintClassification(CStageRaceDoc *pDoc) : CClassification( pDoc )
{
	m_bUnofficial = false;
	m_nFS = 1;
	m_nHS = 1;
}

void CSprintClassification::AddCompetitor(CArrival &aArr, CClassification* pLastResort, int nFS, int nHS)
{
	m_nFS = nFS;
	m_nHS = nHS;
	m_pLastResort = pLastResort;
	ASSERT( pLastResort );

	CArrival objArr( aArr );	// We make sure that all these functions do NOT
								// mess up the data from the calling functions

	// the stage classification
	DoClass( objArr );
	// the general classification
	// while preventing not-finished competitors
		// The following arranges competitors that didn't arrive in the
		// stage to be excluded from this classification
		// This only done though, when the stage is actually arrived,
		// otherwise everyone is included
		if( nFS && nHS && m_pDoc->StagesGet( m_nFS, m_nHS )->m_arrival.GetCount() )
		{
			// Only insert when still competing during this stage
			if( m_pDoc->StagesGet( m_nFS, m_nHS )->m_arrival.Exist( aArr.m_staNo ) )
				DoGeneral( aArr );
		}
		else
		{
			DoGeneral( aArr );
			m_bUnofficial = true;
		}

//We do no longer call the base function
//	CClassification::AddCompetitor( aArr );
}

bool CSprintClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
{
	// This function is to decide how two arrivals relate to each other

	// objSubj is the arrival of which we want to know whether it is "smaller"
	// than the objSubj that was already in the list

	// The function returns true if the subject (objSubj) should be inserted
	// just "before" the test object, where "after" means further away from
	// the winner

	// First test on the points
	if( objTest.m_points < objSubj.m_points )
		return true;

	if( objTest.m_points == objSubj.m_points )
	{
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_SPRINT_ONMOSTHIGHRANKINGS) ) // User can have changed the sort method by settings
		{
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_SPRINT_INCLUDEFINISH) )
			{
				// Secondly test on the amount of best rankings within full stages

				// Start with the best (1st) rank
				int nPlace = 1;
				// Test every rank (1, 2, 3, ...) until a certain extend
				//  and see if our subject competitor is better then the reference
				while( nPlace <= ((CSettingsRanking*)m_pDoc->m_allsettings.GetSettings(SETT_RANKING))->m_maxDepthFinish )
				{
					int nScoreSubj = 0;
					int nScoreTest = 0;

					// Iterate through every stage so far backwards
					for( int nStage = m_nFS; nStage; nStage-- )
					{
						int nStartHS;
						if( nStage == m_nFS )
							nStartHS = m_nHS;
						else
							nStartHS = m_pDoc->StagesGet( nStage )->CountHalfStages();

						// Iterate through every half stage within every stage
						for( int nHStage = nStartHS; nHStage; nHStage-- )
						{
							CHalfStage* pHS;
							pHS = m_pDoc->StagesGet( nStage, nHStage );

							CArrivalList* pArrList;
							pArrList = &pHS->m_arrival;

							// If either the subject or test competitor has
							// this particular ranking, we increment its score
							if( pArrList->Exist( objSubj.m_staNo ) )
								if( pArrList->GetAt( objSubj.m_staNo ).m_rank == nPlace )
									nScoreSubj ++;

							if( pArrList->Exist( objTest.m_staNo ) )
								if( pArrList->GetAt( objTest.m_staNo ).m_rank == nPlace )
									nScoreTest ++;
						}
					}

					if( nScoreSubj>
						nScoreTest )
						return true;
					if( nScoreSubj<
						nScoreTest )
						return false;

					nPlace++;
				}
			}
			// Obviously, we still have a draw
			// (otherwise we would have returned by now)

			// Thirthly we test on the amount of best rankings within intermediate sprints
			{
				// Start with the best (1st) rank
				int nPlace = 1;
				// Test every rank (1, 2, 3, ...) until a certain extend
				//  and see if our subject competitor is better then the reference
				while( nPlace <= ((CSettingsRanking*)m_pDoc->m_allsettings.GetSettings(SETT_RANKING))->m_maxDepthSprint )
				{
					int nScoreSubj = 0;
					int nScoreTest = 0;

					// Iterate through every stage so far
					for( int nStage = m_nFS; nStage; nStage-- )
					{
						int nStartHS;
						if( nStage == m_nFS )
							nStartHS = m_nHS;
						else
							nStartHS = m_pDoc->StagesGet( nStage )->CountHalfStages();

						// Iterate through every half stage within every stage
						for( int nHStage = nStartHS; nHStage; nHStage-- )
						{
							CHalfStage* pHS;
							pHS = m_pDoc->StagesGet( nStage, nHStage );


							// Iterate through every points classification within every half stage
							CArrivalList* pArrList;
							POSITION nPos = pHS->m_sprints.GetHeadPosition();
							while( nPos )
							{
								pArrList = &pHS->m_sprints.GetNext( nPos );

								// If either the subject or test competitor has
								// this particular ranking, we increment its score
								if( pArrList->Exist( objSubj.m_staNo ) )
									if( pArrList->GetAt( objSubj.m_staNo ).m_rank == nPlace )
										nScoreSubj ++;

								if( pArrList->Exist( objTest.m_staNo ) )
									if( pArrList->GetAt( objTest.m_staNo ).m_rank == nPlace )
										nScoreTest ++;
							}
						}
					}

					if( nScoreSubj>
						nScoreTest )
						return true;
					if( nScoreSubj<
						nScoreTest )
						return false;

					nPlace++;
				}
			}//Just compounds
		}

		// Obviously, we still have a draw
		// (otherwise we would have returned by now)
		if( m_pDoc->m_allsettings.ValueGet(IDD_SETT_RANK_LASTRESORT_GENERAL_CL) )
			return InsertHereLastResort( objTest, objSubj );
		else
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_SPRINT_INCLUDEFINISH) )
				return InsertHereLastResort( objTest, objSubj );
			else
			{
				// Iterate through every stage backwards
				for( int nStage = m_nFS; nStage; nStage-- )
				{
					int nStartHS;
					if( nStage == m_nFS )
						nStartHS = m_nHS;
					else
						nStartHS = m_pDoc->StagesGet( nStage )->CountHalfStages();

					// Iterate through every half stage within every stage backwards
					for( int nHStage = nStartHS; nHStage; nHStage-- )
					{
						CHalfStage* pHS;
						pHS = m_pDoc->StagesGet( nStage, nHStage );

						CArrivalList* pArrList;
						// Iterate through every sprint classification within every half stage backwards
						POSITION nPos = pHS->m_sprints.GetTailPosition();
						while( nPos )
						{
							pArrList = &pHS->m_sprints.GetPrev( nPos );

							int nRankSubj = 0;
							int nRankTest = 0;

							if( pArrList->Exist( objSubj.m_staNo ) )
								nRankSubj = pArrList->GetAt( objSubj.m_staNo ).m_rank;

							if( pArrList->Exist( objTest.m_staNo ) )
								nRankTest = pArrList->GetAt( objTest.m_staNo ).m_rank;

							if( nRankSubj && !nRankTest )
								return true;

							if( !nRankSubj && nRankTest )
								return false;

							if( nRankTest && nRankSubj )
								return nRankSubj < nRankTest;
						}

					}
				}
			}
	}
	return false;
}

bool CSprintClassification::InsertHereLastResort(CArrival &objTest, CArrival &objSubj)
{
	// Choose a last resort
	CList<CArrival,CArrival&>* pList;
	if( m_pDoc->m_allsettings.ValueGet(IDD_SETT_RANK_LASTRESORT_STAGE_CL) )
		pList = &m_pLastResort->m_classification;
	else
		pList = &m_pLastResort->m_generalClassification;

	// Use it to find our test/subject
	POSITION nPos = pList->GetHeadPosition();
	while( nPos )
	{
		CArrival aTestValue;
		aTestValue = pList->GetNext( nPos );

		if( aTestValue.m_staNo == objSubj.m_staNo )
			return true;
		if( aTestValue.m_staNo == objTest.m_staNo )
			return false;
	}
	ASSERT(false);// THIS IS SOOOO BAD!
	return false;
}

bool CSprintClassification::CalculateGeneralFromStage(CArrival *pArr)
{
	// We iterate the stored values list to look for this particular
	//  competitor with results from the past
	CArrival aTestValue;
	if( m_store.Lookup( pArr->m_staNo, aTestValue ) )
	{
		// If it exists, we add the new points to it and remove it from 
		//  the ordered list, because it has probably changed its place
		//  due to the added points
		(*pArr) = (*pArr) + aTestValue;
		m_store.RemoveKey( pArr->m_staNo );
	}

	// This always succeeds, because if we don't find an old record, we still
	// wanna store the current/new one
	return true;
}

void CSprintClassification::FinishClassification()
{
	// We iterate the stored values list to look for competitors
	// from previous sprints/stages which have not been ranked now
	while( !m_store.IsEmpty() )
	{
		POSITION nPos = m_store.GetStartPosition();

		CArrival aArr;
		m_store.GetNextAssoc( nPos, aArr.m_staNo, aArr );

		m_store.RemoveKey( aArr.m_staNo );

		// The following arranges competitors that didn't arrive in the
		// stage to be excluded from this classification
		// This only done though, when the stage is actually arrived,
		// otherwise everyone is included
		if( m_pDoc->StagesGet( m_nFS, m_nHS )->m_arrival.GetCount() )
		{
			// Only insert when still competing during this stage
			if( m_pDoc->StagesGet( m_nFS, m_nHS )->m_arrival.Exist( aArr.m_staNo )
					&& (!m_pDoc->StagesGet( m_nFS, m_nHS )->m_arrival.IsTimeCutted( aArr.m_staNo )
					|| m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_EXCLUDETIMECUTOFFFROMSPRINTS)) )
				DoGeneral( aArr );
		}
		else
		{
			DoGeneral( aArr );
			m_bUnofficial = true;
		}
	}

}

bool CSprintClassification::IsOfficial()
{
	return !m_bUnofficial;
}

bool CSprintClassification::IsUnOfficial()
{
	return m_bUnofficial;
}

