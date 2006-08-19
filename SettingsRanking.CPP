// SettingsRanking.cpp: implementation of the CSettingsRanking class.
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

CSettingsRanking::CSettingsRanking()
{
	ValueAdd( IDS_SETT_RANK_INDIVIDUAL,
				CSettings::CSetting::GROUP, false, 0, 6 );

	ValueAdd( IDS_SETT_RANK_GENERAL_GENERATETSTANOSORTEDGENERAL,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_RANK_INDIVIDUAL );

	ValueAdd( IDS_SETT_RANK_GENERAL,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_INDIVIDUAL, 6 );
	ValueAdd( IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_GENERAL );
	ValueAdd( IDS_SETT_RANK_GENERAL_SORT_ONSUMRANKINGS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_GENERAL );
	ValueAdd( IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_GENERAL );

	ValueAdd( IDS_SETT_RANK_SPRINT,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_INDIVIDUAL, 9 );
	ValueAdd( IDS_SETT_RANK_SPRINT_ONMOSTHIGHRANKINGS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_SPRINT );
	ValueAdd( IDS_SETT_RANK_SPRINT_ONLATESTRANKING,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_SPRINT );
	ValueAdd( IDS_SETT_RANK_SPRINT_INCLUDEFINISH,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_RANK_SPRINT );
	ValueAdd( IDS_SETT_RANK_SPRINT_PRINTSTAGE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_RANK_SPRINT );

	ValueAdd( IDS_SETT_RANK_POINTS,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_INDIVIDUAL, 10 );
	ValueAdd( IDS_SETT_RANK_POINTS_ONMOSTHIGHRANKINGS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_POINTS );
	ValueAdd( IDS_SETT_RANK_POINTS_ONLATESTRANKING,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_POINTS );

	ValueAdd( IDS_SETT_RANK_CLIMB,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_INDIVIDUAL, 8 );
	ValueAdd( IDS_SETT_RANK_CLIMB_ONMOSTHIGHRANKINGS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_CLIMB );
	ValueAdd( IDS_SETT_RANK_CLIMB_ONLATESTRANKING,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_CLIMB );
	ValueAdd( IDS_SETT_RANK_CLIMB_DIFFCATEGORIES,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_RANK_CLIMB );

	ValueAdd( IDD_SETT_RANK_LASTRESORT,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_INDIVIDUAL );
	ValueAdd( IDD_SETT_RANK_LASTRESORT_STAGE_CL,
				CSettings::CSetting::MULTIOPTION, true, IDD_SETT_RANK_LASTRESORT );
	ValueAdd( IDD_SETT_RANK_LASTRESORT_GENERAL_CL,
				CSettings::CSetting::MULTIOPTION, false, IDD_SETT_RANK_LASTRESORT );

	ValueAdd( IDS_SETT_RANK_TEAMS,
				CSettings::CSetting::GROUP, false, 0, 7 );
	ValueAdd( IDS_SETT_RANK_TEAMS_GENERATE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_RANK_TEAMS );

	ValueAdd( IDS_SETT_RANK_TEAMS_BUNCH,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_TEAMS );
	ValueAdd( IDS_SETT_RANK_TEAMS_BUNCH_FROMTIMES,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_TEAMS_BUNCH );
	ValueAdd( IDS_SETT_RANK_TEAMS_BUNCH_FROMRANKINGS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_TEAMS_BUNCH );

	ValueAdd( IDS_SETT_RANK_TEAMS_STAGE,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_TEAMS );
	ValueAdd( IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_TEAMS_STAGE );
	ValueAdd( IDS_SETT_RANK_TEAMS_STAGE_ONWITHOUTSUMRANKINGS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_TEAMS_STAGE );

	ValueAdd( IDS_SETT_RANK_TEAMS_DECIDING,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_TEAMS );
	ValueAdd( IDS_SETT_RANK_TEAMS_DECIDING_FIRST,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_TEAMS_DECIDING );
	ValueAdd( IDS_SETT_RANK_TEAMS_DECIDING_LAST,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_TEAMS_DECIDING );

	ValueAdd( IDS_SETT_RANK_TEAMS_GENERAL,
				CSettings::CSetting::GROUP, false, IDS_SETT_RANK_TEAMS );
	ValueAdd( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_RANK_TEAMS_GENERAL );
	ValueAdd( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHOUTSUMRANKINGS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_RANK_TEAMS_GENERAL );

	
	m_bunchSize = 3;
	m_maxDepthFinish = 250;
	m_maxDepthSprint = 8;
}

CSettingsRanking::CSettingsRanking(CSettingsRanking *pSettings)
{
	CSettingsRanking();
	*this = *pSettings;
}

CPageSettings* CSettingsRanking::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsRanking();
	// Make a copy of this settings
	CSettingsRanking*	pCopy = new CSettingsRanking();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsRanking::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsRanking* s1 = (CSettingsRanking*)&s;
	m_bunchSize = s1->m_bunchSize;
	m_maxDepthFinish = s1->m_maxDepthFinish;
	m_maxDepthSprint = s1->m_maxDepthSprint;

	return *this;
}

void CSettingsRanking::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> m_bunchSize >> m_maxDepthFinish >> m_maxDepthSprint;
	}
	else
	{
		ar << m_bunchSize << m_maxDepthFinish << m_maxDepthSprint;
	}
}
