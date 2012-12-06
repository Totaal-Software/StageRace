// StaNoEdit.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaNoEdit

CStaNoEdit::CStaNoEdit()
{
}

CStaNoEdit::~CStaNoEdit()
{
}


BEGIN_MESSAGE_MAP(CStaNoEdit, CEdit)
	//{{AFX_MSG_MAP(CStaNoEdit)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaNoEdit message handlers

void CStaNoEdit::AddStaNoObjectList(CStaNoObjectList *pList)
{
	m_list.AddTail( pList );
}

bool CStaNoEdit::Exist()
{
	if( GetValue() )
	{
		POSITION nPos = m_list.GetHeadPosition();
		while( nPos )
			if( m_list.GetNext( nPos )->Exist( GetValue() ) )
				return true;
	}
	return false;
}

WORD CStaNoEdit::GetValue()
{
	CString cEntered;
	GetWindowText( cEntered );
	return _ttoi( cEntered );
}

void CStaNoEdit::OnKillfocus() 
{
	if( GetValue() && !Exist() )
	{
		CString cEntered;
		GetWindowText( cEntered );
		SetWindowText( TEXT("0") );
		MessageBox( LoadStr( IDS_MBC_9 )+cEntered,
					LoadStr( IDS_MBT_9 ),
					MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );
		SetFocus();
		SetSel( 0, -1 );
	}
}

BOOL CStaNoEdit::PreTranslateMessage(MSG* pMsg) 
{
	// Make sure there is something to submit
	// before we acknowledge [ENTER] being pressed
	if( pMsg->message==WM_KEYDOWN &&
		pMsg->wParam==VK_RETURN )
	{
		// If 0 entered, do nothing
		if( !GetValue() )
			return TRUE;
		// If invalid value entered, do error thingy
		if( !Exist() )
		{
			OnKillfocus();
			return TRUE;
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CStaNoEdit::SetValue(WORD nStaNo)
{
	TCHAR czBuffer[10];
	_itot( nStaNo, czBuffer, 10 );
	SetWindowText( czBuffer );
}
