// HelpTool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HelpTool.h"
#include "HelpToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpToolApp

BEGIN_MESSAGE_MAP(CHelpToolApp, CWinApp)
	//{{AFX_MSG_MAP(CHelpToolApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpToolApp construction

CHelpToolApp::CHelpToolApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHelpToolApp object

void Report(CString str)
{
	int n = ((CHelpToolDlg*)AfxGetMainWnd())->m_reporting.AddString(str);
	((CHelpToolDlg*)AfxGetMainWnd())->m_reporting.SetTopIndex( n );
}

CHelpToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHelpToolApp initialization

BOOL CHelpToolApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CHelpToolDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
