#if !defined(AFX_LISTSIGNOUTS_H__74F0EAA0_B624_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_LISTSIGNOUTS_H__74F0EAA0_B624_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListSignOuts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListSignOuts dialog

class CListSignOuts : public CAllListPages
{
// Construction
public:
	BOOL PreTranslateMessage(MSG* pMsg);
	CSignOutList m_listSignOuts;
	CListSignOuts::CListSignOuts(	const CAvailableList* pListAvailable,
									const CSignOutList* pListSignOuts,
									const CMultiLanguage::REQUIREDLANGUAGES* pLang,
									const CCompetitorList* pListCompetitor=NULL
								);

protected:
// Dialog Data
	//{{AFX_DATA(CListSignOuts)
	enum { IDD = IDD_LISTSIGNOUTS };
	CSignOutListCtrl	m_ctrlSignOutList;
	CStaNoEdit	m_staNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListSignOuts)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	const CMultiLanguage::REQUIREDLANGUAGES* m_pLang;
	int m_nLastUseValue;

	// Generated message map functions
	//{{AFX_MSG(CListSignOuts)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual void OnOK();
	afx_msg void OnItemchangedSignoutsListsignouts(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RestoreReasons(void);
	void StoreReasons(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTSIGNOUTS_H__74F0EAA0_B624_11D3_92DA_0040954019F4__INCLUDED_)
