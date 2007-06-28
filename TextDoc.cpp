///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: TextDoc.h
// Description: Implementation file for the CTextDoc class
///////////////////////////////////////////////////////////////////////////
//
// ---------------------------- Coding History ----------------------------
// date			ID	Description
// ----			--	-------------------------------------------------------
// 05-01-2000	SV	Delivered as is
// 06-01-2000	SV	Alle variabelenamen aangepast volgens nieuwe conventie
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND INITIALISATION

CTextDoc::CTextDoc( CEventItem ei )
{
	// Save for further use
	m_ei = ei;
	m_pDocument = ei.GetDocument();

	// Set the flags
	m_competitorsStarted = false;
	m_nPrintedRules = 0;
	m_previousGap = 0;
	m_bEvaluation = (ei.m_tiConcerning!=TI_SIGNINLIST) && !(ei.m_nFullStage==1) && ((CStageRaceApp*) AfxGetApp())->m_key.CheckDongle();

	// Set up filename
	CString sFileName = ei.ComposeFileNamePathCSV();

	// We create a file with this new name
	CFileException objFileException;

	// We open the new file
	if ( !m_output.Open( sFileName, CFile::modeCreate |   
		CFile::typeBinary | CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
	{
		MessageBox( NULL, LoadStr( IDS_MBC_7A )+sFileName+LoadStr( IDS_MBC_7B ), LoadStr( IDS_MBT_7 ), MB_OK|MB_SETFOREGROUND|MB_TOPMOST );
		m_openSuccess = false;
	}
	else
		m_openSuccess = true;

	if( m_openSuccess )
	{
		// Add Unicode "BOM" character
		char p[] = { (char)0xFF,(char)0xFE };
		m_output.Write( p, 2 );
	}
}

void CTextDoc::Finish()
{
	if( !m_openSuccess )
		return;

	// We finish the document by writing it to disk
	m_output.Close();

}

///////////////////////////////////////////////////////////////////////////
// VISIBLE HEADER AND FOOTER

void CTextDoc::Header(unsigned short nId)
{
	if( !m_openSuccess )
		return;

	// TOP LINE
	if( m_ei.m_nFullStage )
	{
		WriteStringLineComment( m_ei.StagesMakeIDString()
			+TEXT(" ")
			+m_ei.ComposeTocTitle());
	}
	else
	{
		WriteStringLineComment( m_ei.ComposeTocTitle());
	}

	// Insert the ID if required by settings
	if( nId && m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
	{
		TCHAR czBuffer[10];
		_itot( nId, czBuffer, 10 );
		WriteStringLineComment( TEXT("COMMUNIQUÉ Nº: ")
			+CString(czBuffer) );
	}

	// Print additional security notice
	if ( m_bEvaluation )
	{
		WriteStringLineComment( TEXT("StageRace Evaluation Mode") );
	}

	// Event name and sub title
	WriteStringLineComment( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName );
	WriteStringLineComment( m_ei.GetSponsorSubTitle() );
	
	WriteStringLineComment();

	PUBLI_PROPERTIES props[PUBLI_PROPERTIES_MAX];
	m_ei.GetPublicationProperties( props );
	Properties( props );
}

void CTextDoc::Footer(PUBLI_BODYCOLUMNS columns[]/*NULL*/, CSignOutList* pSignOuts/*=NULL*/, int nNumberNotStarted/*=-1*/, int nNumberStarters/*=-1*/, int nNumberLeft/*=-1*/, CString czDroppedOut/*=""*/, CString czCutOff/*=""*/)
{
	if( !m_openSuccess )
		return;

	if( pSignOuts )
		WriteStringLine();

	// We add eventual sign outs
	m_competitorsStarted = false;
	SignOuts( columns, pSignOuts );

	// Additional info
	if( nNumberStarters>=0 )
	{
		WriteStringLine();

		TCHAR czBuffer[10];

		_itot( nNumberNotStarted, czBuffer, 10 );
		WriteStringLineComment( AssembleStr( TEXT("FootNotStart"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )
			+TEXT(": ")
			+CString(czBuffer) );
		_itot( nNumberStarters, czBuffer, 10 );
		WriteStringLineComment( AssembleStr( TEXT("FootNumStart"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )
			+TEXT(": ")
			+CString(czBuffer) );
		_itot( nNumberLeft, czBuffer, 10 );
		WriteStringLineComment( AssembleStr( TEXT("FootRemain"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )
			+TEXT(": ")
			+CString(czBuffer) );
		WriteStringLineComment( AssembleStr( TEXT("FootCutOff"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )
			+TEXT(": ")
			+CString(czCutOff) );
		WriteStringLineComment( AssembleStr( TEXT("FootDroppOut"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )
			+TEXT(": ")
			+CString(czDroppedOut) );
	}

	WriteStringLine();

	// Here we make an eventual time stamp
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP) )
	{
		SYSTEMTIME timeNow;
 		GetLocalTime( &timeNow );
 
 		TCHAR cBuffer[10];
 		CString cStamp;
 
 		_itot( timeNow.wDay, cBuffer, 10 );
		if( !(timeNow.wDay/10) ) cStamp += TEXT("0");
 		cStamp = cBuffer;
 
 		_itot( timeNow.wMonth, cBuffer, 10 );
 		cStamp += TEXT("-");
		if( !(timeNow.wMonth/10) ) cStamp += TEXT("0");
 		cStamp += cBuffer;
 
 		_itot( timeNow.wHour, cBuffer, 10 );
 		cStamp += TEXT(", ");
 		cStamp += cBuffer;
 
 		_itot( timeNow.wMinute, cBuffer, 10 );
 		cStamp += TEXT(".");
		if( !(timeNow.wMinute/10) ) cStamp += TEXT("0");
 		cStamp += cBuffer;

		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP_SECONDS) )
		{
 			_itot( timeNow.wSecond, cBuffer, 10 );
			cStamp += TEXT(".");
			if( !(timeNow.wSecond/10) ) cStamp += TEXT("0");
 			cStamp += cBuffer;
		}

		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP_TIMEZONE) )
		{
			TIME_ZONE_INFORMATION tzi;
			UINT i = GetTimeZoneInformation( &tzi );
			switch( i )
			{
				case TIME_ZONE_ID_STANDARD:
					cStamp += TEXT(" (") + CString(tzi.StandardName) + TEXT(")");
					break;
				case TIME_ZONE_ID_DAYLIGHT:
					cStamp += TEXT(" (") + CString(tzi.DaylightName) + TEXT(")");
					break;
			}
		}

		CString cLastCalculated = AssembleStr( TEXT("CalcultdLast"), TEXT(", "), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		if( !cLastCalculated.SpanExcluding( TEXT(", ") ).GetLength() )
			cLastCalculated = TEXT("Last calculated");

		WriteStringLineComment( cLastCalculated
			+TEXT(": ")
			+cStamp );
	}

	// This function makes the visible footer
	WriteStringLineComment( TEXT("Classification software: StageRace ")
		+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()
		+TEXT(" software  --  www.stagerace.com") );

}


///////////////////////////////////////////////////////////////////////////
// SERVICES

CString CTextDoc::UnQuote(CString s)
{
	// Replace double quotes by single quotes
	// so that we can build safe HTML HREF's
	s.Replace( '\"', '\'' );
	return s;
}

///////////////////////////////////////////////////////////////////////////
// MAIN COMPETITORS TABLE

void CTextDoc::StartCompetitorsTable(PUBLI_BODYCOLUMNS columns[])
{
	// If this is the first line, the flag m_competitorsStarted will be
	// false and the table header will printed
	if( !m_competitorsStarted )
	{
		ColumnTitles(columns);
		m_competitorsStarted = true;
	};
}

void CTextDoc::ColumnTitle(CString title)
{
	if( title.GetLength() )
	{
		WriteStringColumnQuote( title );
	}
}

void CTextDoc::ColumnTitles( PUBLI_BODYCOLUMNS columns[] )
{
	if( !m_openSuccess )
		return;

	// This function prints the column titles for the columns
	// with competitor information we need to be printed
	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed
	
	// Start the titles row
	int i=0;
	while( columns[i]!=PBC_TERMINATOR ) // Print every column title
	{
		switch( columns[i] )
		{
			case PBC_SIGNINAREA:
				ColumnTitle( AssembleStr( TEXT("Signature"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_CATEGORY:
				ColumnTitle( AssembleStr( TEXT("Category"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_RIDER:
				ColumnTitle( AssembleStr( TEXT("Rider"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_COUNTRY:
				ColumnTitle( AssembleStr( TEXT("Country"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_LICENSE:
				ColumnTitle( AssembleStr( TEXT("License"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_STANO:
				ColumnTitle( AssembleStr( TEXT("StaNo"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_UCICODE:
				ColumnTitle( AssembleStr( TEXT("UCICode"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_RANK:
				ColumnTitle( AssembleStr( TEXT("Position"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TIME:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_SPEED:
				ColumnTitle( AssembleStr( TEXT("Speed"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_GAP:
			case PBC_NEWGAP:
				ColumnTitle( AssembleStr( TEXT("Gap"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_BONUSES:
				ColumnTitle( AssembleStr( TEXT("Bonuses"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_POINTS:
				ColumnTitle( AssembleStr( TEXT("Points"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TEAMCODE:
			case PBC_TEAMCODEFROMRANK:
			case PBC_TEAMNAME:
			case PBC_TEAMNAMEFROMRANK:
				ColumnTitle( AssembleStr( TEXT("Team"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TIMEWITHTHOUSANDTH:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages) );
				break;
			case PBC_STARTINGORDERTIME:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_STARTINGORDER:
				ColumnTitle( AssembleStr( TEXT("Order"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_INVOLVEDBUNCH:
				ColumnTitle( AssembleStr( TEXT("InvolvdBunch"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TEAMCODEWITHOUTCOLUMNHEADER:
			case PBC_TEAMCODEFROMRANKWITHOUTCOLUMNHEADER:
			case PBC_MASK1:
			case PBC_MASK2:
			case PBC_MASK3:
			case PBC_MASK4:
			case PBC_MASK5:
			case PBC_MASK6:
			case PBC_MASK7:
			case PBC_MASK8:
			case PBC_MASK9:
			case PBC_MASK10:
				ColumnTitle( TEXT("") );
				break;
			case PBC_PENALTY:
				ColumnTitle(AssembleStr( TEXT("Penalty"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ));
				break;
			case PBC_SIGNOUTREASON:
				ColumnTitle(AssembleStr( TEXT("Reason"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ));
				break;
		};
		i++;
	};

	// End the titles row
	WriteStringLine();
}

void CTextDoc::ColumnItem(CString item)
{
	if( item.GetLength() )
	{
		WriteStringColumnQuote( item );
	}
}

void CTextDoc::Competitor( PUBLI_BODYCOLUMNS columns[], WORD nComp, CArrival* pRank/*=NULL*/, CSignOut* pSignOut/*=NULL*/, bool bDraw/*=true*/, bool bBold/*=false*/, bool bSuppressGap/*=false*/ )
{
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one competitor

	// This function is called with an array of enumeration values (zero-
	// terminated) which contains the (order of) columns we need to be printed

	StartCompetitorsTable(columns);

	CCompetitor* pComp = NULL;
	if( m_pDocument->CompetitorsExist( nComp ) )
		pComp = &m_pDocument->CompetitorsGet( nComp );

	// Security
	if ( m_bEvaluation && (m_nPrintedRules>=9) )
		return;

	int i=0;
	while( true )
	{
		switch( columns[i++] )
		{
			case PBC_SIGNINAREA:
				if( pComp )
				{
					TCHAR cBuffer[10];
					_itot( pComp->m_staNo, cBuffer, 10 );
					WriteStringColumn( cBuffer );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_CATEGORY:
				if( pComp )
				{
					WriteStringColumnQuote( pComp->m_category );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_RIDER:
				if( pComp )
				{
					WriteStringColumnQuote( pComp->m_competitor );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_COUNTRY:
				if( pComp )
				{
					WriteStringColumnQuote( pComp->m_countryCode );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_LICENSE:
				if( pComp )
				{
					WriteStringColumnQuote( pComp->m_license );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_STANO:
				if( pComp )
				{
					TCHAR cBuffer[10];
					_itot( pComp->m_staNo, cBuffer, 10 );
					WriteStringColumn( cBuffer );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TEAMCODEWITHOUTCOLUMNHEADER:
			case PBC_TEAMCODE:
				if( pComp && pComp->m_pTeam )
				{
					WriteStringColumnQuote( pComp->m_pTeam->m_code );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TEAMNAME:
				if( pComp && pComp->m_pTeam )
				{
					WriteStringColumnQuote( pComp->m_pTeam->m_name );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_UCICODE:
				if( pComp )
				{
					WriteStringColumnQuote( pComp->m_UCICode );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_RANK:
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_rank, cBuffer, 10 );
					WriteStringColumn( cBuffer );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TIME:
				if( pRank )
				{
					WriteStringColumn( CStageTime( pRank->m_units ).GetFormattedSemicolons() );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_SPEED:
				if( pRank )
				{
					const CHalfStage* pHS = ((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage, m_ei.m_nHalfStage);
					if( (pHS->m_rounds==1) || (pHS->m_stageType!=ST_NORMAL) )
						WriteStringColumn( CStageSpeed::GetSpeed( pHS->m_distance, pRank->m_units,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE ),
							", "
						) );
					else
						WriteStringColumn( CStageSpeed::GetSpeed( pHS->m_distance*pHS->m_rounds, pRank->m_units,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE ),
							", "
						) );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_INVOLVEDBUNCH:
				{
					CArrival bunchcompetitor;
					if( pRank && pRank->m_pBunch )
					{
						POSITION nPos;

						nPos = pRank->m_pBunch->m_classification.GetHeadPosition();
						CString cBunch;
						TCHAR cBuffer1[10];
						TCHAR cBuffer2[10];
						while( nPos )
						{
							bunchcompetitor = pRank->m_pBunch->m_classification.GetNext(nPos);
							_itot( bunchcompetitor.m_staNo, cBuffer1, 10 );
							_itot( bunchcompetitor.m_rank , cBuffer2, 10 );
							if( cBunch.GetLength() )
							{
								if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_INLINE) )
									cBunch+=TEXT(", ");
								else
									cBunch+=TEXT("&nbsp;&nbsp;<BR>");
							}
							if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_STANO) )
								cBunch += CString(cBuffer1) + TEXT(" (") + CString(cBuffer2) + TEXT(".)");
							else
								cBunch += CString(cBuffer1);
						}
						WriteStringColumnQuote( cBunch );
					}
					else
					{
						WriteStringColumnQuote();
					}
				}
				break;
			case PBC_NEWGAP:
				if( !bSuppressGap && pRank )
				{
					if( pRank && ((pRank->m_units/1000)*1000-m_championTime != m_previousGap)
						|| m_previousGap==0 )
					{
						m_previousGap = (pRank->m_units/1000)*1000-m_championTime;
						WriteStringColumn( CStageTime( m_previousGap ).GetFormattedSemicolons() );
					}
					else
					{
						WriteStringColumnQuote( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_sameGap );
					}
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_GAP:
				if( !bSuppressGap && pRank )
				{
					WriteStringColumn( CStageTime( (pRank->m_units/1000)*1000-m_championTime ).GetFormattedSemicolons() );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_BONUSES:
				if( pRank && pRank->m_bonus )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_bonus, cBuffer, 10 );
					WriteStringColumn( CString(cBuffer) );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_POINTS:
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_points, cBuffer, 10 );
					WriteStringColumn( CString(cBuffer) );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TEAMNAMEFROMRANK:
				if( pRank && pRank->m_pTeam )
				{
					WriteStringColumnQuote( pRank->m_pTeam->m_name );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TEAMCODEFROMRANK:
			case PBC_TEAMCODEFROMRANKWITHOUTCOLUMNHEADER:
				if( pRank && pRank->m_pTeam )
				{
					WriteStringColumnQuote( pRank->m_pTeam->m_code );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TIMEWITHTHOUSANDTH:
				if( pRank )
				{
					if( bDraw )
					{
						WriteStringColumn( CStageTime( pRank->m_units ).GetFormattedSemicolons()
							+"."+CStageTime( pRank->m_units ).GetThousandth() );
					}
					else
					{
						WriteStringColumn( CStageTime( pRank->m_units ).GetFormattedSemicolons() );
					}
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_STARTINGORDERTIME:
				if( pRank )
				{
					WriteStringColumn( CStageTime( pRank->m_unitsAtStart ).GetFormattedSemicolons() );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_STARTINGORDER:
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_order, cBuffer, 10 );
					WriteStringColumn( cBuffer );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK1:
				if( pComp && pComp->m_mask1 )
				{
					WriteStringColumnQuote( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask1icon );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK2:
				if( pComp && pComp->m_mask2 )
				{
					WriteStringColumnQuote( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask2icon );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK3:
				if( pComp && pComp->m_mask3 )
				{
					WriteStringColumnQuote( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask3icon );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK4:
				if( pComp && pComp->m_mask4 )
				{
					WriteStringColumnQuote( TEXT("M4") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK5:
				if( pComp && pComp->m_mask5 )
				{
					WriteStringColumnQuote( TEXT("M5") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK6:
				if( pComp && pComp->m_mask6 )
				{
					WriteStringColumnQuote( TEXT("M6") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK7:
				if( pComp && pComp->m_mask7 )
				{
					WriteStringColumnQuote( TEXT("M7") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK8:
				if( pComp && pComp->m_mask8 )
				{
					WriteStringColumnQuote( TEXT("M8") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK9:
				if( pComp && pComp->m_mask9 )
				{
					WriteStringColumnQuote( TEXT("M9") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_MASK10:
				if( pComp && pComp->m_mask10 )
				{
					WriteStringColumnQuote( TEXT("M10") );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_PENALTY:
				if( pRank && pRank->m_penalty )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_penalty, cBuffer, 10 );
					WriteStringColumn( CString(cBuffer) );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_SIGNOUTREASON:
				if( pSignOut )
				{
					WriteStringColumnQuote( pSignOut->m_reasonOfSignOut );
				}
				else
				{
					WriteStringColumnQuote();
				}
				break;
			case PBC_TERMINATOR:
			default:
				// End the competitor row
				WriteString( TEXT("\r\n") );

				// Add 1 to the rules count for the security
				m_nPrintedRules++;

				// End subroutine
				return;
		};
	};
}

void CTextDoc::SayText(PUBLI_BODYCOLUMNS columns[], CString czText)
{
	if( !m_openSuccess )
		return;

	// This function prints a single row with the provided text

	StartCompetitorsTable(columns);
	WriteString( TEXT("\r\n") );
	WriteStringLineComment( czText );
}

void CTextDoc::Legenda(PUBLI_BODYCOLUMNS columns[])
{
	CString line;
	int i=0;
	while( columns[i]!=PBC_TERMINATOR )
	{
		switch( columns[i] )
		{
			case PBC_MASK1:
				line = ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask1icon;
				line += TEXT(" ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1;
				WriteStringLineComment(line);
				break;
			case PBC_MASK2:
				line = ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask2icon;
				line += TEXT(" ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2;
				WriteStringLineComment(line);
				break;
			case PBC_MASK3:
				line = ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask3icon;
				line += TEXT(" ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3;
				WriteStringLineComment(line);
				break;
			case PBC_MASK4:
				line = TEXT("M4 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4;
				WriteStringLineComment(line);
				break;
			case PBC_MASK5:
				line = TEXT("M5 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5;
				WriteStringLineComment(line);
				break;
			case PBC_MASK6:
				line = TEXT("M6 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6;
				WriteStringLineComment(line);
				break;
			case PBC_MASK7:
				line = TEXT("M7 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7;
				WriteStringLineComment(line);
				break;
			case PBC_MASK8:
				line = TEXT("M8 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8;
				WriteStringLineComment(line);
				break;
			case PBC_MASK9:
				line = TEXT("M9 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9;
				WriteStringLineComment(line);
				break;
			case PBC_MASK10:
				line = TEXT("M10 ");
				line += ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10;
				WriteStringLineComment(line);
				break;
		};
		i++;
	};
}

void CTextDoc::TeamHeader(PUBLI_BODYCOLUMNS columns[], CTeam *pTeam)
{
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one team

	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed

	StartCompetitorsTable(columns);

	CString cLine;

	if( pTeam )
		cLine += pTeam->m_code
			+ TEXT("  ")
			+ pTeam->m_name;
	else
		cLine += AssembleStr( TEXT("WithoutTeam"), TEXT(" - "), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
	
	cLine += TEXT("  --  ");

	if( pTeam )
		cLine += pTeam->m_country;

	// End the competitor row
	WriteStringLineComment( cLine );
}

void CTextDoc::TeamFooter(PUBLI_BODYCOLUMNS columns[], CTeam *pTeam)
{
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one team

	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed

	if( pTeam && pTeam->m_manager.GetLength() )
	{
		StartCompetitorsTable(columns);

		CString cLine;
		cLine = AssembleStr( TEXT("TeamCaptain"), TEXT(", "), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		cLine += TEXT(": ")
			+ pTeam->m_manager;

		WriteStringLineComment( cLine );
	}
}

void CTextDoc::Break(PUBLI_BODYCOLUMNS columns[])
{
	if( !m_openSuccess )
		return;

	// End the competitor row
	WriteStringLine();
}

void CTextDoc::Property(CString caption, int property)
{
	CString str;
	str.Format( TEXT("%d"), property );
	Property( caption, str );
}

void CTextDoc::Property(CString caption, CString property)
{
	WriteStringLineComment( caption + TEXT(": ") + property );
}

void CTextDoc::Property(CString caption)
{
	WriteStringLineComment( caption );
}

void CTextDoc::Properties( PUBLI_PROPERTIES props[], CObject* pObj/*=NULL*/ )
{
	if( !m_openSuccess )
		return;

	// This function prints the properties in a row
	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) properties we need to be printed

	const CHalfStage* pHS = ((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage, m_ei.m_nHalfStage);
	int i=0;
	while( props[i]!=PPR_TERMINATOR ) // Print every property
	{
		switch( props[i] )
		{
			case PPR_COMPETITORSCOUNT:
				Property( AssembleStr( TEXT("CountComps"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					m_pDocument->CompetitorsCount() );
				break;
			case PPR_TEAMSCOUNT:
				Property( AssembleStr( TEXT("CountTeams"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					m_pDocument->TeamsCountUsed() );
				break;
			case PPR_CATEGORY:
				Property( AssembleStr( TEXT("Category"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_category );
				break;
			case PPR_DATE:
				Property( AssembleStr( TEXT("Date"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_dates );
				break;
			case PPR_ORGANISER:
				Property( AssembleStr( TEXT("Organiser"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_organiser );
				break;
			case PPR_LOCATION:
				Property( AssembleStr( TEXT("Location"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_location );
				break;
			case PPR_TITLE_COMMUNIQUE:
				Property( AssembleStr( TEXT("Title"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CCommunique*)pObj)->m_title );
				break;
			case PPR_SINGLE_STAGE_CLASSIFICATION:
				Property( AssembleStr( TEXT("PropArrival"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_GENERAL_CLASSIFICATION:
				Property( AssembleStr( TEXT("PropGeneral"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_STAGE_INDICATOR:
				Property( AssembleStr( TEXT("Stage"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage)->m_date );
				break;
			case PPR_DISTANCE:
				{
					CString cCompose;
					cCompose =
						CStageDistance::DistanceStage(
							pHS->m_stageType!=ST_NORMAL ? 1 : pHS->m_rounds,
							pHS->m_distance,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						);

					// If already distance elapsed: print from--to
					if( m_ei.GetOfficialDistanceCumulativeBefore() )
					{
						cCompose += TEXT("/");
						cCompose += CStageDistance::DistanceFromTo(
							m_ei.GetOfficialDistanceCumulativeBefore(),
							m_ei.GetOfficialDistanceCumulative(),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						);
					}

					Property( AssembleStr( TEXT("Distance"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						cCompose );
				}
				break;
			case PPR_OVERALL_DISTANCE:
				{
					Property(
						AssembleStr( TEXT("DistancTotal"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						CStageDistance::DistanceSingle(
							m_ei.GetOfficialDistanceCumulative(),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						)
					);
				}
				break;
			case PPR_SPEED:
				if( (pHS->m_rounds==1) || (pHS->m_stageType!=ST_NORMAL) )
					Property( AssembleStr( TEXT("PropSpeed"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						CStageSpeed::GetSpeed( pHS->m_distance, m_championTime,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						) );
				else
					Property( AssembleStr( TEXT("PropSpeed"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						CStageSpeed::GetSpeed( pHS->m_distance*pHS->m_rounds, m_championTime,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						) );
				break;
			case PPR_OVERALL_SPEED:
				Property( AssembleStr( TEXT("PropSpeed"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageSpeed::GetSpeed( m_ei.GetRealDistanceCumulative(), m_championTime,
						m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
						m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
					) );
				break;
			case PPR_MASK_1:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1 );
				break;
			case PPR_MASK_2:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2 );
				break;
			case PPR_MASK_3:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3 );
				break;
			case PPR_MASK_4:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4 );
				break;
			case PPR_MASK_5:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5 );
				break;
			case PPR_MASK_6:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6 );
				break;
			case PPR_MASK_7:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7 );
				break;
			case PPR_MASK_8:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8 );
				break;
			case PPR_MASK_9:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9 );
				break;
			case PPR_MASK_10:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10 );
				break;
			case PPR_SPRINTS:
				Property( AssembleStr( TEXT("PropSprints"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_POINTS:
				Property( AssembleStr( TEXT("PropPoints"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_CLIMBS:
				Property( AssembleStr( TEXT("PropClimbs"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_MOSTAGGRESSIVE:
				Property( AssembleStr( TEXT("PropAggressv"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_HALF_STAGE_INDICATOR:
				Property( AssembleStr( TEXT("HalfStage"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_START_OF_EVENT_TIME:
				Property( AssembleStr( TEXT("OpeningHour"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_openingHour );
				break;
			case PPR_DATE_COMMUNIQUE:
				Property( AssembleStr( TEXT("Date"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CCommunique*)pObj)->m_date );
				break;
			case PPR_TIME_OF_WINNER:
				Property( AssembleStr( TEXT("TimeOfWinner"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageTime( m_championTime ).GetFormattedLefttrimmed() );
				break;
			case PPR_TIME_OF_WINNER_WITHTHOUSANDTH:
				Property( AssembleStr( TEXT("TimeOfWinner"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageTime( m_championTime ).GetFormattedLefttrimmed()+CStageTime( m_championTime ).GetThousandth() );
				break;

			// More to come here!

		}
		i++;
	}
	WriteStringLine();
}

///////////////////////////////////////////////////////////////////////////
// VARIOUS

#define MAXTOCROWINDENT 4

void CTextDoc::SignOuts(PUBLI_BODYCOLUMNS columns[], CSignOutList* pSignOuts)
{
	if( !m_openSuccess )
		return;

	if( pSignOuts )
		if( pSignOuts->GetCount() && columns )
		{
			PUBLI_BODYCOLUMNS so_columns[PUBLI_BODYCOLUMNS_MAX];
			int nPos = 0;
			int i = 0;
			do
			{
				switch( columns[i] )
				{
					case PBC_TERMINATOR:
						so_columns[nPos++] = PBC_SIGNOUTREASON;
					case PBC_STANO:
					case PBC_UCICODE:
					case PBC_LICENSE:
					case PBC_RIDER:
					case PBC_TEAMNAME:
					case PBC_TEAMCODEWITHOUTCOLUMNHEADER:
					case PBC_TEAMCODE:
					case PBC_COUNTRY:
					case PBC_CATEGORY:
						so_columns[nPos++] = columns[i];
				}
			}
			while( columns[i++]!=PBC_TERMINATOR );

			// The following code prints the sign outs
			WriteStringLineComment( AssembleStr( TEXT("FootSignOut"), TEXT("/"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );

			StartCompetitorsTable( so_columns );

			DWORD nState = 0;
			CSignOut objSignOut;
			while( pSignOuts->IterateSorted( nState, objSignOut ) )
				Competitor( so_columns, objSignOut.m_staNo, NULL, &objSignOut );
			
			m_competitorsStarted = false;
		}
}

void CTextDoc::MakeDummy(CEventItem ei, unsigned short nId)
{
	if( ei.GetDocument()->m_allsettings.ValueGet(IDS_SETT_HTML_DUMMY_PRINT) )
	{
		// Make the text document
		CTextDoc objText( ei );

		if( !objText.m_openSuccess )
			return;

		objText.Header(nId);
		objText.WriteStringLine(
			AssembleStr(
				TEXT("DummyDoc"),
				TEXT("\r\n"),
				&((CSettingsPublication*)ei.GetDocument()->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
		objText.Finish();
	}
}

void CTextDoc::WriteString(CString c)
{
	m_output.WriteString(c);
}

void CTextDoc::WriteStringLine(CString c)
{
	m_output.WriteString(c + TEXT("\r\n"));
}

void CTextDoc::WriteStringLineComment(CString c)
{
	m_output.WriteString(TEXT("; ") + c + TEXT("\r\n"));
}

void CTextDoc::WriteStringColumn(CString c)
{
	m_output.WriteString(c + TEXT(";"));
}

void CTextDoc::WriteStringColumnQuote(CString c)
{
	m_output.WriteString(TEXT("\"") + UnQuote(c) + TEXT("\";"));
}

bool CTextDoc::IsFileOpened()
{
	return m_openSuccess;
}
