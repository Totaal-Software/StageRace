// FullStage.h: interface for the CFullStage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FULLSTAGE_H__55C51AA2_C40F_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_FULLSTAGE_H__55C51AA2_C40F_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFullStage : public CObject  
{
public:
	CCommunique m_communique;
	CString m_date;
	CList < CHalfStage, CHalfStage& > m_halfStages;

	CFullStage();
	virtual ~CFullStage();

	CFullStage& operator=( CFullStage& aFullStage );
	CFullStage& operator=( CFullStageTrialDat& aTrialDat);

	void Serialize(CArchive& ar);
	
	void AddHalfStage(CHalfStage* aNewOne);
	int CountHalfStages() const;
	int Edit(HANDLE hSemaphore=NULL);
};

#endif // !defined(AFX_FULLSTAGE_H__55C51AA2_C40F_11D2_B376_0040954019F4__INCLUDED_)
