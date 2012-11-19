// ListViewCompetitorsTeams.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitorsTeams

IMPLEMENT_DYNCREATE(CListViewCompetitorsTeams, CListView)

CListViewCompetitorsTeams::CListViewCompetitorsTeams()
{
	m_nSelectedCount	= 0;
	
	m_subitem			= 0;
	m_edititem			= -1;

	m_nSortedColumn		= 0;
	m_bSortedAsc		= true;
	
	m_bRepeatedly		= false;
	m_bGrid				= false;
	m_bBars				= false;
}

BEGIN_MESSAGE_MAP(CListViewCompetitorsTeams, CListView)
	//{{AFX_MSG_MAP(CListViewCompetitorsTeams)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EDITSELECTION, OnUpdateEditEditselection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_INSERT_REPEATEDLY, OnUpdateInsertRepeatedly)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_INSERT_REPEATEDLY, OnInsertRepeatedly)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_NEXT_PANE, OnNextPane)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_PAINT()
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_VIEW_BARS, OnViewBars)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BARS, OnUpdateViewBars)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_COMMAND(ID_PREV_PANE, OnNextPane)
	ON_COMMAND(ID_EDIT_CLEANUPCOMPETITORS, OnEditCleanupcompetitors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitorsTeams diagnostics

#ifdef _DEBUG
void CListViewCompetitorsTeams::AssertValid() const
{
	CListView::AssertValid();
}

void CListViewCompetitorsTeams::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitorsTeams message handlers

void CListViewCompetitorsTeams::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// Only available if a single item is selected
	pCmdUI->Enable( m_nSelectedCount>=1 );
}

void CListViewCompetitorsTeams::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// Only available if a single item is selected
	pCmdUI->Enable( m_nSelectedCount>=1 );
}

void CListViewCompetitorsTeams::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_pDoc->CompetitorsCanPaste() );
}

void CListViewCompetitorsTeams::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// Only available if a single item is selected
	pCmdUI->Enable( m_nSelectedCount>=1 );
}

void CListViewCompetitorsTeams::OnUpdateEditEditselection(CCmdUI* pCmdUI) 
{
	// Only available if a single item is selected
	pCmdUI->Enable( m_nSelectedCount==1 );
}

void CListViewCompetitorsTeams::OnUpdateInsertRepeatedly(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (int)m_bRepeatedly );
}

void CListViewCompetitorsTeams::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (int)m_bGrid );
}

void CListViewCompetitorsTeams::OnUpdateViewBars(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( (int)m_bBars );
}

void CListViewCompetitorsTeams::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Arrange sort order
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if(m_nSortedColumn==pNMListView->iSubItem)
		m_bSortedAsc=!m_bSortedAsc;
	else
	{
		m_nSortedColumn = pNMListView->iSubItem;
		m_bSortedAsc = true;
	}
	SortItems(m_nSortedColumn, m_bSortedAsc, 0, -1);
	
	TCHAR x[5];
	_itot(m_nSortedColumn, &x[0], 10);

	*pResult = 0;
}

void CListViewCompetitorsTeams::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Act as if clicked on edit menu item
	SendMessage( WM_COMMAND, ID_EDIT_EDITSELECTION );
	
	*pResult = 0;
}

void CListViewCompetitorsTeams::OnEditSelectall() 
{
	if( m_edititem!=-1 )
		m_editWnd.SetSel(0,-1);
	else
	{
		LV_ITEM theItem;

		theItem.mask		= LVIF_STATE;
		theItem.iItem		= -1;
		theItem.iSubItem	= 0;
		theItem.state		= LVIS_SELECTED;
		theItem.stateMask	= 2;

		GetListCtrl().SetItemState(-1, &theItem);
	}
}

void CListViewCompetitorsTeams::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();

	if( m_bGrid )
		GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	else
		GetListCtrl().SetExtendedStyle((LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP)&~LVS_EX_GRIDLINES);

	m_imageList.Create( IDB_COMPETITORSTEAMS, 16, 1, RGB(255,0,255) );
	GetListCtrl().SetImageList( &m_imageList, LVSIL_SMALL );

	// Temporarely?
	PostMessage( WM_PAINT, (WPARAM)GetDC()->m_hDC );

	// Set the document pointer
	m_pDoc = (CStageRaceDoc*)GetDocument();
}

void CListViewCompetitorsTeams::OnInsertRepeatedly() 
{
	m_bRepeatedly=!m_bRepeatedly;
}

void CListViewCompetitorsTeams::OnViewGrid() 
{
	m_bGrid=!m_bGrid;

	DWORD dwOld = GetListCtrl().GetExtendedStyle();
	if( m_bGrid )
		GetListCtrl().SetExtendedStyle(dwOld|LVS_EX_GRIDLINES);
	else
		GetListCtrl().SetExtendedStyle(dwOld&~LVS_EX_GRIDLINES);
}

void CListViewCompetitorsTeams::OnViewBars() 
{
	m_bBars=!m_bBars;
	Invalidate();
}

void CListViewCompetitorsTeams::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_nSelectedCount = GetListCtrl().GetSelectedCount();
	*pResult = 0;
}

void CListViewCompetitorsTeams::OnSetFocus(CWnd* pOldWnd) 
{
	CListView::OnSetFocus(pOldWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion( (CStageRaceDoc*)GetDocument() );
}

void CListViewCompetitorsTeams::OnKillFocus(CWnd* pNewWnd) 
{
	CListView::OnKillFocus(pNewWnd);
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetDocVersion(NULL);
}

void CListViewCompetitorsTeams::OnNextPane() 
{
	// Delicate business beyond this point
	// We order the split frame that somewhere is
	//  the parent of this class to switch the active pane
	((CChildFrame*)
		((CSplitterWnd*)GetParent())
			->GetParent())
				->SetActivePaneTreeViewMain();
}

void CListViewCompetitorsTeams::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( m_edititem==-1 )
	{
		LVHITTESTINFO lvhit;
		lvhit.pt = point;
		int item = GetListCtrl().SubItemHitTest(&lvhit);

		// if over a subitem
		if( item != -1 && lvhit.iSubItem && (lvhit.flags&LVHT_ONITEM) )
		{
			m_subitem = lvhit.iSubItem;

			CRect rect;
			GetListCtrl().GetSubItemRect(item,m_subitem,LVIR_LABEL,rect);
			if(point.x < rect.left+16)
			{
				GetListCtrl().EditLabel(item);
				return;
			}
		}
		else
		{
			m_subitem = 0;
		}
	}

	CListView::OnLButtonDown(nFlags, point);
}

void CListViewCompetitorsTeams::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	switch( EditAllowedOnSubitem(m_subitem) )
	{
		case EDIT_CHECK:
			{
				CRect subrect;
				GetListCtrl().GetSubItemRect( pDispInfo->item.iItem,
					m_subitem,
					LVIR_BOUNDS,
					subrect );

				// Load the menu
				CMenu aMenu;
				aMenu.CreatePopupMenu();
				bool bSet = EditGetBool(pDispInfo->item.iItem,m_subitem);
				aMenu.AppendMenu(MF_STRING|(bSet?MF_CHECKED:0), 2, LoadStr(IDS_DIV96));
				aMenu.AppendMenu(MF_STRING|(bSet?0:MF_CHECKED), 1, LoadStr(IDS_DIV97));				

				ClientToScreen(&subrect);

				BOOL result = aMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
												subrect.CenterPoint().x,
												subrect.CenterPoint().y,
												this );

				if( result )
					EditSetBool(pDispInfo->item.iItem,m_subitem,result==2);

				*pResult = 1;
			}
			break;
		case EDIT_INLINE:
			{
				// if subitem selected for editing
				if(m_subitem)
				{
					CRect subrect;
					GetListCtrl().GetSubItemRect( pDispInfo->item.iItem,
						m_subitem,
						LVIR_BOUNDS,
						subrect );

					//get edit control and subclass
					HWND hWnd=(HWND)SendMessage(LVM_GETEDITCONTROL);
					ASSERT(hWnd!=NULL);
					VERIFY(m_editWnd.SubclassWindow(hWnd));

					m_editWnd.SetLimitText(EditFieldLength(m_subitem));
					if( EditNumeric(m_subitem) )
						m_editWnd.ModifyStyle(0,ES_NUMBER);

					m_editWnd.m_x	= subrect.left+4;
					m_editWnd.m_y	= subrect.top;

					m_editWnd.SetWindowText(
							GetListCtrl().GetItemText( pDispInfo->item.iItem,
								m_subitem
							)
						);

					//hide subitem text so it don't show if we delete some
					//text in the edit control
					//OnPaint handles other issues also regarding this
					CRect rect;
					GetListCtrl().GetSubItemRect( pDispInfo->item.iItem,
						m_subitem,
						LVIR_LABEL,
						rect);

					CDC* hDc = GetDC();
					hDc->FillRect( rect,
						&CBrush(::GetSysColor(COLOR_WINDOW)));
					ReleaseDC(hDc);

				}
				else
				{
					//get edit control and subclass
					HWND hWnd=(HWND)SendMessage(LVM_GETEDITCONTROL);
					ASSERT(hWnd!=NULL);

					((CEdit*)CWnd::FromHandle( hWnd ))->SetLimitText(EditFieldLength(m_subitem));
					if( EditNumeric(m_subitem) )
						((CEdit*)CWnd::FromHandle( hWnd ))->ModifyStyle(0,ES_NUMBER);
				}

				m_edititem = pDispInfo->item.iItem;
				// return: editing permitted
				*pResult = 0;
			}
			break;
		case EDIT_NOT:
		default:
			{
				MessageBeep(MB_ICONASTERISK);
				// return: editing not permitted
				*pResult = 1;
			}
	}
}

void CListViewCompetitorsTeams::OnPaint() 
{
	//if subitem editing
	if( m_subitem && (m_edititem!=-1))
	{
		CRect rect;
		//block filling redraw of leftmost item (caused by FillRect)
		GetListCtrl().GetItemRect( m_edititem, rect, LVIR_LABEL );
		ValidateRect(rect);
	}
	CListView::OnPaint();
}

void CListViewCompetitorsTeams::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
	LV_ITEM  *plvItem = &plvDispInfo->item;

	plvItem->iSubItem = m_subitem;
	// plvItem->pszText is NULL if editing canceled
	if( plvItem->pszText != NULL )
		UpdateField( plvItem );

	m_edititem = -1;
	//if (end of sub-editing) do cleanup
	if( m_subitem )
	{

		VERIFY(m_editWnd.UnsubclassWindow()!=NULL);

		m_subitem = 0;
		//always revert to org label (Windows thinks we are editing
		//the leftmost item)
		*pResult = 0;
	}
	else
	//return: update label on leftmost item
	*pResult = 0;
}

BOOL CListViewCompetitorsTeams::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= ( LVS_EDITLABELS|LVS_REPORT|LVS_SHOWSELALWAYS );
	return CListView::PreCreateWindow(cs);
}

// Restores the listview layout from the registry
void CListViewCompetitorsTeams::RestoreSettings(CString key)
{
	CListCtrl& ctrlList = GetListCtrl();

	int nColumnCount = ctrlList.GetHeaderCtrl()->GetItemCount();
	
	LONG er;
	CSRRegKey reg;
	er = reg.Open( HKEY_CURRENT_USER, "Software\\Totaal Software\\StageRace\\"+key );
	if( er == ERROR_SUCCESS )
	{
		//Column order
			// Read from registry
			CString cVal;
			cVal = reg.GetString( TEXT("Column order"), TEXT("") );

			// Convert string to int array
			int nTemp[25];
			int i;
			for( i = 0; (i<nColumnCount)&&(i<cVal.GetLength()); i++ )
				nTemp[i] = (int)(cVal[i]-'a');

			// Set the column order
			ctrlList.SetColumnOrderArray(i, nTemp);
			
		//Column widths
			for( i = 0; i<nColumnCount; i++ )
			{
				int n;
				n = reg.GetDWord( CString((char)('a'+i)), -1 );
				if( n != -1 )
					ctrlList.SetColumnWidth(i, n);
			}
		//Grid
			m_bGrid = reg.GetBool( TEXT("Show grid"), false );
			DWORD dwOld = GetListCtrl().GetExtendedStyle();
			if( m_bGrid )
				GetListCtrl().SetExtendedStyle(dwOld|LVS_EX_GRIDLINES);
			else
				GetListCtrl().SetExtendedStyle(dwOld&~LVS_EX_GRIDLINES);
		//Bars
			m_bBars = reg.GetBool( TEXT("Show bars"), false );
	}
}

// Stores the listview layout in the registry
void CListViewCompetitorsTeams::StoreSettings(CString key)
{
	CListCtrl& ctrlList = GetListCtrl();

	int nColumnCount = ctrlList.GetHeaderCtrl()->GetItemCount();
	
	LONG er;
	CSRRegKey reg;
	er = reg.Create( HKEY_CURRENT_USER, "Software\\Totaal Software\\StageRace\\"+key );
	if( er == ERROR_SUCCESS )
	{
		//Column order
			// Get the column order
			int nTemp[25];
			ctrlList.GetColumnOrderArray(nTemp, nColumnCount);
			
			// Convert int array to string
			CString cVal;
			int i;
			for( i = 0; i<nColumnCount; i++ )
				cVal += CString((char)('a'+nTemp[i]));

			// Write to registry
			reg.SetString( TEXT("Column order"), cVal );

		//Column widths
			for( i = 0; i<nColumnCount; i++ )
				reg.SetDWord( CString((char)('a'+i)), ctrlList.GetColumnWidth(i) );

		//Grid
			reg.SetBool( TEXT("Show grid"), m_bGrid );
		//Bars
			reg.SetBool( TEXT("Show bars"), m_bBars );
	}
}

void CListViewCompetitorsTeams::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
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
			*pResult |= CDRF_NOTIFYSUBITEMDRAW;
			break;
		case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
			{
				if( m_bBars && (nItem%2) )
					pNMLVCUSTOMDRAW->clrTextBk = BARSCOLOR;
			}
			break;
		default:
			ASSERT(CDRF_DODEFAULT==0);
			*pResult = 0;
    }
}

void CListViewCompetitorsTeams::OnEditCleanupcompetitors() 
{
	m_pDoc->CompetitorsCleanup();	
}
