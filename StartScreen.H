// StartScreen.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_STARTSCREEN_H__E705F004_C466_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_STARTSCREEN_H__E705F004_C466_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CStartScreen dialog

class CStartScreen : public CDialog
{
// Construction
public:
	void DoMsgBoxHardwareKey();
	void SetMainFrame( CWnd* pMainFrame );
	CStartScreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStartScreen)
	enum { IDD = IDD_STARTSCREEN };
	CProgressCtrl	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartScreen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnCancel();
	CMsgBoxHardwareKey	m_msgBoxHardwareKey;
	CWnd*				m_pMainFrame;
	CBrush				m_brush;

	// Generated message map functions
	//{{AFX_MSG(CStartScreen)
	virtual BOOL OnInitDialog();
public:
	virtual void OnOK();
protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTSCREEN_H__E705F004_C466_11D2_B376_0040954019F4__INCLUDED_)
