#if !defined(AFX_LISTVIEWTeams_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_)
#define AFX_LISTVIEWTeams_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListViewTeams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListViewTeams view

class CListViewTeams : public CListViewCompetitorsTeams
{
	DECLARE_DYNCREATE(CListViewTeams)

public:
	UINT GetResourceID();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewTeams)
	protected:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT EditFieldLength(int);
	virtual EDIT_TYPE EditAllowedOnSubitem(int);
	virtual void UpdateField(LV_ITEM* plvItem);
	CListViewTeams();
	// Drawing of single items
	void DrawTeam(const CTeam* pTeam, int nItem = -1 );
	void EnsureVisible(const CTeam* pTeam);
	void ClearTeam(const CTeam* pTeam);
	int FindTeam(const CTeam* pTeam);

	// Ensuring storing of settings

	// Sorting
	bool SortItems(int nCol, bool bAscending, int low=0, int high=-1);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CListViewTeams)
	afx_msg void OnEditEditselection();
	afx_msg void OnDestroy();
	afx_msg void OnEditDelete();
	afx_msg void OnInsertTeam();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWTeams_H__D41C10AC_A224_4212_9791_BA5CED55E774__INCLUDED_)
