///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: Stage.cpp
// Description: Implementation file for the application
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
// 06-01-2000	SV	Alle variabelenamen aangepast volgens nieuwe conventie
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"
#include "versionno.h"
#include <initguid.h>
#include "StageRace_i.c"
#include "StageRaceServer (COM).h"
#include "StageRaceDoc (COM).h"
#include "SRHalfStage (COM).h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRaceApp

BEGIN_MESSAGE_MAP(CStageRaceApp, CWinApp)
	//{{AFX_MSG_MAP(CStageRaceApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_LISTVIEWACTIVEDOC, OnViewListviewactivedoc)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LISTVIEWACTIVEDOC, OnUpdateViewListviewactivedoc)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_THREAD_MESSAGE(WM_USER_COM_OPERATORMESSAGE, ShowOperatorMessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStageRaceApp construction

CStageRaceApp::CStageRaceApp()
{
	m_pActiveDocTracker = NULL;
	m_pMultiLang = NULL;
	// Place all significant initialization in InitInstance
}

CStageRaceApp::~CStageRaceApp()
{
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CStageRaceApp initialization

BOOL CStageRaceApp::InitInstance()
{
	if( AUTOINCREMENTEDVERSIONNO !=
		_ttoi( m_key.GetVersionTitle() )*100*10 +
		_ttoi( m_key.GetVersionNo() )*100 +
		_ttoi( m_key.GetReleaseNo() ) ) *(int*)0=0;

	if( !CheckExe() ) *(int*)0=0;

	if( CString("-Embedding").Compare(m_lpCmdLine)==0 )
	{
#ifdef _DEBUG
		AfxMessageBox(TEXT("Embedding not allowed"));
#endif
		// We don't want clients to start the server! Grr!
		return FALSE;
	}
	if( CString("unreg").CompareNoCase(m_lpCmdLine)==0 )
	{
		InitATL();
		UnregisterShellFileTypes();
		return FALSE;
	}
	else
	{
		// Standard initialization
		// If you are not using these features and wish to reduce the size
		//  of your final executable, you should remove from the following
		//  the specific initialization routines you do not need.

	#ifdef _DEBUG
		Language();
	#endif // _DEBUG

	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif

		// Create start info screen
		m_startScreen.Create( IDD_STARTSCREEN );

		// Progress indicator
		m_startScreen.m_progress.SetPos( 12 );

			// Set the correct registry key
			SetRegistryKey( TEXT("Totaal Software") );
			// Load standard INI file options (including MRU)
			LoadStdProfileSettings(5);

			// Make sure we have a document manager that handles our own file dialogs
			m_pDocManager = new CDocManagerEx;
			// Register the application's document templates. Document templates
			//  serve as the connection between documents, frame windows and views
			CMultiDocTemplate* pDocTemplate;
			pDocTemplate = new CMultiDocTemplate(
				IDR_STAGERACEDOC,
				RUNTIME_CLASS(CStageRaceDoc),
				RUNTIME_CLASS(CChildFrame),
				RUNTIME_CLASS(CTreeViewMain));
			AddDocTemplate(pDocTemplate);

			// Make a document for tracking open StageRace document
			pDocTemplate = new CMultiDocTemplate(
				IDR_ACTIVEDOCTRACKER,
				RUNTIME_CLASS(CActiveDocTracker),
				RUNTIME_CLASS(CChildFrameExclusive),
				RUNTIME_CLASS(CListViewActiveDoc));
			AddDocTemplate(pDocTemplate);
			// We add the tracker document to the template
			m_pActiveDocTracker = new CActiveDocTracker;
			pDocTemplate->AddDocument( m_pActiveDocTracker );

		// Progress indicator
		m_startScreen.m_progress.SetPos( 24 );

			// Create main MDI Frame window
			CMainFrame* pMainFrame = new CMainFrame;
			if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
				return FALSE;
			m_pMainWnd = pMainFrame;
			m_startScreen.SetMainFrame( pMainFrame );
		
		// Progress indicator
		m_startScreen.m_progress.SetPos( 36 );

			// Enable drag/drop open
			m_pMainWnd->DragAcceptFiles();

			// Initialize ATL thingies
			InitATL();

			// Enable DDE Execute open
			EnableShellOpen();
			RegisterShellFileTypes();
		
		// Progress indicator
		m_startScreen.m_progress.SetPos( 48 );

			// Parse command line for standard shell commands, DDE, file open
			CCommandLineInfo cmdInfo;
			ParseCommandLine(cmdInfo);

			// We don't want a new document on normal startup
			if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
				cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

			//Read the window state out of the registry
			RestoreWindowState(m_nCmdShow);
			
			// Dispatch commands specified on the command line
			if (!ProcessShellCommand(cmdInfo))
				return FALSE;

		// Progress indicator
		m_startScreen.m_progress.SetPos( 60 );

			// Database connection for multi-language support
			m_pMultiLang = new CMultiLanguage(m_startScreen.m_hWnd);
			CStageRaceDoc::Init();

		// Progress indicator
		m_startScreen.m_progress.SetPos( 72 );

			// The main window has been initialized, so show and update it.
			pMainFrame->ShowWindow(m_nCmdShow);
			pMainFrame->UpdateWindow();

			// We might need this later
			AfxInitRichEdit();

		// Progress indicator
		m_startScreen.m_progress.SetPos( 84 );

			AfxEnableControlContainer();

			// We check with the registry whether it is preferred by the user to get a
			// message on a missing hardware key
			LONG er;

			// Various
			CSRRegKey reg1;
			er = reg1.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );

			if( !reg1.GetBool( TEXT("SuppressHardwareKeyCheck"), false ) )
			{
				if( !m_key.HaspCheckDongle() )
					m_startScreen.DoMsgBoxHardwareKey();
			}

		// Progress indicator
		m_startScreen.m_progress.SetPos( 100 );

		// Message on start screen about hardware key
		if( m_key.CheckDongle( TRUE ) ) ((CStatic*)m_startScreen.GetDlgItem( IDC_DONGLE ))->ShowWindow( true );

		// Hide these two controls because loading is finished
		// Otherwise they can be visible behind the transparent image
		m_startScreen.GetDlgItem(IDC_LOADING_TEXT)->ShowWindow(false);
		m_startScreen.GetDlgItem(IDC_PROGRESS)->ShowWindow(false);
		// Show the Go! button
		m_startScreen.GetDlgItem(IDOK)->ShowWindow(true);
		// Set the focus to the Go! dialog to force the user to use it
		m_startScreen.SetFocus();

		return TRUE;
	}
}

// App command to run the dialog
void CStageRaceApp::OnAppAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.m_name		= m_key.GetProjectCodeName();
	dlgAbout.m_version	= m_key.GetExtraLongVersion();

	if( m_key.CheckDongle() )
	{
		dlgAbout.m_hardwareKey			= LoadStr( IDS_DIV29 );
		dlgAbout.m_evaluation			= LoadStr( IDS_DIV30 );
	}
	else
	{
		dlgAbout.m_hardwareKey			= LoadStr( IDS_DIV31 )+" "+m_key.HaspID();
		dlgAbout.m_evaluation			= LoadStr( IDS_DIV32 );
	}
	dlgAbout.m_hardwareKeyContents	= m_key.HaspContents();

	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CStageRaceApp commands

//Loads the windows state from the registry
void CStageRaceApp::RestoreWindowState(int& nCmdShow)
{
	CSRRegKey reg;
	LONG er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\MainFrame") );
	if( er == ERROR_SUCCESS )
	{
		if( reg.GetBool( TEXT("Zoomed"), false ) )
		{
			//Restore to maximized style
			nCmdShow = SW_SHOWMAXIMIZED;
		}
	}
}

// This function is only loaded during debug mode
void CStageRaceApp::Language()
{
//	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_FRENCH,SUBLANG_DEFAULT),SORT_DEFAULT));
//	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH,LANG_ENGLISH),SORT_DEFAULT));
	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_DUTCH,SUBLANG_DEFAULT),SORT_DEFAULT));

	SetThreadUILanguage(MAKELANGID(LANG_DUTCH,SUBLANG_DEFAULT));
}

//DEL void CStageRaceApp::OnLanguageEn() 
//DEL 	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT),SORT_DEFAULT));
//DEL void CStageRaceApp::OnLanguageNl() 
//DEL 	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_DUTCH,SUBLANG_DEFAULT),SORT_DEFAULT));
//DEL void CStageRaceApp::OnLanguageDe() 
//DEL 	::SetThreadLocale(MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_DEFAULT),SORT_DEFAULT));

/////////////////////////////////////////////////////////////////////////////
// CActiveDocTracker related stuff

// Pass this on, because it is not accessible when all views closed
// for this document
void CStageRaceApp::OnViewListviewactivedoc() 
{
	if( m_pActiveDocTracker )
		m_pActiveDocTracker->OnViewListviewactivedoc();	
}

// Pass this on, because it is not accessible when all views closed
// for this document
void CStageRaceApp::OnUpdateViewListviewactivedoc(CCmdUI* pCmdUI) 
{
	if( m_pActiveDocTracker )
		m_pActiveDocTracker->OnUpdateViewListviewactivedoc(pCmdUI);
}

void CStageRaceApp::ActiveDocOpen(CStageRaceDoc * pDoc)
{
	if( m_pActiveDocTracker )
		m_pActiveDocTracker->Open(pDoc);
}

void CStageRaceApp::ActiveDocClose(CStageRaceDoc * pDoc)
{
	if( m_pActiveDocTracker )
		m_pActiveDocTracker->Close(pDoc);
}

void CStageRaceApp::ActiveDocSelect(CStageRaceDoc * pDoc)
{
	if( m_pActiveDocTracker )
		m_pActiveDocTracker->Select(pDoc);
}

BOOL CStageRaceApp::PreTranslateMessage(MSG* pMsg) 
{
	// Let the active doc tracker have
	// the first look at all messages
	if( m_pActiveDocTracker->PreTranslateMessage( pMsg ) )
		return TRUE;
	else
		return CWinApp::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStageRaceApp object
CStageRaceApp theApp;

void CStageRaceApp::RegisterShellFileTypes()
{
	// Overridden because we could only either have a non-working solution
	// or a solution that also implemented unwanted printing dde functions
	LONG er;
	CString cPath;
	TCHAR chBuffer[500];
	GetModuleFileName( NULL, chBuffer, 500 );
	cPath = CString(chBuffer);

	{// EXTENSION
		CSRRegKey reg1;
		er = reg1.Create( HKEY_CLASSES_ROOT, TEXT(".str") );
		if( er == ERROR_SUCCESS )
		{
			reg1.SetString( TEXT(""), TEXT("StageRace.Document") );
		}
	}
	{// DOCUMENT NAME
		CSRRegKey reg1;
		er = reg1.Create( HKEY_CLASSES_ROOT, TEXT("StageRace.Document") );
		if( er == ERROR_SUCCESS )
		{
			reg1.SetString( TEXT(""), TEXT("StageRace Document") );
		}
	}
	{// DOCUMENT ICON
		CSRRegKey reg1;
		er = reg1.Create( HKEY_CLASSES_ROOT, TEXT("StageRace.Document\\DefaultIcon") );
		if( er == ERROR_SUCCESS )
		{
			reg1.SetString( TEXT(""), TEXT("\"")+cPath+TEXT("\",1") );
		}
	}
	{// DOCUMENT OPEN COMMAND
		CSRRegKey reg1;
		er = reg1.Create( HKEY_CLASSES_ROOT, TEXT("StageRace.Document\\shell\\open\\command") );
		if( er == ERROR_SUCCESS )
		{
			reg1.SetString( TEXT(""), TEXT("\"")+cPath+TEXT("\" /dde") );
		}
	}
	{// DOCUMENT OPEN DDE
		CSRRegKey reg1;
		er = reg1.Create( HKEY_CLASSES_ROOT, TEXT("StageRace.Document\\shell\\open\\ddeexec") );
		if( er == ERROR_SUCCESS )
		{
			reg1.SetString( TEXT(""), TEXT("[open(\"%1\")]") );
		}
	}

	// New since V2004
	// Also add COM components to the system
	HRESULT hr;
	hr = _Module.UpdateRegistryFromResource(IDR_STAGERACE, TRUE);
	hr = _Module.RegisterServer(TRUE);
}

void CStageRaceApp::UnregisterShellFileTypes()
{
	LONG success;
	CSRRegKey reg1;
	success = reg1.Open( HKEY_CLASSES_ROOT, TEXT("") );
	if( success == ERROR_SUCCESS )
	{
		reg1.RecurseDeleteKey( TEXT(".str") );
		reg1.RecurseDeleteKey( TEXT("StageRace.Document") );
	}
	CSRRegKey reg2;
	success = reg2.Open( HKEY_LOCAL_MACHINE, TEXT("Software\\Totaal Software") );
	if( success == ERROR_SUCCESS )
	{
		reg2.RecurseDeleteKey( TEXT("StageRace") );
	}
	CSRRegKey reg3;
	success = reg3.Open( HKEY_LOCAL_MACHINE, TEXT("Software") );
	if( success == ERROR_SUCCESS )
	{
		reg3.DeleteSubKey( TEXT("Totaal Software") );
	}
	CSRRegKey reg4;
	success = reg4.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software") );
	if( success == ERROR_SUCCESS )
	{
		reg4.RecurseDeleteKey( TEXT("StageRace") );
	}
	CSRRegKey reg5;
	success = reg5.Open( HKEY_CURRENT_USER, TEXT("Software") );
	if( success == ERROR_SUCCESS )
	{
		// Use DeleteSubKey so that it is only removed
		// when actually empty
		reg5.DeleteSubKey( TEXT("Totaal Software") );
	}

	// New since V2004
	// Also remove COM components from the system
	_Module.UpdateRegistryFromResource(IDR_STAGERACE, FALSE);
	_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
}

int CStageRaceApp::ExitInstance() 
{
	// End multilanguage thread
	if( m_pMultiLang ) delete m_pMultiLang;
	
	// Uninitialize the main document (such as
	// the HTML generator thread
	CStageRaceDoc::Exit();

	// Uninitialize our COM features
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	
		CoUninitialize();
	}

	return CWinApp::ExitInstance();
}

	
CStageRaceModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_StageRaceServer, CStageRaceServer)
OBJECT_ENTRY(CLSID_StageRaceDoc, CStageRaceComDoc)
OBJECT_ENTRY(CLSID_SRHalfStage, CSRHalfStage)
END_OBJECT_MAP()

LONG CStageRaceModule::Unlock()
{
	// Changed by Totaal Software:
	// The following is undesired as
	// we really want to kill servers
	// when exiting this application
//	AfxOleUnlockApp();
	return 0;
}

LONG CStageRaceModule::Lock()
{
	// Changed by Totaal Software:
	// The following is undesired as
	// we really want to kill servers
	// when exiting this application
//	AfxOleLockApp();
	return 1;
}

BOOL CStageRaceApp::InitATL()
{
	m_bATLInited = TRUE;

//#if _WIN32_WINNT >= 0x0400
//	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
//#else
	HRESULT hRes = CoInitialize(NULL);
//#endif

	if(FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);

	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		CoUninitialize();
		return FALSE;
	}	

	return TRUE;

}

const CStageRaceDoc* CStageRaceApp::ActiveDocGet()
{
	return m_pActiveDocTracker->GetSelected();
}

bool CStageRaceApp::CheckExe()
{
	TCHAR szPath[_MAX_PATH];
	GetModuleFileName( NULL, szPath, sizeof(szPath) );
	bool b = CExeChecksum::Compare( CString(szPath) );
	if( !b )
	{
	#ifdef _DEBUG
		MessageBox( NULL, TEXT("This file has been tampered with!"), TEXT("Error"), MB_OK );
		return true;
	#endif
		return false;
	}
	else
		return true;
}

void CStageRaceApp::ShowOperatorMessage(WPARAM message, LPARAM user)
{
	CString* pMessage = (CString*)message;
	CString* pUser = (CString*)user;

	// Show a message
	AfxMessageBox(
		LoadStr(IDS_DIV102)+
		*pUser+
		LoadStr(IDS_DIV103)+
		CTime::GetCurrentTime().Format(TEXT("%Hh%M"))+
		TEXT(":\n\n")+
		*pMessage );

	// Delete the strings
	delete pMessage;
	delete pUser;
}
