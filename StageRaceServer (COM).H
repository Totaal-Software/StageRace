// StageRaceServer.h : Declaration of the CStageRaceServer

#ifndef __STAGERACESERVER_H_
#define __STAGERACESERVER_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStageRaceServer
class ATL_NO_VTABLE CStageRaceServer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStageRaceServer, &CLSID_StageRaceServer>,
	public IStageRaceServer
{
public:
	CStageRaceServer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STAGERACESERVER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStageRaceServer)
	COM_INTERFACE_ENTRY(IStageRaceServer)
END_COM_MAP()

// IStageRaceServer
public:
	STDMETHOD(GetActiveDocName)(BSTR* pTitle);
	STDMETHOD(GetDocument)(BSTR title, IStageRaceDoc** ppDoc);
	STDMETHOD(SendMessage)(BSTR user, BSTR message);
	STDMETHOD(EnumerateDocuments)(VARIANT* pDocs);
};

#endif //__STAGERACESERVER_H_
