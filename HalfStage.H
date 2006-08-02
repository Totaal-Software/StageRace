// HalfStage.h: interface for the CHalfStage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HALFSTAGE_H__F878B640_C503_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_HALFSTAGE_H__F878B640_C503_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CHalfStage : public CObject
{
public:
	bool OrderInvolvesArrival();
	bool InputOnTimingIdle();
	bool InputArrivalReset(WORD nStaNo);
	bool InputArrivalSetByTime(WORD nStaNo, DWORD nUnits, CStaNoObjectList* pAvail);
	bool InputArrivalSet(WORD nStaNo, WORD nRank, DWORD nUnits, CStaNoObjectList* pAvail);
	void PublishTTArrivalList(CStageRaceDoc*, int nFS, int nHS);
	CId m_idStage;
	CId m_idTTArrival;
	CId m_idGeneral;
	CId m_idClimbs;
	CId m_idSprints;
	CId m_idPoints;
	CId m_idMostAggressive;
	CId m_idStartList;
	CId m_idMask1stage;
	CId m_idMask2stage;
	CId m_idMask3stage;
	CId m_idMask4stage;
	CId m_idMask5stage;
	CId m_idMask6stage;
	CId m_idMask7stage;
	CId m_idMask8stage;
	CId m_idMask9stage;
	CId m_idMask10stage;
	CId m_idMask1gen;
	CId m_idMask2gen;
	CId m_idMask3gen;
	CId m_idMask4gen;
	CId m_idMask5gen;
	CId m_idMask6gen;
	CId m_idMask7gen;
	CId m_idMask8gen;
	CId m_idMask9gen;
	CId m_idMask10gen;
	CId m_idTeams;
	CId m_idCrossOut;
	CId m_idSignIn;
	CId m_idGeneralStaNoSorted;

	CCommunique m_communique;

	int m_rounds;
	int m_distance;
	CString m_openingHour;
	CString m_title;

	CMap<WORD,WORD&,WORD,WORD&> m_bonusesIntermediate;
	CMap<WORD,WORD&,WORD,WORD&> m_bonusesFinish;
	WORD m_bonusesCount;

	CMap<WORD,WORD&,WORD,WORD&> m_sprintpointsIntermediate;
	CMap<WORD,WORD&,WORD,WORD&> m_sprintpointsFinish;
	WORD m_sprintpointsCount;

	CMap<WORD,WORD&,WORD,WORD&> m_pointspointsFinish;

	CMap<WORD,WORD&,WORD,WORD&> m_mostaggressivepoints;

	CMap<WORD,WORD&,WORD,WORD&> m_climbpointshc;
	CMap<WORD,WORD&,WORD,WORD&> m_climbpoints1;
	CMap<WORD,WORD&,WORD,WORD&> m_climbpoints2;
	CMap<WORD,WORD&,WORD,WORD&> m_climbpoints3;
	CMap<WORD,WORD&,WORD,WORD&> m_climbpoints4;
	CList<WORD,WORD&> m_climbsorder;

	STAGETYPES m_stageType;
	bool m_exclude;
	bool m_oneForTeamsClass;
	bool m_allowLateChangesStartOrder;

	bool m_bWorkPendingForTimingIdle;

	CList< CArrivalList, CArrivalList& > m_bonuses;
	CList< CArrivalList, CArrivalList& > m_sprints;
	CList< CArrivalList, CArrivalList& > m_climbs;
	CArrivalList m_mostaggressive;

	CSignOutList m_signOuts;
	CArrivalList m_timeTrialOrder;
	CArrivalList m_arrival;
	CCorrectionList m_correction;

	CHalfStage& operator=(CBonusDat &aBonusDat);
	CHalfStage& operator=(CSprintDat &aSprintDat);
	CHalfStage& operator=(CPointsDat &aPointsDat);
	CHalfStage& operator=(CMostAggressiveDat &aMostAggressiveDat);
	CHalfStage& operator=(CMountainDat &aMountainDat);
	CHalfStage& operator=(CHalfStage &aHalfStage);
	CHalfStage& operator=(CHalfStageTrialDat &aHalfStageTrialDat);
	CHalfStage& operator=(CListCorrection &aListCorr);

	CHalfStage();
	virtual ~CHalfStage();
	void Serialize(CArchive& ar);
	void FunctionRemovegaps();
	void FunctionRemove1xseconds();
	bool FunctionImport(const CStaNoObjectList* pAvail, HANDLE hSemaphore);
	void FunctionGroupt(short nSecs);
	void FunctionCheck();
	int InputSignOuts(const CStaNoObjectList* pAvail,
		const CMultiLanguage::REQUIREDLANGUAGES* pLang,
		const CCompetitorList* pCompReference,
		HANDLE hSemaphore);
	int InputStartingOrder(const CStaNoObjectList* pAvail,
		const CCompetitorList* pCompReference,
		HANDLE hSemaphore,
		const CDistributedClassification* pPreviousHS=NULL,
		const CDistributedClassification* pPreviousFS=NULL );
	int InputRanking(char nType, const CStaNoObjectList* pAvail, int nAccuracy, const CCompetitorList* pCompReference,
		HANDLE hSemaphore );
	void Generate(int nFS, int nHS, CClassification* pClass, CTeamClassification *pTeam=NULL, CPointsClassification* pPoints=NULL, CSprintClassification* pSprint=NULL);
	int Edit( CFullStage* pFullStage, HANDLE hSemaphore=NULL );
};

#endif // !defined(AFX_HALFSTAGE_H__F878B640_C503_11D2_B376_0040954019F4__INCLUDED_)
