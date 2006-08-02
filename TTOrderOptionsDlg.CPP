// TTOrderOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTTOrderOptionsDlg dialog


CTTOrderOptionsDlg::CTTOrderOptionsDlg()
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_TTORDER_ORDEROPTIONS, CTTOrderOptionsDlg::IDD)
{
	//{{AFX_DATA_INIT(CTTOrderOptionsDlg)
	m_avoidConsecutiveTeamMembers = TRUE;
	m_leavePlacesForDroppedTeams = TRUE;
	//}}AFX_DATA_INIT
	m_individual = TRUE;
	m_team = FALSE;
}


void CTTOrderOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTTOrderOptionsDlg)
	DDX_Check(pDX, IDC_AVOIDCONSECUTIVETEAMMEMBERS, m_avoidConsecutiveTeamMembers);
	DDX_Check(pDX, IDC_LEAVEPLACESFORDROPPEDTEAMS, m_leavePlacesForDroppedTeams);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_INDIVIDUAL, m_individual );
	m_team = !m_individual;
}


BEGIN_MESSAGE_MAP(CTTOrderOptionsDlg, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CTTOrderOptionsDlg)
	ON_BN_CLICKED(IDC_TEAMS, OnTeams)
	ON_BN_CLICKED(IDC_INDIVIDUAL, OnIndividual)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTOrderOptionsDlg message handlers

void CTTOrderOptionsDlg::OnTeams() 
{
	Update();
}

void CTTOrderOptionsDlg::OnIndividual() 
{
	Update();
}

void CTTOrderOptionsDlg::Update()
{
	bool b = IsDlgButtonChecked(IDC_TEAMS)!=0;
	GetDlgItem(IDC_LEAVEPLACESFORDROPPEDTEAMS)->EnableWindow( b );
	GetDlgItem(IDC_AVOIDCONSECUTIVETEAMMEMBERS)->EnableWindow( !b );
}

BOOL CTTOrderOptionsDlg::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	Update();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
