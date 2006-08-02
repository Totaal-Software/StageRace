// FileDialogWithMemory.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDialogWithMemory

BEGIN_MESSAGE_MAP(CFileDialogWithMemory::CMySubClassWnd, CButton)
	{ WM_COMMAND+WM_REFLECT_BASE, (WORD)BN_CLICKED, 0, 0, \
		AfxSig_vv, (AFX_PMSG)&CFileDialogWithMemory::CMySubClassWnd::OnButtonWorkDir },
END_MESSAGE_MAP()

CFileDialogWithMemory::CFileDialogWithMemory(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

BEGIN_MESSAGE_MAP(CFileDialogWithMemory, CFileDialog)
	//{{AFX_MSG_MAP(CFileDialogWithMemory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CFileDialogWithMemory::DoModal()
{
	// Give this dialog its own previous folder
	CString s = AfxGetApp()->GetProfileString( TEXT("File dialogs"), m_ofn.lpstrTitle );
	m_ofn.lpstrInitialDir = s;

	// Run the modal dialog
	int nRet = CFileDialog::DoModal();

	if( nRet==IDOK )
	{
		// Store the folder
		CString s = m_ofn.lpstrFile;
		s = s.Left( s.GetLength() - CString(m_ofn.lpstrFileTitle).GetLength() );
		AfxGetApp()->WriteProfileString( TEXT("File dialogs"), m_ofn.lpstrTitle, s );
	}
	return nRet;
}

BOOL CFileDialogWithMemory::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	// Get a pointer to the original dialog box.
	CWnd *wndDlg = GetParent();
	RECT Rect;

	// Change the size of FileOpen dialoog
	wndDlg->GetWindowRect(&Rect);
	wndDlg->SetWindowPos (NULL, 0, 0,
							Rect.right - Rect.left, 
							Rect.bottom - Rect.top,
							SWP_NOMOVE);

	// Get the dimensions of a combo box as a reference
	// for positioning our button
	wndDlg->GetDlgItem(cmb1)->GetWindowRect(&Rect);
	wndDlg->ScreenToClient(&Rect); // Remember it is child controls

	// Put our control(s) somewhere below combo box
	Rect.top += 30;
	Rect.bottom += 30;

	m_buttonWorkDir.Create( LoadStr( IDS_DIV79 ), WS_CHILD | WS_VISIBLE | WS_TABSTOP, Rect, 
		wndDlg, psh16 );

	// Save new control font according to other control fonts
	m_buttonWorkDir.SetFont (wndDlg->GetFont(), true);
	m_buttonWorkDir.SetFocus();

	// Resize some existing buttons for niceness
	wndDlg->GetDlgItem(IDOK)->GetWindowRect(&Rect);
	wndDlg->ScreenToClient(&Rect); // Remember it is child controls
	wndDlg->GetDlgItem(IDOK)->
		SetWindowPos (NULL, Rect.left, Rect.top,
							Rect.right - Rect.left, 
							Rect.bottom - Rect.top + 15,
							SWP_NOZORDER);
		
	wndDlg->GetDlgItem(IDCANCEL)->GetWindowRect(&Rect);
	wndDlg->ScreenToClient(&Rect); // Remember it is child controls
	wndDlg->GetDlgItem(IDCANCEL)->
		SetWindowPos (NULL, Rect.left, Rect.top + 15,
							Rect.right - Rect.left, 
							Rect.bottom - Rect.top + 15,
							SWP_NOZORDER);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFileDialogWithMemory::CMySubClassWnd::OnButtonWorkDir()
{
	HRESULT hr;
	// Get a pointer to the Desktop's IShellFolder interface
	LPSHELLFOLDER pDesktopFolder;
	hr = SHGetDesktopFolder(&pDesktopFolder);
	if(SUCCEEDED(hr))
	{
		LONG er;
		CSRRegKey reg;
		er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
		if( er == ERROR_SUCCESS )
		{
			// Get the path to the file we need to convert.
			CString cPath = reg.GetString( TEXT("Work directory"), TEXT("") );

			// Convert the path to an ITEMIDLIST
			// pidl will contain a pointer to an ITEMIDLIST for our file
			LPITEMIDLIST pidl;
			ULONG chEaten;
			ULONG dwAttributes;
			hr = pDesktopFolder->ParseDisplayName(NULL,
							NULL,
							cPath.AllocSysString(),
							&chEaten,
							&pidl,
							&dwAttributes);

			if(SUCCEEDED(hr))
			{
				// Get a pointer to the browser that we see
				IShellBrowser* pShBrowser =
				(IShellBrowser*)::SendMessage( GetParent()->m_hWnd,
							/*WM_GETISHELLBROWSER*/ WM_USER+7, 0, 0 );

				if( pShBrowser )
					// Browse to the desired directory
					pShBrowser->BrowseObject( pidl, SBSP_SAMEBROWSER );

				// This ITEMIDLIST needs to be freed using the IMalloc allocator
				// returned from SHGetMalloc()
				pDesktopFolder->Release();
			}
		}
	}
}

void CFileDialogWithMemory::PreInitDialog()
{
    m_dlgOuter.SubclassWindow(
        ::GetParent(m_hWnd));
}
