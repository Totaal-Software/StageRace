// AllListPages.cpp: implementation of the CAllListPages class.
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

CAllListPages::CAllListPages( CHelp::HELP_TOPIC helptopic,
								UINT nIDTemplate,
								UINT nIDLabel,
								const CAvailableList* pListAvailable,
								const CArrivalList* pListArrival,
								const CCompetitorList* pListCompetitor/*=NULL*/
							)
							: CStageRaceWnd<cdxCDynamicPropPage>( helptopic, nIDTemplate, nIDLabel )
{
	if( pListArrival )
		m_listArrival = *pListArrival;
	if( pListAvailable )
	{
		DWORD nState=0;
		CArrival objArr;
		while( pListAvailable->IterateSorted( nState, objArr ) )
			if( !m_listArrival.Exist( objArr.m_staNo ) )
				m_listAvailable.Insert( objArr );
	}
	m_listArrival.ClearDirty();
}
