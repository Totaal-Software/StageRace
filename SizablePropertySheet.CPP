// SizablePropertySheet.cpp: implementation of the CSizablePropertySheet class.
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

BEGIN_MESSAGE_MAP(CSizablePropertySheet, cdxCDynamicPropSheet)
	//{{AFX_MSG_MAP(CSizablePropertySheet)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMapStringToPtr CSizablePropertySheet::m_selectedtabs;

CSizablePropertySheet::CSizablePropertySheet(LPCTSTR pszCaption, LPCTSTR pszRegistryName) : cdxCDynamicPropSheet(pszCaption)
{
	ActivateAutoPos( pszRegistryName );
	m_psh.dwFlags = m_psh.dwFlags | PSH_NOAPPLYNOW;
}

BOOL CSizablePropertySheet::OnInitDialog()
{
	// Modifications by Totaal Software
	ModifyStyle(0,WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU);
	SetIcon( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_DIALOG ) ), TRUE );

	BOOL b = cdxCDynamicPropSheet::OnInitDialog();

	int i;
	if( m_selectedtabs.Lookup( m_strAutoPos, (void*&)i ) )
		if( i<GetPageCount() )
			SetActivePage( i );

	return b;
}

void CSizablePropertySheet::OnSysCommand(UINT nID, LPARAM lparam)
{
	switch( nID&0xFFF0 )
	{
		// Trapping the close icon in the caption bar
		case SC_CLOSE:
			int i = GetActiveIndex();
			m_selectedtabs.SetAt( m_strAutoPos, (void*)i);
	}
	cdxCDynamicPropSheet::OnSysCommand(nID, lparam);
}

BOOL CSizablePropertySheet::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if( (LOWORD(wParam)==IDCANCEL) || (LOWORD(wParam)==IDOK) )
	{
		// Trapping the OK and Cancel buttons
		int i = GetActiveIndex();
		m_selectedtabs.SetAt( m_strAutoPos, (void*)i);
	}
	return cdxCDynamicPropSheet::OnCommand(wParam, lParam);
}
