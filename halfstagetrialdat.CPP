// HalfStageTrialDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHalfStageTrialDat property page


CHalfStageTrialDat::CHalfStageTrialDat() : CStageRaceWnd<CPropertyPage>(CHelp::HLP_DLG_CONF_HALFSTAGE, CHalfStageTrialDat::IDD,(UINT)0)
{
	//{{AFX_DATA_INIT(CHalfStageTrialDat)
	m_date = _T("");
	m_distance = 0;
	m_openingHour = _T("");
	m_title = _T("");
	m_rounds = 0;
	m_exclude = FALSE;
	m_oneForTeamsClass = FALSE;
	m_timeCut = 0;
	m_allowLateChangesStartOrder = TRUE;
	//}}AFX_DATA_INIT
	m_timeTrialType = ST_TT_GROSS;
}

CHalfStageTrialDat::~CHalfStageTrialDat()
{
}

void CHalfStageTrialDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CPropertyPage>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHalfStageTrialDat)
	DDX_Text(pDX, IDC_DATE, m_date);
	DDX_Text(pDX, IDC_DISTANCE, m_distance);
	DDV_MinMaxInt(pDX, m_distance, 1, 1000000);
	DDX_Text(pDX, IDC_OPENINGHOUR, m_openingHour);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Text(pDX, IDC_ROUNDS, m_rounds);
	DDV_MinMaxInt(pDX, m_rounds, 1, 999);
	DDX_Check(pDX, IDC_EXCLUDE, m_exclude);
	DDX_Check(pDX, IDC_ONEFORTEAMSCLASS, m_oneForTeamsClass);
	DDX_Text(pDX, IDC_TIMECUT, m_timeCut);
	DDV_MinMaxInt(pDX, m_timeCut, 0, 75);
	DDX_Check(pDX, IDC_TIMETRIALSTARTLATECHANGE, m_allowLateChangesStartOrder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHalfStageTrialDat, CStageRaceWnd<CPropertyPage>)
	//{{AFX_MSG_MAP(CHalfStageTrialDat)
	ON_BN_CLICKED(IDC_TIMETRIAL, OnTimetrial)
	ON_BN_CLICKED(IDC_TIMETRIAL_NETTIMES, OnTimetrial)
	ON_BN_CLICKED(IDC_TIMETRIAL_GROSSTIMES, OnTimetrial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHalfStageTrialDat message handlers

CHalfStageTrialDat & CHalfStageTrialDat::operator =(CHalfStage &aHS)
{
	this->m_distance = aHS.m_distance;
	this->m_openingHour = aHS.m_openingHour;
	this->m_rounds = aHS.m_rounds;
	this->m_title = aHS.m_title;
	this->m_stageType = aHS.m_stageType;
	this->m_exclude = aHS.m_exclude;
	this->m_allowLateChangesStartOrder = aHS.m_allowLateChangesStartOrder;
	this->m_oneForTeamsClass = aHS.m_oneForTeamsClass;
	this->m_timeCut = aHS.m_arrival.GetTimeCut();
	return *this;
}

BOOL CHalfStageTrialDat::OnInitDialog() 
{
	CStageRaceWnd<CPropertyPage>::OnInitDialog();

	if( m_stageType!=ST_NORMAL )
		m_timeTrialType=m_stageType;

	CheckDlgButton( IDC_TIMETRIAL, m_stageType!=ST_NORMAL );
	CheckDlgButton( IDC_TIMETRIAL_NETTIMES, m_timeTrialType==ST_TT_NET );
	CheckDlgButton( IDC_TIMETRIAL_GROSSTIMES, m_timeTrialType==ST_TT_GROSS );

	GetDlgItem( IDC_ROUNDS )->EnableWindow( m_stageType==ST_NORMAL );
	GetDlgItem( IDC_TIMETRIAL_NETTIMES )->EnableWindow( m_stageType!=ST_NORMAL );
	GetDlgItem( IDC_TIMETRIAL_GROSSTIMES )->EnableWindow( m_stageType!=ST_NORMAL );
	GetDlgItem( IDC_TIMETRIALSTARTLATECHANGE )->EnableWindow( m_stageType!=ST_NORMAL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHalfStageTrialDat::OnTimetrial() 
{
	if( IsDlgButtonChecked( IDC_TIMETRIAL_NETTIMES ) )
		m_timeTrialType = ST_TT_NET;
	else
		m_timeTrialType = ST_TT_GROSS;
	if( !IsDlgButtonChecked( IDC_TIMETRIAL ) )
		m_stageType = ST_NORMAL;
	else
		m_stageType = m_timeTrialType;

	GetDlgItem( IDC_ROUNDS )->EnableWindow( m_stageType==ST_NORMAL );
	GetDlgItem( IDC_TIMETRIAL_NETTIMES )->EnableWindow( m_stageType!=ST_NORMAL );
	GetDlgItem( IDC_TIMETRIAL_GROSSTIMES )->EnableWindow( m_stageType!=ST_NORMAL );
	GetDlgItem( IDC_TIMETRIALSTARTLATECHANGE )->EnableWindow( m_stageType!=ST_NORMAL );
}
