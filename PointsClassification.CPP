// PointsClassification.cpp: implementation of the CPointsClassification class.
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

CPointsClassification::CPointsClassification(CStageRaceDoc* pDoc) : CSprintClassification( pDoc )
{

}

bool CPointsClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
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
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_POINTS_ONMOSTHIGHRANKINGS) ) // User can have changed the sort method by settings
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

					// Iterate through every half stage (so far) within every stage
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
		return InsertHereLastResort(objTest, objSubj);
	}
	return false;
}

void CPointsClassification::Publish(int nFS, int nHS)
{
	CHtmlDoc* pObjHtml = NULL;

	// Select the columns to print
	PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
	CEventItem::GetPublicationColumns( TI_POINTS, m_pDoc, columns );

	// Make the html document
	pObjHtml = new CHtmlDoc( CEventItem( m_pDoc, TI_POINTS, nFS, nHS) );

	// We provide the html document with the information
	// to make the headers
	pObjHtml->Header(m_pDoc->StagesGet(nFS,nHS)->m_idPoints.GetNo());

	// INTERMEDIATE CLASSIFICATION

	// For the actual contents, we just have to iterate the
	// points classification we just made
	POSITION nPos;
	nPos = m_classification.GetHeadPosition();
	while( nPos )
	{
		CArrival objArrival;
		objArrival = m_classification.GetNext( nPos );

		// We write the competitor with his ranking to the html document
		pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );
	}
	
	// GENERAL CLASSIFICATION
	pObjHtml->SayText( columns, AssembleStr( TEXT("TocGeneral"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
	// For the actual contents, we just have to iterate the
	// points general classification we just made
	nPos = m_generalClassification.GetHeadPosition();
	int nAll = 1; // Provide correct rankings for every printed arrival
	while( nPos )
	{
		CArrival objArrival = m_generalClassification.GetNext( nPos );

		// We write the competitor with his ranking to the html document
		objArrival.m_rank = nAll++;
		pObjHtml->Competitor( columns, objArrival.m_staNo, &objArrival );
	}

	pObjHtml->Footer(columns);
	pObjHtml->Finish();
	delete pObjHtml;
}
