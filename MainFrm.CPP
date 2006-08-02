///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: AppWizard
// Primary date: 01-01-2000
// Filename: MainFrm.h
// Description: Implementation file for the CMainFrame class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
// 06-01-2000	SV	Alle variabelenamen aangepast volgens nieuwe conventie
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame


BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_VIEW_TLBAR_STANDARD, OnViewTlbarStandard)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TLBAR_STANDARD, OnUpdateViewTlbarStandard)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STATUS_BAR, OnUpdateViewStatusBar)
	ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
	ON_WM_DESTROY()
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_COMMAND(ID_TOOLS_SPEEDCALCULATOR, OnToolsSpeedcalculator)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_SPEEDCALCULATOR, OnUpdateToolsSpeedcalculator)
	ON_COMMAND(ID_TOOLS_TIMECALCULATOR, OnToolsTimecalculator)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TIMECALCULATOR, OnUpdateToolsTimecalculator)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_HELP_LICENSE, OnHelpLicense)
	ON_COMMAND(ID_HELP_SEARCH, OnHelpSearch)
	ON_COMMAND(ID_HELP_TIPOFTHEDAY, OnHelpTipoftheday)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_THREAD_MESSAGE(WM_USER_COM_OPERATORMESSAGE, ShowOperatorMessage)
	//}}AFX_MSG_MAP
	// Global help commands

	// If the message remains unprocessed, then the default Help is invoked
	// This is done by sending a ID_DEFAULT_HELP command to the main window
	// This command is generally mapped to CWinApp::OnHelpIndex
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pDlgCurrentlyRunning	= NULL;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Standard toolbar
	if (!m_wndStandardToolBar.CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS,CBRS_ALIGN_ANY   ) ||
		!m_wndStandardToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	// ReBar
	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndStandardToolBar, LoadStr( IDR_MAINFRAME ) ) )
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	// Status bar
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Background image for MDICLIENT area
	VERIFY( m_wndClient.SubclassWindow( m_hWndMDIClient ) );
	// Background image
	m_wndClient.SetBitmap( IDB_MDICLIENT );
	m_wndClient.SetDisplayMode( CMDIClient::dispCenter );

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, LoadStr( IDS_DIV26 ));
	}

	m_wndStandardToolBar.SetMainFrame(this);
	SetFocusStartScreen();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}
void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// Arrange for the About box
	if((nID & 0xFFF0) == IDM_ABOUTBOX)
		((CStageRaceApp*)AfxGetApp())->OnAppAbout();
	else
		CMDIFrameWnd::OnSysCommand(nID, lParam);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	RestoreWindowState(cs);

	return CMDIFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnDestroy() 
{
	StoreWindowState();
	CMDIFrameWnd::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// View menu handlers

void CMainFrame::OnViewTlbarStandard() 
{
	BOOL bVisible = ((m_wndStandardToolBar.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndStandardToolBar, !bVisible, FALSE);
}

void CMainFrame::OnUpdateViewTlbarStandard(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(( m_wndStandardToolBar.GetStyle() & WS_VISIBLE) !=0 );
}

void CMainFrame::OnViewStatusBar() 
{
	m_wndStatusBar.ToggleShow(this);
}

void CMainFrame::OnUpdateViewStatusBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_wndStatusBar.IsVisible()!=0 );
}

/////////////////////////////////////////////////////////////////////////////
// Tools menu handlers

void CMainFrame::OnToolsSpeedcalculator() 
{
	CString czToolFile = "\"" + GetModulePathName() + "SRSpeed.exe\"";

	// Create a process with the application and document we want
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset (&si, 0, sizeof (si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;

	if( !CreateProcess(
				NULL,
				czToolFile.GetBuffer(0),
				NULL,
				NULL,
				FALSE,
				NORMAL_PRIORITY_CLASS,
				NULL,
				NULL,
				&si,
				&pi
			) )
		MessageBox( LoadStr( IDS_MBC_43 ), LoadStr( IDS_MBT_43 ) );
}

void CMainFrame::OnUpdateToolsSpeedcalculator(CCmdUI* pCmdUI) 
{
	CFileFind objCheckFile;
	pCmdUI->Enable(
			objCheckFile.FindFile( GetModulePathName() + "SRSpeed.exe" )
		);
}

void CMainFrame::OnToolsTimecalculator() 
{
	CString czToolFile = "\"" + GetModulePathName() + "SRCalc.exe\"";

	// Create a process with the application and document we want
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset (&si, 0, sizeof (si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;

	if( !CreateProcess(
				NULL,
				czToolFile.GetBuffer(0),
				NULL,
				NULL,
				FALSE,
				NORMAL_PRIORITY_CLASS,
				NULL,
				NULL,
				&si,
				&pi
			) )
		MessageBox( LoadStr( IDS_MBC_43 ), LoadStr( IDS_MBT_43 ) );
}

void CMainFrame::OnUpdateToolsTimecalculator(CCmdUI* pCmdUI) 
{
	CFileFind objCheckFile;
	pCmdUI->Enable(
			objCheckFile.FindFile( GetModulePathName() + "SRCalc.exe" )
		);
}

void CMainFrame::OnToolsOptions() 
{
	COptionsDlg objDlg;
	objDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// Help menu handlers

void CMainFrame::OnHelpContents() 
{
	CHelp::Contents();
}

void CMainFrame::OnHelpSearch() 
{
	CHelp::Search();
}

void CMainFrame::OnHelpLicense() 
{
	CMainFrame* pMainWnd		= (CMainFrame*)AfxGetApp()->m_pMainWnd;

	// We create a new child frame
	CMDIChildWnd* pFrame		= new CMDIChildWnd();

	// We create a context describing the contents of the child frame (doc/view)
	CCreateContext objContext;
	objContext.m_pCurrentDoc	= new CLicense;//NULL; // No document
	objContext.m_pNewViewClass	= RUNTIME_CLASS( CStaticPresentationView );
	objContext.m_pNewDocTemplate= NULL;
	objContext.m_pLastView		= pMainWnd->GetActiveFrame() ? pMainWnd->GetActiveFrame()->GetActiveView() : NULL;
	objContext.m_pCurrentFrame	= pMainWnd->GetActiveFrame();

	// We load the frame as defined above
	if ( !pFrame->LoadFrame( IDR_MAINFRAME, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, pMainWnd, &objContext ) )
		return;
	pFrame->SetHandles(LoadMenu(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_LICENSE)),
			LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
	pFrame->InitialUpdateFrame( NULL, TRUE );

	// Load the license	
	((CStaticPresentationView*)pFrame->GetActiveView())->NavigateLicense();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame functions

//Saves the window size to the registry
void CMainFrame::StoreWindowState()
{
	RECT wndRect;
	GetWindowRect(&wndRect);

	CSRRegKey reg;
	LONG er = reg.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\MainFrame") );
	if( er == ERROR_SUCCESS )
	{
		reg.SetBool( TEXT("Zoomed"), IsZoomed()!=0 );
		reg.SetBool( TEXT("Iconic"), IsIconic()!=0 );
		reg.SetDWord( TEXT("WindowRect1"), (DWORD)wndRect.bottom );
		reg.SetDWord( TEXT("WindowRect2"), (DWORD)wndRect.left );
		reg.SetDWord( TEXT("WindowRect3"), (DWORD)wndRect.right );
		reg.SetDWord( TEXT("WindowRect4"), (DWORD)wndRect.top );
	}
}

//Loads the window size from the registry
void CMainFrame::RestoreWindowState(CREATESTRUCT &cs)
{
	CSRRegKey reg;
	LONG er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\MainFrame") );
	if( er == ERROR_SUCCESS )
	{
		RECT wndRect;
		BOOL wndState;

		wndState = reg.GetBool( TEXT("Zoomed"), false )
				|| reg.GetBool( TEXT("Iconic"), false );
		wndRect.bottom	= (LONG)reg.GetDWord( TEXT("WindowRect1"), cs.y+cs.cy );
		wndRect.left	= (LONG)reg.GetDWord( TEXT("WindowRect2"), cs.x );
		wndRect.right	= (LONG)reg.GetDWord( TEXT("WindowRect3"), cs.x+cs.cx );
		wndRect.top		= (LONG)reg.GetDWord( TEXT("WindowRect4"), cs.y );

		//Only if not iconic
		//Because the window is positioned outside the visible area when iconized
		//We don't want to restore such position
		if( !wndState )
		{
			//Restore the window size and position
			cs.cy = wndRect.bottom - wndRect.top;
			cs.cx = wndRect.right - wndRect.left;
			cs.y = wndRect.top;
			cs.x = wndRect.left;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Start screen related

void CMainFrame::SetFocusStartScreen()
{
	// Bring the start screen to the top
	if( IsWindow( ((CStageRaceApp*)AfxGetApp())->m_startScreen.m_hWnd ) )
		((CStageRaceApp*)AfxGetApp())->m_startScreen.SendMessage(WM_SETFOCUS);
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIFrameWnd::OnSetFocus(pOldWnd);
	SetFocusStartScreen();
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// Ensure that the status bar receives UDF messages
	if( (pMsg->message > WM_USER) && (pMsg->message < WM_APP) )
		if( m_wndStatusBar.PreTranslateMessage( pMsg ) )
			return true;
	// Other messages handled in standard way
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnHelpTipoftheday() 
{
	CHelp::Tip();
}

void CMainFrame::OnHelpAbout() 
{
	CHelp::Topic(CHelp::HLP_HLPABOUT);
}

void CMainFrame::ShowOperatorMessage(WPARAM message, LPARAM user)
{
	CString* pMessage = (CString*)message;
	CString* pUser = (CString*)user;

	// Show a message
	AfxMessageBox(
		LoadStr(IDS_DIV102)+
		*pUser+
		LoadStr(IDS_DIV103)+
		CTime::GetCurrentTime().Format(TEXT("%Hh%M"))+
		TEXT(":\n\n")+
		*pMessage );

	// Delete the strings
	delete pMessage;
	delete pUser;
}
