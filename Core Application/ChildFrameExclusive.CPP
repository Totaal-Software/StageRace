// ChildFrameExclusive.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrameExclusive

IMPLEMENT_DYNCREATE(CChildFrameExclusive, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrameExclusive, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrameExclusive)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrameExclusive message handlers

void CChildFrameExclusive::OnClose() 
{
	GetActiveDocument()->RemoveView(GetActiveView());
	DestroyWindow();
}
