// SettingsAccess.h: interface for the CSettingsAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSACCESS_H__D56D4A6F_F107_450D_8E02_A4F366185A73__INCLUDED_)
#define AFX_SETTINGSACCESS_H__D56D4A6F_F107_450D_8E02_A4F366185A73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsAccess : public CSettings  
{
public:
	CSettingsAccess(CSettingsAccess*);
	void Serialize(CArchive &objAr);
	CSettingsAccess();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	CString m_key;
	CString m_password;
};

#endif // !defined(AFX_SETTINGSACCESS_H__D56D4A6F_F107_450D_8E02_A4F366185A73__INCLUDED_)
