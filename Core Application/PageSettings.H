#if !defined(AFX_PAGESETTINGS_H__BC5C71BB_EC82_4176_AA3E_1F343EBC47F7__INCLUDED_)
#define AFX_PAGESETTINGS_H__BC5C71BB_EC82_4176_AA3E_1F343EBC47F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSettings dialog

class CPageSettings : public CStageRaceWnd<cdxCDynamicPropPage>
{
// Construction
public:
	bool GetBinariesMaximized();
	HWND Get();
	void Add( HWND hwnd );
	~CPageSettings();
	CSettings* m_pSettings;
	CPageSettings(CHelp::HELP_TOPIC helptopic, UINT nID);

// Dialog Data
	//{{AFX_DATA(CPageSettings)
	protected:
	CSettingsPanel m_ctrlBinarySettings;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ToggleBigBinaries();
	bool m_bBinariesMaximized;
	bool m_bActualBinariesMaximized;
	virtual void ArrangeEnabling()=0;
	void OnSettingsBinarysettingsSelChange(NMHDR *pNMHDR,LRESULT *pResult);
	void Connect(CArray<UINT,UINT&>& done, CMap<UINT,UINT&,int,int&>& mapdone, UINT nGroupID);
	// Generated message map functions
	//{{AFX_MSG(CPageSettings)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETTINGS_H__BC5C71BB_EC82_4176_AA3E_1F343EBC47F7__INCLUDED_)
