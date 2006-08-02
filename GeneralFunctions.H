///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Edwin Engelen
// Primary date: 06-04-2000
// Filename: GeneralFunctions.cpp
// Description: -
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 06-04-2000	EE	Created
//
///////////////////////////////////////////////////////////////////////////

// StageRace messages
// To SR
extern const UINT WM_STAGERACE_GETCOMPFROMSTANO;
extern const UINT WM_STAGERACE_AR_SETCOMP;
extern const UINT WM_STAGERACE_AR_DECLASSCOMP;
extern const UINT WM_STAGERACE_AR_GETCOMPFROMSTANO;
extern const UINT WM_STAGERACE_AR_GETCOMPFROMTIME;
extern const UINT WM_STAGERACE_AR_GETCOMPFROMRANK;
extern const UINT WM_STAGERACE_TT_GETSTARTTIME;
// From SR
extern const UINT WM_STAGERACE_COMP;
extern const UINT WM_STAGERACE_AR_INFOCOMP;
extern const UINT WM_STAGERACE_TT_INFOCOMP;

// Global functions
CString LoadStr( int nID );
CString LoadStr( TCHAR czID[], const CMultiLanguage::LANGUAGE lang );
void MultiLanguagePopulateListBox(CComboBox *pComboBox);
CString AssembleStr( TCHAR czID[], TCHAR czCement[], const CMultiLanguage::REQUIREDLANGUAGES* pLang );
CString NoQuotes( CString cQuotes );
CString NoCommas( CString cQuotes );
CString MakePathUsable( CString czPath );
CString GetModulePathName();
