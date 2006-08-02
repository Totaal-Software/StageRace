#if !defined(AFX_PAGESETTINGSRANKING_H__78871FD4_BBC4_4CA4_9441_2F17333B2491__INCLUDED_)
#define AFX_PAGESETTINGSRANKING_H__78871FD4_BBC4_4CA4_9441_2F17333B2491__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettingsRanking.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettingsRanking dialog

class CPageSettingsRanking : public CPageSettings
{
// Construction
public:
	CPageSettingsRanking();
	~CPageSettingsRanking();

// Dialog Data
	//{{AFX_DATA(CPageSettingsRanking)
	enum { IDD = IDD_SETT_RANK };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettingsRanking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ArrangeEnabling();
	void OnOK();
	// Generated message map functions
	//{{AFX_MSG(CPageSettingsRanking)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSettingsrankingBunchsize();
	afx_msg void OnChangeSettingsrankingDepthintermediate();
	afx_msg void OnChangeSettingsrankingDepthstage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGSRANKING_H__78871FD4_BBC4_4CA4_9441_2F17333B2491__INCLUDED_)
