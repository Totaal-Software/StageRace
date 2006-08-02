#if !defined(AFX_CHECKIMPORTFILE_H__F95A660D_7A77_42BA_B0B4_BC6B00928066__INCLUDED_)
#define AFX_CHECKIMPORTFILE_H__F95A660D_7A77_42BA_B0B4_BC6B00928066__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckImportFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckImportFile dialog

class CCheckImportFile : public CStageRaceWnd<CDialog>
{
// Construction
public:
	CCheckImportFile(CString cFilename);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckImportFile)
	enum { IDD = IDD_CHECKIMPORTFILE };
	protected:
	CString	m_cFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckImportFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckImportFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTime m_fileTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKIMPORTFILE_H__F95A660D_7A77_42BA_B0B4_BC6B00928066__INCLUDED_)
