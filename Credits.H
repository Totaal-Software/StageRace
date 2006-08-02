#if !defined(AFX_CREDITS_H__92440F67_F837_11D3_92DD_0040954019F4__INCLUDED_)
#define AFX_CREDITS_H__92440F67_F837_11D3_92DD_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Credits.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog

class CCredits : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CCredits(CWnd* pParent = NULL);   // standard constructor

protected:
// Dialog Data
	//{{AFX_DATA(CCredits)
	enum { IDD = IDD_CREDITS };
	CBrush m_brush;
	CStaticWebBrowser2	m_credits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCredits)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCredits)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREDITS_H__92440F67_F837_11D3_92DD_0040954019F4__INCLUDED_)
