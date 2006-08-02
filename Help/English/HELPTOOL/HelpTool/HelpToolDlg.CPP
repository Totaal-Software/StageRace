// HelpToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HelpTool.h"
#include "Process.h"
#include "HelpToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpToolDlg dialog


CHelpToolDlg::CHelpToolDlg(CWnd* pParent/* = NULL*/)
	: CDialog(CHelpToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpToolDlg)
	m_source = _T("..\\..\\..\\rawtopics");
	m_targethtml = _T("..\\..\\..\\topics");
	m_targetdoc = _T("..\\..\\..\\doctopics");
	m_includes = _T("..\\..\\..\\includes");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CHelpToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpToolDlg)
	DDX_Control(pDX, IDC_REPORTING, m_reporting);
	DDX_Text(pDX, IDC_SOURCE, m_source);
	DDX_Text(pDX, IDC_TARGETHTML, m_targethtml);
	DDX_Text(pDX, IDC_TARGETDOC, m_targetdoc);
	DDX_Text(pDX, IDC_INCLUDES, m_includes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpToolDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpToolDlg)
	ON_BN_CLICKED(IDC_GO, OnGo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpToolDlg message handlers

BOOL CHelpToolDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHelpToolDlg::OnGo() 
{
	UpdateData();
	Process::Go( m_source, m_targethtml, m_targetdoc, m_includes );

//<LINK REL="stylesheet" HREF="../css/stagerace.css" TYPE="text/css">

}

