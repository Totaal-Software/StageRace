#if !defined(AFX_MASKAPPLYDLG_H__60118D3D_835A_4DDA_84CE_74265FE6FE99__INCLUDED_)
#define AFX_MASKAPPLYDLG_H__60118D3D_835A_4DDA_84CE_74265FE6FE99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaskApplyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaskApplyDlg dialog

class CMaskApplyDlg : public CStageRaceWnd<CDialog>
{
// Construction
public:
	bool IsMatch( CCompetitor* );
	CMaskApplyDlg(CStageRaceDoc* pDoc);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaskApplyDlg)
	enum { IDD = IDD_MASKAPPLY };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskApplyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStageRaceDoc* m_pDoc;

	// Generated message map functions
	//{{AFX_MSG(CMaskApplyDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASKAPPLYDLG_H__60118D3D_835A_4DDA_84CE_74265FE6FE99__INCLUDED_)
