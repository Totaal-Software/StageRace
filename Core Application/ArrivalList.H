// ArrivalList.h: interface for the CArrivalList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRIVALLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_ARRIVALLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArrivalList : public CStaNoObjectList  
{
	DECLARE_DYNAMIC( CArrivalList )
public:
	void ApplyRanks(bool bTimeTrial=false);
	bool GetAtTime(DWORD nUnits, CArrival *pArrival) const;
	BYTE GetTimeCut();
	bool IsTimeCutted( WORD nStaNo ) const;
	void ResetTimeCut();
	void SetTimeCut( BYTE );
	void ApplyTimeTrialRanks();
	void Insert( const CArrivalList &aArrL );
	void Insert( const CCorrectionList &aCorrL );
	bool Import();
	bool CheckIntegrity( CString* cCheckResult );
	void RemoveGapsOrder();
	void RemoveGapsRanking();
	void ApplyGroupTime( unsigned short nDelaySec );
	void Remove1XSeconds();
	void AwardBonuses(CMap<WORD,WORD&,WORD,WORD&>* pBonusesList);
	void AwardPoints( CMap<WORD,WORD&,WORD,WORD&>* pPointsList );
	bool GetAtRank(WORD nRank, CArrival *pArrival) const;
	CArrivalList();
	void Iterate( POSITION& rNextPosition, CArrival& rValue ) const;
	bool GetAtOrder( WORD nOrder, CArrival* pArrival ) const;
	CArrivalList(const CArrivalList &aArrival);
	CArrival GetAt( WORD nStaNo ) const;
	bool IterateSortedUncut( DWORD& nState, CArrival& objArr) const;
	bool IterateSortedCut( DWORD& nState, CArrival& objArr) const;
	bool IterateSorted( DWORD& nState, CArrival& objArr) const;
	void Serialize(CArchive &ar);
	void Insert( CArrival &objArr );
	CArrivalList& operator =(const CArrivalList &aArrL);
	CArrivalList& operator =(const CCorrectionList &aCorrL);
protected:
	bool m_bTimeCut;
	char m_nTimeCut;
};

#endif // !defined(AFX_ARRIVALLIST_H__4D7E4401_ED55_11D3_92DC_0040954019F4__INCLUDED_)
