// StageRaceWnd.h: interface for the CStageRaceWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAGERACEWND_H__8EA058A5_71F7_4399_9AE1_61D9FA1EA759__INCLUDED_)
#define AFX_STAGERACEWND_H__8EA058A5_71F7_4399_9AE1_61D9FA1EA759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// Definition

template <class T> class CStageRaceWnd : public T
{
public:
	CStageRaceWnd( CHelp::HELP_TOPIC helptopic, LPCTSTR pszCaption, CWnd *pParentWnd = NULL, UINT iSelectPage = 0 );
	CStageRaceWnd( CHelp::HELP_TOPIC helptopic, UINT nIDTemplate, CWnd* pParentWnd = NULL );
	CStageRaceWnd( CHelp::HELP_TOPIC helptopic, UINT nIDTemplate, UINT nIDCaption );
	BOOL PreTranslateMessage(MSG *pMsg);
protected:
	CHelp::HELP_TOPIC m_helptopic;
	CBitmap m_borderline;
	CBitmap m_bannerbottom;
	CButton m_btnHelp;
	CFont m_fntBtnHelp;
	CBrush m_brush;

	void OnHelp();
	void OnSize(UINT nType, int cx, int cy);
	HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	BOOL OnInitDialog();
	BOOL OnEraseBkgnd(CDC* pDC);

// Message map
	static const AFX_MSGMAP* PASCAL _GetBaseMessageMap();
	static const AFX_MSGMAP* GetMessageMap();
	static AFX_COMDAT AFX_DATADEF const AFX_MSGMAP messageMap;
	static AFX_COMDAT const AFX_MSGMAP_ENTRY _messageEntries[];
};

//////////////////////////////////////////////////////////////////////
// Implementation

template <class T> BOOL CStageRaceWnd<T>::OnEraseBkgnd(CDC* pDC) 
{
	T::OnEraseBkgnd(pDC);

	if(!m_borderline.m_hObject)
		return true;

	// Get the rectangle for the dialog
	CRect rectdlg;
	GetClientRect(&rectdlg);

	// Create a DC to work with
	CDC dc;
	dc.CreateCompatibleDC(pDC);

	int bmw, bmh;
	BITMAP bmap;
	CBitmap* pOldBitmap;

	// Draw the borderline
	pOldBitmap = dc.SelectObject(&m_borderline);
	
	m_borderline.GetBitmap(&bmap);

	bmw=bmap.bmWidth;
	bmh=bmap.bmHeight;

	pDC->StretchBlt( 0, rectdlg.Height()-25,
			rectdlg.Width(), rectdlg.Height()-22,
			&dc,
			0, 0,
			bmap.bmWidth, bmap.bmHeight,
			SRCCOPY );

	// Draw the bottom bitmap
	dc.SelectObject(&m_bannerbottom);
	
	m_bannerbottom.GetBitmap(&bmap);

	bmw=bmap.bmWidth;
	bmh=bmap.bmHeight;

	pDC->BitBlt( 0, rectdlg.Height()-22,
			rectdlg.Width(), rectdlg.Height(),
			&dc,
			0, 0,
			SRCCOPY );
	
	// Fill the rest of the banner
	CRect rect1( bmap.bmWidth, rectdlg.Height()-22, rectdlg.Width(), rectdlg.Height() );
	CBrush black(RGB(0,0,0));
	pDC->FillRect( &rect1, &black );
	
	dc.SelectObject(pOldBitmap);

	return true;
}

template <class T> CStageRaceWnd<T>::CStageRaceWnd(CHelp::HELP_TOPIC helptopic, LPCTSTR pszCaption, CWnd *pParentWnd/* =NULL*/, UINT iSelectPage/* =0*/)
	: T(pszCaption, pParentWnd, iSelectPage)
{
	m_helptopic = helptopic;
	m_borderline.LoadBitmap(IDB_BORDERLINE);
	m_bannerbottom.LoadBitmap(IDB_BANNERBOTTOM);

	m_brush.CreateSolidBrush(RGB(0, 0, 0)); // color black brush 
}

template <class T> CStageRaceWnd<T>::CStageRaceWnd(CHelp::HELP_TOPIC helptopic, UINT nIDTemplate, CWnd *pParentWnd/* =NULL*/)
	: T(nIDTemplate, pParentWnd)
{
	m_helptopic = helptopic;
	m_borderline.LoadBitmap(IDB_BORDERLINE);
	m_bannerbottom.LoadBitmap(IDB_BANNERBOTTOM);

	m_brush.CreateSolidBrush(RGB(0, 0, 0)); // color black brush 
}

template <class T> CStageRaceWnd<T>::CStageRaceWnd(CHelp::HELP_TOPIC helptopic, UINT nIDTemplate, UINT nIDCaption/*No default!*/)
	: T(nIDTemplate, nIDCaption)
{
	m_helptopic = helptopic;
	m_borderline.LoadBitmap(IDB_BORDERLINE);
	m_bannerbottom.LoadBitmap(IDB_BANNERBOTTOM);

	m_brush.CreateSolidBrush(RGB(0, 0, 0)); // color black brush 
}

template <class T> BOOL CStageRaceWnd<T>::OnInitDialog()
{
	// Set the icon
	SetIcon( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_DIALOG ) ), TRUE );

	// Get the original dialog size
	RECT Rect;
    GetWindowRect(&Rect);
    // Change the size
    SetWindowPos(NULL, 0, 0, 
                        Rect.right - Rect.left, 
                        Rect.bottom - Rect.top + 25, 
                        SWP_NOMOVE);

    GetClientRect(&Rect);
	// Create a button control in the added area on the bottom
	m_btnHelp.Create( LoadStr(IDS_DIV114), WS_EX_TRANSPARENT|WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(
		Rect.right-55,
		Rect.bottom-20,
		Rect.right-5,
		Rect.bottom-2),
		this,
		ID_SRWND_HELP );
	m_fntBtnHelp.CreateFont( 13, 0, 0, 0, 0, false, false, NULL, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, TEXT("Arial"));
	m_btnHelp.SetFont( &m_fntBtnHelp );

	// Call base class
	T::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

template <class T> BOOL CStageRaceWnd<T>::PreTranslateMessage(MSG *pMsg)
{
	// Organise the dialogs to be dragged by mouse down everywhere
	// on the dialog's window area or that of the border

	// First check if the message is a button click
	if( (pMsg->hwnd==this->m_hWnd) && (pMsg->message == WM_LBUTTONDOWN) )
	{
		// Check if it is actually this dialog's background we clicked on
		CWnd* pWnd = ChildWindowFromPoint( 
				CPoint( LOWORD(pMsg->lParam),HIWORD(pMsg->lParam) ), CWP_SKIPINVISIBLE|CWP_SKIPDISABLED|CWP_SKIPTRANSPARENT );
		if( pWnd==this )
		{
			// Get the window that actually has the caption bar
			// (Necessary to get the sheet for a property page)
			while( !(pWnd->GetStyle()&&WS_CAPTION) ||
				pWnd->IsKindOf(RUNTIME_CLASS(CPropertyPage)) )
				pWnd = GetParent();

			// Post the mouse click to the caption bar
			pWnd->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(LOWORD(pMsg->lParam),LOWORD(pMsg->lParam)));
			return true;
		}
	}

	if( pMsg->message == WM_KEYDOWN )
	{
		// Organise F1 to invoke the help
		if( pMsg->wParam == VK_F1 )
			OnHelp();
		// Make that ESC does not quit the dialog
		if( pMsg->wParam == VK_ESCAPE )
		{
			CSRRegKey reg;
			reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
			if( reg.GetBool( TEXT("ProtectDialogsFromEscape"), false ) )
			{
				MessageBeep( MB_ICONASTERISK );
				return TRUE;
			}
		}
	}

	return T::PreTranslateMessage(pMsg);
}

template <class T> const AFX_MSGMAP* PASCAL CStageRaceWnd<T>::_GetBaseMessageMap()
	{ return &T::messageMap; }
template <class T> const AFX_MSGMAP* CStageRaceWnd<T>::GetMessageMap()
	{ return &messageMap; } 
template <class T> AFX_COMDAT AFX_DATADEF const AFX_MSGMAP CStageRaceWnd<T>::messageMap =
	{ &CStageRaceWnd<T>::_GetBaseMessageMap, CStageRaceWnd<T>::_messageEntries };
template <class T> AFX_COMDAT const AFX_MSGMAP_ENTRY CStageRaceWnd<T>::_messageEntries[] = 
	{
		ON_WM_ERASEBKGND()
		ON_WM_SIZE()
		ON_COMMAND(ID_SRWND_HELP, OnHelp)
		ON_WM_CTLCOLOR()
	};

template <class T> void CStageRaceWnd<T>::OnSize(UINT nType, int cx, int cy)
{
	T::OnSize( nType, cx, cy );

	// Repaint the background
	Invalidate();

	RECT Rect;
    GetClientRect(&Rect);
	// Make sure that the help button moves when resizing
	if( ::IsWindow( m_btnHelp.m_hWnd ) )
		m_btnHelp.SetWindowPos( NULL,
								Rect.right-55,
								Rect.bottom-20,
								NULL,
								NULL,
								SWP_NOSIZE|SWP_NOZORDER );
}

template <class T> void CStageRaceWnd<T>::OnHelp()
{
	CHelp::Topic( m_helptopic );
}

template <class T> HBRUSH CStageRaceWnd<T>::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
	if( (nCtlColor==CTLCOLOR_BTN) && pWnd->m_hWnd==m_btnHelp.m_hWnd )
	{
		// Return the black brush
		// Nicer with new XP controls that do not cover
		// the whole rectangle that is assigned to the
		// button due to round corners
		return m_brush;
		// Note that this does not seem to work when in
		// property pages
	}
	return T::OnCtlColor( pDC,pWnd, nCtlColor );
}

#endif // !defined(AFX_STAGERACEWND_H__8EA058A5_71F7_4399_9AE1_61D9FA1EA759__INCLUDED_)
