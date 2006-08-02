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


CDlgInterval::CDlgInterval(WORD nStaNo, int nStartTime, int nInterval/* = 60*/)
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
	DDX_Text(pDX, IDC_INTERVAL, m_interval);
	DDV_MinMaxInt(pDX, m_interval, 0, 500);
	DDX_Text(pDX, IDC_STANO, m_staNo);
	DDX_Text(pDX, IDC_STARTTIME, m_startTime);
	DDV_MinMaxInt(pDX, m_startTime, 0, 120000);
	DDX_Check(pDX, IDC_USEORDER, m_useOrder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInterval, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgInterval)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInterval message handlers
