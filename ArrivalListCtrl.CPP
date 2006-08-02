// ArrivalListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArrivalListCtrl

CArrivalListCtrl::CArrivalListCtrl()
{
	m_nColumnCount = 0;
	m_pCompetitorSource = NULL;
	m_pLockedCompetitors = NULL;
	m_pHighlightcallback = NULL;
}

BEGIN_MESSAGE_MAP(CArrivalListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CArrivalListCtrl)
	ON_WM_CHAR()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArrivalListCtrl message handlers

void CArrivalListCtrl::Init(unsigned short accuracy, ARRIVALLISTTYPES altType, const CArrivalList* pa/*=NULL*/)
{
	SetExtendedStyle((LVS_OWNERDRAWFIXED   |LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT)&~LVS_EX_GRIDLINES);

	m_pHighlightcallback = pa;
	m_accuracy = accuracy;
	m_type = altType;
	m_nColumnCount = 0;
	switch( m_type )
	{
		case ALT_CORRECTION:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 75, 0); // Start no.
			InsertColumn(1, LoadStr( IDS_DIV59 ), LVCFMT_RIGHT, 75, 1); // Bonus time
			InsertColumn(2, LoadStr( IDS_DIV60 ), LVCFMT_RIGHT, 75, 2); // Penalty time
			m_nColumnCount = 3;
			break;
		case ALT_TTORDERAVAILABLE:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 0); // Start no.
			InsertColumn(1, LoadStr( IDS_DIV62 ), LVCFMT_RIGHT, 30, 1); // Start time
			m_nColumnCount = 2;
			break;
		case ALT_AVAILABLERANKONLY:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 0); // Start no.
			m_nColumnCount = 1;
			break;
		case ALT_TTAVAILABLE:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV64 ), LVCFMT_RIGHT, 30, 0); // Order
			InsertColumn(1, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 1); // Start no.
			InsertColumn(2, LoadStr( IDS_DIV61 ), LVCFMT_RIGHT, 75, 2); // Time
			m_nColumnCount = 3;
			break;
		case ALT_AVAILABLE:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 0); // Start no.
			InsertColumn(1, LoadStr( IDS_DIV61 ), LVCFMT_RIGHT, 75, 1); // Time
			m_nColumnCount = 2;
			break;
		case ALT_TTORDERARRIVAL:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV64 ), LVCFMT_RIGHT, 30, 0); // Order
			InsertColumn(1, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 1); // Start no.
			InsertColumn(2, LoadStr( IDS_DIV65 ), LVCFMT_CENTER, 30, 2); // Ranked
			InsertColumn(3, LoadStr( IDS_DIV62 ), LVCFMT_RIGHT, 75, 3); // Start time
			m_nColumnCount = 4;
			break;
		case ALT_ARRIVALRANKONLY:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV63 ), LVCFMT_RIGHT, 30, 0); // Rank
			InsertColumn(1, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 1); // Start no.
			m_nColumnCount = 2;
			break;
		case ALT_TTARRIVAL:
		case ALT_ARRIVAL:
		default:
			// Add columns
			InsertColumn(0, LoadStr( IDS_DIV63 ), LVCFMT_RIGHT, 30, 0); // Rank
			InsertColumn(1, LoadStr( IDS_DIV58 ), LVCFMT_RIGHT, 30, 1); // Start no.
			InsertColumn(2, LoadStr( IDS_DIV61 ), LVCFMT_RIGHT, 80, 2); // Time
			m_nColumnCount = 3;
	}
	// Set first column's alignment explicitly
	LVCOLUMN lvCol;
	lvCol.mask	= LVCF_FMT;
	lvCol.fmt	= LVCFMT_RIGHT;
	SetColumn(0, &lvCol);

	// Add columns for competitor info
	InsertColumn(m_nColumnCount++, LoadStr( IDS_DIV12 ), LVCFMT_LEFT, 175, 2); // Competitor
	InsertColumn(m_nColumnCount++, LoadStr( IDS_DIV13 ), LVCFMT_LEFT, 175, 2); // Team
}

void CArrivalListCtrl::Draw(CArrival *pArr)
{
	// Make sure it does not yet exist
	int nItem = Clear( pArr->m_staNo );

	nItem = DrawIntern( pArr, nItem );

	// Make sure it's visible
	SetSelectionMark( nItem );

	SortItems();
}

void CArrivalListCtrl::DrawList(CArrivalList *pList)
{
	DeleteAllItems();
	CArrival aArr;
	POSITION nPos = pList->GetStartPosition();
	while( nPos )
	{
		pList->Iterate( nPos, aArr );
		DrawIntern( &aArr, -1 );
	}
	SortItems();
}

int CArrivalListCtrl::DrawIntern(CArrival *pArr, int nItem)
{
	// If the item didn't exist, use a new item no.
	if( nItem == -1 )
		nItem = GetItemCount();

	// Convert to text
	TCHAR buffer[10];
	
	// Add to ListControl
	switch( m_type )
	{
		case ALT_CORRECTION:
			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));

			// Bonus
			_itot(pArr->m_bonus, buffer, 10);
			SetItemText(nItem, 1, CString(buffer));

			// Penalty
			_itot(pArr->m_penalty, buffer, 10);
			SetItemText(nItem, 2, CString(buffer));

			break;
		case ALT_TTORDERAVAILABLE:
			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));

			// Start time
			SetItemText(nItem, 1, CStageTime( pArr->m_unitsAtStart ).GetFormattedWide() );
			break;
		case ALT_TTAVAILABLE:
			// Order
			_itot(pArr->m_order, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));

			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			SetItemText(nItem, 1, CString(buffer));

			// Start time
			SetItemText(nItem, 2, CStageTime( pArr->m_unitsAtStart ).GetFormattedWide() );
			break;
		case ALT_AVAILABLE:
			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));

			// Time
			SetItemText(nItem, 1, CStageTime( pArr->m_units ).GetFormattedWide() + CStageTime( pArr->m_units ).GetThousandth().Left( 3-m_accuracy ) );
			break;
		case ALT_AVAILABLERANKONLY:
			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));
			break;
		case ALT_TTORDERARRIVAL:
			// Order
			_itot(pArr->m_order, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer));

			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			SetItemText(nItem, 1, CString(buffer));

			// Ranked
			if( m_pLockedCompetitors )
				if( m_pLockedCompetitors->Exist( pArr->m_staNo ) )
					SetItemText(nItem, 2, TEXT(" * "));

			// Start time
			SetItemText(nItem, 3, CStageTime( pArr->m_unitsAtStart ).GetFormattedWide() );
			break;
		case ALT_ARRIVALRANKONLY:
			// Rank
			_itot(pArr->m_rank, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer)+".");

			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			SetItemText(nItem, 1, CString(buffer));
			break;
		case ALT_TTARRIVAL:
		case ALT_ARRIVAL:
		default:
			// Rank
			_itot(pArr->m_rank, buffer, 10);
			nItem = InsertItem(nItem, CString(buffer)+".");

			// StaNo
			_itot(pArr->m_staNo, buffer, 10);
			SetItemText(nItem, 1, CString(buffer));

			// Time
			SetItemText(nItem, 2, CStageTime( pArr->m_units ).GetFormattedWide() + CStageTime( pArr->m_units ).GetThousandth().Left( 3-m_accuracy ) );
	}

	if( m_pCompetitorSource )
	{
		CCompetitor aComp = m_pCompetitorSource->GetAt( pArr->m_staNo );
		SetItemText(nItem,m_nColumnCount-2,aComp.m_competitor);
		if( aComp.m_pTeam )
			SetItemText(nItem,m_nColumnCount-1,aComp.m_pTeam->m_name);
	}

	// Set the item data
	SetItemData(nItem, pArr->m_staNo);

	return nItem;
}

void CArrivalListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar == 1 ) // 1 == Ctrl+A
	{
		SelectAll();
	}
	CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CArrivalListCtrl::SelectAll()
{
	LV_ITEM item;

	item.mask		= LVIF_STATE;
	item.iItem		= -1;
	item.iSubItem	= 0;
	item.state		= LVIS_SELECTED;
	item.stateMask	= 2;

	SetItemState(-1, &item);
}

void CArrivalListCtrl::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
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
				// Sub Item PrePaint
				// Set sub item number (data will be valid now)
				WORD n=pNMLVCUSTOMDRAW->nmcd.lItemlParam;
				if( m_pHighlightcallback && m_pHighlightcallback->IsTimeCutted(n) )
				{
					pNMLVCUSTOMDRAW->clrText	= RGB( 0xFF, 0, 0 );
					pNMLVCUSTOMDRAW->clrTextBk	= RGB( 0xFF, 0xF4, 0xF4 );
				}
				else
				{
					pNMLVCUSTOMDRAW->clrText = CLR_DEFAULT;
					pNMLVCUSTOMDRAW->clrText = CLR_DEFAULT;
				}
			}
			break;
		default:
			ASSERT(CDRF_DODEFAULT==0);
			*pResult = 0;
    }
}


