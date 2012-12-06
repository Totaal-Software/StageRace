// ListTimeTrialArrival.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListTimeTrialArrivalGross property page

CListTimeTrialArrivalGross::CListTimeTrialArrivalGross(	int nAccuracy,
												const CAvailableList* pListAvailable,
												const CArrivalList* pListArrival,
												const CCompetitorList* pListCompetitor/*=NULL*/,
												UINT nIDLabel/*=NULL*/,
												CHelp::HELP_TOPIC helptopic/*=CHelp::HLP_DLG_LSTP_ARR_TT_GROSS*/
											)
											: CAllListArrivalPages(
												helptopic,
												CListTimeTrialArrivalGross::IDD,
												nIDLabel,
												nAccuracy,
												pListAvailable,
												pListArrival,
												pListCompetitor )
{
	//{{AFX_DATA_INIT(CListTimeTrialArrivalGross)
	//}}AFX_DATA_INIT
}

void CListTimeTrialArrivalGross::DoDataExchange(CDataExchange* pDX)
{
	CAllListArrivalPages::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListTimeTrialArrivalGross)
	DDX_Control(pDX, IDC_ARRIVAL_ANTICIPATEDTIME, m_anticipatedTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListTimeTrialArrivalGross, CAllListArrivalPages)
	//{{AFX_MSG_MAP(CListTimeTrialArrivalGross)
	ON_BN_CLICKED(IDC_DECLASS, OnDeclass)
	ON_BN_CLICKED(IDC_SUBMIT, OnSubmit)
	ON_BN_CLICKED(IDC_ARRIVAL_ANTICIPATETIME, OnArrivalAnticipatetime)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_ARRIVAL_TIMECUT, OnChangeArrivalTimecut)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Declass and submit

void CListTimeTrialArrivalGross::OnSubmit() 
{
	// When single selection
	if( m_staNo.IsWindowEnabled() )
	{
		CArrival aArrival;

		// If no Rank or no StaNo entered, generate error beep
		if( m_staNo.Exist() )
		{
			if ( m_listAvailable.Exist( m_staNo.GetValue() ) )
			// The StaNo exists as Available, so look it up and remove it
			{
				aArrival = m_listAvailable.GetAt( m_staNo.GetValue() );

				// Remove the aArrival from m_listAvailable
				m_listAvailable.Remove( aArrival.m_staNo );

				// Remove from the available view
				m_ctrlAvailableList.Clear( aArrival.m_staNo );
			}
			// Obviously the StaNo exists in Arrival, so look it up to change it
			else
			{
				aArrival = m_listArrival.GetAt( m_staNo.GetValue() );
			}

			// Set the properties of the retrieved competitor to the entered values
			SetUnits( &aArrival, m_time.GetTime() );

			// Insert the aArrival in m_listArrival again
			m_listArrival.Insert( aArrival );

			// Recalculate and redraw the arrival list
			m_listArrival.ApplyTimeTrialRanks();
			m_ctrlArrivalList.DrawList( &m_listArrival );

			m_ctrlArrivalList.Select( aArrival.m_staNo );

			// Prepare the dialog box for the next cycle
			// Set the focus to StaNo and select the contents
			m_staNo.SetFocus();
			m_staNo.SetSel( 0, -1, FALSE );

			DrawCounters();
		}
		else
			MessageBeep( MB_ICONASTERISK );
	}
	else
	// When multiple selection (replace only)
	{
		POSITION nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
		if( nPos )
		{
			DWORD t = m_time.GetTime();
			WORD nStaNo;
			while( nPos )
			{
				// Lookup item
				int nItem = m_ctrlArrivalList.GetNextSelectedItem(nPos);
				// Get corresponding StaNo
				nStaNo = (WORD)m_ctrlArrivalList.GetItemData( nItem );
				// Get the matching arrival
				CArrival aArr = m_listArrival.GetAt( nStaNo );
				// Set the time property right
				SetUnits( &aArr, t );
				// Store the changed arrival
				m_listArrival.Insert( aArr );
				// Draw the item again
				m_ctrlArrivalList.Draw( &aArr );
				// Get the newly first selected item for the next iteration
				nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
			}

			m_listArrival.ApplyTimeTrialRanks();
			m_ctrlArrivalList.DrawList( &m_listArrival );

			m_ctrlArrivalList.Select( nStaNo );
		}
		else
			MessageBeep( MB_ICONASTERISK );
	}
}

void CListTimeTrialArrivalGross::OnDeclass() 
{
	POSITION nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
	if( nPos )
	{
		while( nPos )
		{
			// Lookup item
			int nItem = m_ctrlArrivalList.GetNextSelectedItem(nPos);
			// Get corresponding StaNo
			WORD nStaNo = (WORD)m_ctrlArrivalList.GetItemData( nItem );
			// Copy from the arrival list to the available list
			m_listAvailable.Insert( m_listArrival.GetAt( nStaNo ) );
			// Remove from the arrival list
			m_listArrival.Remove( nStaNo );
			// Delete it from the view (arrivals)
			m_ctrlArrivalList.DeleteItem( nItem );
			// Draw the item in the view (availables)
			m_ctrlAvailableList.Draw( &m_listAvailable.GetAt( nStaNo ) );
			// Get the newly first selected item for the next iteration
			nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
		}
		// No multiple selection possible at this point,
		// so enable all edit controls again
		GetDlgItem( IDC_ARRIVAL_TIME )->EnableWindow( TRUE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( TRUE );

		DrawCounters();
	}
	else
		// Nothing to delete
		MessageBeep( MB_ICONASTERISK );

	m_listArrival.ApplyTimeTrialRanks();
	m_ctrlArrivalList.DrawList( &m_listArrival );
	DrawCounters();
}

/////////////////////////////////////////////////////////////////////////////
// Various

BOOL CListTimeTrialArrivalGross::PreTranslateMessage(MSG* pMsg) 
{
	// Check for [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_RETURN )
	{
		// If we're in the rank or stano box, we first want the user to go
		// to the time boxes
		if( (GetFocus() == GetDlgItem( IDC_ARRIVAL_STANO )) )
		{
			// If nothing is in the current box, we don't want to jump
			// anywhere but let the user first fill in some value
			// We check on the numerical value; zero is not sufficient
			CString cContents;
			GetFocus()->GetWindowText( cContents );
			if( _ttoi( cContents ) )
			{
				m_time.SetFocus();
				m_time.SetSel( 0, -1 );
			}
		}
		else
			// On enter, 13 we submit the form
			OnSubmit();

		return TRUE;
	};
	
	// StageRace message handling

	////////////////////////////////
	// INCOMING COMPETITOR PLUS TIME
	if( pMsg->message == WM_STAGERACE_AR_SETCOMP )
	{
		CArrival aArrival;
		// If no Rank or no StaNo entered, generate error beep
		if( m_listAvailable.Exist( pMsg->wParam ) ||
			m_listArrival.Exist( pMsg->wParam ) )
		{
			if ( m_listAvailable.Exist( pMsg->wParam ) )
			// The StaNo exists as Available, so look it up and remove it
			{
				aArrival = m_listAvailable.GetAt( pMsg->wParam );

				// Remove the aArrival from m_listAvailable
				m_listAvailable.Remove( aArrival.m_staNo );

				// Remove from the available view
				m_ctrlAvailableList.Clear( aArrival.m_staNo );
			}
			// Obviously the StaNo exists in Arrival, so look it up to change it
			else
			{
				aArrival = m_listArrival.GetAt( pMsg->wParam );
			}

			// Set the properties of the retrieved competitor to the entered values
			aArrival.SetArrival( pMsg->lParam );

			// Insert the aArrival in m_listArrival again
			m_listArrival.Insert( aArrival );

			// Recalculate and redraw the arrival list
			m_listArrival.ApplyTimeTrialRanks();
			m_ctrlArrivalList.DrawList( &m_listArrival );

			m_ctrlArrivalList.Select( aArrival.m_staNo );

			DrawCounters();
		}
		return TRUE;
	}
	////////////////////////////////////////
	// REQUEST TO DECLASS ARRIVED COMPETITOR
	if( pMsg->message == WM_STAGERACE_AR_DECLASSCOMP )
	{
		if( m_listArrival.Exist( pMsg->wParam ) )
		{
			// Copy from the arrival list to the available list
			m_listAvailable.Insert( m_listArrival.GetAt( pMsg->wParam ) );
			// Remove from the arrival list
			m_listArrival.Remove( pMsg->wParam );
			// Delete it from the view (arrivals)
			m_ctrlArrivalList.Clear( pMsg->wParam );
			// Draw the item in the view (availables)
			m_ctrlAvailableList.Draw( &m_listAvailable.GetAt( pMsg->wParam ) );

			// Recalculate and redraw the arrival list
			m_listArrival.ApplyTimeTrialRanks();
			m_ctrlArrivalList.DrawList( &m_listArrival );

			DrawCounters();
		}
		// Return null indicating message handled satisfactory
		return TRUE;
	}
	/////////////////////////////////////////////////
	// INFORMATION REQUEST: COMPETITOR BASED ON STANO
	if( pMsg->message == WM_STAGERACE_AR_GETCOMPFROMSTANO )
	{
		// Check if requested competitor exists
		if( m_listArrival.Exist( pMsg->wParam & 0xFFFF ) )
		{
			CArrival aArrival;
 			// The StaNo exists as Arrival, so look it up and use it
 			aArrival = m_listArrival.GetAt( pMsg->wParam & 0xFFFF );
			
			// wP: ub: rank wP: lb: StaNo
			UINT wParam = (aArrival.m_rank << 16) | (aArrival.m_staNo & 0xFFFF);
			// lP: time [ms] - Net time!
			UINT lParam = aArrival.m_units;

			// Post the message as it is to the appropriate window
			::PostMessage( (HWND)pMsg->lParam,
							WM_STAGERACE_AR_INFOCOMP,
							wParam,
							lParam );
		}
		else
			// If not exist, return "invalid" message to the appropriate window
			::PostMessage( (HWND)pMsg->lParam,
							WM_STAGERACE_AR_INFOCOMP,
							-1, // Indicates (by convention) invalid request
							-1 );

		// Return null indicating message handled satisfactory
		return TRUE;
	}
	/////////////////////////////////////////////////
	// INFORMATION REQUEST: START TIME BASED ON STANO
	if( pMsg->message == WM_STAGERACE_TT_GETSTARTTIME )
	{
		// Check if requested competitor exists
		if( m_listArrival.Exist( pMsg->wParam & 0xFFFF ) )
		{
			CArrival aArrival;
 			// The StaNo exists as Arrival, so look it up and use it
 			aArrival = m_listArrival.GetAt( pMsg->wParam & 0xFFFF );
			
			// wP: ub: NULL wP: lb: StaNo
			UINT wParam = aArrival.m_staNo & 0xFFFF;
			// lP: time [ms] - Start time!
			UINT lParam = aArrival.m_unitsAtStart;

			// Post the message as it is to the appropriate window
			::PostMessage( (HWND)pMsg->lParam,
							WM_STAGERACE_TT_INFOCOMP,
							wParam,
							lParam );
		}
		else
		{
			// Check if requested competitor exists
			if( m_listAvailable.Exist( pMsg->wParam & 0xFFFF ) )
			{
				CArrival aArrival;
 				// The StaNo exists as Arrival, so look it up and use it
 				aArrival = m_listAvailable.GetAt( pMsg->wParam & 0xFFFF );
				
				// wP: ub: NULL wP: lb: StaNo
				UINT wParam = aArrival.m_staNo & 0xFFFF;
				// lP: time [ms] - Start time!
				UINT lParam = aArrival.m_unitsAtStart;

				// Post the message as it is to the appropriate window
				::PostMessage( (HWND)pMsg->lParam,
								WM_STAGERACE_TT_INFOCOMP,
								wParam,
								lParam );
			}
			else
				// If not exist, return "invalid" message to the appropriate window
				::PostMessage( (HWND)pMsg->lParam,
								WM_STAGERACE_TT_INFOCOMP,
								-1, // Indicates (by convention) invalid request
								-1 );
		}

		// Return null indicating message handled satisfactory
		return TRUE;
	}
	////////////////////////////////////////////////
	// INFORMATION REQUEST: COMPETITOR BASED ON RANK
	if( pMsg->message == WM_STAGERACE_AR_GETCOMPFROMRANK )
	{
		int nRank = pMsg->wParam >> 16;

		CArrival aArrival;
		// Check if the requested rank exists
		if( m_listArrival.GetAtRank( nRank, &aArrival ) )
		{
			// wP: ub: rank wP: lb: StaNo
			UINT wParam = (aArrival.m_rank << 16) | (aArrival.m_staNo & 0xFFFF);
			// lP: time [ms] - Net time!
			UINT lParam = aArrival.m_units;

			// Post the message as it is to the appropriate window
			::PostMessage( (HWND)pMsg->lParam,
							WM_STAGERACE_AR_INFOCOMP,
							wParam,
							lParam );
		}
		else
			// If not exist, return "invalid" message to the appropriate window
			::PostMessage( (HWND)pMsg->lParam,
							WM_STAGERACE_AR_INFOCOMP,
							-1, // Indicates (by convention) invalid request
							-1 );

		// Return null indicating message handled satisfactory
		return TRUE;
	}
	////////////////////////////////////////////////
	// INFORMATION REQUEST: COMPETITOR BASED ON TIME
	if( pMsg->message == WM_STAGERACE_AR_GETCOMPFROMTIME )
	{
		CArrival aArrival;
		int nRank = m_listArrival.GetCount();
		// Iterate the list backwards, looking for the first smaller time
		do
		{
			// Top of list has been reached
			if( nRank==0 )
			{
				// If not exist, return "invalid" message to the appropriate window
				::PostMessage( (HWND)pMsg->lParam,
								WM_STAGERACE_AR_INFOCOMP,
								-1, // Indicates (by convention) invalid request
								-1 );
				// Return null indicating message handled satisfactory
				return TRUE;
			}

 			// The StaNo exists as Arrival, so look it up and use it
 			m_listArrival.GetAtRank( nRank--, &aArrival );
		}
		while( aArrival.m_units > (int)pMsg->wParam );

		// wP: ub: rank wP: lb: StaNo
		UINT wParam = (aArrival.m_rank << 16) | (aArrival.m_staNo & 0xFFFF);
		// lP: time [ms] - Net time!
		UINT lParam = aArrival.m_units;

		// Post the message as it is to the appropriate window
		::PostMessage( (HWND)pMsg->lParam,
						WM_STAGERACE_AR_INFOCOMP,
						wParam,
						lParam );

		// Return null indicating message handled satisfactory
		return TRUE;
	}

	return CAllListArrivalPages::PreTranslateMessage(pMsg);
}

BOOL CListTimeTrialArrivalGross::OnInitDialog() 
{
	CAllListArrivalPages::OnInitDialog();

	SetDlgItemText( IDC_ARRIVAL_INFO, LoadStr( IDS_DIV77 )+" " );

	m_time.Init( (m_accuracy==1)?2:3, 2 );
	m_ctrlAvailableList.Init( m_accuracy, CArrivalListCtrl::ALT_TTAVAILABLE );
	m_ctrlArrivalList.Init( m_accuracy, CArrivalListCtrl::ALT_TTARRIVAL, &m_listArrival );
		
	// Arrange the time cut display
	SetDlgItemInt( IDC_ARRIVAL_TIMECUT, m_listArrival.GetTimeCut() );

	// Anticipated time
	CSRRegKey reg;
	reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Time trial arrival") );

	((CButton*)GetDlgItem(IDC_ARRIVAL_ANTICIPATETIME))->
		SetCheck( reg.GetBool(TEXT("Anticipate time"),false) );

	m_anticipatedTime.Init( 0, 1 );
	m_anticipatedTime.SetTime( reg.GetDWord(TEXT("Anticipated time"),3600000) );
	m_anticipatedTime.EnableWindow( IsDlgButtonChecked( IDC_ARRIVAL_ANTICIPATETIME )!=0 );

	// Set the edit box StaNo to default zero
	GetDlgItem( IDC_ARRIVAL_STANO )->SetWindowText( TEXT("0") );
	
	// Fill the list boxes with availables/arrivals
	m_ctrlAvailableList.DrawList( &m_listAvailable );
	m_ctrlArrivalList.DrawList( &m_listArrival );

	// Make resizable
	AddSzControl(IDC_IMPORT, mdNone, mdRepos);
	AddSzControl(IDC_ARRIVAL_INFO, mdRelativeRepos, mdRepos);
	AddSzControl(IDC_ARRIVAL_ANTICIPATETIME, mdRelativeRepos, mdRepos);
	AddSzControl(IDC_ARRIVAL_ANTICIPATEDTIME, mdRepos, mdRepos);

	AddSzControl(IDC_ARRIVAL_LABELTIMECUT1, mdRelativeRepos, mdRepos);
	AddSzControl(IDC_ARRIVAL_LABELTIMECUT2, mdRepos, mdRepos);
	AddSzControl(IDC_ARRIVAL_TIMECUT, mdRepos, mdRepos);

	DrawCounters();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD CListTimeTrialArrivalGross::GetUnits(CArrival *pArr)
{
	return pArr->m_unitsAtArrival;
}

void CListTimeTrialArrivalGross::SetUnits(CArrival *pArr, DWORD units)
{
	pArr->SetArrival( units, IsDlgButtonChecked(IDC_ARRIVAL_ANTICIPATETIME)!=0, m_anticipatedTime.GetTime() );
}

WORD CListTimeTrialArrivalGross::GetRank(CArrival *pArr)
{
	return pArr->m_rank;
}

void CListTimeTrialArrivalGross::SetRank(CArrival *pArr, WORD nRank)
{
	pArr->m_rank = nRank;
}

void CListTimeTrialArrivalGross::OnArrivalAnticipatetime() 
{
	m_anticipatedTime.EnableWindow( IsDlgButtonChecked( IDC_ARRIVAL_ANTICIPATETIME )!=0 );
}

void CListTimeTrialArrivalGross::OnDestroy() 
{
	CSRRegKey reg;
	if( reg.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Time trial arrival") ) == ERROR_SUCCESS )
	{
		reg.SetBool( TEXT("Anticipate time"), IsDlgButtonChecked( IDC_ARRIVAL_ANTICIPATETIME )!=0 );
		reg.SetDWord( TEXT("Anticipated time"), m_anticipatedTime.GetTime() );
	}
	CAllListArrivalPages::OnDestroy();
}

void CListTimeTrialArrivalGross::OnChangeArrivalTimecut() 
{
	m_listArrival.SetTimeCut(
		GetDlgItemInt( IDC_ARRIVAL_TIMECUT, NULL, FALSE ) );
	m_ctrlArrivalList.Invalidate();
}

void CListTimeTrialArrivalGross::OnImport() 
{
	CArrivalList listImport;
	if( listImport.Import() )
	{
		m_listAvailable.Insert( m_listArrival );
		m_listArrival.RemoveAll();

		CArrival aArr;
		CString cListNotFound;
		DWORD nState = 0;
		while( listImport.IterateSorted( nState, aArr ) )
		{
			if( m_listAvailable.Exist( aArr.m_staNo) )
			{
				CArrival aArrMove =
					m_listAvailable.GetAt( aArr.m_staNo );
				SetUnits( &aArrMove, aArr.m_units );
				m_listAvailable.Remove( aArr.m_staNo );
				m_listArrival.Insert( aArrMove );
			}
			else
			{
				// We add the faulty StaNo to the string
				if( cListNotFound.GetLength() )
					cListNotFound = cListNotFound + ", ";
				TCHAR czBuffer[10];
				_itot( aArr.m_staNo, czBuffer, 10 );
   				cListNotFound = cListNotFound + CString(czBuffer);
			}
		}

		m_listArrival.ApplyTimeTrialRanks();
		m_ctrlArrivalList.DrawList( &m_listArrival );
		m_ctrlAvailableList.DrawList( &m_listAvailable );

		// DISPLAY IMPORTED STANO's WHICH DO NOT EXIST
		if( cListNotFound.GetLength() )
			MessageBox( LoadStr( IDS_MBC_44 ) + "\r\n\r\n" + cListNotFound, LoadStr( IDS_MBT_44 ) );

		DrawCounters();
	}
}
