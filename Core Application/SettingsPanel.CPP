// SettingsPanel.cpp: implementation of the CSettingsPanel class.
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

BEGIN_MESSAGE_MAP(CSettingsPanel, COptionsPanel)
	//{{AFX_MSG_MAP(CSettingsPanel
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSettingsPanel::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if( !GetItemAtCursor() )
		GetParent()->SendMessage( WM_LBUTTONDBLCLK );
}

bool CSettingsPanel::IsScroll()
{
	if(IsWindow(GetSafeHwnd()))
		return (m_wndVertScroll.IsWindowVisible()>0);
	else
		return false;
}
