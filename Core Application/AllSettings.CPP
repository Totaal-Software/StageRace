// AllSettings.cpp: implementation of the CAllSettings class.
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

CAllSettings::CAllSettings()
{
	m_allsettings.Add( new CSettingsGeneral );
	m_allsettings.Add( new CSettingsRanking );
	m_allsettings.Add( new CSettingsPublication );
	m_allsettings.Add( new CSettingsHTML );
	m_allsettings.Add( new CSettingsUpload );
	m_allsettings.Add( new CSettingsAccess );

	m_profilenames.Add( LoadStr( IDS_DIV95 ) );

	m_currentprofile = 0;

	m_bAdjustFileNames = true;
	m_bUseProfileNames = true;
}

CAllSettings::~CAllSettings()
{
	for( int i = m_allsettings.GetSize(); i; i-- )
		if( m_allsettings.GetAt(i-1) )
			delete m_allsettings.GetAt(i-1);
}

void CAllSettings::Add(CSettings *pSet)
{
	m_allsettings.Add( pSet );
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CAllSettings::Serialize(CArchive & objAr)
{
	CObject::Serialize(objAr);

	if ( objAr.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		// First profile
		for( int i=0; i<=SETT_MAX; i++ )
			m_allsettings.GetAt( i )->Serialize( objAr );
		// Profile names
		m_profilenames.Serialize( objAr );
		// Additional profiles
		for( int pr=1; pr<ProfilesGetCount(); pr++ )
		{
			for( int i=0; i<=SETT_MAX; i++ )
			{
				if( m_allsettings.GetAt( pr*SETT_SIZE + i ) )
				{
					objAr << (UINT)(SETTINGS_TYPE)i;
					m_allsettings.GetAt( pr*SETT_SIZE + i )->Serialize( objAr );
				}
			}
			objAr << (UINT)(SETTINGS_TYPE)SETT_NONE;
		}
		// Current profile
		objAr << m_currentprofile;
		// File names settings
		char temp;
		temp = ( m_bAdjustFileNames?0x2:0x0 ) | ( m_bUseProfileNames?0x1:0x0 );
		objAr << temp;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////

		// FILE STRUCTURE AVAILABLE SINCE 3.00
		if( *(int*)(objAr.m_pDocument) >= 3000 )
		{
			// First profile
			for( int i=0; i<=SETT_MAX; i++ )
				m_allsettings.GetAt( i )->Serialize( objAr );
			// Profile names
			m_profilenames.Serialize( objAr );
			// Additional profiles
			for( int pr=1; pr<m_profilenames.GetSize(); pr++ )
			{
				for( int i=0; i<=SETT_MAX; i++ )
					m_allsettings.Add(NULL);

				SETTINGS_TYPE t;
				do
				{
					UINT temp;
					objAr >> temp;
					t = (SETTINGS_TYPE)temp;
					switch( t )
					{
						case SETT_GENERAL:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsGeneral );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_RANKING:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsRanking );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_PUBLICATION:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsPublication );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_HTML:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsHTML );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_UPLOAD:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsUpload );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_ACCESS:
							m_allsettings.SetAt( pr*SETT_SIZE + t, new CSettingsAccess );
							m_allsettings.GetAt( pr*SETT_SIZE + t )->Serialize( objAr );
							break;
						case SETT_NONE:
							// do nothing
							break;
					}
				}
				while( t!=SETT_NONE );
			}
			// Current profile
			objAr >> m_currentprofile;
			
			// File names settings
			char temp;
			objAr >> temp;
			m_bAdjustFileNames = (temp & 0x2)>0;
			m_bUseProfileNames = (temp & 0x1)>0;
		}
		else
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			if( *(int*)(objAr.m_pDocument) >= 2000 )
			{
				for( int i=0; i<m_allsettings.GetSize(); i++ )
					m_allsettings.GetAt( i )->Serialize( objAr );
			}
			else
			{ // FILE STRUCTURE AVAILABLE SINCE 1.20
				if( *(int*)(objAr.m_pDocument) >= 1200 )
				{
					//Main trialdat
					int n1, n2, n3;
					objAr
						>> ((CSettingsGeneral*)m_allsettings[0])->m_category
						>> ((CSettingsGeneral*)m_allsettings[0])->m_dates
						>> ((CSettingsGeneral*)m_allsettings[0])->m_eventName
						>> ((CSettingsGeneral*)m_allsettings[0])->m_eventSubTitle
						>> ((CSettingsGeneral*)m_allsettings[0])->m_location
						>> ((CSettingsGeneral*)m_allsettings[0])->m_organiser
						>> n1
						>> n2
						>> n3
						>> ((CSettingsGeneral*)m_allsettings[0])->m_mask1
						>> ((CSettingsGeneral*)m_allsettings[0])->m_mask2
						>> ((CSettingsGeneral*)m_allsettings[0])->m_mask3;
					m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE1, n1!=0 );
					m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE2, n2!=0 );
					m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE3, n3!=0 );

					// Publication
					objAr
						>> ((CSettingsPublication*)m_allsettings[2])->m_companyURL
						>> ((CSettingsPublication*)m_allsettings[2])->m_companyName
						>> n1
						>> ((CSettingsPublication*)m_allsettings[2])->m_signature
						>> n2;
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE, n1!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP, n2!=0 );
					objAr
						>> n1	// SignOutsOnClass // Obsolete for the moment
						>> n2;	// SignOutsOnCommu // Obsolete for the moment
					objAr
						>> n1;
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATE, !n1 );
					objAr
						>> n1;
					m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_100, n1==1 );
					m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_1000, n1==0 );
					objAr
						>> n1;
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COMMNOS_USE, n1!=0 );
					objAr
						>> n1
						>> n2;	// ShowFooterReport // Obsolete for the moment
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMNAME, n1==0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODEWITHOUTCOLUMNTITLE, n1==0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODE, n1!=0 );

					//Ranking
					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS_ONSUMRANKINGS_ONLATESTRANKING, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONSUMRANKINGS_ONLATESTRANKING, n1==1 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING, n1==2 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONMOSTHIGHRANKINGS, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONLATESTRANKING, n1==1 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONMOSTHIGHRANKINGS, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONLATESTRANKING, n1==1 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_INCLUDEFINISH, n1!=0 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERATE, n1!=0 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHOUTSUMRANKINGS, n1==1 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_FIRST, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_LAST, n1==1 );

					objAr >> n1;
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS, n1==0 );
					m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHOUTSUMRANKINGS, n1==1 );

					objAr >> n1;
					((CSettingsRanking*)m_allsettings[1])->m_bunchSize = (char)n1;

					// Presentation
					objAr
						>> ((CSettingsHTML*)m_allsettings[3])->m_titleColor
						>> ((CSettingsHTML*)m_allsettings[3])->m_descriptColor
						>> ((CSettingsHTML*)m_allsettings[3])->m_bodyColor
						>> ((CSettingsHTML*)m_allsettings[3])->m_bgColor
						>> ((CSettingsHTML*)m_allsettings[3])->m_eventLogo
						>> ((CSettingsHTML*)m_allsettings[3])->m_styleSheet
						>> n1;
					m_allsettings[3]->ValueSet( IDS_SETT_HTML_TOC_EVENTNAME, n1==0 );
					m_allsettings[3]->ValueSet( IDS_SETT_HTML_TOC_INDEXHTML, n1==1 );

					objAr
						>> n1
						>> n2
						>> n3;
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1, n1!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2, n2!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3, n3!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1, n1!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2, n2!=0 );
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3, n3!=0 );
					objAr
						>> n1
						>> n2;
					((CSettingsPublication*)m_allsettings[2])->m_modulusCrossOutTeamNames = (char)n2;
					m_allsettings[2]->ValueSet( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES, n1!=0 );
					objAr
						>> ((CSettingsPublication*)m_allsettings[2])->m_mask1icon
						>> ((CSettingsPublication*)m_allsettings[2])->m_mask2icon
						>> ((CSettingsPublication*)m_allsettings[2])->m_mask3icon;
					// Upload
					objAr
						>> n1
						>> ((CSettingsUpload*)m_allsettings[4])->m_hostAddress
						>> ((CSettingsUpload*)m_allsettings[4])->m_username
						>> ((CSettingsUpload*)m_allsettings[4])->m_password
						>> ((CSettingsUpload*)m_allsettings[4])->m_remoteDir;
					m_allsettings[4]->ValueSet( IDS_SETT_UPLOAD_ALLOW, n1!=0 );
					// Access
					objAr
						>> n1
						>> ((CSettingsAccess*)m_allsettings[5])->m_key
						>> ((CSettingsAccess*)m_allsettings[5])->m_password;
					m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_FREE, n1==0 );
					m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_PASSWORD, n1==1 );
					m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_KEY, n1==2 );
				}
				else
				{ // FILE STRUCTURE AVAILABLE SINCE 1.12
					if( *(int*)(objAr.m_pDocument) >= 1120 )
					{
						//Main trialdat
						int n1, n2, n3;
						objAr
							>> ((CSettingsGeneral*)m_allsettings[0])->m_category
							>> ((CSettingsGeneral*)m_allsettings[0])->m_dates
							>> ((CSettingsGeneral*)m_allsettings[0])->m_eventName
							>> ((CSettingsGeneral*)m_allsettings[0])->m_eventSubTitle
							>> ((CSettingsGeneral*)m_allsettings[0])->m_location
							>> ((CSettingsGeneral*)m_allsettings[0])->m_organiser
							>> n1
							>> n2
							>> n3
							>> ((CSettingsGeneral*)m_allsettings[0])->m_mask1
							>> ((CSettingsGeneral*)m_allsettings[0])->m_mask2
							>> ((CSettingsGeneral*)m_allsettings[0])->m_mask3;
						m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE1, n1!=0 );
						m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE2, n2!=0 );
						m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE3, n3!=0 );

						// Publication
						objAr
							>> ((CSettingsPublication*)m_allsettings[2])->m_companyURL
							>> ((CSettingsPublication*)m_allsettings[2])->m_companyName
							>> n1
							>> ((CSettingsPublication*)m_allsettings[2])->m_signature
							>> n2;
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE, n1!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP, n2!=0 );
						objAr
							>> n1	// SignOutsOnClass // Obsolete for the moment
							>> n2;	// SignOutsOnCommu // Obsolete for the moment
						objAr
							>> n1;
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATE, !n1 );
						objAr
							>> n1;
						m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_100, n1==1 );
						m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_1000, n1==0 );
						objAr
							>> n1;
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COMMNOS_USE, n1!=0 );
						objAr
							>> n1
							>> n2;	// ShowFooterReport // Obsolete for the moment
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMNAME, n1==0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODEWITHOUTCOLUMNTITLE, n1==0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODE, n1!=0 );

						//Ranking
						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS_ONSUMRANKINGS_ONLATESTRANKING, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONSUMRANKINGS_ONLATESTRANKING, n1==1 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING, n1==2 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONMOSTHIGHRANKINGS, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONLATESTRANKING, n1==1 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONMOSTHIGHRANKINGS, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONLATESTRANKING, n1==1 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_INCLUDEFINISH, n1!=0 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERATE, n1!=0 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHOUTSUMRANKINGS, n1==1 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_FIRST, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_LAST, n1==1 );

						objAr >> n1;
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS, n1==0 );
						m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHOUTSUMRANKINGS, n1==1 );

						objAr >> n1;
						((CSettingsRanking*)m_allsettings[1])->m_bunchSize = (char)n1;

						// Presentation
						objAr
							>> ((CSettingsHTML*)m_allsettings[3])->m_titleColor
							>> ((CSettingsHTML*)m_allsettings[3])->m_descriptColor
							>> ((CSettingsHTML*)m_allsettings[3])->m_bodyColor
							>> ((CSettingsHTML*)m_allsettings[3])->m_bgColor
							>> ((CSettingsHTML*)m_allsettings[3])->m_eventLogo;

						objAr
							>> n1
							>> n2
							>> n3;
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1, n1!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2, n2!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3, n3!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1, n1!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2, n2!=0 );
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3, n3!=0 );
						objAr
							>> n1
							>> n2;
						((CSettingsPublication*)m_allsettings[2])->m_modulusCrossOutTeamNames = (char)n1;
						m_allsettings[2]->ValueSet( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES, n2!=0 );
						objAr
							>> ((CSettingsPublication*)m_allsettings[2])->m_mask1icon
							>> ((CSettingsPublication*)m_allsettings[2])->m_mask2icon
							>> ((CSettingsPublication*)m_allsettings[2])->m_mask3icon;
						// Upload
						objAr
							>> n1
							>> ((CSettingsUpload*)m_allsettings[4])->m_hostAddress
							>> ((CSettingsUpload*)m_allsettings[4])->m_username
							>> ((CSettingsUpload*)m_allsettings[4])->m_password
							>> ((CSettingsUpload*)m_allsettings[4])->m_remoteDir;
						m_allsettings[4]->ValueSet( IDS_SETT_UPLOAD_ALLOW, n1!=0 );
						// Access
						objAr
							>> n1
							>> ((CSettingsAccess*)m_allsettings[5])->m_key
							>> ((CSettingsAccess*)m_allsettings[5])->m_password;
						m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_FREE, n1==0 );
						m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_PASSWORD, n1==1 );
					}
					else
					{ // FILE STRUCTURE AVAILABLE SINCE 1.07
						if( *(int*)(objAr.m_pDocument) >= 1070 )
						{
							//Main trialdat
							int n1, n2, n3;
							objAr
								>> ((CSettingsGeneral*)m_allsettings[0])->m_category
								>> ((CSettingsGeneral*)m_allsettings[0])->m_dates
								>> ((CSettingsGeneral*)m_allsettings[0])->m_eventName
								>> ((CSettingsGeneral*)m_allsettings[0])->m_eventSubTitle
								>> ((CSettingsGeneral*)m_allsettings[0])->m_location
								>> ((CSettingsGeneral*)m_allsettings[0])->m_organiser
								>> n1
								>> n2
								>> n3
								>> ((CSettingsGeneral*)m_allsettings[0])->m_mask1
								>> ((CSettingsGeneral*)m_allsettings[0])->m_mask2
								>> ((CSettingsGeneral*)m_allsettings[0])->m_mask3;
							m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE1, n1!=0 );
							m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE2, n2!=0 );
							m_allsettings[0]->ValueSet( IDS_SETT_GNRL_MASKS_USE3, n3!=0 );

							// Publication
							objAr
								>> ((CSettingsPublication*)m_allsettings[2])->m_companyURL
								>> ((CSettingsPublication*)m_allsettings[2])->m_companyName
								>> n1
								>> ((CSettingsPublication*)m_allsettings[2])->m_signature
								>> n2;
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE, n1!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP, n2!=0 );
							objAr
								>> n1	// SignOutsOnClass // Obsolete for the moment
								>> n2;	// SignOutsOnCommu // Obsolete for the moment
							objAr
								>> n1;
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATE, !n1 );
							objAr
								>> n1;
							m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_100, n1==1 );
							m_allsettings[0]->ValueSet( IDS_SETT_GNRL_INPUTACCURACY_1000, n1==0 );
							objAr
								>> n1;
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COMMNOS_USE, n1!=0 );

							//Ranking
							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONTIMETRIALS_ONSUMRANKINGS_ONLATESTRANKING, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONSUMRANKINGS_ONLATESTRANKING, n1==1 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_GENERAL_SORT_ONLATESTRANKING, n1==2 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONMOSTHIGHRANKINGS, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_SPRINT_ONLATESTRANKING, n1==1 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONMOSTHIGHRANKINGS, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_CLIMB_ONLATESTRANKING, n1==1 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERATE, n1!=0 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHSUMRANKINGS, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_STAGE_ONWITHOUTSUMRANKINGS, n1==1 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_FIRST, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_DECIDING_LAST, n1==1 );

							objAr >> n1;
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHSUMRANKINGS, n1==0 );
							m_allsettings[1]->ValueSet( IDS_SETT_RANK_TEAMS_GENERAL_ONWITHOUTSUMRANKINGS, n1==1 );

							// Presentation
							objAr
								>> ((CSettingsHTML*)m_allsettings[3])->m_titleColor
								>> ((CSettingsHTML*)m_allsettings[3])->m_descriptColor
								>> ((CSettingsHTML*)m_allsettings[3])->m_bodyColor
								>> ((CSettingsHTML*)m_allsettings[3])->m_bgColor
								>> ((CSettingsHTML*)m_allsettings[3])->m_eventLogo;

							objAr
								>> n1
								>> n2
								>> n3;
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1, n1!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2, n2!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3, n3!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1, n1!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2, n2!=0 );
							m_allsettings[2]->ValueSet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3, n3!=0 );
							objAr
								>> ((CSettingsPublication*)m_allsettings[2])->m_mask1icon
								>> ((CSettingsPublication*)m_allsettings[2])->m_mask2icon
								>> ((CSettingsPublication*)m_allsettings[2])->m_mask3icon;
							// Upload
							objAr
								>> n1
								>> ((CSettingsUpload*)m_allsettings[4])->m_hostAddress
								>> ((CSettingsUpload*)m_allsettings[4])->m_username
								>> ((CSettingsUpload*)m_allsettings[4])->m_password
								>> ((CSettingsUpload*)m_allsettings[4])->m_remoteDir;
							m_allsettings[4]->ValueSet( IDS_SETT_UPLOAD_ALLOW, n1!=0 );
							// Access
							objAr
								>> n1
								>> ((CSettingsAccess*)m_allsettings[5])->m_key
								>> ((CSettingsAccess*)m_allsettings[5])->m_password;
							m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_FREE, n1==0 );
							m_allsettings[5]->ValueSet( IDS_SETT_ACCESS_PASSWORD, n1==1 );
						}
					}
				}
			}

			m_allsettings[2]->ValueSet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_OWN, 
				m_allsettings[2]->ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE) );
			m_allsettings[2]->ValueSet(IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG, true);
			m_allsettings[2]->ValueSet(IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_SHORT, false);
		}
	}
}

int CAllSettings::Settings(HANDLE hSemaphore)
{
	CString title( LoadStr( IDS_DIV46 ) );
	if( ProfilesGetCount()>1 )
		title += " (" + LoadStr( IDS_DIV94 ) + ": \"" + ProfilesGetName(ProfilesGetCurrent()) + "\")";
	CSizablePropertySheet dlgPropertySheet( title, TEXT("Settings") );

	// Make a page for every CSettings that is
	// held by this CAllSettings
	int i;
	for( i=0; i<=SETT_MAX; i++ )
	{
		// Get the CSettings
		CSettings* pSet = GetSettings((SETTINGS_TYPE)i);
		// Ask it for an appropriate page
		CPageSettings* pPage = pSet->GetPage();
		// Add the page to the sheet
		dlgPropertySheet.AddPage( pPage );
	}

	// Run the complete settings form
	int nRet = dlgPropertySheet.DoModal();

	// Go through all CSettings that are held by this CAllSettings,
	// copy their contents and delete them
	for( i=0; i<=SETT_MAX; i++ )
	{
		// Get the page
		CPageSettings* pPage = (CPageSettings*)
			dlgPropertySheet.GetPage( i );

		if( nRet == IDOK)
		{
			WaitForSingleObject(hSemaphore,INFINITE);

			// Get the CSettings
			CSettings* pSet = GetSettings((SETTINGS_TYPE)i);
			// Copy the settings from the page to the CSettings
			*pSet = *pPage->m_pSettings;

			ReleaseSemaphore(hSemaphore,1,NULL);
		}
		// Delete the page
		delete pPage;
	}
	return nRet;
}

bool CAllSettings::ValueGet(DWORD nID) const
{
	for( int i=0; i<=SETT_MAX; i++ )
		if( GetSettings((SETTINGS_TYPE)i)->ValueExist( nID ) )
			return GetSettings((SETTINGS_TYPE)i)->ValueGet( nID );
	ASSERT(0);
	return false;
}

CSettings* CAllSettings::GetSettings( SETTINGS_TYPE t ) const
{
	CSettings* ptr;
	ptr = m_allsettings.GetAt( (int)t+(SETT_SIZE*m_currentprofile) );
	if( !ptr )
		ptr = m_allsettings.GetAt( (int)t );
	return ptr;
}

void CAllSettings::ProfilesSetCurrent(unsigned short i)
{
	m_currentprofile = i % ProfilesGetCount();
}

unsigned short CAllSettings::ProfilesGetCurrent() const
{
	return m_currentprofile;
}

unsigned short CAllSettings::ProfilesGetCount() const
{
	return m_allsettings.GetSize()/SETT_SIZE;
}

void CAllSettings::ProfilesAdd(CString pr)
{
	m_allsettings.Add(NULL);
	m_allsettings.Add(NULL);
	m_allsettings.Add(new CSettingsPublication((CSettingsPublication*)m_allsettings[SETT_PUBLICATION]));
	m_allsettings.Add(new CSettingsHTML((CSettingsHTML*)m_allsettings[SETT_HTML]));
	m_allsettings.Add(new CSettingsUpload((CSettingsUpload*)m_allsettings[SETT_UPLOAD]));
	m_allsettings.Add(NULL);
	// The above must be SETT_SIZE number of Add's...

	m_profilenames.Add( CString(pr) );
}

void CAllSettings::ProfilesRemove(unsigned short pr)
{
	for( int i=0; i<=SETT_MAX; i++ )
		if( m_allsettings.GetAt(pr*SETT_SIZE+i) )
			delete m_allsettings.GetAt(pr*SETT_SIZE+i);
	m_allsettings.RemoveAt( pr*SETT_SIZE, SETT_SIZE );
	m_profilenames.RemoveAt( pr );
	if( m_currentprofile > (ProfilesGetCount()-1) )
		m_currentprofile--;
}

void CAllSettings::ProfilesSetName(unsigned short pr,CString c)
{
	c.SpanExcluding(TEXT("\\/:*?\"<>|."));
	m_profilenames.SetAt(pr, c);
}

CString CAllSettings::ProfilesGetName(unsigned short pr) const
{
	return m_profilenames.GetAt(pr);
}

int CAllSettings::Profiles(bool bLock, HANDLE hSemaphore)
{
	CDlgProfilePicker dlg(this, bLock, hSemaphore);

	int nRet = dlg.DoModal();

	return nRet;
}

bool CAllSettings::ProfilesRename(unsigned short pr)
{
	CDlgProfileName dlg( ProfilesGetName(pr) );

    dlg.m_indicator_access = m_allsettings.GetAt(pr*SETT_SIZE+SETT_ACCESS)!=NULL;
    dlg.m_indicator_general = m_allsettings.GetAt(pr*SETT_SIZE+SETT_GENERAL)!=NULL;
    dlg.m_indicator_publication = m_allsettings.GetAt(pr*SETT_SIZE+SETT_PUBLICATION)!=NULL;
    dlg.m_indicator_ranking = m_allsettings.GetAt(pr*SETT_SIZE+SETT_RANKING)!=NULL;
    dlg.m_indicator_html = m_allsettings.GetAt(pr*SETT_SIZE+SETT_HTML)!=NULL;
    dlg.m_indicator_upload = m_allsettings.GetAt(pr*SETT_SIZE+SETT_UPLOAD)!=NULL;

	if( dlg.DoModal()==IDOK )
	{
		ProfilesSetName(pr, dlg.m_name);
		return true;
	}
	return false;
}

bool CAllSettings::ProfilesAdd()
{
	CString name;
	name.Format( LoadStr(IDS_DIV92)+" #%d", ProfilesGetCount()+1 );

	CDlgProfileName dlg( name );

    dlg.m_indicator_access = false;
    dlg.m_indicator_general = false;
    dlg.m_indicator_publication = true;
    dlg.m_indicator_ranking = false;
    dlg.m_indicator_html = true;
    dlg.m_indicator_upload = true;

	if( dlg.DoModal()==IDOK )
	{
		ProfilesAdd(dlg.m_name);
		return true;
	}
	return false;
}

bool CAllSettings::ProfilesGetAdjustFileNames() const
{
	return m_bAdjustFileNames && (ProfilesGetCount()>1);
}

void CAllSettings::ProfilesSetAdjustFileNames(bool b)
{
	m_bAdjustFileNames = b;
}

bool CAllSettings::ProfilesGetUseProfileNames() const
{
	return ProfilesGetAdjustFileNames() && m_bUseProfileNames;
}

void CAllSettings::ProfilesSetUseProfileNames(bool b)
{
	m_bUseProfileNames = b;
}

CString CAllSettings::ProfilesGetCurrentFileName() const
{
	if( m_bAdjustFileNames && (ProfilesGetCount()>1) )
	{
		CString ret;
		if( m_bUseProfileNames )
		{
			ret = ProfilesGetName( ProfilesGetCurrent() ) + TEXT(" - ");
		}
		else
		{
			if( ProfilesGetCurrent()==0 )
				return "";
			else
				ret.Format( TEXT("profile #%d - "), ProfilesGetCurrent() );
		}
		return ret;
	}
	else
		return "";
}
