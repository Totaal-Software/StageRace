// AllListPages.h: interface for the CAllListPages class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALLLISTPAGES_H__52844EB4_8269_4DFB_8A28_30CC327C7195__INCLUDED_)
#define AFX_ALLLISTPAGES_H__52844EB4_8269_4DFB_8A28_30CC327C7195__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAllListPages : public CStageRaceWnd<cdxCDynamicPropPage>
{
public:
	CArrivalList m_listArrival;
	CArrivalList m_listAvailable;

	CAllListPages(
		CHelp::HELP_TOPIC helptopic,
		UINT nIDTemplate,
		UINT nIDLabel,
		const CAvailableList* pListAvailable,
		const CArrivalList* pListArrival,
		const CCompetitorList* pListCompetitor=NULL );
};

#endif // !defined(AFX_ALLLISTPAGES_H__52844EB4_8269_4DFB_8A28_30CC327C7195__INCLUDED_)
