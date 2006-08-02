// TeamClassification.h: interface for the CTeamClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEAMCLASSIFICATION_H__BA6C0900_07E3_11D4_92DE_0040954019F4__INCLUDED_)
#define AFX_TEAMCLASSIFICATION_H__BA6C0900_07E3_11D4_92DE_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTeamClassification : public CClassification
{
public:
	void Publish( int nFS, int nHS );
	bool CalculateGeneralFromStage(CArrival *pArr);
	void StoreClassification();
	CTeamClassification(CStageRaceDoc *pDoc);
	void LoadClassification( CClassification* pClass, bool bOneForTeamsClass );

private:
	bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);
	CMap<CTeam*,CTeam*,CArrival,CArrival&> m_store;
};

#endif // !defined(AFX_TEAMCLASSIFICATION_H__BA6C0900_07E3_11D4_92DE_0040954019F4__INCLUDED_)
