// Arrival.h: interface for the CArrival class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRIVAL_H__F878B641_C503_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_ARRIVAL_H__F878B641_C503_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CArrival : public CStaNoObject
{
public:
	void CorrectStartGross(const CArrival&);
	void CorrectStartNet(const CArrival&);
	CClassification* m_pBunch;
	CTeam* m_pTeam;
	unsigned short m_bonus;
	unsigned short m_penalty;
	DWORD m_sumRank;
	DWORD m_thousandth;
	WORD m_rank;
	WORD m_order;
	WORD m_points;
	DWORD m_units;
	DWORD m_unitsAtArrival;							// TimeTrial specific
	DWORD m_unitsAtStart;							// TimeTrial specific
	
	CArrival();
	CArrival(const CArrival &aArrival);
	virtual ~CArrival();
	CArrival& operator=(const CArrival &aArriv);
	CArrival& operator=(const CCorrection &aCorr);
	CArrival& operator+(const CArrival &aArrival);

	void	Serialize(CArchive & ar);

	void	SetStart(DWORD aStarttime);				// TimeTrial specific
	DWORD	SetArrival(DWORD aArrivaltime, bool anticipateTime=false, DWORD anticipatedTime=0);			// TimeTrial specific
};

#endif // !defined(AFX_ARRIVAL_H__F878B641_C503_11D2_B376_0040954019F4__INCLUDED_)
