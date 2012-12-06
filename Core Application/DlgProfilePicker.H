#if !defined(AFX_DLGPROFILEPICKER_H__3906062E_6ABD_49E4_9871_17B6447E00D3__INCLUDED_)
#define AFX_DLGPROFILEPICKER_H__3906062E_6ABD_49E4_9871_17B6447E00D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProfilePicker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProfilePicker dialog

class CDlgProfilePicker : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CDlgProfilePicker(CAllSettings*, bool bLock, HANDLE hSemaphore);

// Dialog Data
	//{{AFX_DATA(CDlgProfilePicker)
	enum { IDD = IDD_DLGPROFILEPICKER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProfilePicker)
	public:
	virtual int DoModal();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HANDLE m_hSemaphore;
	bool m_bLocked;
	bool m_bChanged;
	void DrawList(int select = -1);
	CAllSettings * m_pAllsettings;
	// Generated message map functions
	//{{AFX_MSG(CDlgProfilePicker)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRename();
	afx_msg void OnSetcurrent();
	afx_msg void OnDblclkList();
	afx_msg void OnAdjustfilenames();
	afx_msg void OnUseprofilenames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROFILEPICKER_H__3906062E_6ABD_49E4_9871_17B6447E00D3__INCLUDED_)
