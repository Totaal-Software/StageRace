// HelpToolDlg.h : header file
//

#if !defined(AFX_HELPTOOLDLG_H__4EAC8B66_2099_4817_9FC8_81AA59280D4C__INCLUDED_)
#define AFX_HELPTOOLDLG_H__4EAC8B66_2099_4817_9FC8_81AA59280D4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHelpToolDlg dialog

class CHelpToolDlg : public CDialog
{
// Construction
public:
	CHelpToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHelpToolDlg)
	enum { IDD = IDD_HELPTOOL_DIALOG };
	CListBox	m_reporting;
	CString	m_source;
	CString	m_targethtml;
	CString	m_targetdoc;
	CString	m_includes;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpToolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHelpToolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPTOOLDLG_H__4EAC8B66_2099_4817_9FC8_81AA59280D4C__INCLUDED_)
