#if !defined(AFX_HALFSTAGETRIALDAT_H__7FB3E0A1_EC75_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_HALFSTAGETRIALDAT_H__7FB3E0A1_EC75_11D3_92DC_0040954019F4__INCLUDED_

#include "EventItem.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HalfStageTrialDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHalfStageTrialDat dialog

class CHalfStageTrialDat : public CStageRaceWnd<CPropertyPage>
{

// Construction
public:
	STAGETYPES m_stageType;
	CHalfStageTrialDat & operator =(CHalfStage &aHS);
	CHalfStageTrialDat();
	~CHalfStageTrialDat();

// Dialog Data
	//{{AFX_DATA(CHalfStageTrialDat)
	enum { IDD = IDD_HALFSTAGETRIALDAT };
	CString	m_date;
	int		m_distance;
	CString	m_openingHour;
	CString	m_title;
	int		m_rounds;
	BOOL	m_exclude;
	BOOL	m_oneForTeamsClass;
	int		m_timeCut;
	BOOL	m_allowLateChangesStartOrder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHalfStageTrialDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	STAGETYPES m_timeTrialType;
	// Generated message map functions
	//{{AFX_MSG(CHalfStageTrialDat)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimetrial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HALFSTAGETRIALDAT_H__7FB3E0A1_EC75_11D3_92DC_0040954019F4__INCLUDED_)
