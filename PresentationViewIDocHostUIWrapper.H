#if !defined(AFX_PRESENTATIONVIEWWRAPPER_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_PRESENTATIONVIEWWRAPPER_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPresentationViewIDocHostUIWrapper : public IDocHostUIHandler
{
public:
	CPresentationViewIDocHostUIWrapper(CPresentationView *pWrappee);

private:
	CPresentationView *m_pWrappee;

protected:
	// IUnknown members
	STDMETHOD(QueryInterface)(const struct _GUID &,void **)
		{ return E_NOTIMPL; }
	STDMETHOD_(ULONG,AddRef)(void)
		{ return E_NOTIMPL; }
	STDMETHOD_(ULONG,Release)(void)
		{ return E_NOTIMPL; }
	// IDocHostUIHandler members
	STDMETHOD(ShowContextMenu)(unsigned long,struct tagPOINT *,struct IUnknown *,struct IDispatch *);
	STDMETHOD(GetHostInfo)(struct _DOCHOSTUIINFO * pInfo)
	{
		pInfo->cbSize  = sizeof(DOCHOSTUIINFO);
		pInfo->dwFlags = 0;
		return S_OK;
	}
	STDMETHOD(ShowUI)(unsigned long,struct IOleInPlaceActiveObject *,struct IOleCommandTarget *,struct IOleInPlaceFrame *,struct IOleInPlaceUIWindow *)
		{ return E_NOTIMPL; }
	STDMETHOD(HideUI)(void)
		{ return E_NOTIMPL; }
	STDMETHOD(UpdateUI)(void)
		{ return E_NOTIMPL; }
	STDMETHOD(EnableModeless)(int)
		{ return E_NOTIMPL; }
	STDMETHOD(OnDocWindowActivate)(int)
		{ return E_NOTIMPL; }
//	virtual HRESULT OnDocWindowActivate(BOOL fActivate)
//		{ return E_NOTIMPL; }
	STDMETHOD(OnFrameWindowActivate)(int)
		{ return E_NOTIMPL; }
//	virtual HRESULT OnFrameWindowActivate(BOOL fActivate)
//		{ return E_NOTIMPL; }
	STDMETHOD(ResizeBorder)(const struct tagRECT *,struct IOleInPlaceUIWindow *,int)
		{ return E_NOTIMPL; }
	STDMETHOD(TranslateAcceleratorA)(struct tagMSG *,const struct _GUID *,unsigned long)
		{ return E_NOTIMPL; }
	STDMETHOD(TranslateAcceleratorW)(struct tagMSG *,const struct _GUID *,unsigned long)
		{ return E_NOTIMPL; }
	STDMETHOD(GetOptionKeyPath)(unsigned short ** ,unsigned long)
		{ return E_NOTIMPL; }
	STDMETHOD(GetDropTarget)(struct IDropTarget *,struct IDropTarget ** )
		{ return E_NOTIMPL; }
	STDMETHOD(GetExternal)(struct IDispatch ** ppDispatch)
	{
		*ppDispatch = m_pWrappee;
		return S_OK;
	}
	STDMETHOD(TranslateUrl)(unsigned long,unsigned short *,unsigned short ** )
		{ return E_NOTIMPL; }
	STDMETHOD(FilterDataObject)(struct IDataObject *,struct IDataObject ** )
		{ return E_NOTIMPL; }

	STDMETHOD(GetOptionKeyPath)(LPOLESTR *,DWORD)
		{ return E_NOTIMPL; }
	STDMETHOD(TranslateUrl)(DWORD,OLECHAR *,OLECHAR **)
		{ return E_NOTIMPL; }
};

#endif // !defined(AFX_PRESENTATIONVIEWWRAPPER_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_)
