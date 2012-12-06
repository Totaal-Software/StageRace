// StatusGenerate.cpp: implementation of the CStatusGenerate class.
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

CStatusGenerate::CStatusGenerate()
{
	m_nProgressLength = 0;
}

CStatusGenerate::~CStatusGenerate()
{

}

void CStatusGenerate::Start(int progresslength)
{
	m_nProgressLength = progresslength;
	SetRange( 0, progresslength );
	SetPos(0);
	ShowWindow(SW_SHOW);
}

void CStatusGenerate::Finish()
{
	SetPos(0);
	ShowWindow(SW_HIDE);
}

void CStatusGenerate::Increment()
{
#ifdef _DEBUG
	if( GetPos() == m_nProgressLength )
	{
		ASSERT(0);
	}
#endif //_DEBUG
	SetPos( GetPos()+1 );
	if( GetPos() == m_nProgressLength )
	{
		ShowWindow(SW_HIDE);
	}
}

BOOL CStatusGenerate::PreTranslateMessage(MSG *pMsg)
{
	if( pMsg->message == WM_USER_GENERATE_PROGRESS_SET )
	{
		Start( (int)pMsg->wParam );
		return true;
	}
	if( pMsg->message == WM_USER_GENERATE_PROGRESS_INCREMENT )
	{
		Increment();
		return true;
	}
	if( pMsg->message == WM_USER_GENERATE_PROGRESS_FINISH )
	{
		Finish();
		return true;
	}
	return false;
}

BOOL CStatusGenerate::Create(CStatusBar * parent, UINT id, DWORD style)
{
	BOOL b = CStatusProgress::Create(parent, id, style);

	// Initially hide
	ShowWindow(SW_HIDE);

	return b;
}

void CStatusGenerate::Reposition()
{
	// "Overridden" from CStatusControl so that we can
	// set our own window positions
	if(m_hWnd == NULL)
		return;
	UINT id = ::GetWindowLong(m_hWnd, GWL_ID);
	CRect r;

	CStatusBar * parent = (CStatusBar *)GetParent();
	int i = parent->CommandToIndex(id);
	parent->GetItemRect(i, &r);
	SetWindowPos(&wndTop, r.left+4, r.top+4, r.Width()-8, r.Height()-8, 0);
}
