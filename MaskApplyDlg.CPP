// MaskApplyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaskApplyDlg dialog


CMaskApplyDlg::CMaskApplyDlg(CStageRaceDoc* pDoc)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_MASKAPPLY, CMaskApplyDlg::IDD)
{
	m_pDoc = pDoc;
	//{{AFX_DATA_INIT(CMaskApplyDlg)
	//}}AFX_DATA_INIT
}


void CMaskApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaskApplyDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaskApplyDlg, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CMaskApplyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaskApplyDlg message handlers

BOOL CMaskApplyDlg::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	((CComboBox*)GetDlgItem( IDC_FIELD ))->SetCurSel( 0 );
	((CComboBox*)GetDlgItem( IDC_MATCH ))->SetCurSel( 0 );
	CheckDlgButton( IDC_STARTEMPTY, 1 );


	// Fill the text line for available masks
	// Or disable the radio button for unavailable masks
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
	{
		//Adjust the mask texts
		((CEdit*)GetDlgItem(IDC_MASK1))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1==""?LoadStr(IDS_DIV98)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1+" ("+LoadStr(IDS_DIV98)+")");
	}
	else
		GetDlgItem( IDC_MASK1 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
	{
		((CEdit*)GetDlgItem(IDC_MASK2))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2==""?LoadStr(IDS_DIV99)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2+" ("+LoadStr(IDS_DIV99)+")");
	}
	else
		GetDlgItem( IDC_MASK2 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
	{
		((CEdit*)GetDlgItem(IDC_MASK3))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3==""?LoadStr(IDS_DIV100)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3+" ("+LoadStr(IDS_DIV100)+")");
	}
	else
		GetDlgItem( IDC_MASK3 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
	{
		((CEdit*)GetDlgItem(IDC_MASK4))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4==""?LoadStr(IDS_DIV106)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4+" ("+LoadStr(IDS_DIV106)+")");
	}
	else
		GetDlgItem( IDC_MASK4 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
	{
		((CEdit*)GetDlgItem(IDC_MASK5))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5==""?LoadStr(IDS_DIV107)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5+" ("+LoadStr(IDS_DIV107)+")");
	}
	else
		GetDlgItem( IDC_MASK5 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
	{
		((CEdit*)GetDlgItem(IDC_MASK6))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6==""?LoadStr(IDS_DIV108)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6+" ("+LoadStr(IDS_DIV108)+")");
	}
	else
		GetDlgItem( IDC_MASK6 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
	{
		((CEdit*)GetDlgItem(IDC_MASK7))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7==""?LoadStr(IDS_DIV109)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7+" ("+LoadStr(IDS_DIV109)+")");
	}
	else
		GetDlgItem( IDC_MASK7 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
	{
		((CEdit*)GetDlgItem(IDC_MASK8))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8==""?LoadStr(IDS_DIV110)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8+" ("+LoadStr(IDS_DIV110)+")");
	}
	else
		GetDlgItem( IDC_MASK8 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
	{
		((CEdit*)GetDlgItem(IDC_MASK9))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9==""?LoadStr(IDS_DIV111)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9+" ("+LoadStr(IDS_DIV111)+")");
	}
	else
		GetDlgItem( IDC_MASK9 )->EnableWindow( false );

	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
	{
		((CEdit*)GetDlgItem(IDC_MASK10))->SetWindowText(
			((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10==""?LoadStr(IDS_DIV112)
				:((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10+" ("+LoadStr(IDS_DIV112)+")");
	}
	else
		GetDlgItem( IDC_MASK10 )->EnableWindow( false );

	// Select an appropriate radio button	
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
	{
		CheckDlgButton( IDC_MASK1, 1 );
	}
	else
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
		{
			CheckDlgButton( IDC_MASK2, 1 );
		}
		else
			CheckDlgButton( IDC_MASK3, 1 );

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMaskApplyDlg::OnOK() 
{
	// User pressed OK
	// Execute the masking procedure

	// FIRST DO NORMAL COMPETITORS
		CCompetitor aComp;
		DWORD nState=0;
		// While competitors exist
		// We walk through the competitor list
		while( m_pDoc->CompetitorsIterateSorted( nState, aComp ) )
		{

			// For every competitor, we involve the required
			// mask field into the check (actually check done in IsMatch)
			// Consider that IsMatch==false may not have an effect
			// on the current mask when "Add only" is checked 
			if( IsDlgButtonChecked( IDC_MASK1 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 1, 
					IsMatch( &aComp ) || ( aComp.m_mask1 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK2 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 2, 
					IsMatch( &aComp ) || ( aComp.m_mask2 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK3 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 3, 
					IsMatch( &aComp ) || ( aComp.m_mask3 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK4 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 4, 
					IsMatch( &aComp ) || ( aComp.m_mask4 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK5 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 5, 
					IsMatch( &aComp ) || ( aComp.m_mask5 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK6 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 6, 
					IsMatch( &aComp ) || ( aComp.m_mask6 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK7 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 7, 
					IsMatch( &aComp ) || ( aComp.m_mask7 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK8 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 8, 
					IsMatch( &aComp ) || ( aComp.m_mask8 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK9 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 9, 
					IsMatch( &aComp ) || ( aComp.m_mask9 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK10 )==BST_CHECKED )
				m_pDoc->CompetitorsSetMask( aComp.m_staNo, 10, 
					IsMatch( &aComp ) || ( aComp.m_mask10 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
		}

	// NEXT DO SPARE COMPETITORS
		CCompetitor* pComp;
		// Get the first spare competitor
		POSITION nPos = m_pDoc->SpareCompetitorsGetStartPosition();
		// While spare competitors exist
		while( nPos )
		{
			// We walk through the spare competitor list
			pComp = (CCompetitor*)m_pDoc->SpareCompetitorsIterate( nPos );

			if( IsDlgButtonChecked( IDC_MASK1 )==BST_CHECKED )
				pComp->SetMask( 1, 
					IsMatch( pComp ) || ( pComp->m_mask1 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK2 )==BST_CHECKED )
				pComp->SetMask( 2, 
					IsMatch( pComp ) || ( pComp->m_mask2 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK3 )==BST_CHECKED )
				pComp->SetMask( 3, 
					IsMatch( pComp ) || ( pComp->m_mask3 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK4 )==BST_CHECKED )
				pComp->SetMask( 4, 
					IsMatch( pComp ) || ( pComp->m_mask4 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK5 )==BST_CHECKED )
				pComp->SetMask( 5, 
					IsMatch( pComp ) || ( pComp->m_mask5 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK6 )==BST_CHECKED )
				pComp->SetMask( 6, 
					IsMatch( pComp ) || ( pComp->m_mask6 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK7 )==BST_CHECKED )
				pComp->SetMask( 7, 
					IsMatch( pComp ) || ( pComp->m_mask7 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK8 )==BST_CHECKED )
				pComp->SetMask( 8, 
					IsMatch( pComp ) || ( pComp->m_mask8 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK9 )==BST_CHECKED )
				pComp->SetMask( 9, 
					IsMatch( pComp ) || ( pComp->m_mask9 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
			if( IsDlgButtonChecked( IDC_MASK10 )==BST_CHECKED )
				pComp->SetMask( 10, 
					IsMatch( pComp ) || ( pComp->m_mask10 && IsDlgButtonChecked( IDC_ADDONLY ) ) );
		}

	MessageBox( LoadStr( IDS_MBC_49 ), LoadStr( IDS_MBT_49 ), MB_OK );
	
	CStageRaceWnd<CDialog>::OnOK();
}

bool CMaskApplyDlg::IsMatch( CCompetitor* pComp )
{

	// Get some settings
	int nMatch = ((CComboBox*)GetDlgItem( IDC_MATCH ))->GetCurSel();
	int nField = ((CComboBox*)GetDlgItem( IDC_FIELD ))->GetCurSel();

	CString cValue;
	// Get the value to search for
	GetDlgItemText( IDC_VALUE, cValue );
	cValue.TrimRight();

	CString cField;
	// Get the required competitor's field to search in
	switch( nField )
	{
		case 1: //Name
			cField = pComp->m_competitor;
			break;
		case 2: //Team code
			if( pComp->m_pTeam )
				cField = pComp->m_pTeam->m_code;
			else
				cField = "";
			break;
		case 3: //Country Code
			cField = pComp->m_countryCode;
			break;
		case 4: //UCI Code
			cField = pComp->m_UCICode;
			break;
		case 5: //License
			cField = pComp->m_license;
			break;
		case 6: //Category
			cField = pComp->m_category;
			break;
		default: //Startno.
			{
				TCHAR czBuffer[10];
				_itot( pComp->m_staNo, czBuffer, 10 );
				cField = "          "+CString(czBuffer);
				cField = cField.Right(10);
				cValue = "          "+cValue;
				cValue = cValue.Right(10);
			}
	}

	// Remove wildcard character positions from both strings (value/field)
	cField += CString( ' ', cValue.GetLength() );
	int n;
	while( (n = cValue.Find( '*' ))!=-1 )
	{
		cField.Delete( n );
		cValue.Delete( n );
	}
	cField.TrimRight();

	cField.MakeLower();
	cValue.MakeLower();

	// Accordingly to the type of match we use a correct operator
	switch( nMatch )
	{
		case 0: // <=
			return cField <= cValue;
		case 2: // =~
			return (cField.Find( cValue )!=-1) || (cValue.Find( cField )!=-1);
		case 3: // >=
			return cField >= cValue;
		default: // ==
			return cField == cValue;
	}
}
