// EditCompetitor.h: interface for the CEditCompetitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITCOMPETITOR_H__F3F273E0_BA18_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_EDITCOMPETITOR_H__F3F273E0_BA18_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEditCompetitor dialog

class CEditCompetitor : public CStageRaceWnd<CDialog>
{

//Functions and variables
protected:
	int m_oldStaNo;
public:
	CTeam* m_pTeam;
	const CStageRaceDoc* m_pStageRaceDoc;
	
	CEditCompetitor& operator =(const CCompetitor & aComp);
	CEditCompetitor& operator=(const CEditCompetitor& aComp);
	CEditCompetitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditCompetitor)
	enum { IDD = IDD_COMPETITOR };
	CString	m_category;
	CString	m_competitor;
	CString	m_license;
	BOOL	m_mask1;
	BOOL	m_mask2;
	BOOL	m_mask3;
	BOOL	m_mask4;
	BOOL	m_mask5;
	BOOL	m_mask6;
	BOOL	m_mask7;
	BOOL	m_mask8;
	BOOL	m_mask9;
	BOOL	m_mask10;
	CString	m_UCICode;
	int		m_staNo;
	CString	m_countryCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCompetitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_rememberedStaNo;

	// Generated message map functions
	//{{AFX_MSG(CEditCompetitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTeam();
	virtual void OnOK();
	afx_msg void OnNewteam();
	afx_msg void OnChangeStano();
	afx_msg void OnStanoNonactive();
	afx_msg void OnStanoActive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_EDITCOMPETITOR_H__F3F273E0_BA18_11D2_B376_0040954019F4__INCLUDED_)
