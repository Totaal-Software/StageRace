// MostAggressiveClassification.h: interface for the CMostAggressiveClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOSTAGGRESSIVECLASSIFICATION_H__41C5C646_89CF_4083_ABFB_3D6555DFCE21__INCLUDED_)
#define AFX_MOSTAGGRESSIVECLASSIFICATION_H__41C5C646_89CF_4083_ABFB_3D6555DFCE21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMostAggressiveClassification : public CSprintClassification  
{
public:
	void Publish(int nFS, int nHS);
	CMostAggressiveClassification(CStageRaceDoc* pDoc);

private:
	virtual bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);
};

#endif // !defined(AFX_MOSTAGGRESSIVECLASSIFICATION_H__41C5C646_89CF_4083_ABFB_3D6555DFCE21__INCLUDED_)
