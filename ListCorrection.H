#if !defined(AFX_LISTCORRECTION_H__B71E4F93_941D_453D_B17B_1D4678370142__INCLUDED_)
#define AFX_LISTCORRECTION_H__B71E4F93_941D_453D_B17B_1D4678370142__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCorrection.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCorrection dialog

class CListCorrection : public CAllListPages
{
//	DECLARE_DYNCREATE(CListCorrection)

// Construction
public:
	CListCorrection(const CAvailableList* pListAvailable,
		const CCorrectionList* pListCorrection,
		const CCompetitorList* pListCompetitor=NULL );
	CArrivalList m_listCorrection;

// Dialog Data
	//{{AFX_DATA(CListCorrection)
	private:
	enum { IDD = IDD_LISTCORRECTION };
	CTimeEdit	m_penalty;
	CStaNoEdit	m_staNo;
	CTimeEdit	m_bonus;
	CArrivalListCtrl	m_ctrlCorrectionList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CListCorrection)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CListCorrection)
	virtual BOOL OnInitDialog();
	afx_msg void OnListcorrectionAdd();
	afx_msg void OnListcorrectionDelete();
	afx_msg void OnItemchangedListcorrection(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCORRECTION_H__B71E4F93_941D_453D_B17B_1D4678370142__INCLUDED_)
