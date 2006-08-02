#if !defined(AFX_PAGESETTINGSUPLOAD_H__7443D47D_2D5C_4236_8D77_2A4AFB4B355A__INCLUDED_)
#define AFX_PAGESETTINGSUPLOAD_H__7443D47D_2D5C_4236_8D77_2A4AFB4B355A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsUpload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsUpload dialog

class CPageSettingsUpload : public CPageSettings
{
// Construction
public:
	CPageSettingsUpload();
	~CPageSettingsUpload();

// Dialog Data
	//{{AFX_DATA(CPageSettingsUpload)
	enum { IDD = IDD_SETT_UPLOAD };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsUpload)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSUPLOAD_H__7443D47D_2D5C_4236_8D77_2A4AFB4B355A__INCLUDED_)
