// EditCommunique.h : header file
//
#if !defined(AFX_EDITCOMMUNIQUE_H__10439C00_BE4A_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_EDITCOMMUNIQUE_H__10439C00_BE4A_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditCommunique dialog

class CEditCommunique : public CStageRaceWnd<cdxCDynamicDialog>
{
// Construction
public:
	virtual  ~CEditCommunique();
	int m_nFS;
	int m_nHS;
	CEditCommunique(const CStageRaceDoc* pDoc);
	CEditCommunique& operator =(const CCommunique &aComm);
// Dialog Data
	//{{AFX_DATA(CEditCommunique)
	enum { IDD = IDD_COMMUNIQUE };
	CString	m_contents;
	CString	m_title;
	CString	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCommunique)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   CFont m_contentsfont;
	void OnCancel();
	void UpdatePreview();
	void UpdateMenu(CMenu*);
	bool m_bChanged;
	const CStageRaceDoc* m_pDoc;
	CPreviewCommunique* m_pPreviewWnd;
	void InsertOrderTeamVehicles(BOOL bGeneral=FALSE);

	// Generated message map functions
	//{{AFX_MSG(CEditCommunique)
	virtual BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnChange();
	afx_msg void OnViewPreview();
	afx_msg void OnUpdateViewPreview(CCmdUI* pCmdUI);
	afx_msg void OnInsertOrderteamcaptainvehiclesOngeneralclassification();
	afx_msg void OnUpdateInsertOrderteamcaptainvehiclesOngeneralclassification(CCmdUI* pCmdUI);
	afx_msg void OnInsertOrderteamcaptainvehiclesOnstageclassification();
	afx_msg void OnUpdateInsertOrderteamcaptainvehiclesOnstageclassification(CCmdUI* pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnInsertPagebreak();
	afx_msg void OnInsertItem();
	afx_msg void OnEditApplystyletoselectionBold();
	afx_msg void OnEditApplystyletoselectionItalic();
	afx_msg void OnEditApplystyletoselectionUnderlined();
	afx_msg void OnUpdateEditApplystyletoselection(CCmdUI* pCmdUI);
	afx_msg void OnInsertParagraphtitle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCOMMUNIQUE_H__10439C00_BE4A_11D3_92DA_0040954019F4__INCLUDED_)
