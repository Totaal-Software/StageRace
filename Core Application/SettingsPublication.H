// SettingsPublication.h: interface for the CSettingsPublication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSPUBLICATION_H__ECC22C28_2A71_4900_88C1_C004239C7F20__INCLUDED_)
#define AFX_SETTINGSPUBLICATION_H__ECC22C28_2A71_4900_88C1_C004239C7F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsPublication : public CSettings  
{
public:
	CSettingsPublication(CSettingsPublication*);
	void Serialize(CArchive &objAr);
	CSettingsPublication();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	CString m_companyName;
	CString m_companyURL;
	CString m_signature;
	CString m_mask1icon;
	CString m_mask2icon;
	CString m_mask3icon;
	CString m_sameGap;
	char	m_modulusCrossOutTeamNames;
	CMultiLanguage::REQUIREDLANGUAGES
			m_requiredLanguages;
};

#endif // !defined(AFX_SETTINGSPUBLICATION_H__ECC22C28_2A71_4900_88C1_C004239C7F20__INCLUDED_)
