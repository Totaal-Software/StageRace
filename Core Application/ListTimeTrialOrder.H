#if !defined(AFX_LISTTIMETRIALORDER_H__856E9CC0_7E3D_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_LISTTIMETRIALORDER_H__856E9CC0_7E3D_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListTimeTrialOrder.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CListTimeTrialOrder dialog

class CListTimeTrialOrder : public CListArrival
{
public:
	CListTimeTrialOrder( const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		const CArrivalList* pListRanked,
		const CCompetitorList* pListCompetitor=NULL,
		const CDistributedClassification* pPreviousHS=NULL,
		const CDistributedClassification* pPreviousFS=NULL,
		bool bAllowLateChangesStartOrder=true);
	~CListTimeTrialOrder();

// Dialog Data
	//{{AFX_DATA(CListTimeTrialOrder)
	enum { IDD = IDD_LISTTIMETRIALORDER };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CListTimeTrialOrder)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK();
	const CArrivalList* m_pListRanked;
	const CDistributedClassification* m_pListPreviousHS;
	const CDistributedClassification* m_pListPreviousFS;
	void FromEarlierStage(const CDistributedClassification* pClassPrevious);

	virtual BOOL ChangesAllowed(WORD nStaNo);
	virtual void SetUnits(CArrival *, DWORD);
	virtual DWORD GetUnits( CArrival* );
	virtual void SetRank(CArrival *, WORD);
	virtual WORD GetRank( CArrival* );
	// Generated message map functions
	//{{AFX_MSG(CListTimeTrialOrder)
	afx_msg void OnTtorderFunctions();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimetrialorderfunctionsGaps();
	afx_msg void OnTimetrialorderfunctionsAuto();
	afx_msg void OnTimetrialorderfunctionsFromlasthalfstage();
	afx_msg void OnTimetrialorderfunctionsFromlastfullstage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTTIMETRIALORDER_H__856E9CC0_7E3D_11D3_92DA_0040954019F4__INCLUDED_)
