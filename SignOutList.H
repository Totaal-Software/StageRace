// SignOutList.h: interface for the CSignOutList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGNOUTLIST_H__FF557385_8190_4166_9E30_A336E9350038__INCLUDED_)
#define AFX_SIGNOUTLIST_H__FF557385_8190_4166_9E30_A336E9350038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSignOutList : public CStaNoObjectList  
{
public:
	CSignOutList();
	CSignOutList(const CSignOutList &aSignOutL);
	CSignOutList& operator =(const CSignOutList &aSignOutL);
	void Insert(CSignOut &objSignOut);
	virtual bool IterateSorted( DWORD& nState, CSignOut& objSignOut) const;
	virtual void Serialize(CArchive &ar);
	virtual void Iterate( POSITION& rNextPosition, CSignOut& rValue ) const;
	CSignOut GetAt( WORD nStaNo ) const;
};

#endif // !defined(AFX_SIGNOUTLIST_H__FF557385_8190_4166_9E30_A336E9350038__INCLUDED_)
