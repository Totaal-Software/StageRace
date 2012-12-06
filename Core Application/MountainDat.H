#if !defined(AFX_MOUNTAINDAT_H__8CB20E01_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_MOUNTAINDAT_H__8CB20E01_EBBA_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MountainDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMountainDat dialog

class CMountainDat : public CStageRaceWnd<CPropertyPage>
{

// Construction
public:
	CMountainDat& operator =(CHalfStage &aMountainDat);
	CList<WORD,WORD&> m_climbpointshc;
	CList<WORD,WORD&> m_climbpoints1;
	CList<WORD,WORD&> m_climbpoints2;
	CList<WORD,WORD&> m_climbpoints3;
	CList<WORD,WORD&> m_climbpoints4;
	CList<WORD,WORD&> m_climbs;
	CMountainDat();
	~CMountainDat();

// Dialog Data
	//{{AFX_DATA(CMountainDat)
	enum { IDD = IDD_MOUNTAINDAT };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMountainDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMountainDat)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnSelchangePointsclimb1();
	afx_msg void OnSelchangePointsclimb2();
	afx_msg void OnSelchangePointsclimb3();
	afx_msg void OnSelchangePointsclimb4();
	afx_msg void OnSelchangeListclimb();
	afx_msg void OnSelchangePointsclimbhc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUNTAINDAT_H__8CB20E01_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
