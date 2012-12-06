// Credits.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog


CCredits::CCredits(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_CREDITS, CCredits::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCredits)
	//}}AFX_DATA_INIT

	// White background
	m_brush.CreateSolidBrush(RGB(255, 255, 255)); // color white brush 
}

void CCredits::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCredits)
	DDX_Control(pDX, IDC_CREDITS, m_credits);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCredits, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CCredits)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCredits message handlers

HBRUSH CCredits::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// We return to alternative brush in order to obtain the coloured background
	return m_brush;
}

BOOL CCredits::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();
	
	//Load the license resource
	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);

	CString strResourceURL;
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
	{
		strResourceURL.Format(_T("res://%s/%d"), lpszModule, IDR_CREDITS);
		m_credits.Navigate(strResourceURL, 0, 0, 0, 0);
	}
	delete [] lpszModule;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
