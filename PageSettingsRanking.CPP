// PageSettingsRanking.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsRanking property page

CPageSettingsRanking::CPageSettingsRanking() : CPageSettings(CHelp::HLP_DLG_SETT_RANK, CPageSettingsRanking::IDD)
{
	//{{AFX_DATA_INIT(CPageSettingsRanking)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageSettingsRanking::~CPageSettingsRanking()
{

}

void CPageSettingsRanking::DoDataExchange(CDataExchange* pDX)
{
	CPageSettings::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSettingsRanking)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSettingsRanking, CPageSettings)
	//{{AFX_MSG_MAP(CPageSettingsRanking)
	ON_EN_CHANGE(IDC_SETTINGSRANKING_BUNCHSIZE, OnChangeSettingsrankingBunchsize)
	ON_EN_CHANGE(IDC_SETTINGSRANKING_DEPTHINTERMEDIATE, OnChangeSettingsrankingDepthintermediate)
	ON_EN_CHANGE(IDC_SETTINGSRANKING_DEPTHSTAGE, OnChangeSettingsrankingDepthstage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsRanking message handlers

BOOL CPageSettingsRanking::OnInitDialog() 
{
	CPageSettings::OnInitDialog();
	
	CSettingsRanking* pSet = (CSettingsRanking*)m_pSettings;
	SetDlgItemInt ( IDC_SETTINGSRANKING_BUNCHSIZE, pSet->m_bunchSize );
	SetDlgItemInt ( IDC_SETTINGSRANKING_DEPTHSTAGE, pSet->m_maxDepthFinish );
	SetDlgItemInt ( IDC_SETTINGSRANKING_DEPTHINTERMEDIATE, pSet->m_maxDepthSprint );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSettingsRanking::OnOK()
{
	CSettingsRanking* pSet = (CSettingsRanking*)m_pSettings;
	pSet->m_bunchSize = GetDlgItemInt ( IDC_SETTINGSRANKING_BUNCHSIZE );
	pSet->m_maxDepthFinish = GetDlgItemInt ( IDC_SETTINGSRANKING_DEPTHSTAGE );
	pSet->m_maxDepthSprint = GetDlgItemInt ( IDC_SETTINGSRANKING_DEPTHINTERMEDIATE );

	CPageSettings::OnOK();
}

void CPageSettingsRanking::OnChangeSettingsrankingBunchsize() 
{
	CString cNumber;
	((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_BUNCHSIZE ))->GetWindowText( cNumber );
	if( _ttoi( cNumber ) < 2 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_BUNCHSIZE ))->SetWindowText( TEXT("2") );
	if( _ttoi( cNumber ) > 6 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_BUNCHSIZE ))->SetWindowText( TEXT("6") );
}

void CPageSettingsRanking::ArrangeEnabling()
{
	CSettingsRanking* pSet = (CSettingsRanking*)m_pSettings;
	GetDlgItem( IDC_SETTINGSRANKING_BUNCHSIZE )->
		EnableWindow( pSet->ValueGet( IDS_SETT_RANK_TEAMS_GENERATE ) );
}

void CPageSettingsRanking::OnChangeSettingsrankingDepthintermediate() 
{
	CString cNumber;
	((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHINTERMEDIATE ))->GetWindowText( cNumber );
	if( _ttoi( cNumber ) < 1 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHINTERMEDIATE ))->SetWindowText( TEXT("1") );
	if( _ttoi( cNumber ) > 100 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHINTERMEDIATE ))->SetWindowText( TEXT("100") );
}

void CPageSettingsRanking::OnChangeSettingsrankingDepthstage() 
{
	CString cNumber;
	((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHSTAGE ))->GetWindowText( cNumber );
	if( _ttoi( cNumber ) < 1 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHSTAGE ))->SetWindowText( TEXT("1") );
	if( _ttoi( cNumber ) > 65536 )
		((CWnd*) GetDlgItem( IDC_SETTINGSRANKING_DEPTHSTAGE ))->SetWindowText( TEXT("65535") );
}
