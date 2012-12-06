// ListArrival.h : header file
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_LISTARRIVAL_H__8C75A320_CAA5_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_LISTARRIVAL_H__8C75A320_CAA5_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListArrival.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListArrival dialog

class CListArrival : public CAllListArrivalPages
{
public:
	CListArrival( int nAccuracy,
		const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		bool bRankOnly=false,
		const CCompetitorList* pListCompetitor=NULL,
		UINT nIDLabel=NULL,
		CHelp::HELP_TOPIC helptopic=CHelp::HLP_DLG_LSTP_ARR );

protected:
	//{{AFX_DATA(CListArrival)
	enum { IDD = IDD_LISTARRIVAL };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListArrival)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void Insert(unsigned int n);
	bool m_bRankOnly;
	virtual BOOL ChangesAllowed( WORD nStaNo );
	virtual void SetUnits(CArrival *, DWORD);
	virtual DWORD GetUnits( CArrival* );
	virtual void SetRank(CArrival *, WORD);
	virtual WORD GetRank( CArrival* );

	// Generated message map functions
	//{{AFX_MSG(CListArrival)
	virtual BOOL OnInitDialog();
	afx_msg void OnSubmit();
	afx_msg void OnArrivalFunctions();
	virtual void OnOK();
	afx_msg void OnArrivalFunctionsCheck();
	afx_msg void OnArrivalFunctionsGroupt1();
	afx_msg void OnArrivalFunctionsGroupt2();
	afx_msg void OnArrivalFunctionsGroupt3();
	afx_msg void OnArrivalFunctionsImport();
	afx_msg void OnDeclass();
	afx_msg void OnArrivalFunctionsRemovegaps();
	afx_msg void OnArrivalFunctionsRemove1xseconds();
	afx_msg void OnEditSelectall();
	afx_msg void OnChangeArrivalTimecut();
	afx_msg void OnArrivalFunctionsInsertposition();
	afx_msg void OnArrivalFunctionsInsertpositions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTARRIVAL_H__8C75A320_CAA5_11D2_B376_0040954019F4__INCLUDED_)
