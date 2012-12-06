#if !defined(AFX_PAGESETTINGSPUBLICATION_H__D8D9FD17_8846_4F14_834E_BEEEC0A57F5F__INCLUDED_)
#define AFX_PAGESETTINGSPUBLICATION_H__D8D9FD17_8846_4F14_834E_BEEEC0A57F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsPublication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsPublication dialog

class CPageSettingsPublication : public CPageSettings
{
// Construction
public:
	CPageSettingsPublication();
	~CPageSettingsPublication();

// Dialog Data
	//{{AFX_DATA(CPageSettingsPublication)
	enum { IDD = IDD_SETT_PUBL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsPublication)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsPublication)
	virtual BOOL OnInitDialog();
	afx_msg void OnSettingsRemoverequiredlanguage();
	afx_msg void OnSettingsAddrequiredlanguage();
	afx_msg void OnChangeSettingsCrossoutteamnamesmodulus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSPUBLICATION_H__D8D9FD17_8846_4F14_834E_BEEEC0A57F5F__INCLUDED_)
