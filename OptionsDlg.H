#if !defined(AFX_OPTIONSDLG_H__B09CD049_3E5B_11D4_92E2_0040954019F4__INCLUDED_)
#define AFX_OPTIONSDLG_H__B09CD049_3E5B_11D4_92E2_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CString GetFolder( CString cCaption, CString cCurrent );
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseomega();
	afx_msg void OnBrowseamb();
	afx_msg void OnBrowsealge();
	afx_msg void OnBrowselynx();
	afx_msg void OnBrowsework();
	afx_msg void OnBrowseeditor();
	afx_msg void OnBrowseskunkware();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__B09CD049_3E5B_11D4_92E2_0040954019F4__INCLUDED_)
