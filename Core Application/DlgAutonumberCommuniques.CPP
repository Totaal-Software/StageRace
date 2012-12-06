// DlgAutonumberCommuniques.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutonumberCommuniques dialog


CDlgAutonumberCommuniques::CDlgAutonumberCommuniques(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_UNKNOWN, CDlgAutonumberCommuniques::IDD)
{
	//{{AFX_DATA_INIT(CDlgAutonumberCommuniques)
	m_crossoutlists = FALSE;
	m_signinlists = FALSE;
	m_stanosortedgeneral = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAutonumberCommuniques::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutonumberCommuniques)
	DDX_Check(pDX, IDC_AUTONUMBER_CROSSOUTLISTS, m_crossoutlists);
	DDX_Check(pDX, IDC_AUTONUMBER_SIGNINLISTS, m_signinlists);
	DDX_Check(pDX, IDC_AUTONUMBER_STANOSORTEDGENERAL, m_stanosortedgeneral);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutonumberCommuniques, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgAutonumberCommuniques)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutonumberCommuniques message handlers
