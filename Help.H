// Help.h: interface for the CHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELP_H__0CFE4824_C96A_4C51_8E6B_E1D252CC4FA3__INCLUDED_)
#define AFX_HELP_H__0CFE4824_C96A_4C51_8E6B_E1D252CC4FA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHelp  
{
public:
	enum HELP_TOPIC
	{
		HLP_UNKNOWN,

		HLP_HLPABOUT,

		HLP_DLG_ABOUT,
		HLP_DLG_CREDITS,
		
		HLP_DLG_OPTIONS,
		HLP_DLG_MASKAPPLY,
// List pages
		HLP_DLG_LSTP_ARR,
		HLP_DLG_LSTP_CORR,
		HLP_DLG_LSTP_SO,
		HLP_DLG_LSTP_ARR_TT_GROSS,
		HLP_DLG_LSTP_ARR_TT_NET,
		HLP_DLG_LSTP_TTORDER,
// List pages helpers
		HLP_DLG_LSTP_ARR_REPORT,
		HLP_DLG_LSTP_TTORDER_INTERVAL,
		HLP_DLG_LSTP_TTORDER_ORDEROPTIONS,
// Import
		HLP_DLG_IMPORT_CHECK,
		HLP_DLG_IMPORT_PREVIEW,
// Item editors		
		HLP_DLG_LSTP_COMM,
		HLP_DLG_LSTP_COMP,
		HLP_DLG_LSTP_TEAM,
// Configuration dialogs
		HLP_DLG_CONF_STAGE,
		HLP_DLG_CONF_HALFSTAGE,
		HLP_DLG_CONF_BONUS,
		HLP_DLG_CONF_POINTS,
		HLP_DLG_CONF_SPRINT,
		HLP_DLG_CONF_CLIMB,
		HLP_DLG_CONF_MOSTAGGRESSIVE,

		HLP_DLG_PASSWORD,

// Settings dialogs
		HLP_DLG_SETT_ACCESS,
		HLP_DLG_SETT_GENERAL,
		HLP_DLG_SETT_HTML,
		HLP_DLG_SETT_PUBL,
		HLP_DLG_SETT_RANK,
		HLP_DLG_SETT_UPLOAD,

// Hardware key
		HLP_DLG_HARDWAREKEY
	};
	static void Topic( HELP_TOPIC topic );
	static void Tip();
	static void Search();
	static void Contents();
	static void Keyword( TCHAR* keyword );
protected:
	static bool HelpFile(CString *c);
	// Protected constructor so that we can only
	// this class for its static functions
	CHelp();
};

#endif // !defined(AFX_HELP_H__0CFE4824_C96A_4C51_8E6B_E1D252CC4FA3__INCLUDED_)
