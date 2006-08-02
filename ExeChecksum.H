// ExeChecksum.h: interface for the CExeChecksum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXECHECKSUM_H__1D730006_EBE5_4D7B_A903_3333BA10C4A3__INCLUDED_)
#define AFX_EXECHECKSUM_H__1D730006_EBE5_4D7B_A903_3333BA10C4A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExeChecksum  
{
public:
	static bool AppendChecksum(CString cFile);
	static bool Compare( CString cFile );
	static DWORD Check( CString cFile, bool bMinusFour = true );

protected:
	static DWORD Calculate( char[], int len );
	static DWORD s_arrdwCrc32Table[256];
};

#endif // !defined(AFX_EXECHECKSUM_H__1D730006_EBE5_4D7B_A903_3333BA10C4A3__INCLUDED_)
