#if !defined(AFX_IDVIEW_H__EBF9CD0E_8C34_46DD_A773_763A8791BDC0__INCLUDED_)
#define AFX_IDVIEW_H__EBF9CD0E_8C34_46DD_A773_763A8791BDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IdView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIdView form view

class CIdView : public CFormView
{
	DECLARE_DYNCREATE(CIdView)
protected:
	//{{AFX_DATA(CIdView)
	enum { IDD = IDD_IDVIEW };
	CColorStaticST	m_ctrlId;
	//}}AFX_DATA

public:
	CId* Get();
	void Reset();
	void Set(CId *pId);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIdView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
	CId* m_pId;
	CIdView();           // protected constructor used by dynamic creation
	void SetBar();
	void Enable();
	void Disable();
	void EnableButton();
	void DisableButton();
	void OnInitialUpdate();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIdView)
	afx_msg void OnDeltaposIdspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditPublishPlus();
	afx_msg void OnUpdateEditPublishPlus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPublishMinus(CCmdUI* pCmdUI);
	afx_msg void OnEditPublishMinus();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDVIEW_H__EBF9CD0E_8C34_46DD_A773_763A8791BDC0__INCLUDED_)
