#if !defined(AFX_DLGAUTONUMBERCOMMUNIQUES_H__3D2991C7_9B11_48D6_840A_0C9859B43ED7__INCLUDED_)
#define AFX_DLGAUTONUMBERCOMMUNIQUES_H__3D2991C7_9B11_48D6_840A_0C9859B43ED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutonumberCommuniques.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAutonumberCommuniques dialog

class CDlgAutonumberCommuniques : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CDlgAutonumberCommuniques(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAutonumberCommuniques)
	enum { IDD = IDD_DLGAUTONUMBERCOMMUNIQUES };
	BOOL	m_crossoutlists;
	BOOL	m_signinlists;
	BOOL	m_stanosortedgeneral;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAutonumberCommuniques)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAutonumberCommuniques)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTONUMBERCOMMUNIQUES_H__3D2991C7_9B11_48D6_840A_0C9859B43ED7__INCLUDED_)
