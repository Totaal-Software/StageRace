#if !defined(AFX_LISTTIMETRIALARRIVAL_H__8EDAAEA0_7DC2_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_LISTTIMETRIALARRIVAL_H__8EDAAEA0_7DC2_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListTimeTrialArrival.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListTimeTrialArrivalGross dialog

class CListTimeTrialArrivalGross : public CAllListArrivalPages
{
public:
	CListTimeTrialArrivalGross( int nAccuracy,
		const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		const CCompetitorList* pListCompetitor=NULL,
		UINT nIDLabel=NULL,
		CHelp::HELP_TOPIC helptopic=CHelp::HLP_DLG_LSTP_ARR_TT_GROSS );
protected:
 	//{{AFX_DATA(CListTimeTrialArrivalGross)
	enum { IDD = IDD_LISTTIMETRIALARRIVAL };
	CTimeEdit m_anticipatedTime;
	//}}AFX_DATA

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CListTimeTrialArrivalGross)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	virtual void SetUnits(CArrival *, DWORD);
	virtual DWORD GetUnits( CArrival* );
	virtual void SetRank(CArrival *, WORD);
	virtual WORD GetRank( CArrival* );
	// Generated message map functions
	//{{AFX_MSG(CListTimeTrialArrivalGross)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeclass();
	afx_msg void OnSubmit();
	afx_msg void OnArrivalAnticipatetime();
	afx_msg void OnDestroy();
	afx_msg void OnChangeArrivalTimecut();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTIMETRIALARRIVAL_H__8EDAAEA0_7DC2_11D3_92DA_0040954019F4__INCLUDED_)
