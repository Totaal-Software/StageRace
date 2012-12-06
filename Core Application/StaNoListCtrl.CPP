// StaNoListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaNoListCtrl

CStaNoListCtrl::CStaNoListCtrl()
{
}

BEGIN_MESSAGE_MAP(CStaNoListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CStaNoListCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaNoListCtrl message handlers

WORD CStaNoListCtrl::GetSelected()
{
	POSITION nPos = GetFirstSelectedItemPosition();
	return (WORD)GetItemData( GetNextSelectedItem(nPos) );
}

void CStaNoListCtrl::Select(WORD nStaNo)
{
	// Make sure it's visible
	for( int i=0; i<GetItemCount(); i++ )
		if( GetItemData(i)==nStaNo )
		{
			LVITEM lvItem;
			lvItem.iItem = i;
			lvItem.iSubItem = 0;
			lvItem.mask = LVIF_STATE;
			lvItem.stateMask = LVIS_SELECTED|LVIS_FOCUSED;
			lvItem.state = LVIS_SELECTED|LVIS_FOCUSED;
			SetItem(&lvItem);

			EnsureVisible( i, FALSE );
			return;
		}
}

int CStaNoListCtrl::Clear(WORD nStaNo)
{
	// Look for an old view item with the same StaNo and remove it
	// Just iterate the whole list control, looking for our item
	for( int i=0; i<GetItemCount(); i++ )
		if( GetItemData(i)==nStaNo )
		{
			DeleteItem( i );
			SortItems();
			return i;
		}
	return -1;
}

void CStaNoListCtrl::SortItems()
{
	CListCtrl::SortItems( (PFNLVCOMPARE)&CompareFunc, (unsigned long)this );
}

int CALLBACK CStaNoListCtrl::CompareFunc(
	LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	LVFINDINFO find1, find2;
	find1.flags	= LVFI_PARAM;
	find1.lParam= lParam1;
	find2.flags	= LVFI_PARAM;
	find2.lParam= lParam2;
	
	int item1, item2;
	item1 = ((CListCtrl*)lParamSort)->FindItem( &find1 );
	item2 = ((CListCtrl*)lParamSort)->FindItem( &find2 );

	WORD value1, value2;
	value1 = (WORD) _ttoi( ((CListCtrl*)lParamSort)->GetItemText( item1, 0 ) );
	value2 = (WORD) _ttoi( ((CListCtrl*)lParamSort)->GetItemText( item2, 0 ) );

	return value1-value2;
}

