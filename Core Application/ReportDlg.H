#if !defined(AFX_REPORTDLG_H__F46D27A0_E00C_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_REPORTDLG_H__F46D27A0_E00C_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportDlg dialog

class CReportDlg : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CReportDlg(CString cReport);

// Dialog Data
	//{{AFX_DATA(CReportDlg)
	enum { IDD = IDD_REPORT };
	protected:
	CString	m_Report;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTDLG_H__F46D27A0_E00C_11D3_92DC_0040954019F4__INCLUDED_)
