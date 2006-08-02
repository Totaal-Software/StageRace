#if !defined(AFX_SIGNOUTLISTCTRL_H__AA45C2BE_5D2F_4DDE_8A71_464BA6D33AAA__INCLUDED_)
#define AFX_SIGNOUTLISTCTRL_H__AA45C2BE_5D2F_4DDE_8A71_464BA6D33AAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SignOutListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSignOutListCtrl window

class CSignOutListCtrl : public CStaNoListCtrl
{
public:
	CSignOutListCtrl();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignOutListCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void Draw( CSignOut* pSO );
	void DrawList( CSignOutList* pList );
	void Init();

	// Generated message map functions
protected:
	int DrawIntern(CSignOut *pSO, int nItem);
	//{{AFX_MSG(CSignOutListCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGNOUTLISTCTRL_H__AA45C2BE_5D2F_4DDE_8A71_464BA6D33AAA__INCLUDED_)
