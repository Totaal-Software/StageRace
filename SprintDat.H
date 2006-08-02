#if !defined(AFX_SPRINTDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_SPRINTDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SprintDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSprintDat dialog

class CSprintDat : public CStageRaceWnd<CPropertyPage>
{

// Construction
public:
	CSprintDat& operator =(CHalfStage &aSprintDat);
	CList<WORD,WORD&> m_sprintpointsIntermediate;
	CList<WORD,WORD&> m_sprintpointsFinish;
	CSprintDat();
	~CSprintDat();

// Dialog Data
	//{{AFX_DATA(CSprintDat)
	enum { IDD = IDD_SPRINTDAT };
	int		m_sprintpointsCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSprintDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSprintDat)
	virtual BOOL OnInitDialog();
	afx_msg void OnRemove();
	afx_msg void OnAdd();
	afx_msg void OnSelchangePointssprint();
	afx_msg void OnSelchangePointsfinish();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPRINTDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
