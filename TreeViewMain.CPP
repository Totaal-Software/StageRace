// TreeViewMain.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain

IMPLEMENT_DYNCREATE( CTreeViewMain, CTreeView )

CTreeViewMain::CTreeViewMain()
{
	m_DragDrop.m_bDragging	= false;
	m_pHalfStage			= NULL;
	m_bRedrawMode			= false;
}

BEGIN_MESSAGE_MAP(CTreeViewMain, CTreeView)
	//{{AFX_MSG_MAP(CTreeViewMain)
	ON_COMMAND(ID_CONFIGURE_INSERT_FULLSTAGE, OnConfigureInsertFullstage)
	ON_COMMAND(ID_CONFIGURE_INSERT_HALFSTAGE, OnConfigureInsertHalfstage)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CONFIGURE_CONFIGURE, OnConfigureConfigure)
	ON_COMMAND(ID_EDIT_EDITSELECTION, OnEditEditselection)
	ON_COMMAND(ID_CONFIGURE_DELETE, OnConfigureDelete)
	ON_COMMAND(ID_INSERT_SIGNOUTS, OnInsertSignouts)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_COMMAND(ID_INSERT_COMMUNIQUE, OnInsertCommunique)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_INSERT_COMMUNIQUE, OnUpdateInsertCommunique)
	ON_UPDATE_COMMAND_UI(ID_INSERT_SIGNOUTS, OnUpdateInsertSignouts)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EDITSELECTION, OnUpdateEditEditselection)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_INSERT_HALFSTAGE, OnUpdateConfigureInsertHalfStage)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_DELETE, OnUpdateConfigureDelete)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURE_CONFIGURE, OnUpdateConfigureConfigure)
	ON_COMMAND(ID_TOOLS_EXPORTOPTIC, OnToolsExportoptic)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EXPORTOPTIC, OnUpdateToolsExportoptic)
	ON_COMMAND(ID_TOOLS_EXPORTCHRONX, OnToolsExportchronx)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EXPORTCHRONX, OnUpdateToolsExportchronx)
	ON_COMMAND(ID_EDIT_PUBLISH, OnEditPublish)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PUBLISH, OnUpdateEditPublish)
	ON_COMMAND(ID_NEXT_PANE, OnNextPane)
	ON_COMMAND(ID_EDIT_COMPETITORS, OnEditCompetitors)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COMPETITORS, OnUpdateEditCompetitors)
	ON_COMMAND(ID_EDIT_TEAMS, OnEditTeams)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TEAMS, OnUpdateEditTeams)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_COPYTOSELECTIONDLG, OnEditCopytoselectiondlg)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPYTOSELECTIONDLG, OnUpdateEditCopytoselectiondlg)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_CHECK, OnArrivalFunctionsCheck)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_1, OnArrivalFunctionsGroupt1)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_2, OnArrivalFunctionsGroupt2)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_GROUPT_3, OnArrivalFunctionsGroupt3)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_IMPORT, OnArrivalFunctionsImport)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_REMOVE1XSECONDS, OnArrivalFunctionsRemove1xseconds)
	ON_COMMAND(ID_ARRIVAL_FUNCTIONS_REMOVEGAPS, OnArrivalFunctionsRemovegaps)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_CHECK, OnUpdateArrivalFunctionsCheck)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_GROUPT_1, OnUpdateArrivalFunctionsGroupt1)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_GROUPT_2, OnUpdateArrivalFunctionsGroupt2)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_GROUPT_3, OnUpdateArrivalFunctionsGroupt3)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_IMPORT, OnUpdateArrivalFunctionsImport)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_REMOVE1XSECONDS, OnUpdateArrivalFunctionsRemove1xseconds)
	ON_UPDATE_COMMAND_UI(ID_ARRIVAL_FUNCTIONS_REMOVEGAPS, OnUpdateArrivalFunctionsRemovegaps)
	ON_COMMAND(ID_GENERATE_SELECTION, OnGenerateSelection)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_SELECTION, OnUpdateGenerateSelection)
	ON_COMMAND(ID_GENERATE_READONLY, OnGenerateReadonly)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_READONLY, OnUpdateGenerateReadonly)
	ON_COMMAND(ID_TOOLS_EDITPUBL, OnToolsEditpubl)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EDITPUBL, OnUpdateToolsEditpubl)
	ON_COMMAND(ID_VIEW_EXPAND, OnViewExpand)
	ON_COMMAND(ID_PREV_PANE, OnNextPane)
	ON_COMMAND(ID_TOOLS_EXPORTTTWARE, OnToolsExportttware)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_EXPORTTTWARE, OnUpdateToolsExportttware)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain diagnostics

#ifdef _DEBUG
void CTreeViewMain::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeViewMain::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CStageRaceDoc* CTreeViewMain::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStageRaceDoc)));
	return (CStageRaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// TREE RELATED

BOOL CTreeViewMain::PreCreateWindow(CREATESTRUCT& cs)
{
	// Modify the Window class or styles here by modifying the CREATESTRUCT cs
	cs.style |= ( TVS_SHOWSELALWAYS|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT );
	cs.style &= ~TVS_DISABLEDRAGDROP;
	return CTreeView::PreCreateWindow(cs);
}

void CTreeViewMain::OnInitialUpdate()
{
	// Check box support obtained from codeguru.earthweb.com
	// Adding Simple Checkbox for each Item - Zafir Anjum (1998/08/06)

	CTreeView::OnInitialUpdate();

	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Set the document pointer
	m_pDoc = (CStageRaceDoc*)GetDocument();
	m_eiSelected.SetDoc( m_pDoc );

	
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	// TreeView properties

		// Create image lists
		m_imageList		.Create( IDB_TREE     , 20, 1, RGB(255,0,255) );
		m_imageListState.Create( IDB_TREESTATE, 15, 1, RGB(255,0,255) );

		// Connect image lists
		ctrlTree.SetImageList( &m_imageList		, TVSIL_NORMAL );
		ctrlTree.SetImageList( &m_imageListState, TVSIL_STATE  );

		// Set the height and amount of indention of the tree items
		// (slightly larger than the average Windows setting)
		ctrlTree.SetIndent(25);
		ctrlTree.SetItemHeight( 25 );

	// Fill the tree
	DrawTreeFromScratch();

	// Maximize the whole frame window
	// for the first document that is opened
	((CChildFrame*)GetParentFrame())->DoInitialMaximize();
}

void CTreeViewMain::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	SendMessage( WM_RBUTTONUP, 0, MAKELPARAM(point.x,point.y) );

	*pResult = 0;
}

void CTreeViewMain::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Test whether we really doubleclicked a tree item
	UINT uFlags=0;
	HTREEITEM hItem = GetTreeCtrl().HitTest( point, &uFlags );

	if( uFlags & TVHT_ONITEMSTATEICON )
	{
		// If we dblclk'd a tree item's check box:
		// let's handle it
		GetTreeCtrl().Select( hItem, TVGN_CARET );
		CheckItem();
	}
	else
	{
		if( uFlags & TVHT_ONITEM )
		{
			// If we dblclk'd a tree item after all:
			// let's handle it
			if( !OnEditEditselection() )
			{
				CTreeView::OnLButtonDblClk(nFlags, point);
			}
		}
	}
}

void CTreeViewMain::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( !m_bRedrawMode )
	{
		ItemSwitch();
		ItemDisplay();
	}
}

void CTreeViewMain::DrawTreeFromScratch()
{
	// Prevent enduring OnSelchanged calls
	m_bRedrawMode = true;

	LockWindowUpdate();

	CTreeCtrl& ctrlTree = GetTreeCtrl();
	// Remove all tree leafs
	ctrlTree.DeleteAllItems();

	// Overhead items
	HTREEITEM hBaseItem = ctrlTree.InsertItem( " "+m_pDoc->GetTitle()+" ", TIC_ROOT, TIC_ROOT );
	ctrlTree.SetItemData( hBaseItem, TI_ROOT );

	TCHAR czBuffer[10];
	_itot( m_pDoc->CompetitorsCount(), czBuffer, 10 );
	// Competitors
	HTREEITEM hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV36 ), TIC_COMPETITORS, TIC_COMPETITORS, ctrlTree.GetSelectedItem() );
	ctrlTree.SetItemData( hItem, TI_COMPETITORS );
	{
		HTREEITEM hItem1;

		// Type 1 competitors list
		hItem1 = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV69 )+" ", TIC_LISTCOMPETITORS, TIC_LISTCOMPETITORS, hItem );
		ctrlTree.SetItemData( hItem1, TI_LISTCOMPETITORS1 );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem1,
				InitDetermineState( &m_pDoc->m_idCompetitors ), TVIS_STATEIMAGEMASK );

		// Type 2 competitors list
		hItem1 = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV70 )+" ", TIC_LISTCOMPETITORS, TIC_LISTCOMPETITORS, hItem );
		ctrlTree.SetItemData( hItem1, TI_LISTCOMPETITORS2 );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem1,
				InitDetermineState( &m_pDoc->m_idTeams ), TVIS_STATEIMAGEMASK );

		// Expand to see the competitors lists
		ctrlTree.Expand( hItem, TVE_EXPAND );
	}

	_itot( m_pDoc->TeamsCount(), czBuffer, 10 );
	// Teams
	ctrlTree.SetItemData( ctrlTree.InsertItem( " "+LoadStr( IDS_DIV37 ), TIC_TEAMS, TIC_TEAMS,
		ctrlTree.GetSelectedItem() ), TI_TEAMS );

	// General communique
	if ( !m_pDoc->m_communique.IsEmpty() )
	{
		hItem = ctrlTree.InsertItem( " "+m_pDoc->m_communique.m_title+" ", TIC_COMMUNIQUE, TIC_COMMUNIQUE, hBaseItem );
		ctrlTree.SetItemData( hItem, TI_COMMUNIQUE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &m_pDoc->m_communique.m_id ), TVIS_STATEIMAGEMASK );
	}

	// Contents
	CFullStage* pFullStage;
	// Iterate the full stages list
	for ( int i=1; i <= m_pDoc->StagesFullCount(); i++ )
	{
		HTREEITEM hParent;
		// Add every full stage
		pFullStage = m_pDoc->StagesGet( i );
		hParent = ctrlTree.InsertItem( " " + CEventItem::StagesMakeIDString(i,m_pDoc) + ": " + pFullStage->m_date+" ", TIC_FULLSTAGE, TIC_FULLSTAGE, ctrlTree.GetRootItem() );
		// and also set the item data
		ctrlTree.SetItemData( hParent, i );

		// Add eventually a communique for every full stage
		if ( !pFullStage->m_communique.IsEmpty() )
		{
			hItem = ctrlTree.InsertItem( " "+pFullStage->m_communique.m_title+" ", TIC_COMMUNIQUE, TIC_COMMUNIQUE, hParent );
			ctrlTree.SetItemData( hItem, TI_COMMUNIQUE );
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
				ctrlTree.SetItemState( hItem,
					InitDetermineState( &pFullStage->m_communique.m_id ), TVIS_STATEIMAGEMASK );
		}

		CHalfStage* pHalfStage;
		// Iterate the half stages list
		for ( int j=1; j <= pFullStage->CountHalfStages(); j++ )
		{
			// Add every half stage (or time trial)
			pHalfStage = m_pDoc->StagesGet( i, j );
			DrawHalfStage( pHalfStage, i, j, hParent );
		}
	}
	// Expand the root item from the three, to make the stages one-click-easier
	//  accessible
	ctrlTree.Expand( ctrlTree.GetRootItem(), TVE_EXPAND );
	ctrlTree.Select( ctrlTree.GetRootItem(), TVGN_CARET );

	// End preventing enduring OnSelchanged calls
	m_bRedrawMode = false;

	// Make the right initial item being displayed
	ItemSwitch();
	ItemDisplay();

	UpdateCountCompetitors();
	UpdateCountTeams();

	UnlockWindowUpdate();
}

HTREEITEM CTreeViewMain::DrawHalfStage(CHalfStage* pHalfStage, int nFS, int nHS, HTREEITEM hParent, HTREEITEM hInsertAfter/*=TVI_LAST*/ )
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	// The stage itself
	HTREEITEM aHsParent, hItem;
	if ( pHalfStage->m_stageType==ST_NORMAL )
	{
		aHsParent = ctrlTree.InsertItem( " " + CEventItem::StagesMakeIDString(nFS,nHS,m_pDoc) + ": " + LoadStr( IDS_DIV40 )+" - "+pHalfStage->m_title+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hParent, hInsertAfter );
	}
	else
	{
		aHsParent = ctrlTree.InsertItem( " " + CEventItem::StagesMakeIDString(nFS,nHS,m_pDoc) + ": " + LoadStr( IDS_DIV38 )+" - "+pHalfStage->m_title+" ", TIC_TIMETRIAL, TIC_TIMETRIAL, hParent, hInsertAfter );
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV39 )+" ", TIC_TIMETRIALORDER, TIC_TIMETRIALORDER, aHsParent );
		ctrlTree.SetItemData( hItem, TI_TIMETRIALORDER );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idStartList ), TVIS_STATEIMAGEMASK );
	}
	// Cross out list
	hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV52 )+" ", TIC_CROSSOUTLIST, TIC_CROSSOUTLIST, aHsParent );
	ctrlTree.SetItemData( hItem, TI_CROSSOUTLIST );
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
		ctrlTree.SetItemState( hItem,
			InitDetermineState( &pHalfStage->m_idCrossOut ), TVIS_STATEIMAGEMASK );

	// Sign in list
	hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV83 )+" ", TIC_SIGNINLIST, TIC_SIGNINLIST, aHsParent );
	ctrlTree.SetItemData( hItem, TI_SIGNINLIST );
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
		ctrlTree.SetItemState( hItem,
			InitDetermineState( &pHalfStage->m_idSignIn ), TVIS_STATEIMAGEMASK );

	// Most aggressive
	if( pHalfStage->m_mostaggressivepoints.GetCount() )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV44 )+" ", TIC_MOSTAGGRESSIVE, TIC_MOSTAGGRESSIVE, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_MOSTAGGRESSIVE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMostAggressive ), TVIS_STATEIMAGEMASK );
	}
	// Climbs
	if( pHalfStage->m_climbsorder.GetCount() )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV41 )+" ", TIC_CLIMB, TIC_CLIMB, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLIMB );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idClimbs ), TVIS_STATEIMAGEMASK );
	}
	// Points
	if( pHalfStage->m_pointspointsFinish.GetCount() )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV68 )+" ", TIC_POINTS, TIC_POINTS, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_POINTS );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idPoints ), TVIS_STATEIMAGEMASK );
	}
	// Sprints
	if( pHalfStage->m_sprintpointsCount )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV42 )+" ", TIC_SPRINT, TIC_SPRINT, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_SPRINT );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idSprints ), TVIS_STATEIMAGEMASK );
	}
	// Teams classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_GENERATE) )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV56 )+" ", TIC_CLASSTEAMS, TIC_CLASSTEAMS, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSTEAMS );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idTeams ), TVIS_STATEIMAGEMASK );
	}
	// Mask 10 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 10: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK10 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK10GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask10gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK10STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask10stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 9 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 9: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK9 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK9GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask9gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK9STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask9stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 8 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 8: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK8 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK8GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask8gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK8STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask8stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 7 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 7: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK7 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK7GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask7gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK7STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask7stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 6 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 6: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK6 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK6GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask6gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK6STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask6stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 5 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 5: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK5 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK5GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask5gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK5STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask5stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 4 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 4: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK4 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK4GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask4gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK4STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask4stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 3 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 3: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK3 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK3GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask3gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK3STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask3stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 2 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 2: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK2 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK2GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask2gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK2STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask2stage ), TVIS_STATEIMAGEMASK );
	}
	// Mask 1 classification
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
	{
		HTREEITEM hItemPar = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV57 )+" mask 1: "+((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1+" ", TIC_CLASSMASK, TIC_CLASSMASK, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItemPar, TI_CLASSMASK1 );
		
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK1GENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask1gen ), TVIS_STATEIMAGEMASK );
		
		hItem = ctrlTree.InsertItem( " "+((pHalfStage->m_stageType==ST_NORMAL)?LoadStr( IDS_DIV40 ):LoadStr( IDS_DIV38 ))+" ", TIC_HALFSTAGE, TIC_HALFSTAGE, hItemPar, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSMASK1STAGE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idMask1stage ), TVIS_STATEIMAGEMASK );
	}

	// General classification sorted on stano
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_GENERATETSTANOSORTEDGENERAL) )
	{
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV113 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_CLASSSTANOSORTEDGENERAL );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idGeneralStaNoSorted ), TVIS_STATEIMAGEMASK );
	}

	// General classification
	hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV55 )+" ", TIC_CLASSGENERAL, TIC_CLASSGENERAL, aHsParent, TVI_FIRST );
	ctrlTree.SetItemData( hItem, TI_CLASSGENERAL );
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
		ctrlTree.SetItemState( hItem,
			InitDetermineState( &pHalfStage->m_idGeneral ), TVIS_STATEIMAGEMASK );

	if( pHalfStage->m_stageType==ST_TT_GROSS )
	{
		// Time trial arrival listing
		hItem = ctrlTree.InsertItem( " "+LoadStr( IDS_DIV104 )+" ", TIC_TTARRIVALLIST, TIC_TTARRIVALLIST, aHsParent, TVI_FIRST );
		ctrlTree.SetItemData( hItem, TI_TTARRIVALLIST );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_idTTArrival ), TVIS_STATEIMAGEMASK );
	}

	// Set the item data for the half stage
	ctrlTree.SetItemData( aHsParent, nHS );
	if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
		ctrlTree.SetItemState( aHsParent,
			InitDetermineState( &pHalfStage->m_idStage ), TVIS_STATEIMAGEMASK );

	// Add eventually a communique
	if ( !pHalfStage->m_communique.IsEmpty() )
	{
		hItem = ctrlTree.InsertItem( " "+pHalfStage->m_communique.m_title+" ", TIC_COMMUNIQUE, TIC_COMMUNIQUE, aHsParent );
		ctrlTree.SetItemData( hItem, TI_COMMUNIQUE );
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			ctrlTree.SetItemState( hItem,
				InitDetermineState( &pHalfStage->m_communique.m_id ), TVIS_STATEIMAGEMASK );
	}

	// Add eventually a signouts list
	if ( pHalfStage->m_signOuts.GetCount() )
		ctrlTree.SetItemData( ctrlTree.InsertItem( " "+LoadStr( IDS_DIV43 )+" ", TIC_SIGNOUTS, TIC_SIGNOUTS, aHsParent ), TI_SIGNOUTS );

	return aHsParent;
}

// Sets the internal members to represent the current selection
// We get the item's item data and sort out what it is
// We fill m_eiSelected.m_tiConcerning, m_nHalfStage and m_nFullStage here
void CTreeViewMain::ItemSwitch()
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	m_eiSelected = GetEventItem( GetTreeCtrl().GetSelectedItem() );
	if( m_eiSelected.m_nFullStage && m_eiSelected.m_nHalfStage )
		m_pHalfStage = m_pDoc->StagesGet( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
}

CEventItem CTreeViewMain::GetEventItem(HTREEITEM hti)
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	CEventItem ei;
	ei.SetDoc( m_pDoc );
	int n = ctrlTree.GetItemData( hti );
	if( n>0 )
	{
		// It is a full or half stage

		ei.m_nHalfStage = n;
		ei.m_nFullStage = n;

		// Check the item's parent
		n = ctrlTree.GetItemData(
				ctrlTree.GetParentItem(
					hti ) );
		if( TI_ROOT == n )
		{
			// This is a full stage
			ei.m_tiConcerning = TI_FULLSTAGE;
			// So there is no half stage involved
			ei.m_nHalfStage = 0;
		}
		else
		{
			// The item is a half stage
			ei.m_tiConcerning = TI_HALFSTAGE;
			// So its parent is a full stage
			ei.m_nFullStage = n;
		}
	}
	else
	{
		// It is a specific item


		switch( (TREEITEMS)n )
		{
			case TI_COMMUNIQUE:
				ei.m_tiConcerning = (TREEITEMS)n;

				// Check the communiqué's parent
				n = ctrlTree.GetItemData(
						ctrlTree.GetParentItem(
							hti ) );
				if(	TI_ROOT == n )
				{
					// This is the root communiqué
					// with no full nor half stage parent
					ei.m_nFullStage = 0;
					ei.m_nHalfStage = 0;
				}
				else
				{
					ei.m_nHalfStage = n;
					ei.m_nFullStage = n;
					// Check the communiqué's parent's parent
					n = ctrlTree.GetItemData(
							ctrlTree.GetParentItem(
								ctrlTree.GetParentItem(
									hti ) ) );
					if(	TI_ROOT == n )
						// Apparently this is a full stage's communiqué
						// with no half stage parent involved
						ei.m_nHalfStage = 0;
					else
					{
						// Apparently this is a half stage's communiqué
						ei.m_nFullStage = n;
					}

				}
				break;
			case TI_SIGNOUTS:
			case TI_TIMETRIALORDER:
			case TI_SPRINT:
			case TI_CLIMB:
			case TI_MOSTAGGRESSIVE:
			case TI_POINTS:
			case TI_CROSSOUTLIST:
			case TI_SIGNINLIST:
			case TI_TTARRIVALLIST:
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSTEAMS:
			case TI_CLASSMASK1:
			case TI_CLASSMASK2:
			case TI_CLASSMASK3:
			case TI_CLASSMASK4:
			case TI_CLASSMASK5:
			case TI_CLASSMASK6:
			case TI_CLASSMASK7:
			case TI_CLASSMASK8:
			case TI_CLASSMASK9:
			case TI_CLASSMASK10:
					ei.m_tiConcerning = (TREEITEMS)n;
					ei.m_nFullStage =
						ctrlTree.GetItemData(
							ctrlTree.GetParentItem(
								ctrlTree.GetParentItem(
									hti ) ) );
					ei.m_nHalfStage = 
						ctrlTree.GetItemData(
							ctrlTree.GetParentItem(
								hti ) );
				break;
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
					ei.m_tiConcerning = (TREEITEMS)n;
					ei.m_nFullStage =
						ctrlTree.GetItemData(
							ctrlTree.GetParentItem(
								ctrlTree.GetParentItem(
									ctrlTree.GetParentItem(
										hti ) ) ) );
					ei.m_nHalfStage = 
						ctrlTree.GetItemData(
							ctrlTree.GetParentItem(
								ctrlTree.GetParentItem(
									hti ) ) );
				break;
			case TI_COMPETITORS:
			case TI_TEAMS:
			case TI_LISTCOMPETITORS1:
			case TI_LISTCOMPETITORS2:
			default:
					ei.m_tiConcerning = (TREEITEMS)n;
					ei.m_nFullStage = 0;
					ei.m_nHalfStage = 0;
				break;
		}
	}
	return ei;
}

// We make the details view to represent the current selection
// according to the internal members
void CTreeViewMain::ItemDisplay()
{
	// Make sure this window is the active pane
	((CSplitterWnd*)((CSplitterWnd*)GetParent())->GetParent())->SetActivePane(0,0);
	((CSplitterWnd*)GetParent())->SetActivePane(0,0,this);
	this->SetFocus();

	// Empty the ID bar to suit it for not-allowed selections
	if(m_pIdView->IsWindowVisible())
		m_pIdView->Reset();
	
	CChildFrame* pFrame = (CChildFrame*)GetParentFrame();

	switch( m_eiSelected.m_tiConcerning )
	{
	// ROOT ITEM
		case TI_ROOT:
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// CROSS OUT LIST
		case TI_CROSSOUTLIST:
			m_pIdView->Set( &m_pHalfStage->m_idCrossOut );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// SIGN IN LIST
		case TI_SIGNINLIST:
			m_pIdView->Set( &m_pHalfStage->m_idSignIn );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MOST AGGRESSIVE
		case TI_MOSTAGGRESSIVE:
			m_pIdView->Set( &m_pHalfStage->m_idMostAggressive );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// CLIMB
		case TI_CLIMB:
			m_pIdView->Set( &m_pHalfStage->m_idClimbs );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// POINTS
		case TI_POINTS:
			m_pIdView->Set( &m_pHalfStage->m_idPoints );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// SPRINT
		case TI_SPRINT:
			m_pIdView->Set( &m_pHalfStage->m_idSprints );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// TIME TRIAL ORDER
		case TI_TIMETRIALORDER:
			m_pIdView->Set( &m_pHalfStage->m_idStartList );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// LIST COMPETITORS TYPE 1
		case TI_LISTCOMPETITORS1:
			m_pIdView->Set( &m_pDoc->m_idCompetitors );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// LIST COMPETITORS TYPE 2
		case TI_LISTCOMPETITORS2:
			m_pIdView->Set( &m_pDoc->m_idTeams );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// TIME TRIAL ARRIVAL LISTING
		case TI_TTARRIVALLIST:
			m_pIdView->Set( &m_pHalfStage->m_idTTArrival );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// GENERAL CLASSIFICATION ON STANO
		case TI_CLASSSTANOSORTEDGENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idGeneralStaNoSorted );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// GENERAL CLASSIFICATION
		case TI_CLASSGENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idGeneral );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 1 STAGE CLASSIFICATION
		case TI_CLASSMASK1STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask1stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 1 GENERAL CLASSIFICATION
		case TI_CLASSMASK1GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask1gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 2 STAGE CLASSIFICATION
		case TI_CLASSMASK2STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask2stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 2 GENERAL CLASSIFICATION
		case TI_CLASSMASK2GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask2gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 3 STAGE CLASSIFICATION
		case TI_CLASSMASK3STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask3stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 3 GENERAL CLASSIFICATION
		case TI_CLASSMASK3GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask3gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 4 STAGE CLASSIFICATION
		case TI_CLASSMASK4STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask4stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 4 GENERAL CLASSIFICATION
		case TI_CLASSMASK4GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask4gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 5 STAGE CLASSIFICATION
		case TI_CLASSMASK5STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask5stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 5 GENERAL CLASSIFICATION
		case TI_CLASSMASK5GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask5gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 6 STAGE CLASSIFICATION
		case TI_CLASSMASK6STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask6stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 6 GENERAL CLASSIFICATION
		case TI_CLASSMASK6GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask6gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 7 STAGE CLASSIFICATION
		case TI_CLASSMASK7STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask7stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 7 GENERAL CLASSIFICATION
		case TI_CLASSMASK7GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask7gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 8 STAGE CLASSIFICATION
		case TI_CLASSMASK8STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask8stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 8 GENERAL CLASSIFICATION
		case TI_CLASSMASK8GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask8gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 9 STAGE CLASSIFICATION
		case TI_CLASSMASK9STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask9stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 9 GENERAL CLASSIFICATION
		case TI_CLASSMASK9GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask9gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 10 STAGE CLASSIFICATION
		case TI_CLASSMASK10STAGE:
			m_pIdView->Set( &m_pHalfStage->m_idMask10stage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// MASK 10 GENERAL CLASSIFICATION
		case TI_CLASSMASK10GENERAL:
			m_pIdView->Set( &m_pHalfStage->m_idMask10gen );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// TEAMS CLASSIFICATION
		case TI_CLASSTEAMS:
			m_pIdView->Set( &m_pHalfStage->m_idTeams );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// HALFSTAGE CLASSIFICATION
		case TI_HALFSTAGE:
			m_pIdView->Set( &m_pHalfStage->m_idStage );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	// COMPETITORS VIEW
		case TI_COMPETITORS:
			if( pFrame->ShowViewListCompetitors() )
				return;
			break;
	// TEAMS VIEW
		case TI_TEAMS:
			if( pFrame->ShowViewListTeams() )
				return;
			break;
	// COMMUNIQUE
		case TI_COMMUNIQUE:
			// Half stage communiqué
			if( m_eiSelected.m_nHalfStage )
				m_pIdView->Set( &(m_pHalfStage->m_communique.m_id) );
			else
				// Full stage communiqué
				if( m_eiSelected.m_nFullStage )
					m_pIdView->Set( &m_pDoc->StagesGet(m_eiSelected.m_nFullStage)->m_communique.m_id );
				else
				// Event communiqué
					m_pIdView->Set( &m_pDoc->m_communique.m_id );
			if( pFrame->ShowViewPresentation()->Navigate(&m_eiSelected) ) return;
			break;
	}
	// Default reaktion
	pFrame->ShowViewDetailsEmpty();
}

void CTreeViewMain::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	CUpdateViewHint* pUVH = (CUpdateViewHint*)pHint;

	// Note that the default is to do nothing, since the update
	// request can as well be intented for a very different type
	// of view

	if( pUVH && (pUVH->GetReason() == UV_PUBLISHED) )
	{
		// Some item's publication check box has to be changed

		CId* pId = (CId*)pUVH->GetConcerning();
		HTREEITEM hItem = GetStageItem(
			pUVH->GetFullStage(),
			pUVH->GetHalfStage(),
			(TREEITEMS)lHint
		);
		if( hItem )
		{
			// Draw the appropriate check box
			ctrlTree.SetItemState( hItem,
				INDEXTOSTATEIMAGEMASK(
					m_pDoc->m_pListID->Published(pId) ? 2 : 1 ),
				TVIS_STATEIMAGEMASK );
		}
		return;
	}
	switch( lHint )
	{
		case TI_SPARECOMPETITORS:
		case TI_COMPETITORS:
			UpdateCountCompetitors();
			break;
		case TI_TEAMS:
			UpdateCountTeams();
			break;
		case TI_SETTINGS:
			DrawTreeFromScratch();
			break;
		case TI_ROOT:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_CONFIGURED:
						{
							CStageRaceDoc* pDoc = (CStageRaceDoc*)pUVH->GetConcerning();
							ctrlTree.SetItemText( ctrlTree.GetRootItem(), " "+pDoc->GetTitle()+" " );
							ItemDisplay();
						}
						break;
					//default:
						// Wrong behavior
				}
			else
			{
				// Possibly because updated TOC
			}
			break;
		case TI_FULLSTAGE:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							CFullStage* pFS = (CFullStage*)pUVH->GetConcerning();
							// Add the new full stage to the view
							HTREEITEM hNewOne = ctrlTree.InsertItem( " " + CEventItem::StagesMakeIDString(pUVH->GetFullStage(),m_pDoc) + ": " + pFS->m_date+" ",
								TIC_FULLSTAGE,
								TIC_FULLSTAGE,
								ctrlTree.GetRootItem() );
							// Set the item data
							ctrlTree.SetItemData( hNewOne, pUVH->GetFullStage() );
							// Make this new one the current selection
							ctrlTree.Select( hNewOne, TVGN_CARET );

							if( m_eiSelected.m_tiConcerning==lHint )
								ItemDisplay();
						}
						break;
					case UV_CONFIGURED:
						{
							CFullStage* pFS = (CFullStage*)pUVH->GetConcerning();
							// Update the title in the view
							ctrlTree.SetItemText( GetStage( pUVH->GetFullStage() ),
								" " + CEventItem::StagesMakeIDString(pUVH->GetFullStage(),m_pDoc) + ": " + pFS->m_date );
						}
						break;
					case UV_DELETED:
						DrawTreeFromScratch();
						break;
					//default:
						// Wrong behavior
				}
			else
			{
				// Wrong behavior
			}
			break;
		case TI_SIGNOUTS:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							ctrlTree.SetItemData(
								ctrlTree.InsertItem( " "+LoadStr( IDS_DIV43 )+" ",
									TIC_SIGNOUTS,
									TIC_SIGNOUTS,
									GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() )
								),
								TI_SIGNOUTS
							);
						}
						break;
					case UV_DELETED:
						{
							ctrlTree.DeleteItem( GetStageItem(
								GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() ),
								TI_SIGNOUTS ) );
						}
						break;
					//default:
						// Wrong behavior
				}
			// Necessary when added and when deleted
			ItemDisplay();
			break;
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_HALFSTAGE:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							if( m_pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_STAGENUMBERING_SUPPRESS )
									&& (m_pDoc->StagesHalfCount( pUVH->GetFullStage() )==2) )
							{
								// Do this so that the first half stage of a stage
								// that is displaying only the stage number gets
								// updated to display [stage no.]-[half stage no.]
								DrawTreeFromScratch();
							}
							else
							{
								CHalfStage* pHS = (CHalfStage*)pUVH->GetConcerning();
								// Add the new half stage to the view
								DrawHalfStage( pHS, pUVH->GetFullStage(),
									pUVH->GetHalfStage(), GetStage( pUVH->GetFullStage() ) );
								ItemDisplay();
							}
						}
						break;
					case UV_CONFIGURED:
						{
							CHalfStage* pHS = (CHalfStage*)pUVH->GetConcerning();
							// Update the item in the view
							LockWindowUpdate();

							// Update the view
							HTREEITEM hHalfStage = GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() );
							HTREEITEM hParent    = ctrlTree.GetParentItem( hHalfStage );
							HTREEITEM hNewHalfStage;

							hNewHalfStage = DrawHalfStage( pHS, pUVH->GetFullStage(), pUVH->GetHalfStage(), hParent, hHalfStage );
							ctrlTree.DeleteItem( hHalfStage );
							ctrlTree.Select( hHalfStage, TVGN_CARET );
							ctrlTree.Expand( hHalfStage, TVE_EXPAND );

							ItemDisplay();

							UnlockWindowUpdate();
						}
						break;
					case UV_DELETED:
						DrawTreeFromScratch();
						break;
					//default:
						// Wrong behavior
				}
			else
			{
				// Possibly because updated
			}
			break;
		case TI_COMMUNIQUE:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							CCommunique* pComm = (CCommunique*)pUVH->GetConcerning();
							// Insert the new item
							HTREEITEM hItem = ctrlTree.InsertItem( " "+pComm->m_title+" ", TIC_COMMUNIQUE, TIC_COMMUNIQUE, 
								GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() ) );
							// Set the item data
							ctrlTree.SetItemData( hItem, TI_COMMUNIQUE );
							// Make this new one the current selection
							ctrlTree.Select( hItem, TVGN_CARET );
							ctrlTree.SetItemState( hItem,
								InitDetermineState( &pComm->m_id ), TVIS_STATEIMAGEMASK );

							ItemDisplay();
						}
						break;
					case UV_UPDATED:
						{
							CCommunique* pComm = (CCommunique*)pUVH->GetConcerning();
							// Update the title in the view
							ctrlTree.SetItemText( 
								GetStageItem(
									GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() ),
									TI_COMMUNIQUE ),
								" "+pComm->m_title+" " );

							ItemDisplay();
						}
						break;
					case UV_DELETED:
						{
							CCommunique* pComm = (CCommunique*)pUVH->GetConcerning();
							// Empty it
							if( GetDocument()->m_pListID->Published( &(pComm->m_id) ) )
								GetDocument()->m_pListID->UnPublish( pComm->m_id.GetNo() );

							// Also remove it from the view
							ctrlTree.DeleteItem( 
								GetStageItem(
									GetStage( pUVH->GetFullStage(), pUVH->GetHalfStage() ),
									TI_COMMUNIQUE ) );

							ItemDisplay();
						}
						break;
					//default:
						// Wrong behavior
				}
			else
			{
				// Wrong behavior
			}
			break;
	}
	if( lHint == m_eiSelected.m_tiConcerning )
		ItemDisplay();
}

HTREEITEM CTreeViewMain::GetStageItem(int nFS, int nHS, TREEITEMS tiType)
{
	HTREEITEM hItem;
	// If no full stage provided,
	// we search the tree root area
	if( !nFS )
	{
		// See if the item is a root item
		hItem = GetStageItem( tiType );
		if( !hItem )
		{
			// If not:
			// See if the item is a child of the root item
			// such as a general communiqué
			hItem = GetStageItem( GetStageItem( TI_ROOT ), tiType );
			if( !hItem )
			{
				// If not:
				// See if the item is a child of the competitors leaf
				hItem = GetStageItem( TI_COMPETITORS );
				hItem = GetStageItem( hItem, tiType );
			}
		}
	}
	// If a full stage is provided,
	// we get the particular stage or half stage
	else
	{
		hItem = GetStage( nFS, nHS );
		if( nHS )
		{
			// If not the half stage itself, get a child item
			if( tiType!=TI_HALFSTAGE )
			{
				// It could be a mask sub folder
				switch( tiType )
				{
					case TI_CLASSMASK1STAGE:
					case TI_CLASSMASK1GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK1 );
						break;
					case TI_CLASSMASK2STAGE:
					case TI_CLASSMASK2GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK2 );
						break;
					case TI_CLASSMASK3STAGE:
					case TI_CLASSMASK3GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK3 );
						break;
					case TI_CLASSMASK4STAGE:
					case TI_CLASSMASK4GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK4 );
						break;
					case TI_CLASSMASK5STAGE:
					case TI_CLASSMASK5GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK5 );
						break;
					case TI_CLASSMASK6STAGE:
					case TI_CLASSMASK6GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK6 );
						break;
					case TI_CLASSMASK7STAGE:
					case TI_CLASSMASK7GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK7 );
						break;
					case TI_CLASSMASK8STAGE:
					case TI_CLASSMASK8GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK8 );
						break;
					case TI_CLASSMASK9STAGE:
					case TI_CLASSMASK9GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK9 );
						break;
					case TI_CLASSMASK10STAGE:
					case TI_CLASSMASK10GENERAL:
						// Get one deeper
						hItem = GetStageItem( hItem, TI_CLASSMASK10 );
						break;
				}
				// Normal
				hItem = GetStageItem( hItem, tiType );
			}
		}
		else if( nFS )
		{
			// If not the full stage itself, get a child item
			if( tiType!=TI_FULLSTAGE )
				hItem = GetStageItem( hItem, tiType );
		}
	}
	return hItem;
}

HTREEITEM CTreeViewMain::GetStage(int nFS/*=0*/, int nHS/*=0*/)
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	if( nFS )
	{
		// Search the particular full stage
		HTREEITEM hSkipFS = ctrlTree.GetChildItem(
			ctrlTree.GetRootItem() );
		while( ctrlTree.GetParentItem( hSkipFS ) ==
			ctrlTree.GetRootItem() )
		{
			if( ctrlTree.GetItemData( hSkipFS )==nFS )
			{
				// Full stage found
				if( nHS )
				{
					// Search the particular child
					HTREEITEM hSkipHS = ctrlTree.GetChildItem( hSkipFS );
					while( ctrlTree.GetParentItem( hSkipHS ) == hSkipFS )
					{
						// Half stage found
						if( ctrlTree.GetItemData( hSkipHS )==nHS )
							return hSkipHS;
						hSkipHS = ctrlTree.GetNextItem( hSkipHS, TVGN_NEXT );
					}
				}
				else
					return hSkipFS;
				break;
			}
			hSkipFS = ctrlTree.GetNextItem( hSkipFS, TVGN_NEXT );
		}
	}
	else
	{
		return ctrlTree.GetRootItem();
	}
	// This is basically to make the compiler happy
	// Let's hope it is not actually being used...
	return NULL;
}

HTREEITEM CTreeViewMain::GetStageItem(HTREEITEM hParent, TREEITEMS tiItem)
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	// Search the particular tree item
	HTREEITEM hSkip = ctrlTree.GetChildItem( hParent );
	while( ctrlTree.GetParentItem( hSkip ) == hParent )
	{
		// Half stage found
		if( ctrlTree.GetItemData( hSkip )==tiItem )
			return hSkip;
		hSkip = ctrlTree.GetNextItem( hSkip, TVGN_NEXT );
	}
	return NULL;
}

HTREEITEM CTreeViewMain::GetStageItem(TREEITEMS tiType)
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	// Search the particular tree item
	HTREEITEM hSkip = ctrlTree.GetRootItem();
	while( hSkip )
	{
		// Requested item found
		if( ctrlTree.GetItemData( hSkip )==tiType )
			return hSkip;
		hSkip = ctrlTree.GetNextItem(hSkip, TVGN_NEXT);
	}
	return hSkip;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// CONFIGURATION

void CTreeViewMain::OnConfigureInsertFullstage() 
{
	m_pDoc->StagesFullNew();
}

void CTreeViewMain::OnConfigureInsertHalfstage()
{
	// Only enter when current selection somehow involves a full stage
	if ( m_eiSelected.m_nFullStage )
		m_pDoc->StagesHalfNew(m_eiSelected.m_nFullStage);
}

void CTreeViewMain::OnUpdateConfigureInsertHalfStage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_nFullStage>0 );
}

void CTreeViewMain::OnConfigureDelete() 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_COMMUNIQUE:
			m_pDoc->CommuniqueDelete( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		case TI_HALFSTAGE:
			m_pDoc->StagesDelete( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		case TI_FULLSTAGE:
			m_pDoc->StagesDelete( m_eiSelected.m_nFullStage );
			break;
		default:
			MessageBox( LoadStr( IDS_MBC_36 ), LoadStr( IDS_MBT_36 ), MB_OK );
	}
}

void CTreeViewMain::OnUpdateConfigureDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_eiSelected.m_tiConcerning==TI_HALFSTAGE) ||
		(m_eiSelected.m_tiConcerning==TI_FULLSTAGE) || (m_eiSelected.m_tiConcerning==TI_COMMUNIQUE) );
}

void CTreeViewMain::OnConfigureConfigure() 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->StagesHalfEdit( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		case TI_FULLSTAGE:
			m_pDoc->StagesFullEdit( m_eiSelected.m_nFullStage );
			break;
		case TI_ROOT:
			m_pDoc->Settings();
			break;
		default:
			MessageBox( LoadStr( IDS_MBC_32 ), LoadStr( IDS_MBT_32 ), MB_OK );
	}
}

void CTreeViewMain::OnUpdateConfigureConfigure(CCmdUI* pCmdUI) 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
		case TI_FULLSTAGE:
		case TI_ROOT:
			pCmdUI->Enable();
			break;
		default:
			pCmdUI->Enable( false );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// GENERATING

void CTreeViewMain::OnGenerateSelection() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_ROOT:
			m_pDoc->GenerateToc();
			break;
		case TI_COMPETITORS:
		case TI_TEAMS:
		case TI_LISTCOMPETITORS1:
		case TI_LISTCOMPETITORS2:
			m_pDoc->GenerateCompetitors();
			break;
		case TI_COMMUNIQUE:
			m_pDoc->GenerateCommunique(m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
//			m_pDoc->UpdateAllViews( NULL, TI_ROOT );
			break;
		case TI_CROSSOUTLIST:
			m_pDoc->GenerateCrossout();
			break;
		case TI_SIGNINLIST:
			m_pDoc->GenerateSignin();
			break;
		case TI_HALFSTAGE:
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_TTARRIVALLIST:
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
		case TI_CLASSMASK1:
		case TI_CLASSMASK2:
		case TI_CLASSMASK3:
		case TI_CLASSMASK4:
		case TI_CLASSMASK5:
		case TI_CLASSMASK6:
		case TI_CLASSMASK7:
		case TI_CLASSMASK8:
		case TI_CLASSMASK9:
		case TI_CLASSMASK10:
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
		case TI_CLASSTEAMS:
			m_pDoc->GenerateClass( CStageRaceDoc::PWH_THIS, m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
//			m_pDoc->UpdateAllViews( NULL, TI_HALFSTAGE );
			break;
		case TI_TIMETRIALORDER:
			m_pDoc->GenerateOrder( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
//			m_pDoc->UpdateAllViews( NULL, TI_TIMETRIALORDER );
			break;
	}
}

void CTreeViewMain::OnUpdateGenerateSelection(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.IsPublicable() );
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// COMMUNIQUÉS

void CTreeViewMain::OnInsertCommunique() 
{
	// Check the selections status
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_ROOT:
		case TI_FULLSTAGE:
		case TI_HALFSTAGE:
		case TI_SIGNOUTS:
		case TI_TIMETRIALORDER:
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_CROSSOUTLIST:
		case TI_SIGNINLIST:
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
		case TI_TTARRIVALLIST:
		case TI_CLASSMASK1:
		case TI_CLASSMASK2:
		case TI_CLASSMASK3:
		case TI_CLASSMASK4:
		case TI_CLASSMASK5:
		case TI_CLASSMASK6:
		case TI_CLASSMASK7:
		case TI_CLASSMASK8:
		case TI_CLASSMASK9:
		case TI_CLASSMASK10:
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
		case TI_CLASSTEAMS:
			m_pDoc->CommuniqueEdit( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
	}
}

void CTreeViewMain::OnUpdateInsertCommunique(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( (m_eiSelected.m_nFullStage || (m_eiSelected.m_tiConcerning==TI_ROOT)) && // correct leaf
		m_pDoc->CommuniqueGet( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage )->IsEmpty() ); // not already exists	
}

void CTreeViewMain::OnEditDelete() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_COMMUNIQUE:
			m_pDoc->CommuniqueDelete( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
	}
}

void CTreeViewMain::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_COMMUNIQUE:
			pCmdUI->Enable();
			break;
		default:
			pCmdUI->Enable(FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// SIGN OUTS

void CTreeViewMain::OnInsertSignouts() 
{
	if( m_eiSelected.m_nHalfStage || (m_eiSelected.m_tiConcerning==TI_SIGNOUTS) )
		m_pDoc->InputSignOuts( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
}

void CTreeViewMain::OnUpdateInsertSignouts(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_nHalfStage || (m_eiSelected.m_tiConcerning==TI_SIGNOUTS) );
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// TOOLS RELATED

void CTreeViewMain::OnToolsExportoptic() 
{
	m_pDoc->ExportOptic(m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage);
}

void CTreeViewMain::OnToolsExportchronx() 
{
	m_pDoc->ExportChronx(m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage);
}

void CTreeViewMain::OnToolsExportttware() 
{
	m_pDoc->ExportTTWare(m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage);
}

void CTreeViewMain::OnUpdateToolsExportoptic(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_nHalfStage &&
		!((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() );
}

void CTreeViewMain::OnUpdateToolsExportchronx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_nHalfStage &&
		!((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() );
}

void CTreeViewMain::OnUpdateToolsExportttware(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_nHalfStage &&
		!((CStageRaceApp*) AfxGetApp())->m_key.FastIsProtected() &&
		(m_pDoc->StagesGet( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage )->m_stageType!=ST_NORMAL) );
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// TREE ITEM RELATED

bool CTreeViewMain::OnEditEditselection() 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_TIMETRIALORDER:
			m_pDoc->InputStartingOrder( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		case TI_SIGNOUTS:
			m_pDoc->InputSignOuts( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		case TI_HALFSTAGE:
			m_pDoc->InputRanking( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0 );
			break;
		case TI_SPRINT:
			m_pDoc->InputRanking( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1 );
			break;
		case TI_POINTS:
			m_pDoc->InputRanking( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputRanking( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4 );
			break;
		case TI_CLIMB:
			m_pDoc->InputRanking( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2 );
			break;
		case TI_COMMUNIQUE:
			m_pDoc->CommuniqueEdit( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		default:
			return false;
	}
	return true;
}

void CTreeViewMain::OnUpdateEditEditselection(CCmdUI* pCmdUI) 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_TIMETRIALORDER:
		case TI_SIGNOUTS:
		case TI_HALFSTAGE:
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_COMMUNIQUE:
			pCmdUI->Enable();
			break;
		default:
			pCmdUI->Enable(FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers
// PUBLICATIONS RELATED

bool CTreeViewMain::IsItemChecked(HTREEITEM hItem)
{
	return (GetTreeCtrl().GetItemState( hItem, TVIS_STATEIMAGEMASK ))>>12 == 2;
}

UINT CTreeViewMain::InitDetermineState(CId *pId)
{
	if( pId->IsPublished() )
	{
		// This possibly publish it when it is already
		// published before in the ID's list, but this
		// is not really a problem; we require it to be
		// published at least once to be registered
		GetDocument()->m_pListID->Register( pId );
		return INDEXTOSTATEIMAGEMASK( 2 );
	}
	else
		return INDEXTOSTATEIMAGEMASK( 1 );
}


void CTreeViewMain::OnEditPublish() 
{
	CheckItem();
}

void CTreeViewMain::OnUpdateEditPublish(CCmdUI* pCmdUI) 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if( hItem )
	{
		int nTestValue = GetTreeCtrl().GetItemState( hItem, TVIS_STATEIMAGEMASK );
		nTestValue = nTestValue >> 12;
		pCmdUI->Enable( nTestValue );
		if( nTestValue )
			pCmdUI->SetCheck( nTestValue-1 );
		else
			pCmdUI->SetCheck( 0 );
	}
	else
		pCmdUI->SetCheck( 0 );
}

void CTreeViewMain::CheckItem()
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	CUpdateViewHint UVH(
		UV_PUBLISHED,
		m_pIdView->Get(),
		m_eiSelected.m_nFullStage,
		m_eiSelected.m_nHalfStage
	);
	if( m_pDoc->m_pListID->Published( m_pIdView->Get() ) )
	{
		// We remove the item in the id's list
		GetDocument()->m_pListID->UnPublish( m_pIdView->Get()->GetNo(), &UVH, m_eiSelected.m_tiConcerning );
	}
	else
	{
		// We insert the item in the id's list
		GetDocument()->m_pListID->Publish( m_pIdView->Get(), &UVH, m_eiSelected.m_tiConcerning );
	}
}

/////////////////////////////////////////////////////////////////////////////
// Stage functions

void CTreeViewMain::OnUpdateArrivalFunctionsCheck(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		(
			m_eiSelected.m_tiConcerning == TI_HALFSTAGE
		)
		&&
		m_pHalfStage
		&& 
		(m_pHalfStage->m_stageType==ST_NORMAL)
	);
}

void CTreeViewMain::OnUpdateArrivalFunctionsGroupt1(CCmdUI* pCmdUI) 
{
	OnUpdateArrivalFunctionsCheck(pCmdUI);
}

void CTreeViewMain::OnUpdateArrivalFunctionsGroupt2(CCmdUI* pCmdUI) 
{
	OnUpdateArrivalFunctionsCheck(pCmdUI);
}

void CTreeViewMain::OnUpdateArrivalFunctionsGroupt3(CCmdUI* pCmdUI) 
{
	OnUpdateArrivalFunctionsCheck(pCmdUI);
}

void CTreeViewMain::OnUpdateArrivalFunctionsImport(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		(
			(m_eiSelected.m_tiConcerning == TI_HALFSTAGE)
			|| (m_eiSelected.m_tiConcerning == TI_CLIMB)
			|| (m_eiSelected.m_tiConcerning == TI_SPRINT)
			|| (m_eiSelected.m_tiConcerning == TI_POINTS)
			|| (m_eiSelected.m_tiConcerning == TI_MOSTAGGRESSIVE)
		)
		&&
		m_pHalfStage
		&& 
		(
			(m_pHalfStage->m_stageType==ST_NORMAL)
			|| (m_pHalfStage->m_stageType==ST_TT_NET)
		)
	);
}

void CTreeViewMain::OnUpdateArrivalFunctionsRemove1xseconds(CCmdUI* pCmdUI) 
{
	OnUpdateArrivalFunctionsCheck(pCmdUI);
}

void CTreeViewMain::OnUpdateArrivalFunctionsRemovegaps(CCmdUI* pCmdUI) 
{
	OnUpdateArrivalFunctionsCheck(pCmdUI);
}

void CTreeViewMain::OnArrivalFunctionsCheck() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionCheck( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsGroupt1() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0, 1 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1, 1 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3, 1 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2, 1 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4, 1 );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsGroupt2() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0, 2 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1, 2 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3, 2 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2, 2 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4, 2 );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsGroupt3() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0, 3 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1, 3 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3, 3 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2, 3 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionGroupt( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4, 3 );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsImport() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionImport( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionImport( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionImport( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionImport( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionImport( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4 );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsRemove1xseconds() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionRemove1xseconds( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionRemove1xseconds( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionRemove1xseconds( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionRemove1xseconds( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionRemove1xseconds( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4 );
			break;
		default:
			return;
	}
}

void CTreeViewMain::OnArrivalFunctionsRemovegaps() 
{
	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_HALFSTAGE:
			m_pDoc->InputFunctionRemovegaps( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 0 );
			break;
		case TI_SPRINT:
			m_pDoc->InputFunctionRemovegaps( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 1 );
			break;
		case TI_POINTS:
			m_pDoc->InputFunctionRemovegaps( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 3 );
			break;
		case TI_CLIMB:
			m_pDoc->InputFunctionRemovegaps( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 2 );
			break;
		case TI_MOSTAGGRESSIVE:
			m_pDoc->InputFunctionRemovegaps( m_eiSelected.m_nFullStage, m_eiSelected.m_nHalfStage, 4 );
			break;
		default:
			return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewMain message handlers

void CTreeViewMain::OnNextPane() 
{
	// Delicate business beyond this point
	// We order the CStageRaceSplitFrame that somewhere is
	//  the parent of this class to switch the active pane
	((CChildFrame*)
		((CSplitterWnd*)
			((CSplitterWndFixed*)GetParent())
				->GetParent())
					->GetParent())
						->SetActivePaneDetailView();
}

UINT CTreeViewMain::GetResourceID()
{
	return IDR_TREEVIEWMAIN;
}

void CTreeViewMain::OnEditCompetitors() 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	ctrlTree.Select(
		GetStageItem( TI_COMPETITORS ),
		TVGN_CARET
	);
	OnNextPane();
}

void CTreeViewMain::OnUpdateEditCompetitors(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_tiConcerning != TI_COMPETITORS );
}

void CTreeViewMain::OnEditTeams() 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	ctrlTree.Select(
		GetStageItem( TI_TEAMS ),
		TVGN_CARET
	);
	OnNextPane();
}

void CTreeViewMain::OnUpdateEditTeams(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.m_tiConcerning != TI_TEAMS );
}

void CTreeViewMain::UpdateCountCompetitors()
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	TCHAR czBuffer1[10];
	TCHAR czBuffer2[10];
	_itot( m_pDoc->CompetitorsCount(), czBuffer1, 10 );
	_itot( m_pDoc->SpareCompetitorsCount(), czBuffer2, 10 );
	if( m_pDoc->SpareCompetitorsCount() )
		ctrlTree.SetItemText(
				GetStageItem( TI_COMPETITORS ),
				" "+LoadStr( IDS_DIV36 )+" ["+CString(czBuffer1)+
				" ("+CString(czBuffer2)+" "+
				LoadStr( IDS_DIV25 )+")] "
			);
	else
		ctrlTree.SetItemText(
				GetStageItem( TI_COMPETITORS ),
				" "+LoadStr( IDS_DIV36 )+" ["+CString(czBuffer1)+"] "
			);
}

void CTreeViewMain::UpdateCountTeams()
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	TCHAR czBuffer[10];
	_itot( m_pDoc->TeamsCount(), czBuffer, 10 );
	ctrlTree.SetItemText(
			GetStageItem( TI_TEAMS ),
			" "+LoadStr( IDS_DIV37 )+" ["+CString(czBuffer)+"] "
		);
}

void CTreeViewMain::ContextState(CPoint point)
{
	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTTREESTATE );
	// Show the menu
	ClientToScreen(&point);
	aMenu.GetSubMenu(0)->SetDefaultItem( ID_EDIT_PUBLISH, false );
	aMenu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
											point.x+2,
											point.y+2,
											this->GetParentFrame() );
}

void CTreeViewMain::ContextTree(CPoint point)
{
	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTTREEITEMS );
	// Show the menu
	ClientToScreen(&point);
	aMenu.GetSubMenu(10)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
											point.x+2,
											point.y+2,
											this->GetParentFrame() );
}

void CTreeViewMain::ContextItem(CPoint point)
{
	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTTREEITEMS );

	// Choose one of the sub menus
	CMenu* pChosenMenu;

	switch( m_eiSelected.m_tiConcerning )
	{
		case TI_FULLSTAGE:
			pChosenMenu = aMenu.GetSubMenu(0);
			break;
		case TI_TTARRIVALLIST:
		case TI_HALFSTAGE:
			pChosenMenu = aMenu.GetSubMenu(1);
			break;
		case TI_ROOT:
			pChosenMenu = aMenu.GetSubMenu(2);
			break;
		case TI_COMPETITORS:
			pChosenMenu = aMenu.GetSubMenu(3);
			break;
		case TI_TEAMS:
			pChosenMenu = aMenu.GetSubMenu(4);
			break;
		case TI_COMMUNIQUE:
			pChosenMenu = aMenu.GetSubMenu(5);
			break;
		case TI_SIGNOUTS:	
		case TI_TIMETRIALORDER:
		case TI_SPRINT:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_POINTS:
			pChosenMenu = aMenu.GetSubMenu(6);
			break;
		case TI_CROSSOUTLIST:
			pChosenMenu = aMenu.GetSubMenu(7);
			break;
		case TI_SIGNINLIST:
			pChosenMenu = aMenu.GetSubMenu(9);
			break;
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
		case TI_CLASSTEAMS:
		case TI_LISTCOMPETITORS1:
		case TI_LISTCOMPETITORS2:
			pChosenMenu = aMenu.GetSubMenu(8);
			break;
		default:
			pChosenMenu = NULL;
	}
	if( pChosenMenu )
	{
		// Show the menu
		ClientToScreen(&point);
		pChosenMenu->SetDefaultItem( ID_EDIT_EDITSELECTION, false );
		pChosenMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										point.x+2,
										point.y+2,
										GetParentFrame() );
	}
}

void CTreeViewMain::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// If key down was the cause
	if( point==CPoint(-1,-1) )
	{
		if( GetTreeCtrl().GetSelectedItem() )
		{
			// Use the middle of the selected item
			// to align the context menu 
			CRect rect;
			GetTreeCtrl().GetItemRect(
				GetTreeCtrl().GetSelectedItem(),
				rect, true );
			point = rect.CenterPoint()+CPoint(0,5);
			ContextItem(point);
		}
		else
		{
			// Won't happen as there appears always to be a selection
			point+=CPoint(10,10);
			ContextTree(point);
		}
		return;
	}

	ScreenToClient(&point);
	// Test whether we really doubleclicked a tree item
	UINT uFlags=0;
	HTREEITEM hItem = GetTreeCtrl().HitTest( point, &uFlags );

	if( uFlags & (TVHT_ONITEMSTATEICON|TVHT_ONITEM) )
	{
		// Make sure the clicked item is selected as well
		if( hItem )
			GetTreeCtrl().Select(hItem, TVGN_CARET);
		else
		{
			CRect rect;
			GetTreeCtrl().GetItemRect(
				GetTreeCtrl().GetSelectedItem(), &rect, true );
			point.x = rect.left+1;
			point.y = rect.CenterPoint().y;
		}
	}

	if( uFlags & TVHT_ONITEMSTATEICON )
		// If we right click a tree item's check box
        ContextState(point);
	else
		if( uFlags & TVHT_ONITEM )
			// If we right click a tree item after all
			ContextItem(point);
		else
			ContextTree(point);

}

void CTreeViewMain::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	CEventItem ei = GetEventItem( pNMTreeView->itemNew.hItem );
	if( ei.IsPublicable()
		// Exception: TI_CLASSMASKxx also hold publicable events, typically
		|| (ei.m_tiConcerning >= TI_CLASSMASK10 && ei.m_tiConcerning <= TI_CLASSMASK1) )
	{
		m_DragDrop.m_hItemDrag = pNMTreeView->itemNew.hItem;

		// Get the image (list) for dragging
		if( m_DragDrop.m_pImageListDrag = ctrlTree.CreateDragImage(m_DragDrop.m_hItemDrag) )
		{
			POINT pt = pNMTreeView->ptDrag;
			ClientToScreen( &pt );
			// Start dragging
			m_DragDrop.m_bDragging = true;
			m_DragDrop.m_pImageListDrag->BeginDrag(0, CPoint(15,5));
			// Draw the dragging
			m_DragDrop.m_pImageListDrag->DragEnter(NULL, pt);

			// Make sure we capture the mouse move from all windows in the system
			SetCapture();
		}
	}
}

void CTreeViewMain::OnMouseMove(UINT nFlags, CPoint point) 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();

	if (m_DragDrop.m_bDragging)
	{
		POINT pt = point;
		ClientToScreen( &pt );

		// Draw the dragging
		CImageList::DragMove(pt);
		// Set the proper mouse arrows for hovering over the desired window or not
		CWnd* pWnd = WindowFromPoint(pt);
		if( pWnd )
		{
			if( !pWnd->IsKindOf( RUNTIME_CLASS( CDlgEventItemSelection ) ) )
				pWnd = pWnd->GetParent();
			if( pWnd && pWnd->IsKindOf( RUNTIME_CLASS( CDlgEventItemSelection ) ) )
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			else
				SetCursor(LoadCursor(NULL, IDC_NO));
		}
		else
			SetCursor(LoadCursor(NULL, IDC_NO));
	}
	CTreeView::OnMouseMove(nFlags, point);
}

void CTreeViewMain::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeCtrl& ctrlTree = GetTreeCtrl();
	
	if (m_DragDrop.m_bDragging)
	{
		m_DragDrop.m_bDragging = false;
		// Draw not longer the dragging
		CImageList::DragLeave(this);
		// Stop dragging
		CImageList::EndDrag();

		// Not longer capture the mouse move from all windows in the system
		ReleaseCapture();

		// Remove the drag image
		if( m_DragDrop.m_pImageListDrag ) delete m_DragDrop.m_pImageListDrag;
		m_DragDrop.m_pImageListDrag = NULL;

		// Handle the drop
		ClientToScreen(&point);
		CWnd* pWnd = WindowFromPoint(point);
		if( pWnd )
		{
			if( !pWnd->IsKindOf( RUNTIME_CLASS( CDlgEventItemSelection ) ) )
				pWnd = pWnd->GetParent();
			if( pWnd && pWnd->IsKindOf( RUNTIME_CLASS( CDlgEventItemSelection ) ) )
			{
				CEventItem* pEI = new CEventItem(
					GetEventItem( m_DragDrop.m_hItemDrag ) );

				// Exception: TI_CLASSMASKxx also hold publicable events, typically
				if(pEI->m_tiConcerning >= TI_CLASSMASK10 && pEI->m_tiConcerning <= TI_CLASSMASK1)
				{
					// Get the two child items typically below a
					// class mask leaf; don't use the leaf itself
					// This is very specific
					HTREEITEM hchild;
					hchild = ctrlTree.GetNextItem(m_DragDrop.m_hItemDrag, TVGN_CHILD);
					pWnd->PostMessage( WM_USER_DRAGGEDEVENTITEM,
											(WPARAM)m_pDoc,
											(LPARAM)new CEventItem(
												GetEventItem(hchild))
										);
					hchild = ctrlTree.GetNextItem(hchild, TVGN_NEXT);
					pWnd->PostMessage( WM_USER_DRAGGEDEVENTITEM,
											(WPARAM)m_pDoc,
											(LPARAM)new CEventItem(
												GetEventItem(hchild))
										);
					delete pEI;
					
				}
				else
				{
					pWnd->PostMessage( WM_USER_DRAGGEDEVENTITEM,
											(WPARAM)m_pDoc,
											(LPARAM)pEI
										);
				}
			}
		}
		// This prevents from ugly leftovers from the dragging process
		RedrawWindow();
	}
	CTreeView::OnLButtonUp(nFlags, point);
}


void CTreeViewMain::OnEditCopytoselectiondlg() 
{
	if( !m_pDoc->GetEventItemSelectionDlg() )
		m_pDoc->OnCmdMsg( ID_VIEW_EVENTITEMSELECTION, 0, NULL, NULL );
	if( m_pDoc->GetEventItemSelectionDlg() )
	{
		CEventItem* pEI = new CEventItem( m_eiSelected );
		m_pDoc->GetEventItemSelectionDlg()->
			PostMessage( WM_USER_DRAGGEDEVENTITEM,
							(WPARAM)m_pDoc,
							(LPARAM)pEI
						);
		m_pDoc->GetEventItemSelectionDlg()->ShowWindow( SW_SHOW );
	}
}

void CTreeViewMain::OnUpdateEditCopytoselectiondlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.IsPublicable() );
}

void CTreeViewMain::OnSetFocus(CWnd* pOldWnd) 
{
	CTreeView::OnSetFocus(pOldWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion( GetDocument() );
}

void CTreeViewMain::OnKillFocus(CWnd* pNewWnd) 
{
	CTreeView::OnKillFocus(pNewWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion(NULL);
}

void CTreeViewMain::OnGenerateReadonly() 
{
	m_eiSelected.ToggleReadonly();
}

void CTreeViewMain::OnUpdateGenerateReadonly(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable	( m_eiSelected.IsPublicationAvailable() );
	pCmdUI->SetCheck( m_eiSelected.IsPublicationReadonly() );
}

void CTreeViewMain::OnToolsEditpubl() 
{
	m_eiSelected.EditPublication();
}

void CTreeViewMain::OnUpdateToolsEditpubl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_eiSelected.IsPublicationAvailable() );
}

void CTreeViewMain::ExpandBranch(HTREEITEM hti)
{
    if( GetTreeCtrl().ItemHasChildren( hti ) ){
        GetTreeCtrl().Expand( hti, TVE_EXPAND );
        hti = GetTreeCtrl().GetChildItem( hti );
        do
		{
			ExpandBranch( hti );
        }
		while( (hti = GetTreeCtrl().GetNextSiblingItem( hti )) != NULL );
    }
}

void CTreeViewMain::OnViewExpand() 
{
	ExpandBranch( GetTreeCtrl().GetRootItem() );
    GetTreeCtrl().EnsureVisible( GetTreeCtrl().GetSelectedItem() );
}

BOOL CTreeViewMain::PreTranslateMessage(MSG* pMsg) 
{
	// This is necessary to make sure that threaded
	// processing can call UpdateAllViews
	if( pMsg->message == WM_USER_UPDATEALLVIEWS )
	{
		m_pDocument->UpdateAllViews( NULL,
			pMsg->lParam,
			(CObject*)pMsg->wParam );
	}
	return CTreeView::PreTranslateMessage(pMsg);
}
