// srcalcDlg.h : header file
//

#if !defined(AFX_SRCALCDLG_H__B98CAC46_3DEB_11D4_92E2_0040954019F4__INCLUDED_)
#define AFX_SRCALCDLG_H__B98CAC46_3DEB_11D4_92E2_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSrcalcDlg dialog

class CSrcalcDlg : public CDialog
{
// Construction
public:
	void DoCalc( bool bPlus );
	bool m_afterClear;
	CSrcalcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSrcalcDlg)
	enum { IDD = IDD_SRCALC_DIALOG };
	CTimeEdit	m_res1;
	CTimeEdit	m_inp3;
	CTimeEdit	m_inp2;
	CTimeEdit	m_inp1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrcalcDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSrcalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClear();
	afx_msg void OnMinus();
	afx_msg void OnPlus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRCALCDLG_H__B98CAC46_3DEB_11D4_92E2_0040954019F4__INCLUDED_)
