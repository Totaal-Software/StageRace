// DistributedClassification.h: interface for the CDistributedClassification class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISTRIBUTEDCLASSIFICATION_H__54906AE0_E2E8_4570_83F3_D80B09DF96BB__INCLUDED_)
#define AFX_DISTRIBUTEDCLASSIFICATION_H__54906AE0_E2E8_4570_83F3_D80B09DF96BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDistributedClassification  
{
public:
	const CArrivalList* GenerateStartingOrder(CStaNoObjectList* pAvail1, CStaNoObjectList* pAvail2) const;
	const CClassification* GenerateClassification() const;
	CDistributedClassification(int nFS, int nHS, CStageRaceDoc* pDoc);

protected:
	int m_nFS;
	int m_nHS;
	CStageRaceDoc* m_pDoc;
};

#endif // !defined(AFX_DISTRIBUTEDCLASSIFICATION_H__54906AE0_E2E8_4570_83F3_D80B09DF96BB__INCLUDED_)
