// ToolBarWithProfilePicker.cpp: implementation of the CToolBarWithProfilePicker class.
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

CToolBarWithProfilePicker::CToolBarWithProfilePicker()
{
	m_pDocument = NULL;
}

CToolBarWithProfilePicker::~CToolBarWithProfilePicker()
{

}

BEGIN_MESSAGE_MAP(CToolBarWithProfilePicker, CToolBar)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(ID_CONFIGURE_PROFILEPICKER_TOOLBAR, OnSelchange)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CToolBarWithProfilePicker::OnShowWindow(BOOL, UINT)
{
	int index;
	CRect rect;
	// first get the index of the placeholder's position in the toolbar
	index = CommandToIndex(ID_CONFIGURE_PROFILEPICKER_TOOLBAR);

	// next convert that button to a seperator and get its position
	SetButtonInfo(index, ID_CONFIGURE_PROFILEPICKER_TOOLBAR, TBBS_SEPARATOR, 125);
	
	// expand the rectangle to allow the combo box room to drop down
	GetItemRect(index, &rect);
	rect.top+=2;
	rect.bottom += 125;
 
	// then create the combo box and show it
	if(!m_profilepicker.Create(WS_CHILD|WS_VISIBLE|CBS_AUTOHSCROLL| 
									   CBS_DROPDOWNLIST|CBS_HASSTRINGS ,
									   rect, this, ID_CONFIGURE_PROFILEPICKER_TOOLBAR))
	{
		TRACE0("Failed to create listbox\n");
	}
	else
	{
		/*
		LOGFONT lf;
		GetFont()->GetLogFont( &lf );
		lf.lfHeight += 1;
		m_font.CreateFontIndirect( &lf );
		m_profilepicker.SetFont( &m_font );
		*/
		m_profilepicker.SetFont( GetFont() );
		m_profilepicker.SetItemHeight( -1, 13 );
		// 13 is the height (15) from our own toolbar resources minus 2 for nice fit
		
		m_profilepicker.ShowWindow(SW_SHOW);

		ResetDoc();
	}
}

void CToolBarWithProfilePicker::SetMainFrame(CMDIFrameWnd *p)
{
	ASSERT(p);
	m_pMainFrame = p;
}

void CToolBarWithProfilePicker::SetDoc(CStageRaceDoc * pDoc)
{
	m_pDocument = pDoc;
	if( m_pDocument )
	{
		m_profilepicker.ResetContent();
		for( int i=0; i<pDoc->m_allsettings.ProfilesGetCount(); i++ )
			m_profilepicker.AddString( pDoc->m_allsettings.ProfilesGetName(i) );
		m_profilepicker.SetCurSel( pDoc->m_allsettings.ProfilesGetCurrent() );
		m_profilepicker.EnableWindow( pDoc->m_allsettings.ProfilesGetCount()>1 );
	}
	else
		ResetDoc();
}

void CToolBarWithProfilePicker::ResetDoc()
{
	m_profilepicker.ResetContent();
	m_profilepicker.AddString( LoadStr( IDS_DIV93 ) );
	m_profilepicker.SetCurSel(0);
	m_profilepicker.EnableWindow(FALSE);
}

void CToolBarWithProfilePicker::OnSelchange()
{
	if( m_pDocument )
	{
		if( m_pDocument->m_allsettings.ProfilesGetCurrent()
			!= m_profilepicker.GetCurSel() )
		{
			m_pDocument->m_allsettings.ProfilesSetCurrent(
				m_profilepicker.GetCurSel() );
			
			// Set the document's modified flag
			m_pDocument->SetModifiedFlag();

			// Update all the views
			m_pDocument->UpdateAllViews( NULL, TI_SETTINGS, NULL );
		}
	}
}

HBRUSH CToolBarWithProfilePicker::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CToolBar::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_LISTBOX)
	{
		int nListWidth = 300;
		CRect rect;
		// New width of a listbox is defined
		pWnd->GetWindowRect(&rect);
		if (rect.Width() != nListWidth)
		{
			rect.right = rect.left + nListWidth;
			pWnd->MoveWindow(&rect);
		}
	}
	return hbr;
}

void CToolBarWithProfilePicker::RedrawDoc()
{
	SetDoc(m_pDocument);
}
