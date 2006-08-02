#if !defined(AFX_LISTVIEWACTIVEDOC_H__40F57F78_8194_492B_B9A6_5D47CFEC29E4__INCLUDED_)
#define AFX_LISTVIEWACTIVEDOC_H__40F57F78_8194_492B_B9A6_5D47CFEC29E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListViewActiveDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListViewActiveDoc view

class CListViewActiveDoc : public CListView
{
	DECLARE_DYNCREATE(CListViewActiveDoc)

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListViewActiveDoc)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
	// Selected state image (list)
	CImageList m_imageListState;
	// Our own - casted - document pointer
	CActiveDocTracker* m_pDoc;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	//{{AFX_MSG(CListViewActiveDoc)
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditSelect();
	afx_msg void OnUpdateEditSelect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTVIEWACTIVEDOC_H__40F57F78_8194_492B_B9A6_5D47CFEC29E4__INCLUDED_)
