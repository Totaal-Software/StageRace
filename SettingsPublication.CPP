// SettingsPublication.cpp: implementation of the CSettingsPublication class.
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

CSettingsPublication::CSettingsPublication()
{
	ValueAdd( IDS_SETT_PUBL_CSV,
				CSettings::CSetting::GROUP, false, 0, 22 );
	ValueAdd( IDS_SETT_PUBL_CSV_GENERATE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_CSV );
	ValueAdd( IDS_SETT_PUBL_CSV_COPYTO,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_CSV );

	ValueAdd( IDS_SETT_PUBL_COMMNOS,
				CSettings::CSetting::GROUP, false, 0, 18 );
	ValueAdd( IDS_SETT_PUBL_COMMNOS_USE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COMMNOS );

	ValueAdd( IDS_SETT_PUBL_HEADER,
				CSettings::CSetting::GROUP, false, 0, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_DOCRECOGNITION_USE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER );
	ValueAdd( IDS_SETT_PUBL_HEADER_DOCRECOGNITION_REPEAT,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER );
	ValueAdd( IDS_SETT_PUBL_HEADER_TITLE,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER );
	ValueAdd( IDS_SETT_PUBL_HEADER_TITLE_DONTSHOW,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_TITLE );
	ValueAdd( IDS_SETT_PUBL_HEADER_TITLEALIGN_DEFAULT,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_TITLE );
	ValueAdd( IDS_SETT_PUBL_HEADER_TITLEALIGN_CENTER,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_TITLE );
	ValueAdd( IDS_SETT_PUBL_HEADER_TITLEALIGN_RIGHT,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_HEADER_TITLE );

	ValueAdd( IDS_SETT_PUBL_HEADER_LOGOPOSITION,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER, 14 );
	ValueAdd( IDS_SETT_PUBL_HEADER_LOGOPOSITION_LEFT,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_LOGOPOSITION );
	ValueAdd( IDS_SETT_PUBL_HEADER_LOGOPOSITION_CENTER,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_LOGOPOSITION );
	ValueAdd( IDS_SETT_PUBL_HEADER_LOGOPOSITION_RIGHT,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_HEADER_LOGOPOSITION );

	ValueAdd( IDS_SETT_PUBL_HEADER_SPONSOR,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER );
	ValueAdd( IDS_SETT_PUBL_HEADER_SPONSOR_DONTUSE,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_SPONSOR );
	ValueAdd( IDS_SETT_PUBL_HEADER_SPONSOR_ASSUBTITLE,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_SPONSOR );
	ValueAdd( IDS_SETT_PUBL_HEADER_SPONSOR_ADDTOSUBTITLE,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_HEADER_SPONSOR );

	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_DIRECTION,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_DIRECTION_HORIZONTAL,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_DIRECTION );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_DIRECTION_VERTICAL,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_DIRECTION );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_ORGANISER,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS );
	
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_FULLSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_HALFSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_SPEED,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_DISTANCE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_BESTTIME,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_STAGE,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_STAGE_OPENINGHOUR,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_STAGE );

	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_FULLSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_TTORDER );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_HALFSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_TTORDER );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_TTORDER );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_DISTANCE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_TTORDER );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_OPENINGHOUR,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_TTORDER );

	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_FULLSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_HALFSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_DISTANCE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_OPENINGHOUR,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT );

	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_FULLSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_SIGNIN );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_HALFSTAGE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_SIGNIN );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_SIGNIN );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_DISTANCE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_SIGNIN );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_OPENINGHOUR,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_SIGNIN );

	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_HEADER_PROPS, 15 );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_ORGANISER,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_MAINLOCATION,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_DATES,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_TEAMCOUNT,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_COMPCOUNT,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS );

    ValueAdd( IDS_SETT_PUBL_COLS,
				CSettings::CSetting::GROUP, true, 0, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL,
				CSettings::CSetting::GROUP, true, IDS_SETT_PUBL_COLS, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_RANK,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STANO,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_UCICODE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_LICENSE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_RIDER,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMNAME,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODEWITHOUTCOLUMNTITLE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_COUNTRY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL );

    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS_INDIVIDUAL, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_TIME,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_GAP,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_NEWGAP,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_BONUSES,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_PENALTY,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE );
	ValueAdd( IDS_SETT_PUBL_TT,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE, 16 );
	ValueAdd( IDS_SETT_PUBL_TT_SHOWNORMAL,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_TT );
	ValueAdd( IDS_SETT_PUBL_TT_SHOWACCURATEWITHDRAWS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_TT );
	ValueAdd( IDS_SETT_PUBL_TT_SHOWACCURATE,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_TT );
	ValueAdd( IDS_SETT_PUBL_TT_SPEED,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_TT );

    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS_INDIVIDUAL, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_TIME,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_GAP,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL );
    ValueAdd( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_NEWGAP,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL );

    ValueAdd( IDS_SETT_PUBL_COLS_TEAM,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_RANK,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_TEAMNAME,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_TEAMCODEWITHOUTCOLUMNTITLE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_TEAMCODE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_INLINE,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASROWS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASFULLROWS,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_STANO,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_TIME,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_GAP,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_TEAM );
    ValueAdd( IDS_SETT_PUBL_COLS_TEAM_NEWGAP,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_TEAM );
    
	ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_STANO,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK4,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK5,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK6,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK7,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK8,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK9,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK10,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_RIDER,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMNAME,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMCODEWITHOUTCOLUMNTITLE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMCODE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_UCICODE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_LICENSE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_COUNTRY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP1_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP1 );
    
	ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS, 16 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_STANO,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK4,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK5,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK6,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK7,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK8,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK9,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK10,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_RIDER,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_UCICODE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_LICENSE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COUNTRY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_CATEGORY,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );

	ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_COLS_LISTCOMP2 );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_1,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_2,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_3,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_4,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_5,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_6,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );
    ValueAdd( IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS_SEPARATE,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_COLS_LISTCOMP2_COLUMNS );

	ValueAdd( IDS_SETT_PUBL_FOOTER,
				CSettings::CSetting::GROUP, false, 0, 17 );

	ValueAdd( IDS_SETT_PUBL_FOOTER_CUTOFFS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER );
	ValueAdd( IDS_SETT_PUBL_FOOTER_DROPOUTS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER );
	ValueAdd( IDS_SETT_PUBL_FOOTER_SIGNOUTS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER );
	ValueAdd( IDS_SETT_PUBL_FOOTER_STATS,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_FOOTER );
	ValueAdd( IDS_SETT_PUBL_FOOTER_STATS_OTHERS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER_STATS );
	ValueAdd( IDS_SETT_PUBL_FOOTER_STATS_CUTOFFS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER_STATS );
	ValueAdd( IDS_SETT_PUBL_FOOTER_STATS_DROPOUTS,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER_STATS );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_FOOTER );

	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_OWN,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_PLAIN,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASWEB,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASWEBWITHHTTP,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL_ASEMAIL,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_URL );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_FOOTER_UNDERSIGN );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP_TIMEZONE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP );
	ValueAdd( IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP_SECONDS,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_FOOTER_UNDERSIGN_TIMESTAMP );
	ValueAdd( IDS_SETT_PUBL_FOOTER_ADVERTISEMENT,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_FOOTER );
	ValueAdd( IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_FOOTER_ADVERTISEMENT );
	ValueAdd( IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_SHORT,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_FOOTER_ADVERTISEMENT );

	ValueAdd( IDS_SETT_PUBL_TOC,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_PUBL_TOC_ORDER,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_TOC );
	ValueAdd( IDS_SETT_PUBL_TOC_ORDER_NORMAL,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_TOC_ORDER );
	ValueAdd( IDS_SETT_PUBL_TOC_ORDER_REVERSE,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_TOC_ORDER );
	ValueAdd( IDS_SETT_PUBL_TOC_COMPETITORS,
				CSettings::CSetting::GROUP, false, IDS_SETT_PUBL_TOC );
	ValueAdd( IDS_SETT_PUBL_TOC_COMPETITORS_TOP,
				CSettings::CSetting::MULTIOPTION, true, IDS_SETT_PUBL_TOC_COMPETITORS );
	ValueAdd( IDS_SETT_PUBL_TOC_COMPETITORS_BOTTOM,
				CSettings::CSetting::MULTIOPTION, false, IDS_SETT_PUBL_TOC_COMPETITORS );

	ValueAdd( IDS_SETT_PUBL_CROSSOUTLISTS,
				CSettings::CSetting::GROUP, false, 0, 2 );
	ValueAdd( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTTEAMNAMES,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_CROSSOUTLISTS );
	ValueAdd( IDS_SETT_PUBL_CROSSOUTLISTS_PRINTCOMPETITORNAMES,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_CROSSOUTLISTS );

	ValueAdd( IDS_SETT_PUBL_DISTANCES,
				CSettings::CSetting::GROUP, false, 0, 0 );
	ValueAdd( IDS_SETT_PUBL_DISTANCES_KM,
				CSettings::CSetting::SINGLEOPTION, true, IDS_SETT_PUBL_DISTANCES );
	ValueAdd( IDS_SETT_PUBL_DISTANCES_MILE,
				CSettings::CSetting::SINGLEOPTION, false, IDS_SETT_PUBL_DISTANCES );

	m_mask1icon = "#";
	m_mask2icon = "!";
	m_mask3icon = "*";
	m_sameGap = "...";
	m_modulusCrossOutTeamNames = 10;

	// Default document languages
	CMultiLanguage::LANGUAGE lang;
	strcpy( lang.ac, "EN" );
	m_requiredLanguages.Add( lang );
	strcpy( lang.ac, "FR" );
	m_requiredLanguages.Add( lang );
/*	strcpy( lang.ac, "ES" );
	m_requiredLanguages.Add( lang );
	strcpy( lang.ac, "DE" );
	m_requiredLanguages.Add( lang );
	strcpy( lang.ac, "NL" );
	m_requiredLanguages.Add( lang ); */
}

CSettingsPublication::CSettingsPublication(CSettingsPublication *pSettings)
{
	CSettingsPublication();
	*this = *pSettings;
}

CPageSettings* CSettingsPublication::GetPage()
{
	// Make the page
	CPageSettings*		pPage = new CPageSettingsPublication();
	// Make a copy of this settings
	CSettingsPublication*	pCopy = new CSettingsPublication();
	*pCopy = *this;
	// Connect the copy to the dialog
	pPage->m_pSettings = pCopy;
	return pPage;
}

CSettings& CSettingsPublication::operator=( const CSettings& s )
{
	CSettings::operator =( s );

	CSettingsPublication* s1 = (CSettingsPublication*)&s;
	m_companyName = s1->m_companyName;
	m_companyURL = s1->m_companyURL;
	m_signature = s1->m_signature;
	m_mask1icon = s1->m_mask1icon;
	m_mask2icon = s1->m_mask2icon;
	m_mask3icon = s1->m_mask3icon;
	m_sameGap = s1->m_sameGap;
	m_modulusCrossOutTeamNames = s1->m_modulusCrossOutTeamNames;

	m_requiredLanguages.RemoveAll();
	for( int i = 0 ; i < s1->m_requiredLanguages.GetSize() ; i++ )
	{
		this->m_requiredLanguages.Add( s1->m_requiredLanguages.GetAt(i) );
	}

	return *this;
}

void CSettingsPublication::Serialize(CArchive &ar)
{
	CSettings::Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_companyName << m_companyURL << m_signature << m_mask1icon << m_mask2icon << m_mask3icon << m_modulusCrossOutTeamNames;
		// Required languages
		ar << m_requiredLanguages.GetSize();

		CMultiLanguage::LANGUAGE lang;
		for( int i = 0 ; i < m_requiredLanguages.GetSize() ; i++ )
		{
			lang = m_requiredLanguages.GetAt(i);
			ar << lang.n;
		}
	}
	else
	{
		if( *(int*)(ar.m_pDocument) >= 3000 )
		{
			ar >> m_companyName >> m_companyURL >> m_signature >> m_mask1icon >> m_mask2icon >> m_mask3icon >> m_modulusCrossOutTeamNames;
			// Required languages
			int nCount;
			ar >> nCount;

			m_requiredLanguages.RemoveAll();
			CMultiLanguage::LANGUAGE lang;
			while( nCount-- )
			{
				ar >> lang.n;
				m_requiredLanguages.Add( lang );
			}
		}
		else
		{
			ar >> m_companyName >> m_companyURL >> m_signature >> m_mask1icon >> m_mask2icon >> m_mask3icon >> m_modulusCrossOutTeamNames;
			// Required languages
			int nCount;
			ar >> nCount;

			m_requiredLanguages.RemoveAll();
			CMultiLanguage::LANGUAGE lang;
			while( nCount-- )
			{
				ar >> lang.n;
				m_requiredLanguages.Add( lang );
			}
			
			// Footer
			ValueSet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE_OWN,
				ValueGet(IDS_SETT_PUBL_FOOTER_UNDERSIGN_SIGNATURE) );
			ValueSet(IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_LONG, true);
			ValueSet(IDS_SETT_PUBL_FOOTER_ADVERTISEMENT_SHORT, false);

			// Table of contents
			ValueSet(IDS_SETT_PUBL_TOC_COMPETITORS_TOP, false);
			ValueSet(IDS_SETT_PUBL_TOC_COMPETITORS_BOTTOM, true);

			// Time trial accuracy
			ValueSet( IDS_SETT_PUBL_TT_SHOWNORMAL, false );
			if( ValueGet(IDS_SETT_PUBL_TT_SHOWACCURATE) )
			{
				ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATEWITHDRAWS, true );
				ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATE, false );
			}
			else
			{
				ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATEWITHDRAWS, false );
				ValueSet( IDS_SETT_PUBL_TT_SHOWACCURATE, true );
			}
		}
	}
}
