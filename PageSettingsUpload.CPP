// PageSettingsUpload.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsUpload property page

CPageSettingsUpload::CPageSettingsUpload() : CPageSettings(CHelp::HLP_DLG_SETT_UPLOAD, CPageSettingsUpload::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsUpload)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsUpload::~CPageSettingsUpload()
{
}

void CPageSettingsUpload::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsUpload)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsUpload, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsUpload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsUpload message handlers

BOOL CPageSettingsUpload::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsUpload* pSet = (CSettingsUpload*)m_pSettings;
	SetDlgItemText( IDC_SETTINGS_HOSTADDRESS, pSet->m_hostAddress );
	SetDlgItemText( IDC_SETTINGS_USERNAME, pSet->m_username );
	SetDlgItemText( IDC_SETTINGS_PASSWORD, pSet->m_password );
	SetDlgItemText( IDC_SETTINGS_REMOTEDIR, pSet->m_remoteDir );
	SetDlgItemText( IDC_SETTINGS_MAILRECIPIENTS, pSet->m_mailRecipients );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsUpload::OnOK()
{
	CSettingsUpload* pSet = (CSettingsUpload*)m_pSettings;
	GetDlgItemText( IDC_SETTINGS_HOSTADDRESS, pSet->m_hostAddress );
	GetDlgItemText( IDC_SETTINGS_USERNAME, pSet->m_username );
	GetDlgItemText( IDC_SETTINGS_PASSWORD, pSet->m_password );
	GetDlgItemText( IDC_SETTINGS_REMOTEDIR, pSet->m_remoteDir );
	GetDlgItemText( IDC_SETTINGS_MAILRECIPIENTS, pSet->m_mailRecipients );

	CPageSettings::OnOK();
}

void CPageSettingsUpload::ArrangeEnabling()
{
	CSettingsUpload* pSet = (CSettingsUpload*)m_pSettings;
	GetDlgItem( IDC_SETTINGS_HOSTADDRESS )->
		EnableWindow( pSet->ValueGet( IDS_SETT_UPLOAD_ALLOW ) );
	GetDlgItem( IDC_SETTINGS_USERNAME )->
		EnableWindow( pSet->ValueGet( IDS_SETT_UPLOAD_ALLOW ) );
	GetDlgItem( IDC_SETTINGS_PASSWORD )->
		EnableWindow( pSet->ValueGet( IDS_SETT_UPLOAD_ALLOW ) );
	GetDlgItem( IDC_SETTINGS_REMOTEDIR )->
		EnableWindow( pSet->ValueGet( IDS_SETT_UPLOAD_ALLOW ) );
}


