#if !defined(AFX_DLGINTERVAL_H__2C3A4B10_0E74_11D4_92DF_0040954019F4__INCLUDED_)
#define AFX_DLGINTERVAL_H__2C3A4B10_0E74_11D4_92DF_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInterval.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInterval dialog

class CDlgInterval : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CDlgInterval(WORD nStaNoFirst, int nStartTimeFirst, int nPositionFirst,
						   WORD nStaNoLast, int nStartTimeLast, int nPositionLast, int nInterval = 60000);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInterval)
	enum { IDD = IDD_TTORDER_INTERVAL };
	CTimeEdit	m_ctrl_starttime;
	CTimeEdit	m_ctrl_interval;
	int		m_interval;
	int		m_startTime;
	BOOL	m_useOrder;
	//}}AFX_DATA
	bool	m_ascending;
	int		m_startTimeFirst;
	int		m_startTimeLast;
	int		m_staNoFirst;
	int		m_staNoLast;
	int		m_positionFirst;
	int		m_positionLast;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInterval)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetFirstLast();

	// Generated message map functions
	//{{AFX_MSG(CDlgInterval)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAscending();
	afx_msg void OnDescending();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERVAL_H__2C3A4B10_0E74_11D4_92DF_0040954019F4__INCLUDED_)
