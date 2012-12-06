#if !defined(AFX_CHILDFRAME_H__0216C69E_18CA_4F66_9902_FC31639FD59F__INCLUDED_)
#define AFX_CHILDFRAME_H__0216C69E_18CA_4F66_9902_FC31639FD59F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
protected:
	CChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	CWnd* GetActiveDetailView();
	void DoInitialMaximize();
	UINT GetResourceID();
	CFormViewDetailsEmpty*	ShowViewDetailsEmpty();
	CListViewTeams*			ShowViewListTeams();
	CListViewCompetitors*	ShowViewListCompetitors();
	CPresentationView*		ShowViewPresentation();
	CPresentationTextView*	ShowViewPresentationText();
	void SetActivePaneDetailView();
	void SetActivePaneTreeViewMain();
protected:
	static BOOL m_bDoneInitialMaximize;
	BOOL m_bDisplayTreeViewMainToolBar;
	BOOL m_bDisplayConfigureToolBar;
	void SetToolbar(int nIDR);
	void SwitchToolbar();
	int AddToolbar (int nIDR);
	int m_nFormViewDetailsEmpty;
	int m_nListViewCompetitors;
	int m_nListViewTeams;
	int m_nPresentationView;
	int m_nPresentationViewText;
	CSplitterWndHidable		m_wndSplitterColumns;
	CSplitterWndFixed		m_wndSplitterLeftColumn;
	virtual ~CChildFrame();

	CReBar		m_wndReBar;
	CToolBar    m_wndGenerateToolBar;
	CToolBar    m_wndTreeViewMainToolBar;
	CToolBar	m_wndConfigureToolBar;
	// Members for automatic changing tool bar
	// Every view can get his own additional tool bar
	CArray<CToolBar *, CToolBar *>
				m_arrayToolbars;	// holds pointers to loaded toolbar windows
	CArray<int,int>
				m_arrayToolbarIDs;	// hold IDs of loaded toolbars

	// Generated message map functions
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnViewTreeviewmain();
	afx_msg void OnUpdateViewTreeviewmain(CCmdUI* pCmdUI);
	afx_msg void OnViewTlbarConfigure();
	afx_msg void OnUpdateViewTlbarConfigure(CCmdUI* pCmdUI);
	afx_msg void OnViewTlbarTreeviewmain();
	afx_msg void OnUpdateViewTlbarTreeviewmain(CCmdUI* pCmdUI);
	afx_msg void OnViewTlbarGenerate();
	afx_msg void OnUpdateViewTlbarGenerate(CCmdUI* pCmdUI);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRAME_H__0216C69E_18CA_4F66_9902_FC31639FD59F__INCLUDED_)
