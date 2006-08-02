#if !defined(AFX_DLGNEWPARAGRAPHTITLE_H__CCE3004E_EE85_462D_AD7D_6E475721D7DB__INCLUDED_)
#define AFX_DLGNEWPARAGRAPHTITLE_H__CCE3004E_EE85_462D_AD7D_6E475721D7DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewParagraphTitle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewParagraphTitle dialog

class CDlgNewParagraphTitle : public CDialog
{
// Construction
public:
	CDlgNewParagraphTitle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewParagraphTitle)
	enum { IDD = IDD_PARAGRAPHTITLE };
	CString	m_title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewParagraphTitle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewParagraphTitle)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWPARAGRAPHTITLE_H__CCE3004E_EE85_462D_AD7D_6E475721D7DB__INCLUDED_)
