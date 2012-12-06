#if !defined(AFX_MSGBOXINDEXHTML_H__E645E4C1_13EE_406A_A10C_3481B326CAFC__INCLUDED_)
#define AFX_MSGBOXINDEXHTML_H__E645E4C1_13EE_406A_A10C_3481B326CAFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxIndexHtml.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxIndexHtml dialog

class CMsgBoxIndexHtml : public CDialog
{
// Construction
public:
	CMsgBoxIndexHtml(CString cTitle);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgBoxIndexHtml)
	enum { IDD = IDD_MSGBOX_INDEXHTML };
	BOOL	m_futureSuppress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgBoxIndexHtml)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_title;
	// Generated message map functions
	//{{AFX_MSG(CMsgBoxIndexHtml)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXINDEXHTML_H__E645E4C1_13EE_406A_A10C_3481B326CAFC__INCLUDED_)
