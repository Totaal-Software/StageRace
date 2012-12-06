#if !defined(AFX_PAGESETTINGSHTML_H__F1339CCA_FABB_4B49_8459_AF4F4196ED33__INCLUDED_)
#define AFX_PAGESETTINGSHTML_H__F1339CCA_FABB_4B49_8459_AF4F4196ED33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsHTML.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsHTML dialog

class CPageSettingsHTML : public CPageSettings
{
// Construction
public:
	CPageSettingsHTML();
	~CPageSettingsHTML();

// Dialog Data
	//{{AFX_DATA(CPageSettingsHTML)
	enum { IDD = IDD_SETT_HTML };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsHTML)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsHTML)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSHTML_H__F1339CCA_FABB_4B49_8459_AF4F4196ED33__INCLUDED_)
