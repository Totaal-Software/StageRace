// Communique.h: interface for the CCommunique class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNIQUE_H__10439C01_BE4A_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_COMMUNIQUE_H__10439C01_BE4A_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommunique : public CObject  
{
public:
	CString m_date;
	CString m_contents;
	CString m_title;
	CId m_id;

	void Serialize(CArchive & ar);

	CCommunique();
	virtual ~CCommunique();
	CCommunique& operator =(const CCommunique &aComm);
	CCommunique& operator =(const CEditCommunique &aEdit);

	bool IsEmpty();
	void Empty();
};

#endif // !defined(AFX_COMMUNIQUE_H__10439C01_BE4A_11D3_92DA_0040954019F4__INCLUDED_)
