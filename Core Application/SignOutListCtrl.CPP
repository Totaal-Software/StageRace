// SignOutListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignOutListCtrl

CSignOutListCtrl::CSignOutListCtrl()
{
}

BEGIN_MESSAGE_MAP(CSignOutListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CSignOutListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignOutListCtrl message handlers

void CSignOutListCtrl::Init()
{
	SetExtendedStyle((LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP)&~LVS_EX_GRIDLINES);
	
	m_nColumnCount = 2;
	// Add columns
	InsertColumn(0, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 60, 0); // Start no.
	InsertColumn(1, LoadStr( IDS_DIV67 ), LVCFMT_LEFT, 200, 0); // Reason

	// Set first column's alignment explicitly
	LVCOLUMN lvCol;
	lvCol.mask	= LVCF_FMT;
	lvCol.fmt	= LVCFMT_RIGHT;
	SetColumn(0, &lvCol);

	// Add columns for competitor info
	InsertColumn(m_nColumnCount++, LoadStr( IDS_DIV12 ), LVCFMT_LEFT, 175, 2); // Competitor
	InsertColumn(m_nColumnCount++, LoadStr( IDS_DIV13 ), LVCFMT_LEFT, 175, 2); // Team
}

void CSignOutListCtrl::Draw(CSignOut *pSO)
{
	// Make sure it does not yet exist
	int nItem = Clear( pSO->m_staNo );

	nItem = DrawIntern( pSO, nItem );

	// Make sure it's visible
	SetSelectionMark( nItem );

	SortItems();
}

void CSignOutListCtrl::DrawList(CSignOutList *pList)
{
	DeleteAllItems();

	pList->LockRead();

	CSignOut aSO;
	POSITION nPos = pList->GetStartPosition();
	while( nPos )
	{
		pList->Iterate( nPos, aSO );
		DrawIntern( &aSO, -1 );
	}

	pList->UnlockRead();

	SortItems();
}

int CSignOutListCtrl::DrawIntern(CSignOut *pSO, int nItem)
{
	// If the item didn't exist, use a new item no.
	if( nItem == -1 )
		nItem = GetItemCount();

	// Convert to text
	TCHAR buffer[10];

	// Add to ListControl
		// StaNo
		_itot(pSO->m_staNo, buffer, 10);
		nItem = InsertItem(nItem, CString(buffer));

		// Bonus
		SetItemText(nItem, 1, pSO->m_reasonOfSignOut);

	if( m_pCompetitorSource )
	{
		CCompetitor aComp = m_pCompetitorSource->GetAt( pSO->m_staNo );
		SetItemText(nItem,m_nColumnCount-2,aComp.m_competitor);
		if( aComp.m_pTeam )
			SetItemText(nItem,m_nColumnCount-1,aComp.m_pTeam->m_name);
	}

	// Set the item data
	SetItemData(nItem, pSO->m_staNo);

	return nItem;
}
