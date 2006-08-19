// SettingsUpload.cpp: implementation of the CSettingsUpload class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSettingsUpload::CSettingsUpload()
{
	ValueAdd( IDS_SETT_UPLOAD,
				CSettings::CSetting::GROUP, false, 0, 12 );
	ValueAdd( IDS_SETT_UPLOAD_ALLOW,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_UPLOAD );
	ValueAdd( IDS_SETT_UPLOAD_ADDFOLDER,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_UPLOAD );
	ValueAdd( IDS_SETT_MAIL,
				CSettings::CSetting::GROUP, false, 0, 21 );
	ValueAdd( IDS_SETT_MAIL_BCC,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_MAIL );
}

CSettingsUpload::CSettingsUpload(CSettingsUpload *pSettings)
{
	CSettingsUpload();
	*this = *pSettings;
}

CPageSettings* CSettingsUpload::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsUpload();
	// Make a copy of this settings
	CSettingsUpload*	pCopy = new CSettingsUpload();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsUpload::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsUpload* s1 = (CSettingsUpload*)&s;
	m_password		= s1->m_password;
	m_username		= s1->m_username;	
	m_hostAddress	= s1->m_hostAddress;
	m_remoteDir		= s1->m_remoteDir;
	m_mailRecipients= s1->m_mailRecipients;

	return *this;
}

void CSettingsUpload::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsLoading())
	{
		if( *(int*)(ar.m_pDocument) >= 3120 )
		{
			ar >> m_password >> m_username >> m_hostAddress >> m_remoteDir >> m_mailRecipients;
			m_password = CSimpleCrypt::Decrypt(m_password);
		}
		else
		{
			if( *(int*)(ar.m_pDocument) >= 2030 )
			{
				ar >> m_password >> m_username >> m_hostAddress >> m_remoteDir;
				m_password = CSimpleCrypt::Decrypt(m_password);
			}
			else
			{
				ar >> m_password >> m_username >> m_hostAddress >> m_remoteDir;
			}
		}
	}
	else
	{
		ar << CSimpleCrypt::Encrypt(m_password) << m_username << m_hostAddress << m_remoteDir << m_mailRecipients;
	}
}
