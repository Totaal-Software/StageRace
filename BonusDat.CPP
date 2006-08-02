// BonusDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBonusDat dialog


CBonusDat::CBonusDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_BONUS, CBonusDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CBonusDat)
	m_bonusesCount = 0;
	//}}AFX_DATA_INIT
}


void CBonusDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBonusDat)
	DDX_Text(pDX, IDC_BONUSSPRINTCOUNT, m_bonusesCount);
	DDV_MinMaxInt(pDX, m_bonusesCount, 0, 25);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBonusDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CBonusDat)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_CBN_SELCHANGE(IDC_BONUSSPRINT, OnSelchangeBonussprint)
	ON_CBN_SELCHANGE(IDC_BONUSFINISH, OnSelchangeBonusfinish)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_STANDARD, OnStandard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBonusDat message handlers

CBonusDat& CBonusDat::operator =(CHalfStage &aBonusDat)
{
	WORD i, nSkipMap, nValue;

	for ( i=1, nSkipMap=1;
			i<=aBonusDat.m_bonusesIntermediate.GetCount(); i++, nSkipMap++)
	{
		while ( !aBonusDat.m_bonusesIntermediate.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_bonusesIntermediate.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aBonusDat.m_bonusesFinish.GetCount(); i++, nSkipMap++)
	{
		while ( !aBonusDat.m_bonusesFinish.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_bonusesFinish.AddTail( nValue );
	}

	this->m_bonusesCount = aBonusDat.m_bonusesCount;

	return *this;
}

void CBonusDat::OnAdd() 
{
	CString chBuffer;
	WORD nScore;
	
	// Get Value
	GetDlgItem( IDC_BONUSSPRINT )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_bonusesIntermediate.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->AddString( chBuffer );
	}

	// Get Value
	GetDlgItem( IDC_BONUSFINISH )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_bonusesFinish.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->AddString( chBuffer );
	}

	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->Clear();
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->Clear();
}

void CBonusDat::OnSelchangeBonussprint() 
{
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->SetCurSel(-1);
}

void CBonusDat::OnSelchangeBonusfinish() 
{
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->SetCurSel(-1);
}

void CBonusDat::OnRemove() 
{
	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_bonusesIntermediate.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->GetCurSel();
		while( nPos && i-- )
			m_bonusesIntermediate.GetNext( nPos );
		// Remove value from data
		m_bonusesIntermediate.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_bonusesFinish.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->GetCurSel();
		while( nPos && i-- )
			m_bonusesFinish.GetNext( nPos );
		// Remove value from data
		m_bonusesFinish.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->GetCurSel() );
	}
}

BOOL CBonusDat::OnInitDialog() 
{
	CStageRaceWnd<CPropertyPage>::OnInitDialog();
	
	POSITION nPos;

	nPos = m_bonusesIntermediate.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_bonusesIntermediate.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->AddString( CString(chBuffer) );
	}

	nPos = m_bonusesFinish.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_bonusesFinish.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->AddString( CString(chBuffer) );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBonusDat::OnStandard() 
{
	m_bonusesIntermediate.RemoveAll();
	m_bonusesFinish.RemoveAll();
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->ResetContent();
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->ResetContent();

	WORD v;
	// Fill data
	v=3;
	m_bonusesIntermediate.AddTail( v );
	v=2;
	m_bonusesIntermediate.AddTail( v );
	v=1;
	m_bonusesIntermediate.AddTail( v );
	v=10;
	m_bonusesFinish.AddTail( v );
	v=6;
	m_bonusesFinish.AddTail( v );
	v=4;
	m_bonusesFinish.AddTail( v );
	// Update view
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->AddString( TEXT("3") );
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->AddString( TEXT("2") );
	((CComboBox*)GetDlgItem( IDC_BONUSSPRINT ))->AddString( TEXT("1") );
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->AddString( TEXT("10") );
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->AddString( TEXT("6") );
	((CComboBox*)GetDlgItem( IDC_BONUSFINISH ))->AddString( TEXT("4") );	
}
