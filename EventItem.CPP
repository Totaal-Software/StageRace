// EventItem.cpp: implementation of the CEventItem class.
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

// Keep track of "do not display again" for
// the message box that alerts us of a TOC
// that is stored in a index.html being used
BOOL CEventItem::m_bIndexMsgSuppress = false;

CEventItem::CEventItem()
{
	m_pDoc = NULL;
	Reset();
}

CEventItem::CEventItem(const CEventItem &ei)
{
	*this = ei;
}

bool CEventItem::operator==( const CEventItem& e )
{
	return	(m_nFullStage	== e.m_nFullStage)
		&&	(m_nHalfStage	== e.m_nHalfStage)
		&&	(m_tiConcerning	== e.m_tiConcerning);
}

CEventItem& CEventItem::operator=( const CEventItem& e )
{
	m_nFullStage = e.m_nFullStage;
	m_nHalfStage = e.m_nHalfStage;
	m_tiConcerning = e.m_tiConcerning;
	m_pDoc = e.m_pDoc;

	return *this;
}

void CEventItem::Reset()
{
	m_tiConcerning = TI_UNKNOWN;
	m_nHalfStage = 0;
	m_nFullStage = 0;
}

CEventItem::CEventItem( const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS )
{
	m_pDoc = pDoc;
	m_tiConcerning = ti;
	m_nHalfStage = nHS;
	m_nFullStage = nFS;
}

TREEICONS CEventItem::IconFromItem(TREEITEMS pti)
{
	switch( pti )
	{
		case TI_FULLSTAGE:
			return TIC_FULLSTAGE;
		case TI_HALFSTAGE:
			return TIC_HALFSTAGE;
//			return TIC_TIMETRIAL;
		case TI_ROOT:
			return TIC_ROOT;
		case TI_COMPETITORS:
			return TIC_COMPETITORS;
		case TI_TEAMS:
			return TIC_TEAMS;
		case TI_COMMUNIQUE:
			return TIC_COMMUNIQUE;
		case TI_SIGNOUTS:
			return TIC_SIGNOUTS;
		case TI_TIMETRIALORDER:
			return TIC_TIMETRIALORDER;
		case TI_SPRINT:
			return TIC_SPRINT;
		case TI_CLIMB:
			return TIC_CLIMB;
		case TI_MOSTAGGRESSIVE:
			return TIC_MOSTAGGRESSIVE;
		case TI_POINTS:
			return TIC_POINTS;
		case TI_CROSSOUTLIST:
			return TIC_CROSSOUTLIST;
		case TI_SIGNINLIST:
			return TIC_SIGNINLIST;
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
			return TIC_CLASSGENERAL;
		case TI_TTARRIVALLIST:
			return TIC_TTARRIVALLIST;
		case TI_CLASSMASK1:
		case TI_CLASSMASK2:
		case TI_CLASSMASK3:
		case TI_CLASSMASK4:
		case TI_CLASSMASK5:
		case TI_CLASSMASK6:
		case TI_CLASSMASK7:
		case TI_CLASSMASK8:
		case TI_CLASSMASK9:
		case TI_CLASSMASK10:
			return TIC_CLASSMASK;
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
			return TIC_HALFSTAGE;
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
			return TIC_CLASSGENERAL;
		case TI_CLASSTEAMS:
			return TIC_CLASSTEAMS;
		case TI_LISTCOMPETITORS1:
		case TI_LISTCOMPETITORS2:
			return TIC_LISTCOMPETITORS;
//		case TI_SPARECOMPETITORS:
		case TI_UNKNOWN:
		default:
			return TIC_UNKNOWN;
	}
}

TREEICONS CEventItem::IconFromItem() const
{
	return IconFromItem(m_tiConcerning);
}

CString CEventItem::ComposeTocTitle()
{
	CString cstage;
	if( ((CStageRaceDoc*)m_pDoc)->StagesGet( m_nFullStage, m_nHalfStage )->m_stageType==ST_NORMAL )
		cstage = AssembleStr( TEXT("TocStage"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
	else
		cstage = AssembleStr( TEXT("TocTimeTrial"), TEXT(", "), &((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
	CString cgeneral;
	cgeneral = AssembleStr( TEXT("TocGeneral"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );

	switch( m_tiConcerning )
	{
		case TI_HALFSTAGE:
			return cstage;
		case TI_ROOT:
			return AssembleStr( TEXT("TocToc"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_COMMUNIQUE:
			// Half stage communiqué
			if( m_nHalfStage )
				return "Communiqué \""+((CStageRaceDoc*)m_pDoc)->StagesGet(m_nFullStage, m_nHalfStage)->m_communique.m_title+"\"";
			else
				// Full stage communiqué
				if( m_nFullStage )
					return "Communiqué \""+((CStageRaceDoc*)m_pDoc)->StagesGet(m_nFullStage)->m_communique.m_title+"\"";
				else
				// Event communiqué
					return AssembleStr( TEXT("TocCommGenrl"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages )+" \""+m_pDoc->m_communique.m_title+"\"";
		case TI_TIMETRIALORDER:
			return AssembleStr( TEXT("TocTTOrder"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_SPRINT:
			return AssembleStr( TEXT("TocSprint"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_POINTS:
			return AssembleStr( TEXT("TocPoints"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_CLIMB:
			return AssembleStr( TEXT("TocClimb"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_MOSTAGGRESSIVE:
			return AssembleStr( TEXT("TocAggressv"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_CROSSOUTLIST:
			return AssembleStr( TEXT("TocCrossOut"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_CLASSSTANOSORTEDGENERAL:
			return AssembleStr( TEXT("TocStaNoSort"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_SIGNINLIST:
			return AssembleStr( TEXT("TocSignIn"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_CLASSGENERAL:
			return cgeneral;
		case TI_TTARRIVALLIST:
			return AssembleStr( TEXT("TocTTArrival"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_CLASSMASK1STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 1: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1;
		case TI_CLASSMASK2STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 2: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2;
		case TI_CLASSMASK3STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 3: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3;
		case TI_CLASSMASK4STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 4: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4;
		case TI_CLASSMASK5STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 5: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5;
		case TI_CLASSMASK6STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 6: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6;
		case TI_CLASSMASK7STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 7: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7;
		case TI_CLASSMASK8STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 8: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8;
		case TI_CLASSMASK9STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 9: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9;
		case TI_CLASSMASK10STAGE:
			cstage += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cstage += TEXT("Mask 10: ");
			}
			return cstage + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10;
		case TI_CLASSMASK1GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 1: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1;
		case TI_CLASSMASK2GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 2: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2;
		case TI_CLASSMASK3GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 3: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3;
		case TI_CLASSMASK4GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 4: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4;
		case TI_CLASSMASK5GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 5: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5;
		case TI_CLASSMASK6GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 6: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6;
		case TI_CLASSMASK7GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 7: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7;
		case TI_CLASSMASK8GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 8: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8;
		case TI_CLASSMASK9GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 9: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9;
		case TI_CLASSMASK10GENERAL:
			cgeneral += TEXT("<BR>");
			if( !m_pDoc->m_allsettings.ValueGet(IDS_SETT_GNRL_MASKS_SUPPRESSMASKNO) )
			{
				cgeneral += TEXT("Mask 10: ");
			}
			return cgeneral + ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10;
		case TI_CLASSTEAMS:
			return AssembleStr( TEXT("TocTeams"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_LISTCOMPETITORS1:
			return AssembleStr( TEXT("TocCompList1"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
		case TI_LISTCOMPETITORS2:
			return AssembleStr( TEXT("TocCompList2"), TEXT(", "),&((CSettingsPublication*)m_pDoc->m_allsettings.GetSettings(SETT_PUBLICATION))->m_requiredLanguages );
	}
	return "";
}

CString CEventItem::ComposeFileTitle()
{
	CString cHSID = StagesMakeIDString();
	CString cFSID = StagesMakeIDString();
	switch( m_tiConcerning )
	{
		case TI_HALFSTAGE:
			return "Stage "+cHSID+", Etape "+cHSID;
		case TI_ROOT:
			return "Table of Contents, Table des matières";
		case TI_COMMUNIQUE:
			// Half stage communiqué
			if( m_nHalfStage )
				return "Communiqué half stage, demi-étape "+cHSID;
			else
				// Full stage communiqué
				if( m_nFullStage )
					return "Communiqué "+cFSID;
				else
				// Event communiqué
					return "Communiqué general";
		case TI_TIMETRIALORDER:
			return "Time trial order "+cHSID+", Ordre de départ "+cHSID;
		case TI_SPRINT:
			return "Sprints "+cHSID;
		case TI_POINTS:
			return "Points "+cHSID;
		case TI_CLIMB:
			return "Climbing "+cHSID+", Meilleur grimpeur "+cHSID;
		case TI_MOSTAGGRESSIVE:
			return "Most aggressive "+cHSID+", Combativité "+cHSID;
		case TI_CROSSOUTLIST:
			return "Cross out list "+cHSID+", Liste de barrer "+cHSID;
		case TI_SIGNINLIST:
			return "Sign in list "+cHSID+", Liste à inscrire "+cHSID;
		case TI_CLASSSTANOSORTEDGENERAL:
			return "General sorted "+cHSID+", General trié "+cHSID;
		case TI_CLASSGENERAL:
			return "General "+cHSID;
		case TI_TTARRIVALLIST:
			return "Arrival "+cHSID+", Arrivée "+cHSID;
		case TI_CLASSMASK1STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1.Left(25) + " (M1) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK2STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2.Left(25) + " (M2) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK3STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3.Left(25) + " (M3) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK4STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4.Left(25) + " (M4) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK5STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5.Left(25) + " (M5) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK6STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6.Left(25) + " (M6) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK7STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7.Left(25) + " (M7) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK8STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8.Left(25) + " (M8) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK9STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9.Left(25) + " (M9) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK10STAGE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10.Left(25) + " (M10) - Stage "+cHSID+", Etape "+cHSID;
		case TI_CLASSMASK1GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask1.Left(25) + " (M1) - General "+cHSID;
		case TI_CLASSMASK2GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask2.Left(25) + " (M2) - General "+cHSID;
		case TI_CLASSMASK3GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask3.Left(25) + " (M3) - General "+cHSID;
		case TI_CLASSMASK4GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask4.Left(25) + " (M4) - General "+cHSID;
		case TI_CLASSMASK5GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask5.Left(25) + " (M5) - General "+cHSID;
		case TI_CLASSMASK6GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask6.Left(25) + " (M6) - General "+cHSID;
		case TI_CLASSMASK7GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask7.Left(25) + " (M7) - General "+cHSID;
		case TI_CLASSMASK8GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask8.Left(25) + " (M8) - General "+cHSID;
		case TI_CLASSMASK9GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask9.Left(25) + " (M9) - General "+cHSID;
		case TI_CLASSMASK10GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_mask10.Left(25) + " (M10) - General "+cHSID;
		case TI_CLASSTEAMS:
			return "Teams "+cHSID+", Equipes "+cHSID;
		case TI_LISTCOMPETITORS1:
			return "Competitors, Coureurs";
		case TI_LISTCOMPETITORS2:
			return "Teams, Equipes";
	}
	return "";
}

CString CEventItem::ComposeFileName()
{
	if( m_tiConcerning==TI_ROOT
		&& (m_pDoc->m_allsettings.ValueGet(IDS_SETT_HTML_TOC_INDEXHTML)) )
	{
		if( !m_pDoc->m_IndexTocFlag )
		{
			if( !m_bIndexMsgSuppress )
			{
				CMsgBoxIndexHtml dlgMsg(m_pDoc->GetTitle());
				dlgMsg.DoModal();
				if( dlgMsg.m_futureSuppress )
					m_bIndexMsgSuppress = true;
			}
			((CStageRaceDoc*)m_pDoc)->m_IndexTocFlag=true;
		}
		return "index.html";
	}
	else
		return RemoveIllegalChars(m_pDoc->FilesTitle()+" - "+m_pDoc->m_allsettings.ProfilesGetCurrentFileName()+ComposeFileTitle()+".html");
}

CString CEventItem::ComposeFileNamePath()
{
	return m_pDoc->FilesPath()+ComposeFileName();
}

CString CEventItem::ComposeTocTitle(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.ComposeTocTitle();
}

CString CEventItem::ComposeFileTitle(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.ComposeFileTitle();
}

CString CEventItem::ComposeFileName(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS)
{
	if( ti == TI_ROOT )
		return "index.html";
	else
	{
		CEventItem ei( pDoc, ti, nFS, nHS );
		return ei.ComposeFileName();
	}
}

CString CEventItem::ComposeFileNamePath(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.ComposeFileNamePath();
}

bool CEventItem::IsPublicationAvailable()
{
	CFileFind objCheckFile;
	// If the file exists...
	return objCheckFile.FindFile( ComposeFileNamePath() )==TRUE;
}

bool CEventItem::IsPublicationAvailable(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.IsPublicationAvailable();
}

bool CEventItem::IsPublicable()
{
	return ComposeFileTitle().GetLength()>0;
}

bool CEventItem::IsPublicable(const CStageRaceDoc* pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.IsPublicable();
}

void CEventItem::SetDoc(const CStageRaceDoc *pDoc)
{
	m_pDoc = pDoc;
}

const CStageRaceDoc* CEventItem::GetDocument()
{
	return m_pDoc;
}

void CEventItem::GetPublicationColumns(PUBLI_BODYCOLUMNS columns[], STAGETYPES stType /*= ST_NORMAL*/)
{
	GetPublicationColumns( m_tiConcerning, m_pDoc, columns, stType );
}

void CEventItem::GetPublicationColumns(TREEITEMS ti, const CStageRaceDoc* pDoc, PUBLI_BODYCOLUMNS columns[], STAGETYPES stType /*= ST_NORMAL*/)
{
	int nPos = 0;
	switch( ti )
	{
		case TI_TIMETRIALORDER:
			columns[ nPos++ ] = PBC_STARTINGORDER;
			columns[ nPos++ ] = PBC_STARTINGORDERTIME;
	}
	switch( ti )
	{
		case TI_TTARRIVALLIST:
		case TI_HALFSTAGE:
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_RANK					) ) columns[ nPos++ ] = PBC_RANK;
		case TI_SIGNINLIST:
		case TI_TIMETRIALORDER:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STANO					) ) columns[ nPos++ ] = PBC_STANO;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_UCICODE					) ) columns[ nPos++ ] = PBC_UCICODE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_LICENSE					) ) columns[ nPos++ ] = PBC_LICENSE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_RIDER					) ) columns[ nPos++ ] = PBC_RIDER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMNAME				) ) columns[ nPos++ ] = PBC_TEAMNAME;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODEWITHOUTCOLUMNTITLE
																									) ) columns[ nPos++ ] = PBC_TEAMCODEWITHOUTCOLUMNHEADER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_TEAMCODE				) ) columns[ nPos++ ] = PBC_TEAMCODE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_COUNTRY					) ) columns[ nPos++ ] = PBC_COUNTRY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_CATEGORY				) ) columns[ nPos++ ] = PBC_CATEGORY;
	}
	switch( ti )
	{
		case TI_HALFSTAGE:
		case TI_TTARRIVALLIST:
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK10STAGE:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_TIME				) )
				if( stType==ST_NORMAL )
					columns[ nPos++ ] = PBC_TIME;
				else
					columns[ nPos++ ] = PBC_TIMEWITHTHOUSANDTH;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_GAP				) ) columns[ nPos++ ] = PBC_GAP;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_NEWGAP			) ) columns[ nPos++ ] = PBC_NEWGAP;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_TT_SPEED ) && ( stType!=ST_NORMAL		) ) columns[ nPos++ ] = PBC_SPEED;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_BONUSES			) ) columns[ nPos++ ] = PBC_BONUSES;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STAGE_PENALTY			) ) columns[ nPos++ ] = PBC_PENALTY;
			break;
//		case TI_ROOT:
//		case TI_COMMUNIQUE:
//		case TI_CROSSOUTLIST:
		case TI_SIGNINLIST:
			columns[ nPos++ ] = PBC_SIGNINAREA;
			break;
		case TI_SPRINT:
		case TI_POINTS:
		case TI_CLIMB:
		case TI_MOSTAGGRESSIVE:
			columns[ nPos++ ] = PBC_POINTS;
			break;
		case TI_CLASSSTANOSORTEDGENERAL:
			// Note that there is no point in PBC_NEWGAP for this type of classification, so we prevent the occurance of it
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_TIME			) ) columns[ nPos++ ] = PBC_TIME;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_GAP				) ) columns[ nPos++ ] = PBC_GAP;
			else if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_NEWGAP		) ) columns[ nPos++ ] = PBC_GAP;
			break;																						
		case TI_CLASSGENERAL:
		case TI_CLASSMASK1GENERAL:
		case TI_CLASSMASK2GENERAL:
		case TI_CLASSMASK3GENERAL:
		case TI_CLASSMASK4GENERAL:
		case TI_CLASSMASK5GENERAL:
		case TI_CLASSMASK6GENERAL:
		case TI_CLASSMASK7GENERAL:
		case TI_CLASSMASK8GENERAL:
		case TI_CLASSMASK9GENERAL:
		case TI_CLASSMASK10GENERAL:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_TIME			) ) columns[ nPos++ ] = PBC_TIME;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_GAP				) ) columns[ nPos++ ] = PBC_GAP;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_GENERAL_NEWGAP			) ) columns[ nPos++ ] = PBC_NEWGAP;
			break;																						
		case TI_CLASSTEAMS:																				
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_RANK							) ) columns[ nPos++ ] = PBC_RANK;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASFULLROWS		) )
			{
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_STANO				) ) columns[ nPos++ ] = PBC_STANO;
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_UCICODE				) ) columns[ nPos++ ] = PBC_UCICODE;
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_LICENSE				) ) columns[ nPos++ ] = PBC_LICENSE;
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_RIDER				) ) columns[ nPos++ ] = PBC_RIDER;
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_COUNTRY				) ) columns[ nPos++ ] = PBC_COUNTRY;
				if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_INDIVIDUAL_CATEGORY			) ) columns[ nPos++ ] = PBC_CATEGORY;
			}
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_TEAMNAME						) ) columns[ nPos++ ] = PBC_TEAMNAMEFROMRANK;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_TEAMCODEWITHOUTCOLUMNTITLE		) ) columns[ nPos++ ] = PBC_TEAMCODEFROMRANKWITHOUTCOLUMNHEADER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_TEAMCODE						) ) columns[ nPos++ ] = PBC_TEAMCODEFROMRANK;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH )
				&& !pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_INVOLVEDBUNCH_ASFULLROWS	) ) columns[ nPos++ ] = PBC_INVOLVEDBUNCH;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_TIME							) ) columns[ nPos++ ] = PBC_TIME;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_GAP							) ) columns[ nPos++ ] = PBC_GAP;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_TEAM_NEWGAP						) ) columns[ nPos++ ] = PBC_NEWGAP;
			break;																					
		case TI_LISTCOMPETITORS1:																	
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_STANO					) ) columns[ nPos++ ] = PBC_STANO;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE1									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK1					) ) columns[ nPos++ ] = PBC_MASK1;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE2									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK2					) ) columns[ nPos++ ] = PBC_MASK2;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE3									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK3					) ) columns[ nPos++ ] = PBC_MASK3;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE4									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK4					) ) columns[ nPos++ ] = PBC_MASK4;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE5									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK5					) ) columns[ nPos++ ] = PBC_MASK5;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE6									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK6					) ) columns[ nPos++ ] = PBC_MASK6;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE7									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK7					) ) columns[ nPos++ ] = PBC_MASK7;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE8									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK8					) ) columns[ nPos++ ] = PBC_MASK8;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE9									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK9					) ) columns[ nPos++ ] = PBC_MASK9;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE10									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_MASK10					) ) columns[ nPos++ ] = PBC_MASK10;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_RIDER					) ) columns[ nPos++ ] = PBC_RIDER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMNAME					) ) columns[ nPos++ ] = PBC_TEAMNAME;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMCODEWITHOUTCOLUMNTITLE
																									) ) columns[ nPos++ ] = PBC_TEAMCODEWITHOUTCOLUMNHEADER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_TEAMCODE					) ) columns[ nPos++ ] = PBC_TEAMCODE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_UCICODE					) ) columns[ nPos++ ] = PBC_UCICODE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_LICENSE					) ) columns[ nPos++ ] = PBC_LICENSE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_COUNTRY					) ) columns[ nPos++ ] = PBC_COUNTRY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP1_CATEGORY					) ) columns[ nPos++ ] = PBC_CATEGORY;
			break;																					
		case TI_LISTCOMPETITORS2:																	
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_STANO					) ) columns[ nPos++ ] = PBC_STANO;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE1									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK1					) ) columns[ nPos++ ] = PBC_MASK1;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE2									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK2					) ) columns[ nPos++ ] = PBC_MASK2;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE3									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK3					) ) columns[ nPos++ ] = PBC_MASK3;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE4									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK4					) ) columns[ nPos++ ] = PBC_MASK4;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE5									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK5					) ) columns[ nPos++ ] = PBC_MASK5;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE6									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK6					) ) columns[ nPos++ ] = PBC_MASK6;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE7									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK7					) ) columns[ nPos++ ] = PBC_MASK7;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE8									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK8					) ) columns[ nPos++ ] = PBC_MASK8;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE9									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK9					) ) columns[ nPos++ ] = PBC_MASK9;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_MASKS_USE10									) &&
				pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_MASK10					) ) columns[ nPos++ ] = PBC_MASK10;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_RIDER					) ) columns[ nPos++ ] = PBC_RIDER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_UCICODE					) ) columns[ nPos++ ] = PBC_UCICODE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_LICENSE					) ) columns[ nPos++ ] = PBC_LICENSE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_COUNTRY					) ) columns[ nPos++ ] = PBC_COUNTRY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_COLS_LISTCOMP2_CATEGORY					) ) columns[ nPos++ ] = PBC_CATEGORY;
			break;
	}
	switch( ti )
	{
		case TI_TTARRIVALLIST:
			columns[ nPos++ ] = PBC_STARTINGORDER;
	}
	columns[ nPos++ ] = PBC_TERMINATOR;
}

void CEventItem::RemovePublicationColumn(PUBLI_BODYCOLUMNS columns[], PUBLI_BODYCOLUMNS remove)
{
	int i = 0;
	int nRemove = 0;
	while( columns[i]!=PBC_TERMINATOR )
	{
		if( columns[i]==remove )
		{
			nRemove++;
		}
		columns[i] = columns[i+nRemove];
		i++;
	}
}

void CEventItem::GetPublicationProperties(PUBLI_PROPERTIES props[])
{
	GetPublicationProperties( m_pDoc, m_tiConcerning, m_nFullStage, m_nHalfStage, props );
}

void CEventItem::GetPublicationProperties(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS, PUBLI_PROPERTIES props[], STAGETYPES stType /*= ST_NORMAL*/)
{
	PUBLI_PROPERTIES tempprops[PUBLI_PROPERTIES_MAX];

	int nPos = 0;

	// Organiser for all except competitors lists
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_ORGANISER					) ) 
		switch( ti )
		{
			case TI_SPRINT:
			case TI_CLIMB:
			case TI_MOSTAGGRESSIVE:
			case TI_POINTS:
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
			case TI_CLASSTEAMS:
			case TI_TIMETRIALORDER:
			case TI_CROSSOUTLIST:
			case TI_SIGNINLIST:
				tempprops[ nPos++ ] = PPR_ORGANISER;
				break;
		}
	// Mask type
	switch( ti )
	{
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK1GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_1;
			break;
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK2GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_2;
			break;
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK3GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_3;
			break;
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK4GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_4;
			break;
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK5GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_5;
			break;
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK6GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_6;
			break;
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK7GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_7;
			break;
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK8GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_8;
			break;
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK9GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_9;
			break;
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK10GENERAL:
			tempprops[ nPos++ ] = PPR_MASK_10;
			break;
	}	
	// Full stage
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_FULLSTAGE			) ) 
		switch( ti )
		{
			case TI_SPRINT:
			case TI_CLIMB:
			case TI_MOSTAGGRESSIVE:
			case TI_POINTS:
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
			case TI_CLASSTEAMS:
				tempprops[ nPos++ ] = PPR_STAGE_INDICATOR;
				break;
		}
	// Half stage
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_HALFSTAGE			) ) 
		switch( ti )
		{
			case TI_SPRINT:
				tempprops[ nPos++ ] = PPR_SPRINTS;
				break;
			case TI_MOSTAGGRESSIVE:
				tempprops[ nPos++ ] = PPR_MOSTAGGRESSIVE;
				break;
			case TI_CLIMB:
				tempprops[ nPos++ ] = PPR_CLIMBS;
				break;
			case TI_POINTS:
				tempprops[ nPos++ ] = PPR_POINTS;
				break;
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
				tempprops[ nPos++ ] = PPR_SINGLE_STAGE_CLASSIFICATION;
				break;
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
				tempprops[ nPos++ ] = PPR_GENERAL_CLASSIFICATION;
				break;
			case TI_CLASSTEAMS:
				tempprops[ nPos++ ] = PPR_GENERAL_CLASSIFICATION;
				break;
		}
	// Main category
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_CATEGORY			) ) 
		switch( ti )
		{
			case TI_SPRINT:
			case TI_CLIMB:
			case TI_MOSTAGGRESSIVE:
			case TI_POINTS:
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
			case TI_CLASSTEAMS:
				tempprops[ nPos++ ] = PPR_CATEGORY;
				break;
		}
	// Speed
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_SPEED				) ) 
		switch( ti )
		{
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
				tempprops[ nPos++ ] = PPR_SPEED;
				break;
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
				tempprops[ nPos++ ] = PPR_OVERALL_SPEED;
				break;
		}
	// Distance
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_DISTANCE			) ) 
		switch( ti )
		{
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
				tempprops[ nPos++ ] = PPR_DISTANCE;
				break;
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
				tempprops[ nPos++ ] = PPR_OVERALL_DISTANCE;
				break;
		}
	// Time of winner
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_BESTTIME			) ) 
		switch( ti )
		{
			case TI_HALFSTAGE:
			case TI_TTARRIVALLIST:
			case TI_CLASSMASK1STAGE:
			case TI_CLASSMASK2STAGE:
			case TI_CLASSMASK3STAGE:
			case TI_CLASSMASK4STAGE:
			case TI_CLASSMASK5STAGE:
			case TI_CLASSMASK6STAGE:
			case TI_CLASSMASK7STAGE:
			case TI_CLASSMASK8STAGE:
			case TI_CLASSMASK9STAGE:
			case TI_CLASSMASK10STAGE:
				if( stType!=ST_NORMAL )
				{
					tempprops[ nPos++ ] = PPR_TIME_OF_WINNER_WITHTHOUSANDTH;
					break;
				}
			case TI_CLASSSTANOSORTEDGENERAL:
			case TI_CLASSGENERAL:
			case TI_CLASSMASK1GENERAL:
			case TI_CLASSMASK2GENERAL:
			case TI_CLASSMASK3GENERAL:
			case TI_CLASSMASK4GENERAL:
			case TI_CLASSMASK5GENERAL:
			case TI_CLASSMASK6GENERAL:
			case TI_CLASSMASK7GENERAL:
			case TI_CLASSMASK8GENERAL:
			case TI_CLASSMASK9GENERAL:
			case TI_CLASSMASK10GENERAL:
				tempprops[ nPos++ ] = PPR_TIME_OF_WINNER;
				break;
		}
	// Opening hour on stage classifications
	if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_INDIVIDUAL_STAGE_OPENINGHOUR	)
			&& ((ti==TI_HALFSTAGE)||(ti==TI_TTARRIVALLIST)) ) 
		tempprops[ nPos++ ] = PPR_START_OF_EVENT_TIME;

	switch( ti )
	{
		case TI_TIMETRIALORDER:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_FULLSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_HALFSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_HALF_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_CATEGORY				) ) 
				tempprops[ nPos++ ] = PPR_CATEGORY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_DISTANCE				) ) 
				tempprops[ nPos++ ] = PPR_DISTANCE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_TTORDER_OPENINGHOUR			) ) 
				tempprops[ nPos++ ] = PPR_START_OF_EVENT_TIME;
			break;
		case TI_CROSSOUTLIST:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_FULLSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_HALFSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_HALF_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_CATEGORY			) ) 
				tempprops[ nPos++ ] = PPR_CATEGORY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_DISTANCE			) ) 
				tempprops[ nPos++ ] = PPR_DISTANCE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_CROSSOUT_OPENINGHOUR			) ) 
				tempprops[ nPos++ ] = PPR_START_OF_EVENT_TIME;
			break;
		case TI_SIGNINLIST:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_FULLSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_HALFSTAGE			) ) 
				tempprops[ nPos++ ] = PPR_HALF_STAGE_INDICATOR;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_CATEGORY			) ) 
				tempprops[ nPos++ ] = PPR_CATEGORY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_DISTANCE			) ) 
				tempprops[ nPos++ ] = PPR_DISTANCE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_SIGNIN_OPENINGHOUR			) ) 
				tempprops[ nPos++ ] = PPR_START_OF_EVENT_TIME;
			break;
		case TI_LISTCOMPETITORS1:
		case TI_LISTCOMPETITORS2:
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_ORGANISER		) ) 
				tempprops[ nPos++ ] = PPR_ORGANISER;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_MAINLOCATION	) )
				tempprops[ nPos++ ] = PPR_LOCATION;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_DATES			) )
				tempprops[ nPos++ ] = PPR_DATE;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_CATEGORY		) )
				tempprops[ nPos++ ] = PPR_CATEGORY;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_COMPCOUNT		) )
				tempprops[ nPos++ ] = PPR_COMPETITORSCOUNT;
			if( pDoc->m_allsettings.ValueGet( IDS_SETT_PUBL_HEADER_PROPS_COMPETITORS_TEAMCOUNT		) )
				tempprops[ nPos++ ] = PPR_TEAMSCOUNT;
			break;
		case TI_COMMUNIQUE:
			// Be careful, the following is considered to be content
			// instead of properties, ergo is done elsewhere
			// Other properties can nevertheless be included here
//			tempprops[ nPos++ ] = PPR_TITLE_COMMUNIQUE;
//			tempprops[ nPos++ ] = PPR_DATE_COMMUNIQUE;
			break;
		case TI_ROOT:
			break;
	}
	tempprops[ nPos++ ] = PPR_TERMINATOR;

	int nCount = GetPublicationPropertiesCount( tempprops );
	if( pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_PROPS_DIRECTION_HORIZONTAL) )
	{
		for( int i=0, breaks=0; i<=nCount; i++ )
		{
			props[i+breaks] = tempprops[i];
			if( (nCount== 4) && (i== 1) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 5) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 6) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 7) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 8) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 8) && (i== 4) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 9) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 9) && (i== 5) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==10) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==10) && (i== 6) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==11) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==11) && (i== 6) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==12) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==12) && (i== 7) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==13) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==13) && (i== 6) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==13) && (i== 9) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==14) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==14) && (i== 6) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==14) && (i== 9) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==15) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==15) && (i== 7) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==15) && (i==10) ) props[i+(++breaks)] = PPR_LINEBREAK;
		}
	}
	else
	{
		for( int i=0, breaks=0; i<=nCount; i++ )
		{
			props[i+breaks] = tempprops[i];
			if( (nCount== 6) && (i== 2) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 7) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 8) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount== 9) && (i== 4) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==10) && (i== 4) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==11) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==11) && (i== 6) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==12) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==12) && (i== 7) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==13) && (i== 3) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==13) && (i== 8) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==14) && (i== 4) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==14) && (i== 8) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==15) && (i== 4) ) props[i+(++breaks)] = PPR_LINEBREAK;
			if( (nCount==15) && (i== 9) ) props[i+(++breaks)] = PPR_LINEBREAK;
		}
	}
}

int CEventItem::GetPublicationColumnsArrayCount(PUBLI_BODYCOLUMNS columns[])
{
 	int i = 0;
 	int count = 0;
 	while( columns[i++]!=PBC_TERMINATOR );
 	return i + count;
}

int CEventItem::GetPublicationColumnsCount(PUBLI_BODYCOLUMNS columns[])
{
 	int i = 0;
 	int count = 0;
 	while( columns[i]!=PBC_TERMINATOR )
 	{
 		switch(columns[i])
 		{
 			case PBC_TIMEWITHTHOUSANDTH:
 			case PBC_UCICODE:
 				count++;
 		};
 		i++;
 	}
 	return i + count;
}

int CEventItem::GetPublicationPropertiesCount(PUBLI_PROPERTIES props[])
{
 	int i = 0;
 	int count = 0;
 	while( props[i]!=PPR_TERMINATOR )
 		if( props[i++]==PPR_LINEBREAK ) count++;
 	return i + count;
}

int CEventItem::GetDistance()
{
	if( m_nHalfStage )
		return ((CStageRaceDoc*)m_pDoc)->StagesGet( m_nFullStage, m_nHalfStage )->m_distance;
	else
		return 0;
}

int CEventItem::GetRealDistanceCumulative()
{
	return GetCumulativeDistance( false, false );
}

int CEventItem::GetOfficialDistanceCumulativeBefore()
{
	return GetCumulativeDistance( true );
}

int CEventItem::GetOfficialDistanceCumulative()
{
	return GetCumulativeDistance( false );
}

int CEventItem::GetCumulativeDistance(bool bBefore, bool bOfficial)
{
	int nDistance=0;
	if( m_nHalfStage )
	{
		CHalfStage* pStage = ((CStageRaceDoc*)m_pDoc)->StagesGet( m_nFullStage, m_nHalfStage );

		// Iterate the full stages list
		for ( int i=1;
			i <= ((CStageRaceDoc*)m_pDoc)->StagesFullCount(); i++ )
		{
			// Iterate the half stages list
			for ( int j=1;
				j <= ((CStageRaceDoc*)m_pDoc)->StagesGet( i )->CountHalfStages(); j++ )
			{
				if( (((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )==pStage) && bBefore )
					goto done;
				// If this stage is a prologue, do not count in the distance
				if( (i>1) || (j>1) || !m_pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_PROLOGUE_EXISTS ) || !bOfficial )
				{
					// Add every half stage distance
					if( !((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )->m_exclude )
						nDistance += (((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )->m_distance
							* ((((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )->m_stageType==ST_NORMAL)?((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )->m_rounds:1));
				}
				if( (((CStageRaceDoc*)m_pDoc)->StagesGet( i, j )==pStage) && !bBefore )
					goto done;
			}
		}
	}
done:
	return nDistance;
}

// IN: the identifiers of the half stage of which we need an ID string
// OUT: an ID string of the form "<FSID>-<HSID>"
CString CEventItem::StagesMakeIDString(int nFS, int nHS, const CStageRaceDoc* pDoc)
{
	if( !nHS )
		return StagesMakeIDString( nFS, pDoc );

	if( (nHS==1) && (nFS==1) && pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_PROLOGUE_EXISTS ) )
	{
		return "P";
	}
	else
	{
		CString cID = StagesMakeIDString( nFS, pDoc );

		if( !pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_STAGENUMBERING_SUPPRESS )
				|| (((CStageRaceDoc*)pDoc)->StagesHalfCount(nFS)>1) )
		{
			TCHAR cBuffer[10];
			_itot( nHS, cBuffer, 10 );
			cID = cID + "-" + CString(cBuffer);
		}

		return cID;
	}
}

// IN: the identifier of the full stage of which we need an ID string
// OUT: an ID string of the form "<FSID>"
CString CEventItem::StagesMakeIDString(int nFS, const CStageRaceDoc* pDoc)
{
	if( (nFS==1) && pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_PROLOGUE_EXISTS ) )
	{
		return "P";
	}
	else
	{
		TCHAR cBuffer[10];
		_itot( pDoc->m_allsettings.ValueGet( IDS_SETT_GNRL_PROLOGUE_EXISTS )?(nFS-1):nFS, cBuffer, 10 );
		return CString(cBuffer);
	}
}

CString CEventItem::StagesMakeIDString()
{
	return StagesMakeIDString( m_nFullStage, m_nHalfStage, m_pDoc );
}

bool CEventItem::IsPublicationReadonly()
{
	if( IsPublicationAvailable() )
	{
		HANDLE handle;
		BY_HANDLE_FILE_INFORMATION info;

		handle = CreateFile(
			ComposeFileNamePath(),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL );

		if( handle != INVALID_HANDLE_VALUE )
		{
			GetFileInformationByHandle(handle, &info);

			CloseHandle( handle );

			return info.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
		}
	}
	return false;
}

bool CEventItem::IsPublicationReadonly(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	return ei.IsPublicationReadonly();
}

void CEventItem::ToggleReadonly()
{
	if( IsPublicationAvailable() )
	{
		HANDLE handle;
		BY_HANDLE_FILE_INFORMATION info;

		handle = CreateFile(
			ComposeFileNamePath(),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL );

		if( handle != INVALID_HANDLE_VALUE )
		{
			GetFileInformationByHandle(handle, &info);

			CloseHandle( handle );

			info.dwFileAttributes = info.dwFileAttributes ^ FILE_ATTRIBUTE_READONLY;

			SetFileAttributes(
				ComposeFileNamePath(),
				info.dwFileAttributes
			);
		}
	}
}

void CEventItem::ToggleReadonly(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	ei.ToggleReadonly();
}

void CEventItem::EditPublication()
{
	// First get the name of the application
	CSRRegKey reg;
	reg.Open( HKEY_CURRENT_USER, TEXT("Software\\Totaal Software\\StageRace\\Options") );

	// Set up a path for Notepad that we use as default application
	TCHAR lpBuffer[MAX_PATH];
	GetWindowsDirectory( lpBuffer, MAX_PATH );
	CString cBuffer = CString(lpBuffer);
	if( cBuffer.Right(1)!="\\" ) cBuffer+="\\";
	cBuffer+="notepad.exe";

	// Get the path to the file we need to convert.
	CString cPath = reg.GetString( TEXT("Publication editor"), cBuffer );

	// Create a process with the application and document we want
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset (&si, 0, sizeof (si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;

	CreateProcess(
			cPath.GetBuffer(0),
			CString(" \""+ComposeFileNamePath()+"\"").GetBuffer(0),
			NULL,
			NULL,
			FALSE,
			NORMAL_PRIORITY_CLASS,
			NULL,
			NULL,
			&si,
			&pi
		);
}

void CEventItem::EditPublication(const CStageRaceDoc *pDoc, TREEITEMS ti, int nFS, int nHS)
{
	CEventItem ei( pDoc, ti, nFS, nHS );
	ei.EditPublication();
}

CString CEventItem::GetSponsorSubTitle()
{
	if( GetSponsor().IsEmpty() )
	{
		return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle;
	}
	else
	{
		// Replace sub title with sponsor
		if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_SPONSOR_ASSUBTITLE) )
			return GetSponsor();
		// Add sponsor to sub title
		else if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_SPONSOR_ADDTOSUBTITLE) )
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle
				+ TEXT("<BR>") + GetSponsor();
		// Just use sub title only
		else // if( m_pDoc->m_allsettings.ValueGet(IDS_SETT_PUBL_HEADER_SPONSOR_DONTUSE) )
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_eventSubTitle;
	}
}

CString CEventItem::GetSponsor()
{
	switch( m_tiConcerning )
	{
		case TI_CLASSSTANOSORTEDGENERAL:
		case TI_CLASSGENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_general;
		case TI_CLASSTEAMS:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_teams;
		case TI_SPRINT:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_sprint;
		case TI_CLIMB:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_climb;
		case TI_POINTS:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_points;
		case TI_MOSTAGGRESSIVE:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mostaggressive;
		case TI_CLASSMASK1STAGE:
		case TI_CLASSMASK1GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask1;
		case TI_CLASSMASK2STAGE:
		case TI_CLASSMASK2GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask2;
		case TI_CLASSMASK3STAGE:
		case TI_CLASSMASK3GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask3;
		case TI_CLASSMASK4STAGE:
		case TI_CLASSMASK4GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask4;
		case TI_CLASSMASK5STAGE:
		case TI_CLASSMASK5GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask5;
		case TI_CLASSMASK6STAGE:
		case TI_CLASSMASK6GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask6;
		case TI_CLASSMASK7STAGE:
		case TI_CLASSMASK7GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask7;
		case TI_CLASSMASK8STAGE:
		case TI_CLASSMASK8GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask8;
		case TI_CLASSMASK9STAGE:
		case TI_CLASSMASK9GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask9;
		case TI_CLASSMASK10STAGE:
		case TI_CLASSMASK10GENERAL:
			return ((CSettingsGeneral*)m_pDoc->m_allsettings.GetSettings(SETT_GENERAL))->m_cl_sponsor_mask10;
		default:
			return CString();
	}
}

CString CEventItem::RemoveIllegalChars(CString c)
{
	c.Replace('/', '_');
	c.Replace('\\', '_');
	c.Replace(':', '_');
	c.Replace('*', '_');
	c.Replace('?', '_');
	c.Replace('"', '_');
	c.Replace('<', '_');
	c.Replace('>', '_');
	c.Replace('|', '_');
	return c;
}
