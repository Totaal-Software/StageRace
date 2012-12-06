// StageRaceStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRaceStatusBar

CStageRaceStatusBar::CStageRaceStatusBar()
{
}

CStageRaceStatusBar::~CStageRaceStatusBar()
{
}


BEGIN_MESSAGE_MAP(CStageRaceStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CStageRaceStatusBar)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStageRaceStatusBar message handlers

BOOL CStageRaceStatusBar::Create(CWnd *pParentWnd)
{
	// Create the status bar
	if( CStatusBar::Create(pParentWnd) )
	{
		// Fill it with panes
		const UINT indicators[] =
		{
			ID_SEPARATOR,   // status line indicator
			ID_INDICATOR_GENERATE,
			ID_INDICATOR_KEY,
			ID_INDICATOR_ACTIVEDOC,
			ID_INDICATOR_MESSAGINGACTION,
			ID_INDICATOR_DOCVERSION,
			ID_INDICATOR_CAPS,
			ID_INDICATOR_NUM
		};
		if( SetIndicators(indicators,
				sizeof(indicators)/sizeof(UINT)))
		{
			SetPaneInfo( CommandToIndex( ID_INDICATOR_GENERATE ),
							ID_INDICATOR_GENERATE,
							SBPS_NORMAL,
							100 );
			SetPaneInfo( CommandToIndex( ID_INDICATOR_KEY ),
							ID_INDICATOR_KEY,
							SBPS_NOBORDERS,
							16 );
			SetPaneInfo( CommandToIndex( ID_INDICATOR_MESSAGINGACTION ),
							ID_INDICATOR_MESSAGINGACTION,
							SBPS_NOBORDERS,
							16 );
			SetPaneText( CommandToIndex( ID_INDICATOR_DOCVERSION ), TEXT("") );

			// Create the generate progress control in the status bar
			m_prGenerate.Create( this, ID_INDICATOR_GENERATE, WS_VISIBLE|PBS_SMOOTH );
			// Create the active doc combo box in the status bar
			m_cbActiveDoc.Create( this, ID_INDICATOR_ACTIVEDOC, WS_VISIBLE|CBS_DROPDOWNLIST );
			// Adapt the status bar height to the combo box height
			CRect rect;
			m_cbActiveDoc.GetWindowRect(rect);
			GetStatusBarCtrl().SetMinHeight(
				max(16/*size of icons!*/,
					rect.Height()/*combo height*/+2/*for the beauty*/
				)
			);

			// Set the standard content of the messaging action indicator
			SetNoAction();

			// Return success
			return true;
		}
	}
	return false;
}

BOOL CStageRaceStatusBar::IsVisible()
{
	BOOL bVisible = ((GetStyle() & WS_VISIBLE) != 0);
	return bVisible;
}

void CStageRaceStatusBar::ToggleShow(CFrameWnd *pMain)
{
	pMain->ShowControlBar(this, IsVisible()==0, FALSE);
}

void CStageRaceStatusBar::SetKey(BOOL bLocked/*= TRUE*/)
{
	if( m_stKey.m_hWnd == NULL)
	{
		// Create it
		m_stKey.Create( this, ID_INDICATOR_KEY, WS_VISIBLE|SS_ICON|SS_CENTERIMAGE );
	}
	// Set the right icon
	HICON hIcon = (HICON)LoadImage( AfxGetInstanceHandle(),
			MAKEINTRESOURCE(bLocked?IDI_KEY_LOCKED:IDI_KEY_FREE),
			IMAGE_ICON, 16, 16, LR_SHARED);
	if( m_stKey.GetIcon() != hIcon )
		m_stKey.SetIcon( hIcon );
}

void CStageRaceStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	m_stKey.Reposition();
	m_cbActiveDoc.Reposition();
	m_stMessagingAction.Reposition();
	m_prGenerate.Reposition();
}

BOOL CStageRaceStatusBar::PreTranslateMessage(MSG *pMsg)
{
	if( (pMsg->message > WM_USER) && (pMsg->message < WM_APP) )
	{
		if( pMsg->message == WM_USER_KEY_LOCKED )
		{
			SetKey();
			return true;
		}
		if( pMsg->message == WM_USER_KEY_FREE )
		{
			SetKey(false);
			return true;
		}
		if( pMsg->message == WM_USER_MESSAGINGACTION )
		{
			SetAction();
			return true;
		}
		if( (pMsg->message == WM_USER_GENERATE_PROGRESS_SET) ||
			(pMsg->message == WM_USER_GENERATE_PROGRESS_FINISH) ||
			(pMsg->message == WM_USER_GENERATE_PROGRESS_INCREMENT))
		{
			if( m_prGenerate.PreTranslateMessage( pMsg ) )
				return true;
		}
		if( (pMsg->message == WM_USER_ACTIVEDOC_DOCOPEN) ||
			(pMsg->message == WM_USER_ACTIVEDOC_DOCCLOSE) ||
			(pMsg->message == WM_USER_ACTIVEDOC_DOCSELECT))
		{
			if( m_cbActiveDoc.PreTranslateMessage( pMsg ) )
				return true;
		}
		return false;
	}
	return CStatusBar::PreTranslateMessage(pMsg);
}

void CStageRaceStatusBar::SetAction()
{
	if( m_stMessagingAction.m_hWnd == NULL)
		// Create it
		m_stMessagingAction.Create( this, ID_INDICATOR_MESSAGINGACTION, WS_VISIBLE|SS_ICON|SS_CENTERIMAGE );

	// Set the right icon
	HICON hIcon = (HICON)LoadImage( AfxGetInstanceHandle(),
			MAKEINTRESOURCE(IDR_ACTIVEDOCTRACKER),
			IMAGE_ICON, 16, 16, LR_SHARED);
	if( m_stMessagingAction.GetIcon() != hIcon )
		m_stMessagingAction.SetIcon( hIcon );

	// Set a timer that will let the icon disappear again, soon
	SetTimer( 2 /*StageRace unique!*/, 800, NULL );
}

void CStageRaceStatusBar::SetNoAction()
{
	if( m_stMessagingAction.m_hWnd == NULL)
		// Create it
		m_stMessagingAction.Create( this, ID_INDICATOR_MESSAGINGACTION, WS_VISIBLE|SS_ICON|SS_CENTERIMAGE );

	// Set the right icon
	HICON hIcon = (HICON)LoadImage( AfxGetInstanceHandle(),
			MAKEINTRESOURCE(IDR_ACTIVEDOCTRACKER_GRAY),
			IMAGE_ICON, 16, 16, LR_SHARED);
	if( m_stMessagingAction.GetIcon() != hIcon )
		m_stMessagingAction.SetIcon( hIcon );
}

void CStageRaceStatusBar::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == 2 )
	{
		KillTimer(2);
		SetNoAction();
	}
	CStatusBar::OnTimer(nIDEvent);
}

void CStageRaceStatusBar::SetDocVersion(CStageRaceDoc* pDoc)
{
	// This function sets the document version in the status bar

	if( pDoc )
	{
		TCHAR czBuffer[10];
		_itot( pDoc?pDoc->GetFileVersion():0, czBuffer, 10 );

		// Display the new text
		SetPaneText( 5, czBuffer );
	}
	else
		SetPaneText( 5, TEXT("") );
}
