// StaNoObject.h: interface for the CStaNoObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANOOBJECT_H__163B4677_814E_4549_BBAB_153F3C3E10CA__INCLUDED_)
#define AFX_STANOOBJECT_H__163B4677_814E_4549_BBAB_153F3C3E10CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaNoObject : public CObject  
{
public:
	WORD m_staNo;

	void Serialize(CArchive & ar);
	CStaNoObject();
	CStaNoObject(const CStaNoObject &aStaNo);
	virtual ~CStaNoObject();
	CStaNoObject& operator =(const CStaNoObject & aStaNo);
};

#endif // !defined(AFX_STANOOBJECT_H__163B4677_814E_4549_BBAB_153F3C3E10CA__INCLUDED_)
