// PageSettingsPublication.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsPublication property page

CPageSettingsPublication::CPageSettingsPublication() : CPageSettings(CHelp::HLP_DLG_SETT_PUBL, CPageSettingsPublication::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsPublication)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsPublication::~CPageSettingsPublication()
{
}

void CPageSettingsPublication::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsPublication)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsPublication, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsPublication)
	ON_BN_CLICKED(IDC_SETTINGS_REMOVEREQUIREDLANGUAGE, OnSettingsRemoverequiredlanguage)
	ON_BN_CLICKED(IDC_SETTINGS_ADDREQUIREDLANGUAGE, OnSettingsAddrequiredlanguage)
	ON_EN_CHANGE(IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS, OnChangeSettingsCrossoutteamnamesmodulus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsPublication message handlers

BOOL CPageSettingsPublication::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsPublication* pSet = (CSettingsPublication*)m_pSettings;
	SetDlgItemText( IDC_SETTINGS_SIGNATURE, pSet->m_signature );
	SetDlgItemText( IDC_NAME, pSet->m_companyName );
	SetDlgItemText( IDC_URL, pSet->m_companyURL );
	SetDlgItemText( IDC_SETTINGS_MASK1ICON, pSet->m_mask1icon );
	SetDlgItemText( IDC_SETTINGS_MASK2ICON, pSet->m_mask2icon );
	SetDlgItemText( IDC_SETTINGS_MASK3ICON, pSet->m_mask3icon );
	SetDlgItemInt ( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS, pSet->m_modulusCrossOutTeamNames );
	SetDlgItemText( IDC_SETTINGS_SAMEGAP, pSet->m_sameGap );
	
	// Populate listboxes
	for( int i = 0 ; i < pSet->m_requiredLanguages.GetSize() ; i++ )
	{
		((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->
			AddString( CString(pSet->m_requiredLanguages.GetAt(i).ac) );
	}

	MultiLanguagePopulateListBox(
		(CComboBox*)GetDlgItem( IDC_SETTINGS_LANGUAGESSOURCE ) );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsPublication::OnOK()
{
	CSettingsPublication* pSet = (CSettingsPublication*)m_pSettings;
	GetDlgItemText( IDC_SETTINGS_SIGNATURE, pSet->m_signature );
	GetDlgItemText( IDC_NAME, pSet->m_companyName );
	GetDlgItemText( IDC_URL, pSet->m_companyURL );
	GetDlgItemText( IDC_SETTINGS_MASK1ICON, pSet->m_mask1icon );
	GetDlgItemText( IDC_SETTINGS_MASK2ICON, pSet->m_mask2icon );
	GetDlgItemText( IDC_SETTINGS_MASK3ICON, pSet->m_mask3icon );
	pSet->m_modulusCrossOutTeamNames = GetDlgItemInt ( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS );
	GetDlgItemText( IDC_SETTINGS_SAMEGAP, pSet->m_sameGap );

	CPageSettings::OnOK();
}

void CPageSettingsPublication::OnSettingsRemoverequiredlanguage() 
{
	CSettingsPublication* pSet = (CSettingsPublication*)m_pSettings;

	int sel = ((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->GetCurSel();
	if( sel != LB_ERR )
	{
		((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->DeleteString( sel );

		pSet->m_requiredLanguages.RemoveAll();
		for( int i = 0; i < ((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->GetCount(); i++ )
		{
			CString cTemp;
			((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->GetText( i, cTemp );
			CMultiLanguage::LANGUAGE lang;
			lang.ac[0] = (char)cTemp[0];
			lang.ac[1] = (char)cTemp[1];
			lang.ac[2] = (char)'\0';
			pSet->m_requiredLanguages.Add( lang );
		}
	}
}

void CPageSettingsPublication::OnSettingsAddrequiredlanguage() 
{
	CSettingsPublication* pSet = (CSettingsPublication*)m_pSettings;

	CString cEntered;
	GetDlgItemText( IDC_SETTINGS_LANGUAGESSOURCE, cEntered );

	cEntered.MakeUpper();
	cEntered = cEntered.SpanIncluding( TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") );

	if( cEntered.GetLength() >= 2 )
	{
		((CListBox*)GetDlgItem( IDC_SETTINGS_REQUIREDLANGUAGES ))->AddString(cEntered.Left(2));
		CMultiLanguage::LANGUAGE lang;
		lang.ac[0] = (char)cEntered[0];
		lang.ac[1] = (char)cEntered[1];
		lang.ac[2] = (char)'\0';
		pSet->m_requiredLanguages.Add( lang );
	}
	else
		MessageBeep( MB_ICONASTERISK );
}

void CPageSettingsPublication::OnChangeSettingsCrossoutteamnamesmodulus() 
{
	CString cNumber;
	((CWnd*) GetDlgItem( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS ))->GetWindowText( cNumber );
	if( _ttoi( cNumber ) < 3 )
		((CWnd*) GetDlgItem( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS ))->SetWindowText( TEXT("3") );
	if( _ttoi( cNumber ) > 12 )
		((CWnd*) GetDlgItem( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS ))->SetWindowText( TEXT("12") );
}

void CPageSettingsPublication::ArrangeEnabling()
{
	CSettingsPublication* pSet = (CSettingsPublication*)m_pSettings;
	GetDlgItem( IDC_NAME )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG ) );
	GetDlgItem( IDC_URL )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG ) );
	GetDlgItem( IDC_SETTINGS_SIGNATURE )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE ) &&
			pSet->ValueGet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_OWN ) );
	GetDlgItem( IDC_SETTINGS_MASK1ICON )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1 )||pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1 ) );
	GetDlgItem( IDC_SETTINGS_MASK2ICON )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2 )||pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2 ) );
	GetDlgItem( IDC_SETTINGS_MASK3ICON )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3 )||pSet->ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3 ) );
	GetDlgItem( IDC_SETTINGS_CROSSOUTTEAMNAMESMODULUS )->
		EnableWindow( pSet->ValueGet( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES ) );
	GetDlgItem( IDC_SETTINGS_SAMEGAP )->
		EnableWindow(
			pSet->ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_NEWGAP ) ||
			pSet->ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_NEWGAP ) ||
			pSet->ValueGet( IDS_SETT_PUBL_COLS_TEAM_NEWGAP ) );

	if( !pSet->ValueGet( IDS_SETT_PUBL_DISTANCES_KM ) &&
		!pSet->ValueGet( IDS_SETT_PUBL_DISTANCES_MILE ) )
	{
		// This guarantees that always one distance type is selected
		m_ctrlBinarySettings.SetCheckState( IDS_SETT_PUBL_DISTANCES_KM );
		m_ctrlBinarySettings.RedrawWindow();
		pSet->ValueSet( IDS_SETT_PUBL_DISTANCES_KM, true );
	}
}

