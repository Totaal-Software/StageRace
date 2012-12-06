#if !defined(AFX_STANOLISTCTRL_H__FC6F6A38_6326_4E1C_8FC1_FE42865BF12E__INCLUDED_)
#define AFX_STANOLISTCTRL_H__FC6F6A38_6326_4E1C_8FC1_FE42865BF12E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaNoListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaNoListCtrl window

class CStaNoListCtrl : public CListCtrl
{
public:
	CStaNoListCtrl();
	void Select( WORD nStaNo );
	void AddLockedCompetitors( const CStaNoObjectList* pList )
	{
		m_pLockedCompetitors = /*(CStaNoList*)*/pList;
	}
	void AddCompetitorSource( const CCompetitorList* pList )
	{
		m_pCompetitorSource = /*(CCompetitorList*)*/pList;
	}
	WORD GetSelected();
	int Clear( WORD nStaNo );

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaNoListCtrl)
	//}}AFX_VIRTUAL


protected:
	void SortItems();
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	const CCompetitorList* m_pCompetitorSource;
	const CStaNoObjectList* m_pLockedCompetitors;
	int m_nColumnCount;
	//{{AFX_MSG(CStaNoListCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STANOLISTCTRL_H__FC6F6A38_6326_4E1C_8FC1_FE42865BF12E__INCLUDED_)
