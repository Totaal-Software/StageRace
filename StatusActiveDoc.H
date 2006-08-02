// StatusActiveDoc.h: interface for the CStatusActiveDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSACTIVEDOC_H__1DEFC55E_6045_40A3_9EA9_2B3EE570FF83__INCLUDED_)
#define AFX_STATUSACTIVEDOC_H__1DEFC55E_6045_40A3_9EA9_2B3EE570FF83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStatusActiveDoc : public CStatusCombo  
{
public:
	void SelectDoc(CStageRaceDoc*pDoc);
	void RemoveDoc( CStageRaceDoc *pDoc );
	BOOL Create(CStatusBar * parent, UINT id, DWORD style);
	void AddDoc( CStageRaceDoc* pDoc );
	BOOL PreTranslateMessage(MSG *pMsg);
	CStatusActiveDoc();
	virtual ~CStatusActiveDoc();

	//{{AFX_MSG(CListViewActiveDoc)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_STATUSACTIVEDOC_H__1DEFC55E_6045_40A3_9EA9_2B3EE570FF83__INCLUDED_)
