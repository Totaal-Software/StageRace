// ListTimeTrialArrivalNet.cpp: implementation of the CListTimeTrialArrivalNet class.
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

CListTimeTrialArrivalNet::CListTimeTrialArrivalNet( int nAccuracy,
							const CAvailableList* pListAvailable,
							const CArrivalList* pListArrival,
							const CCompetitorList* pListCompetitor/*=NULL*/
						)
						: CListTimeTrialArrivalGross(
							nAccuracy,
							pListAvailable,
							pListArrival,
							pListCompetitor,
							NULL,
							CHelp::HLP_DLG_LSTP_ARR_TT_NET )
{
	//{{AFX_DATA_INIT(CListArrival)
	//}}AFX_DATA_INIT
}

BOOL CListTimeTrialArrivalNet::OnInitDialog()
{
	CListTimeTrialArrivalGross::OnInitDialog();

	SetDlgItemText( IDC_ARRIVAL_INFO, LoadStr( IDS_DIV76 )+" " );

	// Anticipated time - not needed in this one
	GetDlgItem( IDC_ARRIVAL_ANTICIPATETIME )->EnableWindow(FALSE);
	GetDlgItem( IDC_ARRIVAL_ANTICIPATEDTIME )->EnableWindow(FALSE);

	m_time.Init( m_accuracy?2:3 );

	return TRUE;
}

void CListTimeTrialArrivalNet::SetUnits(CArrival *pArr, DWORD units)
{
	pArr->m_units = units;
	// The following is important: you want to know at arrival, later on
	// You could also override GetUnits, but this is nicer, since it will
	// also work when reconfiguring from net to gross time trial
	pArr->m_unitsAtArrival = units;
}
