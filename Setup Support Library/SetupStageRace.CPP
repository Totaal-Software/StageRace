// StageRaceSetup.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
#include <shlwapi.h>

int GET_MSIE_VERSION(int *,int *);

/*__declspec(dllexport)*/ BOOL APIENTRY ONNEWPAGE(DWORD Page, DWORD NextPage, HWND HWnd,
void (APIENTRY *GetProc)(PCHAR Name, PCHAR Buffer, PDWORD Count, DWORD Mode),
void (APIENTRY *SetProc)(PCHAR Name, PCHAR Buffer, PDWORD Count, DWORD Mode))
{
	switch( Page )
	{
		case 2:
		{
			int major, minor;
			int result;
	//		MessageBox(NULL, "The version of Microsoft® Internet Explorer is being retrieved.", "Check", MB_OK );
			result = GET_MSIE_VERSION(&major,&minor);
			if( result )
			{
				// Getting the version nos. failed
				MessageBox(
					HWnd,
					"The version no. of the Microsoft® Internet Explorer on your computer could not be retrieved. Setup will continue, but appreciate that StageRace requires Internet Explorer 4.0 or up to work.",
					"Warning",
					MB_OK
				);
			}
			else
			{
				// Evaluate the version nos.
				if( major < 4 )
				{
					MessageBox(
						HWnd,
						"StageRace requires Microsoft® Internet Explorer 4.0 or up to work. A sufficiently high version of Internet Explorer could not be found on your computer. Setup cannot continue.",
						"Error",
						MB_OK
					);
					return FALSE;
				}
			}
		}
		break;
		case -2:
		{
	//		MessageBox(NULL, "Arranging the My Stage Races folder", "MSR folder", MB_OK );

			// Get the name of the My Documents folder
			char msrfolder[MAX_PATH];
			DWORD count = MAX_PATH;
			GetProc( "@DOCUMENTS", msrfolder, &count, 3 );
			
			// Set the My Stage Races sub folder to system prop.
			strcat( msrfolder, "My Stage Races" );
			if( PathMakeSystemFolder(msrfolder)==0 )
				MessageBox( NULL, "Error while setting My Stage Races folder as system folder (1).", "Error", MB_OK );
			
			// Set the desktop.ini to system prop.
			if( SetFileAttributes( msrfolder,
						FILE_ATTRIBUTE_SYSTEM )
					== 0 )
				MessageBox( NULL, "Error while setting My Stage Races folder as system folder (2).", "Error", MB_OK );


			// Set the desktop.ini to system prop.
			strcat( msrfolder, "\\desktop.ini" );
			if( SetFileAttributes( msrfolder,
						FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM )
					== 0 )
				MessageBox( NULL, "Error while setting My Stage Races folder's layout.", "Error", MB_OK );


		}
		break;
	}
	return TRUE;
}

int GET_MSIE_VERSION(int *iMajor, int *iMinor)
// Created: 3/23/2001  (rk)
// Last modified: 4/4/2001  (rk)
// Please send any bugs or suggestions to kochhar@physiology.wisc.edu
// Get MS Internet Explorer version by reading the registry
// Return major version in iMajor, minor version in iMinor
// Return code is 0 for success, error otherwise
// Should work with Windows 95/98/ME/NT/2000
// Return codes are as follows:
//    0    : Success
//    644  : Unable to open Registry Key
//    645  : Unable to read key value
//    650  : Unable to decipher IE version number
{
	LONG lResult;
	int iPos,iPos2;
    HKEY hKey;
	DWORD dwSize=100,dwType;
	char szVAL[100],szTemp[5];
	char *pDec,*pDec2;

    // Open the key for query access
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                    (LPCTSTR)"SOFTWARE\\Microsoft\\Internet Explorer",
					0,KEY_QUERY_VALUE,&hKey);

	if(lResult != ERROR_SUCCESS)   // Unable to open Key
	{
		return 644;
	}

    // OK, read the value
	lResult = RegQueryValueEx(hKey,(LPTSTR)"Version",NULL,
			&dwType, (LPBYTE)szVAL,&dwSize);

	if(lResult != ERROR_SUCCESS)    // Unable to get value
	{
	  // Close the key before quitting
		lResult = RegCloseKey(hKey);
	  return 645;
	}

	// Close the key
    lResult = RegCloseKey(hKey);

	// Extract major version by looking for the first decimal
	pDec=strstr(szVAL,".");
	if(pDec==NULL)
		return 650;         // Unable to decipher version number
	iPos=pDec-szVAL+1;
	ZeroMemory(szTemp,5);
	strncpy(szTemp,szVAL,iPos-1);
	*iMajor=atoi(szTemp);

	// Find the Minor version number, look for second decimal
	pDec++;
	pDec2=strstr(pDec,".");
	if(pDec2==NULL)
	{
		*iMinor=0;          // Minor version not found
		return 0;
	}
	iPos2=pDec2-szVAL+1;
	ZeroMemory(szTemp,5);
	strncpy(szTemp,pDec,iPos2-iPos-1);
	*iMinor=atoi(szTemp);

	return 0;
}