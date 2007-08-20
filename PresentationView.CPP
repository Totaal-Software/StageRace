// PresentationView.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPresentationView

IMPLEMENT_DYNCREATE( CPresentationView, CHtmlView )

CPresentationView::CPresentationView()
{
	m_scrollheight = 0;
	m_cLastFile = "";
	//{{AFX_DATA_INIT(CPresentationView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CPresentationView, CHtmlView)
	//{{AFX_MSG_MAP(CPresentationView)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnPageSetup)
	ON_COMMAND(ID_EDIT_FIND, OnFind)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_VIEW_INFO, OnViewInfo)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_COPYSHORTCUT, OnUpdateAnchorItem)
	ON_COMMAND(ID_VIEW_FONT_ZOOMIN, OnViewFontZoomin)
	ON_COMMAND(ID_VIEW_FONT_ZOOMOUT, OnViewFontZoomout)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONT_ZOOMIN, OnUpdateViewFontZoomin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONT_ZOOMOUT, OnUpdateViewFontZoomout)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_OPEN, OnUpdateAnchorItem)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_OPENINNEWWINDOW, OnUpdateAnchorItem)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_PRINTTARGET, OnUpdateAnchorItem)
	ON_COMMAND(ID_NEXT_PANE, OnNextPane)
	ON_COMMAND(ID_PREV_PANE, OnNextPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPresentationView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPresentationView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CPresentationView diagnostics

#ifdef _DEBUG
void CPresentationView::AssertValid() const
{
	CHtmlView::AssertValid();
}
void CPresentationView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPresentationView message handlers

void CPresentationView::OnFind()
{
	::SendMessage(((this->GetWindow(GW_CHILD))->GetWindow(GW_CHILD))->GetWindow(GW_CHILD)->m_hWnd, WM_COMMAND, 0x10043, 0x0);
}

void CPresentationView::OnPageSetup()
{
	ExecWB( OLECMDID_PAGESETUP, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnFilePrintPreview() 
{
	ExecWB( OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

/////////////////////////////////////////////////////////////////////////////
// CPresentationView services

UINT CPresentationView::GetResourceID()
{
	return IDR_PRESENTATIONVIEW;
}

void CPresentationView::Navigate(LPCTSTR URL)
{
	if( m_cLastFile==CString(URL) )
	{
		// This is the existing file being
		// refreshed

		// Only refresh if this is an updated file
		CFileStatus status;
		if( !CFile::GetStatus( m_cLastFile, status ) ||
				(m_tLastFile != status.m_mtime) )
		{
			HRESULT hr;

			// Prepare the scroll extent restore
			CComPtr<IDispatch> pDisp = GetHtmlDocument();
			if( pDisp )
			{
				// get document interface
				CComPtr<IHTMLDocument2> pDocument;
				hr = pDisp->QueryInterface( __uuidof(IHTMLDocument2), (void**)&pDocument );
				if( SUCCEEDED( hr ) && pDocument )
				{
					// take the body element from document...
    				CComPtr<IHTMLElement> pBody;
					hr = pDocument->get_body( &pBody );
					if( SUCCEEDED( hr ) && pBody )
					{
						// from body we can get element2 interface, which allows us to do scrolling
						CComPtr<IHTMLElement2> pElement;
						hr = pBody->QueryInterface(__uuidof(IHTMLElement2),(void**)&pElement);
						if( SUCCEEDED( hr ) && pElement )
						{
							// get the current scroll extent
							pElement->get_scrollTop( &m_scrollheight );
						}
					}
				}
			}

			// Do the actual refresh
			CHtmlView::Navigate2( m_cLastFile, 0, 0, 0, 0 );
		}
	}
	else
	{
		// This is a new file to display
		m_cLastFile = CString( URL );

		CHtmlView::Navigate2( m_cLastFile, 0, 0, 0, 0 );
	}
	// Store the latest write time of this file
	CFileStatus status;
	if( CFile::GetStatus( m_cLastFile, status ) )
		m_tLastFile = status.m_mtime;
}

bool CPresentationView::Navigate(CEventItem* pEI)
{
	if( pEI->IsPublicationAvailableHTML() )
	{
		CPresentationView::Navigate( pEI->ComposeFileNamePathHTML() );	
		return true;
	}
	else
		return false;
}

void CPresentationView::OnViewRefresh() 
{
	CString temp = m_cLastFile;
	m_cLastFile = TEXT(""); // So that the user will actually see the refresh
	CPresentationView::Navigate( temp );
}

void CPresentationView::NavigateLicense()
{
	CHtmlView::LoadFromResource( IDR_LICENSE );
}

void CPresentationView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// Method must exist!
	if( lHint )
	{
		CPresentationView::Navigate( m_cLastFile );
	}
}

void CPresentationView::OnViewInfo() 
{
	// Show the html document's properties
	ExecWB( OLECMDID_PROPERTIES, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnEditCopy() 
{
	ExecWB( OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( QueryStatusWB(OLECMDID_COPY) & OLECMDF_ENABLED );
}

void CPresentationView::OnEditCut() 
{
	ExecWB( OLECMDID_CUT, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( QueryStatusWB(OLECMDID_CUT) & OLECMDF_ENABLED );
}

void CPresentationView::OnEditPaste() 
{
	ExecWB( OLECMDID_PASTE, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( QueryStatusWB(OLECMDID_PASTE) & OLECMDF_ENABLED );
}

void CPresentationView::OnEditSelectall() 
{
	ExecWB( OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL, NULL );
}

void CPresentationView::OnUpdateAnchorItem(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

HRESULT CPresentationView::ShowContextMenu(unsigned long dwID,struct tagPOINT * ppt,struct IUnknown * pcmdtReserved,struct IDispatch *)
{
	#define IDR_BROWSE_CONTEXT_MENU  24641
	#define IDR_FORM_CONTEXT_MENU    24640
	#define SHDVID_GETMIMECSETMENU   27
	#define SHDVID_ADDMENUEXTENSIONS 53

	// Load the menu
	CMenu aMenu;
	aMenu.LoadMenu( IDR_CONTEXTPRESENTATION );

	// Choose one of the sub menus
	CMenu* pChosenMenu;

	switch( dwID )
	{
		case CONTEXT_MENU_ANCHOR:
			pChosenMenu = aMenu.GetSubMenu(1);
			pChosenMenu->SetDefaultItem( ID_ANCHOR_OPEN );
			break;
		case CONTEXT_MENU_TEXTSELECT:
			pChosenMenu = aMenu.GetSubMenu(2);
			break;
		case CONTEXT_MENU_DEFAULT:
		default:
			pChosenMenu = aMenu.GetSubMenu(0);
	}
	BOOL result;
	if( pChosenMenu )
	{
		// Show the menu
		result = pChosenMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
										ppt->x+2,
										ppt->y+2,
										GetParentFrame() );
		switch( result )
		{
			case ID_ANCHOR_OPEN:
			case ID_ANCHOR_OPENINNEWWINDOW:
			case ID_ANCHOR_PRINTTARGET:
			case ID_ANCHOR_COPYSHORTCUT:
			{
				CComPtr<IOleWindow> spWnd;

				HRESULT hr;
				hr = pcmdtReserved->QueryInterface(IID_IOleWindow, (void**)&spWnd);
				if( hr == ERROR_SUCCESS )
				{
					HWND hwnd;
					hr = spWnd->GetWindow(&hwnd);
					if( hr == ERROR_SUCCESS )
					{
						switch( result )
						{
							case ID_ANCHOR_OPEN:
								::SendMessage(hwnd, WM_COMMAND, IDM_FOLLOWLINKC, NULL);
								break;
							case ID_ANCHOR_OPENINNEWWINDOW:
								::SendMessage(hwnd, WM_COMMAND, IDM_FOLLOWLINKN, NULL);
								break;
							case ID_ANCHOR_PRINTTARGET:
								::SendMessage(hwnd, WM_COMMAND, IDM_PRINTTARGET, NULL);
								break;
							case ID_ANCHOR_COPYSHORTCUT:
								::SendMessage(hwnd, WM_COMMAND, IDM_COPYSHORTCUT, NULL);
								break;
						}
					}
				}
			}
			break;
			default:
				::SendMessage(
					AfxGetMainWnd()->m_hWnd,
					WM_COMMAND, result, NULL);
		}
	}
	return S_OK;
}

//DEL HRESULT CPresentationView::OnGetOptionKeyPath(LPOLESTR * pchKey, DWORD)
//DEL {
//DEL 	if( !pchKey )
//DEL 		return E_INVALIDARG;
//DEL 
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	OLECHAR * pchKeyPath = T2OLE( _T("Software\\Totaal Software\\StageRace\\Presentation View") );
//DEL 
//DEL 	*pchKey = reinterpret_cast< LPOLESTR >
//DEL 		(::CoTaskMemAlloc( (::wcslen( pchKeyPath ) + 1) * sizeof(OLECHAR) ));
//DEL 
//DEL 	if (*pchKey)
//DEL 	{
//DEL 		::wcscpy( *pchKey, pchKeyPath );
//DEL 		return S_OK;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		return E_OUTOFMEMORY;
//DEL 	}
//DEL }

//DEL HRESULT CPresentationView::OnGetOverrideKeyPath(LPOLESTR * pchKey, DWORD)
//DEL {
//DEL 	if( !pchKey )
//DEL 		return E_INVALIDARG;
//DEL 
//DEL 	USES_CONVERSION;
//DEL 
//DEL 	OLECHAR * pchKeyPath = T2OLE( _T("Software\\Totaal Software\\StageRace\\Presentation View") );
//DEL 
//DEL 	*pchKey = reinterpret_cast< LPOLESTR >
//DEL 		(::CoTaskMemAlloc( (::wcslen( pchKeyPath ) + 1) * sizeof(OLECHAR) ));
//DEL 
//DEL 	if (*pchKey)
//DEL 	{
//DEL 		::wcscpy( *pchKey, pchKeyPath );
//DEL 		return S_OK;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		return E_OUTOFMEMORY;
//DEL 	}
//DEL }

void CPresentationView::OnNavigateComplete2(LPCTSTR strURL) 
{
	CHtmlView::OnNavigateComplete2(strURL);
	CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> i_doc2(GetHtmlDocument());
	if( i_doc2.p )
	{
		CComQIPtr<ICustomDoc, &IID_ICustomDoc> i_doc(i_doc2);
		if( i_doc.p )
		{
			VERIFY( i_doc->SetUIHandler( this ) == S_OK );
		}
	}
}

void CPresentationView::OnViewFontZoomin() 
{
	Zoom();
}

void CPresentationView::OnViewFontZoomout() 
{
	Zoom(false);
}

void CPresentationView::Zoom(bool in)
{
	LPDISPATCH pDisp = NULL;
	LPOLECOMMANDTARGET pCmdTarg = NULL;

	HRESULT hr;

	pDisp = GetHtmlDocument();
	ASSERT(pDisp);

	hr = pDisp->QueryInterface(IID_IOleCommandTarget, (LPVOID*)&pCmdTarg);
	ASSERT(pCmdTarg);

	VARIANT vaZoomRange;
	hr = pCmdTarg->Exec(NULL,
		OLECMDID_GETZOOMRANGE ,
		OLECMDEXECOPT_DONTPROMPTUSER,
		NULL,
		&vaZoomRange);

	VARIANT vaZoomFactor;
	hr = pCmdTarg->Exec(NULL,
		OLECMDID_ZOOM,
		OLECMDEXECOPT_DONTPROMPTUSER,
		NULL,
		&vaZoomFactor);

	if( in )
	{
		if( vaZoomFactor.lVal < HIWORD(vaZoomRange.lVal) )
			vaZoomFactor.lVal++;
	}
	else
	{
		if( vaZoomFactor.lVal > LOWORD(vaZoomRange.lVal) )
			vaZoomFactor.lVal--;
	}

	hr = pCmdTarg->Exec(NULL,
		OLECMDID_ZOOM,
		OLECMDEXECOPT_DONTPROMPTUSER,
		&vaZoomFactor,
		NULL);
	
	VariantClear(&vaZoomFactor);
	VariantClear(&vaZoomRange);

	if (pCmdTarg)
		pCmdTarg->Release(); // release document's command target
	if (pDisp)
		pDisp->Release();    // release document's dispatch interface
}

bool CPresentationView::CanZoom(bool in)
{
	LPDISPATCH pDisp = NULL;
	LPOLECOMMANDTARGET pCmdTarg = NULL;

	HRESULT hr;

	pDisp = GetHtmlDocument();
	ASSERT(pDisp);

	hr = pDisp->QueryInterface(IID_IOleCommandTarget, (LPVOID*)&pCmdTarg);
	ASSERT(pCmdTarg);

	VARIANT vaZoomRange;
	hr = pCmdTarg->Exec(NULL,
		OLECMDID_GETZOOMRANGE ,
		OLECMDEXECOPT_DONTPROMPTUSER,
		NULL,
		&vaZoomRange);

	VARIANT vaZoomFactor;
	hr = pCmdTarg->Exec(NULL,
		OLECMDID_ZOOM,
		OLECMDEXECOPT_DONTPROMPTUSER,
		NULL,
		&vaZoomFactor);

	bool ret = false;
	if( in )
	{
		if( vaZoomFactor.lVal < HIWORD(vaZoomRange.lVal) )
			ret = true;
	}
	else
	{
		if( vaZoomFactor.lVal > LOWORD(vaZoomRange.lVal) )
			ret = true;
	}

	VariantClear(&vaZoomFactor);
	VariantClear(&vaZoomRange);

	if (pCmdTarg)
		pCmdTarg->Release(); // release document's command target
	if (pDisp)
		pDisp->Release();    // release document's dispatch interface

	return ret;
}

void CPresentationView::OnUpdateViewFontZoomin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CanZoom() );
}

void CPresentationView::OnUpdateViewFontZoomout(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( CanZoom(false) );	
}

void CPresentationView::OnDocumentComplete(LPCTSTR lpszURL) 
{/*
	if( m_scrollheight )
	{
		HRESULT hr;

		CComPtr<IDispatch> pDisp = GetHtmlDocument();
		if( pDisp )
		{
			// get document interface
			CComPtr<IHTMLDocument2> pDocument;
			hr = pDisp->QueryInterface( __uuidof(IHTMLDocument2), (void**)&pDocument );
			if( SUCCEEDED( hr ) && pDocument )
			{
				// take the body element from document...
    			CComPtr<IHTMLElement> pBody;
				hr = pDocument->get_body( &pBody );
				if( SUCCEEDED( hr ) && pBody )
				{
					// from body we can get element2 interface, which allows us to do scrolling
					CComPtr<IHTMLElement2> pElement;
					hr = pBody->QueryInterface(__uuidof(IHTMLElement2),(void**)&pElement);
					if( SUCCEEDED( hr ) && pElement )
					{
						// get the current scroll extent
						hr = pElement->put_scrollTop( m_scrollheight );
					}
				}
			}
		}
		m_scrollheight = 0;
	}*/
	CHtmlView::OnDocumentComplete(lpszURL);
}

BOOL CPresentationView::OnEraseBkgnd(CDC* pDC) 
{
	// This is absolutely necessary for the
	// scrolling to work
	return FALSE;
	//return CHtmlView::OnEraseBkgnd(pDC);
}



void CPresentationView::OnNextPane() 
{
	// Delicate business beyond this point
	// We order the split frame that somewhere is
	//  the parent of this class to switch the active pane
	((CChildFrame*)
		((CSplitterWnd*)GetParent())
			->GetParent())
				->SetActivePaneTreeViewMain();
}
