#if !defined(AFX_PRESENTATIONTEXTVIEW_H__4D5755B5_6E3A_4C12_90DF_24FCDDF679FC__INCLUDED_)
#define AFX_PRESENTATIONTEXTVIEW_H__4D5755B5_6E3A_4C12_90DF_24FCDDF679FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PresentationTextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPresentationTextView view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxrich.h>

class CPresentationTextView : public CRichEditView
{
protected:
	CPresentationTextView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPresentationTextView)

// Attributes
public:

// Operations
public:
	void OnNextPane();

// Overrides
	bool Navigate( CEventItem* pEI );
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPresentationTextView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPresentationTextView();
	CFont m_font;
	CHARFORMAT m_cf1;
	CHARFORMAT m_cf2;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPresentationTextView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRESENTATIONTEXTVIEW_H__4D5755B5_6E3A_4C12_90DF_24FCDDF679FC__INCLUDED_)
