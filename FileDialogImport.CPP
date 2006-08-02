// FileDialogImport.cpp: implementation of the CFileDialogImport class.
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileDialogWithImport

BEGIN_MESSAGE_MAP(CFileDialogImport::CMySubClassWnd, CButton)
	{ WM_COMMAND+WM_REFLECT_BASE, (WORD)BN_CLICKED, 0, 0, \
	    AfxSig_vv, (AFX_PMSG)&CFileDialogImport::CMySubClassWnd::OnButtonSuppressPreview },
END_MESSAGE_MAP()

CFileDialogImport::CFileDialogImport(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialogWithMemory(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

BEGIN_MESSAGE_MAP(CFileDialogImport, CFileDialogWithMemory)
	//{{AFX_MSG_MAP(CFileDialogImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFileDialogImport::OnInitDialog()
{
	CFileDialogWithMemory::OnInitDialog();

	// Get a pointer to the original dialog box.
	CWnd *wndDlg = GetParent();
	RECT Rect;
	RECT RectButton;

	// Put our control(s) somewhere below combo box
	wndDlg->GetDlgItem(stc2)->GetWindowRect(&Rect);
	wndDlg->ScreenToClient(&Rect); // Remember it is child controls
	RectButton.left		= Rect.left;

	wndDlg->GetDlgItem(psh16)->GetWindowRect(&Rect);
	wndDlg->ScreenToClient(&Rect); // Remember it is child controls
	RectButton.top		= Rect.top-10;
	RectButton.right	= Rect.left;
	RectButton.bottom	= Rect.bottom+10;

	m_buttonSuppressPreview.Create( LoadStr( IDS_DIV91 ), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX | BS_MULTILINE, RectButton, 
		wndDlg, psh14 );

	m_buttonSuppressPreview.SetCheck( GetSuppressPreview() );

	// Save new control font according to other control fonts
	m_buttonSuppressPreview.SetFont (wndDlg->GetFont(), true);
	m_buttonSuppressPreview.SetFocus();

	return TRUE;
}

void CFileDialogImport::CMySubClassWnd::OnButtonSuppressPreview()
{
	m_suppressPreview = GetCheck()!=0;
}

int CFileDialogImport::DoModal()
{
	CSRRegKey reg;
	reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
	SetSuppressPreview(
		reg.GetBool( TEXT("Suppress preview"), false ) );	

	// Run the modal dialog
	int nRet = CFileDialog::DoModal();

	if( nRet==IDOK )
	{
		CSRRegKey reg;
		HRESULT er = reg.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Import") );
		if( er == ERROR_SUCCESS )
			reg.SetBool( TEXT("Suppress preview"), GetSuppressPreview() );
	}
	return nRet;
}
