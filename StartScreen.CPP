// StartScreen.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStartScreen dialog


CStartScreen::CStartScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CStartScreen::IDD, pParent)
{
	m_pMainFrame = NULL;
	//{{AFX_DATA_INIT(CStartScreen)
	//}}AFX_DATA_INIT

	// White background
	m_brush.CreateSolidBrush(RGB(255, 255, 255)); // color white brush 
}


void CStartScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartScreen)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStartScreen, CDialog)
	//{{AFX_MSG_MAP(CStartScreen)
	ON_WM_CTLCOLOR()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartScreen message handlers

BOOL CStartScreen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Place a long version no. on the dialog
	((CWnd*)GetDlgItem( IDC_VERSION_NUMBER ))->SetWindowText( ((CStageRaceApp*)AfxGetApp())->m_key.GetNiceLongVersion() );
#ifdef _DEBUG
//	MoveWindow(1000,1000,10,10);
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStartScreen::OnOK() 
{
	CDialog::OnOK();
	DestroyWindow();

 	CCommandLineInfo cmdInfo;
 	AfxGetApp()->ParseCommandLine(cmdInfo);
 	if( cmdInfo.m_bShowSplash )
 	{
 		CTipDlg dlg;
		if( dlg.m_bStartup )
			dlg.DoModal();
 	}

	if( m_pMainFrame )
		m_pMainFrame->SetFocus();
}

HBRUSH CStartScreen::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// We return to alternative brush in order to obtain the coloured background
	return m_brush;
}

void CStartScreen::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	BringWindowToTop();	
	if( IsWindow( m_msgBoxHardwareKey.m_hWnd ) )
	{
		m_msgBoxHardwareKey.SetFocus();
		m_msgBoxHardwareKey.BringWindowToTop();
	}
	else
		GetDlgItem(IDOK)->SetFocus();
}

void CStartScreen::SetMainFrame(CWnd *pMainFrame)
{
	m_pMainFrame = pMainFrame;
}

void CStartScreen::DoMsgBoxHardwareKey()
{
	m_msgBoxHardwareKey.Create(this);
}

void CStartScreen::OnCancel()
{
	OnOK();
}
