#if !defined(AFX_IMPORTPREVIEW_H__4E20C722_EF58_4C95_B253_B055BF750987__INCLUDED_)
#define AFX_IMPORTPREVIEW_H__4E20C722_EF58_4C95_B253_B055BF750987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportPreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportPreview dialog

class CImportPreview : public CStageRaceWnd<CDialog>
{
// Construction
public:
	void UpdatePreview();
	bool m_changeHandled;
	CString m_contents;
	CHARFORMAT m_cfRank;
	CHARFORMAT m_cfTime;
	CHARFORMAT m_cfStaNo;
	CImportPreview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportPreview)
	enum { IDD = IDD_ARRIVALIMPORTPREVIEW };
	int		m_headerSize;
	int		m_staNoEnd;
	int		m_staNoStart;
	int		m_timeEnd;
	int		m_timeStart;
	int		m_rankEnd;
	int		m_rankStart;
	int		m_importType;
	int		m_decimals;
	BOOL	m_rank;
	int		m_rankCol;
	int		m_separation;
	int		m_staNoCol;
	int		m_timeCol;
	int		m_timeNotation;
	int		m_separator;
	int		m_event;
	int		m_heat;
	int		m_round;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportPreview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportPreview)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeArrivalimportstanoend();
	afx_msg void OnChangeArrivalimportstanostart();
	afx_msg void OnChangeArrivalimporttimeend();
	afx_msg void OnChangeArrivalimporttimestart();
	afx_msg void OnChangeArrivalimportheadersize();
	virtual void OnOK();
	afx_msg void OnChangeArrivalimportrankend();
	afx_msg void OnChangeArrivalimportrankstart();
	afx_msg void OnArrivalimporttype();
	afx_msg void OnArrivalimporttype1();
	afx_msg void OnArrivalimportseparation1();
	afx_msg void OnArrivalimportseparation();
	afx_msg void OnChangeArrivalimportrankcol();
	afx_msg void OnChangeArrivalimportstanocol();
	afx_msg void OnChangeArrivalimporttimecol();
	afx_msg void OnArrivalimportalgeoptic();
	afx_msg void OnArrivalimportomegacl();
	afx_msg void OnSelchangeArrivalimportseparator();
	afx_msg void OnArrivalimportambchronx();
	afx_msg void OnArrivalimportlynxfinishlynx();
	afx_msg void OnArrivalimportskunkwarettware();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTPREVIEW_H__4E20C722_EF58_4C95_B253_B055BF750987__INCLUDED_)
