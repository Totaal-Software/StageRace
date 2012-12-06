#if !defined(AFX_FULLSTAGETRIALDAT_H__274A3C21_C90D_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_FULLSTAGETRIALDAT_H__274A3C21_C90D_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFullStageTrialDat dialog

class CFullStageTrialDat : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CFullStageTrialDat& operator =(CFullStage & aFullStage);
	CFullStageTrialDat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFullStageTrialDat)
	enum { IDD = IDD_FULLSTAGETRIALDAT };
	CString	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullStageTrialDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFullStageTrialDat)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSTAGETRIALDAT_H__274A3C21_C90D_11D2_B376_0040954019F4__INCLUDED_)
