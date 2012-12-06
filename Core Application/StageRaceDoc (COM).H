// StageRaceDoc.h : Declaration of the CStageRaceDoc

#ifndef __CSTAGERACEDOC_H_
#define __CSTAGERACEDOC_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStageRaceComDoc
class ATL_NO_VTABLE CStageRaceComDoc : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStageRaceComDoc, &CLSID_StageRaceDoc>,
	public IStageRaceDoc
{
public:
	CStageRaceComDoc()
	{
		m_pDocument = NULL;
	}
	virtual ~CStageRaceComDoc()
	{
		// Decrement the number of opened COM documents of this type
		m_pDocument->Release();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STAGERACECOMDOC)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStageRaceComDoc)
	COM_INTERFACE_ENTRY(IStageRaceDoc)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

// IStageRaceDoc
public:
	STDMETHOD(GetFullStageName)(int nFS, BSTR* pname);
	HRESULT Init(BSTR title);
	STDMETHOD(GetCompetitor)(/*[in]*/unsigned short nStaNo, /*[in,out]*/BSTR* pname, /*[in,out]*/BSTR* pteam);
	STDMETHOD(CompetitorExists)(/*[in]*/unsigned short nStaNo, /*[out]*/BOOL* bExists);
	STDMETHOD(GetHalfStageName)(/*[in]*/int nFS, /*[in]*/int nHS, /*[in,out]*/BSTR* pname);
	STDMETHOD(GetCountFullStages)(/*[in,out]*/int* pnCount);
	STDMETHOD(GetCountHalfStages)(/*[in]*/int nFS, /*[in,out]*/int* pnCount);
	STDMETHOD(GetHalfStage)(/*[in]*/int nFS, /*[in]*/int nHS, /*[out]*/ISRHalfStage** ppHS);
protected:
	CStageRaceDoc* m_pDocument;
};

#endif //__CSTAGERACEDOC_H_
