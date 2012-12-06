// srspeedDlg.h : header file
//

#if !defined(AFX_SRSPEEDDLG_H__96A09626_3E1C_11D4_92E2_0040954019F4__INCLUDED_)
#define AFX_SRSPEEDDLG_H__96A09626_3E1C_11D4_92E2_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSrspeedDlg dialog

class CSrspeedDlg : public CDialog
{
// Construction
public:
	void DoCalc();
	CSrspeedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSrspeedDlg)
	enum { IDD = IDD_SRSPEED_DIALOG };
	CTimeEdit	m_time;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrspeedDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSrspeedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChange();
	afx_msg void OnMph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSPEEDDLG_H__96A09626_3E1C_11D4_92E2_0040954019F4__INCLUDED_)
