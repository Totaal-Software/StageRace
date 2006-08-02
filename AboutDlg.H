#if !defined(AFX_ABOUTDLG_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_ABOUTDLG_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CStageRaceWnd<CDialog>
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CTransparentImage	m_totaallogo;
	CHyperlink	m_website;
	CHyperlink	m_email;
	CString	m_hardwareKey;
	CString	m_name;
	CString	m_version;
	CString	m_hardwareKeyContents;
	CString	m_evaluation;
	CStaticWebBrowser2	m_license;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnAboutTotaallogo();
	afx_msg void OnCredits();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_ABOUTDLG_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
