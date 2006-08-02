// GetPwd.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetPwd dialog


CGetPwd::CGetPwd()
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_PASSWORD, CGetPwd::IDD)
{
	//{{AFX_DATA_INIT(CGetPwd)
	m_accessPassword = _T("");
	//}}AFX_DATA_INIT
}


void CGetPwd::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetPwd)
	DDX_Text(pDX, IDC_PASSWORD, m_accessPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetPwd, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CGetPwd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetPwd message handlers
