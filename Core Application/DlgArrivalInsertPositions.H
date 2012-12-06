#if !defined(AFX_DLGARRIVALINSERTPOSITIONS_H__0EF070A2_B6E9_4D7A_A370_C7887E331FF2__INCLUDED_)
#define AFX_DLGARRIVALINSERTPOSITIONS_H__0EF070A2_B6E9_4D7A_A370_C7887E331FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgArrivalInsertPositions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgArrivalInsertPositions dialog

class CDlgArrivalInsertPositions : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CDlgArrivalInsertPositions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgArrivalInsertPositions)
	enum { IDD = IDD_ARRIVALINSERTPOSITIONS };
	int		m_count;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArrivalInsertPositions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArrivalInsertPositions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGARRIVALINSERTPOSITIONS_H__0EF070A2_B6E9_4D7A_A370_C7887E331FF2__INCLUDED_)
