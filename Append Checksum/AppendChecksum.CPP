// AppendChecksum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AppendChecksum.h"
#include "..\ExeChecksum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		CString c(argv[1]);
		c.Remove('\"');
		if( CExeChecksum::AppendChecksum( c ) )
		{
			cout << "Append succesful " << c.GetBuffer(0) << endl;
			TRACE("\nAppend of checksum succesful\n"+c+"\n\n");
		}
		else
		{
			cout << "Append unsuccesful "<< c.GetBuffer(0) << endl;
		}
	}

	return nRetCode;
}


