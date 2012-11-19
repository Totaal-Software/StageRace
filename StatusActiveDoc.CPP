// StatusActiveDoc.cpp: implementation of the CStatusActiveDoc class.
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

CStatusActiveDoc::CStatusActiveDoc()
{

}

CStatusActiveDoc::~CStatusActiveDoc()
{

}

BEGIN_MESSAGE_MAP(CStatusActiveDoc, CStatusCombo)
	//{{AFX_MSG_MAP(CStatusActiveDoc)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CStatusActiveDoc::PreTranslateMessage(MSG *pMsg)
{
	if( pMsg->message == WM_USER_ACTIVEDOC_DOCOPEN )
	{
		AddDoc( (CStageRaceDoc*)pMsg->wParam );
		return true;
	}
	if( pMsg->message == WM_USER_ACTIVEDOC_DOCCLOSE )
	{
		RemoveDoc( (CStageRaceDoc*)pMsg->wParam );
		return true;
	}
	if( pMsg->message == WM_USER_ACTIVEDOC_DOCSELECT )
	{
		SelectDoc( (CStageRaceDoc*)pMsg->wParam );
		return true;
	}
	return false;
}

void CStatusActiveDoc::AddDoc(CStageRaceDoc *pDoc)
{
	bool bSelected = false;
	for( int i=GetCount(); i; i-- )
		if( GetItemData( i-1 )==(DWORD)pDoc )
		{
			if( i-1 == GetCurSel() )
				bSelected = true;
			DeleteString( i-1 );
		}
	int i = AddString( pDoc->GetTitle() );
	SetItemData( i, (DWORD)pDoc );
	if( bSelected )
		SetCurSel( i );
}

BOOL CStatusActiveDoc::Create(CStatusBar *parent, UINT id, DWORD style)
{
	if( CStatusCombo::Create( parent, id, style ) )
	{
		// Make a default 'not selected' string and select it
		int i = AddString( LoadStr( IDS_DIV51 ) );
		SetItemData( i, NULL );
		SetCurSel( i );

		// Return success
		return true;
	}
	return false;
}

void CStatusActiveDoc::RemoveDoc(CStageRaceDoc *pDoc)
{
	for( int i=GetCount(); i; i-- )
		if( GetItemData( i-1 )==(DWORD)pDoc )
		{
			if( i-1 == GetCurSel() )
				SetCurSel( 0 );
			DeleteString( i-1 );
			return;
		}
}

void CStatusActiveDoc::SelectDoc(CStageRaceDoc *pDoc)
{
	for( int i=GetCount(); i; i-- )
		if( GetItemData( i-1 )==(DWORD)pDoc )
		{
			SetCurSel(i-1);
			return;
		}
}

void CStatusActiveDoc::OnSelchange() 
{
	((CStageRaceApp*)AfxGetApp())->ActiveDocSelect(
		(CStageRaceDoc*)GetItemData( GetCurSel() ) );
}

HBRUSH CStatusActiveDoc::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	// Make this a wider listbox
	HBRUSH hbr = CStatusCombo::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_LISTBOX)
	{
		int nListWidth = 350;
		CRect rect;
		// New width of a listbox is defined
		pWnd->GetWindowRect(&rect);
		if (rect.Width() != nListWidth)
		{
			rect.left = rect.right - nListWidth;
			pWnd->MoveWindow(&rect);
		}
	}
	return hbr;
}
