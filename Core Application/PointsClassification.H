// PointsClassification.h: interface for the CPointsClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTSCLASSIFICATION_H__F396F739_B629_4A15_8CFE_F7B01109610F__INCLUDED_)
#define AFX_POINTSCLASSIFICATION_H__F396F739_B629_4A15_8CFE_F7B01109610F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointsClassification : public CSprintClassification  
{
public:
	void Publish(int nFS, int nHS);
	CPointsClassification(CStageRaceDoc* pDoc);

private:
	virtual bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);
};

#endif // !defined(AFX_POINTSCLASSIFICATION_H__F396F739_B629_4A15_8CFE_F7B01109610F__INCLUDED_)
