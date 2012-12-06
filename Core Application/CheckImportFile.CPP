// CheckImportFile.cpp : implementation file
//

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckImportFile dialog


CCheckImportFile::CCheckImportFile(CString cFileName)
	: CStageRaceWnd<CDialog>(CHelp::HLP_DLG_IMPORT_CHECK, CCheckImportFile::IDD)
{
	//{{AFX_DATA_INIT(CCheckImportFile)
	m_cFileName = _T("");
	//}}AFX_DATA_INIT
	m_cFileName = cFileName;
}


void CCheckImportFile::DoDataExchange(CDataExchange* pDX)
{
	CStageRaceWnd<CDialog>::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckImportFile)
	DDX_Text(pDX, IDC_FILENAME, m_cFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckImportFile, CStageRaceWnd<CDialog>)
	//{{AFX_MSG_MAP(CCheckImportFile)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckImportFile message handlers

BOOL CCheckImportFile::OnInitDialog() 
{
	CStageRaceWnd<CDialog>::OnInitDialog();

	// Get the file time to start off with
	CFileFind objCheckFile;
	objCheckFile.FindFile( m_cFileName );
	objCheckFile.FindNextFile();
	objCheckFile.GetLastWriteTime( m_fileTime );

	// Set the timer so that our clock will work
	OnTimer( 1 );
	SetTimer( 1, 1000, NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckImportFile::OnTimer(UINT nIDEvent) 
{
	// React on the timer
	if( nIDEvent == 1 )
	{
		// Get the file time to compare it
		CFileFind objCheckFile;
		objCheckFile.FindFile( m_cFileName );
		objCheckFile.FindNextFile();

		CTime objTime;
		objCheckFile.GetLastWriteTime( objTime );

		// Compare it to the time from the start
		if( m_fileTime!=objTime )
			// If the file time changed, see what to do
			if( IsDlgButtonChecked(IDC_CHECKIMPORTFILEPROCEED) )
				// Proceed
				OnOK();
			else
				// Just update the start time in case someone checks
				// the 'Proceed on change of file time' later
				m_fileTime=objTime;

		// Print the file time
		((CWnd*)GetDlgItem(IDC_FILETIME))->SetWindowText( objTime.Format( "%Hh %M' %S\"   (%A %d %B %Y)" ) );


		// Print the current time
		objTime = CTime::GetCurrentTime();
		((CWnd*)GetDlgItem(IDC_SYSTEMTIME))->SetWindowText( objTime.Format( "%Hh %M' %S\"   (%A %d %B %Y)" ) );
	}
}

void CCheckImportFile::OnOK() 
{
	// Stop the timer
	KillTimer( 1 );

	CStageRaceWnd<CDialog>::OnOK();
}

void CCheckImportFile::OnCancel() 
{
	// Stop the timer
	KillTimer( 1 );
	
	CStageRaceWnd<CDialog>::OnCancel();
}

