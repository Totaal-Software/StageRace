// AllSettings.h: interface for the CAllSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALLSETTINGS_H__9CE86FC9_0290_43F6_80DA_4F0375F5628B__INCLUDED_)
#define AFX_ALLSETTINGS_H__9CE86FC9_0290_43F6_80DA_4F0375F5628B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum SETTINGS_TYPE
{
	SETT_GENERAL,
	SETT_RANKING,
	SETT_PUBLICATION,
	SETT_HTML,
	SETT_UPLOAD,
	SETT_ACCESS,

	SETT_NONE
};
#define SETT_MAX SETT_ACCESS
#define SETT_SIZE (SETT_MAX+1)

class CAllSettings : public CObject  
{
public:
	CString ProfilesGetCurrentFileName() const;
	void ProfilesSetUseProfileNames(bool);
	bool ProfilesGetUseProfileNames() const;
	void ProfilesSetAdjustFileNames(bool);
	bool ProfilesGetAdjustFileNames() const;
	bool ProfilesAdd();
	bool ProfilesRename(unsigned short);
	CString ProfilesGetName(unsigned short) const;
	unsigned short ProfilesGetCount() const;
	void ProfilesSetName(unsigned short,CString);
	void ProfilesSetCurrent(unsigned short);
	unsigned short ProfilesGetCurrent() const;
	void ProfilesAdd(CString name);
	void ProfilesRemove(unsigned short);
	CSettings* GetSettings( SETTINGS_TYPE ) const;
	bool ValueGet( DWORD nID ) const;
	int Settings(HANDLE hSemaphore);
	int Profiles(bool bLock, HANDLE hSemaphore);
	CAllSettings();
	virtual ~CAllSettings();
	void Serialize(CArchive & ar);

protected:
	bool m_bUseProfileNames;
	bool m_bAdjustFileNames;
	void Add( CSettings* pSet );
	unsigned short m_currentprofile;
	CTypedPtrArray<CPtrArray,CSettings*> m_allsettings;
	CArray<CString,CString&> m_profilenames;
};

#endif // !defined(AFX_ALLSETTINGS_H__9CE86FC9_0290_43F6_80DA_4F0375F5628B__INCLUDED_)
