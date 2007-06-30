// DlgInterval.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInterval dialog


CDlgInterval::CDlgInterval(WORD nStaNoFirst, int nStartTimeFirst, int nPositionFirst,
						   WORD nStaNoLast, int nStartTimeLast, int nPositionLast, int nInterval/* = 60000*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_TTORDER_INTERVAL, CDlgInterval::IDD)
{
	//{{AFX_DATA_INIT(CDlgInterval)
	m_interval = 0;
	m_useOrder = TRUE;
	//}}AFX_DATA_INIT
	m_interval = nInterval;
	
	m_startTimeFirst = nStartTimeFirst;
	m_staNoFirst = nStaNoFirst;
	m_positionFirst = nPositionFirst;
	m_startTimeLast = nStartTimeLast;
	m_staNoLast = nStaNoLast;
	m_positionLast = nPositionLast;
	m_ascending = true;
}


void CDlgInterval::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInterval)
	DDX_Control(pDX, IDC_STARTTIME, m_ctrl_starttime);
	DDX_Control(pDX, IDC_INTERVAL, m_ctrl_interval);
	DDX_Check(pDX, IDC_USEORDER, m_useOrder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInterval, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgInterval)
	ON_BN_CLICKED(IDC_ASCENDING, OnAscending)
	ON_BN_CLICKED(IDC_DESCENDING, OnDescending)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInterval message handlers

BOOL CDlgInterval::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	m_ctrl_starttime.Init(0, 2);
	m_ctrl_interval.Init(0, 0);
	m_ctrl_interval.SetTime(m_interval);

	CheckDlgButton(IDC_ASCENDING, TRUE);

	SetFirstLast();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInterval::OnOK() 
{

	m_interval = m_ctrl_interval.GetTime();
	m_startTime = m_ctrl_starttime.GetTime();

	CStageRaceWnd<CDialog>::OnOK();
}

void CDlgInterval::OnAscending() 
{
	m_ascending = true;
	SetFirstLast();
}

void CDlgInterval::OnDescending() 
{
	m_ascending = false;
	SetFirstLast();
}

void CDlgInterval::SetFirstLast()
{
	if( m_ascending )
	{
		GetDlgItem(IDC_STATICFIRST)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATICLAST)->ShowWindow(SW_HIDE);
		SetDlgItemInt(IDC_STANO, m_staNoFirst);
		SetDlgItemInt(IDC_POSITION, m_positionFirst);
		m_ctrl_starttime.SetTime(m_startTimeFirst);
	}
	else
	{
		GetDlgItem(IDC_STATICFIRST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICLAST)->ShowWindow(SW_SHOW);
		SetDlgItemInt(IDC_STANO, m_staNoLast);
		SetDlgItemInt(IDC_POSITION, m_positionLast);
		m_ctrl_starttime.SetTime(m_startTimeLast);
	}
}