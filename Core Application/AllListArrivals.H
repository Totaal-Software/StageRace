// AllListArrivals.h: interface for the CAllListArrivalPages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALLLISTARRIVALS_H__B430BA25_ED82_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_ALLLISTARRIVALS_H__B430BA25_ED82_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAllListArrivalPages : public CAllListPages
{
public:
	BOOL PreTranslateMessage( MSG*pMsg );
	CAllListArrivalPages(
		CHelp::HELP_TOPIC helptopic,
		UINT nIDTemplate,
		UINT nIDLabel,
		int nAccuracy,
		const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		const CCompetitorList* pListCompetitor=NULL );

protected:
	virtual void SetUnits(CArrival *, DWORD) = 0;
	virtual DWORD GetUnits( CArrival* ) = 0;
	virtual void SetRank(CArrival *, WORD) = 0;
	virtual WORD GetRank( CArrival* ) = 0;
	void DrawCounters();
	int m_accuracy;
	CArrivalListCtrl	m_ctrlArrivalList;
	CArrivalListCtrl	m_ctrlAvailableList;
	CStaNoEdit			m_staNo;
	CTimeEdit			m_time;

	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAllListArrivalPages)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CAllListArrivalPages)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedArrivalListarrival(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedArrivalListavailable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusArrivalListarrival(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusArrivalListavailable(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_ALLLISTARRIVALS_H__B430BA25_ED82_11D3_92DC_0040954019F4__INCLUDED_)
