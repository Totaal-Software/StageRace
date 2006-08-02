// MsgBoxIndexHtml.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxIndexHtml dialog


CMsgBoxIndexHtml::CMsgBoxIndexHtml(CString cTitle)
	: CDialog(CMsgBoxIndexHtml::IDD, NULL)
{
	//{{AFX_DATA_INIT(CMsgBoxIndexHtml)
	m_futureSuppress = FALSE;
	//}}AFX_DATA_INIT
	m_title = cTitle;
}


void CMsgBoxIndexHtml::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgBoxIndexHtml)
	DDX_Check(pDX, IDC_FUTURESUPPRESS, m_futureSuppress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgBoxIndexHtml, CDialog)
	//{{AFX_MSG_MAP(CMsgBoxIndexHtml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxIndexHtml message handlers

BOOL CMsgBoxIndexHtml::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Set up the proper title
	CString cExisting;
	GetWindowText( cExisting );
	SetWindowText( cExisting + "\"" + m_title + "\"" );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
