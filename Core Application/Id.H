// Id.h: interface for the CId class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ID_H__5F6F3B4C_DC05_4A0F_90A3_4A4C8266CC9D__INCLUDED_)
#define AFX_ID_H__5F6F3B4C_DC05_4A0F_90A3_4A4C8266CC9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CId : public CObject
{
	friend class CIdView;
	friend class CIdUseList;
public:
	void SetNo(unsigned short);
	CId();
	void Serialize(CArchive & ar);

	CId& operator =(const CId &aId);
	unsigned short GetNo() const;
	BOOL IsPublished() const;
protected:
	BOOL			m_bPublished;
	unsigned short	m_nId;
};

#endif // !defined(AFX_ID_H__5F6F3B4C_DC05_4A0F_90A3_4A4C8266CC9D__INCLUDED_)
