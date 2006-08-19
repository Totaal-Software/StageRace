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


CDlgInterval::CDlgInterval(WORD nStaNo, int nStartTime, int nInterval/* = 60000*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_TTORDER_INTERVAL, CDlgInterval::IDD)
{
	//{{AFX_DATA_INIT(CDlgInterval)
	m_interval = 0;
	m_staNo = 0;
	m_startTime = 0;
	m_useOrder = TRUE;
	//}}AFX_DATA_INIT
	m_interval = nInterval;
	m_staNo = nStaNo;
	m_startTime = nStartTime;
}


void CDlgInterval::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInterval)
	DDX_Control(pDX, IDC_STARTTIME, m_ctrl_starttime);
	DDX_Control(pDX, IDC_INTERVAL, m_ctrl_interval);
	DDX_Text(pDX, IDC_STANO, m_staNo);
	DDX_Check(pDX, IDC_USEORDER, m_useOrder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInterval, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgInterval)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInterval message handlers

BOOL CDlgInterval::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	m_ctrl_starttime.Init(0, 2);
	m_ctrl_starttime.SetTime(m_startTime);
	m_ctrl_interval.Init(0, 0);
	m_ctrl_interval.SetTime(m_interval);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInterval::OnOK() 
{

	m_interval = m_ctrl_interval.GetTime();
	m_startTime = m_ctrl_starttime.GetTime();
	
	CStageRaceWnd<CDialog>::OnOK();
}
