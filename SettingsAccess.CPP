// SettingsAccess.cpp: implementation of the CSettingsAccess class.
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

CSettingsAccess::CSettingsAccess()
{
	ValueAdd( IDS_SETT_ACCESS,
				CSettings::CSetting::GROUP, false, 0, 11 );
	ValueAdd( IDS_SETT_ACCESS_FREE,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_ACCESS );
	ValueAdd( IDS_SETT_ACCESS_PASSWORD,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_ACCESS );
	ValueAdd( IDS_SETT_ACCESS_KEY,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_ACCESS );
}

CSettingsAccess::CSettingsAccess(CSettingsAccess *pSettings)
{
	CSettingsAccess();
	*this = *pSettings;
}

CPageSettings* CSettingsAccess::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsAccess();
	// Make a copy of this settings
	CSettingsAccess*	pCopy = new CSettingsAccess();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsAccess::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsAccess* s1 = (CSettingsAccess*)&s;
	m_key		= s1->m_key;
	m_password	= s1->m_password;

	return *this;
}

void CSettingsAccess::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> m_key >> m_password;
		m_password = CSimpleCrypt::Decrypt(m_password);
	}
	else
	{
		ar << m_key << CSimpleCrypt::Encrypt(m_password);
	}
}
