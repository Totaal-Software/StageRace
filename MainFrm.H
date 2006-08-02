///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: AppWizard
// Primary date: 01-01-2000
// Filename: MainFrm.h
// Description: Interface file for the CMainFrame class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
// 06-01-2000	SV	Alle variabelenamen aangepast volgens nieuwe conventie
//
///////////////////////////////////////////////////////////////////////////


#if !defined(AFX_MAINFRM_H__552C7528_B87F_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_MAINFRM_H__552C7528_B87F_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CMDIFrameWnd
{
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CWnd* m_pDlgCurrentlyRunning;

private:
	void SetFocusStartScreen();
	// Functions for keeping some settings alive for a next session
	void RestoreWindowState(CREATESTRUCT &cs);
	void StoreWindowState();

public:
	// Bars and stuff
	CStageRaceStatusBar			m_wndStatusBar;
	CToolBarWithProfilePicker	m_wndStandardToolBar;
protected:
	CReBar						m_wndReBar;
	
	// MDI client area picture
	CMDIClient m_wndClient;

// Generated message map functions
protected:
	void ShowOperatorMessage(WPARAM,LPARAM);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnViewTlbarStandard();
	afx_msg void OnUpdateViewTlbarStandard(CCmdUI* pCmdUI);
	afx_msg void OnViewStatusBar();
	afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnHelpContents();
	afx_msg void OnDestroy();
	afx_msg void OnToolsOptions();
	afx_msg void OnToolsSpeedcalculator();
	afx_msg void OnUpdateToolsSpeedcalculator(CCmdUI* pCmdUI);
	afx_msg void OnToolsTimecalculator();
	afx_msg void OnUpdateToolsTimecalculator(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHelpLicense();
	afx_msg void OnHelpSearch();
	afx_msg void OnHelpTipoftheday();
	afx_msg void OnHelpAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__552C7528_B87F_11D2_B376_0040954019F4__INCLUDED_)
