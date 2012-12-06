#include "stdafx.h"
#include "incl.h"

// StageRace messages
// To SR
const UINT WM_STAGERACE_GETCOMPFROMSTANO		= ::RegisterWindowMessage(TEXT("WM_STAGERACE_GETCOMPFROMSTANO"));
const UINT WM_STAGERACE_AR_DECLASSCOMP			= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_DECLASSCOMP"));
const UINT WM_STAGERACE_AR_SETCOMP				= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_SETCOMP"));
const UINT WM_STAGERACE_AR_GETCOMPFROMSTANO		= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_GETCOMPFROMSTANO"));
const UINT WM_STAGERACE_AR_GETCOMPFROMTIME		= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_GETCOMPFROMTIME"));
const UINT WM_STAGERACE_AR_GETCOMPFROMRANK		= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_GETCOMPFROMRANK"));
const UINT WM_STAGERACE_TT_GETSTARTTIME			= ::RegisterWindowMessage(TEXT("WM_STAGERACE_TT_GETSTARTTIME"));
// From SR
const UINT WM_STAGERACE_COMP					= ::RegisterWindowMessage(TEXT("WM_STAGERACE_COMP"));
const UINT WM_STAGERACE_AR_INFOCOMP				= ::RegisterWindowMessage(TEXT("WM_STAGERACE_AR_INFOCOMP"));
const UINT WM_STAGERACE_TT_INFOCOMP				= ::RegisterWindowMessage(TEXT("WM_STAGERACE_TT_INFOCOMP"));

// Loads a string from the multi-language database
CString LoadStr( TCHAR czID[], const CMultiLanguage::LANGUAGE lang )
{
	return ((CStageRaceApp*)AfxGetApp())->m_pMultiLang->LoadStr( czID, lang );
}

CString AssembleStr( TCHAR czID[], TCHAR czCement[], const CMultiLanguage::REQUIREDLANGUAGES* pLang )
{
	return ((CStageRaceApp*)AfxGetApp())->m_pMultiLang->AssembleStr( czID, czCement, pLang );
}

// Loads a string from the resources and returns it
CString LoadStr( int nID )
{
	CString chHelp;
	chHelp.LoadString( nID );
	return chHelp;
}

void MultiLanguagePopulateListBox(CComboBox *pComboBox)
{
	((CStageRaceApp*)AfxGetApp())->m_pMultiLang->PopulateListBox( pComboBox );
}

// Removes quotes from a string and returns it
CString NoQuotes( CString cQuoted )
{
	cQuoted.Remove( '\"' );
	return cQuoted;
}

// Removes commas from a string and returns it
CString NoCommas( CString cQuoted )
{
	cQuoted.Remove( ',' );
	return cQuoted;
}

CString MakePathUsable( CString czPath )
{
	// Make sure there always is a slash on the right
	// (except when no path at all is given)
	if( czPath.GetLength() )
		if( czPath.Right( 1 )!="\\" )
			czPath += "\\";
	return czPath;
}

// Get the path name to this executable
CString GetModulePathName()
{
	CString dir;
	GetModuleFileName( NULL, dir.GetBuffer(MAX_PATH), MAX_PATH );
	dir.ReleaseBuffer();
	dir = dir.Left( dir.ReverseFind( '\\' )+1 );
	return dir;
}

