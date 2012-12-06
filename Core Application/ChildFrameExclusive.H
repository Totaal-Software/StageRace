#if !defined(AFX_CHILDFRAMEEXCLUSIVE_H__EC0BF56E_AF79_425F_9884_EFDAFC923A72__INCLUDED_)
#define AFX_CHILDFRAMEEXCLUSIVE_H__EC0BF56E_AF79_425F_9884_EFDAFC923A72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildFrameExclusive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildFrameExclusive frame

class CChildFrameExclusive : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrameExclusive)
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrameExclusive)
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CChildFrameExclusive)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRAMEEXCLUSIVE_H__EC0BF56E_AF79_425F_9884_EFDAFC923A72__INCLUDED_)
