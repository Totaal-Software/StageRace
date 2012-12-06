// PageSettingsAccess.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsAccess property page

CPageSettingsAccess::CPageSettingsAccess() : CPageSettings(CHelp::HLP_DLG_SETT_ACCESS, CPageSettingsAccess::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsAccess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsAccess::~CPageSettingsAccess()
{
}

void CPageSettingsAccess::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsAccess)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsAccess, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsAccess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsAccess message handlers

BOOL CPageSettingsAccess::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsAccess* pSet = (CSettingsAccess*)m_pSettings;
	SetDlgItemText( IDC_PASSWORD, pSet->m_password );
	SetDlgItemText( IDC_KEYNO, ((CStageRaceApp*) AfxGetApp())->m_key.HaspID() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsAccess::OnOK()
{
	CSettingsAccess* pSet = (CSettingsAccess*)m_pSettings;
	GetDlgItemText( IDC_PASSWORD, pSet->m_password );
	GetDlgItemText( IDC_KEYNO, pSet->m_key );

	CPageSettings::OnOK();
}

void CPageSettingsAccess::ArrangeEnabling()
{
	CSettingsAccess* pSet = (CSettingsAccess*)m_pSettings;
	GetDlgItem( IDC_PASSWORD )->
		EnableWindow( pSet->ValueGet( IDS_SETT_ACCESS_PASSWORD ) );
}
