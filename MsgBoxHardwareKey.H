#if !defined(AFX_MSGBOXHARDWAREKEY_H__D2ADC929_BE4B_4392_8B69_031329F77A47__INCLUDED_)
#define AFX_MSGBOXHARDWAREKEY_H__D2ADC929_BE4B_4392_8B69_031329F77A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxHardwareKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxHardwareKey dialog

class CMsgBoxHardwareKey : public CDialog
{
// Construction
public:
	BOOL Create(CWnd* pParent);
	CMsgBoxHardwareKey();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgBoxHardwareKey)
	enum { IDD = IDD_MSGBOX_HARDWAREKEY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgBoxHardwareKey)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgBoxHardwareKey)
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXHARDWAREKEY_H__D2ADC929_BE4B_4392_8B69_031329F77A47__INCLUDED_)
