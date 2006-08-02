// ListArrival.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListArrival property page

CListArrival::CListArrival( int nAccuracy,
							const CAvailableList* pListAvailable,
							const CArrivalList* pListArrival,
							bool bRankOnly/*=false*/,
							const CCompetitorList* pListCompetitor/*=NULL*/,
							UINT nIDLabel/*=NULL*/,
							CHelp::HELP_TOPIC helptopic/*=HLP_DLG_LSTP_ARR*/
						)
						: CAllListArrivalPages(
							helptopic,
							CListArrival::IDD,
							nIDLabel,
							nAccuracy,
							pListAvailable,
							pListArrival,
							pListCompetitor )
{
	m_bRankOnly = bRankOnly;
	//{{AFX_DATA_INIT(CListArrival)
	//}}AFX_DATA_INIT
}

void CListArrival::DoDataExchange(CDataExchange* pDX)
{
	CAllListArrivalPages::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListArrival)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListArrival, CAllListArrivalPages)
	//{{AFX_MSG_MAP(CListArrival)
	ON_BN_CLICKED(IDC_SUBMIT, OnSubmit)
	ON_BN_CLICKED(IDC_ARRIVAL_FUNCTIONS, OnArrivalFunctions)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_CHECK, OnArrivalFunctionsCheck)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_1, OnArrivalFunctionsGroupt1)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_2, OnArrivalFunctionsGroupt2)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_3, OnArrivalFunctionsGroupt3)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_IMPORT, OnArrivalFunctionsImport)
	ON_BN_CLICKED(IDC_DECLASS, OnDeclass)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_REMOVEGAPS, OnArrivalFunctionsRemovegaps)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_REMOVE1XSECONDS, OnArrivalFunctionsRemove1xseconds)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_EN_CHANGE(IDC_ARRIVAL_TIMECUT, OnChangeArrivalTimecut)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_INSERTPOSITION, OnArrivalFunctionsInsertposition)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_INSERTPOSITIONS, OnArrivalFunctionsInsertpositions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListArrival message handlers

/////////////////////////////////////////////////////////////////////////////
// Functions menu

void CListArrival::OnArrivalFunctions() 
{
	// SHOW THE FUNCTIONS MENU

	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_ARRIVALFUNCTIONS );
	// Retrieve the position of the button by which this menu is requested
	RECT posButton;
	GetDlgItem( IDC_ARRIVAL_FUNCTIONS )->GetWindowRect( &posButton );
	// Show the menu
	aMenu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
						posButton.left + (posButton.right-posButton.left)/2, // Middle of button
						posButton.top + (posButton.bottom-posButton.top)/2,
						this );
}

void CListArrival::OnArrivalFunctionsCheck() 
{
	CString checkResult;
	m_listArrival.CheckIntegrity( &checkResult );

	CReportDlg dlgRep(checkResult);
	dlgRep.DoModal();
}

void CListArrival::OnArrivalFunctionsGroupt1() 
{
	m_listArrival.ApplyGroupTime(1);
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

void CListArrival::OnArrivalFunctionsGroupt2() 
{
	m_listArrival.ApplyGroupTime(2);
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

void CListArrival::OnArrivalFunctionsGroupt3() 
{
	m_listArrival.ApplyGroupTime(3);
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

void CListArrival::OnArrivalFunctionsImport() 
{
	CArrivalList listImport;
	if( listImport.Import() )
	{
		m_listAvailable.Insert( m_listArrival );
		m_listArrival = listImport;

		CArrival aArr;
		CString cListNotFound;
		DWORD nState = 0;
		while( listImport.IterateSorted( nState, aArr ) )
		{
			if( m_listAvailable.Exist( aArr.m_staNo) )
			{
				m_listAvailable.Remove( aArr.m_staNo );
			}
			else
			{
				m_listArrival.Remove( aArr.m_staNo );

				// We add the faulty StaNo to the string
				if( cListNotFound.GetLength() )
					cListNotFound = cListNotFound + ", ";
				TCHAR czBuffer[10];
				_itot( aArr.m_staNo, czBuffer, 10 );
   				cListNotFound = cListNotFound + CString(czBuffer);
			}
		}

		m_ctrlArrivalList.DrawList( &m_listArrival );
		m_ctrlAvailableList.DrawList( &m_listAvailable );

		// DISPLAY IMPORTED STANO's WHICH DO NOT EXIST
		if( cListNotFound.GetLength() )
			MessageBox( LoadStr( IDS_MBC_44 ) + "\r\n\r\n" + cListNotFound, LoadStr( IDS_MBT_44 ) );

		DrawCounters();
	}
}

void CListArrival::OnArrivalFunctionsRemove1xseconds() 
{
	m_listArrival.Remove1XSeconds();
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

void CListArrival::OnArrivalFunctionsRemovegaps() 
{
	m_listArrival.RemoveGapsRanking();
	m_ctrlArrivalList.DrawList( &m_listArrival );
}

/////////////////////////////////////////////////////////////////////////////
// Integrity check

void CListArrival::OnOK() 
{
	CString checkResult;
	if( m_bRankOnly || !m_listArrival.CheckIntegrity( &checkResult ) )
	{
		CReportDlg dlgRep(checkResult);
		dlgRep.DoModal();
	}
	CAllListArrivalPages::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// Declass and submit

void CListArrival::OnDeclass() 
{
	POSITION nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
	if( nPos )
	{
		bool bAllAllowed = true;
		while( nPos )
		{
			// Lookup item
			int nItem = m_ctrlArrivalList.GetNextSelectedItem(nPos);
			// Get corresponding StaNo
			WORD nStaNo = (WORD)m_ctrlArrivalList.GetItemData( nItem );
			if( ChangesAllowed(nStaNo) )
			{
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
			else
				bAllAllowed = false;
		}
		// No multiple selection possible at this point,
		// so enable all edit controls again
		GetDlgItem( IDC_ARRIVAL_RANK )->EnableWindow( TRUE );
		GetDlgItem( IDC_ARRIVAL_STANO )->EnableWindow( TRUE );

		DrawCounters();

		// Make error if not all changes were allowed due to competitors
		// already being ranked in this time trial
		if( !bAllAllowed )
			MessageBox( LoadStr( IDS_MBC_50 ),
						LoadStr( IDS_MBT_50 ),
						MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );
	}
	else
		// Nothing to delete
		MessageBeep( MB_ICONASTERISK );
}

void CListArrival::OnSubmit() 
{
	// When single selection
	if( m_staNo.IsWindowEnabled() )
	{
		CString cRank;
		GetDlgItem( IDC_ARRIVAL_RANK )->GetWindowText( cRank );
		WORD nRank = _ttoi( cRank );

		if( nRank && m_staNo.Exist() )
		{
			if( ChangesAllowed(m_staNo.GetValue()) )
			{
				CArrival aArr;
				if( m_listAvailable.Exist( m_staNo.GetValue() ) )
				{
					aArr = m_listAvailable.GetAt( m_staNo.GetValue() );
					m_listAvailable.Remove( aArr.m_staNo );
					m_ctrlAvailableList.Clear( aArr.m_staNo );

					// Prepare the dialog boxes for the next cycle
					// Set the rank to current+1
					TCHAR czBuffer[10];
					_itot( _ttoi( cRank )+1, czBuffer, 10 );
					GetDlgItem( IDC_ARRIVAL_RANK )->SetWindowText( czBuffer );
					m_staNo.SetValue(0);
				}
				else if( m_listArrival.Exist( m_staNo.GetValue() ) )
				{
					aArr = m_listArrival.GetAt( m_staNo.GetValue() );
				}
				else
				{
					// Should be illegal, but provide an error beep anyway
					MessageBeep( MB_ICONASTERISK );
					return;
				}
				SetRank(&aArr, _ttoi( cRank ));
				SetUnits( &aArr, m_time.GetTime() );

				m_listArrival.Insert( aArr );
				m_ctrlArrivalList.Draw( &aArr );

				// Prepare the dialog boxes for the next cycle
				// Set the focus to StaNo and select the contents
				m_staNo.SetFocus();
				m_staNo.SetSel( 0, -1, FALSE );

				DrawCounters();
			}
			else
				MessageBox( LoadStr( IDS_MBC_47 ),
							LoadStr( IDS_MBT_47 ),
							MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );
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
			while( nPos )
			{
				// Lookup item
				int nItem = m_ctrlArrivalList.GetNextSelectedItem(nPos);
				// Get corresponding StaNo
				WORD nStaNo = (WORD)m_ctrlArrivalList.GetItemData( nItem );
				if( ChangesAllowed(nStaNo) )
				{
					// Get the matching arrival
					CArrival aArr = m_listArrival.GetAt( nStaNo );
					// Set the time property right
					SetUnits( &aArr, t );
					// Store the changed arrival
					m_listArrival.Insert( aArr );
					// Draw the item again
					m_ctrlArrivalList.Draw( &aArr );
				}
				// Get the newly first selected item for the next iteration
				nPos = m_ctrlArrivalList.GetFirstSelectedItemPosition();
			}
		}
		else
			MessageBeep( MB_ICONASTERISK );
	}
}

/////////////////////////////////////////////////////////////////////////////
// Various

BOOL CListArrival::PreTranslateMessage(MSG* pMsg)
{
	// Check for [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN )
	{
		switch( pMsg->wParam )
		{
			case VK_RETURN:

				// If we're in the rank or stano box, we first want the user to go
				// to the time boxes
				if( (GetFocus() == GetDlgItem( IDC_ARRIVAL_RANK ))
					||
					(GetFocus() == GetDlgItem( IDC_ARRIVAL_STANO ))
					)
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
			case VK_INSERT:
				{
	 				CSRRegKey reg1;
	 				reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
	 				if( reg1.GetBool(TEXT("UseInsDelForArrivals"),false) )
	 				{
	 					Insert(1);
	 				}
				}
				return TRUE;
			case VK_DELETE:
				{
	 				CSRRegKey reg1;
	 				reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
	 				if( reg1.GetBool(TEXT("UseInsDelForArrivals"),false) )
	 				{
	 					OnDeclass();
	 				}
				}
				return TRUE;
		}
	}
	
	return CAllListArrivalPages::PreTranslateMessage(pMsg);
}

BOOL CListArrival::OnInitDialog() 
{
	CAllListArrivalPages::OnInitDialog();

	m_time.Init( m_accuracy?2:3, 1, true );
	if( m_bRankOnly )
	{
		m_ctrlAvailableList.Init( m_accuracy, CArrivalListCtrl::ALT_AVAILABLERANKONLY );
		m_ctrlArrivalList.Init( m_accuracy, CArrivalListCtrl::ALT_ARRIVALRANKONLY );
		m_time.ShowWindow( SW_HIDE );
		GetDlgItem(IDC_ARRIVAL_LABELTIME)->ShowWindow( SW_HIDE );
		GetDlgItem(IDC_ARRIVAL_TIMECUT)->ShowWindow( SW_HIDE );
		GetDlgItem(IDC_ARRIVAL_LABELTIMECUT1)->ShowWindow( SW_HIDE );
		GetDlgItem(IDC_ARRIVAL_LABELTIMECUT2)->ShowWindow( SW_HIDE );

		LONG er;
		CSRRegKey reg;
		er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
		if( er == ERROR_SUCCESS )
		{
			if( reg.GetBool( TEXT("HideFunctionsForSprints"), false ) )
				GetDlgItem(IDC_ARRIVAL_FUNCTIONS)->ShowWindow( SW_HIDE );
		}
	}
	else
	{
		m_ctrlAvailableList.Init( m_accuracy, CArrivalListCtrl::ALT_AVAILABLE );
		m_ctrlArrivalList.Init( m_accuracy, CArrivalListCtrl::ALT_ARRIVAL, &m_listArrival );
		
		// Arrange the time cut display
		SetDlgItemInt( IDC_ARRIVAL_TIMECUT, m_listArrival.GetTimeCut() );
	}

	// Set the edit boxes StaNo and Rank to default zero
	GetDlgItem( IDC_ARRIVAL_STANO )->SetWindowText( TEXT("0") );
	GetDlgItem( IDC_ARRIVAL_RANK )->SetWindowText( TEXT("0") );
	
	// Fill the list boxes with availables/arrivals
	m_ctrlAvailableList.DrawList( &m_listAvailable );
	m_ctrlArrivalList.DrawList( &m_listArrival );

	// Make resizable
	AddSzControl(IDC_ARRIVAL_LABELRANK, mdRelative, mdRepos);
	AddSzControl(IDC_ARRIVAL_RANK, mdRelative, mdRepos);

	AddSzControl(IDC_ARRIVAL_FUNCTIONS, mdNone, mdRepos);

	AddSzControl(IDC_ARRIVAL_LABELTIMECUT1, mdNone, mdRepos);
	AddSzControl(IDC_ARRIVAL_LABELTIMECUT2, mdNone, mdRepos);
	AddSzControl(IDC_ARRIVAL_TIMECUT, mdNone, mdRepos);

	DrawCounters();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD CListArrival::GetUnits(CArrival *pArr)
{
	return pArr->m_units;
}

void CListArrival::SetUnits(CArrival *pArr, DWORD units)
{
	if( m_bRankOnly )
		pArr->m_units = 0;
	else
		pArr->m_units = units;
}

WORD CListArrival::GetRank(CArrival *pArr)
{
	return pArr->m_rank;
}

void CListArrival::SetRank(CArrival *pArr, WORD nRank)
{
	pArr->m_rank = nRank;
}

BOOL CListArrival::ChangesAllowed(WORD nStaNo)
{
	return true;
}

void CListArrival::OnEditSelectall() 
{
	m_ctrlArrivalList.SelectAll();
}

void CListArrival::OnChangeArrivalTimecut() 
{
	m_listArrival.SetTimeCut(
		GetDlgItemInt( IDC_ARRIVAL_TIMECUT, NULL, FALSE ) );
	m_ctrlArrivalList.Invalidate();
}

void CListArrival::OnArrivalFunctionsInsertposition() 
{
	Insert(1);
}

void CListArrival::Insert(unsigned int n)
{
	int selectionmark1, selectionmark2;
	selectionmark1 = selectionmark2 =
		m_ctrlArrivalList.GetSelectionMark();

	// Check if something selected to base the procedure on
	if( selectionmark1 != -1 )
	{
		CArrival aArr;
		// Handle items while we are not at the end of our list
		while( selectionmark1 < m_ctrlArrivalList.GetItemCount() )
		{
			// Get the corresponding arrival element
			aArr = m_listArrival.GetAt( 
				m_ctrlArrivalList.GetItemData(selectionmark1) );

			// Update it accordingly to the parameter to this method
			aArr.m_rank += n;

			// Put the arrival element back
			m_listArrival.Insert( aArr );

			// Go on with the next item
			selectionmark1++;
		}

		// Redraw the entire list
		m_ctrlArrivalList.DrawList( &m_listArrival );
		// Make sure the starting item from where we started inserting,
		// just now, is for sure visible
		m_ctrlArrivalList.SetSelectionMark(selectionmark2);
		m_ctrlArrivalList.EnsureVisible(selectionmark2, FALSE);
		LV_ITEM item;

		item.mask		= LVIF_STATE;
		item.iItem		= selectionmark2;
		item.iSubItem	= 0;
		item.state		= LVIS_SELECTED;
		item.stateMask	= 2;

		m_ctrlArrivalList.SetItemState(selectionmark2, &item);
	}
}

void CListArrival::OnArrivalFunctionsInsertpositions() 
{
	// Check if something selected to base the procedure on
	if( m_ctrlArrivalList.GetSelectionMark() != -1 )
	{
		// Ask user how many positions to insert
		CDlgArrivalInsertPositions dlg;
		if( dlg.DoModal()==IDOK )
		{
			Insert( dlg.m_count );
		}
	}
}
