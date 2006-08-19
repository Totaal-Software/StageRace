// SettingsUpload.h: interface for the CSettingsUpload class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSUPLOAD_H__CF2DE107_4CA2_4C17_81B1_997B141521C5__INCLUDED_)
#define AFX_SETTINGSUPLOAD_H__CF2DE107_4CA2_4C17_81B1_997B141521C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsUpload : public CSettings  
{
public:
	CSettingsUpload(CSettingsUpload*);
	void Serialize(CArchive &objAr);
	CSettingsUpload();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	CString m_password;
	CString m_username;
	CString m_hostAddress;
	CString m_remoteDir;
	CString m_mailRecipients;
};

#endif // !defined(AFX_SETTINGSUPLOAD_H__CF2DE107_4CA2_4C17_81B1_997B141521C5__INCLUDED_)
