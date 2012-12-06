// SprintClassification.h: interface for the CSprintClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SprintCLASSIFICATION_H__DF01CE40_FA0E_11D3_92DD_0040954019F4__INCLUDED_)
#define AFX_SprintCLASSIFICATION_H__DF01CE40_FA0E_11D3_92DD_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Note that this class and file used to be named PointsClassification
// Changed as of 2003, 2, 0, 445
class CSprintClassification : public CClassification
{
public:
	bool IsUnOfficial();
	bool IsOfficial();
	void FinishClassification();
	void AddCompetitor(CArrival &aArr, CClassification* pLastResort, int nFS, int nHS);
	CSprintClassification(CStageRaceDoc* pDoc);

private:
	virtual bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);
protected:
	bool InsertHereLastResort(CArrival &objTest, CArrival &objSubj);
	bool m_bUnofficial;
	bool CalculateGeneralFromStage( CArrival* pArr );
	int m_nFS;
	int m_nHS;
	CClassification* m_pLastResort;

};

#endif // !defined(AFX_SprintCLASSIFICATION_H__DF01CE40_FA0E_11D3_92DD_0040954019F4__INCLUDED_)
