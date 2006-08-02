// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_OPTIONS, COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	//}}AFX_DATA_INIT
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_BN_CLICKED(IDC_BROWSEOMEGA, OnBrowseomega)
	ON_BN_CLICKED(IDC_BROWSEAMB, OnBrowseamb)
	ON_BN_CLICKED(IDC_BROWSEALGE, OnBrowsealge)
	ON_BN_CLICKED(IDC_BROWSELYNX, OnBrowselynx)
	ON_BN_CLICKED(IDC_BROWSEWORK, OnBrowsework)
	ON_BN_CLICKED(IDC_BROWSEEDITOR, OnBrowseeditor)
	ON_BN_CLICKED(IDC_BROWSESKUNKWARE, OnBrowseskunkware)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

void COptionsDlg::OnOK() 
{
	LONG er;
	CString cPath;

	// Various
	CSRRegKey reg1;
	er = reg1.Create( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );

	if( er == ERROR_SUCCESS )
	{
//		reg1.SetDWord( TEXT("HelpLanguage", ((CButton*)GetDlgItem(IDC_OPTIONS_HELP_DUTCH))->GetCheck() );
		reg1.SetDWord( TEXT("HideFunctionsForSprints"), ((CButton*)GetDlgItem(IDC_OPTIONS_HIDEFUNCTIONSFORSPRINTS))->GetCheck() );
		reg1.SetDWord( TEXT("SuppressHardwareKeyCheck"), ((CButton*)GetDlgItem(IDC_OPTIONS_SUPPRESSHWKCHECK))->GetCheck() );
		reg1.SetDWord( TEXT("ShowImportFileCheckDialog"), ((CButton*)GetDlgItem(IDC_OPTIONS_IMPORTCHECKDIALOG))->GetCheck() );
		reg1.SetDWord( TEXT("UseCtrlForCompetitorPaste"), ((CButton*)GetDlgItem(IDC_OPTIONS_USECONTROLFORCOMPETITORPASTE))->GetCheck() );
		reg1.SetDWord( TEXT("UseInsDelForArrivals"), ((CButton*)GetDlgItem(IDC_OPTIONS_USEINSDELFORARRIVALS))->GetCheck() );
		reg1.SetDWord( TEXT("ProtectDialogsFromEscape"), ((CButton*)GetDlgItem(IDC_OPTIONS_PROTECTDIALOGSFROMESCAPE))->GetCheck() );
		reg1.SetDWord( TEXT("IndicateMissingLanguageStrings"), ((CButton*)GetDlgItem(IDC_OPTIONS_INDICATEMISSINGLANGUAGESTRINGS))->GetCheck() );
		GetDlgItemText( IDC_OPTIONS_PATH_WORK, cPath );
		reg1.SetString( TEXT("Work directory"), cPath );
		GetDlgItemText( IDC_OPTIONS_PATH_EDITOR, cPath );
		reg1.SetString( TEXT("Publication editor"), cPath );
	}

	// Export folders paths
	CSRRegKey reg2;
	er = reg2.Create( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );

	if( er == ERROR_SUCCESS )
	{
		GetDlgItemText( IDC_OPTIONS_PATH_AMB, cPath );
		reg2.SetString( TEXT("AMB ChronX"), cPath );
		GetDlgItemText( IDC_OPTIONS_PATH_ALGE, cPath );
		reg2.SetString( TEXT("Alge OPTIc"), cPath );
		GetDlgItemText( IDC_OPTIONS_PATH_OMEGA, cPath );
		reg2.SetString( TEXT("Omega Scan'O'Vision"), cPath );
		GetDlgItemText( IDC_OPTIONS_PATH_LYNX, cPath );
		reg2.SetString( TEXT("Lynx FinishLynx"), cPath );
		GetDlgItemText( IDC_OPTIONS_PATH_SKUNKWARE, cPath );
		reg2.SetString( TEXT("Skunkware TT*Ware"), cPath );
	}
	
	// This one stores an IE Options Advanced setting in the registry
	if( IsDlgButtonChecked(IDC_OPTIONS_PRINTBACKGROUND)!=2 )
	{
		CSRRegKey reg3;
		er = reg3.Create( HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Internet Explorer\\Main") );

		if( er == ERROR_SUCCESS )
		{
			reg3.SetString( TEXT("Print_Background"), (IsDlgButtonChecked(IDC_OPTIONS_PRINTBACKGROUND)==0)?TEXT("no"):TEXT("yes") );
		}
	}

	CStageRaceWnd<CDialog>::OnOK();
}

BOOL COptionsDlg::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();

	// Various
	CSRRegKey reg1;
	reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );

	// This one handles the help
/*	int bCode = 0;
	bCode = reg1.GetDWord( TEXT("HelpLanguage"), 0 );
	switch(bCode)
	{
		case 1:
			((CButton*)GetDlgItem(IDC_OPTIONS_HELP_DUTCH))->SetCheck(1);
			break;
		default:
			((CButton*)GetDlgItem(IDC_OPTIONS_HELP_ENGLISH))->SetCheck(1);
	}
*/
	// This one handles the suppression of the functions menu
	((CButton*)GetDlgItem(IDC_OPTIONS_HIDEFUNCTIONSFORSPRINTS))->
		SetCheck( reg1.GetBool(TEXT("HideFunctionsForSprints"),false) );

	// This one handles the suppression of the hardware key check
	((CButton*)GetDlgItem(IDC_OPTIONS_SUPPRESSHWKCHECK))->
		SetCheck( reg1.GetBool(TEXT("SuppressHardwareKeyCheck"),false) );

	// This one handles the import file check dialog show/don't-show
	((CButton*)GetDlgItem(IDC_OPTIONS_IMPORTCHECKDIALOG))->
		SetCheck( reg1.GetBool(TEXT("ShowImportFileCheckDialog"),true) );

	// This one handles the print indication for missing language strings
	((CButton*)GetDlgItem(IDC_OPTIONS_INDICATEMISSINGLANGUAGESTRINGS))->
		SetCheck( reg1.GetBool(TEXT("IndicateMissingLanguageStrings"),true) );

	// This one handles the ctrl key for pasting with start nos.
	((CButton*)GetDlgItem(IDC_OPTIONS_USECONTROLFORCOMPETITORPASTE))->
		SetCheck( reg1.GetBool(TEXT("UseCtrlForCompetitorPaste"),true) );

	// This one handles the ins/del key for arrival dialogs
	((CButton*)GetDlgItem(IDC_OPTIONS_USEINSDELFORARRIVALS))->
		SetCheck( reg1.GetBool(TEXT("UseInsDelForArrivals"),false) );

	// This one handles the protection against incidently exiting dialogs
	((CButton*)GetDlgItem(IDC_OPTIONS_PROTECTDIALOGSFROMESCAPE))->
		SetCheck( reg1.GetBool(TEXT("ProtectDialogsFromEscape"),false) );

	// This one handles the work directory for StageRace events
	SetDlgItemText( IDC_OPTIONS_PATH_WORK, reg1.GetString( TEXT("Work directory"), TEXT("") ) );

	// This one handles the publication editor
	// Set up a path for Notepad that we use as default application
	TCHAR lpBuffer[MAX_PATH];
	GetWindowsDirectory( lpBuffer, MAX_PATH );
	CString cBuffer = CString(lpBuffer);
	if( cBuffer.Right(1)!="\\" ) cBuffer+="\\";
	cBuffer+="notepad.exe";
	SetDlgItemText( IDC_OPTIONS_PATH_EDITOR, reg1.GetString( TEXT("Publication editor"), cBuffer ) );

	// Export folders paths
	CSRRegKey reg2;
	reg2.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software\\StageRace\\Export paths") );

	SetDlgItemText( IDC_OPTIONS_PATH_OMEGA, reg2.GetString( TEXT("Omega Scan'O'Vision"), TEXT("") ) );
	SetDlgItemText( IDC_OPTIONS_PATH_AMB, reg2.GetString( TEXT("AMB ChronX"), TEXT("") ) );
	SetDlgItemText( IDC_OPTIONS_PATH_ALGE, reg2.GetString( TEXT("Alge OPTIc"), TEXT("") ) );
	SetDlgItemText( IDC_OPTIONS_PATH_LYNX, reg2.GetString( TEXT("Lynx FinishLynx"), TEXT("") ) );
	SetDlgItemText( IDC_OPTIONS_PATH_SKUNKWARE, reg2.GetString( TEXT("Skunkware TT*Ware"), TEXT("") ) );

	// This one retrieves an IE Options Advanced setting from the registry
	CSRRegKey reg3;
	LONG er;

	er = reg3.Open( HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Internet Explorer\\Main") );
	if( er == ERROR_SUCCESS )
	{
		CString csValue;
		csValue = reg3.GetString( TEXT("Print_Background"), TEXT("unknown") );

		if( csValue==TEXT("unknown") )
			CheckDlgButton( IDC_OPTIONS_PRINTBACKGROUND, 2 );
		else if( csValue==TEXT("yes") )
			CheckDlgButton( IDC_OPTIONS_PRINTBACKGROUND, 1 );
		else
			CheckDlgButton( IDC_OPTIONS_PRINTBACKGROUND, 0 );
	}
	else
		CheckDlgButton( IDC_OPTIONS_PRINTBACKGROUND, 2 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::OnBrowsework() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_WORK ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_WORK ))->SetWindowText( GetFolder( "Work directory (*.str)", cCurrent ) );
}

void COptionsDlg::OnBrowseomega() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_OMEGA ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_OMEGA ))->SetWindowText( GetFolder( "Omega Scan'O'Vision", cCurrent ) );
}

void COptionsDlg::OnBrowseamb() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_AMB ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_AMB ))->SetWindowText( GetFolder( "AMB ChronX", cCurrent ) );
}

void COptionsDlg::OnBrowsealge() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_ALGE ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_ALGE ))->SetWindowText( GetFolder( "AMB ChronX", cCurrent ) );
}

void COptionsDlg::OnBrowselynx() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_LYNX ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_LYNX ))->SetWindowText( GetFolder( "Lynx FinishLynx", cCurrent ) );
}

void COptionsDlg::OnBrowseskunkware() 
{
	CString cCurrent;
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_SKUNKWARE ))->GetWindowText( cCurrent );
	((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_SKUNKWARE ))->SetWindowText( GetFolder( "Skunkware TT*Ware", cCurrent ) );
}

CString COptionsDlg::GetFolder(CString cCaption, CString cCurrent)
{
	BROWSEINFO lpbi;

	lpbi.hwndOwner = this->m_hWnd;
	lpbi.pidlRoot = NULL;
	
	TCHAR szDisplayName[MAX_PATH];
	lpbi.pszDisplayName = szDisplayName;
	
	CString cHeader = LoadStr( IDS_DIV54 )+cCaption;
	lpbi.lpszTitle = cHeader;
    
	lpbi.ulFlags = BIF_EDITBOX|BIF_RETURNONLYFSDIRS|BIF_RETURNONLYFSDIRS|BIF_RETURNFSANCESTORS ;
	lpbi.lpfn = NULL;

	LPITEMIDLIST pSelectedItem;
	pSelectedItem = SHBrowseForFolder( &lpbi );

	TCHAR czSelectedItem[MAX_PATH];
	if( SHGetPathFromIDList( pSelectedItem, czSelectedItem ) )
		return CString(czSelectedItem);
	else
		return cCurrent;
}

void COptionsDlg::OnBrowseeditor() 
{
	// Set up the open dialog box
	CFileDialogWithMemory aFileDlg( TRUE, TEXT("*.exe") );
	aFileDlg.m_ofn.lpstrFilter = TEXT("Executable files (*.exe; *.bat; *.com)\0*.exe;*.bat;*.com\0All files (*.*)\0*.*\0\0");
	CString czBoxTitle = LoadStr( IDS_DIV81 );
	aFileDlg.m_ofn.lpstrDefExt = NULL;
	aFileDlg.m_ofn.lpstrTitle = czBoxTitle;
	if( aFileDlg.DoModal()==IDOK )
	{
		((CWnd*)GetDlgItem( IDC_OPTIONS_PATH_EDITOR ))->SetWindowText( aFileDlg.GetPathName() );
	}
}
