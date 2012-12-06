#if !defined(AFX_DLGPROFILENAME_H__A56DDC27_D05D_4602_91AD_5F991B447A2A__INCLUDED_)
#define AFX_DLGPROFILENAME_H__A56DDC27_D05D_4602_91AD_5F991B447A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProfileName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProfileName dialog

class CDlgProfileName : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CDlgProfileName(CString name);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProfileName)
	enum { IDD = IDD_DLGPROFILENAME };
	CString	m_name;
	BOOL	m_indicator_access;
	BOOL	m_indicator_general;
	BOOL	m_indicator_html;
	BOOL	m_indicator_publication;
	BOOL	m_indicator_ranking;
	BOOL	m_indicator_upload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProfileName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProfileName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROFILENAME_H__A56DDC27_D05D_4602_91AD_5F991B447A2A__INCLUDED_)
