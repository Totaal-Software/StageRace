// SettingsPanel.h: interface for the CSettingsPanel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSPANEL_H__5F42607A_7E6A_44D3_B580_9D696BA344BF__INCLUDED_)
#define AFX_SETTINGSPANEL_H__5F42607A_7E6A_44D3_B580_9D696BA344BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptionsPanel.h"

class CSettingsPanel : public COptionsPanel  
{
	DECLARE_MESSAGE_MAP()
public:
	bool IsScroll();

protected:
	void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_SETTINGSPANEL_H__5F42607A_7E6A_44D3_B580_9D696BA344BF__INCLUDED_)
