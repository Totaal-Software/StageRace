#if !defined(AFX_STAGERACESTATUSBAR_H__5BA5D3E8_1F5D_40B1_A6CA_B1635E405674__INCLUDED_)
#define AFX_STAGERACESTATUSBAR_H__5BA5D3E8_1F5D_40B1_A6CA_B1635E405674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageRaceStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStageRaceStatusBar window

class CStageRaceStatusBar : public CStatusBar
{
public:
	void SetDocVersion(CStageRaceDoc*);
	void SetNoAction();
	void SetAction();
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	void SetKey( BOOL bLocked = TRUE );
	void ToggleShow(CFrameWnd* pMain);
	BOOL IsVisible();
	BOOL Create(CWnd* pParentWnd);
	CStageRaceStatusBar();
	virtual ~CStageRaceStatusBar();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageRaceStatusBar)
	//}}AFX_VIRTUAL

protected:
	CStatusGenerate m_prGenerate;
	CStatusStatic m_stKey;
	CStatusStatic m_stMessagingAction;
	CStatusActiveDoc m_cbActiveDoc;

	//{{AFX_MSG(CStageRaceStatusBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGERACESTATUSBAR_H__5BA5D3E8_1F5D_40B1_A6CA_B1635E405674__INCLUDED_)
