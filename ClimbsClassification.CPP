// ClimbsClassification.cpp: implementation of the CClimbsClassification class.
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

CClimbsClassification::CClimbsClassification(CStageRaceDoc *pDoc) : CSprintClassification( pDoc )
{
}

CClimbsClassification::~CClimbsClassification()
{
}

bool CClimbsClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
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
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_CLIMB_ONMOSTHIGHRANKINGS) ) // User can have changed the sort method by settings
		{
			// Secondly test on the amount of best rankings

			int nCount = 0;
			do
			{
				// Start with the best (1st) rank
				int nPlace = 1;
				// Test every rank (1, 2, 3, ...) until a certain extend
				//  and see if our subject competitor is better then the reference
				while( nPlace <= ((CSettingsRanking*)m_pDoc->m_allsettings.GetSettings(SETT_RANKING))->m_maxDepthSprint )
				{
					int nScoreSubj = 0;
					int nScoreTest = 0;

					// Iterate through every stage
					for( int nStage = m_pDoc->StagesFullCount(); nStage; nStage-- )
					{
						// Iterate through every half stage within every stage
						for( int nHStage = m_pDoc->StagesGet( nStage )->CountHalfStages(); nHStage; nHStage-- )
						{
							CHalfStage* pHS;
							pHS = m_pDoc->StagesGet( nStage, nHStage );

							// Iterate through every climb classification within every half stage
							CArrivalList* pArrList;
							POSITION nPos1 = pHS->m_climbs.GetHeadPosition();
							POSITION nPos2 = pHS->m_climbsorder.GetHeadPosition();
							while( nPos1&&nPos2 )
							{
								pArrList = &pHS->m_climbs.GetNext( nPos1 );

								if( (pHS->m_climbsorder.GetNext( nPos2 )==nCount)
									|| !m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_CLIMB_DIFFCATEGORIES) )
								{
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
			while( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_CLIMB_DIFFCATEGORIES)
				&& ++nCount<=4 );
		}
		// Obviously, we still have a draw
		// (otherwise we would have returned by now)
		return InsertHereLastResort(objTest, objSubj);
	}
	return false;
}
