// FullStageTrialDat.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullStageTrialDat dialog


CFullStageTrialDat::CFullStageTrialDat(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_CONF_STAGE, CFullStageTrialDat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFullStageTrialDat)
	m_date = _T("");
	//}}AFX_DATA_INIT
}


void CFullStageTrialDat::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFullStageTrialDat)
	DDX_Text(pDX, IDC_DATE, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFullStageTrialDat, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CFullStageTrialDat)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullStageTrialDat message handlers

CFullStageTrialDat& CFullStageTrialDat::operator =(CFullStage & aFullStage)
{
	this->m_date = aFullStage.m_date;

	return *this;
}
