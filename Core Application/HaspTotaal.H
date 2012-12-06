// HaspTotaal.h: interface for the CHaspTotaal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASPTOTAAL_H__7C0B384A_38AB_47A3_B5FB_1B601059A01E__INCLUDED_)
#define AFX_HASPTOTAAL_H__7C0B384A_38AB_47A3_B5FB_1B601059A01E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHaspTotaal
{
public:
	CString GetVersionInfo( LPCTSTR lpFile, LPCTSTR lpEntry );
	CString GetReleaseNo();
	bool FastIsProtected();
	CString GetNiceLongVersion();
	CString GetRawLongVersion();
	CString GetVersionTitle();
	CString GetExtraLongVersion();
	CString GetProjectCodeName();
	CString GetVersionNo();
	CHaspTotaal();
	virtual ~CHaspTotaal();
	bool IsProtected();
	CString HaspContents();
	CString HaspID();
	bool HaspCheckSeed();
	bool HaspCheckDongle();
	bool CheckDongle(bool bSuppress=FALSE);

protected:
	struct VERSIONINFO
	{
		CString		m_ProjectCodeName;
		CString		m_VersionTitle;
		CString		m_VersionNo;
		CString		m_Release;
		CString		m_LongVersion;
		CString		m_ExtraLongVersion;
	} m_VersionInfo;

	bool m_protected;
	bool m_firstshot;
private:
	void Unlock();
	void Lock();
	HANDLE m_hSemaphore;
	int m_haspPwd2;
	int m_haspPwd1;
	int m_haspChecksum;
	int m_haspSeedCode;
};

#endif // !defined(AFX_HASPTOTAAL_H__7C0B384A_38AB_47A3_B5FB_1B601059A01E__INCLUDED_)
