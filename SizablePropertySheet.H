// SizablePropertySheet.h: interface for the CSizablePropertySheet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIZABLEPROPERTYSHEET_H__CF60B88E_8C0C_4A94_9909_3895CF4140E2__INCLUDED_)
#define AFX_SIZABLEPROPERTYSHEET_H__CF60B88E_8C0C_4A94_9909_3895CF4140E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSizablePropertySheet : public cdxCDynamicPropSheet  
{
public:
	void OnSysCommand(UINT nID, LPARAM);
	CSizablePropertySheet(LPCTSTR pszCaption, LPCTSTR pszRegistryName);

protected:
	BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	static CMapStringToPtr m_selectedtabs;
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SIZABLEPROPERTYSHEET_H__CF60B88E_8C0C_4A94_9909_3895CF4140E2__INCLUDED_)
