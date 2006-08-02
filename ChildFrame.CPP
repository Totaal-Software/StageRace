// ChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE( CChildFrame, CMDIChildWnd )

// Keep track of "do not display again" for
// the message box that alerts us of a TOC
// that is stored in a index.html being used
BOOL CChildFrame::m_bDoneInitialMaximize = false;

CChildFrame::CChildFrame()
{
	m_nListViewCompetitors	= -1;
	m_nListViewTeams		= -1;
	m_nPresentationView		= -1;
	m_nFormViewDetailsEmpty = -1;
	m_bDisplayConfigureToolBar = false;
	m_bDisplayTreeViewMainToolBar = true;
}

CChildFrame::~CChildFrame()
{
	CToolBar *pTB;
	// Remove all the tool bars that we were holding
	for(int n=0; n < m_arrayToolbars.GetSize(); n++)
	{
		pTB = m_arrayToolbars.GetAt(n);
		if (pTB) delete pTB;
	}
}

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_VIEW_TREEVIEWMAIN, OnViewTreeviewmain)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TREEVIEWMAIN, OnUpdateViewTreeviewmain)
	ON_COMMAND(ID_VIEW_TLBAR_CONFIGURE, OnViewTlbarConfigure)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TLBAR_CONFIGURE, OnUpdateViewTlbarConfigure)
	ON_COMMAND(ID_VIEW_TLBAR_TREEVIEWMAIN, OnViewTlbarTreeviewmain)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TLBAR_TREEVIEWMAIN, OnUpdateViewTlbarTreeviewmain)
	ON_COMMAND(ID_VIEW_TLBAR_GENERATE, OnViewTlbarGenerate)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TLBAR_GENERATE, OnUpdateViewTlbarGenerate)
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// COLUMNS
		// Create the two columns
		if (!m_wndSplitterColumns.CreateStatic(this, 1, 2))
		{
			TRACE0("Failed to create top-level splitter\n");
			return FALSE;
		}
		
		// Create the two rows in the left column
		if (!m_wndSplitterLeftColumn.CreateStatic(
				&m_wndSplitterColumns, // left column is parent
				2,
				1,
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				m_wndSplitterColumns.
					IdFromRowCol(0,0) ) ) // left column's ID within the top-level splitter
		{
			TRACE0("Failed to create nested splitter\n");
			return FALSE;
		}

	// VIEWS
		// Set the width of the left column to 300
		m_wndSplitterColumns.SetColumnInfo(0, 300, 0);
		// Create the views in the left column
		if (!m_wndSplitterLeftColumn.CreateView(0, 0,
			RUNTIME_CLASS(CIdView), CSize(0, 31), pContext))
		{
			TRACE0("Failed to create third pane\n");
			return FALSE;
		}
		if (!m_wndSplitterLeftColumn.CreateView(1, 0,
			pContext->m_pNewViewClass /* is CTreeViewMain */, CSize(0, 0), pContext))
		{
			TRACE0("Failed to create second pane\n");
			return FALSE;
		}
		// Create the first view in the right column
		m_nFormViewDetailsEmpty = m_wndSplitterColumns.AddView(0, 1, RUNTIME_CLASS(CFormViewDetailsEmpty), pContext);
		m_wndSplitterColumns.ShowView( m_nFormViewDetailsEmpty );

		// Make the CTreeViewMain the active view
		SetActiveView( (CView*)m_wndSplitterLeftColumn.GetPane(1,0) );
		
		// Fill the different views with pointers to the other views
		((CTreeViewMain*)m_wndSplitterLeftColumn.GetPane(1,0))->m_pIdView
			= ((CIdView*)m_wndSplitterLeftColumn.GetPane(0,0));

	// TOOLBARS
		// Generate toolbar
		if (!m_wndGenerateToolBar.CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS,CBRS_ALIGN_ANY   ) ||
			!m_wndGenerateToolBar.LoadToolBar(IDR_GENERATE))
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}
		// Configure toolbar
		if (!m_wndConfigureToolBar.CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS) ||
			!m_wndConfigureToolBar.LoadToolBar(IDR_CONFIGURE))
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}

		// TreeViewMain toolbar
		if (!m_wndTreeViewMainToolBar.CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS) ||
			!m_wndTreeViewMainToolBar.LoadToolBar(IDR_TREEVIEWMAIN))
		{
			TRACE0("Failed to create toolbar\n");
			return -1;      // fail to create
		}

		// ReBar
		if (!m_wndReBar.Create(this) ||
			!m_wndReBar.AddBar(&m_wndTreeViewMainToolBar, LoadStr( IDR_TREEVIEWMAIN ) ) ||
			!m_wndReBar.AddBar(&m_wndConfigureToolBar, LoadStr( IDS_DIV24 ) ) ||
			!m_wndReBar.AddBar(&m_wndGenerateToolBar, LoadStr( IDS_DIV80 ) ) )
		{
			TRACE0("Failed to create rebar\n");
			return -1;      // fail to create
		}

		// Hide the GenerateToolBar and TreeToolBar initially
		ShowControlBar(&m_wndGenerateToolBar, FALSE, FALSE);
		ShowControlBar(&m_wndConfigureToolBar, FALSE, FALSE);

	// Maximize the whole document area, that is including the CPresentationView
//	ShowWindow( SW_SHOWMAXIMIZED );
//	GetParent()->GetParent()->GetParent()->ShowWindow( SW_SHOWMAXIMIZED );

	return TRUE;
}

void CChildFrame::OnViewTreeviewmain() 
{
	m_wndSplitterColumns.Hide();
	ShowControlBar(&m_wndTreeViewMainToolBar,
		m_bDisplayTreeViewMainToolBar && !m_wndSplitterColumns.Hidden(),
		FALSE);
	ShowControlBar(&m_wndConfigureToolBar,
		m_bDisplayConfigureToolBar && !m_wndSplitterColumns.Hidden(),
		FALSE);
}

void CChildFrame::OnUpdateViewTreeviewmain(CCmdUI* pCmdUI) 
{
	if( pCmdUI->m_pMenu )
		// Make the menu item being checked or not according to the
		// tree view being visible or not
		pCmdUI->SetCheck( !m_wndSplitterColumns.Hidden() );
	else
		// Make the button pressed or not according to the tree view
		// being hidden or not
		pCmdUI->SetCheck( m_wndSplitterColumns.Hidden() );
	// Make sure it is only available for not empty right columns
	if( m_wndSplitterColumns.Hidden() )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(
			m_wndSplitterColumns.GetPane(0,1) !=
			m_wndSplitterColumns.GetView(m_nFormViewDetailsEmpty) );
}

void CChildFrame::SetActivePaneTreeViewMain()
{
	m_wndSplitterLeftColumn.SetActivePane(1,0);
}

void CChildFrame::SetActivePaneDetailView()
{
	m_wndSplitterColumns.SetActivePane(0,1);
}

CFormViewDetailsEmpty* CChildFrame::ShowViewDetailsEmpty()
{
	m_wndSplitterColumns.ShowView( m_nFormViewDetailsEmpty );
	SwitchToolbar();
	return (CFormViewDetailsEmpty*)m_wndSplitterColumns.GetView( m_nListViewTeams );
}

CListViewCompetitors* CChildFrame::ShowViewListCompetitors()
{
	// If this is the first time
	if( m_nListViewCompetitors == -1 )
	{
		// Set up the view
		m_nListViewCompetitors = m_wndSplitterColumns.AddView(
			0,m_wndSplitterColumns.Hidden()?0:1,RUNTIME_CLASS(CListViewCompetitors),NULL);
	}
	// Anyway, display it
	m_wndSplitterColumns.ShowView( m_nListViewCompetitors );
	SwitchToolbar();
	return (CListViewCompetitors*)m_wndSplitterColumns.GetView( m_nListViewCompetitors );
}

CListViewTeams* CChildFrame::ShowViewListTeams()
{
	// If this is the first time
	if( m_nListViewTeams == -1 )
	{
		// Set up the view
		m_nListViewTeams = m_wndSplitterColumns.AddView(
			0,m_wndSplitterColumns.Hidden()?0:1,RUNTIME_CLASS(CListViewTeams),NULL);
	}
	// Anyway, display it
	m_wndSplitterColumns.ShowView( m_nListViewTeams );
	SwitchToolbar();
	return (CListViewTeams*)m_wndSplitterColumns.GetView( m_nListViewTeams );
}

CPresentationView* CChildFrame::ShowViewPresentation()
{
	// If this is the first time
	if( m_nPresentationView == -1 )
	{
		m_nPresentationView = 0;
		// Set up the view
		m_nPresentationView = m_wndSplitterColumns.AddView(
			0,m_wndSplitterColumns.Hidden()?0:1,RUNTIME_CLASS(CPresentationView),NULL);
	}
	// Anyway, display it
	m_wndSplitterColumns.ShowView( m_nPresentationView );
	SwitchToolbar();

	return (CPresentationView*)m_wndSplitterColumns.GetView( m_nPresentationView );
}

UINT CChildFrame::GetResourceID()
{
	int n = m_wndSplitterColumns.GetColumnCount();
	CView* pView
		= (CView*)m_wndSplitterColumns.GetPane(
								0,
								n-1 );

	// Look up the ID no.
	if( pView->IsKindOf( RUNTIME_CLASS(CListViewCompetitors) ) )
		return ((CListViewCompetitors*)pView)->GetResourceID();
	else
	{
		if( pView->IsKindOf( RUNTIME_CLASS(CListViewTeams) ) )
			return ((CListViewTeams*)pView)->GetResourceID();
		else
		{
			if( pView->IsKindOf( RUNTIME_CLASS(CPresentationView) ) )
				return ((CPresentationView*)pView)->GetResourceID();
			else
				return 0;
		}
	}

}

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
    // Route to standard command targets first
    if(CMDIChildWnd::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo))
        return TRUE;
	
	CView* pActiveView = GetActiveView();
    // Route to inactive views secondly
    CDocument* pDoc = GetActiveDocument();
    if(pDoc)
	{
		POSITION pos = pDoc->GetFirstViewPosition ();
		while (pos != NULL)
		{
			CView* pNextView = pDoc->GetNextView(pos);
			if(pNextView->IsWindowVisible())
				if( IsChild( pNextView ) )
					if (pNextView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
						return TRUE;
		}
	}
    return FALSE;
}

void CChildFrame::SwitchToolbar()
{
	// Code from Omer Eisenberg/CodeGuru
	// This function retrive the resource ID from the current view
	// Then it calls 'SetToolbar' to activate the specified toolbar
	// and to disactivets all the others
	// If no view is open the resource ID, 'idResource', is set to 0
	// and all toolbars are disactivated

	int nResource = 0;
	// Empty
	SetToolbar( GetResourceID() );
}

int CChildFrame::AddToolbar(int nIDR)
{
	// Code from Omer Eisenberg/CodeGuru
	// This function returns the index of the toolbar, that have the
	// ID of 'nIDR', in the toolbar array, 'm_arrayToolbars'
	// If the ID does not exist in the loaded ID array, 'm_arrayToolbarIDs'
	// the function creates a new toolbar, ads the toolbar pointer
	// to the toolbar array and the ID to the loaded toolbar IDs
	// array
	// The function also docks the toolbar left to the mainframe
	// toolbar
	
	CRect rc;
	int n, nIdx;

	// Return if no real ID requested
	if (nIDR == 0)
		return (-1);
	// Search for this ID in the existing toolbars
	for(n=0, nIdx=-1; n < m_arrayToolbarIDs.GetSize(); n++)
		if(nIDR == m_arrayToolbarIDs.GetAt(n))
			nIdx = n;
	// If not found, we create it
	CToolBar *pTB;
	if(nIdx < 0)
	{
		pTB = new CToolBar;
		pTB->CreateEx(this, TBSTYLE_TRANSPARENT | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS);
		if( !(pTB->LoadToolBar(nIDR)) )
		{
			pTB->DestroyWindow();
			delete pTB;
			return (-1);
		}
		m_wndReBar.AddBar(pTB, LoadStr(nIDR));
		m_wndReBar.GetWindowRect (&rc);
		rc.OffsetRect(1,0);
		pTB->SetWindowText(LoadStr(nIDR));
		pTB->ShowWindow(SW_RESTORE);
		// Add to the array of existing toolbars
		nIdx = m_arrayToolbars.Add(pTB);
		m_arrayToolbarIDs.Add(nIDR);
	}
	return (nIdx);
}

void CChildFrame::SetToolbar(int nIDR)
{
	// Code from Omer Eisenberg/CodeGuru
	// This function gets the toolbar index to the toolbars array,
	// 'm_arrayToolbars'. Then it loops over all the toolbars. If the
	// toolbar the one to be displayed it is closed
	int n, nIdx;

	// Do something
	nIdx = AddToolbar( nIDR );

	// Go over all the existing toolbars
	CToolBar *pTB;
	for(n=0; n < m_arrayToolbars.GetSize(); n++)
	{
		// Get a toolbar
		pTB = m_arrayToolbars.GetAt(n);
		// Check if this is the current toolbar
		if (n != nIdx)
			// Hide!
			ShowControlBar (pTB, 0, 0);
		if (n == nIdx)
		{
			// Make the last toolbar maximized in order to have
			// it left aligned
			// This sometimes even actually works
			m_wndReBar.GetReBarCtrl().MaximizeBand(
				m_wndReBar.GetReBarCtrl().GetBandCount()-1 );

			// Show!
			ShowControlBar (pTB, 1, 0);
		}
	}
	// Reposition all the control bars
	RecalcLayout();
}

void CChildFrame::OnViewTlbarConfigure() 
{
	m_bDisplayConfigureToolBar = !m_bDisplayConfigureToolBar;
	ShowControlBar(&m_wndConfigureToolBar,
		m_bDisplayConfigureToolBar && !m_wndSplitterColumns.Hidden(),
		FALSE);
}

void CChildFrame::OnUpdateViewTlbarConfigure(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bDisplayConfigureToolBar!=0 );
}

void CChildFrame::OnViewTlbarTreeviewmain() 
{
	m_bDisplayTreeViewMainToolBar = !m_bDisplayTreeViewMainToolBar;
	ShowControlBar(&m_wndTreeViewMainToolBar,
		m_bDisplayTreeViewMainToolBar && !m_wndSplitterColumns.Hidden(),
		FALSE);
}

void CChildFrame::OnUpdateViewTlbarTreeviewmain(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bDisplayTreeViewMainToolBar!=0 );
}

void CChildFrame::OnViewTlbarGenerate() 
{
	BOOL bVisible = ((m_wndGenerateToolBar.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar(&m_wndGenerateToolBar, !bVisible, FALSE);
}

void CChildFrame::OnUpdateViewTlbarGenerate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(( m_wndGenerateToolBar.GetStyle() & WS_VISIBLE) !=0 );
}

void CChildFrame::DoInitialMaximize()
{
	// Makes functionality available for a
	// child view to maximize the frame window
	// This should only happen once, in order
	// not to annoy the user, therefor the
	// static m_bDoneInitialMaximize is used
	if( !m_bDoneInitialMaximize )
	{
		ShowWindow( SW_SHOWMAXIMIZED );
		m_bDoneInitialMaximize = true;
	}
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// Arrange the toolbar profile picker
	if( pActivateWnd )
	{
		CDocument* pDoc = ((CMDIChildWnd*)pActivateWnd)->GetActiveDocument();

		if( pDoc )
		{
			if( pDoc->IsKindOf( RUNTIME_CLASS(CStageRaceDoc) ) )
				((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.SetDoc( (CStageRaceDoc*)pDoc );
			else
				((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.ResetDoc();
		}
		else
			((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.ResetDoc();
	}
	else
		((CMainFrame*)AfxGetMainWnd())->m_wndStandardToolBar.ResetDoc();
}

