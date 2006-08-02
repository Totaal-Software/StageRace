// SettingsHTML.h: interface for the CSettingsHTML class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSHTML_H__42DEB83A_50D6_4C0E_B15A_A0FA7CDE1E03__INCLUDED_)
#define AFX_SETTINGSHTML_H__42DEB83A_50D6_4C0E_B15A_A0FA7CDE1E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsHTML : public CSettings  
{
public:
	CSettingsHTML(CSettingsHTML*);
	CString m_customHTMLBottom;
	CString m_customHTMLTop;
	void Serialize(CArchive &objAr);
	CSettingsHTML();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	CString m_eventLogo;
	CString m_styleSheet;
	CString m_titleColor;
	CString m_descriptColor;
	CString m_bodyColor;
	CString m_bgColor;
	int m_fontsize;
	int m_columnspacing;
};

#endif // !defined(AFX_SETTINGSHTML_H__42DEB83A_50D6_4C0E_B15A_A0FA7CDE1E03__INCLUDED_)
