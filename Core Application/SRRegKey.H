// SRRegKey.h: interface for the CSRRegKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SRREGKEY_H__EE95AD4A_C0F4_40D7_9BC6_304AF7187DC8__INCLUDED_)
#define AFX_SRREGKEY_H__EE95AD4A_C0F4_40D7_9BC6_304AF7187DC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSRRegKey : public CRegKey  
{
public:
	CString	GetString( LPCTSTR lpszValueName, CString cDefault ); // ADDED for STAGERACE
	DWORD	GetDWord ( LPCTSTR lpszValueName, DWORD nDefault ); // ADDED for STAGERACE
	bool	GetBool  ( LPCTSTR lpszValueName, bool bDefault ); // ADDED for STAGERACE
	void	SetString( LPCTSTR lpszValueName, CString cVal ); // ADDED for STAGERACE
	void	SetDWord ( LPCTSTR lpszValueName, DWORD nVal ); // ADDED for STAGERACE
	void	SetBool  ( LPCTSTR lpszValueName, bool bVal ); // ADDED for STAGERACE

	CSRRegKey();
	virtual ~CSRRegKey();

};

#endif // !defined(AFX_SRREGKEY_H__EE95AD4A_C0F4_40D7_9BC6_304AF7187DC8__INCLUDED_)
