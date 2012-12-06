// SubEdit1.cpp : implementation file
//

#include "stdafx.h"
#include "SubEdit1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubEdit

CSubEdit::CSubEdit()
{
}

CSubEdit::~CSubEdit()
{
}


BEGIN_MESSAGE_MAP(CSubEdit, CEdit)
	//{{AFX_MSG_MAP(CSubEdit)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubEdit message handlers

void CSubEdit::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	lpwndpos->x		=	m_x;
	lpwndpos->y		=	m_y;

	if (!(lpwndpos->flags & SWP_NOSIZE))
	{
		// Set dimensions of the box based on the current text
		CDC* pDC = GetDC();
		if (pDC)
		{
			CString str;
			GetWindowText(str);
			// Set a Font
			CFont* pOldFont =
				pDC->SelectObject( GetFont() );
			// Check the size of the current text
			// The space is in order to get a cy even with empty string
			CSize size = pDC->GetTextExtent(str+TEXT(" "));
			// Restore the old font
			pDC->SelectObject( pOldFont );

			ReleaseDC(pDC);

			// Set the width, with a minimum of 38 though
			lpwndpos->cx = max( 38, size.cx+17 );
			// Set the height
			lpwndpos->cy = size.cy+4;
		}
	}


	CEdit::OnWindowPosChanging(lpwndpos);
	
	// TODO: Add your message handler code here
	
}

void CSubEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect rect;
	this->GetWindowRect(&rect);
	CEdit::OnChar( nChar, nRepCnt, nFlags );
}
