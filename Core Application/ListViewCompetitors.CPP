// ListViewCompetitors.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors

IMPLEMENT_DYNCREATE(CListViewCompetitors, CListViewCompetitorsTeams)

CListViewCompetitors::CListViewCompetitors()
{
	m_subitem			= 0;
	m_edititem			= -1;

	m_bPasteWithStaNos	= true;
	m_bCtrlKey			= false;
}

BEGIN_MESSAGE_MAP(CListViewCompetitors, CListViewCompetitorsTeams)
	//{{AFX_MSG_MAP(CListViewCompetitors)
	ON_COMMAND(ID_EDIT_EDITSELECTION, OnEditEditselection)
	ON_COMMAND(ID_EDIT_APPLYMASK, OnEditApplymask)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_INSERT_COMPETITORTEAM, OnInsertCompetitor)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE_WITHSTANOS, OnEditPasteWithstanos)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_WITHSTANOS, OnUpdateEditPasteWithstanos)
	ON_COMMAND(ID_EDIT_SWAPCOMPETITORS, OnEditSwapcompetitors)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SWAPCOMPETITORS, OnUpdateEditSwapcompetitors)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_UPDATE_COMMAND_UI(ID_EDIT_APPLYMASK, OnUpdateEditApplymask)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors diagnostics

#ifdef _DEBUG
void CListViewCompetitors::AssertValid() const
{
	CListViewCompetitorsTeams::AssertValid();
}
void CListViewCompetitors::Dump(CDumpContext& dc) const
{
	CListViewCompetitorsTeams::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors message handlers

void CListViewCompetitors::OnInitialUpdate() 
{
	CListViewCompetitorsTeams::OnInitialUpdate();
	
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Set listview styles
	CListCtrl& ctrlList = GetListCtrl();

	// Add columns
	ctrlList.InsertColumn( 0, LoadStr( IDS_DIV11 ), LVCFMT_RIGHT,  60,  0);
	ctrlList.InsertColumn( 1, LoadStr( IDS_DIV12 ),  LVCFMT_LEFT, 130,  1);
	ctrlList.InsertColumn( 2, LoadStr( IDS_DIV13 ),  LVCFMT_LEFT, 155,  2);
	ctrlList.InsertColumn( 3, LoadStr( IDS_DIV13 ),  LVCFMT_LEFT,  50,  3);
	ctrlList.InsertColumn( 4, LoadStr( IDS_DIV14 ),  LVCFMT_LEFT,  50,  4);
	ctrlList.InsertColumn( 5,          TEXT("UCI"),  LVCFMT_LEFT,  90,  5);
	ctrlList.InsertColumn( 6, LoadStr( IDS_DIV15 ),  LVCFMT_LEFT,  60,  6);
	ctrlList.InsertColumn( 7, LoadStr( IDS_DIV16 ),  LVCFMT_LEFT,  60,  7);
	ctrlList.InsertColumn( 8,           TEXT("M1"),  LVCFMT_LEFT,  35,  8);
	ctrlList.InsertColumn( 9,           TEXT("M2"),  LVCFMT_LEFT,  35,  9);
	ctrlList.InsertColumn(10,           TEXT("M3"),  LVCFMT_LEFT,  35, 10);
	ctrlList.InsertColumn(11,           TEXT("M4"),  LVCFMT_LEFT,  35, 11);
	ctrlList.InsertColumn(12,           TEXT("M5"),  LVCFMT_LEFT,  35, 12);
	ctrlList.InsertColumn(13,           TEXT("M6"),  LVCFMT_LEFT,  35, 13);
	ctrlList.InsertColumn(14,           TEXT("M7"),  LVCFMT_LEFT,  35, 14);
	ctrlList.InsertColumn(15,           TEXT("M8"),  LVCFMT_LEFT,  35, 15);
	ctrlList.InsertColumn(16,           TEXT("M9"),  LVCFMT_LEFT,  35, 16);
	ctrlList.InsertColumn(17,          TEXT("M10"),  LVCFMT_LEFT,  35, 17);

	// Set first columns alignment explicitly
	LVCOLUMN lvCol;
	lvCol.mask	= LVCF_FMT;
	lvCol.fmt	= LVCFMT_RIGHT;
	ctrlList.SetColumn(0, &lvCol);

	// Fill the list
	DrawAll();

	// Restore setting from the registry
	RestoreSettings(TEXT("ListCompetitors"));
}

void CListViewCompetitors::OnDestroy() 
{
	// Make sure the layout gets stored
	StoreSettings(TEXT("ListCompetitors"));
	CListViewCompetitorsTeams::OnDestroy();
}

void CListViewCompetitors::OnInsertCompetitor() 
{
	m_pDoc->CompetitorsNew( m_bRepeatedly );
}

void CListViewCompetitors::OnEditEditselection() 
{
	CListCtrl& ctrlList = GetListCtrl();

	// Make sure that exactly one item is selected
	switch( ctrlList.GetSelectedCount() )
	{
		case 0:
			MessageBox( LoadStr( IDS_MBC_17 ), LoadStr( IDS_MBT_17 ), MB_OK | MB_ICONINFORMATION);
			break;
		case 1:
			{
				// Get track of the selected item
				POSITION	pos		= ctrlList.GetFirstSelectedItemPosition();
				int			nItem	= ctrlList.GetNextSelectedItem(pos);
				if( IsSpare( nItem ) )
				{
					const CCompetitor* pComp = (const CCompetitor*)ctrlList.GetItemData(nItem);
					// Run the dialog
					m_pDoc->SpareCompetitorsEdit( pComp );
				}
				else
				{
					DWORD nStaNo = ctrlList.GetItemData(nItem);
					// Run the dialog
					m_pDoc->CompetitorsEdit( nStaNo );
				}
			}
			break;
		default:
			MessageBox( LoadStr( IDS_MBC_18 ), LoadStr( IDS_MBT_18 ), MB_OK | MB_ICONINFORMATION);
	}
}

void CListViewCompetitors::OnEditDelete() 
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
			MessageBox( LoadStr( IDS_MBC_12 ), LoadStr( IDS_MBT_12 ), MB_OK | MB_ICONINFORMATION);
			return;
		}

		// Make sure we want to delete
		if(ctrlList.GetSelectedCount() == 1)
		{
			if (MessageBox( LoadStr( IDS_MBC_13 ),
				LoadStr( IDS_MBT_13 ),
				MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2|MB_APPLMODAL
				) == IDNO ) return;
		}
		else
		{
			if (MessageBox( LoadStr( IDS_MBC_14 ),
				LoadStr( IDS_MBT_14 ),
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

			if( IsSpare( nItem ) )
			{
				const CCompetitor* pComp = (const CCompetitor*)ctrlList.GetItemData(nItem);

				// Delete the competitor
				if( !m_pDoc->SpareCompetitorsDelete( pComp ) )
				{
					// Temporarely deselect it
					arSelectAgain.Add( nItem );
					ctrlList.SetItemState( nItem, 0, LVIS_SELECTED );
				}
			}
			else
			{
				// Retrieve the StaNo from the selected listbox item
				int nStaNo = ctrlList.GetItemData(nItem);

				// Delete the competitor
				if( !m_pDoc->CompetitorsDelete( nStaNo ) )
				{
					// Temporarely deselect it
					arSelectAgain.Add( nItem );
					ctrlList.SetItemState( nItem, 0, LVIS_SELECTED );
				}
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

void CListViewCompetitors::OnEditCopy() 
{
	if( m_edititem!=-1 )
		m_editWnd.Copy();
	else
	{
		CArray<WORD,WORD> arStaNos;
		CPtrArray arComps;
		CListCtrl& ctrlList = GetListCtrl();
		POSITION pos = ctrlList.GetFirstSelectedItemPosition();
		while(pos)
		{
			// Retreive the item index
			int nItem = ctrlList.GetNextSelectedItem(pos);

			if( IsSpare(nItem) )
				arComps.Add( (void*)ctrlList.GetItemData( nItem ) );
			else
				arStaNos.Add( (WORD)ctrlList.GetItemData( nItem ) );
		}
		m_pDoc->CompetitorsCopy( &arStaNos, &arComps );
	}
}

void CListViewCompetitors::OnEditCut() 
{
	if( m_edititem!=-1 )
		m_editWnd.Cut();
	else
	{
		CArray<WORD,WORD> arStaNos;
		CPtrArray arComps;
		CListCtrl& ctrlList = GetListCtrl();
		POSITION pos = ctrlList.GetFirstSelectedItemPosition();
		while(pos)
		{
			// Retreive the item index
			int nItem = ctrlList.GetNextSelectedItem(pos);

			if( IsSpare(nItem) )
				arComps.Add( (void*)ctrlList.GetItemData( nItem ) );
			else
				arStaNos.Add( (WORD)ctrlList.GetItemData( nItem ) );
		}
		m_pDoc->CompetitorsCut( &arStaNos, &arComps );
	}
}

void CListViewCompetitors::OnEditPaste() 
{
	if( m_edititem!=-1 )
		m_editWnd.Paste();
	else
		m_pDoc->CompetitorsPaste(m_bPasteWithStaNos);
}

void CListViewCompetitors::OnEditApplymask() 
{
	m_pDoc->CompetitorsApplyMask();
	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors functions

bool CListViewCompetitors::SortItems(int nCol, bool bAscending, int low/*=0*/, int high/*=-1*/)
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

		//The first column requires numeric sorting
		//other columns text sorting
		if(nCol==0)
		{
			int nMidItem;
			
			//Convert midItem to int
			nMidItem = _ttoi(midItem);
			
			// find the first element that is greater than or equal to 
			// the partition element starting from the left Index.
			if( bAscending )
				while( ( lo < high ) && ( _ttoi(ctrlList.GetItemText(lo, nCol)) < nMidItem ) )
					++lo;
			else
				while( ( lo < high ) && ( _ttoi(ctrlList.GetItemText(lo, nCol)) > nMidItem ) )
					++lo;

			// find an element that is smaller than or equal to 
			// the partition element starting from the right Index.
			if( bAscending )
				while( ( hi > low ) && ( _ttoi(ctrlList.GetItemText(hi, nCol)) > nMidItem ) )
					--hi;
			else
				while( ( hi > low ) && ( _ttoi(ctrlList.GetItemText(hi, nCol)) < nMidItem ) )
					--hi;
		}
		else
		{
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
		}

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

void CListViewCompetitors::ClearCompetitor(DWORD nStaNo)
{
	CListCtrl& ctrlList = GetListCtrl();
	int i = FindCompetitor( nStaNo );
	if( i!=-1 )
		ctrlList.DeleteItem( i );
}

int CListViewCompetitors::FindCompetitor(DWORD nStaNo)
{
	CListCtrl& ctrlList = GetListCtrl();
	// Look for an old view item with the same StaNo and remove it
	// Just iterate the whole list control, looking for our item
	for( int i=0; i< ctrlList.GetItemCount(); i++ )
		if (ctrlList.GetItemData(i) == (DWORD)nStaNo )
			return i;
	return -1;
}

void CListViewCompetitors::DrawCompetitor(const CCompetitor* pCompetitor, int nItem)
{
	CListCtrl& ctrlList = GetListCtrl();

	//Change nItem if '-1'
	if(nItem==-1)
	{
		nItem = ctrlList.GetItemCount();
		//Add to ListControl
		if( pCompetitor->m_staNo )
			nItem = ctrlList.InsertItem(nItem, TEXT(""), 0);
		else
			nItem = ctrlList.InsertItem(nItem, TEXT(""), 2);
	}

	if( pCompetitor->m_staNo )
	{
		TCHAR buffer[10];
		// Convert the StaNo to a sort of string
		_itot( pCompetitor->m_staNo, buffer, 10 );
		ctrlList.SetItemText(nItem, 0, CString(buffer));
	}
	ctrlList.SetItemText(nItem, 1, pCompetitor->m_competitor);
	if(pCompetitor->m_pTeam)
	{
		ctrlList.SetItemText(nItem, 2, pCompetitor->m_pTeam->m_name);
		ctrlList.SetItemText(nItem, 3, pCompetitor->m_pTeam->m_code);
	}
	ctrlList.SetItemText(nItem, 4, pCompetitor->m_countryCode);
	ctrlList.SetItemText(nItem, 5, pCompetitor->m_UCICode);
	ctrlList.SetItemText(nItem, 6, pCompetitor->m_license);
	ctrlList.SetItemText(nItem, 7, pCompetitor->m_category);
	ctrlList.SetItemText(nItem, 8, TEXT("  "));
	ctrlList.SetItemText(nItem, 9, TEXT("  "));
	ctrlList.SetItemText(nItem,10, TEXT("  "));
	ctrlList.SetItemText(nItem,11, TEXT("  "));
	ctrlList.SetItemText(nItem,12, TEXT("  "));
	ctrlList.SetItemText(nItem,13, TEXT("  "));
	ctrlList.SetItemText(nItem,14, TEXT("  "));
	ctrlList.SetItemText(nItem,15, TEXT("  "));
	ctrlList.SetItemText(nItem,16, TEXT("  "));
	ctrlList.SetItemText(nItem,17, TEXT("  "));
	
	//Set the item data
	if( pCompetitor->m_staNo )
		ctrlList.SetItemData(nItem, pCompetitor->m_staNo);
	else
		ctrlList.SetItemData(nItem, (DWORD)pCompetitor);

	//Make sure it's visible
	ctrlList.SetSelectionMark( nItem );
}

void CListViewCompetitors::EnsureVisible(DWORD nStaNo)
{
	CListCtrl& ctrlList = GetListCtrl();
	// Look for an old view item with the same StaNo and ensure its
	// visibility
	// Just iterate the whole list control, looking for our item
	for( int i=0; i< ctrlList.GetItemCount(); i++ )
		if (ctrlList.GetItemData(i) == (DWORD)nStaNo )
		{
			ctrlList.EnsureVisible( i, FALSE );
		}
}

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors services

UINT CListViewCompetitors::GetResourceID()
{
	return IDR_LISTVIEWCOMPETITORS;
}

void CListViewCompetitors::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl& ctrlList = GetListCtrl();
	CUpdateViewHint* pUVH = (CUpdateViewHint*)pHint;

	switch( lHint )
	{
		case TI_SETTINGS:
			Invalidate();
			break;
		case TI_TEAMS:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_UPDATED:
						{
							const CTeam* pTeam = (const CTeam*)pUVH->GetConcerning();
							// Search for this team
							for( int nItem=0; nItem<ctrlList.GetItemCount(); nItem++ )
							{
								if( IsSpare(nItem) )
								{
									if( ((CCompetitor*)ctrlList.GetItemData(nItem))->m_pTeam == pTeam )
										DrawCompetitor( (CCompetitor*)ctrlList.GetItemData(nItem), nItem );
								}
								else
								{
									CCompetitor comp = m_pDoc->CompetitorsGet( ctrlList.GetItemData(nItem) );
									if( comp.m_pTeam == pTeam )
										DrawCompetitor( &comp, nItem );
								}
							}
							SortItems( m_nSortedColumn, m_bSortedAsc );
						}
						break;
				}
			break;
		case TI_SPARECOMPETITORS:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							CCompetitor* pComp = (CCompetitor*)pUVH->GetConcerning();
							// Draw it newly
							DrawCompetitor( pComp );
							SortItems( m_nSortedColumn, m_bSortedAsc );
							EnsureVisible( (DWORD)pComp );
						}
						break;
					case UV_UPDATED:
						// Note that this is not as straightforwarded
						// as it looks - if StaNo changed, ClearCompetitor
						// will not work correctly and therefore UV_DELETED
						// must be used precedingly
						{
							CCompetitor* pComp = (CCompetitor*)pUVH->GetConcerning();
							// Draw it newly
							DrawCompetitor( pComp, FindCompetitor( (DWORD)pComp ) );
							SortItems( m_nSortedColumn, m_bSortedAsc );
						}
						break;
					case UV_DELETED:
						{
							WORD* pnComp = (WORD*)pUVH->GetConcerning();
							// Clear existing
							ClearCompetitor( (DWORD)pnComp );
						}
						break;
				}
			break;
		case TI_COMPETITORS:
			if( pUVH )
				switch( pUVH->GetReason() )
				{
					case UV_ADDED:
						{
							CCompetitor* pComp = (CCompetitor*)pUVH->GetConcerning();
							// Draw it newly
							DrawCompetitor( pComp );
							SortItems( m_nSortedColumn, m_bSortedAsc );
							EnsureVisible( pComp->m_staNo );
						}
						break;
					case UV_UPDATED:
						// Note that this is not as straightforwarded
						// as it looks - if StaNo changed, ClearCompetitor
						// will not work correctly and therefore UV_DELETED
						// must be used precedingly
						{
							CCompetitor* pComp = (CCompetitor*)pUVH->GetConcerning();
							// Draw it newly
							DrawCompetitor( pComp, FindCompetitor( pComp->m_staNo ) );
							SortItems( m_nSortedColumn, m_bSortedAsc );
						}
						break;
					case UV_DELETED:
						{
							WORD* pnComp = (WORD*)pUVH->GetConcerning();
							// Clear existing
							ClearCompetitor( *pnComp );
						}
						break;
					case UV_INVALIDATEALL:
						DrawAll();
						break;
				}
			break;
	}
}

void CListViewCompetitors::OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // first, lets extract data from
    // the message for ease of use later
    NMLVCUSTOMDRAW* pNMLVCUSTOMDRAW = (NMLVCUSTOMDRAW*)pNMHDR;

    // here is the item info
    // note that we don't get the subitem
    // number here, as this may not be
    // valid data except when we are
    // handling a sub item notification
    // so we'll do that separately in
    // the appropriate case statements
    // below.
    int nItem = pNMLVCUSTOMDRAW->nmcd.dwItemSpec;

    // what we do next depends on the
    // drawing stage we are processing
    switch( pNMLVCUSTOMDRAW->nmcd.dwDrawStage )
	{
		case CDDS_PREPAINT:
		case CDDS_ITEMPREPAINT:
			*pResult |= CDRF_NOTIFYSUBITEMDRAW|CDRF_NOTIFYPOSTPAINT;
			break;
		case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
			{
				// Sub Item PrePaint
				// Set sub item number (data will be valid now)
				int nSubItem = pNMLVCUSTOMDRAW->iSubItem;
				if(!nSubItem && !m_bPasteWithStaNos)
					pNMLVCUSTOMDRAW->clrText = RGB(210,210,210);
				else
					pNMLVCUSTOMDRAW->clrText = CLR_DEFAULT;

				if( m_bBars && (nItem%2) )
					pNMLVCUSTOMDRAW->clrTextBk = BARSCOLOR;
			}
			break;
		case CDDS_ITEMPOSTPAINT:
			{
				CDC* pDC = CDC::FromHandle(pNMLVCUSTOMDRAW->nmcd.hdc);
				if( pDC )
				{
					CRect rectitem;
					CRect rectdraw;
					CPoint point;
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
					{
						GetListCtrl().GetSubItemRect(nItem,8,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();

						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 8) )
							pDC->FillSolidRect( &rectdraw, RGB(255,80,80));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
					{
						GetListCtrl().GetSubItemRect(nItem,9,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();

						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 9) )
							pDC->FillSolidRect( &rectdraw, RGB(255,80,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
					{
						GetListCtrl().GetSubItemRect(nItem,10,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 10) )
							pDC->FillSolidRect( &rectdraw, RGB(80,255,80));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
					{
						GetListCtrl().GetSubItemRect(nItem,11,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 11) )
							pDC->FillSolidRect( &rectdraw, RGB(80,80,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
					{
						GetListCtrl().GetSubItemRect(nItem,12,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 12) )
							pDC->FillSolidRect( &rectdraw, RGB(80,255,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
					{
						GetListCtrl().GetSubItemRect(nItem,13,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 13) )
							pDC->FillSolidRect( &rectdraw, RGB(255,80,80));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
					{
						GetListCtrl().GetSubItemRect(nItem,14,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 14) )
							pDC->FillSolidRect( &rectdraw, RGB(255,80,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
					{
						GetListCtrl().GetSubItemRect(nItem,15,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 15) )
							pDC->FillSolidRect( &rectdraw, RGB(80,255,80));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
					{
						GetListCtrl().GetSubItemRect(nItem,16,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 16) )
							pDC->FillSolidRect( &rectdraw, RGB(80,80,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
					if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
					{
						GetListCtrl().GetSubItemRect(nItem,17,LVIR_LABEL,rectitem);
						point = rectitem.CenterPoint();
						
						rectdraw.bottom = point.y+4;
						rectdraw.top = point.y-4;
						rectdraw.left = max( point.x-4, rectitem.left );
						rectdraw.right = min( point.x+4, rectitem.right );
						pDC->FillSolidRect( &rectdraw, RGB(0,0,0));

						rectdraw.bottom = point.y+3;
						rectdraw.top = point.y-3;
						rectdraw.left = max( point.x-3, rectitem.left );
						rectdraw.right = min( point.x+3, rectitem.right );
						if( EditGetBool(nItem, 17) )
							pDC->FillSolidRect( &rectdraw, RGB(80,255,255));
						else
							pDC->FillSolidRect( &rectdraw, RGB(255,255,255));
					}
				}
			}
			break;
		default:
			ASSERT(CDRF_DODEFAULT==0);
			*pResult = 0;
    }
}

void CListViewCompetitors::OnEditPasteWithstanos() 
{
	m_bPasteWithStaNos = !m_bPasteWithStaNos;
	Invalidate();
}

void CListViewCompetitors::OnUpdateEditPasteWithstanos(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( m_bPasteWithStaNos?1:0 );
}

void CListViewCompetitors::DrawAll()
{
	GetListCtrl().DeleteAllItems();
	// Fill the list
	CCompetitor aCompetitor;
	DWORD nState=0;
	// Add all existing competitors to the view by iterating the document's
	//  competitors list
	while(m_pDoc->CompetitorsIterateSorted( nState, aCompetitor ))
	{
		DrawCompetitor(&aCompetitor);
	}
	POSITION pos = m_pDoc->SpareCompetitorsGetStartPosition();
	// Add all existing spare competitors to the view by iterating the document's
	//  spare competitors list
	while(pos)
	{
		DrawCompetitor( m_pDoc->SpareCompetitorsIterate( pos ) );
	}

	//Sort
	SortItems( m_nSortedColumn, m_bSortedAsc );
}

void CListViewCompetitors::OnEditSwapcompetitors() 
{
	CListCtrl& ctrlList = GetListCtrl();

	POSITION pos;
	// Make sure again that we can do this
	if( ctrlList.GetSelectedCount()==2 )
	{
		// Get the first
		pos = ctrlList.GetFirstSelectedItemPosition();
		int nItem1 = ctrlList.GetNextSelectedItem(pos);
		if( IsSpare( nItem1 ) )
		{
			// Get the second
			int nItem2 = ctrlList.GetNextSelectedItem(pos);
			if( !IsSpare( nItem2 ) )
				m_pDoc->CompetitorsSwap(
						(CCompetitor*)ctrlList.GetItemData(nItem1),
						(WORD)ctrlList.GetItemData(nItem2)
					);
			// There is no point in doing this
//			else
//				m_pDoc->CompetitorsSwap(
//						(CCompetitor*)ctrlList.GetItemData(nItem1),
//						(CCompetitor*)ctrlList.GetItemData(nItem2)
//					)
		}
		else
		{
			// Get the second
			int nItem2 = ctrlList.GetNextSelectedItem(pos);
			if( IsSpare( nItem2 ) )
				m_pDoc->CompetitorsSwap(
						(WORD)ctrlList.GetItemData(nItem1),
						(CCompetitor*)ctrlList.GetItemData(nItem2)
					);
			else
				m_pDoc->CompetitorsSwap(
						(WORD)ctrlList.GetItemData(nItem1),
						(WORD)ctrlList.GetItemData(nItem2)
					);
		}
	}
}

void CListViewCompetitors::OnUpdateEditSwapcompetitors(CCmdUI* pCmdUI) 
{
	// Only available if two items are selected
	pCmdUI->Enable( m_nSelectedCount==2 );
}

void CListViewCompetitors::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CListCtrl& ctrlList = GetListCtrl();
	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTCOMPETITORS );

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
		case 2:
			pChosenMenu = aMenu.GetSubMenu(2);
			break;
		default:
			pChosenMenu = aMenu.GetSubMenu(3);
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

void CListViewCompetitors::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// This sets a flag every time the CTRL key is pressed down
	// in order to track if it is released without any other key
	// being pressed for an Ctrl-X combination (where X is any key)
	// Because only pressing Ctrl (and releasing) should have the
	// functionality from OnEditPasteWithstanos() (see OnKeyUp)
	CListViewCompetitorsTeams::OnKeyDown(nChar, nRepCnt, nFlags);
	if( (nFlags&0xff)==0x1d ) // Test for Ctrl
	{
		if( !(nFlags&0x4000) ) // Transition from up state (clears out repetition)
			m_bCtrlKey = true;
	}
	else
		m_bCtrlKey = false;
}

void CListViewCompetitors::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// This checks for every CTRL key being released if the previous key
	// being pressed or released was also a CTRL key
	// Because only pressing Ctrl (and releasing) should have the
	// functionality from OnEditPasteWithstanos()
	CListViewCompetitorsTeams::OnKeyUp(nChar, nRepCnt, nFlags);
	if( ((nFlags&0xff)==0x1d) && m_bCtrlKey )
	{
		// Various
		CSRRegKey reg1;
		reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
		if( reg1.GetBool(TEXT("UseCtrlForCompetitorPaste"),true) )
		{
			MessageBeep( MB_ICONASTERISK );
			OnEditPasteWithstanos();
		}
	}
	m_bCtrlKey = false;
}

void CListViewCompetitors::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Make sure that Ctrl-Mouseclick is not
	// seen as OnKeyDown/OnKeyUp with Ctrl
	m_bCtrlKey = false;
	*pResult = 0;
}

void CListViewCompetitors::OnUpdateEditApplymask(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) ||
			m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10)
		);
}

void CListViewCompetitors::UpdateField(LV_ITEM* plvItem)
{
	CListCtrl& ctrlList = GetListCtrl();
	switch( plvItem->iSubItem )
	{
		case 0:
			if( IsSpare(plvItem->iItem) )
				m_pDoc->SpareCompetitorsChangeStaNo( (const CCompetitor*)plvItem->lParam,
												_ttoi( plvItem->pszText ) );
			else
				m_pDoc->CompetitorsChangeStaNo( (WORD)plvItem->lParam,
												_ttoi( plvItem->pszText ) );
			break;
		case 2:
		case 3:
			break;
		default:
			if( plvItem->iSubItem > 2 )
				plvItem->iSubItem--;
			if( ctrlList.GetItemText( plvItem->iItem, 0 ).IsEmpty() )
				m_pDoc->SpareCompetitorsUpdate( (CCompetitor*)plvItem->lParam, (COMPETITOR_FIELD)plvItem->iSubItem, plvItem->pszText );
			else
				m_pDoc->CompetitorsUpdate( plvItem->lParam, (COMPETITOR_FIELD)plvItem->iSubItem, plvItem->pszText );
	}
}

CListViewCompetitors::EDIT_TYPE CListViewCompetitors::EditAllowedOnSubitem(int i)
{
	switch( i )
	{
		case 2: // team
		case 3: // team code
			return EDIT_NOT;
		case 8:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 9:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 10:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 11:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 12:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 13:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 14:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 15:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 16:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		case 17:
			if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) )
				return EDIT_CHECK;
			else
				return EDIT_NOT;
		default:
			return EDIT_INLINE;
	}
}

UINT CListViewCompetitors::EditFieldLength(int i)
{
	switch(i)
	{
		case 4:
			return 3;
		case 5:
		case 6:
		case 7:
			return 11;
		default:
			return 0;
	}
}

bool CListViewCompetitors::EditNumeric(int i)
{
	switch(i)
	{
		case 0:
			return true;
		default:
			return false;
	}
}

bool CListViewCompetitors::EditGetBool(int iItem, int iSubItem)
{
	switch(iSubItem)
	{
		case 8:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask1>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask1>0;
		case 9:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask2>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask2>0;
		case 10:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask3>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask3>0;
		case 11:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask4>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask4>0;
		case 12:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask5>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask5>0;
		case 13:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask6>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask6>0;
		case 14:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask7>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask7>0;
		case 15:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask8>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask8>0;
		case 16:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask9>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask9>0;
		case 17:
			if( IsSpare(iItem) )
				return ((const CCompetitor*)GetListCtrl().GetItemData(iItem))->m_mask10>0;
			else
				return m_pDoc->CompetitorsGet(GetListCtrl().GetItemData(iItem)).m_mask10>0;
		default:
			return false;
	}
}

void CListViewCompetitors::EditSetBool(int iItem, int iSubItem, bool bVal)
{
	switch(iSubItem)
	{
		case 8:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(1,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),1,bVal,false);
			break;
		case 9:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(2,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),2,bVal,false);
			break;
		case 10:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(3,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),3,bVal,false);
			break;
		case 11:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(4,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),4,bVal,false);
			break;
		case 12:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(5,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),5,bVal,false);
			break;
		case 13:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(6,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),6,bVal,false);
			break;
		case 14:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(7,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),7,bVal,false);
			break;
		case 15:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(8,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),8,bVal,false);
			break;
		case 16:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(9,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),9,bVal,false);
			break;
		case 17:
			if( IsSpare(iItem) )
				((CCompetitor*)GetListCtrl().GetItemData(iItem))->SetMask(10,bVal);
			else
				m_pDoc->CompetitorsSetMask(GetListCtrl().GetItemData(iItem),10,bVal,false);
			break;
	}
	Invalidate();
}

bool CListViewCompetitors::IsSpare(int nItem)
{
	return _ttoi(GetListCtrl().GetItemText( nItem, 0 ))==0;
}
