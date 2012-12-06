// CompetitorList.h: interface for the CCompetitorList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CompetitorLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_CompetitorLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCompetitorList : public CStaNoObjectList  
{
public:
	CCompetitorList();
	CCompetitorList(const CCompetitorList &aCompL);
	CCompetitorList& operator =(const CCompetitorList &aCompL);
	void Insert(CCompetitor &objComp);
	virtual bool IterateSorted( DWORD& nState, CCompetitor& objComp) const;
	virtual void Serialize(CArchive &ar);
	virtual void Iterate( POSITION& rNextPosition, CCompetitor& rValue ) const;
	CCompetitor GetAt( WORD nStaNo ) const;
};

#endif // !defined(AFX_CompetitorLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_)
