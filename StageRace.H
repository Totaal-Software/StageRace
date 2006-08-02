///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: StageRace.h
// Description: Main header file for the application
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
//
///////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAGE_H__552C7524_B87F_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_STAGE_H__552C7524_B87F_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CStageRaceApp:
// See Stage.cpp for the implementation of this class
//

class CStageRaceApp : public CWinApp
{
public:
	const CStageRaceDoc* ActiveDocGet();
	void ActiveDocSelect(CStageRaceDoc*);
	void ActiveDocClose(CStageRaceDoc*);
	void ActiveDocOpen(CStageRaceDoc*);
	CHaspTotaal m_key;
	void Language();
	CStageRaceApp();
	virtual ~CStageRaceApp();
	CStartScreen			m_startScreen;
	CMultiLanguage*			m_pMultiLang;
protected:
	bool CheckExe();
	void UnregisterShellFileTypes();
	void RegisterShellFileTypes();
	CActiveDocTracker*	m_pActiveDocTracker;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRaceApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStageRaceApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewListviewactivedoc();
	afx_msg void OnUpdateViewListviewactivedoc(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
	BOOL InitATL();
	void RestoreWindowState(int& nCmdShow);
};

extern CStageRaceApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGE_H__552C7524_B87F_11D2_B376_0040954019F4__INCLUDED_)
