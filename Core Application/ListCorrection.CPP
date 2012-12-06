// ListCorrection.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCorrection property page

CListCorrection::CListCorrection(	const CAvailableList* pListAvailable,
									const CCorrectionList* pListCorrection,
									const CCompetitorList* pListCompetitor/*=NULL*/
								)
								: CAllListPages(
									CHelp::HLP_DLG_LSTP_CORR,
									CListCorrection::IDD,
									NULL,
									pListAvailable,
									NULL )
{
	m_listCorrection = *pListCorrection;
	m_ctrlCorrectionList.AddCompetitorSource( pListCompetitor );
	//{{AFX_DATA_INIT(CListCorrection)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CListCorrection::DoDataExchange(CDataExchange* pDX)
{
	CAllListPages::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCorrection)
	DDX_Control(pDX, IDC_CORRECTION_PENALTY, m_penalty);
	DDX_Control(pDX, IDC_CORRECTION_STANO, m_staNo);
	DDX_Control(pDX, IDC_CORRECTION_BONUS, m_bonus);
	DDX_Control(pDX, IDC_CORRECTION_LISTCORRECTION, m_ctrlCorrectionList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListCorrection, CAllListPages)
	//{{AFX_MSG_MAP(CListCorrection)
	ON_BN_CLICKED(IDC_SUBMIT, OnListcorrectionAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnListcorrectionDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CORRECTION_LISTCORRECTION, OnItemchangedListcorrection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCorrection message handlers

BOOL CListCorrection::OnInitDialog() 
{
	CAllListPages::OnInitDialog();
	
	// Make resizable
	AddSzControl(IDC_CORRECTION_LISTCORRECTION, mdResize, mdResize);
	AddSzControl(IDC_CORRECTION_GROUPBOX, mdResize, mdRepos);

	AddSzControl(IDC_CORRECTION_LABELSTANO, mdNone, mdRepos);
	AddSzControl(IDC_CORRECTION_LABELBONUS, mdNone, mdRepos);
	AddSzControl(IDC_CORRECTION_LABELPENALTY, mdNone, mdRepos);

	AddSzControl(IDC_CORRECTION_STANO, mdNone, mdRepos);
	AddSzControl(IDC_CORRECTION_BONUS, mdNone, mdRepos);
	AddSzControl(IDC_CORRECTION_PENALTY, mdNone, mdRepos);

	AddSzControl(IDC_REMOVE, mdRepos, mdRepos);
	AddSzControl(IDC_SUBMIT, mdRepos, mdRepos);

	// Make validation of entered StaNo possible
	m_staNo.AddStaNoObjectList( &m_listAvailable );

	m_bonus.Init( 0, 0 );
	m_penalty.Init( 0, 0 );
	m_ctrlCorrectionList.Init( 0, CArrivalListCtrl::ALT_CORRECTION );

	// Fill the list box with arrivals
	m_ctrlCorrectionList.DrawList( &m_listCorrection );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// Declass and submit

void CListCorrection::OnListcorrectionAdd() 
{
	if( m_staNo.Exist() )
	{
		CArrival New;
		New.m_staNo = m_staNo.GetValue();
		New.m_bonus = (WORD)(m_bonus.GetTime()/1000);
		New.m_penalty = (WORD)(m_penalty.GetTime()/1000);

		if( m_ctrlCorrectionList.GetSelectedCount()>1 )
		{
			// If at least one correction for it
			if( New.m_bonus || New.m_penalty )
			{
				// Search the selected item
				POSITION nPos = m_ctrlCorrectionList.GetFirstSelectedItemPosition();
				while( nPos )
				{
					int i = m_ctrlCorrectionList.GetNextSelectedItem(nPos);
					// Change the StaNo for every selected item
					New.m_staNo = (WORD)m_ctrlCorrectionList.GetItemData( i );
					// Add to the document
					m_listCorrection.Insert( New );
					// Add to the view
					m_ctrlCorrectionList.Draw( &New );
				}
			}
		}
		else
		{
			// If a StaNo and at least one correction for it
			if( New.m_staNo && (New.m_bonus || New.m_penalty) )
			{
				// Add to the document
				m_listCorrection.Insert( New );
				// Add to the view
				m_ctrlCorrectionList.Draw( &New );
			}
		}
	}
}

void CListCorrection::OnListcorrectionDelete() 
{
	POSITION nPos = m_ctrlCorrectionList.GetFirstSelectedItemPosition();
	if( nPos )
	{
		while( nPos )
		{
			// Lookup item
			int nItem = m_ctrlCorrectionList.GetNextSelectedItem(nPos);
			// Get corresponding StaNo
			WORD nStaNo = (WORD)m_ctrlCorrectionList.GetItemData( nItem );
			// Remove from the correction list
			m_listCorrection.Remove( nStaNo );
			// Delete it from the view (corrections)
			m_ctrlCorrectionList.DeleteItem( nItem );
			// Get the newly first selected item for the next iteration
			nPos = m_ctrlCorrectionList.GetFirstSelectedItemPosition();
		}
		// No multiple selection possible at this point,
		// so enable all edit controls again
		m_staNo.EnableWindow( TRUE );
	}
	else
		// Nothing to delete
		MessageBeep( MB_ICONASTERISK );
}

/////////////////////////////////////////////////////////////////////////////
// CListCorrection other functions

BOOL CListCorrection::PreTranslateMessage(MSG* pMsg) 
{
	// Check for [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_RETURN )
	{
		OnListcorrectionAdd();
		if( (GetFocus()==GetDlgItem(IDC_CORRECTION_STANO)) ||
			(GetFocus()==GetDlgItem(IDC_CORRECTION_BONUS)) ||
			(GetFocus()==GetDlgItem(IDC_CORRECTION_PENALTY)) )
		{
			((CEdit*)GetFocus())->SetSel(0,-1);
		}

		return TRUE;
	}
	
	return CAllListPages::PreTranslateMessage(pMsg);
}

void CListCorrection::OnItemchangedListcorrection(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// First check if anything selected at all
	if( m_ctrlCorrectionList.GetSelectedCount() )
	{
		CArrival aArrival = 
			m_listCorrection.GetAt( m_ctrlCorrectionList.GetSelected() );

		// Copy its properties to the edit boxes
			// StaNo
			m_staNo.SetValue( aArrival.m_staNo );

			// Times
			m_bonus.SetTime( aArrival.m_bonus*1000 );
			m_penalty.SetTime( aArrival.m_penalty*1000 );
	}

	// Disable some boxes in case of multiple selection
	if( m_ctrlCorrectionList.GetSelectedCount()>1 )
	{
		m_staNo.EnableWindow( FALSE );
	}
	else
	{
		m_staNo.EnableWindow( TRUE );
	}

	*pResult = 0;
}
