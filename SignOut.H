// SignOut.h: interface for the CSignOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNOUT_H__706623A5_B62A_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_SIGNOUT_H__706623A5_B62A_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSignOut : public CStaNoObject
{
public:
	CString m_reasonOfSignOut;

	CSignOut();
	virtual ~CSignOut();
	CSignOut& operator =(const CSignOut &aSignOut);

	void Serialize(CArchive & ar);
};

#endif // !defined(AFX_SIGNOUT_H__706623A5_B62A_11D3_92DA_0040954019F4__INCLUDED_)
