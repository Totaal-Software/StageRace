// ListTimeTrialArrivalNet.h: interface for the CListTimeTrialArrivalNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTTIMETRIALARRIVALNET_H__18343B0C_4CD5_421C_9841_DA4DDD811286__INCLUDED_)
#define AFX_LISTTIMETRIALARRIVALNET_H__18343B0C_4CD5_421C_9841_DA4DDD811286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListTimeTrialArrivalNet : public CListTimeTrialArrivalGross
{
public:
	CListTimeTrialArrivalNet( int nAccuracy,
		const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		const CCompetitorList* pListCompetitor=NULL );
	BOOL OnInitDialog();
protected:
	virtual void SetUnits(CArrival *, DWORD);
};

#endif // !defined(AFX_LISTTIMETRIALARRIVALNET_H__18343B0C_4CD5_421C_9841_DA4DDD811286__INCLUDED_)
