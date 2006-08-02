#if !defined(AFX_SUBEDIT1_H__98F7AA8E_CA20_4B36_A71A_C7F3FCEE3C53__INCLUDED_)
#define AFX_SUBEDIT1_H__98F7AA8E_CA20_4B36_A71A_C7F3FCEE3C53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubEdit1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubEdit window

class CSubEdit : public CEdit
{
// Construction
public:
	CSubEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_x;
	int m_y;
	virtual ~CSubEdit();

	// Generated message map functions
protected:
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//{{AFX_MSG(CSubEdit)
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBEDIT1_H__98F7AA8E_CA20_4B36_A71A_C7F3FCEE3C53__INCLUDED_)
