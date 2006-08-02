// SplitterWndHidable.h: interface for the CSplitterWndHidable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERWNDHIDABLE_H__0248016F_E809_4796_BADE_F57F3C557DF4__INCLUDED_)
#define AFX_SPLITTERWNDHIDABLE_H__0248016F_E809_4796_BADE_F57F3C557DF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplitterWndHidable : public AW_CMultiViewSplitter
{
protected:
	virtual void GetPaneFromViewID(int nViewID, CPoint * pane);
	bool m_bLeftHidden;

public:
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	bool Hidden();
	void Hide();

	CSplitterWndHidable();

	// Generated message map functions
	//{{AFX_MSG(CSplitterWndHidable)
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SPLITTERWNDHIDABLE_H__0248016F_E809_4796_BADE_F57F3C557DF4__INCLUDED_)
