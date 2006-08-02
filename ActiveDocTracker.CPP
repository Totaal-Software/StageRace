// ActiveDocTracker.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveDocTracker

IMPLEMENT_DYNCREATE(CActiveDocTracker, CDocument)

CActiveDocTracker::CActiveDocTracker()
{
	m_pSelection = NULL;
	CDocument::SetTitle( LoadStr( IDR_ACTIVEDOCTRACKER ) );
}

CActiveDocTracker::~CActiveDocTracker()
{
	m_pSelection = NULL;
	CDocument::SetTitle( LoadStr( IDR_ACTIVEDOCTRACKER ) );
}

BEGIN_MESSAGE_MAP(CActiveDocTracker, CDocument)
	//{{AFX_MSG_MAP(CActiveDocTracker)
	ON_COMMAND(ID_VIEW_LISTVIEWACTIVEDOC, OnViewListviewactivedoc)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LISTVIEWACTIVEDOC, OnUpdateViewListviewactivedoc)
	ON_COMMAND(ID_FILE_SAVE, OnDisabled)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateDisabled)
	ON_COMMAND(ID_FILE_SAVE_AS, OnDisabled)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateDisabled)
	ON_COMMAND(ID_FILE_CLOSE, OnDisabled)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateDisabled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveDocTracker diagnostics

#ifdef _DEBUG
void CActiveDocTracker::AssertValid() const
{
	CDocument::AssertValid();
}

void CActiveDocTracker::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CActiveDocTracker commands

void CActiveDocTracker::OnViewListviewactivedoc() 
{
	POSITION nPos = GetFirstViewPosition();
	if( !nPos )
	{
		// No existing view
		// So make one

		CMainFrame* pMainWnd			= (CMainFrame*)AfxGetApp()->m_pMainWnd;
		// We create a new child frame
		CChildFrameExclusive* pFrame	= new CChildFrameExclusive(); // Instantiate a new frame

		// We create a context describing the contents of the child frame (doc/view)
		CCreateContext objContext;
		objContext.m_pCurrentDoc		= this; // Use this document
		objContext.m_pNewViewClass		= RUNTIME_CLASS( CListViewActiveDoc ); // Instantiate a new view
		objContext.m_pNewDocTemplate	= this->GetDocTemplate();
		objContext.m_pLastView			= pMainWnd->GetActiveFrame() ? pMainWnd->GetActiveFrame()->GetActiveView() : NULL;
		objContext.m_pCurrentFrame		= pMainWnd->GetActiveFrame();

		// We load the frame as defined above
		if ( !pFrame->LoadFrame( IDR_ACTIVEDOCTRACKER, WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, pMainWnd, &objContext ) )
			return;
		pFrame->InitialUpdateFrame( objContext.m_pCurrentDoc, TRUE );
	}
	else
	{
		// An existing view
		// So remove it

		CView* pView = GetNextView( nPos );
		RemoveView( pView );
		pView->GetParentFrame()->DestroyWindow();
	}
}

void CActiveDocTracker::OnUpdateViewListviewactivedoc(CCmdUI* pCmdUI) 
{
	// Set a check indicating whether one (or more) view exist(s)
	pCmdUI->SetCheck( GetFirstViewPosition()?1:0 );
}

void CActiveDocTracker::OnChangedViewList() 
{
	// Do not call OnChangedViewList because this one is
	// responsible for cleaning up the document if no view
	// remains
	//	CDocument::OnChangedViewList();
	// Update the frame counts as needed instead
	UpdateFrameCounts();
}

void CActiveDocTracker::OnDisabled() 
{
	// Handler for disabled file menu items
	// Obviously do nothing	
}

void CActiveDocTracker::OnUpdateDisabled(CCmdUI* pCmdUI) 
{
	// Handler for disabled file menu items
	// Disable item
	pCmdUI->Enable(FALSE);	
}

/////////////////////////////////////////////////////////////////////////////
// Setters

void CActiveDocTracker::Open(CStageRaceDoc * pDoc)
{
	// Inform other interested parties
	PostMessage( AfxGetMainWnd()->m_hWnd,
		WM_USER_ACTIVEDOC_DOCOPEN, (WPARAM)pDoc, 0 );

	// Search for an existing copy of this document
	for( int i=m_arDocs.GetSize(); i; i-- )
		if( m_arDocs[i-1]==pDoc )
		{
			// If found, require the views to update it
			UpdateAllViews( NULL, UV_UPDATED, pDoc );
			return;
		}
	// Otherwise, add it
	m_arDocs.Add( pDoc );
	// And require the views to display it anyway
	UpdateAllViews( NULL, UV_ADDED, pDoc );

	// If this is the first document added
	if( GetCount()==1 )
		// Make it also selected
		Select( pDoc );
}

void CActiveDocTracker::Close(CStageRaceDoc * pDoc)
{
	// Inform other interested parties
	PostMessage( AfxGetMainWnd()->m_hWnd,
		WM_USER_ACTIVEDOC_DOCCLOSE, (WPARAM)pDoc, 0 );

	// Search for the existing copy of this document
	for( int i=m_arDocs.GetSize(); i; i-- )
		if( m_arDocs[i-1]==pDoc )
		{
			// When found, remove it
			m_arDocs.RemoveAt( i-1 );
			// And require the views to remove it too
			UpdateAllViews( NULL, UV_DELETED, pDoc );

			// If this is the selected item
			if( m_pSelection==pDoc )
				// Set the selection to none
				Select(NULL);

			return;
		}

	// Closing of a not-opened document shouldn't be possible
	ASSERT(FALSE);
}

void CActiveDocTracker::Select(CStageRaceDoc * pDoc)
{
	// Inform other interested parties
	PostMessage( AfxGetMainWnd()->m_hWnd,
		WM_USER_ACTIVEDOC_DOCSELECT, (WPARAM)pDoc, 0 );

	// Store the new selection
	m_pSelection = pDoc;
	// And require the views to display the new selection
	UpdateAllViews( NULL, UV_SELECTIONCHANGED, m_pSelection );
}

/////////////////////////////////////////////////////////////////////////////
// Getters

UINT CActiveDocTracker::GetCount()
{
	return m_arDocs.GetSize();
}

const CStageRaceDoc* CActiveDocTracker::GetAt(UINT nAt)
{
	return m_arDocs.GetAt(nAt);
}

const CStageRaceDoc* CActiveDocTracker::GetSelected()
{
	return m_pSelection;
}

/////////////////////////////////////////////////////////////////////////////
// StageRace message handling

BOOL CActiveDocTracker::PreTranslateMessage(MSG *pMsg)
{
	// Inform other interested parties
	if( m_pSelection )
	{
		// Look for arrival list messages
		if( (pMsg->message == WM_STAGERACE_AR_SETCOMP)
			||
			(pMsg->message == WM_STAGERACE_AR_DECLASSCOMP)
			||
			(pMsg->message == WM_STAGERACE_AR_GETCOMPFROMSTANO)
			||
			(pMsg->message == WM_STAGERACE_AR_GETCOMPFROMTIME)
			||
			(pMsg->message == WM_STAGERACE_AR_GETCOMPFROMRANK)
			||
			(pMsg->message == WM_STAGERACE_TT_GETSTARTTIME)
		)
		{
			PostMessage( AfxGetMainWnd()->m_hWnd,
				WM_USER_MESSAGINGACTION, 0, 0 );
			if( ((CMainFrame*)AfxGetMainWnd())->m_pDlgCurrentlyRunning )
				return ((CMainFrame*)AfxGetMainWnd())->m_pDlgCurrentlyRunning->PreTranslateMessage( pMsg );
		}
		////////////////////////////////////////////////
		// INFORMATION REQUEST: COMPETITOR BASED ON TIME
		if( pMsg->message == WM_STAGERACE_GETCOMPFROMSTANO )
		{
			PostMessage( AfxGetMainWnd()->m_hWnd,
				WM_USER_MESSAGINGACTION, 0, 0 );

			CCompetitor aComp;
			CStageRaceDoc* pDoc = (CStageRaceDoc*)m_pSelection;
			int nStaNo = pMsg->wParam & 0xFFFF;
			// Get the requested competitor in the document
			if( pDoc->CompetitorsExist( nStaNo ) )
			{
				aComp = pDoc->CompetitorsGet( nStaNo );
				// Create atoms with the requested information strings
				ATOM aName		= GlobalAddAtom( aComp.m_competitor );
				ATOM aTeam		= GlobalAddAtom( aComp.m_pTeam?aComp.m_pTeam->m_name:"" );
				ATOM aTeamCode	= GlobalAddAtom( aComp.m_pTeam?aComp.m_pTeam->m_code:"" );

				// wP: ub: name wP: lb: StaNo
				UINT wParam = (aName<<16)|(nStaNo&0xFFFF);
				// lP: ub: team lP: lb: team code
				UINT lParam = (aTeam<<16)|(aTeamCode&0xFFFF);
					
				// Post the message as it is to the appropriate window
				::PostMessage( (HWND)pMsg->lParam,
								WM_STAGERACE_COMP,
								wParam,
								lParam );
			}
			else
				// If not exist, return "invalid" message to the appropriate window
				::PostMessage( (HWND)pMsg->lParam,
								WM_STAGERACE_COMP,
								-1, // Indicates (by convention) invalid request
								-1 );

			return TRUE;
		}
	}
	// Default 'nothing to do'
	return FALSE;
}

