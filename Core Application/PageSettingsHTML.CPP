// PageSettingsHTML.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsHTML property page

CPageSettingsHTML::CPageSettingsHTML() : CPageSettings(CHelp::HLP_DLG_SETT_HTML, CPageSettingsHTML::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsHTML)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsHTML::~CPageSettingsHTML()
{
}

void CPageSettingsHTML::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsHTML)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsHTML, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsHTML)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsHTML message handlers

BOOL CPageSettingsHTML::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsHTML* pSet = (CSettingsHTML*)m_pSettings;
	SetDlgItemText( IDC_SETTINGS_BGCOLOR, pSet->m_bgColor );
	SetDlgItemText( IDC_SETTINGS_TITLECOLOR, pSet->m_titleColor );
	SetDlgItemText( IDC_SETTINGS_DESCRIPTCOLOR, pSet->m_descriptColor );
	SetDlgItemText( IDC_SETTINGS_BODYCOLOR, pSet->m_bodyColor );
	SetDlgItemText( IDC_SETTINGS_EVENTLOGO, pSet->m_eventLogo );
	SetDlgItemText( IDC_SETTINGS_STYLESHEET, pSet->m_styleSheet );
	SetDlgItemText( IDC_SETTINGS_CUSTOMHTML_TOP, pSet->m_customHTMLTop );
	SetDlgItemText( IDC_SETTINGS_CUSTOMHTML_BOTTOM, pSet->m_customHTMLBottom );
	SetDlgItemInt( IDC_SETTINGS_FONTSIZE, pSet->m_fontsize );
	SetDlgItemInt( IDC_SETTINGS_COLUMNSPACING, pSet->m_columnspacing );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsHTML::OnOK()
{
	CSettingsHTML* pSet = (CSettingsHTML*)m_pSettings;
	GetDlgItemText( IDC_SETTINGS_BGCOLOR, pSet->m_bgColor );
	GetDlgItemText( IDC_SETTINGS_TITLECOLOR, pSet->m_titleColor );
	GetDlgItemText( IDC_SETTINGS_DESCRIPTCOLOR, pSet->m_descriptColor );
	GetDlgItemText( IDC_SETTINGS_BODYCOLOR, pSet->m_bodyColor );
	GetDlgItemText( IDC_SETTINGS_EVENTLOGO, pSet->m_eventLogo );
	GetDlgItemText( IDC_SETTINGS_STYLESHEET, pSet->m_styleSheet );
	GetDlgItemText( IDC_SETTINGS_CUSTOMHTML_TOP, pSet->m_customHTMLTop );
	GetDlgItemText( IDC_SETTINGS_CUSTOMHTML_BOTTOM, pSet->m_customHTMLBottom );
	pSet->m_fontsize = GetDlgItemInt( IDC_SETTINGS_FONTSIZE );
	pSet->m_columnspacing = GetDlgItemInt( IDC_SETTINGS_COLUMNSPACING );

	CPageSettings::OnOK();
}

void CPageSettingsHTML::ArrangeEnabling()
{
	CSettingsHTML* pSet = (CSettingsHTML*)m_pSettings;
	GetDlgItem( IDC_SETTINGS_STYLESHEET )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_EXTERNAL ) );

	GetDlgItem( IDC_SETTINGS_FONTSIZE )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
	GetDlgItem( IDC_SETTINGS_FONTSIZE_STATIC )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
	GetDlgItem( IDC_SETTINGS_BGCOLOR )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
	GetDlgItem( IDC_SETTINGS_TITLECOLOR )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
	GetDlgItem( IDC_SETTINGS_DESCRIPTCOLOR )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
	GetDlgItem( IDC_SETTINGS_BODYCOLOR )->
		EnableWindow( pSet->ValueGet( IDS_SETT_HTML_STYLE_INTERNAL ) );
}
