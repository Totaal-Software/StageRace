#if !defined(AFX_GETPWD_H__D623CF06_E666_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_GETPWD_H__D623CF06_E666_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetPwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGetPwd dialog

class CGetPwd : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CGetPwd();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGetPwd)
	enum { IDD = IDD_GETPWD };
	CString	m_accessPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetPwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGetPwd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETPWD_H__D623CF06_E666_11D3_92DC_0040954019F4__INCLUDED_)
