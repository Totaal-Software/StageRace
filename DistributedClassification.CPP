// DistributedClassification.cpp : implementation file
//

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

CDistributedClassification::CDistributedClassification(int nFS, int nHS, CStageRaceDoc* pDoc)
{
	m_nFS = nFS;
	m_nHS = nHS;
	m_pDoc = pDoc;
}

const CClassification* CDistributedClassification::GenerateClassification() const
{
	return (const CClassification*)m_pDoc->GenerateUpTo( m_nFS, m_nHS );
}

const CArrivalList* CDistributedClassification::GenerateStartingOrder(CStaNoObjectList* pAvail1, CStaNoObjectList* pAvail2) const
{
	CArrivalList* pList = NULL;
	CTTOrderOptionsDlg dlgOptions;
	if( dlgOptions.DoModal() == IDOK )
	{
		CClassification* pClass = NULL;
		CTeamClassification* pTeam = NULL;
		if( dlgOptions.m_team )
			pTeam = new CTeamClassification( m_pDoc );

		pClass = m_pDoc->GenerateUpTo( m_nFS, m_nHS, pClass, pTeam );

		if( dlgOptions.m_individual )
		{
			// Just to be sure
			if( pClass )
			{
				pList = new CArrivalList;
				int i=1;
				// Check the setting in the dialog
				if( dlgOptions.m_avoidConsecutiveTeamMembers )
				{
					pClass->ScrambleForStartingOrder();
				}

				CTeam * ppreviousteam = NULL;
				bool bStillConsecutive = false;
				// Iterate the whole list of arrivals in the general cl.
				POSITION nPos = pClass->m_generalClassification.GetTailPosition();
				while( nPos )
				{
					CArrival objArrival = pClass->m_generalClassification.GetPrev( nPos );
					CCompetitor objComp = m_pDoc->CompetitorsGet(objArrival.m_staNo);
					if( (objComp.m_pTeam==ppreviousteam) && (ppreviousteam!=NULL) )
					{
						bStillConsecutive = true;
					}
					
					ppreviousteam = objComp.m_pTeam;
					// Validate whether this competitor is allowed in this order
					// It could not be included in the availables because of sign out
					if( pAvail1->Exist( objArrival.m_staNo )
						|| pAvail2->Exist( objArrival.m_staNo ) )
					{
						objArrival.m_order = i++;
						pList->Insert( objArrival );
					}
				}

				if( bStillConsecutive && dlgOptions.m_avoidConsecutiveTeamMembers )
				{
					MessageBox(NULL, LoadStr( IDS_MBC_63 ), LoadStr( IDS_MBT_63 ), MB_OK);
				}
			}
		}
		else
		{
			// Just to be sure
			if( pTeam )
			{
				pList = new CArrivalList;
				int i=1;
				// Check the setting in the dialog
				if( dlgOptions.m_leavePlacesForDroppedTeams )
					i += m_pDoc->TeamsCount()-pTeam->m_generalClassification.GetCount();

				// Iterate the whole list of arrivals in the general cl.
				POSITION nPos = pTeam->m_generalClassification.GetTailPosition();
				while( nPos )
				{
					CArrival objTeam = pTeam->m_generalClassification.GetPrev( nPos );
					
					POSITION nPos1 = pClass->m_generalClassification.GetHeadPosition();
					while( nPos1 )
					{
						CArrival objArrival = pClass->m_generalClassification.GetNext(nPos1);
						CCompetitor objComp = m_pDoc->CompetitorsGet( objArrival.m_staNo );
						if( objComp.m_pTeam==objTeam.m_pTeam )
						{
							objArrival.m_order = i;
							pList->Insert( objArrival );
						}
					}
					i++;
				}
			}				
		}
		if( pClass ) delete pClass;
		if( pTeam ) delete pTeam;
	}
	return pList;
}
