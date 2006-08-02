// ListViewActiveDoc.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewActiveDoc

IMPLEMENT_DYNCREATE(CListViewActiveDoc, CListView)

BEGIN_MESSAGE_MAP(CListViewActiveDoc, CListView)
	//{{AFX_MSG_MAP(CListViewActiveDoc)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RETURN, OnReturn)
	ON_COMMAND(ID_EDIT_SELECT, OnEditSelect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT, OnUpdateEditSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewActiveDoc diagnostics

#ifdef _DEBUG
void CListViewActiveDoc::AssertValid() const
{
	CListView::AssertValid();
}

void CListViewActiveDoc::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewActiveDoc message handlers

BOOL CListViewActiveDoc::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= ( LVS_REPORT|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER|LVS_SINGLESEL );
	return CListView::PreCreateWindow(cs);
}

void CListViewActiveDoc::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// This will automatically display a wait cursor
	CWaitCursor objCursor;

	// Set the document pointer
	m_pDoc = (CActiveDocTracker*)GetDocument();

	// Make an image list
	m_imageListState.Create( IDB_LISTSTATE, 20, 1, RGB(255,0,255) );

	// Set listview styles
	CListCtrl& ctrlList = GetListCtrl();
	ctrlList.SetExtendedStyle((LVS_REPORT|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT)&~LVS_EX_GRIDLINES);
	ctrlList.SetImageList( &m_imageListState, LVSIL_STATE );

	// Add columns
	ctrlList.InsertColumn(0, LoadStr( IDR_ACTIVEDOCTRACKER ), LVCFMT_LEFT, 500, 0);

	// Fill the list
	ctrlList.SetItemData(
		ctrlList.InsertItem(
			0,
			LoadStr( IDS_DIV51 ),
			0
		),
		NULL
	);
	for( UINT i=0; i<m_pDoc->GetCount(); i++ )
		ctrlList.SetItemData(
			ctrlList.InsertItem(
				ctrlList.GetItemCount(),
				m_pDoc->GetAt(i)->GetTitle(),
				0
			),
			(DWORD)m_pDoc->GetAt(i)
		);
	OnUpdate( NULL, UV_SELECTIONCHANGED, (CObject*)m_pDoc->GetSelected() );
}

void CListViewActiveDoc::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CListCtrl& ctrlList = GetListCtrl();
	const CStageRaceDoc* pDoc = (CStageRaceDoc*)pHint;
	switch( lHint )
	{
		case UV_ADDED:
			{
				// Add a new line
				// Based on the document pointed passed
				int i = ctrlList.InsertItem(
							ctrlList.GetItemCount(),
							pDoc->GetTitle(),
							0
						);
				ctrlList.SetItemData( i, (DWORD)pDoc );
				ctrlList.SetCheck( i, FALSE );
				break;
			}
		case UV_DELETED:
			{
				// Search for the existing line
				for( int i=0; i<ctrlList.GetItemCount(); i++ )
					// Based on the document pointed passed
					if( ctrlList.GetItemData(i)==(DWORD)pDoc )
					{
						// Remove it
						ctrlList.DeleteItem(i);
						break;
					}
				break;
			}
		case UV_UPDATED:
			{
				// Search for the existing line
				for( int i=0; i<ctrlList.GetItemCount(); i++ )
					// Based on the document pointed passed
					if( ctrlList.GetItemData(i)==(DWORD)pDoc )
					{
						// Redo the text
						ctrlList.SetItemText(i,0,pDoc->GetTitle());
						break;
					}
				break;
			}
		case UV_SELECTIONCHANGED:
			{
				// Search for the existing line
				for( int i=0; i<ctrlList.GetItemCount(); i++ )
					// Based on the document pointed passed
					if( ctrlList.GetItemData(i)==(DWORD)pDoc )
						// Set the selected image
						ctrlList.SetCheck(i);
					else
						// While at it, reset all other selected images
						ctrlList.SetCheck(i, FALSE);
				break;
			}
	}
}

void CListViewActiveDoc::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl& ctrlList = GetListCtrl();
	// When double clicked
	// Search the selected item
	POSITION nPos = ctrlList.GetFirstSelectedItemPosition();
	if( nPos )
		// Pass the selected item to the document
		m_pDoc->Select( (CStageRaceDoc*)
			ctrlList.GetItemData(
				ctrlList.GetNextSelectedItem(nPos)
			)
		);
	// Note that view update will be invoked by the document
	*pResult = 0;
}


void CListViewActiveDoc::OnReturn(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// On [ENTER] the same action is required as on OnDblClk
	OnDblclk(pNMHDR,pResult);
	*pResult = 0;
}

void CListViewActiveDoc::OnEditSelect() 
{
	CListCtrl& ctrlList = GetListCtrl();
	// When double clicked
	// Search the selected item
	POSITION nPos = ctrlList.GetFirstSelectedItemPosition();
	if( nPos )
		// Pass the selected item to the document
		m_pDoc->Select( (CStageRaceDoc*)
			ctrlList.GetItemData(
				ctrlList.GetNextSelectedItem(nPos)
			)
		);
}

void CListViewActiveDoc::OnUpdateEditSelect(CCmdUI* pCmdUI) 
{
	CListCtrl& ctrlList = GetListCtrl();
	// When double clicked
	// Search the selected item
	POSITION nPos = ctrlList.GetFirstSelectedItemPosition();
	if( nPos
		&& m_pDoc->GetSelected()!=
			(CStageRaceDoc*) ctrlList.GetItemData(
							ctrlList.GetNextSelectedItem(nPos)
			)
		)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}