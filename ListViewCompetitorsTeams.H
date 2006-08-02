#if !defined(AFX_LISTVIEWCOMPETITORSTEAMS_H__E39D6274_626C_4E5A_B17E_1BDF636FA44D__INCLUDED_)
#define AFX_LISTVIEWCOMPETITORSTEAMS_H__E39D6274_626C_4E5A_B17E_1BDF636FA44D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListViewCompetitorsTeams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListViewCompetitorsTeams view

#define BARSCOLOR RGB(255,255,220)
class CListViewCompetitorsTeams : public CListView
{
public:
	enum EDIT_TYPE
	{
		EDIT_NOT,
		EDIT_INLINE,
		EDIT_CHECK
	};

protected:
	CListViewCompetitorsTeams();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListViewCompetitorsTeams)
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewCompetitorsTeams)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	void StoreSettings(CString key);
	void RestoreSettings(CString key);
	CImageList m_imageList;
	CSubEdit m_editWnd;
	int m_subitem;
	int m_edititem;

	virtual bool EditGetBool(int,int) { return false; };
	virtual void EditSetBool(int,int,bool) {};
	virtual bool EditNumeric(int) { return false; };
	virtual UINT EditFieldLength(int) { return 0; };
	virtual void UpdateField(LV_ITEM*) {};
	virtual EDIT_TYPE EditAllowedOnSubitem(int) { return EDIT_NOT; };
	virtual bool SortItems(int nCol, bool bAscending, int low=0, int high=-1) { return false; };
	int m_nSelectedCount;
	// Sorting
	int m_nSortedColumn;
	bool m_bSortedAsc;
	// Our own - casted - document pointer
	CStageRaceDoc* m_pDoc;
	// Repeating insert new
	bool m_bRepeatedly;
	// Show options
	bool m_bGrid;
	bool m_bBars;

	//{{AFX_MSG(CListViewCompetitorsTeams)
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditEditselection(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInsertRepeatedly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditSelectall();
	afx_msg void OnInsertRepeatedly();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNextPane();
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnViewBars();
	afx_msg void OnUpdateViewBars(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCleanupcompetitors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWCOMPETITORSTEAMS_H__E39D6274_626C_4E5A_B17E_1BDF636FA44D__INCLUDED_)
