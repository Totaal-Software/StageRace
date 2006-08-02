// ClimbsClassification.h: interface for the CClimbsClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIMBSCLASSIFICATION_H__F49BC965_A092_4199_B82A_5A223084542A__INCLUDED_)
#define AFX_CLIMBSCLASSIFICATION_H__F49BC965_A092_4199_B82A_5A223084542A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClimbsClassification : public CSprintClassification  
{
public:
	bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);
	CClimbsClassification(CStageRaceDoc *pDoc);
	virtual ~CClimbsClassification();

};

#endif // !defined(AFX_CLIMBSCLASSIFICATION_H__F49BC965_A092_4199_B82A_5A223084542A__INCLUDED_)
