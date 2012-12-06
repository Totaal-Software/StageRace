// SRRegKey.cpp: implementation of the CSRRegKey class.
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

CSRRegKey::CSRRegKey()
{

}

CSRRegKey::~CSRRegKey()
{

}

void CSRRegKey::SetBool(LPCTSTR lpszValueName, bool bVal)
{
	SetValue( (DWORD)bVal, lpszValueName );
}

void CSRRegKey::SetDWord(LPCTSTR lpszValueName, DWORD nVal)
{
	SetValue( nVal, lpszValueName );
}

void CSRRegKey::SetString(LPCTSTR lpszValueName, CString cVal)
{
	SetValue( cVal, lpszValueName );
}

CString	CSRRegKey::GetString( LPCTSTR lpszValueName, CString cDefault )
{
	TCHAR czVal[255];
	DWORD dwCount = sizeof( czVal )/sizeof( TCHAR );
	if( QueryValue( czVal, lpszValueName, &dwCount ) == ERROR_SUCCESS )
		return CString(czVal);
	else
		return cDefault;
}

DWORD CSRRegKey::GetDWord( LPCTSTR lpszValueName, DWORD nDefault )
{
	DWORD dwValue=0; // initializing is important
					 // (DWORD is >8bit while QueryValue can
					 // possibly read byte per byte)
	if( QueryValue( dwValue, lpszValueName ) == ERROR_SUCCESS )
		return dwValue;
	else
		return nDefault;
}

bool CSRRegKey::GetBool( LPCTSTR lpszValueName, bool bDefault )
{
	DWORD dwValue=0; // initializing is important
					 // (DWORD is >8bit while QueryValue can
					 // possibly read byte per byte)
	if( QueryValue( dwValue, lpszValueName ) == ERROR_SUCCESS )
		return dwValue!=0;
	else
		return bDefault;
}
