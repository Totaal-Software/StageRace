#if !defined(AFX_MSGBOXBEFOREPASTE_H__3F3F0CD3_3D44_4D87_AF4D_FF0B6C6715D6__INCLUDED_)
#define AFX_MSGBOXBEFOREPASTE_H__3F3F0CD3_3D44_4D87_AF4D_FF0B6C6715D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxBeforePaste.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgBoxBeforePaste dialog

class CMsgBoxBeforePaste : public CDialog
{
// Construction
public:
	CMsgBoxBeforePaste();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgBoxBeforePaste)
	enum { IDD = IDD_MSGBOX_BEFOREPASTE };
	BOOL	m_withoutTeamInput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgBoxBeforePaste)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgBoxBeforePaste)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXBEFOREPASTE_H__3F3F0CD3_3D44_4D87_AF4D_FF0B6C6715D6__INCLUDED_)
