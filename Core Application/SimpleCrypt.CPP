// SimpleCrypt.cpp: implementation of the CSimpleCrypt class.
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

CString CSimpleCrypt::Encrypt(CString c)
{
	for( int i = 0; i<c.GetLength(); i++ )
	{
		c.SetAt(i,255-c[i]);
	}
	return c;
}

CString CSimpleCrypt::Decrypt(CString c)
{
	for( int i = 0; i<c.GetLength(); i++ )
	{
		c.SetAt(i,255-c[i]);
	}
	return c;
}
