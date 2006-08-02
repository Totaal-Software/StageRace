///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Edwin Engelen (from www.codeguru.com)
// Primary date: 21-02-2000
// Filename: Hyperlink.h
// Description: HyperLink static control. Will open the default browser
//              with the given URL when the user clicks on the link
//
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 21-02-2000	EE	Delivered as is
//
#if !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHyperlink window

class CHyperlink : public CStatic
{
// Construction/destruction
public:
	CHyperlink();
	virtual ~CHyperlink();

// Attributes
public:

// Operations
public:

	void SetURL(CString strURL);
	CString GetURL();

	void SetColors(COLORREF crLinkcolor, COLORREF crVisitedColor);
	COLORREF GetLinkColor();
	COLORREF GetVisitedColor();

	void SetVisited(BOOL bVisited = TRUE);
	BOOL GetVisited();

	void SetLinkCursor(HCURSOR hCursor);

	void SetUnderline(BOOL bUnderline = TRUE);
	BOOL GetUnderline();

	void SetAutoSize(BOOL bAutoSize = TRUE);
	BOOL GetAutoSize();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperlink)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HINSTANCE GotoURL(LPCTSTR url, int showcmd);
	void ShowError(int nError);
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void PositionWindow();

// Protected attributes
protected:
	COLORREF m_crLinkColor, m_crVisitedColor;		// Hyperlink colors
	BOOL     m_bVisited;							// Has it been visited?
	BOOL	 m_bUnderline;							// underline hyperlink?
	BOOL	 m_bAdjustToFit;						// Adjust window size to fit text?
	CString  m_strURL;								// hyperlink URL
	CFont	 m_Font;								// Underline font if necessary
	HCURSOR  m_hLinkCursor;							// Cursor for hyperlink
	CToolTipCtrl m_ToolTip;							// The tooltip

	// Generated message map functions
protected:
	//{{AFX_MSG(CHyperlink)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	afx_msg void OnClicked();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
