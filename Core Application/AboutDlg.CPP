// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg() : CStageRaceWnd<CDialog>(CHelp::HLP_DLG_ABOUT, CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_hardwareKey			= _T("");
	m_name					= _T("");
	m_version				= _T("");
	m_hardwareKeyContents	= _T("");
	m_evaluation			= _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_TOTAALLOGO, m_totaallogo);
	DDX_Control(pDX, IDC_WEBSITE, m_website);
	DDX_Control(pDX, IDC_EMAIL, m_email);
	DDX_Text(pDX, IDC_ABOUT_HARDWAREKEY, m_hardwareKey);
	DDX_Text(pDX, IDC_ABOUT_NAME, m_name);
	DDX_Text(pDX, IDC_ABOUT_VERSION, m_version);
	DDX_Text(pDX, IDC_ABOUT_HARDWAREKEYCONTENTS, m_hardwareKeyContents);
	DDX_Text(pDX, IDC_ABOUT_DEMO, m_evaluation);
	DDX_Control(pDX, IDC_LICENSE, m_license);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_ABOUT_TOTAALLOGO, OnAboutTotaallogo)
	ON_BN_CLICKED(IDC_CREDITS, OnCredits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::OnAboutTotaallogo() 
{
	OnCredits();
}

void CAboutDlg::OnCredits() 
{
	CCredits dlgCredits;
	dlgCredits.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	//Load the license resource
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);

	CString strResourceURL;
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		strResourceURL.Format(_T("res://%s/%d"), lpszModule, IDR_LICENSE);
		m_license.Navigate(strResourceURL, 0, 0, 0, 0);
	}
	delete [] lpszModule;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
