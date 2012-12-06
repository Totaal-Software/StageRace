// ReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog


CReportDlg::CReportDlg(CString cReport)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_LSTP_ARR_REPORT, CReportDlg::IDD)
{
	//{{AFX_DATA_INIT(CReportDlg)
	m_Report = _T("");
	//}}AFX_DATA_INIT
	m_Report = cReport;
}


void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportDlg)
	DDX_Text(pDX, IDC_CONTENTS, m_Report);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportDlg, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CReportDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers
