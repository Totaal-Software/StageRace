// ListTimeTrialOrder.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTimeTrialOrder property page


CListTimeTrialOrder::CListTimeTrialOrder( const CAvailableList* pListAvailable,
											const CArrivalList* pListArrival,
											const CArrivalList* pListRanked,
											const CCompetitorList* pListCompetitor/*=NULL*/,
											const CDistributedClassification* pListPreviousHS/*=NULL*/,
											const CDistributedClassification* pListPreviousFS/*=NULL*/,
											bool bAllowLateChangesStartOrder /*=true*/
										)
										: CListArrival(
											0,
											pListAvailable,
											pListArrival,
											true,
											pListCompetitor,
											IDS_DIV39,
											CHelp::HLP_DLG_LSTP_TTORDER )
{
	m_pListPreviousHS = pListPreviousHS;
	m_pListPreviousFS = pListPreviousFS;
	if( !bAllowLateChangesStartOrder )
		m_pListRanked = pListRanked;
	else
		m_pListRanked = NULL;
	m_ctrlArrivalList.AddLockedCompetitors( pListRanked );
	//{{AFX_DATA_INIT(CListTimeTrialOrder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CListTimeTrialOrder::~CListTimeTrialOrder()
{
}

void CListTimeTrialOrder::DoDataExchange(CDataExchange* pDX)
{
	CListArrival::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListTimeTrialOrder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListTimeTrialOrder, CListArrival)
	//{{AFX_MSG_MAP(CListTimeTrialOrder)
	ON_BN_CLICKED(IDC_ARRIVAL_FUNCTIONS, OnTtorderFunctions)
	ON_COMMAND(ID_TIMETRIALORDERFUNCTIONS_GAPS, OnTimetrialorderfunctionsGaps)
	ON_COMMAND(ID_TIMETRIALORDERFUNCTIONS_AUTO, OnTimetrialorderfunctionsAuto)
	ON_COMMAND(ID_TIMETRIALORDERFUNCTIONS_FROMLASTHALFSTAGE, OnTimetrialorderfunctionsFromlasthalfstage)
	ON_COMMAND(ID_TIMETRIALORDERFUNCTIONS_FROMLASTFULLSTAGE, OnTimetrialorderfunctionsFromlastfullstage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListTimeTrialOrder message handlers

void CListTimeTrialOrder::OnTtorderFunctions() 
{
	// SHOW THE FUNCTIONS MENU

	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_TTORDERFUNCTIONS );
	aMenu.EnableMenuItem( ID_TIMETRIALORDERFUNCTIONS_FROMLASTHALFSTAGE,
		m_pListPreviousHS?MF_ENABLED:MF_GRAYED  );
	aMenu.EnableMenuItem( ID_TIMETRIALORDERFUNCTIONS_FROMLASTFULLSTAGE,
		m_pListPreviousFS?MF_ENABLED:MF_GRAYED  );
	aMenu.EnableMenuItem( ID_TIMETRIALORDERFUNCTIONS_AUTO,
		(m_ctrlArrivalList.GetSelectedCount() > 1)?MF_ENABLED:MF_GRAYED );
	// Retrieve the position of the button by which this menu is requested
	RECT posButton;
	GetDlgItem( IDC_ARRIVAL_FUNCTIONS )->GetWindowRect( &posButton );
	// Show the menu
	aMenu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
						posButton.left + (posButton.right-posButton.left)/2, // Middle of button
						posButton.top + (posButton.bottom-posButton.top)/2,
						this );
}

BOOL CListTimeTrialOrder::OnInitDialog() 
{
	// Not base class!
	CAllListArrivalPages::OnInitDialog();

	m_time.Init( 0, 2 );
	m_ctrlAvailableList.Init( 0, CArrivalListCtrl::ALT_TTORDERAVAILABLE );
	m_ctrlArrivalList.Init( 0, CArrivalListCtrl::ALT_TTORDERARRIVAL );

	// Set the edit boxes StaNo and Rank to default zero
	GetDlgItem( IDC_ARRIVAL_STANO )->SetWindowText( TEXT("0") );
	GetDlgItem( IDC_ARRIVAL_RANK )->SetWindowText( TEXT("0") );
	
	// Fill the list boxes with availables/arrivals
	m_ctrlAvailableList.DrawList( &m_listAvailable );
	m_ctrlArrivalList.DrawList( &m_listArrival );

	// Make resizable
	AddSzControl(IDC_ARRIVAL_LABELRANK, mdRelative, mdRepos);
	AddSzControl(IDC_ARRIVAL_RANK, mdRelative, mdRepos);

	// Remove some thingies
	GetDlgItem(IDC_ARRIVAL_LABELTIMECUT1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ARRIVAL_LABELTIMECUT2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ARRIVAL_TIMECUT)->ShowWindow(SW_HIDE);


	// Change "Rank" to "Order"
	SetDlgItemText( IDC_ARRIVAL_LABELRANK, "&"+LoadStr(IDS_DIV64) );

	AddSzControl(IDC_ARRIVAL_FUNCTIONS, mdNone, mdRepos);

	DrawCounters();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListTimeTrialOrder::OnTimetrialorderfunctionsGaps() 
{
	m_listArrival.RemoveGapsOrder();
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

void CListTimeTrialOrder::OnTimetrialorderfunctionsAuto() 
{
	// We only do this if there are two or more competitors selected
	// so that we can use the time of the first competitor to start from
	if( m_ctrlArrivalList.GetSelectedCount() > 1 )
	{
		// Build an array with all selected staNos
		CArray<WORD, WORD> selectedStaNos;
		POSITION nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
		while( nPos )
		{
			int nItem = m_ctrlArrivalList.GetNextSelectedItem(nPos);
			selectedStaNos.Add((WORD)m_ctrlArrivalList.GetItemData(nItem));
		}

		// Get the first and last so that we can use them in the dialog
		CArrival first = m_listArrival.GetAt( selectedStaNos.GetAt(0) );
		CArrival last = m_listArrival.GetAt( selectedStaNos.GetAt(selectedStaNos.GetSize()-1 ) );

		// Ask user for details
		CDlgInterval aDlg( first.m_staNo, first.m_unitsAtStart, first.m_order,
			last.m_staNo, last.m_unitsAtStart, last.m_order );

		if( aDlg.DoModal()==IDOK )
		{
			// We only edit the data, see below for the view
			bool bAllAllowed = true;
			int nCount = 0;
			DWORD tNewTime;
			CArrival objArr;
			short nSign;
			while( nCount < selectedStaNos.GetSize() )
			{
				if( aDlg.m_ascending )
				{
					objArr = m_listArrival.GetAt( selectedStaNos.GetAt(nCount) );
					nSign = 1;
				}
				else
				{
					objArr = m_listArrival.GetAt( selectedStaNos.GetAt(selectedStaNos.GetSize()-nCount-1) );
					nSign = -1;
				}

				if( aDlg.m_useOrder )
				{
					tNewTime = aDlg.m_startTime + (objArr.m_order-first.m_order) * aDlg.m_interval * nSign;
				}
				else
				{
					tNewTime = aDlg.m_startTime + nCount * aDlg.m_interval * nSign;
				}
				if( objArr.m_unitsAtStart != tNewTime )
				{
					if( ChangesAllowed( objArr.m_staNo ) )
					{
						// Give an new order and replace it in the data
						objArr.SetStart(tNewTime);
						m_listArrival.Insert( objArr );
					}
					else
					{
						bAllAllowed = false;
					}
				}
				nCount++;
			}

			// Visualisation
			m_ctrlArrivalList.DrawList( &m_listArrival );
			m_staNo.EnableWindow( TRUE );

			// Make error if not all changes were allowed due to competitors
			// already being ranked in this time trial
			if( !bAllAllowed )
				MessageBox( LoadStr( IDS_MBC_50 ),
							LoadStr( IDS_MBT_50 ),
							MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );
		}
	}
}

void CListTimeTrialOrder::OnTimetrialorderfunctionsFromlasthalfstage() 
{
	if( m_pListPreviousHS ) // Just to make sure (should already be validated by building the menu)
		FromEarlierStage( m_pListPreviousHS );
}

void CListTimeTrialOrder::OnTimetrialorderfunctionsFromlastfullstage() 
{
	if( m_pListPreviousFS ) // Just to make sure (should already be validated by building the menu)
		FromEarlierStage( m_pListPreviousFS );
}

void CListTimeTrialOrder::FromEarlierStage(const CDistributedClassification* pDistriClass)
{
/*

(Informative)

From: Reglement Tour de France 99

In the prologue and individual time trial stages, the starting order is as follows:
- prologue: riders start in the order set by race management;
- Metz: riders start in the reverse order of the general placings following the
  previous stage

By agreement with the commissaires’ panel, the race management may reduce or increase
the interval for all or some of the riders.
By agreement with the race management, the starting order may be altered where the
reverse order of the general placings causes two riders of the same team to be placed
consecutively. In such a case, the less well-placed of the two takes the place of the rider
who would normally have preceded him.
The starting order may also be altered where it is liable to give rise to a particular situation
impairing the fair running of the race.

*/

	const CArrivalList* pClass = pDistriClass->GenerateStartingOrder(&m_listAvailable, &m_listArrival);

	if( pClass )
	{
		bool bAllAllowed = true;
		// Iterate the whole list of arrivals in the general cl.
		DWORD nState = 0;
		CArrival objArrival;
		while( pClass->IterateSorted( nState, objArrival ) )
		{
			// If we are allowed to fiddle with this competitor
			if( ChangesAllowed( objArrival.m_staNo ) )
			{
				m_listAvailable.Remove( objArrival.m_staNo );
				// Insert the aArrival in m_listArrival
				m_listArrival.Insert( objArrival );
			}
			else
				bAllAllowed = false;
		}

		// Visualisation
		m_ctrlArrivalList.DrawList( &m_listArrival );
		m_ctrlAvailableList.DrawList( &m_listAvailable );

		// Make error if not all changes were allowed due to competitors
		// already being ranked in this time trial
		if( !bAllAllowed )
			MessageBox( LoadStr( IDS_MBC_50 ),
						LoadStr( IDS_MBT_50 ),
						MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );

		DrawCounters();

		delete pClass;
	}
}

DWORD CListTimeTrialOrder::GetUnits(CArrival *pArr)
{
	return pArr->m_unitsAtStart;
}

void CListTimeTrialOrder::SetUnits(CArrival *pArr, DWORD units)
{
	pArr->SetStart( units );
}

WORD CListTimeTrialOrder::GetRank(CArrival *pArr)
{
	return pArr->m_order;
}

void CListTimeTrialOrder::SetRank(CArrival *pArr, WORD nRank)
{
	pArr->m_order = nRank;
}

BOOL CListTimeTrialOrder::ChangesAllowed(WORD nStaNo)
{
	if( m_pListRanked )
		return !m_pListRanked->Exist( nStaNo );
	return true;
}


void CListTimeTrialOrder::OnOK()
{
	// This implementation (note that not the direct base class
	// is called) prevents an redundant (and incorrect) integrity
	// check to be performed
	CAllListArrivalPages::OnOK();
}
