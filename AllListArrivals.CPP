// AllListArrivals.cpp: implementation of the CAllListArrivalPages class.
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

CAllListArrivalPages::CAllListArrivalPages( CHelp::HELP_TOPIC helptopic,
									UINT nIDTemplate,
									UINT nIDLabel,
									int nAccuracy,
									const CAvailableList* pListAvailable,
									const CArrivalList* pListArrival,
									const CCompetitorList* pListCompetitor/*=NULL*/
								)
								: CAllListPages(
									helptopic,
									nIDTemplate,
									nIDLabel,
									pListAvailable,
									pListArrival,
									pListCompetitor
								)
{
	m_accuracy = nAccuracy;
	m_ctrlAvailableList.AddCompetitorSource( pListCompetitor );
	m_ctrlArrivalList.AddCompetitorSource( pListCompetitor );
}

void CAllListArrivalPages::DoDataExchange(CDataExchange* pDX)
{
	CAllListPages::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAllListArrivalPages)
	DDX_Control(pDX, IDC_ARRIVAL_STANO, m_staNo);
	DDX_Control(pDX, IDC_ARRIVAL_TIME, m_time);
	DDX_Control(pDX, IDC_ARRIVAL_LISTAVAILABLE, m_ctrlAvailableList);
	DDX_Control(pDX, IDC_ARRIVAL_LISTARRIVAL, m_ctrlArrivalList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAllListArrivalPages, CAllListPages)
	//{{AFX_MSG_MAP(CAllListArrivalPages)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ARRIVAL_LISTARRIVAL, OnItemchangedArrivalListarrival)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ARRIVAL_LISTAVAILABLE, OnItemchangedArrivalListavailable)
	ON_NOTIFY(NM_SETFOCUS, IDC_ARRIVAL_LISTARRIVAL, OnSetfocusArrivalListarrival)
	ON_NOTIFY(NM_SETFOCUS, IDC_ARRIVAL_LISTAVAILABLE, OnSetfocusArrivalListavailable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAllListArrivalPages::OnInitDialog()
{
	CAllListPages::OnInitDialog();

	// Make resizable
	AddSzControl(IDC_ARRIVAL_LISTAVAILABLE, mdRelativeResize, mdResize);
	AddSzControl(IDC_ARRIVAL_LISTARRIVAL, mdRelativeRepos, mdResize);

	AddSzControl(IDC_ARRIVAL_TITLEAVAILABLE, mdNone, mdNone);
	AddSzControl(IDC_ARRIVAL_TITLEARRIVAL, mdRelative, mdNone);

	AddSzControl(IDC_ARRIVAL_COUNTAVAILABLE, mdRelativeResize, mdRepos);
	AddSzControl(IDC_ARRIVAL_COUNTARRIVAL, mdRelativeRepos, mdRepos);

	AddSzControl(IDC_ARRIVAL_TIME, mdRelative, mdRepos);
	AddSzControl(IDC_ARRIVAL_STANO, mdRelative, mdRepos);

	AddSzControl(IDC_ARRIVAL_LABELTIME, mdRelative, mdRepos);
	AddSzControl(IDC_ARRIVAL_LABELSTANO, mdRelative, mdRepos);

	AddSzControl(IDC_ARRIVAL_BAR, mdRelative, mdResize);

	AddSzControl(IDC_DECLASS, mdRelative, mdRepos);
	AddSzControl(IDC_SUBMIT, mdRelative, mdRepos);

	// Make validation of entered StaNo possible
	m_staNo.AddStaNoObjectList( &m_listArrival );
	m_staNo.AddStaNoObjectList( &m_listAvailable );

	return TRUE;
}

BOOL CAllListArrivalPages::PreTranslateMessage(MSG *pMsg)
{
	if( (pMsg->message == WM_CHAR)
		&& (pMsg->wParam == 1) )
		m_ctrlArrivalList.SelectAll();

	return CAllListPages::PreTranslateMessage(pMsg);
}

void CAllListArrivalPages::DrawCounters()
{
	// SET THE STATIC EDIT BOXES WITH THE COUNT OF LIST ITEMS
	TCHAR czBuffer[10];
	_itot( m_listAvailable.GetCount(), czBuffer, 10 );
	GetDlgItem( IDC_ARRIVAL_COUNTAVAILABLE )->SetWindowText( "("+CString(czBuffer)+") " );	
	_itot( m_listArrival.GetCount(), czBuffer, 10 );
	GetDlgItem( IDC_ARRIVAL_COUNTARRIVAL   )->SetWindowText( "("+CString(czBuffer)+") " );
}

void CAllListArrivalPages::OnItemchangedArrivalListavailable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	// First check if anything selected at all
	if( m_ctrlAvailableList.GetSelectedCount() )
	{
		CArrival aArrival = 
			m_listAvailable.GetAt( m_ctrlAvailableList.GetSelected() );

		// Copy its properties to the edit boxes
			// StaNo
			m_staNo.SetValue( aArrival.m_staNo );

			// Rank
			// Don't border the rank edit box, so that the auto increment can do its work

			// Time
			m_time.SetTime( GetUnits( &aArrival ) );
	}

	// Set the focus to the rank box so a selected item can be ranked quickly
	if( GetDlgItem( IDC_ARRIVAL_RANK ) )
	{
		GetDlgItem( IDC_ARRIVAL_RANK )->SetFocus();
		((CEdit*) GetDlgItem( IDC_ARRIVAL_RANK ))->SetSel( 0, -1 );
	}
	else
	{
		m_time.SetFocus();
		m_time.SetSel( 0, -1 );
	}
}

void CAllListArrivalPages::OnItemchangedArrivalListarrival(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	// First check if anything selected at all
	if( m_ctrlArrivalList.GetSelectedCount() )
	{
		CArrival aArrival = 
			m_listArrival.GetAt( m_ctrlArrivalList.GetSelected() );

		// Copy its properties to the edit boxes
			// StaNo
			m_staNo.SetValue( aArrival.m_staNo );

			// Rank
			if( GetDlgItem( IDC_ARRIVAL_RANK ) )
			{
				TCHAR czBuffer[10];
				_itot( GetRank(&aArrival), czBuffer, 10 );
				GetDlgItem( IDC_ARRIVAL_RANK )->SetWindowText( czBuffer );
			}

			// Time
			m_time.SetTime( GetUnits( &aArrival ) );
	}

	// Disable some boxes in case of multiple selection
	if( m_ctrlArrivalList.GetSelectedCount()>1 )
	{
		if( GetDlgItem( IDC_ARRIVAL_RANK ) )
			GetDlgItem( IDC_ARRIVAL_RANK )->EnableWindow( FALSE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( FALSE );
	}
	else
	{
		if( GetDlgItem( IDC_ARRIVAL_RANK ) )
			GetDlgItem( IDC_ARRIVAL_RANK )->EnableWindow( TRUE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( TRUE );
	}

	// Set the focus to the time boxes so a selected item can be given times quickly
	m_time.SetFocus();
	m_time.SetSel( 0, -1 );
}

void CAllListArrivalPages::OnSetfocusArrivalListavailable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;


	// The effects of a multiple selection in the arrival list
	// have to be cancelled when the available list gets focus
	if( m_ctrlArrivalList.GetSelectedCount()>1 )
	{
		if( GetDlgItem( IDC_ARRIVAL_RANK ) )
			GetDlgItem( IDC_ARRIVAL_RANK )->EnableWindow( TRUE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( TRUE );
	}
}

void CAllListArrivalPages::OnSetfocusArrivalListarrival(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	// The effects of a multiple selection in the arrival list
	// have to be reinstated when the arrival list gets focus
	if( m_ctrlArrivalList.GetSelectedCount()>1 )
	{
		if( GetDlgItem( IDC_ARRIVAL_RANK ) )
			GetDlgItem( IDC_ARRIVAL_RANK )->EnableWindow( FALSE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( FALSE );
	}
}
