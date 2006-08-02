// Classification.h: interface for the CClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASSIFICATION_H__0E0C6320_E7EB_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_CLASSIFICATION_H__0E0C6320_E7EB_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClassification : public CObject  
{
public:
	CClassification& operator =(const CClassification & cl);
	CClassification(CClassification & cl);
	void ScrambleForStartingOrder();
	void PublishGeneral( int nFS, int nHS, bool bGeneral, bool bMask1, bool bMask2, bool bMask3, bool bMask4, bool bMask5, bool bMask6, bool bMask7, bool bMask8, bool bMask9, bool bMask10 );
	void PublishClass( int nFS, int nHS );
	virtual bool CalculateGeneralFromStage( CArrival* pArr );
	void ClearAll();
	void StoreClassification();
	virtual void AddCompetitor( CArrival& aArr, bool bExcludeStage = false );

	CClassification(CStageRaceDoc* pDoc);
	virtual ~CClassification();

	CList<CArrival,CArrival&> m_classification;
	CList<CArrival,CArrival&> m_generalClassification;
protected:
	void DoGeneral(CArrival &aArr);
	void DoClass(CArrival &aArr);

	virtual bool InsertHere(CArrival &objTest, CArrival &objSubj, bool bRankOnly);

	CStageRaceDoc* m_pDoc;
	bool m_firstClass;
	CMap<WORD,WORD&,CArrival,CArrival&> m_store;

};

#endif // !defined(AFX_CLASSIFICATION_H__0E0C6320_E7EB_11D3_92DC_0040954019F4__INCLUDED_)
