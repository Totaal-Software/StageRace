#if !defined(AFX_ACTIVEDOCTRACKER_H__1DEABC9A_0BB0_4C0B_B105_007A9BD78F93__INCLUDED_)
#define AFX_ACTIVEDOCTRACKER_H__1DEABC9A_0BB0_4C0B_B105_007A9BD78F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActiveDocTracker.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CActiveDocTracker document

class CActiveDocTracker : public CDocument
{
public:
	CActiveDocTracker();
	~CActiveDocTracker();
	DECLARE_DYNCREATE(CActiveDocTracker)
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveDocTracker)
	public:
	virtual void OnChangedViewList();
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	BOOL PreTranslateMessage(MSG* pMsg);
	// Getters
	const CStageRaceDoc* GetSelected();
	const CStageRaceDoc* GetAt(UINT);
	UINT GetCount();
	// Setters
	void Select(CStageRaceDoc*);
	void Close(CStageRaceDoc*);
	void Open(CStageRaceDoc*);

	//{{AFX_MSG(CActiveDocTracker)
	afx_msg void OnViewListviewactivedoc();
	afx_msg void OnUpdateViewListviewactivedoc(CCmdUI* pCmdUI);
	afx_msg void OnDisabled();
	afx_msg void OnUpdateDisabled(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CStageRaceDoc* m_pSelection;
	CArray<CStageRaceDoc*,CStageRaceDoc*> m_arDocs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEDOCTRACKER_H__1DEABC9A_0BB0_4C0B_B105_007A9BD78F93__INCLUDED_)
