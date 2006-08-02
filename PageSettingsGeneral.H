#if !defined(AFX_PAGESETTINGSGENERAL_H__72A3320D_C007_461D_B995_6EB1A8614DEA__INCLUDED_)
#define AFX_PAGESETTINGSGENERAL_H__72A3320D_C007_461D_B995_6EB1A8614DEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsGeneral dialog

class CPageSettingsGeneral : public CPageSettings
{
// Construction
public:
	CPageSettingsGeneral();
	~CPageSettingsGeneral();

// Dialog Data
	//{{AFX_DATA(CPageSettingsGeneral)
	enum { IDD = IDD_SETT_GENERAL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsGeneral)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSGENERAL_H__72A3320D_C007_461D_B995_6EB1A8614DEA__INCLUDED_)
