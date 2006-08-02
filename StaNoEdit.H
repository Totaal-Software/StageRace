#if !defined(AFX_STANOEDIT_H__AE6D54E9_0F97_4DD0_930B_D24E282F0E2B__INCLUDED_)
#define AFX_STANOEDIT_H__AE6D54E9_0F97_4DD0_930B_D24E282F0E2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaNoEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaNoEdit window

class CStaNoEdit : public CEdit
{
public:
	void SetValue( WORD nStaNo );
	WORD GetValue();
	bool Exist();
	CStaNoEdit();
	virtual ~CStaNoEdit();

	void AddStaNoObjectList(CStaNoObjectList* pList);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaNoEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
	CList<CStaNoObjectList*,CStaNoObjectList*&> m_list;

	//{{AFX_MSG(CStaNoEdit)
	afx_msg void OnKillfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STANOEDIT_H__AE6D54E9_0F97_4DD0_930B_D24E282F0E2B__INCLUDED_)
