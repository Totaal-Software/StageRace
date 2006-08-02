// SprintDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSprintDat property page


CSprintDat::CSprintDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_SPRINT, CSprintDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CSprintDat)
	m_sprintpointsCount = 0;
	//}}AFX_DATA_INIT
}

CSprintDat::~CSprintDat()
{
}

void CSprintDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSprintDat)
	DDX_Text(pDX, IDC_POINTSSPRINTCOUNT, m_sprintpointsCount);
	DDV_MinMaxInt(pDX, m_sprintpointsCount, 0, 25);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSprintDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CSprintDat)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_CBN_SELCHANGE(IDC_POINTSSPRINT, OnSelchangePointssprint)
	ON_CBN_SELCHANGE(IDC_POINTSFINISH, OnSelchangePointsfinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSprintDat message handlers



CSprintDat& CSprintDat::operator =(CHalfStage &aSprintDat)
{
	WORD i, nSkipMap, nValue;

	for ( i=1, nSkipMap=1;
			i<=aSprintDat.m_sprintpointsIntermediate.GetCount(); i++, nSkipMap++)
	{
		while ( !aSprintDat.m_sprintpointsIntermediate.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_sprintpointsIntermediate.AddTail( nValue );
	}

	for ( i=1, nSkipMap=1;
			i<=aSprintDat.m_sprintpointsFinish.GetCount(); i++, nSkipMap++)
	{
		while ( !aSprintDat.m_sprintpointsFinish.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_sprintpointsFinish.AddTail( nValue );
	}

	this->m_sprintpointsCount = aSprintDat.m_sprintpointsCount;

	return *this;
}

BOOL CSprintDat::OnInitDialog() 
{
	CStageRaceWnd<CPropertyPage>::OnInitDialog();
	
	POSITION nPos;

	nPos = m_sprintpointsIntermediate.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_sprintpointsIntermediate.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->AddString( CString(chBuffer) );
	}

	nPos = m_sprintpointsFinish.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_sprintpointsFinish.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->AddString( CString(chBuffer) );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSprintDat::OnRemove() 
{
	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_sprintpointsIntermediate.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->GetCurSel();
		while( nPos && i-- )
			m_sprintpointsIntermediate.GetNext( nPos );
		// Remove value from data
		m_sprintpointsIntermediate.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->GetCurSel() );
	}

	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_sprintpointsFinish.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->GetCurSel();
		while( nPos && i-- )
			m_sprintpointsFinish.GetNext( nPos );
		// Remove value from data
		m_sprintpointsFinish.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->GetCurSel() );
	}
}

void CSprintDat::OnAdd() 
{
	CString chBuffer;
	WORD nScore;

	// Get Value
	GetDlgItem( IDC_POINTSSPRINT )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_sprintpointsIntermediate.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->AddString( chBuffer );
	}

	// Get Value
	GetDlgItem( IDC_POINTSFINISH )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_sprintpointsFinish.AddTail( nScore );
		// Update view
		((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->AddString( chBuffer );
	}

	((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->Clear();
	((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->Clear();
}

void CSprintDat::OnSelchangePointssprint() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSFINISH ))->SetCurSel(-1);
}

void CSprintDat::OnSelchangePointsfinish() 
{
	((CComboBox*)GetDlgItem( IDC_POINTSSPRINT ))->SetCurSel(-1);
}
