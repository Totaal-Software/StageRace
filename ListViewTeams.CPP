// ListViewTeams.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams

IMPLEMENT_DYNCREATE(CListViewTeams, CListViewCompetitorsTeams)

CListViewTeams::CListViewTeams()
{
}

BEGIN_MESSAGE_MAP(CListViewTeams, CListViewCompetitorsTeams)
	//{{AFX_MSG_MAP(CListViewTeams)
	ON_COMMAND(ID_EDIT_EDITSELECTION, OnEditEditselection)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_INSERT_COMPETITORTEAM, OnInsertTeam)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams diagnostics

#ifdef _DEBUG
void CListViewTeams::AssertValid() const
{
	CListViewCompetitorsTeams::AssertValid();
}
void CListViewTeams::Dump(CDumpContext& dc) const
{
	CListViewCompetitorsTeams::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams message handlers

void CListViewTeams::OnInitialUpdate() 
{
	CListViewCompetitorsTeams::OnInitialUpdate();
	
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Set listview styles
	CListCtrl& ctrlList = GetListCtrl();
	
	// Add columns
	ctrlList.InsertColumn(0, LoadStr( IDS_DIV17 ), LVCFMT_LEFT,  80, 0);
	ctrlList.InsertColumn(1, LoadStr( IDS_DIV18 ), LVCFMT_LEFT, 200, 1);
	ctrlList.InsertColumn(2, LoadStr( IDS_DIV19 ), LVCFMT_LEFT, 150, 2);
	ctrlList.InsertColumn(3, LoadStr( IDS_DIV20 ), LVCFMT_LEFT, 125, 3);

	// Fill the list
	CTeam* pTeam = NULL;
	CString szKey;
	// Add all existing teams to the view by iterating the document's
	//  teams list
	POSITION pos = m_pDoc->TeamsGetStartPosition();
	while(pos)
	{
		m_pDoc->TeamsIterate(pos, (CTeam*&)pTeam);
		DrawTeam(pTeam);
	}

	//Sort
	SortItems( m_nSortedColumn, m_bSortedAsc );

	//Restore setting from the registry
	RestoreSettings(TEXT("ListTeams"));
}

void CListViewTeams::OnDestroy() 
{
	// Make sure the layout gets stored
	StoreSettings(TEXT("ListTeams"));
	CListViewCompetitorsTeams::OnDestroy();
}

void CListViewTeams::OnInsertTeam() 
{
	m_pDoc->TeamsNew( m_bRepeatedly );
}

void CListViewTeams::OnEditEditselection() 
{
	CListCtrl& ctrlList = GetListCtrl();

	// Make sure that exactly one item is selected
	switch( ctrlList.GetSelectedCount() )
	{
		case 0:
			MessageBox( LoadStr( IDS_MBC_22 ), LoadStr( IDS_MBT_22 ), MB_OK | MB_ICONINFORMATION);
			break;
		case 1:
			{
				// Get track of the selected item
				POSITION	pos		= ctrlList.GetFirstSelectedItemPosition();
				int			nItem	= ctrlList.GetNextSelectedItem(pos);
				CTeam*		pTeam	= (CTeam*)ctrlList.GetItemData(nItem);

				// Run the dialog
				m_pDoc->TeamsEdit( pTeam );
			}
			break;
		default:
			MessageBox( LoadStr( IDS_MBC_23 ), LoadStr( IDS_MBT_23 ), MB_OK | MB_ICONINFORMATION);
	}
}

void CListViewTeams::OnEditDelete() 
{
	if( m_edititem!=-1 )
	{
		m_editWnd.Clear();
	}
	else
	{
		CListCtrl& ctrlList = GetListCtrl();
		POSITION pos;
		if (ctrlList.GetSelectedCount() == 0)
		{
			MessageBox( LoadStr( IDS_MBC_24 ), LoadStr( IDS_MBT_24 ), MB_OK | MB_ICONINFORMATION);
			return;
		}

		// Make sure we want to delete
		if(ctrlList.GetSelectedCount() == 1)
		{
			if (MessageBox( LoadStr( IDS_MBC_25 ),
				LoadStr( IDS_MBT_25 ),
				MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
				) == IDNO ) return;
		}
		else
		{
			if (MessageBox( LoadStr( IDS_MBC_26 ),
				LoadStr( IDS_MBT_26 ),
				MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
				) == IDNO ) return;
		}

		CArray<int,int> arSelectAgain;
		// If we really want to delete we iterate the selection
		pos = ctrlList.GetFirstSelectedItemPosition();
		while(pos)
		{
			// Retreive the item index
			int nItem = ctrlList.GetNextSelectedItem(pos);

			// Retrieve the StaNo from the selected listbox item
			CTeam* pTeam = (CTeam*)ctrlList.GetItemData(nItem);

			// Delete the team
			if( !m_pDoc->TeamsDelete( pTeam ) )
			{
				// Temporarely deselect it
				arSelectAgain.Add( nItem );
				ctrlList.SetItemState( nItem, 0, LVIS_SELECTED );
			}

			// Get the position again, because it is probably screwed up
			// due to deleting an item
			pos = ctrlList.GetFirstSelectedItemPosition();
		}
		// Reselect items that could not be deleted
		for( int i = 0; i<arSelectAgain.GetSize(); i++ )
			ctrlList.SetItemState( arSelectAgain.GetAt(i),
									LVIS_SELECTED,
									LVIS_SELECTED );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams functions

bool CListViewTeams::SortItems(int nCol, bool bAscending, int low/*=0*/, int high/*=-1*/)
{
// SortItems	- Sort the list based on column text
// Returns		- Returns true for success
// nCol			- column that contains the text to be sorted
// bAscending	- indicate sort order
// low			- row to start scanning from - default row is 0
// high			- row to end scan. -1 indicates last row
	CListCtrl& ctrlList = GetListCtrl();

	if( nCol >= ctrlList.GetHeaderCtrl()->GetItemCount() )
		return false;

	if( high == -1 ) high = ctrlList.GetItemCount() - 1;

	int lo = low;
	int hi = high;
	CString midItem;

	if( hi <= lo ) return false;

	midItem = ctrlList.GetItemText( (lo+hi)/2, nCol );

	// loop through the list until indices cross
	while( lo <= hi )
	{
		// rowText will hold all column text for one row
		CStringArray rowText;

		// find the first element that is greater than or equal to 
		// the partition element starting from the left Index.
		if( bAscending )
			while( ( lo < high ) && ( ctrlList.GetItemText(lo, nCol) < midItem ) )
				++lo;
		else
			while( ( lo < high ) && ( ctrlList.GetItemText(lo, nCol) > midItem ) )
				++lo;

		// find an element that is smaller than or equal to 
		// the partition element starting from the right Index.
		if( bAscending )
			while( ( hi > low ) && ( ctrlList.GetItemText(hi, nCol) > midItem ) )
				--hi;
		else
			while( ( hi > low ) && ( ctrlList.GetItemText(hi, nCol) < midItem ) )
				--hi;

		// if the indexes have not crossed, swap
		// and if the items are not equal
		if( lo <= hi )
		{
			// swap only if the items are not equal
			if( ctrlList.GetItemText(lo, nCol) != ctrlList.GetItemText(hi, nCol))
			{
				// swap the rows
				LV_ITEM lvitemlo, lvitemhi;
				int nColCount = ctrlList.GetHeaderCtrl()->GetItemCount();
				rowText.SetSize( nColCount );
				int i;
				for( i=0; i<nColCount; i++)
					rowText[i] = ctrlList.GetItemText(lo, i);
				lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
				lvitemlo.iItem = lo;
				lvitemlo.iSubItem = 0;
				lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED | 
						LVIS_FOCUSED |  LVIS_SELECTED | 
						LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;

				lvitemhi = lvitemlo;
				lvitemhi.iItem = hi;

				ctrlList.GetItem( &lvitemlo );
				ctrlList.GetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					ctrlList.SetItemText(lo, i, ctrlList.GetItemText(hi, i));

				lvitemhi.iItem = lo;
				ctrlList.SetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					ctrlList.SetItemText(hi, i, rowText[i]);

				lvitemlo.iItem = hi;
				ctrlList.SetItem( &lvitemlo );
			}

			++lo;
			--hi;
		}
	}

	// If the right index has not reached the left side of array
	// must now sort the left partition.
	if( low < hi )
		SortItems( nCol, bAscending , low, hi);

	// If the left index has not reached the right side of array
	// must now sort the right partition.
	if( lo < high )
		SortItems( nCol, bAscending , lo, high );

	return true;
}

void CListViewTeams::ClearTeam(const CTeam* pTeam)
{
	CListCtrl& ctrlList = GetListCtrl();
	int i = FindTeam( pTeam );
	if( i!=-1 )
		ctrlList.DeleteItem( i );
}

int CListViewTeams::FindTeam(const CTeam* pTeam)
{
	CListCtrl& ctrlList = GetListCtrl();
	// Look for an old view item with the same StaNo and remove it
	// Just iterate the whole list control, looking for our item
	for( int i=0; i< ctrlList.GetItemCount(); i++ )
		if (ctrlList.GetItemData(i) == (DWORD)pTeam )
			return i;
	return -1;
}

void CListViewTeams::DrawTeam(const CTeam* pTeam, int nItem)
{
	// If called without an item no. being given
	// make sure it doesn't yet exist
	if( nItem == -1 )
		nItem = FindTeam( pTeam );

	CListCtrl& ctrlList = GetListCtrl();

	//Change nItem if '-1'
	if(nItem==-1)
	{
		nItem = ctrlList.GetItemCount();
		//Add to ListControl
		nItem = ctrlList.InsertItem(nItem, TEXT(""), 1);
	}

	ctrlList.SetItemText(nItem, 0, pTeam->m_code);
	ctrlList.SetItemText(nItem, 1, pTeam->m_name);
	ctrlList.SetItemText(nItem, 2, pTeam->m_manager);
	ctrlList.SetItemText(nItem, 3, pTeam->m_country);
	
	//Set the item data
	ctrlList.SetItemData(nItem, (DWORD)pTeam);

	//Make sure it's visible
	ctrlList.SetSelectionMark( nItem );
}

void CListViewTeams::EnsureVisible(const CTeam* pTeam)
{
	CListCtrl& ctrlList = GetListCtrl();
	// Look for an old view item with the same StaNo and ensure its
	// visibility
	// Just iterate the whole list control, looking for our item
	for( int i=0; i< ctrlList.GetItemCount(); i++ )
		if (ctrlList.GetItemData(i) == (DWORD)pTeam )
		{
			ctrlList.EnsureVisible( i, FALSE );
		}
}

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams services

UINT CListViewTeams::GetResourceID()
{
	return IDR_LISTVIEWTEAMS;
}

void CListViewTeams::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl& ctrlList = GetListCtrl();
	CUpdateViewHint* pUVH = (CUpdateViewHint*)pHint;

	switch( lHint )
	{
		case TI_TEAMS:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							const CTeam* pTeam = (const CTeam*)pUVH->GetConcerning();
							// Draw it newly
							DrawTeam( pTeam );
							SortItems( m_nSortedColumn, m_bSortedAsc );
							EnsureVisible( pTeam );
						}
						break;
					case UV_UPDATED:
						{
							const CTeam* pTeam = (const CTeam*)pUVH->GetConcerning();
							// Draw it newly
							DrawTeam( pTeam );
							SortItems( m_nSortedColumn, m_bSortedAsc );
						}
						break;
					case UV_DELETED:
						{
							const CTeam* pTeam = (const CTeam*)pUVH->GetConcerning();
							// Clear existing
							ClearTeam( pTeam );
						}
						break;
				}
			break;
	}
}

void CListViewTeams::OnEditCopy() 
{
	if( m_edititem!=-1 )
		m_editWnd.Copy();
	else
	{
		CArray<CTeam*,CTeam*> arStaNos;
		CListCtrl& ctrlList = GetListCtrl();
		POSITION pos = ctrlList.GetFirstSelectedItemPosition();
		while(pos)
		{
			arStaNos.Add( (CTeam*)ctrlList.GetItemData(
				ctrlList.GetNextSelectedItem(pos) ) );
		}
		m_pDoc->TeamsCopy( &arStaNos );
	}
}

void CListViewTeams::OnEditCut() 
{
	if( m_edititem!=-1 )
		m_editWnd.Cut();
	else
	{
		CArray<CTeam*,CTeam*> arStaNos;
		CListCtrl& ctrlList = GetListCtrl();
		POSITION pos = ctrlList.GetFirstSelectedItemPosition();
		while(pos)
		{
			arStaNos.Add( (CTeam*)ctrlList.GetItemData(
				ctrlList.GetNextSelectedItem(pos) ) );
		}
		m_pDoc->TeamsCut( &arStaNos );
	}
}

void CListViewTeams::OnEditPaste() 
{
	if( m_edititem!=-1 )
		m_editWnd.Paste();
	else
		m_pDoc->TeamsPaste();
}

void CListViewTeams::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CListCtrl& ctrlList = GetListCtrl();
	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTTEAMS );

	// Choose one of the sub menus
	CMenu* pChosenMenu;

	switch( m_nSelectedCount )
	{
		case 0:
			pChosenMenu = aMenu.GetSubMenu(0);
			break;
		case 1:
			pChosenMenu = aMenu.GetSubMenu(1);
			break;
		default:
			pChosenMenu = aMenu.GetSubMenu(2);
			break;
	}
	if( pChosenMenu )
	{
		if( (point.x==-1) && (point.y==-1) )
		{
			CRect rect;
			ctrlList.GetItemRect(
					ctrlList.GetSelectionMark(),
					&rect,
					LVIR_BOUNDS
				);
			point.x = 10;
			point.y = rect.CenterPoint().y;
			ClientToScreen(&point);
		}
		pChosenMenu->SetDefaultItem( ID_EDIT_EDITSELECTION, false );

		// Show the menu
		pChosenMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
										point.x+2,
										point.y+2,
										GetParentFrame() );
	}
}

void CListViewTeams::UpdateField(LV_ITEM *plvItem)
{
	m_pDoc->TeamsUpdate( (CTeam*)plvItem->lParam, (TEAM_FIELD)plvItem->iSubItem, plvItem->pszText );
}

CListViewTeams::EDIT_TYPE CListViewTeams::EditAllowedOnSubitem(int i)
{
	return EDIT_INLINE;
}

UINT CListViewTeams::EditFieldLength(int i)
{
	switch(i)
	{
		case 0:
			return 3;
		default:
			return 0;
	}
}

