// Help.cpp: implementation of the CHelp class.
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

CHelp::CHelp()
{

}

void CHelp::Contents()
{
	CString target;
	if( HelpFile( &target ) )
		HtmlHelp( NULL, target+">tripane", HH_DISPLAY_TOC, NULL );
}

void CHelp::Search()
{
	#ifdef _DEBUG
		Topic(HLP_UNKNOWN);
		Topic(HLP_HLPABOUT);
		Topic(HLP_DLG_ABOUT);
		Topic(HLP_DLG_CREDITS);
		Topic(HLP_DLG_OPTIONS); // not directly to "options" topic
		Topic(HLP_DLG_MASKAPPLY);
		Topic(HLP_DLG_LSTP_ARR); // not found
		Topic(HLP_DLG_LSTP_CORR); // not found
		Topic(HLP_DLG_LSTP_SO);
		Topic(HLP_DLG_LSTP_ARR_TT_GROSS); // not found
		Topic(HLP_DLG_LSTP_ARR_TT_NET); // not found
		Topic(HLP_DLG_LSTP_TTORDER); // not found
		Topic(HLP_DLG_LSTP_ARR_REPORT); // not found
		Topic(HLP_DLG_LSTP_TTORDER_INTERVAL); // not found
		Topic(HLP_DLG_LSTP_TTORDER_ORDEROPTIONS); // not found
		Topic(HLP_DLG_IMPORT_CHECK);
		Topic(HLP_DLG_IMPORT_PREVIEW);
		Topic(HLP_DLG_LSTP_COMM); // not directly to "dialog" topic
		Topic(HLP_DLG_LSTP_COMP);
		Topic(HLP_DLG_LSTP_TEAM);
		Topic(HLP_DLG_CONF_STAGE); // not directly to "stage" topic
		Topic(HLP_DLG_CONF_HALFSTAGE); // not directly to "half stage" topic
		Topic(HLP_DLG_CONF_BONUS); // not directly to "bonuses" topic
		Topic(HLP_DLG_CONF_POINTS); // not directly to "points" topic
		Topic(HLP_DLG_CONF_SPRINT); // not directly to "sprint" topic
		Topic(HLP_DLG_CONF_CLIMB);
		Topic(HLP_DLG_CONF_MOSTAGGRESSIVE);
		Topic(HLP_DLG_PASSWORD);
		Topic(HLP_DLG_SETT_ACCESS);
		Topic(HLP_DLG_SETT_GENERAL);
		Topic(HLP_DLG_SETT_HTML);
		Topic(HLP_DLG_SETT_PUBL);
		Topic(HLP_DLG_SETT_RANK);
		Topic(HLP_DLG_SETT_UPLOAD);
		Topic(HLP_DLG_HARDWAREKEY);
	#endif //_DEBUG

	CString target;
	if( HelpFile( &target ) )
	{
		HH_FTS_QUERY oQuery;
		oQuery.cbStruct			= sizeof( HH_FTS_QUERY );
		oQuery.fStemmedSearch	= FALSE;
		oQuery.fTitleOnly		= FALSE;
		oQuery.fUniCodeStrings	= FALSE;
		oQuery.iProximity		= HH_FTS_DEFAULT_PROXIMITY;
		oQuery.pszSearchQuery	= TEXT("");
		//buggy: oQuery.pszWindow		= TEXT("tripane");
		oQuery.fExecute			= TRUE;

		HtmlHelp( NULL, target, HH_DISPLAY_SEARCH, (DWORD)&oQuery );
	}
}

void CHelp::Tip()
{
	CTipDlg dlg;
	dlg.DoModal();
}

void CHelp::Topic(HELP_TOPIC topic)
{
	#ifdef _DEBUG
		TCHAR buffer[10];
		_itot( (int)topic, buffer, 10 );
		MessageBox(NULL, TEXT("Topic #")+CString(buffer), TEXT("Help"), MB_OK);
	#endif //_DEBUG
	switch( topic )
	{
		case HLP_HLPABOUT:
											Keyword( TEXT("help") ); break;
		case HLP_DLG_OPTIONS:
											Keyword( TEXT("options") ); break;
		case HLP_DLG_MASKAPPLY:
											Keyword( TEXT("apply a mask dialog") ); break;
		case HLP_DLG_LSTP_ARR:
											Keyword( TEXT("arrival tab sheet") ); break;
		case HLP_DLG_LSTP_CORR:
											Keyword( TEXT("corrections tab sheet") ); break;
		case HLP_DLG_LSTP_SO:
											Keyword( TEXT("sign outs dialog") ); break;
		case HLP_DLG_LSTP_ARR_TT_GROSS:
											Keyword( TEXT("time trials") ); break;
		case HLP_DLG_LSTP_ARR_TT_NET:
											Keyword( TEXT("time trials") ); break;
		case HLP_DLG_LSTP_TTORDER:
											Keyword( TEXT("time trial starting order dialog") ); break;
		case HLP_DLG_LSTP_ARR_REPORT:
											Keyword( TEXT("arrival tab sheet") ); break;
		case HLP_DLG_LSTP_TTORDER_INTERVAL:
											Keyword( TEXT("time trial starting order dialog") ); break;
		case HLP_DLG_LSTP_TTORDER_ORDEROPTIONS:
											Keyword( TEXT("time trial starting order dialog") ); break;
		case HLP_DLG_IMPORT_CHECK:
											Keyword( TEXT("confirm classification file import dialog") ); break;
		case HLP_DLG_IMPORT_PREVIEW:
											Keyword( TEXT("control import classification dialog") ); break;
		case HLP_DLG_LSTP_COMM:
											Keyword( TEXT("communiqués") ); break;
		case HLP_DLG_LSTP_COMP:
											Keyword( TEXT("competitor properties dialog") ); break;
		case HLP_DLG_LSTP_TEAM:
											Keyword( TEXT("team properties dialog") ); break;
		case HLP_DLG_CONF_STAGE:
											Keyword( TEXT("full stage") ); break;
		case HLP_DLG_CONF_HALFSTAGE:
											Keyword( TEXT("half stage") ); break;
		case HLP_DLG_CONF_BONUS:
											Keyword( TEXT("bonuses") ); break;
		case HLP_DLG_CONF_POINTS:
											Keyword( TEXT("points classifications") ); break;
		case HLP_DLG_CONF_SPRINT:
											Keyword( TEXT("sprint classifications") ); break;
		case HLP_DLG_CONF_CLIMB:
											Keyword( TEXT("climbing classifications") ); break;
		case HLP_DLG_CONF_MOSTAGGRESSIVE:
											Keyword( TEXT("most aggressive rider competition") ); break;
		case HLP_DLG_PASSWORD:
											Keyword( TEXT("access settings") ); break;
		case HLP_DLG_SETT_ACCESS:
											Keyword( TEXT("access settings") ); break;
		case HLP_DLG_SETT_GENERAL:
											Keyword( TEXT("general settings") ); break;
		case HLP_DLG_SETT_HTML:
											Keyword( TEXT("html settings") ); break;
		case HLP_DLG_SETT_PUBL:
											Keyword( TEXT("publication settings") ); break;
		case HLP_DLG_SETT_RANK:
											Keyword( TEXT("ranking settings") ); break;
		case HLP_DLG_SETT_UPLOAD:
											Keyword( TEXT("upload settings") ); break;
		case HLP_DLG_HARDWAREKEY:
											Keyword( TEXT("hardware key") ); break;
		case HLP_DLG_ABOUT:
		case HLP_DLG_CREDITS:
		case HLP_UNKNOWN:
		default:
			Contents();
	}
}

void CHelp::Keyword(TCHAR* keyword)
{
	CString target;
	if( HelpFile( &target ) )
	{
		HH_AKLINK link;
		memset( &link, 0, sizeof( HH_AKLINK ) );
		link.cbStruct		= sizeof( HH_AKLINK );
		link.fReserved		= FALSE;
		link.pszKeywords	= keyword;
		link.pszUrl			= NULL;
		//buggy: link.pszWindow		= TEXT("tripane");
		link.fIndexOnFail	= TRUE;

		HtmlHelp( NULL, target, HH_KEYWORD_LOOKUP, (DWORD)&link );
	}
}

bool CHelp::HelpFile(CString*c)
{
	CString cFile = GetModulePathName() + "Help\\";

/*	CRegKey reg;
	LONG er = reg.Open( HKEY_CURRENT_USER, "Software\\Totaal Software\\StageRace\\Options" );
	if( er == ERROR_SUCCESS )
	{
		switch( reg.GetDWord( TEXT("HelpLanguage"), -1 ) )
		{
			case 1:				
				cFile = cFile+"Dutch\\Dutch.chm";
			default:
				cFile = cFile+"English\\English.chm";
		}
	}
	else
*/		cFile = cFile+"English\\English.chm";

	CFileFind objCheckFile;
	if( objCheckFile.FindFile( cFile )==FALSE )
	{
		MessageBox( NULL, LoadStr( IDS_MBT_52 ), LoadStr( IDS_MBC_52 ), MB_OK|MB_ICONEXCLAMATION );
		return false;
	}
	else
	{
		*c = cFile;
		return true;
	}
}
