// DlgArrivalInsertPositions.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgArrivalInsertPositions dialog


CDlgArrivalInsertPositions::CDlgArrivalInsertPositions(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_UNKNOWN, CDlgArrivalInsertPositions::IDD)
{
	//{{AFX_DATA_INIT(CDlgArrivalInsertPositions)
	m_count = 1;
	//}}AFX_DATA_INIT
}


void CDlgArrivalInsertPositions::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArrivalInsertPositions)
	DDX_Text(pDX, IDC_COUNT, m_count);
	DDV_MinMaxInt(pDX, m_count, 1, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgArrivalInsertPositions, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgArrivalInsertPositions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArrivalInsertPositions message handlers
