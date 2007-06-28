// EventItem.h: interface for the CEventItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTITEM_H__0D0FBF96_F35A_42AE_869F_391C4F97B008__INCLUDED_)
#define AFX_EVENTITEM_H__0D0FBF96_F35A_42AE_869F_391C4F97B008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum STAGETYPES
{
	ST_NORMAL,
	ST_TT_GROSS,
	ST_TT_NET
};

enum TREEICONS
{
	TIC_UNKNOWN = -1,
	TIC_ROOT = 0,
	TIC_FULLSTAGE,
	TIC_HALFSTAGE,
	TIC_TIMETRIAL,
	TIC_CLIMB,
	TIC_SPRINT,
	TIC_COMMUNIQUE,
	TIC_SIGNOUTS,
	TIC_COMPETITORS,
	TIC_TEAMS,
	TIC_TIMETRIALORDER,
	TIC_CROSSOUTLIST,
	TIC_CLASSGENERAL,
	TIC_CLASSTEAMS,
	TIC_CLASSMASK,
	TIC_LISTCOMPETITORS,
	TIC_POINTS,
	TIC_SIGNINLIST,
	TIC_MOSTAGGRESSIVE,
	TIC_TTARRIVALLIST = TIC_TIMETRIAL
	// types added here at the end will count
	// further from TIC_TIMETRIAL!!!
};

enum TREEITEMS	
{
	TI_UNKNOWN			=  0,
	TI_FULLSTAGE,
	TI_HALFSTAGE,
	TI_ROOT				= -1,	//   document title
	TI_SETTINGS			= -2,
	TI_COMPETITORS		= -3,	//   competitors
	TI_TEAMS			= -4,	//   teams
	TI_COMMUNIQUE		= -5,	//   communique
	TI_SIGNOUTS			= -6,	//   signouts
	TI_TIMETRIALORDER	= -7,	//   time trial order
	TI_SPRINT			= -8,	//   sprints
	TI_CLIMB			= -9,	//   climbs
	TI_POINTS			= -10,
	TI_CROSSOUTLIST		= -11,	//   cross out list
	TI_CLASSGENERAL		= -12,	//   general classification
	TI_CLASSMASK1		= -13,	//   mask 1 classification
	TI_CLASSMASK2		= -14,	//   mask 2 classification
	TI_CLASSMASK3		= -15,	//   mask 3 classification
	TI_CLASSMASK4       = -24,
	TI_CLASSMASK5       = -25,
	TI_CLASSMASK6       = -26,
	TI_CLASSMASK7       = -27,
	TI_CLASSMASK8       = -28,
	TI_CLASSMASK9       = -29,
	TI_CLASSMASK10      = -30,
	TI_CLASSTEAMS		= -16,	//   teams classification
	TI_LISTCOMPETITORS1	= -17,
	TI_LISTCOMPETITORS2	= -18,
	TI_SPARECOMPETITORS = -19,
	TI_SIGNINLIST		= -20,
	TI_TOBEDETERMINED	= -21,
	TI_TTARRIVALLIST	= -22,
	TI_MOSTAGGRESSIVE	= -23,
	TI_CLASSSTANOSORTEDGENERAL = -31,
	TI_CLASSMASK1STAGE	= -32,
	TI_CLASSMASK2STAGE	= -33,
	TI_CLASSMASK3STAGE	= -34,
	TI_CLASSMASK4STAGE  = -35,
	TI_CLASSMASK5STAGE  = -36,
	TI_CLASSMASK6STAGE  = -37,
	TI_CLASSMASK7STAGE  = -38,
	TI_CLASSMASK8STAGE  = -39,
	TI_CLASSMASK9STAGE  = -40,
	TI_CLASSMASK10STAGE = -41,
	TI_CLASSMASK1GENERAL= -42,
	TI_CLASSMASK2GENERAL= -43,
	TI_CLASSMASK3GENERAL= -44,
	TI_CLASSMASK4GENERAL= -45,
	TI_CLASSMASK5GENERAL= -46,
	TI_CLASSMASK6GENERAL= -47,
	TI_CLASSMASK7GENERAL= -48,
	TI_CLASSMASK8GENERAL= -49,
	TI_CLASSMASK9GENERAL= -50,
	TI_CLASSMASK10GENERAL= -51,
};

#define PUBLI_BODYCOLUMNS_MAX 18
enum PUBLI_BODYCOLUMNS
{
	PBC_UNKNOWN = 0,
	PBC_TERMINATOR = 0,

	PBC_CATEGORY, //1 (old numbering)
	PBC_RIDER, //2
	PBC_COUNTRY, //3
	PBC_LICENSE, //4
	PBC_STANO, //5
	PBC_TEAMCODEWITHOUTCOLUMNHEADER, //6
	PBC_TEAMNAME, //7
	PBC_UCICODE, //8
	PBC_RANK, //9
	PBC_TIME, //10
	PBC_GAP, //11
	PBC_NEWGAP,
	PBC_BONUSES, //12
	PBC_TEAMCODE, //13
	PBC_POINTS, //14
	PBC_TEAMNAMEFROMRANK, //15
	PBC_TEAMCODEFROMRANKWITHOUTCOLUMNHEADER, //16
	PBC_TEAMCODEFROMRANK,
	PBC_INVOLVEDBUNCH,
	PBC_TIMEWITHTHOUSANDTH, //17
	PBC_STARTINGORDERTIME, //18
	PBC_STARTINGORDER, //19
	PBC_MASK1, //20
	PBC_MASK2, //21
	PBC_MASK3, //22
	PBC_MASK4,
	PBC_MASK5,
	PBC_MASK6,
	PBC_MASK7,
	PBC_MASK8,
	PBC_MASK9,
	PBC_MASK10,
	PBC_PENALTY, //23
	PBC_SIGNOUTREASON,
	PBC_SIGNINAREA,
	PBC_SPEED	
};

#define PUBLI_PROPERTIES_MAX 30
enum PUBLI_PROPERTIES
{
	PPR_UNKNOWN = 0,
	PPR_TERMINATOR = 0,
	
	PPR_LINEBREAK,
	
	PPR_CATEGORY, //1
	PPR_DATE, //2
	PPR_ORGANISER, //3
	PPR_LOCATION, //4
	PPR_TITLE_COMMUNIQUE, //5
	PPR_SINGLE_STAGE_CLASSIFICATION, //6
	PPR_GENERAL_CLASSIFICATION, //7
	PPR_STAGE_INDICATOR, //8
	PPR_DISTANCE, //9
	PPR_SPEED, //10
	PPR_MASK_1, //11
	PPR_MASK_2, //12
	PPR_MASK_3, //13
	PPR_MASK_4,
	PPR_MASK_5,
	PPR_MASK_6,
	PPR_MASK_7,
	PPR_MASK_8,
	PPR_MASK_9,
	PPR_MASK_10,
	PPR_SPRINTS, //14
	PPR_POINTS,
	PPR_CLIMBS, //15
	PPR_HALF_STAGE_INDICATOR, //16
	PPR_START_OF_EVENT_TIME, //17
	PPR_OVERALL_DISTANCE, //18
	PPR_OVERALL_SPEED, //19
	PPR_DATE_COMMUNIQUE, //21
	PPR_TIME_OF_WINNER,
	PPR_TIME_OF_WINNER_WITHTHOUSANDTH,
	PPR_MOSTAGGRESSIVE,
	PPR_TEAMSCOUNT,
	PPR_COMPETITORSCOUNT,

	PPR_UNOFFICIAL
};

class CEventItem  
{
	public:
		CString GetSponsor();
		CString GetSponsorSubTitle();
		static void EditPublication(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS);
		void EditPublication();
		void ToggleReadonly(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS);
		void ToggleReadonly();
		static bool IsPublicationReadonly(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		bool IsPublicationReadonly();
		CString StagesMakeIDString();
		static CString StagesMakeIDString(int nFS, int nHS, const CStageRaceDoc* pDoc);
		static CString StagesMakeIDString(int nFS, const CStageRaceDoc* pDoc);
		int GetOfficialDistanceCumulative();
		int GetOfficialDistanceCumulativeBefore();
		int GetRealDistanceCumulative();
		int GetDistance();
		static int GetPublicationPropertiesCount(PUBLI_PROPERTIES props[]);
		static int GetPublicationColumnsCount(PUBLI_BODYCOLUMNS columns[]);
		static int GetPublicationColumnsArrayCount(PUBLI_BODYCOLUMNS columns[]);
		static void GetPublicationProperties(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS, PUBLI_PROPERTIES props[], STAGETYPES stType = ST_NORMAL );
		void GetPublicationProperties( PUBLI_PROPERTIES props[] );
		static void RemovePublicationColumn( PUBLI_BODYCOLUMNS columns[], PUBLI_BODYCOLUMNS remove );
		static void GetPublicationColumns(TREEITEMS ti, const CStageRaceDoc* pDoc, PUBLI_BODYCOLUMNS columns[], STAGETYPES stType = ST_NORMAL);
		void GetPublicationColumns(PUBLI_BODYCOLUMNS columns[], STAGETYPES stType = ST_NORMAL);
		const CStageRaceDoc* GetDocument();
		void SetDoc(const CStageRaceDoc* pDoc);
		static bool IsPublicationAvailable(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static bool IsPublicable(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static bool IsPublicableCSV(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeTocTitle(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeFileTitle(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeFileNameHTML(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeFileNamePathHTML(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeFileNameCSV(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		static CString ComposeFileNamePathCSV(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS);
		bool IsPublicationAvailable();
		bool IsPublicable();
		bool IsPublicableCSV();
		CEventItem( const CEventItem& ei );
		CString ComposeTocTitle();
		CString ComposeFileTitle();
		CString ComposeFileNameHTML();
		CString ComposeFileNamePathHTML();
		CString ComposeFileNameCSV();
		CString ComposeFileNamePathCSV();
		TREEITEMS	m_tiConcerning;
		int			m_nHalfStage;
		int			m_nFullStage;

		CEventItem();
		CEventItem& operator=( const CEventItem& e );
		bool operator==( const CEventItem& e );
		void Reset();
		CEventItem(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS );
		static TREEICONS IconFromItem(TREEITEMS pti);
		TREEICONS IconFromItem() const;
	private:
		const CStageRaceDoc* m_pDoc;
		static BOOL m_bIndexMsgSuppress;
protected:
	CString RemoveIllegalChars(CString);
	int GetCumulativeDistance( bool bBefore = false, bool bOfficial = true );
};

#endif // !defined(AFX_EVENTITEM_H__0D0FBF96_F35A_42AE_869F_391C4F97B008__INCLUDED_)
