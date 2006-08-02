#if !defined(AFX_ARRIVALLISTCTRL_H__2C9138A3_B75C_4378_B774_F0F5C7274BFF__INCLUDED_)
#define AFX_ARRIVALLISTCTRL_H__2C9138A3_B75C_4378_B774_F0F5C7274BFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArrivalListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArrivalListCtrl window

class CArrivalListCtrl : public CStaNoListCtrl
{
public:
	CArrivalListCtrl();
	enum ARRIVALLISTTYPES
	{
		ALT_TTORDERAVAILABLE,
		ALT_TTORDERARRIVAL,
		ALT_TTARRIVAL,
		ALT_TTAVAILABLE,
		ALT_ARRIVAL,
		ALT_AVAILABLE,
		ALT_ARRIVALRANKONLY,
		ALT_AVAILABLERANKONLY,
		ALT_CORRECTION
	};
private:
	ARRIVALLISTTYPES m_type;
	unsigned short m_accuracy;
	const CArrivalList* m_pHighlightcallback;
public:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArrivalListCtrl)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SelectAll();
	void Draw( CArrival* pArr );
	void DrawList( CArrivalList* pList );
	void Init( unsigned short accuracy, ARRIVALLISTTYPES altType, const CArrivalList* pa=NULL );

	// Generated message map functions
protected:
	void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	int DrawIntern(CArrival *pArr, int nItem);
	//{{AFX_MSG(CArrivalListCtrl)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARRIVALLISTCTRL_H__2C9138A3_B75C_4378_B774_F0F5C7274BFF__INCLUDED_)
