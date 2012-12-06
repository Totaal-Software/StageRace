#if !defined(AFX_TTORDEROPTIONSDLG_H__F338C4B9_134F_4E47_9471_35FEFB209257__INCLUDED_)
#define AFX_TTORDEROPTIONSDLG_H__F338C4B9_134F_4E47_9471_35FEFB209257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TTOrderOptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTTOrderOptionsDlg dialog

class CTTOrderOptionsDlg : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CTTOrderOptionsDlg();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTTOrderOptionsDlg)
	enum { IDD = IDD_TTORDEROPTIONS };
	BOOL	m_avoidConsecutiveTeamMembers;
	BOOL	m_leavePlacesForDroppedTeams;
	//}}AFX_DATA
	BOOL m_individual;
	BOOL m_team;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTOrderOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Update();

	// Generated message map functions
	//{{AFX_MSG(CTTOrderOptionsDlg)
	afx_msg void OnTeams();
	afx_msg void OnIndividual();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTORDEROPTIONSDLG_H__F338C4B9_134F_4E47_9471_35FEFB209257__INCLUDED_)
