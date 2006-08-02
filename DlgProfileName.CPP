// DlgProfileName.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileName dialog


CDlgProfileName::CDlgProfileName(CString name)
	: CStageRaceWnd<CDialog>(CHelp::HLP_UNKNOWN, CDlgProfileName::IDD)
{
	//{{AFX_DATA_INIT(CDlgProfileName)
	m_name = _T("");
	m_indicator_access = FALSE;
	m_indicator_general = FALSE;
	m_indicator_html = FALSE;
	m_indicator_publication = FALSE;
	m_indicator_ranking = FALSE;
	m_indicator_upload = FALSE;
	//}}AFX_DATA_INIT
	m_name = name;
}


void CDlgProfileName::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProfileName)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Check(pDX, IDC_INDICATOR_ACCESS, m_indicator_access);
	DDX_Check(pDX, IDC_INDICATOR_GENERAL, m_indicator_general);
	DDX_Check(pDX, IDC_INDICATOR_HTML, m_indicator_html);
	DDX_Check(pDX, IDC_INDICATOR_PUBLICATION, m_indicator_publication);
	DDX_Check(pDX, IDC_INDICATOR_RANKING, m_indicator_ranking);
	DDX_Check(pDX, IDC_INDICATOR_UPLOAD, m_indicator_upload);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProfileName, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CDlgProfileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileName message handlers

void CDlgProfileName::OnOK() 
{
	UpdateData();
	CString test( m_name );
	test.TrimLeft();
	test.TrimRight();
	if( !test.IsEmpty() && (test.FindOneOf(TEXT("\\/:*?\"<>|."))==-1) )
		CStageRaceWnd<CDialog>::OnOK();
	else
		MessageBeep(MB_ICONASTERISK);
}
