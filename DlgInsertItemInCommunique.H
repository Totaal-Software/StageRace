#if !defined(AFX_DLGINSERTITEMINCOMMUNIQUE_H__A715BB2E_B23F_4606_AA43_91535429F09C__INCLUDED_)
#define AFX_DLGINSERTITEMINCOMMUNIQUE_H__A715BB2E_B23F_4606_AA43_91535429F09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInsertItemInCommunique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInsertItemInCommunique dialog

class CDlgInsertItemInCommunique : public CDialog
{
// Construction
public:
	CDlgInsertItemInCommunique(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInsertItemInCommunique)
	enum { IDD = IDD_INSERTITEMINCOMMUNIQUE };
	CString	m_identifier;
	int		m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInsertItemInCommunique)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInsertItemInCommunique)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINSERTITEMINCOMMUNIQUE_H__A715BB2E_B23F_4606_AA43_91535429F09C__INCLUDED_)
