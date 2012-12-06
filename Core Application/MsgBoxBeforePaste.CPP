// MsgBoxBeforePaste.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxBeforePaste dialog


CMsgBoxBeforePaste::CMsgBoxBeforePaste()
	: CDialog(CMsgBoxBeforePaste::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMsgBoxBeforePaste)
	m_withoutTeamInput = FALSE;
	//}}AFX_DATA_INIT
}


void CMsgBoxBeforePaste::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgBoxBeforePaste)
	DDX_Check(pDX, IDC_PASTE_WITHOUTTEAMINPUT, m_withoutTeamInput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgBoxBeforePaste, CDialog)
	//{{AFX_MSG_MAP(CMsgBoxBeforePaste)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxBeforePaste message handlers
