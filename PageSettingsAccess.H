#if !defined(AFX_PAGESETTINGSACCESS_H__6C7CCE35_DC23_41D3_BCBC_416ECE87A747__INCLUDED_)
#define AFX_PAGESETTINGSACCESS_H__6C7CCE35_DC23_41D3_BCBC_416ECE87A747__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsAccess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsAccess dialog

class CPageSettingsAccess : public CPageSettings
{
// Construction
public:
	CPageSettingsAccess();
	~CPageSettingsAccess();

// Dialog Data
	//{{AFX_DATA(CPageSettingsAccess)
	enum { IDD = IDD_SETT_ACCESS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsAccess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsAccess)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSACCESS_H__6C7CCE35_DC23_41D3_BCBC_416ECE87A747__INCLUDED_)
