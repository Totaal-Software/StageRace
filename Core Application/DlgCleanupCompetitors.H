#if !defined(AFX_DLGCLEANUPCOMPETITORS_H__5B7A74F1_5397_4534_B9D0_0E662E7C491E__INCLUDED_)
#define AFX_DLGCLEANUPCOMPETITORS_H__5B7A74F1_5397_4534_B9D0_0E662E7C491E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCleanupCompetitors.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCleanupCompetitors dialog

enum CLEANUPCOMPETITORS
{
	CLC_NONE=0,
	CLC_REMOVEREPEATEDSPACES=1,
	CLC_REMOVESPACESAROUND=2,
	CLC_COPYUCITOCOUNTRY=4,
	CLC_CAPITALIZEBEFORECOMMA=8,
	CLC_CLEANUPCOMMAS=16
};

class CDlgCleanupCompetitors : public CStageRaceWnd<CDialog>
{
// Construction
public:
	int DoModal();

	CDlgCleanupCompetitors(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCleanupCompetitors)
	enum { IDD = IDD_DLGCOMPETITORSCLEANUP };
	BOOL	m_CopyUCIToCountry;
	BOOL	m_RemoveSpacesAround;
	BOOL	m_RemoveRepeatedSpaces;
	BOOL	m_CleanupCommas;
	BOOL	m_CapitalizeBeforeComma;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCleanupCompetitors)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCleanupCompetitors)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLEANUPCOMPETITORS_H__5B7A74F1_5397_4534_B9D0_0E662E7C491E__INCLUDED_)
