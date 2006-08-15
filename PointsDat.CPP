// PointsDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointsDat property page


CPointsDat::CPointsDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_POINTS, CPointsDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CPointsDat)
	//}}AFX_DATA_INIT
}

CPointsDat::~CPointsDat()
{
}

void CPointsDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointsDat)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointsDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CPointsDat)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointsDat message handlers

CPointsDat& CPointsDat::operator =(CHalfStage &aPointsDat)
{
	WORD i, nSkipMap, nValue;

	for ( i=1, nSkipMap=1;
			i<=aPointsDat.m_pointspointsFinish.GetCount(); i++, nSkipMap++)
	{
		while ( !aPointsDat.m_pointspointsFinish.Lookup( nSkipMap, nValue ) )
			nSkipMap++ ;
		m_points.AddTail( nValue );
	}

	return *this;
}

BOOL CPointsDat::OnInitDialog() 
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

void CPointsDat::OnRemove() 
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

void CPointsDat::OnAdd() 
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
