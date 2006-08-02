#if !defined(AFX_PREVIEWCOMMUNIQUE_H__0BF31BE6_E3AA_4C3B_BAD6_359F0D34FD52__INCLUDED_)
#define AFX_PREVIEWCOMMUNIQUE_H__0BF31BE6_E3AA_4C3B_BAD6_359F0D34FD52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewCommunique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewCommunique dialog

class CPreviewCommunique : public CDialog
{
// Construction
public:
	virtual  ~CPreviewCommunique();
	void SetContents( CCommunique* pComm = NULL );
	CPreviewCommunique(CWnd* pParent, const CStageRaceDoc* pDoc);   // standard constructor

protected:
// Dialog Data
	//{{AFX_DATA(CPreviewCommunique)
	enum { IDD = IDD_COMMUNIQUEPREVIEW };
	CStaticWebBrowser2	m_browser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewCommunique)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	const CStageRaceDoc* m_pDoc;
	bool m_ready;
	CCommunique m_communique;

	// Generated message map functions
	//{{AFX_MSG(CPreviewCommunique)
	afx_msg void OnDocumentCompleteBrowser(LPDISPATCH pDisp, VARIANT FAR* URL);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWCOMMUNIQUE_H__0BF31BE6_E3AA_4C3B_BAD6_359F0D34FD52__INCLUDED_)
