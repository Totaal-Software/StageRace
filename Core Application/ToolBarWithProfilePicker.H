// ToolBarWithProfilePicker.h: interface for the CToolBarWithProfilePicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARWITHPROFILEPICKER_H__CDD1D042_A049_46F8_847C_FE77AC5C311B__INCLUDED_)
#define AFX_TOOLBARWITHPROFILEPICKER_H__CDD1D042_A049_46F8_847C_FE77AC5C311B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolBarWithProfilePicker : public CToolBar  
{
public:
	void RedrawDoc();
	void ResetDoc();
	void SetDoc(CStageRaceDoc*);
	void SetMainFrame(CMDIFrameWnd*);
	CToolBarWithProfilePicker();
	virtual ~CToolBarWithProfilePicker();

protected:
	void OnSelchange();
	afx_msg HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	afx_msg void OnShowWindow( BOOL, UINT );
	CStageRaceDoc* m_pDocument;
	CMDIFrameWnd* m_pMainFrame;
	CComboBox m_profilepicker;

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TOOLBARWITHPROFILEPICKER_H__CDD1D042_A049_46F8_847C_FE77AC5C311B__INCLUDED_)
