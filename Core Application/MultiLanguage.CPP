// MultiLanguage.cpp: implementation of the CMultiLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiLanguage::CMultiLanguage(HWND hCurrentWnd)
{
	m_pWorker = AfxBeginThread( ThreadFunction, (LPVOID)hCurrentWnd );
}

CMultiLanguage::~CMultiLanguage()
{
	m_pWorker->PostThreadMessage( WM_QUIT, 0, 0 );

	DWORD exit_code;
	if( GetExitCodeThread(m_pWorker->m_hThread,&exit_code) )
	{
		if( exit_code==STILL_ACTIVE )
			WaitForSingleObject(m_pWorker->m_hThread, INFINITE);
	}
}

// in: the identifier to look up; the desired language
// out: the value indicated by the identifier, in the desired language
CString CMultiLanguage::LoadStr(TCHAR czID[], const CMultiLanguage::LANGUAGE lang)
{
	// Prepare the calling parameters
	LOADSTR ls;
	ls.lang = lang;
	ls.id = czID;
	ls.hSemaphore = CreateSemaphore(NULL, 0, 1, NULL);

	// Make a NULL pointer for the result value
	CString* pRet = NULL;

	// Post the request for a string
	m_pWorker->PostThreadMessage( WM_USER_LOADSTR, (WPARAM)&ls, (LPARAM)&pRet );

	// Wait for the result (being prepared by the worker thread)
	WaitForSingleObject(ls.hSemaphore,INFINITE);


	// If the result string is available, copy it and then delete it
	CString ret = *pRet;
	delete pRet;

	CloseHandle(ls.hSemaphore);

	// Return the copy of the result string
	return ret;
}

// in: the identifier to look up; the separator for the
//	values of the different languages
// out: a string composed of all the values of the required
//	languages, separated by the 'cement'
CString CMultiLanguage::AssembleStr(TCHAR czID[], TCHAR czCement[], const REQUIREDLANGUAGES* pLang)
{
	CString cResult;
	for( int i=0; i<pLang->GetSize(); )
	{
		cResult += LoadStr( czID, pLang->GetAt(i) );
		if( ++i<pLang->GetSize() )
			cResult+=czCement;
	}
	return cResult;
}

void CMultiLanguage::PopulateListBox(CComboBox *pComboBox)
{
	m_pWorker->PostThreadMessage( WM_USER_POPULATELISTBOX, (WPARAM)pComboBox, 0 );
}

UINT CMultiLanguage::ThreadFunction(LPVOID pParam)
{
	// INITIALISATION

		HWND			hCurrentWnd = (HWND)pParam;
		CDaoRecordset*	pRecordset = NULL;
		CDaoDatabase	database;

		// Try to open the database
		try
		{
			/* The MFC DAO classes that ship with Visual C++ 6.0
			load DAO 3.5 (Dao350.dll) by default. DAO 3.5 uses Jet
			3.5, which can only open Jet 3.5 format (or earlier)
			databases. Access 2000 creates Jet 4.0 format database
			files, which are unrecognizable to Jet 3.5. To
			successfully open an Access 2000 database using the
			MFC DAO classes, you need to use DAO 3.6 (Dao360.dll).
			DAO 3.6 uses Jet 4.0, which can open any available
			Access database format.

			For your application to use version 3.6 of DAO, you
			must update the version of MFC at run time to MFC
			version 6.01. To do this depends on whether you are
			building the application to use the MFC DLL or to build
			with the static libraries for MFC. 

			If you are linking with the MFC DLL, you can specify
			that you want MFC to use DAO 3.6 by inserting the
			following line of code before you open an Access 2000
			database:
			*/
			AfxGetModuleState()->m_dwVersion = 0x0601;

			// Open the database
			database.Open( GetModulePathName()+"MultiLanguage2005.mdb",
					TRUE,	// the database is to be opened for exclusive access,
							// see: http://support.microsoft.com/kb/191737
					TRUE	// the database is to be opened for read-only access
				);

			// Indicate the table that has to be opened
			CDaoTableDef Table( &database );
			Table.Open( TEXT("Translations") );

			// Try to open the recordset for that table
			pRecordset = new CDaoRecordset( &database );
			pRecordset->Open( &Table, dbOpenTable, dbReadOnly );

			// Select the primary key from that table
			pRecordset->SetCurrentIndex( TEXT("PrimaryKey") );
		}
		catch( CDaoException* pe )
		{
			if( pe && (pe->m_nAfxDaoError!=AFX_DAO_ERROR_ENGINE_INITIALIZATION) )
			{
				TCHAR   szCause[255];
				pe->GetErrorMessage(szCause,255);
				MessageBox(
					hCurrentWnd,
					szCause,
					::LoadStr( IDS_DIV66 ),
					MB_ICONEXCLAMATION );
			}
			else
				MessageBox(
					hCurrentWnd,
					::LoadStr( IDS_DIV82 ),
					::LoadStr( IDS_DIV66 ),
					MB_ICONEXCLAMATION );
			if( pe )
				pe->Delete();
		}

	// MAIN PROCESS

		MSG msg;
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			switch(msg.message)
			{
				case WM_USER_LOADSTR:
					{
						LOADSTR* pls = (LOADSTR*)msg.wParam;

						CString* pRet = new CString;
						if( pRecordset )
						{
							COleVariant varID	( pls->id, VT_BSTRT );
							COleVariant varLang	( CString(pls->lang.ac), VT_BSTRT );
							CString Holder;

							if( pRecordset->
									Seek( TEXT("="), &varLang, &varID ) )
							{
								COleVariant varRes;
								pRecordset->GetFieldValue( TEXT("Value"), varRes );
								*pRet = CString((LPCTSTR)varRes.pbVal);
							}
							else
							{
								// If string not found, see if we need to return
								// a question mark alternatively
								LONG er;
								CSRRegKey reg;
								er = reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );
								if( er == ERROR_SUCCESS )
									if( reg.GetBool( TEXT("IndicateMissingLanguageStrings"), false ) )
										*pRet = TEXT("?");
							}
						}
						// The following is thread critical, as the
						// CString* that is pointed to is being monitored
						// from the calling thread that will proceed on
						// change
						*((CString**)msg.lParam) = pRet;

						ReleaseSemaphore(pls->hSemaphore,1,NULL);
					}
					break;
				case WM_USER_POPULATELISTBOX:
					{
						CComboBox* pComboBox = (CComboBox*)msg.wParam;

						//	SELECT DISTINCT Translations.Language
						//	FROM Translations;
						if( database.IsOpen() )
						{
							// Establish a query resulting in all the available languages 
							CDaoQueryDef Query( &database );
							Query.Create( NULL,
								TEXT("SELECT DISTINCT Translations.Language FROM Translations;") );

							// Try to open the recordset for that query
							CDaoRecordset Set( &database );
							Set.Open( &Query, dbOpenDynaset, dbReadOnly );

							// Walk through the resulting recordset
							Set.MoveFirst();
							while( !Set.IsEOF() )
							{
								COleVariant varRes;
								Set.GetFieldValue( TEXT("Language"), varRes );
								// Add the strings to the list box
								pComboBox->AddString( CString((LPCTSTR)varRes.pbVal) );
								Set.MoveNext();
							}

							// Close this recordset
							Set.Close();
						}
					}
			}
		}

	// CLEANUP
		
		// Delete the recordset, if it has ever been opened
		if( pRecordset ) delete pRecordset;

		AfxDaoTerm();

		return 0;
}
