#if !defined(AFX_TREEVIEWMAIN_H__D0140AC8_300D_4580_AA20_AA251294BCF5__INCLUDED_)
#define AFX_TREEVIEWMAIN_H__D0140AC8_300D_4580_AA20_AA251294BCF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeViewMain.h : header file
//

class CTreeViewMain : public CTreeView
{
protected:
	void ContextTree(CPoint point);
	void ExpandBranch( HTREEITEM hti );
	CEventItem GetEventItem(HTREEITEM hti);
	struct DRAGDROP
	{
		CImageList* m_pImageListDrag;
		BOOL		m_bDragging;
		HTREEITEM	m_hItemDrag;
	} m_DragDrop;

	void ContextItem(CPoint point);
	void ContextState(CPoint point);
	void UpdateCountTeams();
	void UpdateCountCompetitors();
	HTREEITEM GetStageItem(int nFS, int nHS, TREEITEMS tiType);
	HTREEITEM GetStageItem(TREEITEMS tiType);
	HTREEITEM GetStage( int nFS=0, int nHS=0 );
 	HTREEITEM GetStageItem( HTREEITEM hParent, TREEITEMS tiItem );
	void ItemDisplay();
	void ItemSwitch();
	CTreeViewMain();
	DECLARE_DYNCREATE(CTreeViewMain)
	CImageList m_imageList;
	CImageList m_imageListState;
	bool IsItemChecked(HTREEITEM hItem);
	CEventItem	m_eiSelected;
	bool m_bViewCsv;
	CHalfStage*	m_pHalfStage;
	BOOL		m_bRedrawMode;
	// Our own - casted - document pointer
	CStageRaceDoc* m_pDoc;

	afx_msg bool OnEditEditselection();
	//{{AFX_MSG(CTreeViewMain)
	afx_msg void OnConfigureInsertFullstage();
	afx_msg void OnConfigureInsertHalfstage();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnConfigureConfigure();
	afx_msg void OnVoidEditEditselection();
	afx_msg void OnConfigureDelete();
	afx_msg void OnInsertSignouts();
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertCommunique();
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsertCommunique(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsertSignouts(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditEditselection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigureInsertHalfStage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigureDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigureConfigure(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewCsv(CCmdUI* pCmdUI);
	afx_msg void OnToolsExportoptic();
	afx_msg void OnUpdateToolsExportoptic(CCmdUI* pCmdUI);
	afx_msg void OnToolsExportchronx();
	afx_msg void OnUpdateToolsExportchronx(CCmdUI* pCmdUI);
	afx_msg void OnEditPublish();
	afx_msg void OnUpdateEditPublish(CCmdUI* pCmdUI);
	afx_msg void OnNextPane();
	afx_msg void OnEditCompetitors();
	afx_msg void OnUpdateEditCompetitors(CCmdUI* pCmdUI);
	afx_msg void OnEditTeams();
	afx_msg void OnUpdateEditTeams(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditCopytoselectiondlg();
	afx_msg void OnUpdateEditCopytoselectiondlg(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnArrivalFunctionsCheck();
	afx_msg void OnArrivalFunctionsGroupt1();
	afx_msg void OnArrivalFunctionsGroupt2();
	afx_msg void OnArrivalFunctionsGroupt3();
	afx_msg void OnArrivalFunctionsImport();
	afx_msg void OnArrivalFunctionsRemove1xseconds();
	afx_msg void OnArrivalFunctionsRemovegaps();
	afx_msg void OnUpdateArrivalFunctionsCheck(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsGroupt1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsGroupt2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsGroupt3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsImport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsRemove1xseconds(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArrivalFunctionsRemovegaps(CCmdUI* pCmdUI);
	afx_msg void OnGenerateSelection();
	afx_msg void OnUpdateGenerateSelection(CCmdUI* pCmdUI);
	afx_msg void OnGenerateReadonly();
	afx_msg void OnUpdateGenerateReadonly(CCmdUI* pCmdUI);
	afx_msg void OnToolsEditpubl();
	afx_msg void OnUpdateToolsEditpubl(CCmdUI* pCmdUI);
	afx_msg void OnViewExpand();
	afx_msg void OnViewCsv();
	afx_msg void OnToolsExportttware();
	afx_msg void OnUpdateToolsExportttware(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	UINT GetResourceID();
	void CheckItem();
	HTREEITEM DrawHalfStage( CHalfStage* pHalfStage, int nFS, int nHS, HTREEITEM hParent, HTREEITEM hInsertAfter=TVI_LAST );
	void DrawTreeFromScratch();
	UINT InitDetermineState( CId* pId);
	CStageRaceDoc* GetDocument();
	CIdView* m_pIdView;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeViewMain)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
	
private:
	bool ShouldDrag(CEventItem&);
};

#ifndef _DEBUG  // debug version in TreeViewMain.cpp
inline CStageRaceDoc* CTreeViewMain::GetDocument()
   { return (CStageRaceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVIEWMAIN_H__D0140AC8_300D_4580_AA20_AA251294BCF5__INCLUDED_)
