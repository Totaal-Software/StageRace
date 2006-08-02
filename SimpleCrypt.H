// SimpleCrypt.h: interface for the CSimpleCrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLECRYPT_H__EDD6C805_7651_466A_B8C4_5A44EA2FB205__INCLUDED_)
#define AFX_SIMPLECRYPT_H__EDD6C805_7651_466A_B8C4_5A44EA2FB205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSimpleCrypt  
{
public:
	static CString Encrypt(CString c);
	static CString Decrypt(CString c);

};

#endif // !defined(AFX_SIMPLECRYPT_H__EDD6C805_7651_466A_B8C4_5A44EA2FB205__INCLUDED_)
