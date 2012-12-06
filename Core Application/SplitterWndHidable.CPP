// SplitterWndHidable.cpp: implementation of the CSplitterWndHidable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSplitterWndHidable::CSplitterWndHidable() : m_bLeftHidden(false)
{
	m_cxSplitter=9;
	m_cxBorderShare=0;
	m_cxSplitterGap=9;
}

BEGIN_MESSAGE_MAP(CSplitterWndHidable, AW_CMultiViewSplitter)
	//{{AFX_MSG_MAP(CIdView)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define MINWIDTH 50

void CSplitterWndHidable::Hide()
{
	if( m_bLeftHidden = !m_bLeftHidden )
	{//HIDE IT
		// Make sure always to set the not hidden pane to be active
		SetActivePane(0, 1);
		// Hide all column panes
		for( int row=0; row<m_nRows; row++ )
		{
			CWnd* pPaneHide = GetPane(row, 0);
			pPaneHide->ShowWindow(SW_HIDE);
			pPaneHide->SetDlgCtrlID(
				AFX_IDW_PANE_FIRST + row * 16 + m_nCols);

			for( int col=1; col<m_nCols; col++ )
			{
				CWnd* pPane = GetPane(row, col);
				pPane->SetDlgCtrlID(IdFromRowCol(row, col - 1));
			}
		}
		m_nCols--;
		m_pColInfo[m_nCols].nCurSize = m_pColInfo[0].nCurSize;
		RecalcLayout();
	}
	else
	{// SHOW IT AGAIN
		int cxNew = m_pColInfo[m_nCols].nCurSize;
		m_nCols++;  // Add a column
		// Fill the hided column
		for( int row = 0; row < m_nRows; row++ )
		{
			CWnd* pPaneShow = GetDlgItem(
				AFX_IDW_PANE_FIRST + row * 16 + m_nCols);

			pPaneShow->ShowWindow(SW_SHOWNA);

			for( int col = m_nCols - 2; col >= 0; col-- )
			{
			   CWnd* pPane = GetPane(row, col);
			   ASSERT(pPane != NULL);
			   pPane->SetDlgCtrlID(IdFromRowCol(row, col + 1));
			}
			pPaneShow->SetDlgCtrlID(IdFromRowCol(row, 0));
		}
		// New panes have been created -- recalculate layout
		for( int col = 1; col < m_nCols; col++ )
			m_pColInfo[col].nIdealSize = m_pColInfo[col - 1].nCurSize;
		m_pColInfo[0].nIdealSize = cxNew;
		RecalcLayout();
		// Get the width of the left column
		int cxCur, cxMin;
		GetColumnInfo( 0, cxCur, cxMin );
		// If it is very narrow, make it less narrow
		if( cxCur<MINWIDTH )
		{
			SetColumnInfo( 0, MINWIDTH, cxMin );
			RecalcLayout();
		}
	}
}

bool CSplitterWndHidable::Hidden()
{
	return m_bLeftHidden;
}

void CSplitterWndHidable::GetPaneFromViewID(int nViewID, CPoint *pane)
{
	AW_CMultiViewSplitter::GetPaneFromViewID( nViewID, pane );
	// If the first pane is hidden, tell the other pane's views
	// that they're in that first view
	if( Hidden() )
		pane->y--;
}

void CSplitterWndHidable::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	// Let's pretent this is only fired if double clicked on the
	// splitter bar (it's not, it also responds to some small edges)
	Hide();
}

void CSplitterWndHidable::OnLButtonUp(UINT nFlags, CPoint point)
{
	AW_CMultiViewSplitter::OnLButtonUp(nFlags, point);
	// Get the width of this left column
	int cxCur, cxMin;
	GetColumnInfo( 0, cxCur, cxMin );
	// If it is very narrow, hide it entirely
	if( (cxCur<MINWIDTH) && !Hidden() )
		Hide();
}
