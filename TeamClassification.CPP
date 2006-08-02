// TeamClassification.cpp: implementation of the CTeamClassification class.
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

CTeamClassification::CTeamClassification(CStageRaceDoc *pDoc) : CClassification( pDoc )
{
	// Fill the store with all available teams
	POSITION nPos = pDoc->TeamsGetStartPosition();
	while( nPos )
	{
		CString czKey;
		CTeam* pValue;
		pDoc->TeamsIterate( nPos, pValue );

		CArrival objArrival;
		objArrival.m_pTeam = pValue;
		objArrival.m_units = 0;
		objArrival.m_rank = 0;
		objArrival.m_points = 0;
		m_store.SetAt( pValue, objArrival );
	}
}

void CTeamClassification::LoadClassification(CClassification* pClass, bool bOneForTeamsClass /*= false*/)
{
	// Teams classification
	//
	// Per stage:
	//  1. Sum of times of first three competitors, without bonification times
	// (2. Sum of rankings of first three competitors)*
	//  3. Ranking of first/last* competitor of three
	//
	// General:
	//  1. Sum of times of teams classifications per stage
	// (2. Sum of rankings of teams in teams classifications per stage)
	//  3. Ranking of last stage teams classification
	//
	// * = setting

	// We handle all the teams once
	POSITION nPos1 = m_store.GetStartPosition();
	while( nPos1 )
	{
		// We make an object for the team we handle
		CArrival objSubjTeam;

		// We fill the object with the current team to handle
		m_store.GetNextAssoc( nPos1, objSubjTeam.m_pTeam, objSubjTeam );

		// We clear the object in order to take only this stage's times etc.
		objSubjTeam.m_rank = 0;
		objSubjTeam.m_units = 0;
		objSubjTeam.m_points = 0;

		// We set the number of competitors per team to handle
		int nCompsLeft = min( 6, max( 2, ((CSettingsRanking*)m_pDoc->m_allsettings.GetSettings(SETT_RANKING))->m_bunchSize ) );

		// We are gonna store the involved competitors for printing only
		CClassification* pBunch = new CClassification(m_pDoc);

		// We skip through the classification until we have enough competitors of the team handled
		POSITION nPos2 = pClass->m_classification.GetHeadPosition();
		while( nPos2 && nCompsLeft )
		{
			// We make an object for the competitor we handle
			CArrival objSubjArrival;

			// We fill the object with the current competitor to handle
			objSubjArrival = pClass->m_classification.GetNext( nPos2 );

// Temporarely because we're loosing m_pTeam data somewhere down the road
CCompetitor objTempComp;
objTempComp = m_pDoc->CompetitorsGet( objSubjArrival.m_staNo );
objSubjArrival.m_pTeam = objTempComp.m_pTeam;

			// If the competitor retrieved from the classification matches our
			// team, we handle him
			if( objSubjTeam.m_pTeam == objSubjArrival.m_pTeam )
			{
				// If this is the deciding competitor
				// or we are supposed to take all (so not only the deciding competitor)
				if( (objSubjTeam.m_rank==0 && m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_DECIDING_FIRST)) ||
					(nCompsLeft==1		   && m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_DECIDING_LAST) ) ||
					!bOneForTeamsClass )
				{
					// We store its time
					objSubjTeam.m_units += (objSubjArrival.m_units / 1000)*1000;
					// We store the rest of its information for printing only
					pBunch->AddCompetitor(objSubjArrival);

					// If the user selected differentiation on sum of rankings...
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS) )
						// ...we add his ranking to points field of the team
						// in order to differentiate on sum of rankings, later
						objSubjTeam.m_points += objSubjArrival.m_rank;

					// If this is the 'deciding' competitor, we store his rank in
					// the team's rank field, in order to do last resort for differentiation
					if( !objSubjTeam.m_rank || m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_DECIDING_LAST) )
						objSubjTeam.m_rank = objSubjArrival.m_rank;
				}

				// Well, that was another competitor for the team handled...
				nCompsLeft--;
			}
		}

		// If a sufficient number of competitors handled...
		if( nCompsLeft==0 )
		{
			// ...this team is still 'on' for classifications
			objSubjTeam.m_pBunch = pBunch;
			// Add it to today's classification
			DoClass( objSubjTeam );
		}
		if( pBunch )
		{
			delete pBunch;
			objSubjTeam.m_pBunch = NULL;
		}
	}
	// Now we have a complete stage classification

	int nRank = 1;
	// We handle all the teams of the stage classification once
	POSITION nPos = m_classification.GetHeadPosition();
	while( nPos )
	{
		// We make objects for the team we handle
		CArrival objTeamStage, objTeamGeneral;

		// We fill the 'stage' object with the current team to handle
		objTeamStage = m_classification.GetNext( nPos );

		// We look up that current team in the stored 'previous' general classification
		m_store.Lookup( objTeamStage.m_pTeam, objTeamGeneral );

		// We add the stage's time to the general time
		objTeamGeneral.m_units += objTeamStage.m_units;
		// We add the stage's ranking to the general sum of rankings
		objTeamGeneral.m_points += nRank++;
		// We store the best individual ranking for the last resort
		POSITION nPosLastResort = pClass->m_generalClassification.GetHeadPosition();
		objTeamGeneral.m_rank = 0;
		while( nPosLastResort )
		{
			CArrival teammember =
				pClass->m_generalClassification.GetNext(nPosLastResort);

// Temporarely because we're loosing m_pTeam data somewhere down the road
CCompetitor objTempComp;
objTempComp = m_pDoc->CompetitorsGet( teammember.m_staNo );
teammember.m_pTeam = objTempComp.m_pTeam;

			objTeamGeneral.m_rank++;
			if( teammember.m_pTeam == objTeamGeneral.m_pTeam )
				break;
		}

		// Add it to the general classification
		DoGeneral( objTeamGeneral );
	}
}

bool CTeamClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
{
	if( bRankOnly )
	{
		// ONLY USED FOR STAGE IMPLEMENTATION
		if( objTest.m_units > objSubj.m_units )
			return true;
		if( objTest.m_units == objSubj.m_units )
		{
			if( (objTest.m_points>objSubj.m_points)
				&& m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS) )
				return true;
			if( (objTest.m_points == objSubj.m_points)
				|| !m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS) )
			{
				if( objTest.m_rank > objSubj.m_rank )
					return true;
			}
		}
	}
	else
	{
		// ONLY USED FOR GENERAL IMPLEMENTATION
		if( objTest.m_units > objSubj.m_units )
			return true;
		if( objTest.m_units == objSubj.m_units )
		{
			if( (objTest.m_points>objSubj.m_points)
				&& m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS) )
				return true;
			if( (objTest.m_points == objSubj.m_points)
				|| !m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS) )
			{
				if( objTest.m_rank > objSubj.m_rank )
					return true;
			}
		}
	}
	return false;
}

void CTeamClassification::StoreClassification()
{
	// Function to be called after every calculated stage

	// It copies the current general classification to m_store,
	// in order to be used for the next stage

	// We cannot leave general classification information in m_generalClassification
	// We would then never know whether a team also finished the previous stage
	//  because we want (again) to make sure that a team is finished in all stages!
	m_store.RemoveAll();
	
	CArrival objArrival;
	POSITION nPos = m_generalClassification.GetHeadPosition();
	while( nPos )
	{
		objArrival = m_generalClassification.GetNext( nPos );
		m_store.SetAt( objArrival.m_pTeam, objArrival );
	}

	// After copying, the current stages lists can be emptied
	m_classification.RemoveAll();
	m_generalClassification.RemoveAll();
}

bool CTeamClassification::CalculateGeneralFromStage(CArrival *pArr)
{
	return true;
}

void CTeamClassification::Publish(int nFS, int nHS)
{
	if(m_classification.GetCount())
	{
		// Select the columns to print
		PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
		CEventItem::GetPublicationColumns( TI_CLASSTEAMS, m_pDoc, columns );

		// Make the html document
		CHtmlDoc objHtml( CEventItem( m_pDoc, TI_CLASSTEAMS, nFS, nHS ) );

		objHtml.Header(m_pDoc->StagesGet(nFS,nHS)->m_idTeams.GetNo());

		CArrival objArrival;
		// We provide the html document with the information
		// needed to calculate the time gaps
		objArrival = m_classification.GetHead();
		objHtml.m_championTime = (objArrival.m_units/1000)*1000;

		// Print appropriate classification header
		objHtml.SayText( columns, "Classification" );

		// For the actual contents, we just have to iterate the
		// classification we just made
		POSITION nPos = m_classification.GetHeadPosition();
		int nAll = 1; // Provide correct rankings for every printed arrival
		while( nPos )
		{
			objArrival = m_classification.GetNext( nPos );
			objArrival.m_rank = nAll++;
			// We write the team with its ranking to the html document
			if( m_pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASFULLROWS ) )
				objHtml.Competitor( columns, NULL, &objArrival, NULL, true, true );
			else
				objHtml.Competitor( columns, NULL, &objArrival );

			// Now we possibly have to write each involved competitor
			if( m_pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASFULLROWS )
				&& objArrival.m_pBunch )
			{
				CArrival bunchcompetitor;
				POSITION nPos1 = objArrival.m_pBunch->m_classification.GetHeadPosition();
				while( nPos1 )
				{
					bunchcompetitor = objArrival.m_pBunch->m_classification.GetNext(nPos1);
					objHtml.Competitor( columns, bunchcompetitor.m_staNo, &bunchcompetitor, NULL, true, false, true );
				}
				if( nPos )
					objHtml.SayText(columns, TEXT(""));
			}
		}

		// Print appropriate classification header
		objHtml.SayText( columns, "General classification" );

		// We provide the html document with the information
		// needed to calculate the time gaps
		objArrival = m_generalClassification.GetHead();
		objHtml.m_championTime = (objArrival.m_units/1000)*1000;

		// For the actual contents, we just have to iterate the
		// general classification we just made
		nPos = m_generalClassification.GetHeadPosition();
		nAll = 1; // Provide correct rankings for every printed arrival
		while( nPos )
		{
			objArrival = m_generalClassification.GetNext( nPos );
			objArrival.m_rank = nAll++;
			// We write the team with its ranking to the html document
			objHtml.Competitor( columns, NULL, &objArrival );
		}

		// And we finish the document
		objHtml.Footer(columns);
		objHtml.Finish();
	}
	else
		CHtmlDoc::MakeDummy(
			CEventItem( m_pDoc, TI_CLASSTEAMS, nFS, nHS ),
			m_pDoc->StagesGet(nFS,nHS)->m_idTeams.GetNo() );
}
