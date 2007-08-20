///////////////////////////////////////////////////////////////////////////
// Copyright 1999-2000 Totaal Software
///////////////////////////////////////////////////////////////////////////
// Primary author: Sander Verhagen
// Primary date: 01-01-2000
// Filename: HtmlDoc.h
// Description: Implementation file for the CHtmlDoc class
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
CHtmlDoc::CHtmlDoc( CEventItem ei )
{
	// Generation of CSV counterpart of this method
	m_ptextdoc = NULL;
	// Feature switch on/off right here
	if( true )
	{
		if( ei.IsPublicableCSV() )
		{
			m_ptextdoc = new CTextDoc(ei);
			if( m_ptextdoc && !m_ptextdoc->IsFileOpened() )
			{
				delete m_ptextdoc;
				m_ptextdoc = NULL;
			}
		}
	}
	// Save for further use
	m_ei = ei;
	m_pDocument = ei.GetDocument();

	// Set the flags
	m_competitorsStarted = false;
	m_unknownlabelcounter = 0;
	m_nPrintedRules = 0;
	m_previousGap = 0;
	m_bEvaluation = (ei.m_tiConcerning!=TI_SIGNINLIST) && !(ei.m_nFullStage==1) && ((CStageRaceApp*) AfxGetApp())->m_key.CheckDongle();
	m_b2ByteFile = m_pDocument->m_allsettings.ValueGet(IDS_SETT_HTML_UNICODE_PRINTUNICODE);

	// Set up filename
	CString sFileName = ei.ComposeFileNamePathHTML();

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

	if( m_openSuccess && m_b2ByteFile )
	{
		// Add Unicode "BOM" character
		char p[] = { (char)0xFF,(char)0xFE };
		m_output.Write( p, 2 );
	}

	// Already start the html
	HtmlHeader();
}

CHtmlDoc::~CHtmlDoc()
{
	if( m_ptextdoc )
	{
		delete m_ptextdoc;
		m_ptextdoc = NULL;
	}
}

void CHtmlDoc::Finish()
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Finish();
	}
	if( !m_openSuccess )
		return;

	HtmlFooter();

	// We finish the document by writing it to disk
	m_output.Close();

}

void CHtmlDoc::HtmlHeader()
{
	// Note: this method has not CSV counterpart (due to HTML specifics)
	if( !m_openSuccess )
		return;

	CString cStyleSheet	= ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_styleSheet;
	cStyleSheet.TrimLeft();
	cStyleSheet.TrimRight();

	// This function starts the HTML document and
	// makes it contain some meta and style information
	WriteString( TEXT("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\r\n") );
	WriteString( TEXT("<HTML>\r\n") );
	WriteString( TEXT("    <HEAD>\r\n") );
	WriteString( TEXT("        <META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=utf-8\">\r\n") ); /* was: iso-8859-1 */
	WriteString( TEXT("        <META NAME=\"author\"      CONTENT=\"")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_organiser )+TEXT(" by use of StageRace\">\r\n") );
	WriteString( TEXT("        <META NAME=\"keywords\"    CONTENT=\"cyclng, road cycling, classification, classement, habakuba, ")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName )+TEXT(", ")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle )+TEXT("\">\r\n") );
	WriteString( TEXT("        <META NAME=\"description\" CONTENT=\"Communiqué/Classification/Classement ")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName )+TEXT(" - ")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle )+TEXT("\">\r\n") );
	WriteString( TEXT("        <META NAME=\"date\"        CONTENT=\"")+UnQuote( ((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_dates )+TEXT("\">\r\n") );
	// With the document title
	WriteString( TEXT("        <TITLE>")
		+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName
		+TEXT(" - ") );
	if( m_ei.m_nFullStage ) WriteString( m_ei.StagesMakeIDString() + TEXT(" - ") );
	WriteString( m_ei.ComposeTocTitle()
		+TEXT("</TITLE>\r\n") );
	// Write the style information
	WriteString( GetStylePart( m_pDocument ) );

	WriteString( TEXT("    </HEAD>\r\n") );
	WriteString( TEXT("    <BODY>\r\n") );
	WriteString( TEXT("    <TABLE WIDTH=\"100%\">\r\n") );
	WriteString( TEXT("    <THEAD CLASS=\"customhtml\">\r\n") );
	WriteString( TEXT("    <TR>\r\n") );
	WriteString( TEXT("    <TH>\r\n") );
	WriteString( TEXT("\r\n") );
	WriteString( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_customHTMLTop );
	WriteString( TEXT("\r\n") );
	WriteString( TEXT("    </TH>\r\n") );
	WriteString( TEXT("    </TR>\r\n") );
	WriteString( TEXT("    </THEAD>\r\n") );
	WriteString( TEXT("    <TFOOT>\r\n") );
	WriteString( TEXT("    <TR>\r\n") );
	WriteString( TEXT("    <TD>\r\n") );
	WriteString( TEXT("\r\n") );
	WriteString( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_customHTMLBottom );
	WriteString( TEXT("\r\n") );
	WriteString( TEXT("    </TD>\r\n") );
	WriteString( TEXT("    </TR>\r\n") );
	WriteString( TEXT("    </TFOOT>\r\n") );
	WriteString( TEXT("    <TBODY>\r\n") );
	WriteString( TEXT("    <TR>\r\n") );
	WriteString( TEXT("    <TD>\r\n") );
	Label();
}

void CHtmlDoc::HtmlFooter()
{
	// Note: this method has not CSV counterpart (due to HTML specifics)
	if( !m_openSuccess )
		return;

	// This function ends the HTML document

	// By printing an identification statement
	WriteString( TEXT("        <H6 ALIGN=\"right\">\r\n") );
	WriteString( TEXT("            ")+m_pDocument->GetTitle()+TEXT(" : ")+((CStageRaceApp*)AfxGetApp())->m_key.HaspID()+TEXT(" : ")+((CStageRaceApp*)AfxGetApp())->m_key.GetRawLongVersion()+TEXT("\r\n") );
	WriteString( TEXT("        </H6>\r\n") );
	LabelEnd();
	WriteString( TEXT("    </TD>\r\n") );
	WriteString( TEXT("    </TR>\r\n") );
	WriteString( TEXT("    </TBODY>\r\n") );
	WriteString( TEXT("    </TABLE>\r\n") );
	WriteString( TEXT("    </BODY>\r\n") );
	WriteString( TEXT("</HTML>\r\n") );
}


///////////////////////////////////////////////////////////////////////////
// VISIBLE HEADER AND FOOTER

void CHtmlDoc::Header(unsigned short nId)
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Header(nId);
	}
	if( !m_openSuccess )
		return;

	WriteString( TEXT("    <TABLE WIDTH=\"100%\">\r\n") );

	// TOP LINE
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_DOCRECOGNITION_USE)
			||
			( nId && m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) ) )
		{
			WriteString( TEXT("    <THEAD CLASS=\"docrecognition\">\r\n") );
			WriteString( TEXT("    <TR>\r\n") );
			WriteString( TEXT("    <TH>\r\n") );

			WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
			WriteString( TEXT("            <TR>\r\n") );

			// Insert the stage id
			if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_DOCRECOGNITION_USE) )
			{
				WriteString( TEXT("                <TD>\r\n") );
				WriteString( TEXT("                    <TABLE>\r\n") );
				WriteString( TEXT("                        <TR>\r\n") );
				if( m_ei.m_nFullStage )
				{
					WriteString( TEXT("                            <TD NOWRAP>\r\n") );
					WriteString( TEXT("                                <EM CLASS=\"docregid\">")
						+m_ei.StagesMakeIDString()
						+TEXT("&nbsp;</EM>\r\n") );
					WriteString( TEXT("                            </TD>\r\n") );
				}
				WriteString( TEXT("                            <TD CLASS=\"docreg\">\r\n") );
				WriteString( TEXT("                                ")+m_ei.ComposeTocTitle()+TEXT("\r\n") );
				WriteString( TEXT("                            </TD>\r\n") );
				WriteString( TEXT("                        </TR>\r\n") );
				WriteString( TEXT("                    </TABLE>\r\n") );
				WriteString( TEXT("                </TD>\r\n") );
			}

			// Insert the document title

			// Insert the ID if required by settings
			if( nId && m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			{
				TCHAR czBuffer[10];
				_itot( nId, czBuffer, 10 );
				WriteString( TEXT("                <TD CLASS=\"commnr\" ALIGN=\"right\" NOWRAP>\r\n") );
				WriteString( TEXT("                    COMMUNIQUÉ Nº:\r\n") );
				WriteString( TEXT("                </TD>\r\n") );
				WriteString( TEXT("                <TD WIDTH=\"5%\">\r\n") );
				WriteString( TEXT("                    <TABLE BORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"10\">\r\n") );
				WriteString( TEXT("                        <TR>\r\n") );
				WriteString( TEXT("                            <TD CLASS=\"commnr\">\r\n") );
				WriteString( TEXT("                                ")+CString(czBuffer)+TEXT(".\r\n") );
				WriteString( TEXT("                            </TD>\r\n") );
				WriteString( TEXT("                        </TR>\r\n") );
				WriteString( TEXT("                    </TABLE>\r\n") );
				WriteString( TEXT("                </TD>\r\n") );
			}

			WriteString( TEXT("            </TR>\r\n") );
			WriteString( TEXT("        </TABLE>\r\n") );
			WriteString( TEXT("        <HR SIZE=\"1\" NOSHADE>\r\n") );
			WriteString( TEXT("\r\n") );

			WriteString( TEXT("    </TH>\r\n") );
			WriteString( TEXT("    </TR>\r\n") );
			WriteString( TEXT("    </THEAD>\r\n") );
		}

	WriteString( TEXT("    <TR>\r\n") );
	WriteString( TEXT("    <TD>\r\n") );

	// Print additional security notice
	if ( m_bEvaluation )
	{
		WriteString( TEXT("        <P>\r\n") );
		WriteString( TEXT("            <EM>\r\n") );
		WriteString( TEXT("                StageRace Evaluation Mode\r\n") );
		WriteString( TEXT("            </EM>\r\n") );
		WriteString( TEXT("        </P>\r\n") );
	}

	// If provided by the user, include the link to a logo
	// (can be web or local, according to the user input)

	// Centered logo
	if( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo.SpanExcluding(TEXT(" ")).GetLength()
		&& m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_LOGOPOSITION_CENTER) )
	{
		WriteString( TEXT("        <CENTER>\r\n") );
		WriteString( TEXT("            <IMG SRC=\"")+((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo+TEXT("\" ALT=\"")+UnQuote(((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName)+TEXT("\">\r\n") );
		WriteString( TEXT("        </CENTER>\r\n") );
	}
	
	WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
	WriteString( TEXT("            <TR>\r\n") );

	// Left logo
	if( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo.SpanExcluding(TEXT(" ")).GetLength()
		&& m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_LOGOPOSITION_LEFT) )
	{
		WriteString( TEXT("                <TD>\r\n") );
		WriteString( TEXT("                    <IMG SRC=\"")+((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo+TEXT("\" ALT=\"")+UnQuote(((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName)+TEXT("\">\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
	}

	// Event name and sub title
	if( !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_TITLE_DONTSHOW) )
	{
		WriteString( TEXT("                <TD>\r\n") );

		CString cAlign;
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_TITLEALIGN_CENTER) )	cAlign = " ALIGN=\"center\"";
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_TITLEALIGN_RIGHT) )	cAlign = " ALIGN=\"right\"";
		
		WriteString( TEXT("                    <H1")+cAlign+TEXT(">")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName+TEXT("</H1>\r\n") );
		WriteString( TEXT("                    <H2")+cAlign+TEXT(">")+m_ei.GetSponsorSubTitle()+TEXT("</H2>\r\n") );

		WriteString( TEXT("                </TD>\r\n") );
	}
	
	// Right logo
	if( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo.SpanExcluding(TEXT(" ")).GetLength()
		&& m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_LOGOPOSITION_RIGHT) )
	{
		WriteString( TEXT("                <TD>\r\n") );
		WriteString( TEXT("                    <IMG SRC=\"")+((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_eventLogo+TEXT("\" ALT=\"")+UnQuote(((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName)+TEXT("\">\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
	}

	WriteString( TEXT("            </TR>\r\n") );
	WriteString( TEXT("        </TABLE>\r\n") );

	WriteString( TEXT("        <BR>\r\n") );
	WriteString( TEXT("\r\n") );

	PUBLI_PROPERTIES props[PUBLI_PROPERTIES_MAX];
	m_ei.GetPublicationProperties( props );
	Properties( props );
}

void CHtmlDoc::Footer(PUBLI_BODYCOLUMNS columns[]/*NULL*/, CSignOutList* pSignOuts/*=NULL*/, int nNumberNotStarted/*=-1*/, int nNumberStarters/*=-1*/, int nNumberLeft/*=-1*/, CString czDroppedOut/*=""*/, CString czCutOff/*=""*/)
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Footer(columns, pSignOuts, nNumberNotStarted, nNumberStarters, nNumberLeft, czDroppedOut, czCutOff);
	}
	if( !m_openSuccess )
		return;

	if( m_competitorsStarted )
	{
		m_competitorsStarted = false;
		WriteString( TEXT("        </TABLE>\r\n") );
		LabelEnd(PP_MAINCONTENT);
	}

	// We add eventual sign outs
	SignOuts( columns, pSignOuts );

	WriteString( TEXT("\r\n") );
	WriteString( TEXT("        <BR>\r\n") );
	WriteString( TEXT("        <HR SIZE=\"1\" NOSHADE>\r\n") );

	// Additional info
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_STATS_OTHERS)
		&& (nNumberStarters>=0) )
	{
		TCHAR czBuffer[10];

		WriteString( TEXT("\r\n") );
		Label(PP_STATS);
		WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
		WriteString( TEXT("            <TR>\r\n") );
		WriteString( TEXT("                <TD ALIGN=\"right\" NOWRAP>\r\n") );
		WriteString( TEXT("                    <TT>\r\n") );
		WriteString( TEXT("                        ")+AssembleStr( TEXT("FootNotStart"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
		WriteString( TEXT("                    </TT>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD>\r\n") );
 		_itot( nNumberNotStarted, czBuffer, 10 );
		WriteString( TEXT("                    <EM>")+CString(czBuffer)+TEXT("</EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD ALIGN=\"right\" NOWRAP>\r\n") );
		WriteString( TEXT("                    <TT>\r\n") );
		WriteString( TEXT("                        ")+AssembleStr( TEXT("FootNumStart"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
		WriteString( TEXT("                    </TT>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD>\r\n") );
 		_itot( nNumberStarters, czBuffer, 10 );
		WriteString( TEXT("                    <EM>")+CString(czBuffer)+TEXT("</EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );

		WriteString( TEXT("                <TD ALIGN=\"right\" NOWRAP>\r\n") );
		WriteString( TEXT("                    <TT>\r\n") );
		WriteString( TEXT("                        ")+AssembleStr( TEXT("FootRemain"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
		WriteString( TEXT("                    </TT>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD>\r\n") );
 		_itot( nNumberLeft, czBuffer, 10 );
		WriteString( TEXT("                    <EM>")+CString(czBuffer)+TEXT("</EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );

		WriteString( TEXT("            </TR>\r\n") );
		WriteString( TEXT("        </TABLE>\r\n") );
		
		WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
		WriteString( TEXT("            <TR>\r\n") );
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_STATS_CUTOFFS) )
		{
			WriteString( TEXT("                <TD ALIGN=\"right\" NOWRAP>\r\n") );
			WriteString( TEXT("                    <TT>\r\n") );
			WriteString( TEXT("                        ")+AssembleStr( TEXT("FootCutOff"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
			WriteString( TEXT("                    </TT>\r\n") );
			WriteString( TEXT("                </TD>\r\n") );
			WriteString( TEXT("                <TD>\r\n") );
			WriteString( TEXT("                    <EM>")+czCutOff+TEXT("</EM>\r\n") );
			WriteString( TEXT("                </TD>\r\n") );
		}
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_STATS_DROPOUTS) )
		{
			WriteString( TEXT("                <TD ALIGN=\"right\" NOWRAP>\r\n") );
			WriteString( TEXT("                    <TT>\r\n") );
			WriteString( TEXT("                        ")+AssembleStr( TEXT("FootDroppOut"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
			WriteString( TEXT("                    </TT>\r\n") );
			WriteString( TEXT("                </TD>\r\n") );
			WriteString( TEXT("                <TD>\r\n") );
			WriteString( TEXT("                    <EM>")+czDroppedOut+TEXT("</EM>\r\n") );
			WriteString( TEXT("                </TD>\r\n") );
		}
		WriteString( TEXT("            </TR>\r\n") );
		WriteString( TEXT("        </TABLE>\r\n") );

		LabelEnd(PP_STATS);
	}

	// Here we make an eventual commisionairs signature
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE) )
	{
		// The following code prints an eventual signature
		WriteString( TEXT("\r\n") );
		WriteString( TEXT("        <BLOCKQUOTE CLASS=\"signature\">\r\n") );
		
		Label(PP_SIGNATURE);
	
		CString czSignature;
		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_OWN) )
			czSignature = ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_signature;
		else
			czSignature = AssembleStr( TEXT("StdSignature"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );;
		
		czSignature = czSignature + TEXT("\r\n");
		while( czSignature.GetLength() )
		{
			WriteString( TEXT("            ") );
			WriteString( czSignature.Mid( 0, czSignature.Find( TEXT("\r\n") ) ) );
			WriteString( TEXT("\r\n") );
			czSignature = czSignature.Mid( czSignature.Find( TEXT("\r\n") ) );
			while( czSignature.Left( 2 ) == TEXT("\r\n") )
			{
				czSignature = czSignature.Mid( 2 );
				WriteString( TEXT("            <BR>\r\n") );
			} 
		}

		LabelEnd(PP_SIGNATURE);
		
		WriteString( TEXT("        </BLOCKQUOTE>\r\n") );
	}

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

		WriteString( TEXT("        <BR>\r\n") );
		WriteString( TEXT("        <EM CLASS=\"lastcalc\">\r\n") );
		Label(PP_TIMESTAMP);
		WriteString( TEXT("            ")+cLastCalculated+TEXT(": ")+cStamp+TEXT("\r\n") );
		LabelEnd(PP_TIMESTAMP);
		WriteString( TEXT("        </EM>\r\n") );
	}

	//
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE) || m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP) )
	{
		WriteString( TEXT("        <HR SIZE=\"1\" NOSHADE>\r\n") );
	}

	// This function makes the visible footer
	WriteString( TEXT("\r\n") );
	WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
	WriteString( TEXT("            <TR>\r\n") );
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG) )
	{
		WriteString( TEXT("                <TD VALIGN=\"top\" ALIGN=\"right\">\r\n") );
		WriteString( TEXT("                    <TT>\r\n") );
		WriteString( TEXT("                        Classification\r\n") );
		WriteString( TEXT("                        <BR>\r\n") );
		WriteString( TEXT("                        Service\r\n") );
		WriteString( TEXT("                    </TT>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		// With the classification service name (user defined)
		WriteString( TEXT("                <TD>\r\n") );
		WriteString( TEXT("                    <EM CLASS=\"prop\">\r\n") );
		WriteString( TEXT("                        ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyName+TEXT("\r\n") );
		WriteString( TEXT("                        <BR>\r\n") );

		if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASWEB) )
		{
			WriteString( TEXT("                        <A HREF=\"")+UnQuote(((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL)+TEXT("\" TARGET=\"_blank\">\r\n") );
			WriteString( TEXT("                        ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL+TEXT("\r\n") );
			WriteString( TEXT("                        </A>\r\n") );
		}
		else if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASWEBWITHHTTP) )
		{
			WriteString( TEXT("                        <A HREF=\"http://")+UnQuote(((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL)+TEXT("\" TARGET=\"_blank\">\r\n") );
			WriteString( TEXT("                        ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL+TEXT("\r\n") );
			WriteString( TEXT("                        </A>\r\n") );
		}
		else if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASEMAIL) )
		{
			WriteString( TEXT("                        <A HREF=\"mailto:")+UnQuote(((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL)+TEXT("\">\r\n") );
			WriteString( TEXT("                        ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL+TEXT("\r\n") );
			WriteString( TEXT("                        </A>\r\n") );
		}
		else
			WriteString( TEXT("                        ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_companyURL+TEXT("\r\n") );

		WriteString( TEXT("                    </EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		// And our name (hard coded)
		WriteString( TEXT("                <TD VALIGN=\"top\" ALIGN=\"right\">\r\n") );
		WriteString( TEXT("                    <TT>\r\n") );
		WriteString( TEXT("                        Classification\r\n") );
		WriteString( TEXT("                        <BR>\r\n") );
		WriteString( TEXT("                        Software\r\n") );
		WriteString( TEXT("                    </TT>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD>\r\n") );
		WriteString( TEXT("                    <EM CLASS=\"prop\">\r\n") );
		WriteString( TEXT("                        StageRace ")+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()+TEXT("\r\n") );
		WriteString( TEXT("                        <BR>\r\n") );
		WriteString( TEXT("                        <A HREF=\"http://www.stagerace.com\" TARGET=\"_blank\">\r\n") );
		WriteString( TEXT("                            www.stagerace.com\r\n") );
		WriteString( TEXT("                        </A>\r\n") );
		WriteString( TEXT("                    </EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
	}
	else
	{
		WriteString( TEXT("                <TD ALIGN=\"center\">\r\n") );
		WriteString( TEXT("                    <EM>\r\n") );
		WriteString( TEXT("                        StageRace ")+((CStageRaceApp*)AfxGetApp())->m_key.GetVersionTitle()+TEXT(" software &#151;\r\n") );
		WriteString( TEXT("                        <A HREF=\"http://www.stagerace.com\" TARGET=\"_blank\">\r\n") );
		WriteString( TEXT("                            www.stagerace.com\r\n") );
		WriteString( TEXT("                        </A>\r\n") );
		WriteString( TEXT("                    </EM>\r\n") );
		WriteString( TEXT("                </TD>\r\n") );
	}
	WriteString( TEXT("            </TR>\r\n") );
	WriteString( TEXT("        </TABLE>\r\n") );
	WriteString( TEXT("\r\n") );

	WriteString( TEXT("    </TD>\r\n") );
	WriteString( TEXT("    </TR>\r\n") );
	WriteString( TEXT("    </TABLE>\r\n") );
}


///////////////////////////////////////////////////////////////////////////
// SERVICES

CString CHtmlDoc::UnQuote(CString s)
{
	// Replace double quotes by single quotes
	// so that we can build safe HTML HREF's
	s.Replace( '\"', '\'' );
	return s;
}

CString CHtmlDoc::EncodeURL(CString cURL)
{
	// Replaces all unsafe characters with HTML escape
	// sequences according to W3C specifications
	// For instance: " " --> "%20"

	char hexVals[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		'A', 'B', 'C', 'D', 'E', 'F' };

	CString cNewURL = "";
	// Walk through the provided URL
	for( int i=0; i < cURL.GetLength(); i++ )
	{ 
		if( IsUnsafe( cURL[i] ) )
		{
			// Replace unsafe characters by their safe escape code
			unsigned char temp = cURL[i];
			cNewURL += TEXT("%") + CString(__toascii( hexVals[temp/16] )) + CString(__toascii( hexVals[temp%16] ));
		}
		else
			// Just copy safe characters
			cNewURL += cURL[i];
	}

	return cNewURL;
}

bool CHtmlDoc::IsUnsafe(unsigned char cCompare)
{
	// This function checks to see if a char is URL unsafe
	// Returns bool result. True = unsafe, False = safe
    //   reserved       = ";" | "/" | "?" | ":" | "@" | "&" | "=" | "+"
    //   extra          = "!" | "*" | "'" | "(" | ")" | ","
    //   safe           = "$" | "-" | "_" | "."
    //   unsafe         = CTL | SP | <"> | "#" | "%" | "<" | ">"

	CString unsafeString;
	unsafeString += TEXT(";/?:@&=+"); // reserved
	unsafeString += TEXT("\"#%<>");   // unsafe
	//unsafeString += TEXT("\\^[]`");
	//unsafeString += TEXT("()");
	if( (unsafeString.Find(cCompare)==-1) && (cCompare>32) && (cCompare<123) )
		return false;// found no unsafe chars, return false
	else
		return true;// found unsafe chars, return true
}


///////////////////////////////////////////////////////////////////////////
// MAIN COMPETITORS TABLE

void CHtmlDoc::StartCompetitorsTable(PUBLI_BODYCOLUMNS columns[])
{
	// Note: this method has not CSV counterpart (due to HTML specifics)
	// If this is the first line, the flag m_competitorsStarted will be
	// false and the table header will printed
	if( !m_competitorsStarted )
	{
		WriteString( TEXT("        <TABLE WIDTH=\"100%\" CELLSPACING=\"0\" CELLPADDING=\"0\" BORDER=\"0\">\r\n") );
		ColumnTitles(columns);
		m_competitorsStarted = true;
	};
}

void CHtmlDoc::ColumnTitle(CString title, int nColSpan/*=1*/)
{
	if( nColSpan==1 )
		WriteString( TEXT("                    <TH>\r\n") );
	else
	{
		TCHAR czBuffer[10];
		_itot( nColSpan, czBuffer, 10 );
		WriteString( TEXT("                    <TH COLSPAN=\"")+CString(czBuffer)+TEXT("\">\r\n") );
	}
	if( title.GetLength() )
	{
		WriteString( TEXT("                        ")+title+TEXT("\r\n") );
	}
	WriteString( TEXT("                    </TH>\r\n") );
}

void CHtmlDoc::ColumnTitles( PUBLI_BODYCOLUMNS columns[] )
{
	if( !m_openSuccess )
		return;

	// This function prints the column titles for the columns
	// with competitor information we need to be printed
	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed
	
	// Start the titles row
	WriteString( TEXT("            <THEAD>\r\n") );
	WriteString( TEXT("                <TR VALIGN=bottom>\r\n") );

	int i=0;
	while( columns[i]!=PBC_TERMINATOR ) // Print every column title
	{
		switch( columns[i] )
		{
			case PBC_SIGNINAREA:
				ColumnTitle( AssembleStr( TEXT("Signature"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_CATEGORY:
				ColumnTitle( AssembleStr( TEXT("Category"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_RIDER:
				ColumnTitle( AssembleStr( TEXT("Rider"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_COUNTRY:
				ColumnTitle( AssembleStr( TEXT("Country"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_LICENSE:
				ColumnTitle( AssembleStr( TEXT("License"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_STANO:
				ColumnTitle( AssembleStr( TEXT("StaNo"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_UCICODE:
				ColumnTitle( AssembleStr( TEXT("UCICode"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ), 2 );
				break;
			case PBC_RANK:
				ColumnTitle( AssembleStr( TEXT("Position"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TIME:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_SPEED:
				ColumnTitle( AssembleStr( TEXT("Speed"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_GAP:
			case PBC_NEWGAP:
				ColumnTitle( AssembleStr( TEXT("Gap"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_BONUSES:
				ColumnTitle( AssembleStr( TEXT("Bonuses"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_POINTS:
				ColumnTitle( AssembleStr( TEXT("Points"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TEAMCODE:
			case PBC_TEAMCODEFROMRANK:
			case PBC_TEAMNAME:
			case PBC_TEAMNAMEFROMRANK:
				ColumnTitle( AssembleStr( TEXT("Team"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_TIMEWITHTHOUSANDTH:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages), 2 );
				break;
			case PBC_STARTINGORDERTIME:
				ColumnTitle( AssembleStr( TEXT("Time"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_STARTINGORDER:
				ColumnTitle( AssembleStr( TEXT("Order"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
				break;
			case PBC_INVOLVEDBUNCH:
				ColumnTitle( AssembleStr( TEXT("InvolvdBunch"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
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
				ColumnTitle(AssembleStr( TEXT("Penalty"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ));
				break;
			case PBC_SIGNOUTREASON:
				ColumnTitle(AssembleStr( TEXT("Reason"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ));
				break;
		};
		i++;
		if( (columns[i]!=PBC_TERMINATOR) && ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_columnspacing )
		{
			TCHAR czBuffer[10];
			_itot( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_columnspacing, czBuffer, 10 );
			WriteString( TEXT("                    <TH WIDTH=\""+CString(czBuffer)+"\">&nbsp;</TH>\r\n") );
		}
	};

	// End the titles row
	WriteString( TEXT("                </TR>\r\n") );
	WriteString( TEXT("                <TR>\r\n") );
	if( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_columnspacing )
		ColumnTitle( "<HR SIZE=\"1\" NOSHADE>", CEventItem::GetPublicationColumnsCount( columns )
			+ CEventItem::GetPublicationColumnsArrayCount( columns ) );
	else
		ColumnTitle( "<HR SIZE=\"1\" NOSHADE>", CEventItem::GetPublicationColumnsCount( columns ) );
	WriteString( TEXT("                </TR>\r\n") );
	WriteString( TEXT("            </THEAD>\r\n") );
	WriteString( TEXT("\r\n") );
}

void CHtmlDoc::ColumnItem(CString item, int nColSpan/*=1*/)
{
	if( nColSpan==1 )
		WriteString( TEXT("                <TD>\r\n") );
	else
	{
		TCHAR czBuffer[10];
		_itot( nColSpan, czBuffer, 10 );
		WriteString( TEXT("                <TD COLSPAN=\"")+CString(czBuffer)+TEXT("\">\r\n") );
	}
	WriteString( TEXT("                    ")+item+TEXT("\r\n") );
	WriteString( TEXT("                </TD>\r\n") );
}

void CHtmlDoc::Competitor( PUBLI_BODYCOLUMNS columns[], WORD nComp, CArrival* pRank/*=NULL*/, CSignOut* pSignOut/*=NULL*/, bool bDraw/*=true*/, bool bBold/*=false*/, bool bSuppressGap/*=false*/ )
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Competitor(columns, nComp, pRank, pSignOut, bDraw, bBold, bSuppressGap);
	}
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one competitor

	// This function is called with an array of enumeration values (zero-
	// terminated) which contains the (order of) columns we need to be printed

	if( !m_competitorsStarted )
		Label(PP_MAINCONTENT);
	StartCompetitorsTable(columns);

	CCompetitor* pComp = NULL;
	if( m_pDocument->CompetitorsExist( nComp ) )
		pComp = &m_pDocument->CompetitorsGet( nComp );

	// Security
	if ( m_bEvaluation && (m_nPrintedRules>=9) )
		return;

	// Start the competitor row
	if( bBold )
		WriteString( TEXT("<TR CLASS=\"bold\" VALIGN=\"top\">\r\n") );
	else
		WriteString( TEXT("<TR VALIGN=\"top\">\r\n") );

	int i=0;
	while( true )
	{
		switch( columns[i++] )
		{
			case PBC_SIGNINAREA:
				WriteString( TEXT("<TD>&nbsp;<BR><TT>") );
				if( pComp )
				{
					TCHAR cBuffer[10];
					_itot( pComp->m_staNo, cBuffer, 10 );
					WriteString( cBuffer );
				}
				WriteString( TEXT("</TT>&nbsp;<HR SIZE=\"1\" NOSHADE>") );
				break;
			case PBC_CATEGORY:
				WriteString( TEXT("<TD>") );
				if( pComp )
					WriteString( pComp->m_category );
				break;
			case PBC_RIDER:
				WriteString( TEXT("<TD>") );
				if( pComp )
					WriteString( pComp->m_competitor );
				break;
			case PBC_COUNTRY:
				WriteString( TEXT("<TD>") );
				if( pComp )
					WriteString( pComp->m_countryCode );
				break;
			case PBC_LICENSE:
				WriteString( TEXT("<TD>") );
				if( pComp )
					WriteString( pComp->m_license );
				break;
			case PBC_STANO:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pComp )
				{
					TCHAR cBuffer[10];
					_itot( pComp->m_staNo, cBuffer, 10 );
					WriteString( cBuffer );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_TEAMCODEWITHOUTCOLUMNHEADER:
			case PBC_TEAMCODE:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_pTeam )
				{
					if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_HTML_HYPERLINKS_USE) )
						WriteString( TEXT("<A HREF=\"")
							+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 ))
							+TEXT("#")+EncodeURL(pComp->m_pTeam->m_code)+TEXT("\">") );
					WriteString( pComp->m_pTeam->m_code );
					if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_HTML_HYPERLINKS_USE) )
						WriteString( TEXT("</A>") );
				}
				break;
			case PBC_TEAMNAME:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_pTeam )
					WriteString( pComp->m_pTeam->m_name );
				break;
			case PBC_UCICODE:
				WriteString( TEXT("<TD WIDTH=\"1%\" CLASS=\"ucicode\">") );
				if( pComp )
					WriteString( pComp->m_UCICode.Left(3) );
				WriteString( TEXT("</TD><TD CLASS=\"ucicode\">") );
				if( pComp )
					WriteString( pComp->m_UCICode.Mid(3) );
				break;
			case PBC_RANK:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_rank, cBuffer, 10 );
					WriteString( cBuffer );
					WriteString( TEXT(".") );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_TIME:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
					WriteString( CStageTime( pRank->m_units ).GetFormattedLefttrimmed() );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_SPEED:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
				{
					const CHalfStage* pHS = ((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage, m_ei.m_nHalfStage);
					if( (pHS->m_rounds==1) || (pHS->m_stageType!=ST_NORMAL) )
						WriteString( CStageSpeed::GetSpeed( pHS->m_distance, pRank->m_units,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE ),
							", "
						) );
					else
						WriteString( CStageSpeed::GetSpeed( pHS->m_distance*pHS->m_rounds, pRank->m_units,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE ),
							", "
						) );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_INVOLVEDBUNCH:
				{
					WriteString( TEXT("<TD NOWRAP>") );
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
						WriteString( cBunch );
					}
					WriteString( TEXT("&nbsp;&nbsp;") );
				}
				break;
			case PBC_NEWGAP:
				if( !bSuppressGap && pRank )
				{
					if( pRank && ((pRank->m_units/1000)*1000-m_championTime != m_previousGap)
						|| m_previousGap==0 )
					{
						WriteString( TEXT("<TD ALIGN=\"right\">") );
						m_previousGap = (pRank->m_units/1000)*1000-m_championTime;
						WriteString( CStageTime( m_previousGap ).GetFormattedAlllefttrimmed() );
					}
					else
					{
						WriteString( TEXT("<TD ALIGN=\"right\">") );
						WriteString( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_sameGap );
					}
				}
				else
					WriteString( TEXT("<TD>") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_GAP:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( !bSuppressGap && pRank )
					WriteString( CStageTime( (pRank->m_units/1000)*1000-m_championTime ).GetFormattedAlllefttrimmed() );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_BONUSES:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank && pRank->m_bonus )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_bonus, cBuffer, 10 );
					WriteString( cBuffer );
					WriteString( TEXT("\"") );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_POINTS:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_points, cBuffer, 10 );
					WriteString( cBuffer );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_TEAMNAMEFROMRANK:
				WriteString( TEXT("<TD>") );
				if( pRank && pRank->m_pTeam )
					WriteString( pRank->m_pTeam->m_name );
				break;
			case PBC_TEAMCODEFROMRANK:
			case PBC_TEAMCODEFROMRANKWITHOUTCOLUMNHEADER:
				WriteString( TEXT("<TD>") );
				if( pRank && pRank->m_pTeam )
				{
					if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_HTML_HYPERLINKS_USE) )
						WriteString( TEXT("<A HREF=\"")
							+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 ))
							+TEXT("#")+EncodeURL(pRank->m_pTeam->m_code)+TEXT("\">") );
					WriteString( pRank->m_pTeam->m_code );
					if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_HTML_HYPERLINKS_USE) )
						WriteString( TEXT("</A>") );
				}
				break;
			case PBC_TIMEWITHTHOUSANDTH:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
					WriteString( CStageTime( pRank->m_units ).GetFormattedLefttrimmed() );
				WriteString( TEXT("</TD>") );
				WriteString( TEXT("<TD>") );
				if( bDraw && pRank )
					WriteString( CStageTime( pRank ? pRank->m_units:0 ).GetThousandth() );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_STARTINGORDERTIME:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
					WriteString( CStageTime( pRank->m_unitsAtStart ).GetFormattedLefttrimmed() );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_STARTINGORDER:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_order, cBuffer, 10 );
					WriteString( cBuffer );
					WriteString( TEXT(".") );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK1:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask1 )
					WriteString( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask1icon );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK2:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask2 )
					WriteString( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask2icon );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK3:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask3 )
					WriteString( ((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask3icon );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK4:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask4 )
					WriteString( TEXT("M4") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK5:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask5 )
					WriteString( TEXT("M5") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK6:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask6 )
					WriteString( TEXT("M6") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK7:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask7 )
					WriteString( TEXT("M7") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK8:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask8 )
					WriteString( TEXT("M8") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK9:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask9 )
					WriteString( TEXT("M9") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_MASK10:
				WriteString( TEXT("<TD>") );
				if( pComp && pComp->m_mask10 )
					WriteString( TEXT("M10") );
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_PENALTY:
				WriteString( TEXT("<TD ALIGN=\"right\">") );
				if( pRank && pRank->m_penalty )
				{
					TCHAR cBuffer[10];
					_itot( pRank->m_penalty, cBuffer, 10 );
					WriteString( cBuffer );
					WriteString( TEXT("\"") );
				}
				WriteString( TEXT("&nbsp;&nbsp;") );
				break;
			case PBC_SIGNOUTREASON:
				WriteString( TEXT("<TD>") );
				if( pSignOut )
					WriteString( pSignOut->m_reasonOfSignOut );
				break;
			case PBC_TERMINATOR:
			default:
				// End the competitor row
				WriteString( TEXT("</TR>\r\n\r\n") );

				// Add 1 to the rules count for the security
				m_nPrintedRules++;

				// End subroutine
				return;
		};
		WriteString( TEXT("</TD>\r\n") );
		if( (columns[i]!=PBC_TERMINATOR) && ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_columnspacing )
		{
			TCHAR czBuffer[10];
			_itot( ((CSettingsHTML*)m_pDocument->m_allsettings.GetSettings(SETT_HTML))->m_columnspacing, czBuffer, 10 );
			WriteString( TEXT("<TD WIDTH=\""+CString(czBuffer)+"\">&nbsp;</TD>\r\n") );
		}
	};
}

void CHtmlDoc::SayText(PUBLI_BODYCOLUMNS columns[], CString czText)
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->SayText(columns, czText);
	}
	if( !m_openSuccess )
		return;

	// This function prints a single row with the provided text

	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed

	if( !m_competitorsStarted )
		Label(PP_MAINCONTENT);
	StartCompetitorsTable(columns);

	// Start the competitor row
	WriteString( TEXT("<TR VALIGN=\"top\">\r\n") );

	ColumnItem( 
		TEXT("<BR><EM CLASS=\"section\">") + czText + TEXT("</EM>"),
		CEventItem::GetPublicationColumnsCount(columns) );

	// End the competitor row
	WriteString( TEXT("</TR>\r\n\r\n") );
}

void CHtmlDoc::SaySprint(PUBLI_BODYCOLUMNS columns[], int nSprint)
{
	// Helper
	TCHAR cBuffer[10];
	_itot( nSprint, cBuffer, 10 );

	SayText(columns, CString(cBuffer));
}

void CHtmlDoc::Legenda(PUBLI_BODYCOLUMNS columns[])
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Legenda(columns);
	}
	if( !m_openSuccess )
		return;

	WriteString( TEXT("        <TABLE>\r\n") );
	int i=0;
	while( columns[i]!=PBC_TERMINATOR )
	{
		switch( columns[i] )
		{
			case PBC_MASK1:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask1icon+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK2:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask2icon+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK3:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                ")+((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_mask3icon+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK4:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M4\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK5:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M5\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK6:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M6\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK7:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M7\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK8:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M8\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK9:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M9\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
			case PBC_MASK10:
				WriteString( TEXT("        <TR>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                M10\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("            <TD>\r\n") );
				WriteString( TEXT("                : ")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10+TEXT("\r\n") );
				WriteString( TEXT("            </TD>\r\n") );
				WriteString( TEXT("        </TR>\r\n") );
				break;
		};
		i++;
	};
	WriteString( TEXT("        </TABLE>\r\n") );
	WriteString( TEXT("\r\n") );
	WriteString( TEXT("        <BR>\r\n") );
	WriteString( TEXT("        <BR>\r\n") );
	WriteString( TEXT("\r\n") );
}

void CHtmlDoc::TeamHeader(PUBLI_BODYCOLUMNS columns[], CTeam *pTeam)
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->TeamHeader(columns, pTeam);
	}
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one team

	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed

	if( !m_competitorsStarted )
		Label(PP_MAINCONTENT);
	StartCompetitorsTable(columns);

	// Start the competitor row
	WriteString( TEXT("<TR VALIGN=\"top\">\r\n") );

	CString cLine;
	cLine = "<BR><TABLE WIDTH=\"100%\"><TR VALIGN=\"top\"><TD>";

	if( pTeam )
		cLine += TEXT("<A NAME=\"")+EncodeURL(pTeam->m_code)+TEXT("\"></A><EM>")
			+ pTeam->m_code
			+ TEXT("&nbsp;&nbsp;")
			+ pTeam->m_name
			+ TEXT("</EM>");
	else
		cLine += AssembleStr( TEXT("WithoutTeam"), TEXT(" - "), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
	
	cLine += TEXT("</TD><TD ALIGN=\"right\">");

	if( pTeam )
		cLine += pTeam->m_country;

	cLine += TEXT("</TD></TR></TABLE>");

	ColumnItem( 
		cLine,
		CEventItem::GetPublicationColumnsCount(columns) );

	// End the competitor row
	WriteString( TEXT("</TR>\r\n\r\n") );
}

void CHtmlDoc::TeamFooter(PUBLI_BODYCOLUMNS columns[], CTeam *pTeam)
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->TeamFooter(columns, pTeam);
	}
	if( !m_openSuccess )
		return;

	// This function prints a single row with the information of one team

	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) columns we need to be printed

	if( pTeam && pTeam->m_manager.GetLength() )
	{
		if( !m_competitorsStarted )
			Label(PP_MAINCONTENT);
		StartCompetitorsTable(columns);

		// Start the competitor row
		WriteString( TEXT("<TR VALIGN=\"top\">\r\n") );

		CString cLine;
		cLine = AssembleStr( TEXT("TeamCaptain"), TEXT(", "), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		cLine += TEXT(": <U>")
			+ pTeam->m_manager
			+ TEXT("</U>");

		ColumnItem( 
			cLine,
			CEventItem::GetPublicationColumnsCount(columns) );

		// End the competitor row
		WriteString( TEXT("</TR>\r\n\r\n") );
	}
}

void CHtmlDoc::Break(PUBLI_BODYCOLUMNS columns[])
{
	// Generation of CSV counterpart of this method
	if( m_ptextdoc )
	{
		m_ptextdoc->m_championTime = this->m_championTime;
		m_ptextdoc->Break(columns);
	}
	if( !m_openSuccess )
		return;

	// Start the competitor row
	WriteString( TEXT("<TR>\r\n") );

	int i=0;
	while( columns[i++]!=0 )
	{
		WriteString( TEXT("<TD><BR></TD>") );
	}

	// End the competitor row
	WriteString( TEXT("</TR>\r\n\r\n") );
}


///////////////////////////////////////////////////////////////////////////
// PROPERTIES

void CHtmlDoc::Property(CString caption, int property)
{
	CString str;
	str.Format( TEXT("%d"), property );
	Property( caption, str );
}

void CHtmlDoc::Property(CString caption, CString property)
{
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_PROPS_DIRECTION_HORIZONTAL) )
		WriteString( TEXT("                <TD ALIGN=\"right\">\r\n") );
	else
		WriteString( TEXT("                <TD VALIGN=\"top\">\r\n") );
	WriteString( TEXT("                    <TT>\r\n") );
	WriteString( TEXT("                        ")+caption+TEXT("\r\n") );
	WriteString( TEXT("                    </TT>\r\n") );
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_PROPS_DIRECTION_HORIZONTAL) )
	{
		WriteString( TEXT("                </TD>\r\n") );
		WriteString( TEXT("                <TD>\r\n") );
	}
	else
		WriteString( TEXT("                    <BR>\r\n") );

	WriteString( TEXT("                    <EM CLASS=\"prop\">")+property+TEXT("</EM>\r\n") );
	WriteString( TEXT("                </TD>\r\n") );
}

void CHtmlDoc::Property(CString caption)
{
	WriteString( TEXT("                <TD ALIGN=\"right\">\r\n") );
	WriteString( TEXT("                    <TT>\r\n") );
	WriteString( TEXT("                        ")+caption+TEXT("\r\n") );
	WriteString( TEXT("                    </TT>\r\n") );
	WriteString( TEXT("                </TD>\r\n") );
}

void CHtmlDoc::Properties( PUBLI_PROPERTIES props[], CObject* pObj/*=NULL*/ )
{
	if( !m_openSuccess )
		return;

	// This function prints the properties in a row
	// This function is called with an array of integers (zero-terminated)
	// which contains the (order of) properties we need to be printed

	if( CEventItem::GetPublicationPropertiesCount(props) )
	Label(PP_PROPERTIES);
	
	const CHalfStage* pHS = ((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage, m_ei.m_nHalfStage);
	bool bPropertiesStarted = false;
	int i=0;
	while( props[i]!=PPR_TERMINATOR ) // Print every property
	{
		if( !bPropertiesStarted )
		{
			// Start the properties table
			WriteString( TEXT("        <TABLE WIDTH=\"100%\">\r\n") );
			WriteString( TEXT("            <TR>\r\n") );
			bPropertiesStarted = true;
		}
		switch( props[i] )
		{
			case PPR_COMPETITORSCOUNT:
				Property( AssembleStr( TEXT("CountComps"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					m_pDocument->CompetitorsCount() );
				break;
			case PPR_TEAMSCOUNT:
				Property( AssembleStr( TEXT("CountTeams"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					m_pDocument->TeamsCountUsed() );
				break;
			case PPR_CATEGORY:
				Property( AssembleStr( TEXT("Category"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_category );
				break;
			case PPR_DATE:
				Property( AssembleStr( TEXT("Date"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_dates );
				break;
			case PPR_ORGANISER:
				Property( AssembleStr( TEXT("Organiser"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_organiser );
				break;
			case PPR_LOCATION:
				Property( AssembleStr( TEXT("Location"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_location );
				break;
			case PPR_TITLE_COMMUNIQUE:
				Property( AssembleStr( TEXT("Title"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CCommunique*)pObj)->m_title );
				break;
			case PPR_SINGLE_STAGE_CLASSIFICATION:
				Property( AssembleStr( TEXT("PropArrival"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_GENERAL_CLASSIFICATION:
				Property( AssembleStr( TEXT("PropGeneral"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_STAGE_INDICATOR:
				Property( AssembleStr( TEXT("Stage"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
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
						cCompose += TEXT("<BR>");
						cCompose += CStageDistance::DistanceFromTo(
							m_ei.GetOfficialDistanceCumulativeBefore(),
							m_ei.GetOfficialDistanceCumulative(),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						);
					}

					Property( AssembleStr( TEXT("Distance"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						cCompose );
				}
				break;
			case PPR_OVERALL_DISTANCE:
				{
					Property(
						AssembleStr( TEXT("DistancTotal"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
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
					Property( AssembleStr( TEXT("PropSpeed"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						CStageSpeed::GetSpeed( pHS->m_distance, m_championTime,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						) );
				else
					Property( AssembleStr( TEXT("PropSpeed"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						CStageSpeed::GetSpeed( pHS->m_distance*pHS->m_rounds, m_championTime,
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
							m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
						) );
				break;
			case PPR_OVERALL_SPEED:
				Property( AssembleStr( TEXT("PropSpeed"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageSpeed::GetSpeed( m_ei.GetRealDistanceCumulative(), m_championTime,
						m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_KM ),
						m_pDocument->m_allsettings.ValueGet( IDS_SETT_PUBL_DISTANCES_MILE )
					) );
				break;
			case PPR_MASK_1:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1 );
				break;
			case PPR_MASK_2:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2 );
				break;
			case PPR_MASK_3:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3 );
				break;
			case PPR_MASK_4:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4 );
				break;
			case PPR_MASK_5:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5 );
				break;
			case PPR_MASK_6:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6 );
				break;
			case PPR_MASK_7:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7 );
				break;
			case PPR_MASK_8:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8 );
				break;
			case PPR_MASK_9:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9 );
				break;
			case PPR_MASK_10:
				Property( AssembleStr( TEXT("PropSepClass"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10 );
				break;
			case PPR_SPRINTS:
				Property( AssembleStr( TEXT("PropSprints"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_POINTS:
				Property( AssembleStr( TEXT("PropPoints"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_CLIMBS:
				Property( AssembleStr( TEXT("PropClimbs"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_MOSTAGGRESSIVE:
				Property( AssembleStr( TEXT("PropAggressv"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_title );
				break;
			case PPR_HALF_STAGE_INDICATOR:
				if( ((CStageRaceDoc*)m_pDocument)->StagesGet(m_ei.m_nFullStage)->CountHalfStages()>1 )
				{
					Property( AssembleStr( TEXT("HalfStage"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						pHS->m_title );
				}
				else
				{
					Property( AssembleStr( TEXT("Stage"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
						pHS->m_title );
				}
				break;
			case PPR_START_OF_EVENT_TIME:
				Property( AssembleStr( TEXT("OpeningHour"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					pHS->m_openingHour );
				break;
			case PPR_DATE_COMMUNIQUE:
				Property( AssembleStr( TEXT("Date"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					((CCommunique*)pObj)->m_date );
				break;
			case PPR_TIME_OF_WINNER:
				Property( AssembleStr( TEXT("TimeOfWinner"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageTime( m_championTime ).GetFormattedLefttrimmed() );
				break;
			case PPR_TIME_OF_WINNER_WITHTHOUSANDTH:
				Property( AssembleStr( TEXT("TimeOfWinner"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ),
					CStageTime( m_championTime ).GetFormattedLefttrimmed()+CStageTime( m_championTime ).GetThousandth() );
				break;

			// More to come here!

			case PPR_LINEBREAK:
			default: // end of row
				WriteString( TEXT("            </TR>\r\n") );
				WriteString( TEXT("        </TABLE>\r\n") );
				WriteString( TEXT("        <BR>\r\n") );
				WriteString( TEXT("\r\n") );
				bPropertiesStarted = false; // New row must be started in case of more properties
		}
		i++;
	}
	if( bPropertiesStarted )
	{
		WriteString( TEXT("            </TR>\r\n") );
		WriteString( TEXT("        </TABLE>\r\n") );
		LabelEnd(PP_PROPERTIES);
		WriteString( TEXT("\r\n") );
		WriteString( TEXT("        <BR>\r\n") );
		WriteString( TEXT("        <BR>\r\n") );
		WriteString( TEXT("\r\n") );
	}
}


///////////////////////////////////////////////////////////////////////////
// VARIOUS

void CHtmlDoc::Communique(CCommunique* pComm)
{
	// Note: this method has not CSV counterpart (communique not supported)
	if( !m_openSuccess )
		return;

	PUBLI_PROPERTIES props[] = { PPR_TITLE_COMMUNIQUE, PPR_DATE_COMMUNIQUE, PPR_TERMINATOR };
	Properties( props, pComm );

	Label(PP_MAINCONTENT);
	WriteString( CommuniqueStatic( pComm, m_pDocument ) );
	LabelEnd(PP_MAINCONTENT);
}

CString CHtmlDoc::CommuniqueStatic(CCommunique *pComm, const CStageRaceDoc *pDoc)
{
	CString cReturn;
	cReturn += TEXT("        <BLOCKQUOTE CLASS=\"communique\">\r\n");
	cReturn += TEXT("            <P>\r\n");

	// The following code prints the communique
	// Every \r\n is being replaced by a html <BR>
	CString szContentsComm = pComm->m_contents;
	szContentsComm = szContentsComm + TEXT("\r\n");
	while( szContentsComm.GetLength() )
	{
		cReturn += TEXT("                ");
		cReturn += szContentsComm.Mid( 0, szContentsComm.Find( TEXT("\r\n") ) );
		cReturn += TEXT("\r\n");
		szContentsComm = szContentsComm.Mid( szContentsComm.Find( TEXT("\r\n") ) );
		while( szContentsComm.Left( 4 ) == "\r\n\r\n" )
		{
			szContentsComm = szContentsComm.Mid( 4 );
			cReturn += TEXT("            </P>\r\n");
			cReturn += TEXT("            <P>\r\n");
		} 
		while( szContentsComm.Left( 2 ) == "\r\n" )
		{
			szContentsComm = szContentsComm.Mid( 2 );
			cReturn += TEXT("                <BR>\r\n");
		}
	}

	cReturn += TEXT("            </P>\r\n");
	cReturn += TEXT("        </BLOCKQUOTE>\r\n");

	// Insert page breaks
	cReturn.Replace( TEXT("{pagebreak}"), TEXT("<BR STYLE=\"page-break-after: always\">") );

	{
		// Insert competitors
		int n1 = 0;
		int n2 = 0;
		while( n1!=-1 && n2!=-1 )
		{
			n1 = cReturn.Find( TEXT("{comp,"), n1 );
			n2 = cReturn.Find( '}', n1 );
			if( n2!=-1 )
			{
				// Get the start no.
				int nStaNo = _ttoi( cReturn.Mid( n1+6, n2-n1-6 ) );

				CString temp;
				if( pDoc->CompetitorsExist(nStaNo) )
				{
					CCompetitor comp = pDoc->CompetitorsGet(nStaNo);

					// Set up a string
					if( comp.m_pTeam )
					{
						temp.Format(
							TEXT("#%d %s (%s, %s)"),
							nStaNo,
							comp.m_competitor,
							comp.m_UCICode,
							comp.m_pTeam->m_code );
					}
					else
					{
						temp.Format(
							TEXT("#%d %s (%s)"),
							nStaNo,
							comp.m_competitor,
							comp.m_UCICode );
					}
				}
				else
				{
					// Set up a string
					temp.Format( TEXT("#%d"), nStaNo );
				}
				// Insert the string
				cReturn = cReturn.Left( n1 ) + TEXT("<I>") + temp + TEXT("</I>") + cReturn.Mid( n2+1 );
			}
		}
	}

	{
		// Insert teams
		int n1 = 0;
		int n2 = 0;
		while( n1!=-1 && n2!=-1 )
		{
			n1 = cReturn.Find( TEXT("{team,"), n1 );
			n2 = cReturn.Find( '}', n1 );
			if( n2!=-1 )
			{
				// Get the team code
				CString code = cReturn.Mid( n1+6, n2-n1-6 );
				// Format the team code
				code.MakeUpper();
				code.TrimLeft();
				code.TrimRight();
				code = code.Left(3);

				CString temp;
				if( pDoc->TeamsExist(code) )
				{
					CTeam team = pDoc->TeamsGet(code);

					// Set up a string
					temp.Format(
						TEXT("%s %s"),
						team.m_code,
						team.m_name );
				}
				else
				{
					// Set up a string
					temp.Format( TEXT("%s"), code );
				}
				// Insert the string
				cReturn = cReturn.Left( n1 ) + TEXT("<I>") + temp + TEXT("</I>") + cReturn.Mid( n2+1 );
			}
		}
	}

	{
		// Insert captain
		int n1 = 0;
		int n2 = 0;
		while( n1!=-1 && n2!=-1 )
		{
			n1 = cReturn.Find( TEXT("{captain,"), n1 );
			n2 = cReturn.Find( '}', n1 );
			if( n2!=-1 )
			{
				// Get the team code
				CString code = cReturn.Mid( n1+9, n2-n1-9 );
				// Format the team code
				code.MakeUpper();
				code.TrimLeft();
				code.TrimRight();
				code = code.Left(3);

				CString temp;
				if( pDoc->TeamsExist(code) )
				{
					CTeam team = pDoc->TeamsGet(code);

					// Set up a string
					temp.Format(
						TEXT("%s (%s, %s)"),
						team.m_manager.GetLength()?team.m_manager:TEXT("..."),
						team.m_code,
						team.m_name );
				}
				else
				{
					// Set up a string
					temp.Format( TEXT("%s"), code );
				}
				// Insert the string
				cReturn = cReturn.Left( n1 ) + TEXT("<I>") + temp + TEXT("</I>") + cReturn.Mid( n2+1 );
			}
		}
	}

	return cReturn;
}

void CHtmlDoc::Toc()
{
	// Note: this method has not CSV counterpart (TOC not supported)
	if( !m_openSuccess )
		return;

	// This function composes the TOC
	//
	// Rows are made clickable when publication status allows this
	// Therefore CEventItem::ComposeFileNameHTML is used
	//
	// Contents of rows are taken from CEventItem::ComposeTocTitle
	// except for event, full stage and half stage titles
	//

	Label(PP_MAINCONTENT);

    WriteString( TEXT("        <CENTER>\r\n") );
    WriteString( TEXT("            <TABLE BORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"10\">\r\n") );
    WriteString( TEXT("                <TR>\r\n") );
    WriteString( TEXT("                    <TD>\r\n") );
    WriteString( TEXT("                        <TABLE CELLSPACING=\"0\" CELLPADDING=\"3\">\r\n") );

	// Event title
	TocRow( 0, TEXT("<EM>")+((CSettingsGeneral*)m_pDocument->m_allsettings.GetSettings(SETT_GENERAL))->m_eventName+TEXT("</EM>") );

	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_TOC_COMPETITORS_TOP) )
	{
		TocRow( 0, TEXT("<HR SIZE=\"1\" NOSHADE>") );
		// Competitor lists AT THE TOP
		if( m_pDocument->m_idCompetitors.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			TocRow( 0, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS1, 0, 0 ))+TEXT("\">")
				+CEventItem::ComposeTocTitle( m_pDocument, TI_LISTCOMPETITORS1, 0, 0 )+TEXT("</A>"), &m_pDocument->m_idCompetitors );
		if( m_pDocument->m_idTeams.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
			TocRow( 0, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 ))+TEXT("\">")
				+CEventItem::ComposeTocTitle( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 )+TEXT("</A>"), &m_pDocument->m_idTeams );
	}

	// Contents
	const CFullStage* pFullStage;
	// Iterate the full stages list
	for( int i=1; i <= m_pDocument->StagesFullCount(); i++ )
	{
		TocRow( 0, TEXT("<HR SIZE=\"1\" NOSHADE>") );

		int nFS;
		if(m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_TOC_ORDER_NORMAL))
			nFS = i;
		else // reverse
			nFS = m_pDocument->StagesFullCount()+1-i;

		// Add every full stage
		pFullStage = ((CStageRaceDoc*)m_pDocument)->StagesGet( nFS );
		TocRow( 1, TEXT("<EM>")+pFullStage->m_date+TEXT("</EM>"), NULL, CEventItem::StagesMakeIDString(nFS,m_pDocument) );

		// Full stage communique
		if ( pFullStage->m_communique.m_contents.GetLength() && (pFullStage->m_communique.m_id.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
			TocRow( 2, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_COMMUNIQUE, nFS, 0 ))+TEXT("\">")
				+CEventItem::ComposeTocTitle( m_pDocument, TI_COMMUNIQUE, nFS, 0 )+TEXT("</A>"), &pFullStage->m_communique.m_id );

		const CHalfStage* pHalfStage;
		// Iterate the half stages list
		for( int j=1; j <= pFullStage->CountHalfStages(); j++ )
		{
			int nHS;
			if(m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_TOC_ORDER_NORMAL))
				nHS = j;
			else // reverse
				nHS = pFullStage->CountHalfStages()+1-j;

			// Add every half stage
			pHalfStage = ((CStageRaceDoc*)m_pDocument)->StagesGet( nFS, nHS );
			if( pHalfStage->m_idStage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
				TocRow( 2, TEXT("<A HREF=\"")
					+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_HALFSTAGE, nFS, nHS ))
					+TEXT("\"><EM>")+pHalfStage->m_title+TEXT("</EM> (")+CEventItem::ComposeTocTitle( m_pDocument, TI_HALFSTAGE, nFS, nHS )+TEXT(")</A>"), &pHalfStage->m_idStage, CEventItem::StagesMakeIDString(nFS,nHS,m_pDocument) );
			else
				TocRow( 2, TEXT("<EM>")+pHalfStage->m_title+TEXT("</EM> (")+CEventItem::ComposeTocTitle( m_pDocument, TI_HALFSTAGE, nFS, nHS )+TEXT(")"), &pHalfStage->m_idStage, CEventItem::StagesMakeIDString(nFS,nHS,m_pDocument) );

			// Add half stage items

				if( pHalfStage->m_stageType==ST_TT_GROSS )
				{
					if( pHalfStage->m_idTTArrival.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )	
						TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_TTARRIVALLIST, nFS, nHS ))+TEXT("\">")
							+CEventItem::ComposeTocTitle( m_pDocument, TI_TTARRIVALLIST, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idTTArrival );
				}

				// General classifications
				if( pHalfStage->m_idGeneral.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSGENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSGENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idGeneral );

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) && (pHalfStage->m_idMask1stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK1STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK1STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask1stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE1) && (pHalfStage->m_idMask1gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK1GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK1GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask1gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) && (pHalfStage->m_idMask2stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK2STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK2STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask2stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE2) && (pHalfStage->m_idMask2gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK2GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK2GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask2gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) && (pHalfStage->m_idMask3stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK3STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK3STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask3stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE3) && (pHalfStage->m_idMask3gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK3GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK3GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask3gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) && (pHalfStage->m_idMask4stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK4STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK4STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask4stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE4) && (pHalfStage->m_idMask4gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK4GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK4GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask4gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) && (pHalfStage->m_idMask5stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK5STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK5STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask5stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE5) && (pHalfStage->m_idMask5gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK5GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK5GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask5gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) && (pHalfStage->m_idMask6stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK6STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK6STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask6stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE6) && (pHalfStage->m_idMask6gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK6GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK6GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask6gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) && (pHalfStage->m_idMask7stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK7STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK7STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask7stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE7) && (pHalfStage->m_idMask7gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK7GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK7GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask7gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) && (pHalfStage->m_idMask8stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK8STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK8STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask8stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE8) && (pHalfStage->m_idMask8gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK8GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK8GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask8gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) && (pHalfStage->m_idMask9stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK9STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK9STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask9stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE9) && (pHalfStage->m_idMask9gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK9GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK9GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask9gen );
				}			

				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) && (pHalfStage->m_idMask10stage.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK10STAGE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK10STAGE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask10stage );
				}			
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_USE10) && (pHalfStage->m_idMask10gen.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSMASK10GENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSMASK10GENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMask10gen );
				}			

				// Teams classification
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_RANK_TEAMS_GENERATE) && (pHalfStage->m_idTeams.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSTEAMS, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSTEAMS, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idTeams );

				// Additional classifications
				if( pHalfStage->m_sprintpointsCount && (pHalfStage->m_idSprints.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_SPRINT, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_SPRINT, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idSprints );
				if( pHalfStage->m_climbsorder.GetCount() && (pHalfStage->m_idClimbs.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLIMB, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLIMB, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idClimbs );
				if( pHalfStage->m_pointspointsFinish.GetCount() && (pHalfStage->m_idPoints.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_POINTS, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_POINTS, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idPoints );
				if( pHalfStage->m_mostaggressivepoints.GetCount() && (pHalfStage->m_idMostAggressive.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_MOSTAGGRESSIVE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_MOSTAGGRESSIVE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idMostAggressive );
			
				// Half stage communique
				if ( pHalfStage->m_communique.m_contents.GetLength() && (pHalfStage->m_communique.m_id.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)) )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_COMMUNIQUE, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_COMMUNIQUE, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_communique.m_id );

				// Cross out list
				if( pHalfStage->m_idCrossOut.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CROSSOUTLIST, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CROSSOUTLIST, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idCrossOut );
				
				// Sign in list
				if( pHalfStage->m_idSignIn.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_SIGNINLIST, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_SIGNINLIST, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idCrossOut );
				
				// General classification sorted on stano
				if( ( pHalfStage->m_idGeneralStaNoSorted.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
						&& m_pDocument->m_allsettings.ValueGet(IDS_SETT_RANK_GENERAL_GENERATETSTANOSORTEDGENERAL) )
				{
					TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_CLASSSTANOSORTEDGENERAL, nFS, nHS ))+TEXT("\">")
						+CEventItem::ComposeTocTitle( m_pDocument, TI_CLASSSTANOSORTEDGENERAL, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idGeneralStaNoSorted );
				}

				// Time trial order
				// depending on type of half stage
				if ( pHalfStage->m_stageType!=ST_NORMAL )
				{
					if( pHalfStage->m_idStartList.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
						TocRow( 3, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_TIMETRIALORDER, nFS, nHS ))+TEXT("\">")
							+CEventItem::ComposeTocTitle( m_pDocument, TI_TIMETRIALORDER, nFS, nHS )+TEXT("</A>"), &pHalfStage->m_idStartList );
				}
		}
	}

	// Event communique
	if( m_pDocument->m_communique.m_contents.GetLength() && (m_pDocument->m_communique.m_id.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) ) )
	{
		TocRow( 0, TEXT("<HR SIZE=\"1\" NOSHADE>") );
		TocRow( 0, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_COMMUNIQUE, 0, 0 ))+TEXT("\">")
			+CEventItem::ComposeTocTitle( m_pDocument, TI_COMMUNIQUE, 0, 0 )+TEXT("</A>"), &m_pDocument->m_communique.m_id );
	}

	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_TOC_COMPETITORS_BOTTOM) )
	{
		TocRow( 0, TEXT("<HR SIZE=\"1\" NOSHADE>") );
		// Competitor lists AT THE BOTTOM
		if( m_pDocument->m_idCompetitors.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
			TocRow( 0, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS1, 0, 0 ))+TEXT("\">")
				+CEventItem::ComposeTocTitle( m_pDocument, TI_LISTCOMPETITORS1, 0, 0 )+TEXT("</A>"), &m_pDocument->m_idCompetitors );
		if( m_pDocument->m_idTeams.IsPublished() || !m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE)  )
			TocRow( 0, TEXT("<A HREF=\"")+EncodeURL(CEventItem::ComposeFileNameHTML( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 ))+TEXT("\">")
				+CEventItem::ComposeTocTitle( m_pDocument, TI_LISTCOMPETITORS2, 0, 0 )+TEXT("</A>"), &m_pDocument->m_idTeams );
	}

    WriteString( TEXT("                        </TABLE>\r\n") );
    WriteString( TEXT("                    </TD>\r\n") );
    WriteString( TEXT("                </TR>\r\n") );
    WriteString( TEXT("            </TABLE>\r\n") );
    WriteString( TEXT("        </CENTER>\r\n") );

	LabelEnd(PP_MAINCONTENT);
}

#define MAXTOCROWINDENT 4
void CHtmlDoc::TocRow(int nIndent, CString cContent, const CId* objId/*=NULL*/, CString cNo/*=""*/ )
{
	// Note: this method has not CSV counterpart (TOC not supported)
	if( !m_openSuccess )
		return;

	// Provides one row for the table of contents
	//
	//            |                         |
	//  stage no. | publication description | publication no.
	//            |                         |

	TCHAR czBuffer[10];
    WriteString( TEXT("                            <TR>\r\n") );
    WriteString( TEXT("                                <TD NOWRAP VALIGN=\"top\">\r\n") );
    WriteString( TEXT("                                    ")+cNo+TEXT("&nbsp;\r\n") );
    WriteString( TEXT("                                </TD>\r\n") );
	if( nIndent )
	{
		WriteString( TEXT("                                <TD COLSPAN=\"") );
		_itot( nIndent, czBuffer, 10 );
		WriteString( CString(czBuffer) );
		WriteString( TEXT("\" WIDTH=\"") );
		_itot( 7*nIndent, czBuffer, 10 );
		WriteString( CString(czBuffer) );
		WriteString( TEXT("%\">\r\n") );
		WriteString( TEXT("                                    &nbsp;\r\n") );
		WriteString( TEXT("                                </TD>\r\n") );
	}
	if( nIndent==MAXTOCROWINDENT )
		WriteString( TEXT("                                <TD VALIGN=\"top\">\r\n") );
	else
	{
		WriteString( TEXT("                                <TD VALIGN=\"top\" COLSPAN=\"") );
		_itot( MAXTOCROWINDENT-nIndent, czBuffer, 10 );
		WriteString( CString(czBuffer) );
		WriteString( TEXT("\">\r\n") );
	}
	WriteString( TEXT("                                    ")+cContent+TEXT("\r\n") );
    WriteString( TEXT("                                </TD>\r\n") );

	if( objId )
		_itot( objId->GetNo(), czBuffer, 10 );

	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COMMNOS_USE) )
	{
		WriteString( TEXT("                                <TD VALIGN=\"top\" ALIGN=\"right\">\r\n") );
		if( objId )
		{
			if( objId->GetNo() )
				WriteString( TEXT("                                    &nbsp;&nbsp;&nbsp;")+CString(czBuffer)+TEXT("\r\n") );
			else
				WriteString( TEXT("                                    &nbsp;&nbsp;&nbsp;-\r\n") );
		}
		else
		{
			WriteString( TEXT("                                    &nbsp;\r\n") );
		}
		WriteString( TEXT("                                </TD>\r\n") );
	}
    WriteString( TEXT("                            </TR>\r\n") );
}

void CHtmlDoc::SignOuts(PUBLI_BODYCOLUMNS columns[], CSignOutList* pSignOuts)
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
			WriteString( TEXT("        <P><EM>\r\n") );
			WriteString( TEXT("            ")+AssembleStr( TEXT("FootSignOut"), TEXT("<BR>"), &((CSettingsPublication*)m_pDocument->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+TEXT("\r\n") );
			WriteString( TEXT("        </EM></P>\r\n") );

			StartCompetitorsTable( so_columns );

			DWORD nState = 0;
			CSignOut objSignOut;
			
			// This is a dirty trick to prevent wrong behaviour of the befriended text output class
			CTextDoc* ptextdoc = m_ptextdoc;
			m_ptextdoc = NULL;

			while( pSignOuts->IterateSorted( nState, objSignOut ) )
				Competitor( so_columns, objSignOut.m_staNo, NULL, &objSignOut );

			// End the dirty trick
			m_ptextdoc = ptextdoc;

			WriteString( TEXT("        </TABLE>\r\n") );
			WriteString( TEXT("\r\n") );
			m_competitorsStarted = false;
		}
}

void CHtmlDoc::CrossOut( int nCompetitors[10], int nCrossedOut[10], CTeam* pTeam )
{
	if( !m_openSuccess )
		return;

	// If this is the first line, the flag m_competitorsStarted will be
	// false and the table header will printed
	if( !m_competitorsStarted )
	{
		Label(PP_MAINCONTENT);
		WriteString( TEXT("        <TABLE WIDTH=\"100%\" CELLSPACING=\"0\" CELLPADDING=\"0\" BORDER=\"1\">\r\n") );
		WriteString( TEXT("\r\n") );
		m_competitorsStarted = true;
	};

	for( int nMax=9; (nMax>0) && !nCompetitors[nMax]; nMax-- );
		 
	WriteString( TEXT("<TR ALIGN=\"center\" VALIGN=\"middle\">\r\n") );
	// Check whether team names are actually required in this configuration
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES) )
	{
		if( pTeam )
		{
			WriteString( TEXT("  <TD>\r\n    ") + pTeam->m_code + TEXT("\r\n  </TD>\r\n") );
			CString cTeamName = pTeam->m_name;
			if( cTeamName.GetLength()>21 )
				cTeamName = cTeamName.Left(19)+TEXT("...");

			WriteString( TEXT("  <TD NOWRAP>\r\n    ") + cTeamName + TEXT("\r\n  </TD>\r\n") );
		}
		else
		{
			WriteString( TEXT("  <TD>-</TD>\r\n") );
			WriteString( TEXT("  <TD NOWRAP>-</TD>\r\n") );
		}
	}

	for( int i=0; i<=nMax; i++ )
		if( nCompetitors[i] )
		{
			CCompetitor comp;
			TCHAR czBuffer[10];
			_itot( nCompetitors[i], czBuffer, 10 );
			if( !nCrossedOut[i] )
			{
				if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_CROSSOUTLISTS_PRINTCOMPETITORNAMES) )
				{
					comp = m_pDocument->CompetitorsGet(nCompetitors[i]);
					if( comp.m_competitor.GetLength()>14 )
						comp.m_competitor = comp.m_competitor.Left(12)+TEXT("...");
					WriteString( TEXT("  <TD>\r\n    <STRONG>")+CString(czBuffer)+TEXT("</STRONG>\r\n    <BR><DIV CLASS=\"small\">")+comp.m_competitor+TEXT("</DIV>\r\n  </TD>\r\n") );
				}
				else
				{
					WriteString( TEXT("  <TD>\r\n    <STRONG>")+CString(czBuffer)+TEXT("</STRONG>\r\n  </TD>\r\n") );
				}
			}
			else
				WriteString( TEXT("  <TD CLASS=\"tdblack\">\r\n    <FONT COLOR=\"gray\">\r\n      <S>(")+CString(czBuffer)+TEXT(")</S>\r\n    </FONT>\r\n  </TD>\r\n") );
		}
		else
			WriteString( TEXT("  <TD></TD>\r\n") );
	WriteString( TEXT("</TR>\r\n") );
	WriteString( TEXT("\r\n") );
}

CString CHtmlDoc::GetStylePart(const CStageRaceDoc *pDoc)
{
	CString cStyleSheet	= ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_styleSheet;
	cStyleSheet.TrimLeft();
	cStyleSheet.TrimRight();

	CString cStyle;

	// Write the style information
	if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_STYLE_EXTERNAL ) )
		cStyle = TEXT("        <LINK REL=\"stylesheet\" HREF=\"")+cStyleSheet+TEXT("\" TYPE=\"text/css\">\r\n");
	else
	{
		// Note that the document colors are retrieved from the user preferences
		cStyle = TEXT("        <STYLE TYPE=\"text/css\">\r\n");
		cStyle+= TEXT("            a:link     { text-decoration:      none }\r\n");
		cStyle+= TEXT("            a:visited  { text-decoration:      none }\r\n");
		cStyle+= TEXT("            a:active   { text-decoration: underline }\r\n");
		cStyle+= TEXT("            a:hover    { text-decoration: underline }\r\n");

		if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_FONTSIZE_PROC ) )
		{
			cStyle+= TEXT("            h1         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(275,pDoc)+TEXT("%; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT(" }\r\n");
			cStyle+= TEXT("            h2         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(200,pDoc)+TEXT("%; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT(" }\r\n");
			cStyle+= TEXT("            h6         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize( 30,pDoc)+TEXT("%; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; font-weight: bold; margin: 0 }\r\n");
			cStyle+= TEXT("            tt         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize( 75,pDoc)+TEXT("%; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_descriptColor+TEXT(" }\r\n");

			if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_FONT_TIMES ) )
			{
				cStyle+= TEXT("            em         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
				cStyle+= TEXT("            blockquote { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal }\r\n");
				cStyle+= TEXT("            th         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; text-align: left }\r\n");
				cStyle+= TEXT("            td         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; border-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
			}
			else
			{
				cStyle+= TEXT("            em         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
				cStyle+= TEXT("            blockquote { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal }\r\n");
				cStyle+= TEXT("            th         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; text-align: left }\r\n");
				cStyle+= TEXT("            td         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(75,pDoc)+TEXT("%; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; border-color: "+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+" }\r\n");
			}
			cStyle+= TEXT("            strong     { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(220,pDoc)+TEXT("%; color: ") +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: italic }\r\n"); // cross out font
			cStyle+= TEXT("            .small     { font-size: ")+CalculateFontSize(65,pDoc)+TEXT("% }\r\n");
			cStyle+= TEXT("            .prop      { font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
			cStyle+= TEXT("            .section   { font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
			cStyle+= TEXT("            .communique{ font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
			cStyle+= TEXT("            .signature { font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
		}
		else
		{
			cStyle+= TEXT("            h1         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(25,pDoc)+TEXT("pt; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT(" }\r\n");
			cStyle+= TEXT("            h2         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(18,pDoc)+TEXT("pt; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT(" }\r\n");
			cStyle+= TEXT("            h6         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize( 2,pDoc)+TEXT("pt; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; font-weight: bold; margin: 0 }\r\n");
			cStyle+= TEXT("            tt         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize( 7,pDoc)+TEXT("pt; color: ")  +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_descriptColor+TEXT(" }\r\n");

			if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_FONT_TIMES ) )
			{
				cStyle+= TEXT("            em         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
				cStyle+= TEXT("            blockquote { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal }\r\n");
				cStyle+= TEXT("            th         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; text-align: left }\r\n");
				cStyle+= TEXT("            td         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: \"Times New Roman\", Times, serif; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; border-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
			}
			else
			{
				cStyle+= TEXT("            em         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(8,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
				cStyle+= TEXT("            blockquote { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(8,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal }\r\n");
				cStyle+= TEXT("            th         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(8,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_titleColor   +TEXT("; font-style: normal; font-weight: bold; text-align: left }\r\n");
				cStyle+= TEXT("            td         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif; font-size: ")+CalculateFontSize(8,pDoc)+TEXT("pt; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: normal; border-color: "+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+" }\r\n");
			}
			cStyle+= TEXT("            strong     { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; font-family: Arial, Helvetica, sans-serif;    font-size: ")+CalculateFontSize(20,pDoc)+TEXT("pt; color: ") +((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor    +TEXT("; font-style: italic }\r\n"); // cross out font
			cStyle+= TEXT("            .small     { font-size: ")+CalculateFontSize(7,pDoc)+TEXT("pt }\r\n");
			cStyle+= TEXT("            .prop      { font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
			cStyle+= TEXT("            .section   { font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
			cStyle+= TEXT("            .communique{ font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
			cStyle+= TEXT("            .signature { font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
		}

		cStyle+= TEXT("            thead.docrecognition { ");
		if( pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_DOCRECOGNITION_REPEAT) )
		{
			cStyle+= TEXT("display: table-header-group; ");
		}
		if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_FONTSIZE_PROC ) )
		{
			cStyle+= TEXT("font-size: ")+CalculateFontSize(100,pDoc)+TEXT("% }\r\n");
		}
		else
		{
			cStyle+= TEXT("font-size: ")+CalculateFontSize(9,pDoc)+TEXT("pt }\r\n");
		}

		if( pDoc->m_allsettings.ValueGet(IDS_SETT_HTML_CUSTOMONEACHPAGE_TOP) )
		{
			cStyle+= TEXT("            thead.customhtml { display: table-header-group }\r\n");
		}
		if( pDoc->m_allsettings.ValueGet(IDS_SETT_HTML_CUSTOMONEACHPAGE_BOTTOM) )
		{
			cStyle+= TEXT("            tfoot      { display: table-footer-group }\r\n");
		}
		cStyle+= TEXT("            tr         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; border-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
		cStyle+= TEXT("            table      { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; border-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
		cStyle+= TEXT("            a          { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
		cStyle+= TEXT("            hr         { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_descriptColor+TEXT(" }\r\n");
		cStyle+= TEXT("            body       { background-color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bgColor+TEXT("; color: ")+((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_bodyColor+TEXT(" }\r\n");
		cStyle+= TEXT("            .bold      { font-weight: bold }\r\n");// bold for some types of team classification
		cStyle+= TEXT("            .tdblack   { background-color: Black }\r\n");// cross out black background

		if( ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->ValueGet( IDS_SETT_HTML_UCIFIXEDWIDTH ) )
		{		
			cStyle+= TEXT("            .ucicode   { font-family: Lucida Console, Courier New, courier }\r\n");
		}

		cStyle+= TEXT("        </STYLE>\r\n");
	}
	return cStyle;
}

void CHtmlDoc::Label(PUB_PARTS pp/* = PP_UNKNOWN*/, bool bBegin/* = true*/)
{
	if( !m_openSuccess )
		return;

	WriteString( TEXT("\r\n") );
	WriteString( TEXT("<!-- ") );

	switch( pp )
	{
		case PP_PROPERTIES:
			WriteString( TEXT("properties") );
			break;
		case PP_FIRSTTEN:
			WriteString( TEXT("first_ten") );
			break;
		case PP_FIRSTFIVE:
			WriteString( TEXT("first_five") );
			break;
		case PP_MAINCONTENT:
			WriteString( TEXT("main_content") );
			break;
		case PP_STATS:
			WriteString( TEXT("statistics_report") );
			break;
		case PP_SIGNATURE:
			WriteString( TEXT("signature") );
			break;
		case PP_TIMESTAMP:
			WriteString( TEXT("time_stamp") );
			break;
		case PP_UNKNOWN:
		default:
		{
			if( bBegin ) m_unknownlabelcounter += 1;

			TCHAR buffer[10];
			_itot( m_unknownlabelcounter, buffer, 10 );

			WriteString( TEXT("section_")+CString(buffer) );

			if( !bBegin ) m_unknownlabelcounter -= 1;
		}
	}

	if( bBegin )
		WriteString( TEXT(":begin") );
	else
		WriteString( TEXT(":end") );

	WriteString( TEXT(" -->\r\n") );
	WriteString( TEXT("\r\n") );
}

void CHtmlDoc::LabelEnd(PUB_PARTS pp/* = PP_UNKNOWN*/)
{
	Label(pp, false);
}

// Calculates the font size from a given size, adjusted
// by a percentage entered in the HTML settings
CString CHtmlDoc::CalculateFontSize(int nSize, const CStageRaceDoc *pDoc)
{
	// Calculate the real size
	nSize = (nSize * ((CSettingsHTML*)pDoc->m_allsettings.GetSettings(SETT_HTML))->m_fontsize)/100;
	// Format a string
	CString temp;
	temp.Format( TEXT("    %d"), nSize );
	// Return a fixed width (4 wide) string with the font size
	return temp.Right(4);
}

void CHtmlDoc::MakeDummy(CEventItem ei, unsigned short nId)
{
	// Note: this method has not CSV counterpart (no dummies for CSV exports)

	if( ei.GetDocument()->m_allsettings.ValueGet(IDS_SETT_HTML_DUMMY_PRINT) )
	{
		// Make the html document
		CHtmlDoc objHtml( ei );

		if( !objHtml.m_openSuccess )
			return;

		objHtml.WriteString( TEXT("        <BR>\r\n") );
		objHtml.WriteString( TEXT("        <BR>\r\n") );

		objHtml.WriteString( TEXT("        <TABLE WIDTH=\"100%\" CELLSPACING=\"0\" CELLPADDING=\"10\">\r\n") );
		objHtml.WriteString( TEXT("            <TR>\r\n") );
		objHtml.WriteString( TEXT("                <TD ALIGN=\"center\">\r\n") );
		objHtml.WriteString( TEXT("                    <P><EM>") );
		objHtml.WriteString( ei.StagesMakeIDString() );
		objHtml.WriteString( TEXT("</EM></P>\r\n") );
		objHtml.WriteString( TEXT("                    <P><EM>") );
		objHtml.WriteString( ei.ComposeTocTitle() );
		objHtml.WriteString( TEXT("</EM></P>\r\n") );
		objHtml.WriteString( TEXT("                    <P>") );
		objHtml.WriteString(
			AssembleStr(
				TEXT("DummyDoc"),
				TEXT("<BR>"),
				&((CSettingsPublication*)ei.GetDocument()->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages ) );
		objHtml.WriteString( TEXT("</P>\r\n") );
		objHtml.WriteString( TEXT("                </TD>\r\n") );
		objHtml.WriteString( TEXT("            </TR>\r\n") );
		objHtml.WriteString( TEXT("        </TABLE>\r\n") );
		objHtml.WriteString( TEXT("\r\n") );

		objHtml.WriteString( TEXT("        <BR>\r\n") );
		objHtml.WriteString( TEXT("        <BR>\r\n") );

		objHtml.Finish();
	}
}

void CHtmlDoc::StartColumns()
{
	if( !m_openSuccess )
		return;

	WriteString( TEXT("        <TABLE WIDTH=\"100%\" CELLSPACING=\"5\" CELLPADDING=\"0\" BORDER=\"0\">\r\n") );
	WriteString( TEXT("           <TR VALIGN=\"top\">\r\n") );
	WriteString( TEXT("              <TD>\r\n") );
}

void CHtmlDoc::NextColumn()
{
	if( !m_openSuccess )
		return;

	if( m_competitorsStarted )
	{
		m_competitorsStarted = false;
		WriteString( TEXT("        </TABLE>\r\n") );
		LabelEnd(PP_MAINCONTENT);
	}
	
	WriteString( TEXT("              </TD>\r\n") );
	if( m_pDocument->m_allsettings.ValueGet(IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_SEPARATE) )
	{
		WriteString( TEXT("              <TD style=\"border-right-style: solid; border-right-width: 1px\">&nbsp;</TD>\r\n") );
	}
	WriteString( TEXT("              <TD>\r\n") );
}

void CHtmlDoc::EndColumns()
{
	if( !m_openSuccess )
		return;

	if( m_competitorsStarted )
	{
		m_competitorsStarted = false;
		WriteString( TEXT("        </TABLE>\r\n") );
		LabelEnd(PP_MAINCONTENT);
	}

	WriteString( TEXT("              </TD>\r\n") );
	WriteString( TEXT("           </TR>\r\n") );
	WriteString( TEXT("        </TABLE>\r\n") );
}

void CHtmlDoc::WriteString(CString c)
{
	if( m_b2ByteFile )
      m_output.WriteString(c);
   else
	{
		// If we have decided to output a document
		// that is not throughout Unicode (but uses
		// escape characters such as &#x0000;) for
		// Unicode characters, we need to replace
		// non-ANSI characters by their escaped
		// version

		// "Escape" characters
		// Walk through the entire string
		int length = c.GetLength();
		for( int i=0; i<length; i++ )
			// See if not basic ANSI
			if( c.GetAt(i)>0x7f )
			{
				// Then convert
				TCHAR t = c.GetAt(i);
				c.Format( TEXT("%s&#x%02x%02x;%s"),
					c.Left(i),
					(t>>8)&0xff,	// most  significant 8-bits
					t&0xff,			// least significant 8-bits
					c.Mid(i+1) );
				length += 7;
			}
		
		// Now there shouldn't be any
		// true Unicode in there anymore
			// So convert it to single byte characters
			char* pconverted;
			int need;

			need = WideCharToMultiByte( CP_ACP, 0, c, -1, NULL, 0, NULL, NULL );
			pconverted = new char[need];
			if( pconverted )
			{
				WideCharToMultiByte( CP_ACP, 0, c, -1, pconverted, need, NULL, NULL );
				// Actually print it 
				m_output.Write( pconverted, need-1 );
			}
         delete pconverted;
	}
}
