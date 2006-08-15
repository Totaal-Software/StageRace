// MostAggressiveDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMostAggressiveDat property page


CMostAggressiveDat::CMostAggressiveDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_MOSTAGGRESSIVE, CMostAggressiveDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CMostAggressiveDat)
	//}}AFX_DATA_INIT
}

CMostAggressiveDat::~CMostAggressiveDat()
{
}

void CMostAggressiveDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMostAggressiveDat)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMostAggressiveDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CMostAggressiveDat)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMostAggressiveDat message handlers

CMostAggressiveDat& CMostAggressiveDat::operator =(CHalfStage &aMostAggressiveDat)
{
	WORD i, nSkipMap, nValue;

	for ( i=1, nSkipMap=1;
			i<=aMostAggressiveDat.m_mostaggressivepoints.GetCount(); i++, nSkipMap++)
	{
		while ( !aMostAggressiveDat.m_mostaggressivepoints.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_points.AddTail( nValue );
	}

	return *this;
}

BOOL CMostAggressiveDat::OnInitDialog() 
{
	CStageRaceWnd<CPropertyPage>::OnInitDialog();
	
	POSITION nPos;

	nPos = m_points.GetHeadPosition();
	while( nPos )
	{
		TCHAR chBuffer[10];

		_itot( m_points.GetNext( nPos ), chBuffer, 10 );
		((CComboBox*)GetDlgItem( IDC_POINTS ))->AddString( CString(chBuffer) );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMostAggressiveDat::OnRemove() 
{
	// Look whether an item is selected
	if( ((CComboBox*)GetDlgItem( IDC_POINTS ))->GetCurSel() != CB_ERR )
	{
		// Search value in data
		POSITION nPos = m_points.GetHeadPosition();
		int i=((CComboBox*)GetDlgItem( IDC_POINTS ))->GetCurSel();
		while( nPos && i-- )
			m_points.GetNext( nPos );
		// Remove value from data
		m_points.RemoveAt( nPos );
		// Remove value from view
		((CComboBox*)GetDlgItem( IDC_POINTS ))->DeleteString(
			((CComboBox*)GetDlgItem( IDC_POINTS ))->GetCurSel() );
	}
}

void CMostAggressiveDat::OnAdd() 
{
	CString chBuffer;
	WORD nScore;

	// Get Value
	GetDlgItem( IDC_POINTS )->GetWindowText(chBuffer);
	// Look whether allowed value
	nScore = _ttoi( chBuffer );
	if( nScore )
	{
		// Fill data
		m_points.AddTail( nScore );
		// Update view
		CString c;
		c.Format(TEXT("%d"), nScore);
		((CComboBox*)GetDlgItem( IDC_POINTS ))->AddString( c );
	}

	((CComboBox*)GetDlgItem( IDC_POINTS ))->SetEditSel(0,-1);
	((CComboBox*)GetDlgItem( IDC_POINTS ))->Clear();
}
