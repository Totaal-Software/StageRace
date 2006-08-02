// PageGettingsGeneral.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsGeneral property page

CPageSettingsGeneral::CPageSettingsGeneral() : CPageSettings(CHelp::HLP_DLG_SETT_GENERAL, CPageSettingsGeneral::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsGeneral::~CPageSettingsGeneral()
{
}

void CPageSettingsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsGeneral, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsGeneral message handlers

BOOL CPageSettingsGeneral::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsGeneral* pSet = (CSettingsGeneral*)m_pSettings;
	SetDlgItemText( IDC_DATES, pSet->m_dates );
	SetDlgItemText( IDC_EVENTNAME, pSet->m_eventName );
	SetDlgItemText( IDC_MAINCATEGORY, pSet->m_category );
	SetDlgItemText( IDC_MASK1, pSet->m_mask1 );
	SetDlgItemText( IDC_MASK2, pSet->m_mask2 );
	SetDlgItemText( IDC_MASK3, pSet->m_mask3 );
	SetDlgItemText( IDC_MASK4, pSet->m_mask4 );
	SetDlgItemText( IDC_MASK5, pSet->m_mask5 );
	SetDlgItemText( IDC_MASK6, pSet->m_mask6 );
	SetDlgItemText( IDC_MASK7, pSet->m_mask7 );
	SetDlgItemText( IDC_MASK8, pSet->m_mask8 );
	SetDlgItemText( IDC_MASK9, pSet->m_mask9 );
	SetDlgItemText( IDC_MASK10, pSet->m_mask10 );
	SetDlgItemText( IDC_ORGANISER, pSet->m_organiser );
	SetDlgItemText( IDC_EVENTSUBTITLE, pSet->m_eventSubTitle );
	SetDlgItemText( IDC_LOCATION, pSet->m_location );

	SetDlgItemText( IDC_CLSPONSOR_GENERAL, pSet->m_cl_sponsor_general );
	SetDlgItemText( IDC_CLSPONSOR_TEAMS, pSet->m_cl_sponsor_teams );
	SetDlgItemText( IDC_CLSPONSOR_SPRINT, pSet->m_cl_sponsor_sprint );
	SetDlgItemText( IDC_CLSPONSOR_CLIMB, pSet->m_cl_sponsor_climb );
	SetDlgItemText( IDC_CLSPONSOR_POINTS, pSet->m_cl_sponsor_points );
	SetDlgItemText( IDC_CLSPONSOR_MOSTAGGRESSIVE, pSet->m_cl_sponsor_mostaggressive );
	SetDlgItemText( IDC_CLSPONSOR_MASK1, pSet->m_cl_sponsor_mask1 );
	SetDlgItemText( IDC_CLSPONSOR_MASK2, pSet->m_cl_sponsor_mask2 );
	SetDlgItemText( IDC_CLSPONSOR_MASK3, pSet->m_cl_sponsor_mask3 );
	SetDlgItemText( IDC_CLSPONSOR_MASK4, pSet->m_cl_sponsor_mask4 );
	SetDlgItemText( IDC_CLSPONSOR_MASK5, pSet->m_cl_sponsor_mask5 );
	SetDlgItemText( IDC_CLSPONSOR_MASK6, pSet->m_cl_sponsor_mask6 );
	SetDlgItemText( IDC_CLSPONSOR_MASK7, pSet->m_cl_sponsor_mask7 );
	SetDlgItemText( IDC_CLSPONSOR_MASK8, pSet->m_cl_sponsor_mask8 );
	SetDlgItemText( IDC_CLSPONSOR_MASK9, pSet->m_cl_sponsor_mask9 );
	SetDlgItemText( IDC_CLSPONSOR_MASK10, pSet->m_cl_sponsor_mask10 );
	
	return TRUE;  // return TRUE unless you Get the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsGeneral::OnOK()
{
	CSettingsGeneral* pSet = (CSettingsGeneral*)m_pSettings;
	GetDlgItemText( IDC_DATES, pSet->m_dates );
	GetDlgItemText( IDC_EVENTNAME, pSet->m_eventName );
	GetDlgItemText( IDC_MAINCATEGORY, pSet->m_category );
	GetDlgItemText( IDC_MASK1, pSet->m_mask1 );
	GetDlgItemText( IDC_MASK2, pSet->m_mask2 );
	GetDlgItemText( IDC_MASK3, pSet->m_mask3 );
	GetDlgItemText( IDC_MASK4, pSet->m_mask4 );
	GetDlgItemText( IDC_MASK5, pSet->m_mask5 );
	GetDlgItemText( IDC_MASK6, pSet->m_mask6 );
	GetDlgItemText( IDC_MASK7, pSet->m_mask7 );
	GetDlgItemText( IDC_MASK8, pSet->m_mask8 );
	GetDlgItemText( IDC_MASK9, pSet->m_mask9 );
	GetDlgItemText( IDC_MASK10, pSet->m_mask10 );
	GetDlgItemText( IDC_ORGANISER, pSet->m_organiser );
	GetDlgItemText( IDC_EVENTSUBTITLE, pSet->m_eventSubTitle );
	GetDlgItemText( IDC_LOCATION, pSet->m_location );

	GetDlgItemText( IDC_CLSPONSOR_GENERAL, pSet->m_cl_sponsor_general );
	GetDlgItemText( IDC_CLSPONSOR_TEAMS, pSet->m_cl_sponsor_teams );
	GetDlgItemText( IDC_CLSPONSOR_SPRINT, pSet->m_cl_sponsor_sprint );
	GetDlgItemText( IDC_CLSPONSOR_CLIMB, pSet->m_cl_sponsor_climb );
	GetDlgItemText( IDC_CLSPONSOR_POINTS, pSet->m_cl_sponsor_points );
	GetDlgItemText( IDC_CLSPONSOR_MOSTAGGRESSIVE, pSet->m_cl_sponsor_mostaggressive );
	GetDlgItemText( IDC_CLSPONSOR_MASK1, pSet->m_cl_sponsor_mask1 );
	GetDlgItemText( IDC_CLSPONSOR_MASK2, pSet->m_cl_sponsor_mask2 );
	GetDlgItemText( IDC_CLSPONSOR_MASK3, pSet->m_cl_sponsor_mask3 );
	GetDlgItemText( IDC_CLSPONSOR_MASK4, pSet->m_cl_sponsor_mask4 );
	GetDlgItemText( IDC_CLSPONSOR_MASK5, pSet->m_cl_sponsor_mask5 );
	GetDlgItemText( IDC_CLSPONSOR_MASK6, pSet->m_cl_sponsor_mask6 );
	GetDlgItemText( IDC_CLSPONSOR_MASK7, pSet->m_cl_sponsor_mask7 );
	GetDlgItemText( IDC_CLSPONSOR_MASK8, pSet->m_cl_sponsor_mask8 );
	GetDlgItemText( IDC_CLSPONSOR_MASK9, pSet->m_cl_sponsor_mask9 );
	GetDlgItemText( IDC_CLSPONSOR_MASK10, pSet->m_cl_sponsor_mask10 );

	CPageSettings::OnOK();
}

void CPageSettingsGeneral::ArrangeEnabling()
{
	CSettingsGeneral* pSet = (CSettingsGeneral*)m_pSettings;
	GetDlgItem( IDC_MASK1 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE1 ) );
	GetDlgItem( IDC_MASK2 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE2 ) );
	GetDlgItem( IDC_MASK3 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE3 ) );
	GetDlgItem( IDC_MASK4 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE4 ) );
	GetDlgItem( IDC_MASK5 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE5 ) );
	GetDlgItem( IDC_MASK6 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE6 ) );
	GetDlgItem( IDC_MASK7 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE7 ) );
	GetDlgItem( IDC_MASK8 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE8 ) );
	GetDlgItem( IDC_MASK9 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE9 ) );
	GetDlgItem( IDC_MASK10 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE10 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK1 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE1 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK2 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE2 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK3 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE3 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK4 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE4 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK5 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE5 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK6 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE6 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK7 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE7 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK8 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE8 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK9 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE9 ) );
	GetDlgItem( IDC_CLSPONSOR_MASK10 )->
		EnableWindow( pSet->ValueGet( IDS_SETT_GNRL_MASKS_USE10 ) );
}
