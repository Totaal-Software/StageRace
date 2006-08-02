// MountainDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMountainDat property page


CMountainDat::CMountainDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_CLIMB, CMountainDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CMountainDat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMountainDat::~CMountainDat()
{
}

void CMountainDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMountainDat)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMountainDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CMountainDat)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_CBN_SELCHANGE(IDC_POINTSCLIMB1, OnSelchangePointsclimb1)
	ON_CBN_SELCHANGE(IDC_POINTSCLIMB2, OnSelchangePointsclimb2)
	ON_CBN_SELCHANGE(IDC_POINTSCLIMB3, OnSelchangePointsclimb3)
	ON_CBN_SELCHANGE(IDC_POINTSCLIMB4, OnSelchangePointsclimb4)
	ON_LBN_SELCHANGE(IDC_LISTCLIMB, OnSelchangeListclimb)
	ON_CBN_SELCHANGE(IDC_POINTSCLIMBHC, OnSelchangePointsclimbhc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMountainDat message handlers

CMountainDat& CMountainDat::operator =(CHalfStage &aMountainDat)
{
	WORD i, nSkipMap, nValue;

	for ( i=1, nSkipMap=1;
			i<=aMountainDat.m_climbpointshc.GetCount(); i++, nSkipMap++)
	{
		while ( !aMountainDat.m_climbpointshc.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_climbpointshc.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aMountainDat.m_climbpoints1.GetCount(); i++, nSkipMap++)
	{
		while ( !aMountainDat.m_climbpoints1.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_climbpoints1.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aMountainDat.m_climbpoints2.GetCount(); i++, nSkipMap++)
	{
		while ( !aMountainDat.m_climbpoints2.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_climbpoints2.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aMountainDat.m_climbpoints3.GetCount(); i++, nSkipMap++)
	{
		while ( !aMountainDat.m_climbpoints3.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_climbpoints3.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aMountainDat.m_climbpoints4.GetCount(); i++, nSkipMap++)
	{
		while ( !aMountainDat.m_climbpoints4.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_climbpoints4.AddTail( nValue );
	}

	POSITION nPos;
	nPos = aMountainDat.m_climbsorder.GetHeadPosition();
	while( nPos )
	{
		WORD nValue;
		nValue = aMountainDat.m_climbsorder.GetNext( nPos );
		this->m_climbs.AddTail( nValue );
	}

	return *this;
}

BOOL CMountainDat::OnInitDialog() 
{
	CStageRaceWnd<CPropertyPage>::OnInitDialog();
	
	POSITION nPos;

	nPos = m_climbpointshc.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_climbpointshc.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->AddString( CString(chBuffer) );
	}

	nPos = m_climbpoints1.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_climbpoints1.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->AddString( CString(chBuffer) );
	}

	nPos = m_climbpoints2.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_climbpoints2.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->AddString( CString(chBuffer) );
	}

	nPos = m_climbpoints3.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_climbpoints3.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->AddString( CString(chBuffer) );
	}

	nPos = m_climbpoints4.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_climbpoints4.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->AddString( CString(chBuffer) );
	}
	

	nPos = m_climbs.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		int n = m_climbs.GetNext( nPos );
		if( n>0 )
		{
			_itot( n, chBuffer, 10 );
			((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->AddString( CString(chBuffer) );
		}
		else
			((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->AddString( TEXT("HC") );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMountainDat::OnAdd() 
{
	CString chBuffer;
	WORD nScore;
	
	// Get Value
	GetDlgItem( IDC_POINTSCLIMBHC )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_climbpointshc.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->AddString( chBuffer );
	}
	
	// Get Value
	GetDlgItem( IDC_POINTSCLIMB1 )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_climbpoints1.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->AddString( chBuffer );
	}
	
	// Get Value
	GetDlgItem( IDC_POINTSCLIMB2 )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_climbpoints2.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->AddString( chBuffer );
	}
	
	// Get Value
	GetDlgItem( IDC_POINTSCLIMB3 )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_climbpoints3.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->AddString( chBuffer );
	}
	
	// Get Value
	GetDlgItem( IDC_POINTSCLIMB4 )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_climbpoints4.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->AddString( chBuffer );
	}
	
	// Get Value
	GetDlgItem( IDC_LIST_HC1234 )->GetWindowText(chBuffer);
	// Look whether allowed value
	if( chBuffer.CompareNoCase(TEXT("hc"))==0 )
		nScore = 0;
	else
		nScore = _ttoi( chBuffer );
	if( ((nScore>0) && (nScore<=4)) || (chBuffer.CompareNoCase(TEXT("hc"))==0) )
	{
		if( m_climbs.GetCount()>=25 )
			MessageBox( LoadStr( IDS_MBC_28 ), LoadStr( IDS_MBT_28 ), MB_OK );
		else
		{
			// Fill data
			m_climbs.AddTail( nScore );
			// Update view
			chBuffer.MakeUpper();
			((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->AddString( chBuffer );
		}
	}

	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->Clear();
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->Clear();
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->Clear();
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->Clear();
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->Clear();
	((CComboBox*)GetDlgItem( IDC_LIST_HC1234 ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_LIST_HC1234 ))->Clear();
}

void CMountainDat::OnRemove() 
{
	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_climbpointshc.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->GetCurSel();
		while( nPos && i-- )
			m_climbpointshc.GetNext( nPos );
		// Remove value from data
		m_climbpointshc.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_climbpoints1.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->GetCurSel();
		while( nPos && i-- )
			m_climbpoints1.GetNext( nPos );
		// Remove value from data
		m_climbpoints1.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_climbpoints2.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->GetCurSel();
		while( nPos && i-- )
			m_climbpoints2.GetNext( nPos );
		// Remove value from data
		m_climbpoints2.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_climbpoints3.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->GetCurSel();
		while( nPos && i-- )
			m_climbpoints3.GetNext( nPos );
		// Remove value from data
		m_climbpoints3.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_climbpoints4.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->GetCurSel();
		while( nPos && i-- )
			m_climbpoints4.GetNext( nPos );
		// Remove value from data
		m_climbpoints4.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->GetCurSel() != CB_ERR )
	{
		// Search value in data

		POSITION nPos = m_climbs.GetHeadPosition();
		int i=((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->GetCurSel();
		while( nPos && i-- )
			m_climbs.GetNext( nPos );
		// Remove value from data
		m_climbs.RemoveAt( nPos );
		// Remove value from view
		((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->DeleteString(
			((CListBox*)GetDlgItem( IDC_LISTCLIMB ))->GetCurSel() );
	}

}

void CMountainDat::OnSelchangePointsclimb1() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_LISTCLIMB ))->SetCurSel(-1);
}

void CMountainDat::OnSelchangePointsclimb2() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_LISTCLIMB ))->SetCurSel(-1);	
}

void CMountainDat::OnSelchangePointsclimb3() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_LISTCLIMB ))->SetCurSel(-1);
}

void CMountainDat::OnSelchangePointsclimb4() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_LISTCLIMB ))->SetCurSel(-1);
}

void CMountainDat::OnSelchangeListclimb() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMBHC ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetCurSel(-1);
}

void CMountainDat::OnSelchangePointsclimbhc() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB1 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB2 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB3 ))->SetCurSel(-1);
	((CComboBox*)GetDlgItem( IDC_POINTSCLIMB4 ))->SetCurSel(-1);
}
