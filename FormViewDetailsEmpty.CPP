// FormViewDetailsEmpty.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormViewDetailsEmpty

IMPLEMENT_DYNCREATE(CFormViewDetailsEmpty, CFormView)

CFormViewDetailsEmpty::CFormViewDetailsEmpty()
	: CFormView(CFormViewDetailsEmpty::IDD)
{
	// White background
	m_brush.CreateSolidBrush(RGB(255, 251, 255)); // color (broken) white brush 
	//{{AFX_DATA_INIT(CFormViewDetailsEmpty)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bannerbottom.LoadBitmap(IDB_BORDERLINE);
}

CFormViewDetailsEmpty::~CFormViewDetailsEmpty()
{
}

void CFormViewDetailsEmpty::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormViewDetailsEmpty)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormViewDetailsEmpty, CFormView)
	//{{AFX_MSG_MAP(CFormViewDetailsEmpty)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_NEXT_PANE, OnNextPane)
	ON_COMMAND(ID_PREV_PANE, OnNextPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormViewDetailsEmpty diagnostics

#ifdef _DEBUG
void CFormViewDetailsEmpty::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormViewDetailsEmpty::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormViewDetailsEmpty message handlers

HBRUSH CFormViewDetailsEmpty::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// We return to alternative brush in order to obtain the coloured background
	return m_brush;
}

void CFormViewDetailsEmpty::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	// Code from CodeGuru - Henry Wu
	// Automatically Center the Controls in CFormView

	if ((GetScrollPos(SB_HORZ) != 0) || (GetScrollPos(SB_VERT) != 0))
	{
		return;
	}

	int   topMargin = 2, leftMargin = 2;
	CRect rectView, rectTotal;
	GetWindowRect(&rectView);

	for (CWnd *wnd = GetWindow(GW_CHILD); wnd != NULL;
		wnd = wnd->GetWindow(GW_HWNDNEXT))
	{
		CWnd *pWnd = GetDlgItem(IDC_FORMVIEWDETAILSEMPTYSIZE);
		pWnd->GetWindowRect(&rectTotal);

		CRect rect;
		int xPos, yPos;
		wnd->GetWindowRect(&rect);
		if(rectView.Width()>(rectTotal.Width() + 2*leftMargin))
		{
			xPos = (rectView.Width() - rectTotal.Width())/2;
		} 
		else 
		{
			xPos = leftMargin;
		}

		if(rectView.Height()>(rectTotal.Height() + 2*topMargin))
		{
			yPos = (rectView.Height() - rectTotal.Height())/2;
		}
		else 
		{
			yPos = topMargin;
		}
		wnd->MoveWindow(xPos + rect.left - rectTotal.left, 
		yPos + rect.top - rectTotal.top, 
		rect.Width(), rect.Height(), TRUE);
	}
}

void CFormViewDetailsEmpty::OnNextPane()
{
	// Delicate business beyond this point
	// We order the split frame that somewhere is
	//  the parent of this class to switch the active pane
	((CChildFrame*)
		((CSplitterWnd*)GetParent())
			->GetParent())
				->SetActivePaneTreeViewMain();
}
