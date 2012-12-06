#if !defined(AFX_MostAggressiveDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
#define AFX_MostAggressiveDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MostAggressiveDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMostAggressiveDat dialog

class CMostAggressiveDat : public CStageRaceWnd<CPropertyPage>
{

// Construction
public:
	CMostAggressiveDat& operator =(CHalfStage &aMostAggressiveDat);
	CList<WORD,WORD&> m_points;
	CMostAggressiveDat();
	~CMostAggressiveDat();

// Dialog Data
	//{{AFX_DATA(CMostAggressiveDat)
	enum { IDD = IDD_MOSTAGGRESSIVEDAT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMostAggressiveDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMostAggressiveDat)
	virtual BOOL OnInitDialog();
	afx_msg void OnRemove();
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MostAggressiveDAT_H__8CB20E00_EBBA_11D3_92DC_0040954019F4__INCLUDED_)
