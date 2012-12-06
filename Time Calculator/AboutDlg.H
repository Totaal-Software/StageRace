// AboutDlg.h: interface for the CAboutDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__B8A9B884_5117_4E9B_A8DF_0E8061798AC9__INCLUDED_)
#define AFX_ABOUTDLG_H__B8A9B884_5117_4E9B_A8DF_0E8061798AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_name;
	CString	m_version;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_ABOUTDLG_H__B8A9B884_5117_4E9B_A8DF_0E8061798AC9__INCLUDED_)
