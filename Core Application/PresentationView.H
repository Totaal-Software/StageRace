///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: PresentationView.h
// Description: Interface file for the CPresentationView class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRESENTATIONVIEW_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_PRESENTATIONVIEW_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPresentationView html view

class CPresentationView : public CHtmlView, public IDispatch
{
	DECLARE_DYNCREATE( CPresentationView )
protected:
	// IUnknown members
	STDMETHOD(QueryInterface)(const struct _GUID &,void **)
		{ return E_NOTIMPL; }
	STDMETHOD_(ULONG,AddRef)(void)
		{ return E_NOTIMPL; }
	STDMETHOD_(ULONG,Release)(void)
		{ return E_NOTIMPL; }
	// IDispatch members
	STDMETHOD(GetTypeInfoCount)(unsigned int *)
		{ return E_NOTIMPL; }
	STDMETHOD(GetTypeInfo)(unsigned int,unsigned long,struct ITypeInfo **)
		{ return E_NOTIMPL; }
	STDMETHOD(GetIDsOfNames)(const IID &, LPOLESTR *, UINT, LCID, DISPID *)
		{ return E_NOTIMPL; }
	STDMETHOD(GetIDsOfNames)(const struct _GUID &,unsigned short **,unsigned int,unsigned long,long *)
		{ return E_NOTIMPL; }
	STDMETHOD(Invoke)(long,const struct _GUID &,unsigned long,unsigned short,struct tagDISPPARAMS *,struct tagVARIANT *,struct tagEXCEPINFO *,unsigned int *)
		{ return E_NOTIMPL; }

protected:
	CPresentationView(); // protected constructor used by dynamic creation
	~CPresentationView();
	CString m_cLastFile;
	CTime m_tLastFile;
	CString m_cTitle;
	long m_scrollheight;
	IDocHostUIHandler* m_pHandler;

public:
	void Navigate( LPCTSTR URL);
	bool Navigate( CEventItem* pEI );
	void NavigateLicense();
	UINT GetResourceID();
	//{{AFX_DATA(CPresentationView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPresentationView)
	public:
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
	bool CanZoom(bool in = true);
	void Zoom( bool in = true );
//note: this seems to have been disabled quite a while ago in the .cpp; the .h was forgotten
//	HRESULT OnGetOptionKeyPath(LPOLESTR *, DWORD);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPresentationView)
	afx_msg void OnPageSetup();
	afx_msg void OnFind();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewInfo();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectall();
	afx_msg void OnUpdateAnchorItem(CCmdUI* pCmdUI);
	afx_msg void OnViewFontZoomin();
	afx_msg void OnViewFontZoomout();
	afx_msg void OnUpdateViewFontZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFontZoomout(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNextPane();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRESENTATIONVIEW_H__7245E180_AF16_11D3_92DA_0040954019F4__INCLUDED_)
