#if !defined(AFX_TIMEEDIT_H__D6F158C7_215D_4E2A_A580_24E83900D044__INCLUDED_)
#define AFX_TIMEEDIT_H__D6F158C7_215D_4E2A_A580_24E83900D044__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeEdit window

class CTimeEdit : public CmEdit	
{
// Construction
public:
	CTimeEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetTime(DWORD);
	void Init(unsigned short nSizeT=3, unsigned short nSizeH=1, bool bBrackets=false);
	DWORD GetTime();
	virtual ~CTimeEdit();

	// Generated message map functions
protected:
	unsigned short m_nSizeHours;
	CStageTime* m_pTime;
	//{{AFX_MSG(CTimeEdit)
	afx_msg void OnChange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEEDIT_H__D6F158C7_215D_4E2A_A580_24E83900D044__INCLUDED_)
