// EditTeam.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_EDITTEAM_H__7FE3F320_C048_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_EDITTEAM_H__7FE3F320_C048_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditTeam dialog

class CEditTeam : public CStageRaceWnd<CDialog>
{
// Functions and variables
public:
	const CTeam* m_pTeam;
	const CStageRaceDoc* m_pStageRaceDoc;
	CEditTeam& operator=(const CTeam& aTeam);
	CEditTeam& operator=(const CEditTeam& aTeam);
	CEditTeam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditTeam)
	enum { IDD = IDD_TEAM };
	CString	m_szCode;
	CString	m_szCountry;
	CString	m_szManager;
	CString	m_szName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditTeam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL UpdateData( BOOL bSaveAndValidate = TRUE );

	// Generated message map functions
	//{{AFX_MSG(CEditTeam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTEAM_H__7FE3F320_C048_11D3_92DA_0040954019F4__INCLUDED_)
