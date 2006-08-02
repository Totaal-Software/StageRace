// MostAggressiveClassification.cpp: implementation of the CMostAggressiveClassification class.
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

CMostAggressiveClassification::CMostAggressiveClassification(CStageRaceDoc* pDoc) : CSprintClassification( pDoc )
{

}

bool CMostAggressiveClassification::InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly)
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
		// Obviously, we still have a draw
		// (otherwise we would have returned by now)
		return InsertHereLastResort(objTest, objSubj);
	}
	return false;
}

void CMostAggressiveClassification::Publish(int nFS, int nHS)
{
	CHtmlDoc* pObjHtml = NULL;

	// Select the columns to print
	PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
	CEventItem::GetPublicationColumns( TI_MOSTAGGRESSIVE, m_pDoc, columns );

	// Make the html document
	pObjHtml = new CHtmlDoc( CEventItem( m_pDoc, TI_MOSTAGGRESSIVE, nFS, nHS) );

	// We provide the html document with the information
	// to make the headers
	pObjHtml->Header(m_pDoc->StagesGet(nFS,nHS)->m_idMostAggressive.GetNo());

	// INTERMEDIATE CLASSIFICATION

	// For the actual contents, we just have to iterate the
	// most aggressive classification we just made
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
