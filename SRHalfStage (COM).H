// SRHalfStage.h : Declaration of the CSRHalfStage

#ifndef __SRHALFSTAGE_H_
#define __SRHALFSTAGE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSRHalfStage
class ATL_NO_VTABLE CSRHalfStage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSRHalfStage, &CLSID_SRHalfStage>,
	public ISRHalfStage
{
public:
	CSRHalfStage()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SRHALFSTAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSRHalfStage)
	COM_INTERFACE_ENTRY(ISRHalfStage)
END_COM_MAP()

// ISRHalfStage
public:
	STDMETHOD(SetTimingIdle)();
	STDMETHOD(EnumerateStarts)(VARIANT * pStarts);
	STDMETHOD(ResetArrival)(unsigned int nStaNo);
	STDMETHOD(GetStart)(unsigned short nStaNo, unsigned short *nOrder, unsigned long *nUnits);
	STDMETHOD(GetArrivalByTime)(unsigned long nUnits, unsigned short *nStaNo, unsigned short *nRank, unsigned long *pnUnits);
	STDMETHOD(GetArrivalByStaNo)(unsigned short nStaNo, unsigned short *nRank, unsigned long *nUnits);
	STDMETHOD(GetArrivalByRank)(unsigned short nRank, unsigned short *nStaNo, unsigned long *nUnits);
	STDMETHOD(SetArrival)(unsigned short nStaNo, unsigned short nRank, unsigned long nUnits);
	STDMETHOD(SetArrivalByRank)(unsigned short nStaNo, unsigned short nRank);
	STDMETHOD(SetArrivalByTime)(unsigned short nStaNo, unsigned long nUnits);
	HRESULT Init(CStageRaceDoc*, int nFS, int nHS);
protected:
	CHalfStage* m_pHalfStage;
	CStageRaceDoc* m_pDocument;
	int m_nHalfStage;
	int m_nFullStage;
};

#endif //__SRHALFSTAGE_H_
