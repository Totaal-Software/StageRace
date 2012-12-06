// PresentationViewIDocHostUIWrapper.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPresentationViewIDocHostUIWrapper

CPresentationViewIDocHostUIWrapper::CPresentationViewIDocHostUIWrapper(CPresentationView *pWrappee)
{
	m_pWrappee = pWrappee;
}

HRESULT CPresentationViewIDocHostUIWrapper::ShowContextMenu(unsigned long dwID,struct tagPOINT * ppt,struct IUnknown * pcmdtReserved,struct IDispatch *)
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
										m_pWrappee->GetParentFrame() );
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