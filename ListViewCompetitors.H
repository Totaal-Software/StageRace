#if !defined(AFX_LISTVIEWCOMPETITORS_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_)
#define AFX_LISTVIEWCOMPETITORS_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListViewCompetitors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitors view

class CListViewCompetitors : public CListViewCompetitorsTeams
{
	DECLARE_DYNCREATE(CListViewCompetitors)

public:
	UINT GetResourceID();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewCompetitors)
	protected:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool IsSpare(int iItem);
	virtual void EditSetBool(int,int,bool);
	virtual bool EditGetBool(int,int);
	void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	bool EditNumeric(int);
	UINT EditFieldLength(int);
	virtual EDIT_TYPE EditAllowedOnSubitem(int);
	void DrawAll();
	virtual void UpdateField(LV_ITEM*);
	CListViewCompetitors();
	// Keep track of pasting mode
	bool m_bPasteWithStaNos;
	// Drawing of single items
	void DrawCompetitor(const CCompetitor* pCompetitor, int nItem = -1 );
	void EnsureVisible( DWORD nStaNo );
	void ClearCompetitor( DWORD nStaNo );
	int FindCompetitor( DWORD nStaNo );

	// Ensuring storing of settings

	// Sorting
	bool SortItems(int nCol, bool bAscending, int low=0, int high=-1);
	// Check if the ctrl key was pressed
	bool m_bCtrlKey;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CListViewCompetitors)
	afx_msg void OnEditEditselection();
	afx_msg void OnEditApplymask();
	afx_msg void OnEditDelete();
	afx_msg void OnInsertCompetitor();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCut();
	afx_msg void OnEditPasteWithstanos();
	afx_msg void OnUpdateEditPasteWithstanos(CCmdUI* pCmdUI);
	afx_msg void OnEditSwapcompetitors();
	afx_msg void OnUpdateEditSwapcompetitors(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateEditApplymask(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWCOMPETITORS_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_)
