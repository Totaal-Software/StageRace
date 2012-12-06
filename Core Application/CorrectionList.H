// CorrectionList.h: interface for the CCorrectionList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRECTIONLIST_H__96D11FF4_1A69_4906_94CF_0DADF36D59E9__INCLUDED_)
#define AFX_CORRECTIONLIST_H__96D11FF4_1A69_4906_94CF_0DADF36D59E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCorrectionList : public CStaNoObjectList  
{
public:
	CCorrectionList();
	CCorrectionList(const CCorrectionList &aCorrL);
	CCorrectionList& operator =(const CArrivalList &aArrL);
	CCorrectionList& operator =(const CCorrectionList &aCorrL);
	void Insert(CCorrection &objCorr);
	virtual bool IterateSorted( DWORD& nState, CCorrection& objCorr) const;
	virtual void Serialize(CArchive &ar);
	virtual void Iterate( POSITION& rNextPosition, CCorrection& rValue ) const;
	CCorrection GetAt( WORD nStaNo ) const;
};

#endif // !defined(AFX_CORRECTIONLIST_H__96D11FF4_1A69_4906_94CF_0DADF36D59E9__INCLUDED_)
