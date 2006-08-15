// HaspTotaal.cpp: implementation of the CHaspTotaal class.
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

CHaspTotaal::CHaspTotaal()
{
	// Make thread safe
	m_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
	Lock();
	
	// Change all this for every Totaal Software project

	// Hasp related
	m_haspChecksum	= -1475;		// p1-p2+p3-p4
	m_haspPwd1		= 12981;		// SECRET SECRET SECRET
	m_haspPwd2		=  7548;		// SECRET SECRET SECRET
	m_haspSeedCode	=   100;		// Totaal-default=100
	m_protected		= FALSE;		// Default FALSE on startup of application
	m_firstshot		= TRUE;

	// Get the full name of the app
	TCHAR pcEXE[MAX_PATH];
	GetModuleFileName(NULL, pcEXE, MAX_PATH);

	// Version information
	m_VersionInfo.m_ProjectCodeName	= "STAGERAC";
	CString cFileVersion = GetVersionInfo(pcEXE,TEXT("FileVersion"));

//"2000", "2003"
	int nComma1, nComma2;
	nComma1 = cFileVersion.Find( TEXT(",") );
	m_VersionInfo.m_VersionTitle = cFileVersion.Left( nComma1++ );

//"1", "2"
	nComma2 = cFileVersion.Find( TEXT(","), nComma1 );
	m_VersionInfo.m_VersionNo = cFileVersion.Mid( nComma1,nComma2-nComma1 );
	m_VersionInfo.m_VersionNo.TrimLeft();
	nComma1=nComma2+1;

//"00", "01", "01 DEBUG", ...
	nComma2 = cFileVersion.Find( TEXT(","), nComma1 );
	m_VersionInfo.m_Release = cFileVersion.Mid( nComma1,nComma2-nComma1 );
	m_VersionInfo.m_Release.TrimLeft();
	m_VersionInfo.m_Release = TEXT("00") + m_VersionInfo.m_Release;
	m_VersionInfo.m_Release = m_VersionInfo.m_Release.Right( 2 ) + /*" final update";// +*/ " BÈTA";

	#ifdef _DEBUG
		m_VersionInfo.m_Release	+= " DEBUG";
	#endif

//"V1.00"
	m_VersionInfo.m_LongVersion = "V"+m_VersionInfo.m_VersionNo+"."+m_VersionInfo.m_Release;

	Unlock();
}

CHaspTotaal::~CHaspTotaal()
{
	Lock();
	CloseHandle( m_hSemaphore );
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

bool CHaspTotaal::CheckDongle(bool bSuppress/*=FALSE*/)
{
	// HASP Device Driver installation status:
	// 
	// Version installed:	3.4
	// Driver Path:			C:\WINDOWS\SYSTEM\hasp95.vxd
	// Installation date:	January 27,  1999
	// Computer name:		X86
	// Computer type:		IBM computer
	// Port Mode:			Auto
	// Check earlier absence of hardware key
#ifdef _DEBUG
if( m_firstshot )
PostMessage( AfxGetMainWnd()->m_hWnd, WM_USER_KEY_FREE, NULL, NULL );
m_firstshot = FALSE;
return false;
#endif _DEBUG
	if ( !m_protected )
	{
		// Check presence of any hardware key
		if ( HaspCheckDongle() )
		{
			// Check presence of VALID hardware key on seed code
			if( HaspCheckSeed() ) m_protected  = true;
			else
			{
				// Get key contents
				CString KeyContents = HaspContents();

				if (  KeyContents.Left(8)  ==  m_VersionInfo.m_ProjectCodeName )
				{
					if( KeyContents.Mid(10,4) < m_VersionInfo.m_LongVersion.Mid(1,4) ) m_protected = true;
				}
				else m_protected = true;
			}				
		}
		else
		{
			m_protected = true;
		};
		// If first time detection of absence of hardware key
		// we let a MessageBox pop up
		if ( m_protected && !bSuppress )
			MessageBox(	NULL,
				LoadStr( IDS_MBC_30 ),
				LoadStr( IDS_MBT_30 ), MB_OK|MB_ICONEXCLAMATION|MB_APPLMODAL );

		// Arrange it to be showed in the status bar
		// But only once (will suck up performance otherwise
		if( m_protected )
			PostMessage( AfxGetMainWnd()->m_hWnd, WM_USER_KEY_LOCKED, NULL, NULL );
		else
		{
			if( m_firstshot )
				PostMessage( AfxGetMainWnd()->m_hWnd, WM_USER_KEY_FREE, NULL, NULL );
			m_firstshot = FALSE;
		}
	}

	return m_protected;
}

CString CHaspTotaal::HaspContents()
{
	Lock();

	int n1, n2, n3, n4;
	// Get key contents
	int HaspBuffer[26]={0};
	n1 = 0;
	n2 = 24;
	n4 = (int) HaspBuffer;
	hasp (50, 0, 0, m_haspPwd1, m_haspPwd2, &n1, &n2, &n3, &n4);
	
	CString KeyContents;
	if ( n3<0 ) KeyContents = LoadStr( IDS_DIV33 );
			else KeyContents = (char *) HaspBuffer;

	Unlock();

	return KeyContents;
}

bool CHaspTotaal::HaspCheckDongle()
{
	Lock();
	
	int n1, n2, n3, n4;
	// Check presence of any hardware key
	hasp (1, 0, 0, 0, 0, &n1, &n2, &n3, &n4);

	Unlock();

	if (n1) return true;
		else return false;
}

bool CHaspTotaal::HaspCheckSeed()
{
	Lock();

	int n1, n2, n3, n4;
	// Check presence of VALID hardware key
	// Check return values for particular seed code
	hasp (2, m_haspSeedCode, 0, m_haspPwd1, m_haspPwd2, &n1, &n2, &n3, &n4);
	
	Unlock();

	if(n1-n2+n3-n4-m_haspChecksum) return false;
								else return true;
}

CString CHaspTotaal::HaspID()
{
	Lock();

	union
	{
		signed int s;
		unsigned int u;
	} n1, n2, n3, n4;
	// Get key ID
	hasp (6, 0, 0, m_haspPwd1, m_haspPwd2, &n1.s, &n2.s, &n3.s, &n4.s);

	char buffer[40];
	_ultoa( (unsigned long)(n2.u*65536+n1.u), buffer, 10 );
	CString strID = CString(buffer);

	Unlock();
	
	return strID;
}

bool CHaspTotaal::IsProtected()
{
	return m_protected;
}

CString CHaspTotaal::GetVersionNo()
{
	return m_VersionInfo.m_VersionNo;
}

CString CHaspTotaal::GetProjectCodeName()
{
	return m_VersionInfo.m_ProjectCodeName;
}

CString CHaspTotaal::GetExtraLongVersion()
{
	return "V"+
		m_VersionInfo.m_VersionNo	+"."+
		m_VersionInfo.m_Release		+" - "+
		m_VersionInfo.m_VersionTitle+"."+
		m_VersionInfo.m_VersionNo	+"."+
		m_VersionInfo.m_Release;
}

CString CHaspTotaal::GetVersionTitle()
{
	return m_VersionInfo.m_VersionTitle;
}

CString CHaspTotaal::GetRawLongVersion()
{
	return m_VersionInfo.m_LongVersion;
}

CString CHaspTotaal::GetNiceLongVersion()
{
	return "V"+
		m_VersionInfo.m_VersionTitle+"."+
		m_VersionInfo.m_VersionNo	+"."+
		m_VersionInfo.m_Release;
}

bool CHaspTotaal::FastIsProtected()
{
	return m_protected;
}

CString CHaspTotaal::GetReleaseNo()
{
	return m_VersionInfo.m_Release;
}

CString CHaspTotaal::GetVersionInfo( LPCTSTR lpFile, LPCTSTR lpEntry )
{
	TCHAR szBuffer[_MAX_PATH];
	DWORD dwVerHandle = 0;
	DWORD dwVerSize = GetFileVersionInfoSize((LPTSTR)lpFile, &dwVerHandle );
	CString strReturn;
	HANDLE hMem;

	if( dwVerSize > 0 && ( hMem = GlobalAlloc( GMEM_MOVEABLE, dwVerSize ) ) != NULL )
	{
		LPTSTR lpVerInfo = (LPTSTR)GlobalLock( hMem );
		if( lpVerInfo != NULL )
		{
			TCHAR* szLanguage[] = { TEXT("000004B0") }; // add your language(s) here
			LPCTSTR lpEntryBuffer;
			UINT nEntryLen;
			BOOL b = GetFileVersionInfo( (LPTSTR)lpFile, dwVerHandle, dwVerSize, lpVerInfo );
			for( int n = 0; n < sizeof( szLanguage ) / sizeof( szLanguage[0] ); n++ )
			{
				_stprintf( szBuffer, TEXT("\\StringFileInfo\\%s\\%s"), szLanguage[n], lpEntry );
				if( VerQueryValue( lpVerInfo, szBuffer, (LPVOID*)&lpEntryBuffer, &nEntryLen ) )
				{
					strReturn = CString((LPCTSTR)lpEntryBuffer);
					break;
				}
			}
			GlobalUnlock( hMem );
		}
		GlobalFree( hMem );
	}
	return strReturn;
}

void CHaspTotaal::Lock()
{
	WaitForSingleObject(m_hSemaphore,INFINITE);
}

void CHaspTotaal::Unlock()
{
	ReleaseSemaphore(m_hSemaphore,1,NULL);
}
