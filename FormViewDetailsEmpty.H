#if !defined(AFX_FORMVIEWDETAILSEMPTY_H__D80B39BC_4D0E_45B6_966C_6B11CC029D20__INCLUDED_)
#define AFX_FORMVIEWDETAILSEMPTY_H__D80B39BC_4D0E_45B6_966C_6B11CC029D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormViewDetailsEmpty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormViewDetailsEmpty form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormViewDetailsEmpty : public CFormView
{
protected:
	CFormViewDetailsEmpty();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormViewDetailsEmpty)

// Form Data
public:
	//{{AFX_DATA(CFormViewDetailsEmpty)
	enum { IDD = IDD_FORMVIEWDETAILSEMPTY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void OnNextPane();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormViewDetailsEmpty)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmap m_bannerbottom;
	CBrush m_brush;
	virtual ~CFormViewDetailsEmpty();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormViewDetailsEmpty)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMVIEWDETAILSEMPTY_H__D80B39BC_4D0E_45B6_966C_6B11CC029D20__INCLUDED_)
