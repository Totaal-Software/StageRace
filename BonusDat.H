#if !defined(AFX_BONUSDAT_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_BONUSDAT_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BonusDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBonusDat dialog

class CBonusDat : public CStageRaceWnd<CPropertyPage>
{
// Construction
public:
	CBonusDat& operator =(CHalfStage &aBonusDat);
	CList<WORD,WORD&> m_bonusesIntermediate;
	CList<WORD,WORD&> m_bonusesFinish;
	CBonusDat();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBonusDat)
	enum { IDD = IDD_BONUSDAT };
	int		m_bonusesCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBonusDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBonusDat)
	afx_msg void OnAdd();
	afx_msg void OnSelchangeBonussprint();
	afx_msg void OnSelchangeBonusfinish();
	afx_msg void OnRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnStandard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BONUSDAT_H__8CB20E02_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
