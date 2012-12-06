// SettingsGeneral.cpp: implementation of the CSettingsGeneral class.
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

CSettingsGeneral::CSettingsGeneral()
{
	ValueAdd( IDS_SETT_GNRL_MASKS,
				CSettings::CSetting::GROUP, false, 0, 5 );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE1,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE2,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE3,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE4,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE5,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE6,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE7,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE8,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE9,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_USE10,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );
	ValueAdd( IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_MASKS );

	ValueAdd( IDS_SETT_GNRL_INPUTACCURACY,
				CSettings::CSetting::GROUP, false, 0, 4 );
	ValueAdd( IDS_SETT_GNRL_INPUTACCURACY_100,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_GNRL_INPUTACCURACY );
	ValueAdd( IDS_SETT_GNRL_INPUTACCURACY_1000,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_GNRL_INPUTACCURACY );

	ValueAdd( IDS_SETT_GNRL_PROLOGUE,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_GNRL_PROLOGUE_EXISTS,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_GNRL_PROLOGUE );

	ValueAdd( IDS_SETT_GNRL_STAGENUMBERING,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_GNRL_STAGENUMBERING_SUPPRESS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_GNRL_STAGENUMBERING );
}

CSettingsGeneral::CSettingsGeneral(CSettingsGeneral *pSettings)
{
	CSettingsGeneral();
	*this = *pSettings;
}

CPageSettings* CSettingsGeneral::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsGeneral();
	// Make a copy of this settings
	CSettingsGeneral*	pCopy = new CSettingsGeneral();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsGeneral::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsGeneral* s1		= (CSettingsGeneral*)&s;
	m_eventName					= s1->m_eventName;
	m_eventSubTitle				= s1->m_eventSubTitle;
	m_organiser					= s1->m_organiser;
	m_dates						= s1->m_dates;
	m_location					= s1->m_location;
	m_category					= s1->m_category;
	m_mask1						= s1->m_mask1;
	m_mask2						= s1->m_mask2;
	m_mask3						= s1->m_mask3;
	m_mask4						= s1->m_mask4;
	m_mask5						= s1->m_mask5;
	m_mask6						= s1->m_mask6;
	m_mask7						= s1->m_mask7;
	m_mask8						= s1->m_mask8;
	m_mask9						= s1->m_mask9;
	m_mask10					= s1->m_mask10;

	m_cl_sponsor_general		= s1->m_cl_sponsor_general;
	m_cl_sponsor_teams			= s1->m_cl_sponsor_teams;
	m_cl_sponsor_sprint			= s1->m_cl_sponsor_sprint;
	m_cl_sponsor_climb			= s1->m_cl_sponsor_climb;
	m_cl_sponsor_points			= s1->m_cl_sponsor_points;
	m_cl_sponsor_mostaggressive	= s1->m_cl_sponsor_mostaggressive;
	m_cl_sponsor_mask1			= s1->m_cl_sponsor_mask1;
	m_cl_sponsor_mask2			= s1->m_cl_sponsor_mask2;
	m_cl_sponsor_mask3			= s1->m_cl_sponsor_mask3;
	m_cl_sponsor_mask4			= s1->m_cl_sponsor_mask4;
	m_cl_sponsor_mask5			= s1->m_cl_sponsor_mask5;
	m_cl_sponsor_mask6			= s1->m_cl_sponsor_mask6;
	m_cl_sponsor_mask7			= s1->m_cl_sponsor_mask7;
	m_cl_sponsor_mask8			= s1->m_cl_sponsor_mask8;
	m_cl_sponsor_mask9			= s1->m_cl_sponsor_mask9;
	m_cl_sponsor_mask10			= s1->m_cl_sponsor_mask10;
		
	return *this;
}

void CSettingsGeneral::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_eventName << m_eventSubTitle << m_organiser << m_dates << 
			m_location << m_category << m_mask1 << m_mask2 << m_mask3 <<
			m_mask4 << m_mask5 << m_mask6 << m_mask7 << m_mask8 << m_mask9 << m_mask10 <<
			m_cl_sponsor_general << m_cl_sponsor_teams << m_cl_sponsor_sprint <<
			m_cl_sponsor_climb << m_cl_sponsor_points << m_cl_sponsor_mostaggressive <<
			m_cl_sponsor_mask1 << m_cl_sponsor_mask2 << m_cl_sponsor_mask3 <<
			m_cl_sponsor_mask4 << m_cl_sponsor_mask5 << m_cl_sponsor_mask6 <<
			m_cl_sponsor_mask7 << m_cl_sponsor_mask8 << m_cl_sponsor_mask9 << m_cl_sponsor_mask10;
	}
	else
	{
		if( *(int*)(ar.m_pDocument) >= 3000 )
		{
			ar >> m_eventName >> m_eventSubTitle >> m_organiser >> m_dates >> 
				m_location >> m_category >> m_mask1 >> m_mask2 >> m_mask3 >>
				m_mask4 >> m_mask5 >> m_mask6 >> m_mask7 >> m_mask8 >> m_mask9 >> m_mask10 >>
				m_cl_sponsor_general >> m_cl_sponsor_teams >> m_cl_sponsor_sprint >>
				m_cl_sponsor_climb >> m_cl_sponsor_points >> m_cl_sponsor_mostaggressive >>
				m_cl_sponsor_mask1 >> m_cl_sponsor_mask2 >> m_cl_sponsor_mask3 >>
				m_cl_sponsor_mask4 >> m_cl_sponsor_mask5 >> m_cl_sponsor_mask6 >>
				m_cl_sponsor_mask7 >> m_cl_sponsor_mask8 >> m_cl_sponsor_mask9 >> m_cl_sponsor_mask10;
		}
		else
		{
			ar >> m_eventName >> m_eventSubTitle >> m_organiser >> m_dates >> 
				m_location >> m_category >> m_mask1 >> m_mask2 >> m_mask3;
			ValueSet( IDS_SETT_GNRL_STAGENUMBERING_SUPPRESS, false );
		}
	}
}
