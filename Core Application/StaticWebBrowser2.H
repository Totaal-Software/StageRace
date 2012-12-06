// StaticWebBrowser2.h: interface for the CStaticWebBrowser2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICWEBBROWSER2_H__CF5614F4_FF62_4BE8_8DDB_38A46CA529DA__INCLUDED_)
#define AFX_STATICWEBBROWSER2_H__CF5614F4_FF62_4BE8_8DDB_38A46CA529DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaticWebBrowser2 : public CWebBrowser2
{
public:

protected:
	BOOL PreTranslateMessage(MSG *pMsg);
};

#endif // !defined(AFX_STATICWEBBROWSER2_H__CF5614F4_FF62_4BE8_8DDB_38A46CA529DA__INCLUDED_)
