// HalfStage.cpp: implementation of the CHalfStage class.
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
	
CHalfStage::CHalfStage()
{
	m_distance					= 0;
	m_rounds					= 1;
	m_bonusesCount				= 0;
	m_sprintpointsCount			= 0;
	m_stageType					= ST_NORMAL;
	m_exclude					= false;
	m_allowLateChangesStartOrder= false;
	m_oneForTeamsClass			= false;
	m_bWorkPendingForTimingIdle	= false;
}

CHalfStage::~CHalfStage()
{

}

CHalfStage& CHalfStage::operator =(CHalfStage & aHalfStage)
{
	POSITION nPos;

	// This half stage's communique
	m_communique		= aHalfStage.m_communique;

	// Main trialdat
	m_distance			= aHalfStage.m_distance ;
	m_rounds			= aHalfStage.m_rounds ;
	m_openingHour		= aHalfStage.m_openingHour;
	m_title				= aHalfStage.m_title;
	m_stageType			= aHalfStage.m_stageType;
	m_exclude			= aHalfStage.m_exclude;
	m_allowLateChangesStartOrder = aHalfStage.m_allowLateChangesStartOrder;
	m_oneForTeamsClass	= aHalfStage.m_oneForTeamsClass;

	// Bonuses
		//Configuration
		nPos = aHalfStage.m_bonusesIntermediate.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_bonusesIntermediate.GetNextAssoc( nPos, nKey, nValue );
			m_bonusesIntermediate.SetAt( nKey, nValue );
		}

		nPos = aHalfStage.m_bonusesFinish.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_bonusesFinish.GetNextAssoc( nPos, nKey, nValue );
			m_bonusesFinish.SetAt( nKey, nValue );
		}

		m_bonusesCount = aHalfStage.m_bonusesCount;
		//Data
		m_bonuses.RemoveAll();
		nPos = aHalfStage.m_bonuses.GetHeadPosition();
		while( nPos )
		{
			m_bonuses.AddTail( aHalfStage.m_bonuses.GetNext( nPos ) );
		}

	// Intermediate sprints
		//Configuration
		nPos = aHalfStage.m_sprintpointsIntermediate.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_sprintpointsIntermediate.GetNextAssoc( nPos, nKey, nValue );
			m_sprintpointsIntermediate.SetAt( nKey, nValue );
		}

		nPos = aHalfStage.m_sprintpointsFinish.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_sprintpointsFinish.GetNextAssoc( nPos, nKey, nValue );
			m_sprintpointsFinish.SetAt( nKey, nValue );
		}

		m_sprintpointsCount = aHalfStage.m_sprintpointsCount;
		//Data
		m_sprints.RemoveAll();
		nPos = aHalfStage.m_sprints.GetHeadPosition();
		while( nPos )
		{
			m_sprints.AddTail( aHalfStage.m_sprints.GetNext( nPos ) );
		}

	// Points classification
		//Configuration
		nPos = aHalfStage.m_pointspointsFinish.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_pointspointsFinish.GetNextAssoc( nPos, nKey, nValue );
			m_pointspointsFinish.SetAt( nKey, nValue );
		}

	// Most aggressive rider competition
		//Configuration
		nPos = aHalfStage.m_mostaggressivepoints.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_mostaggressivepoints.GetNextAssoc( nPos, nKey, nValue );
			m_mostaggressivepoints.SetAt( nKey, nValue );
		}

		//Data
		m_mostaggressive = aHalfStage.m_mostaggressive;

	// Hill climbings
		//Configuration
		m_climbpoints1.RemoveAll();
		nPos = aHalfStage.m_climbpoints1.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_climbpoints1.GetNextAssoc( nPos, nKey, nValue );
			m_climbpoints1.SetAt( nKey, nValue );
		}

		m_climbpoints2.RemoveAll();
		nPos = aHalfStage.m_climbpoints2.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_climbpoints2.GetNextAssoc( nPos, nKey, nValue );
			m_climbpoints2.SetAt( nKey, nValue );
		}

		m_climbpoints3.RemoveAll();
		nPos = aHalfStage.m_climbpoints3.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_climbpoints3.GetNextAssoc( nPos, nKey, nValue );
			m_climbpoints3.SetAt( nKey, nValue );
		}

		m_climbpoints4.RemoveAll();
		nPos = aHalfStage.m_climbpoints4.GetStartPosition();
		while( nPos )
		{
			WORD nKey, nValue;
			aHalfStage.m_climbpoints4.GetNextAssoc( nPos, nKey, nValue );
			m_climbpoints4.SetAt( nKey, nValue );
		}

		m_climbsorder.RemoveAll();
		nPos = aHalfStage.m_climbsorder.GetHeadPosition();
		while( nPos )
		{
			WORD nValue;
			nValue = aHalfStage.m_climbsorder.GetNext( nPos );
			m_climbsorder.AddTail( nValue );
		}

		//Data
		m_climbs.RemoveAll();
		nPos = aHalfStage.m_climbs.GetHeadPosition();
		while( nPos )
		{
			m_climbs.AddTail( aHalfStage.m_climbs.GetNext( nPos ) );
		}

    // SignOuts
	m_signOuts			= aHalfStage.m_signOuts;

    // Corrections
	m_correction		= aHalfStage.m_correction;

    // Arrival
	m_arrival			= aHalfStage.m_arrival;

    // Time trial order
	m_timeTrialOrder	= aHalfStage.m_timeTrialOrder;

	// ID's				
	m_idStage			= aHalfStage.m_idStage;
	m_idGeneral			= aHalfStage.m_idGeneral;
	m_idClimbs			= aHalfStage.m_idClimbs;
	m_idSprints			= aHalfStage.m_idSprints;
	m_idPoints			= aHalfStage.m_idPoints;
	m_idMostAggressive	= aHalfStage.m_idMostAggressive;
	m_idStartList		= aHalfStage.m_idStartList;
	m_idMask1stage			= aHalfStage.m_idMask1stage;
	m_idMask2stage			= aHalfStage.m_idMask2stage;
	m_idMask3stage			= aHalfStage.m_idMask3stage;
	m_idMask4stage			= aHalfStage.m_idMask4stage;
	m_idMask5stage			= aHalfStage.m_idMask5stage;
	m_idMask6stage			= aHalfStage.m_idMask6stage;
	m_idMask7stage			= aHalfStage.m_idMask7stage;
	m_idMask8stage			= aHalfStage.m_idMask8stage;
	m_idMask9stage			= aHalfStage.m_idMask9stage;
	m_idMask10stage			= aHalfStage.m_idMask10stage;
	m_idMask1gen			= aHalfStage.m_idMask1gen;
	m_idMask2gen			= aHalfStage.m_idMask2gen;
	m_idMask3gen			= aHalfStage.m_idMask3gen;
	m_idMask4gen			= aHalfStage.m_idMask4gen;
	m_idMask5gen			= aHalfStage.m_idMask5gen;
	m_idMask6gen			= aHalfStage.m_idMask6gen;
	m_idMask7gen			= aHalfStage.m_idMask7gen;
	m_idMask8gen			= aHalfStage.m_idMask8gen;
	m_idMask9gen			= aHalfStage.m_idMask9gen;
	m_idMask10gen			= aHalfStage.m_idMask10gen;
	m_idTeams			= aHalfStage.m_idTeams;
	m_idCrossOut		= aHalfStage.m_idCrossOut;
	m_idSignIn			= aHalfStage.m_idSignIn;
	m_idGeneralStaNoSorted = aHalfStage.m_idGeneralStaNoSorted;

	return *this;
}

CHalfStage& CHalfStage::operator =(CHalfStageTrialDat & aHalfStageTrialDat)
{
	m_distance			= aHalfStageTrialDat.m_distance ;
	m_rounds			= aHalfStageTrialDat.m_rounds;
	m_openingHour		= aHalfStageTrialDat.m_openingHour;
	m_title				= aHalfStageTrialDat.m_title;
	m_stageType			= aHalfStageTrialDat.m_stageType;
	m_exclude			= (aHalfStageTrialDat.m_exclude!=0);
	m_allowLateChangesStartOrder = (aHalfStageTrialDat.m_allowLateChangesStartOrder!=0);
	m_oneForTeamsClass	= (aHalfStageTrialDat.m_oneForTeamsClass!=0);
	m_arrival.SetTimeCut( aHalfStageTrialDat.m_timeCut );

	return *this;
}

CHalfStage& CHalfStage::operator =(CBonusDat & aBonusDat)
{
	WORD nKey;
	POSITION nPos;

	m_bonusesIntermediate.RemoveAll();
	nPos = aBonusDat.m_bonusesIntermediate.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_bonusesIntermediate.SetAt( nKey, aBonusDat.m_bonusesIntermediate.GetNext( nPos ) );
		nKey++;
	}
	
	m_bonusesFinish.RemoveAll();
	nPos = aBonusDat.m_bonusesFinish.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_bonusesFinish.SetAt( nKey, aBonusDat.m_bonusesFinish.GetNext( nPos ) );
		nKey++;
	}
	
	m_bonusesCount = aBonusDat.m_bonusesCount;

	CArrivalList aArrL;
	// Fix bonus list
	while( (m_bonusesCount - 1) > m_bonuses.GetCount() )
		m_bonuses.AddTail( aArrL );
	while( ((m_bonusesCount - 1) < m_bonuses.GetCount()) && m_bonuses.GetCount() )
		m_bonuses.RemoveTail();

	return *this;
}

CHalfStage& CHalfStage::operator =(CSprintDat & aSprintDat)
{
	WORD nKey;
	POSITION nPos;

	m_sprintpointsIntermediate.RemoveAll();
	nPos = aSprintDat.m_sprintpointsIntermediate.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_sprintpointsIntermediate.SetAt( nKey, aSprintDat.m_sprintpointsIntermediate.GetNext( nPos ) );
		nKey++;
	}
	
	m_sprintpointsFinish.RemoveAll();
	nPos = aSprintDat.m_sprintpointsFinish.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_sprintpointsFinish.SetAt( nKey, aSprintDat.m_sprintpointsFinish.GetNext( nPos ) );
		nKey++;
	}

	m_sprintpointsCount = aSprintDat.m_sprintpointsCount;

	CArrivalList aArrL;
	// Fix sprints list
	while( (m_sprintpointsCount - 1) > m_sprints.GetCount() )
		m_sprints.AddTail( aArrL );
	while( ((m_sprintpointsCount - 1) < m_sprints.GetCount()) && m_sprints.GetCount() )
		m_sprints.RemoveTail();

	return *this;
}

CHalfStage& CHalfStage::operator =(CPointsDat & aPointsDat)
{
	WORD nKey;
	POSITION nPos;

	m_pointspointsFinish.RemoveAll();
	nPos = aPointsDat.m_points.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_pointspointsFinish.SetAt( nKey, aPointsDat.m_points.GetNext( nPos ) );
		nKey++;
	}
	
	return *this;
}

CHalfStage& CHalfStage::operator =(CMostAggressiveDat & aMostAggressiveDat)
{
	WORD nKey;
	POSITION nPos;

	m_mostaggressivepoints.RemoveAll();
	nPos = aMostAggressiveDat.m_points.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_mostaggressivepoints.SetAt( nKey, aMostAggressiveDat.m_points.GetNext( nPos ) );
		nKey++;
	}
	
	return *this;
}

CHalfStage& CHalfStage::operator =(CMountainDat & aMountainDat)
{
	WORD nKey;
	POSITION nPos;

	m_climbpointshc.RemoveAll();
	nPos = aMountainDat.m_climbpointshc.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_climbpointshc.SetAt( nKey, aMountainDat.m_climbpointshc.GetNext( nPos ) );
		nKey++;
	}

	m_climbpoints1.RemoveAll();
	nPos = aMountainDat.m_climbpoints1.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_climbpoints1.SetAt( nKey, aMountainDat.m_climbpoints1.GetNext( nPos ) );
		nKey++;
	}

	m_climbpoints2.RemoveAll();
	nPos = aMountainDat.m_climbpoints2.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_climbpoints2.SetAt( nKey, aMountainDat.m_climbpoints2.GetNext( nPos ) );
		nKey++;
	}

	m_climbpoints3.RemoveAll();
	nPos = aMountainDat.m_climbpoints3.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_climbpoints3.SetAt( nKey, aMountainDat.m_climbpoints3.GetNext( nPos ) );
		nKey++;
	}

	m_climbpoints4.RemoveAll();
	nPos = aMountainDat.m_climbpoints4.GetHeadPosition();
	nKey=1;
	while( nPos )
	{
		m_climbpoints4.SetAt( nKey, aMountainDat.m_climbpoints4.GetNext( nPos ) );
		nKey++;
	}

	m_climbsorder.RemoveAll();
	nPos = aMountainDat.m_climbs.GetHeadPosition();
	while( nPos )
	{
		WORD nValue;
		nValue = aMountainDat.m_climbs.GetNext( nPos );
		m_climbsorder.AddTail( nValue );
	}

	CArrivalList aArrL;
	// Fix climbs list
	while( m_climbsorder.GetCount() > m_climbs.GetCount() )
		m_climbs.AddTail( aArrL );
	while( (m_climbsorder.GetCount() < m_climbs.GetCount()) && m_climbs.GetCount() )
		m_climbs.RemoveTail();

	return *this;
}

CHalfStage& CHalfStage::operator =(CListCorrection & aListCorr)
{
	// Correction list
	m_correction = aListCorr.m_listCorrection;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CHalfStage::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////

		// Communique
			m_communique.Serialize(ar);

		// Arrival lists
			m_arrival.Serialize(ar);
			m_timeTrialOrder.Serialize(ar);
			m_idGeneral.Serialize(ar);
			m_idStage.Serialize(ar);
			m_idMask1gen.Serialize(ar);
			m_idMask2gen.Serialize(ar);
			m_idMask3gen.Serialize(ar);
			m_idMask4gen.Serialize(ar);
			m_idMask5gen.Serialize(ar);
			m_idMask6gen.Serialize(ar);
			m_idMask7gen.Serialize(ar);
			m_idMask8gen.Serialize(ar);
			m_idMask9gen.Serialize(ar);
			m_idMask10gen.Serialize(ar);
			m_idMask1stage.Serialize(ar);
			m_idMask2stage.Serialize(ar);
			m_idMask3stage.Serialize(ar);
			m_idMask4stage.Serialize(ar);
			m_idMask5stage.Serialize(ar);
			m_idMask6stage.Serialize(ar);
			m_idMask7stage.Serialize(ar);
			m_idMask8stage.Serialize(ar);
			m_idMask9stage.Serialize(ar);
			m_idMask10stage.Serialize(ar);
			m_idTeams.Serialize(ar);

		// Bonuses/sprints/mountain
		// Configuration
			m_climbpointshc.Serialize(ar);
			m_climbpoints1.Serialize(ar);
			m_climbpoints2.Serialize(ar);
			m_climbpoints3.Serialize(ar);
			m_climbpoints4.Serialize(ar);
			m_climbsorder.Serialize(ar);
			m_idClimbs.Serialize(ar);

			m_sprintpointsIntermediate.Serialize(ar);
			m_sprintpointsFinish.Serialize(ar);
			ar << m_sprintpointsCount;
			m_idSprints.Serialize(ar);

			m_pointspointsFinish.Serialize(ar);
			m_idPoints.Serialize(ar);

			m_bonusesIntermediate.Serialize(ar);
			m_bonusesFinish.Serialize(ar);
			ar << m_bonusesCount;

			m_mostaggressivepoints.Serialize(ar);
			m_idMostAggressive.Serialize(ar);
		// Data
			POSITION pos;
			//Bonuses
			ar << m_bonuses.GetCount();
			pos = m_bonuses.GetHeadPosition();
			while( pos )
			{
				CArrivalList aArrL;
				aArrL = m_bonuses.GetNext( pos );
				aArrL.Serialize(ar);
			}
			//Sprints
			ar << m_sprints.GetCount();
			pos = m_sprints.GetHeadPosition();
			while( pos )
			{
				CArrivalList aArrL;
				aArrL = m_sprints.GetNext( pos );
				aArrL.Serialize(ar);
			}
			//Climbs
			ar << m_climbs.GetCount();
			pos = m_climbs.GetHeadPosition();
			while( pos )
			{
				CArrivalList aArrL;
				aArrL = m_climbs.GetNext( pos );
				aArrL.Serialize(ar);
			}
			//Most aggressive
			m_mostaggressive.Serialize(ar);

		// SignOuts list
			m_signOuts.Serialize(ar);
			m_idCrossOut.Serialize(ar);
			m_idSignIn.Serialize(ar);
			m_idGeneralStaNoSorted.Serialize(ar);

		// Correction list
			m_correction.Serialize(ar);

		// Time trial
		ar << (int)m_stageType;
		m_idStartList.Serialize(ar);

		// Various
		ar  << m_distance
			<< m_openingHour
			<< m_rounds
			<< m_title;

		ar << (int) m_exclude;
		ar << (int) m_oneForTeamsClass;
		ar << (int) m_allowLateChangesStartOrder;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////

		if( *(int*)(ar.m_pDocument) >= 3020 )
		{ // FILE STRUCTURE AVAILABLE SINCE 3.02

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idMask4gen.Serialize(ar);
				m_idMask5gen.Serialize(ar);
				m_idMask6gen.Serialize(ar);
				m_idMask7gen.Serialize(ar);
				m_idMask8gen.Serialize(ar);
				m_idMask9gen.Serialize(ar);
				m_idMask10gen.Serialize(ar);
				m_idMask1stage.Serialize(ar);
				m_idMask2stage.Serialize(ar);
				m_idMask3stage.Serialize(ar);
				m_idMask4stage.Serialize(ar);
				m_idMask5stage.Serialize(ar);
				m_idMask6stage.Serialize(ar);
				m_idMask7stage.Serialize(ar);
				m_idMask8stage.Serialize(ar);
				m_idMask9stage.Serialize(ar);
				m_idMask10stage.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				m_climbpointshc.Serialize(ar);
				m_climbpoints1.Serialize(ar);
				m_climbpoints2.Serialize(ar);
				m_climbpoints3.Serialize(ar);
				m_climbpoints4.Serialize(ar);
				m_climbsorder.Serialize(ar);
				m_idClimbs.Serialize(ar);

				m_sprintpointsIntermediate.Serialize(ar);
				m_sprintpointsFinish.Serialize(ar);
				ar >> m_sprintpointsCount;
				m_idSprints.Serialize(ar);

				m_pointspointsFinish.Serialize(ar);
				m_idPoints.Serialize(ar);

				m_bonusesIntermediate.Serialize(ar);
				m_bonusesFinish.Serialize(ar);
				ar >> m_bonusesCount;

				m_mostaggressivepoints.Serialize(ar);
				m_idMostAggressive.Serialize(ar);
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}
				//Most aggressive
				m_mostaggressive.Serialize(ar);

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);
				m_idSignIn.Serialize(ar);
				m_idGeneralStaNoSorted.Serialize(ar);

			// Correction list
				m_correction.Serialize(ar);

			// Time trial
			int tt;
			ar >> tt;
			m_stageType = (STAGETYPES)tt;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> m_openingHour
				>> m_rounds
				>> m_title;

			int ex;
			ar >> ex;
			m_exclude = (ex>0);
			ar >> ex;
			m_oneForTeamsClass = (ex>0);
			ar >> ex;
			m_allowLateChangesStartOrder = (ex>0);
		}
		else if( *(int*)(ar.m_pDocument) >= 3000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 3.00

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idMask4gen.Serialize(ar);
				m_idMask5gen.Serialize(ar);
				m_idMask6gen.Serialize(ar);
				m_idMask7gen.Serialize(ar);
				m_idMask8gen.Serialize(ar);
				m_idMask9gen.Serialize(ar);
				m_idMask10gen.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				m_climbpointshc.Serialize(ar);
				m_climbpoints1.Serialize(ar);
				m_climbpoints2.Serialize(ar);
				m_climbpoints3.Serialize(ar);
				m_climbpoints4.Serialize(ar);
				m_climbsorder.Serialize(ar);
				m_idClimbs.Serialize(ar);

				m_sprintpointsIntermediate.Serialize(ar);
				m_sprintpointsFinish.Serialize(ar);
				ar >> m_sprintpointsCount;
				m_idSprints.Serialize(ar);

				m_pointspointsFinish.Serialize(ar);
				m_idPoints.Serialize(ar);

				m_bonusesIntermediate.Serialize(ar);
				m_bonusesFinish.Serialize(ar);
				ar >> m_bonusesCount;

				m_mostaggressivepoints.Serialize(ar);
				m_idMostAggressive.Serialize(ar);
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}
				//Most aggressive
				m_mostaggressive.Serialize(ar);

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);
				m_idSignIn.Serialize(ar);
				m_idGeneralStaNoSorted.Serialize(ar);

			// Correction list
				m_correction.Serialize(ar);

			// Time trial
			int tt;
			ar >> tt;
			m_stageType = (STAGETYPES)tt;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> m_openingHour
				>> m_rounds
				>> m_title;

			int ex;
			ar >> ex;
			m_exclude = (ex>0);
			ar >> ex;
			m_oneForTeamsClass = (ex>0);
			ar >> ex;
			m_allowLateChangesStartOrder = (ex>0);
		}
		else if( *(int*)(ar.m_pDocument) >= 2030 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.03

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				m_climbpoints1.Serialize(ar);
				m_climbpoints2.Serialize(ar);
				m_climbpoints3.Serialize(ar);
				m_climbpoints4.Serialize(ar);
				m_climbsorder.Serialize(ar);
				m_idClimbs.Serialize(ar);

				m_sprintpointsIntermediate.Serialize(ar);
				m_sprintpointsFinish.Serialize(ar);
				ar >> m_sprintpointsCount;
				m_idSprints.Serialize(ar);

				m_pointspointsFinish.Serialize(ar);
				m_idPoints.Serialize(ar);

				m_bonusesIntermediate.Serialize(ar);
				m_bonusesFinish.Serialize(ar);
				ar >> m_bonusesCount;
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);
				m_idSignIn.Serialize(ar);

			// Correction list
				m_correction.Serialize(ar);

			// Time trial
			int tt;
			ar >> tt;
			m_stageType = (STAGETYPES)tt;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> m_openingHour
				>> m_rounds
				>> m_title;

			int ex;
			ar >> ex;
			m_exclude = (ex>0);
			ar >> ex;
			m_oneForTeamsClass = (ex>0);
		}
		else if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				m_climbpoints1.Serialize(ar);
				m_climbpoints2.Serialize(ar);
				m_climbpoints3.Serialize(ar);
				m_climbpoints4.Serialize(ar);
				m_climbsorder.Serialize(ar);
				m_idClimbs.Serialize(ar);

				m_sprintpointsIntermediate.Serialize(ar);
				m_sprintpointsFinish.Serialize(ar);
				ar >> m_sprintpointsCount;
				m_idSprints.Serialize(ar);

				m_pointspointsFinish.Serialize(ar);
				m_idPoints.Serialize(ar);

				m_bonusesIntermediate.Serialize(ar);
				m_bonusesFinish.Serialize(ar);
				ar >> m_bonusesCount;
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);

			// Correction list
				m_correction.Serialize(ar);

			// Time trial
			int tt;
			ar >> tt;
			m_stageType = (STAGETYPES)tt;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> m_openingHour
				>> m_rounds
				>> m_title;

			int ex;
			ar >> ex;
			m_exclude = (ex>0);
			ar >> ex;
			m_oneForTeamsClass = (ex>0);
		}
		else if( *(int*)(ar.m_pDocument) >= 1200 )
		{ // FILE STRUCTURE AVAILABLE SINCE 1.20

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				CMap<int,int&,int,int&> temp1;
				CList<int,int&> temp2;
				POSITION nPos;

				//m_climbpoints1.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints1.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints2.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints3.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints4.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints4.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbsorder.Serialize(ar);
				temp2.Serialize(ar);
				nPos = temp2.GetHeadPosition();
				while( nPos )
				{
					WORD wValue = (WORD)temp2.GetNext( nPos );
					m_climbsorder.AddTail( wValue );
				}
				//
				m_idClimbs.Serialize(ar);

				//m_sprintpointsIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_sprintpointsFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsFinish.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//
				int i;
				ar >> i;
				m_sprintpointsCount = (WORD)i;
				m_idSprints.Serialize(ar);

				//m_bonusesIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_bonusesFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesFinish.SetAt(wKey,wValue);
				}
				//
				ar >> i;
				m_bonusesCount = (WORD)i;
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);

			// Time trial
			int tt;
			int nOutdated;
			ar >> tt;
			m_stageType = (tt>0)?ST_TT_GROSS:ST_NORMAL;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> nOutdated
				>> m_openingHour
				>> m_rounds
				>> m_title;

			int ex;
			ar >> ex;
			m_exclude = (ex>0);
		}
		else if( *(int*)(ar.m_pDocument) >= 1070 )
		{ // FILE STRUCTURE AVAILABLE SINCE 1.07

			// Communique
				m_communique.Serialize(ar);

			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);
				m_idGeneral.Serialize(ar);
				m_idStage.Serialize(ar);
				m_idMask1gen.Serialize(ar);
				m_idMask2gen.Serialize(ar);
				m_idMask3gen.Serialize(ar);
				m_idTeams.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				CMap<int,int&,int,int&> temp1;
				CList<int,int&> temp2;
				POSITION nPos;

				//m_climbpoints1.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints1.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints2.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints3.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints4.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints4.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbsorder.Serialize(ar);
				temp2.Serialize(ar);
				nPos = temp2.GetHeadPosition();
				while( nPos )
				{
					WORD wValue = (WORD)temp2.GetNext( nPos );
					m_climbsorder.AddTail( wValue );
				}
				//
				m_idClimbs.Serialize(ar);

				//m_sprintpointsIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_sprintpointsFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsFinish.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//
				int i;
				ar >> i;
				m_sprintpointsCount = (WORD)i;
				m_idSprints.Serialize(ar);

				//m_bonusesIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_bonusesFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesFinish.SetAt(wKey,wValue);
				}
				//
				ar >> i;
				m_bonusesCount = (WORD)i;
			// Data
				int nCount;
				//Bonuses
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_bonuses.AddTail( aArrL );
				}
				//Sprints
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_sprints.AddTail( aArrL );
				}
				//Climbs
				ar >> nCount;

				while( nCount-- )
				{
					CArrivalList aArrL;
					aArrL.Serialize(ar);
					m_climbs.AddTail( aArrL );
				}

			// SignOuts list
				m_signOuts.Serialize(ar);
				m_idCrossOut.Serialize(ar);

			// Time trial
			int tt;
			int nOutdated;
			ar >> tt;
			m_stageType = (tt>0)?ST_TT_GROSS:ST_NORMAL;
			m_idStartList.Serialize(ar);
			// Various
			ar >> m_distance
				>> nOutdated
				>> m_openingHour
				>> m_rounds
				>> m_title;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06

			// Communique
				m_communique.Serialize(ar);

			// Bonuses/sprints/mountain
			// Configuration
				CMap<int,int&,int,int&> temp1;
				CList<int,int&> temp2;
				POSITION nPos;

				//m_climbpoints1.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints1.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints2.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints3.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints3.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbpoints4.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_climbpoints4.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_climbsorder.Serialize(ar);
				temp2.Serialize(ar);
				nPos = temp2.GetHeadPosition();
				while( nPos )
				{
					WORD wValue = (WORD)temp2.GetNext( nPos );
					m_climbsorder.AddTail( wValue );
				}
				//

				//m_sprintpointsIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_sprintpointsFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_sprintpointsFinish.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();

				//m_bonusesIntermediate.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesIntermediate.SetAt(wKey,wValue);
				}
				temp1.RemoveAll();
				//m_bonusesFinish.Serialize(ar);
				temp1.Serialize(ar);
				nPos = temp1.GetStartPosition();
				while( nPos )
				{
					WORD wKey, wValue;
					int  nKey, nValue;
					temp1.GetNextAssoc(nPos,nKey,nValue);

					wKey	= (WORD)nKey;
					wValue	= (WORD)nValue;
					m_bonusesFinish.SetAt(wKey,wValue);
				}
			// Arrival lists
				m_arrival.Serialize(ar);
				m_timeTrialOrder.Serialize(ar);

			int nCount;
			// Bonuses/sprints/mountain
				//Configuration
				//
				int i;
				ar >> i;
				m_sprintpointsCount = (WORD)i;
				ar >> i;
				m_bonusesCount = (WORD)i;
				//Data
					//Bonuses
					ar >> nCount;

					while( nCount-- )
					{
						CArrivalList aArrL;
						aArrL.Serialize(ar);
						m_bonuses.AddTail( aArrL );
					}
					//Sprints
					ar >> nCount;

					while( nCount-- )
					{
						CArrivalList aArrL;
						aArrL.Serialize(ar);
						m_sprints.AddTail( aArrL );
					}
					//Climbs
					ar >> nCount;

					while( nCount-- )
					{
						CArrivalList aArrL;
						aArrL.Serialize(ar);
						m_climbs.AddTail( aArrL );
					}

				// SignOuts list
				m_signOuts.Serialize(ar);

			//
			int tt;
			int nOutdated;
			ar >> tt
				>> m_distance
				>> nOutdated
				>> m_openingHour
				>> m_rounds
				>> m_title;
			ar >> tt;
			m_stageType = (tt>0)?ST_TT_GROSS:ST_NORMAL;
		}
	}

}

//////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////

int CHalfStage::Edit( CFullStage* objFullStage, HANDLE hSemaphore )
{
	// We construct a property sheet for multiple tabs
	CPropertySheet dlgPropertySheet( LoadStr( IDS_DIV1 ) );
	dlgPropertySheet.m_psh.dwFlags = dlgPropertySheet.m_psh.dwFlags | PSH_NOAPPLYNOW;

	// We add tabs here
	CHalfStageTrialDat dlgTrialDat;
	dlgTrialDat = (*this);
	dlgTrialDat.m_date = objFullStage->m_date;
	dlgPropertySheet.AddPage(&dlgTrialDat);

	CBonusDat dlgBonus;
	dlgBonus = (*this);
	dlgPropertySheet.AddPage(&dlgBonus);

	CSprintDat dlgSprint;
	dlgSprint = (*this);
	dlgPropertySheet.AddPage(&dlgSprint);
	
	CPointsDat dlgPoints;
	dlgPoints = (*this);
	dlgPropertySheet.AddPage(&dlgPoints);
	
	CMountainDat dlgMountain;
	dlgMountain = (*this);
	dlgPropertySheet.AddPage(&dlgMountain);

	CMostAggressiveDat dlgMostAggressive;
	dlgMostAggressive = (*this);
	dlgPropertySheet.AddPage(&dlgMostAggressive);

	if ( dlgPropertySheet.DoModal() == IDOK )
	{
		if( hSemaphore )
			WaitForSingleObject(hSemaphore,INFINITE);

		(*this) = dlgTrialDat;
		(*this) = dlgBonus;
		(*this) = dlgSprint;
		(*this) = dlgMountain;
		(*this) = dlgPoints;
		(*this) = dlgMostAggressive;

		if( hSemaphore )
			ReleaseSemaphore(hSemaphore,1,NULL);

		return IDOK;
	}
	return IDCANCEL;
}

bool CHalfStage::InputArrivalSet(WORD nStaNo, WORD nRank, DWORD nUnits, CStaNoObjectList* pAvail)
{
	// Determine which list of competitors to use as a source
	// for the available list
		const CAvailableList* pAvailList = NULL;
		if ( m_stageType == ST_NORMAL )
			pAvailList = new CAvailableList( &m_signOuts, pAvail );
		else
			pAvailList = new CAvailableList( &m_signOuts, &m_timeTrialOrder, pAvail );
	
	// Test if valid rank
	if( nRank )
	{
		// See if this competitor exists
		if( pAvailList->Exist( nStaNo ) )
		{
			CArrival aArr;

			// Get the start info
			aArr = pAvailList->GetAt( nStaNo );
			// Fill in the rank
			aArr.m_rank = nRank;
			// Fill in the time
			if( m_stageType == ST_TT_GROSS )
				aArr.SetArrival( nUnits );
			else
				aArr.m_units = nUnits;

			// Store the arrival
			m_arrival.Insert( aArr );

			m_bWorkPendingForTimingIdle = true;
		}
		else
			// Competitor does not exist
			return false;

		return true;
	}
	else
		// Rank is invalid
		return false;
}

bool CHalfStage::InputArrivalSetByTime(WORD nStaNo, DWORD nUnits, CStaNoObjectList* pAvail)
{
	// Determine which list of competitors to use as a source
	// for the available list
		const CAvailableList* pAvailList = NULL;
		if ( m_stageType == ST_NORMAL )
			pAvailList = new CAvailableList( &m_signOuts, pAvail );
		else
			pAvailList = new CAvailableList( &m_signOuts, &m_timeTrialOrder, pAvail );
	
	// See if this competitor exists
	if( pAvailList->Exist( nStaNo ) )
	{
		CArrival aArr;

		// Get the start info
		aArr = pAvailList->GetAt( nStaNo );
		// Fill in the time
		if( m_stageType == ST_TT_GROSS )
			aArr.SetArrival( nUnits );
		else
			aArr.m_units = nUnits;

		// Store the arrival
		m_arrival.Insert( aArr );

		// Calculate the time trial ranking
		m_arrival.ApplyTimeTrialRanks();

		m_bWorkPendingForTimingIdle = true;
	}
	else
		// Competitor does not exist
		return false;

	return true;
}

bool CHalfStage::InputOnTimingIdle()
{
	if( m_bWorkPendingForTimingIdle )
	{
		if( m_stageType == ST_NORMAL )
			m_arrival.ApplyGroupTime(1);

		// Calculate the time trial ranking
		m_arrival.ApplyRanks(m_stageType!=ST_NORMAL);

		// Add finish bonus data and finish sprints data to the arrival list
		m_arrival.AwardPoints( m_sprintpointsCount?&m_sprintpointsFinish:NULL );
		m_arrival.AwardBonuses( m_bonusesCount?&m_bonusesFinish:NULL );

		m_bWorkPendingForTimingIdle = false;

		return true;
	}
	return false;
}

bool CHalfStage::InputArrivalReset(WORD nStaNo)
{
	// See if this competitor exists
	if( m_arrival.Exist( nStaNo ) )
	{
		// Remove the arrival
		m_arrival.Remove( nStaNo );

		if( m_stageType != ST_NORMAL )
		{
			// Calculate the time trial ranking
			m_arrival.ApplyTimeTrialRanks();
		}
		// Add finish bonus data and finish sprints data to the arrival list
		m_arrival.AwardPoints( m_sprintpointsCount?&m_sprintpointsFinish:NULL );
		m_arrival.AwardBonuses( m_bonusesCount?&m_bonusesFinish:NULL );
	}
	else
		// Competitor does not exist
		return false;

	return true;
}

int CHalfStage::InputRanking(char nType, const CStaNoObjectList* pAvail, int nAccuracy, const CCompetitorList* pCompReference,
		HANDLE hSemaphore )
{
	// Determine which list of competitors to use as a source
	// for the available list
		const CAvailableList* pAvailList = NULL;
		if ( m_stageType == ST_NORMAL )
			pAvailList = new CAvailableList( &m_signOuts, pAvail );
		else
			pAvailList = new CAvailableList( &m_signOuts, &m_timeTrialOrder, pAvail );

	// We construct a property sheet for multiple tabs
		CSizablePropertySheet dlgPropertySheet( LoadStr( IDS_DIV45 ), TEXT("Arrival list") );
		if ( m_stageType!=ST_NORMAL )	dlgPropertySheet.SetTitle( LoadStr( IDS_DIV38 ) );
		if ( nType==1 )					dlgPropertySheet.SetTitle( LoadStr( IDS_DIV42 ) );
		if ( nType==2 )					dlgPropertySheet.SetTitle( LoadStr( IDS_DIV41 ) );
		if ( nType==4 )					dlgPropertySheet.SetTitle( LoadStr( IDS_DIV44 ) );

	// We add the first tab for the actual arrival
		if( (nType!=2) && (nType!=4) )
		{
			m_arrival.ClearDirty();
			switch( m_stageType )
			{
				case ST_NORMAL:
					CListArrival* pLA;
					pLA = new CListArrival( nAccuracy, pAvailList, &m_arrival, false, pCompReference );
					dlgPropertySheet.AddPage( pLA );
					break;
				case ST_TT_GROSS:
					dlgPropertySheet.AddPage( new CListTimeTrialArrivalGross( nAccuracy, pAvailList, &m_arrival, pCompReference ) );
					break;
				case ST_TT_NET:
					dlgPropertySheet.AddPage( new CListTimeTrialArrivalNet( nAccuracy, pAvailList, &m_arrival, pCompReference ) );
					break;
			}
		}

	int nIDCounter;
	POSITION nPos;
	// We add a tab for every bonus sprint
		if( nType==0 )
		{
			nIDCounter = 0;
			nPos = m_bonuses.GetHeadPosition();
			while( nPos )
				// We add the tab
				dlgPropertySheet.AddPage(
					new CListArrival( nAccuracy,
							pAvailList,
							&m_bonuses.GetNext( nPos ),
							true,
							pCompReference,
							IDS_BONUS1 + nIDCounter++
						)
					);
		}

	// We add a tab for every points sprint
		if( nType==1 )
		{
			nIDCounter = 0;
			nPos = m_sprints.GetHeadPosition();
			while( nPos )
				// We add the tab
				dlgPropertySheet.AddPage(
					new CListArrival( nAccuracy,
							pAvailList,
							&m_sprints.GetNext( nPos ),
							true,
							pCompReference,
							IDS_SPRINT1 + nIDCounter++
						)
					);
		}

	// We add a tab for every hill climb
		if( nType==2 )
		{
			nIDCounter = 0;
			nPos = m_climbs.GetHeadPosition();
			while( nPos )
				// We add the tab
				dlgPropertySheet.AddPage(
					new CListArrival( nAccuracy,
							pAvailList,
							&m_sprints.GetNext( nPos ),
							true,
							pCompReference,
							IDS_CLIMB1 + nIDCounter++
						)
					);
		}

	// We add a tab for the most aggressive rider competition
		if( nType==4 )
		{
			dlgPropertySheet.AddPage(
				new CListArrival( nAccuracy,
						pAvailList,
						&m_mostaggressive,
						true,
						pCompReference,
						IDS_DIV44
					)
				);
		}

	// Add a corrections tab
		if( (nType==0)||(nType==3) )
			// We add the tab
			dlgPropertySheet.AddPage(
				new CListCorrection( pAvailList,
							&m_correction,
							pCompReference
						)
					);

	// Delete the CAvailableList, since all tabs have been filled
		if( pAvailList ) delete pAvailList;
	// Make sure messages can be tracked
		((CMainFrame*)AfxGetMainWnd())->m_pDlgCurrentlyRunning = dlgPropertySheet.GetPage( 0 );

	// Run the complete multi-tab dialog
		if ( dlgPropertySheet.DoModal() == IDOK )
		{
			// Stop message tracking in first sheet
				((CMainFrame*)AfxGetMainWnd())->m_pDlgCurrentlyRunning = NULL;

			if( hSemaphore )
				WaitForSingleObject(hSemaphore,INFINITE);

			int nTabPointer = 0;
			CAllListPages* pDlgListArr;
			// Fill the document half stage with the arrival list
				if( (nType!=2) && (nType!=4) )
				{
					pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
					if( pDlgListArr->m_listArrival.IsDirty() )
					{
						if( m_arrival.IsDirty() )
						{
							if( MessageBox( NULL, LoadStr( IDS_MBC_58 ), LoadStr( IDS_MBT_58 ), MB_YESNO|MB_DEFBUTTON2 ) == IDYES )
								// Copy the dialog arrival list into the document
								m_arrival = pDlgListArr->m_listArrival;
						}
						else
							// Copy the dialog arrival list into the document
							m_arrival = pDlgListArr->m_listArrival;
					}
					// Add finish bonus data and finish sprints data to the arrival list
					m_arrival.AwardPoints( m_sprintpointsCount?&m_sprintpointsFinish:NULL );
					m_arrival.AwardBonuses( m_bonusesCount?&m_bonusesFinish:NULL );
					delete pDlgListArr;
				}

			// Fill the half stage bonuses lists
				if( nType==0 )
				{
					// We step through the bonus configuration list and the bonus arrival list side by side
					nPos = m_bonuses.GetHeadPosition();
					while( nPos )
					{
						pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
						// Copy the dialog bonus arrival list into the document
						m_bonuses.SetAt( nPos, pDlgListArr->m_listArrival );
						// Add finish bonus data to the arrival list
						m_bonuses.GetNext( nPos ).AwardBonuses( &m_bonusesIntermediate );
						delete pDlgListArr;
					}
				}

			// Fill the half stage sprints lists
				if( nType==1 )
				{
					// We step through the sprint configuration list and the sprint arrival list side by side
					nPos = m_sprints.GetHeadPosition();
					while( nPos )
					{
						pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
						// Copy the dialog bonus arrival list into the document
						m_sprints.SetAt( nPos, pDlgListArr->m_listArrival );
						// Add finish sprint data to the arrival list
						m_sprints.GetNext( nPos ).AwardPoints( &m_sprintpointsIntermediate );
						delete pDlgListArr;
					}
				}

			// Fill the half stage climbs lists
				if( nType==2 )
				{
					// We step through the climbs configuration list and the climbs arrival list side by side
					nPos = m_climbs.GetHeadPosition();
					POSITION nPosPoints = m_climbsorder.GetHeadPosition();
					while( nPos&&nPosPoints )
					{
						// Determine which points scheme to use
						CMap<WORD,WORD&,WORD,WORD&>* pPointsClimb;
						switch( m_climbsorder.GetNext( nPosPoints ) )
						{
							case 1:  pPointsClimb = &(m_climbpoints1); break;
							case 2:  pPointsClimb = &(m_climbpoints2); break;
							case 3:  pPointsClimb = &(m_climbpoints3); break;
							case 4:  pPointsClimb = &(m_climbpoints4); break;
							case 0:
							default: pPointsClimb = &(m_climbpointshc);
						}

						pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
						// Copy the dialog climb arrival list into the document
						m_climbs.SetAt( nPos, pDlgListArr->m_listArrival );
						// Add finish climb data to the arrival list in the climb dialog
						m_climbs.GetNext( nPos ).AwardPoints( pPointsClimb );
						delete pDlgListArr;
					}
				}

			// Fill the half stage most aggressive rider list
				if( nType==4 )
				{
					pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
					// Copy the dialog most aggressive list into the document
					m_mostaggressive = pDlgListArr->m_listArrival;
					// Add points to the arrival list in the most aggressive dialog
					m_mostaggressive.AwardPoints( &m_mostaggressivepoints );
					delete pDlgListArr;
				}

			// Fill the half stage correction list
				if( (nType==0)||(nType==3) )
				{
					pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
					*this = *(CListCorrection*)pDlgListArr;
					delete pDlgListArr;
				}


			if( hSemaphore )
				ReleaseSemaphore(hSemaphore,1,NULL);

			return IDOK;
		}
		else
		{
			// Stop message tracking in first sheet
			((CMainFrame*)AfxGetMainWnd())->m_pDlgCurrentlyRunning = NULL;

			// Clean up all tabs
			int nTabPointer = 0;
			CAllListPages* pDlgListArr;
			while( nTabPointer < dlgPropertySheet.GetPageCount() )
			{
				pDlgListArr = (CAllListPages*) dlgPropertySheet.GetPage( nTabPointer++ );
				delete pDlgListArr;
			}
		}
	return IDCANCEL;
}

int CHalfStage::InputStartingOrder(const CStaNoObjectList* pAvail, const CCompetitorList* pCompReference,
	HANDLE hSemaphore,
	const CDistributedClassification* pPreviousHS/*=NULL*/,
	const CDistributedClassification* pPreviousFS/*=NULL*/ )
{
	// Determine which list of competitors to use as a source
	// for the available list
		const CAvailableList* pAvailList = NULL;
		pAvailList = new CAvailableList( &m_signOuts, pAvail );

	// We construct a property sheet for multiple tabs
		CSizablePropertySheet dlgPropertySheet( LoadStr( IDS_DIV38 ), TEXT("Starting order") );
	
	// We add the first tab for the actual arrival
		CListTimeTrialOrder dlgOrder( pAvailList,
										&m_timeTrialOrder,
										&m_arrival,
										pCompReference,
										pPreviousHS,
										pPreviousFS,
										m_allowLateChangesStartOrder );
		dlgPropertySheet.AddPage( dlgOrder );

	// Delete the CAvailableList, since all tabs have been filled
		if( pAvailList ) delete pAvailList;

	// Run the complete multi-tab dialog
		if ( dlgPropertySheet.DoModal() == IDOK )
		{
			if( hSemaphore )
				WaitForSingleObject(hSemaphore,INFINITE);

			m_timeTrialOrder = dlgOrder.m_listArrival;

			// Here goes the new feature for V2005 that allows changes
			// to the starting order, even when competitors are ranked
			// already

			if( OrderInvolvesArrival() )
			{
				// Walk through every competitor that is already
				// ranked for this time trial
				POSITION pos = m_arrival.GetStartPosition();
				CArrival arr_ranked, arr_order;
				while( pos )
				{
					// Get an arrival and the corresponding order record
					m_arrival.Iterate(pos, arr_ranked);
					arr_order = m_timeTrialOrder.GetAt(arr_ranked.m_staNo);
					// Update the order
					arr_ranked.m_order = arr_order.m_order;
					// Update the time, according to the type of time trial
					if( m_stageType==ST_TT_GROSS )
					{
						arr_ranked.CorrectStartGross( arr_order );
					}
					else // if( m_stageType==ST_TT_NET )
					{
						arr_ranked.CorrectStartNet( arr_order );
					}
					// Put the arrival back in
					m_arrival.Insert(arr_ranked);
				}
				// Make sure also ranks get updated accordingly
				m_arrival.ApplyTimeTrialRanks();
			}
			
			// End new feature

			if( hSemaphore )
				ReleaseSemaphore(hSemaphore,1,NULL);

			return IDOK;
		}

	return IDCANCEL;
}

int CHalfStage::InputSignOuts(const CStaNoObjectList *pAvail,
							  const CMultiLanguage::REQUIREDLANGUAGES* pLang,
							  const CCompetitorList* pCompReference,
							  HANDLE hSemaphore)
{
	// Determine which list of competitors to use as a source
	// for the available list
		const CAvailableList* pAvailList = NULL;
		if ( m_stageType==ST_NORMAL )
			pAvailList = new CAvailableList( /*&m_signOuts*/NULL, pAvail );
		else
			pAvailList = new CAvailableList( /*&m_signOuts*/NULL, &m_timeTrialOrder );

	// We construct a property sheet for multiple tabs
		CSizablePropertySheet dlgPropertySheet( LoadStr( IDS_DIV43 ), TEXT("Sign outs") );

	// We add the first tab for the actual signouts
		CListSignOuts dlgSignOuts( pAvailList,
									&m_signOuts,
									pLang,
									pCompReference );
		dlgPropertySheet.AddPage( dlgSignOuts );

	// Delete the CAvailableList, since all tabs have been filled
		if( pAvailList ) delete pAvailList;

	// Run the dialog, if OK, save the data
	if ( dlgPropertySheet.DoModal() == IDOK )
	{
		if( hSemaphore )
			WaitForSingleObject(hSemaphore,INFINITE);

		// Copy the dialog's signouts in the document's half stage
		m_signOuts = dlgSignOuts.m_listSignOuts;

		if( hSemaphore )
			ReleaseSemaphore(hSemaphore,1,NULL);

		return IDOK;
	}
	return IDCANCEL;
}

void CHalfStage::FunctionCheck()
{
	CString checkResult;
	m_arrival.CheckIntegrity( &checkResult );

	CReportDlg dlgRep(checkResult);
	dlgRep.DoModal();
}

void CHalfStage::FunctionGroupt(short nSecs)
{
	m_arrival.ApplyGroupTime(nSecs);
}

bool CHalfStage::FunctionImport(const CStaNoObjectList* pAvail, HANDLE hSemaphore)
{
	// Determine which list of competitors to use as a source
	// for the available list
	const CAvailableList* pAvailList = NULL;
	if ( m_stageType == ST_NORMAL )
		pAvailList = new CAvailableList( &m_signOuts, pAvail );
	else
		pAvailList = new CAvailableList( &m_signOuts, &m_timeTrialOrder );

	CArrivalList listImport;
	if( listImport.Import() )
	{
		if( hSemaphore )
			WaitForSingleObject(hSemaphore,INFINITE);

		m_arrival = listImport;

		CArrival aArr;
		CString cListNotFound;
		m_arrival.LockWrite();
		POSITION nPos = m_arrival.GetStartPosition();
		while( nPos )
		{
			m_arrival.Iterate( nPos, aArr );
			if( !pAvailList->Exist(aArr.m_staNo) )
			{
				m_arrival.Remove( aArr.m_staNo, true );

				// We add the faulty StaNo to the string
				if( cListNotFound.GetLength() )
					cListNotFound = cListNotFound + ", ";
				TCHAR czBuffer[10];
				_itot( aArr.m_staNo, czBuffer, 10 );
   				cListNotFound = cListNotFound + CString(czBuffer);
			}
		}
		m_arrival.UnlockWrite();

		if( hSemaphore )
			ReleaseSemaphore(hSemaphore,1,NULL);

		// DISPLAY IMPORTED STANO's WHICH DO NOT EXIST
		if( cListNotFound.GetLength() )
			MessageBox( NULL, LoadStr( IDS_MBC_44 ) + "\r\n\r\n" + cListNotFound, LoadStr( IDS_MBT_44 ), MB_OK );

		delete pAvailList;
		return true;
	}
	delete pAvailList;
	return false;
}

void CHalfStage::FunctionRemove1xseconds()
{
	m_arrival.Remove1XSeconds();
}

void CHalfStage::FunctionRemovegaps()
{
	m_arrival.RemoveGapsRanking();
}

void CHalfStage::Generate(int nFS, int nHS, CClassification *pClass, CTeamClassification *pTeam/*=NULL*/, CPointsClassification *pPoints/*=NULL*/, CSprintClassification *pSprint/*=NULL*/)
{
	ASSERT(pClass);

	// Here we calculate this stage's classification
	DWORD nState = 0;
	CArrival objArrival;

	while( m_arrival.IterateSortedUncut( nState, objArrival ) )
	{
		if( m_stageType==ST_NORMAL )
			objArrival.m_units = (objArrival.m_units/1000)*1000;

		// Every ranking from the arrival list is added to the classification

		// Before doing so, we check the presence of this competitor in the bonuses
		POSITION nPos = m_bonuses.GetHeadPosition();
		while( nPos )
		{
			// Within every bonus we check the presence of our current competitor
			if( m_bonuses.GetAt( nPos ).Exist( objArrival.m_staNo ) )
			{
				// If exist, we take the bonuses and add it to the objArrival for the classification
				objArrival.m_bonus +=
					m_bonuses.GetAt( nPos ).GetAt( objArrival.m_staNo ).m_bonus;
			}
			m_bonuses.GetNext( nPos );
		}

		// We also check if there's a correction bonus and add it
		CCorrection aCorr;
		if( m_correction.Exist( objArrival.m_staNo ) )
		{
			aCorr = m_correction.GetAt( objArrival.m_staNo );
			objArrival.m_bonus	+= aCorr.m_bonus;
			objArrival.m_penalty = aCorr.m_penalty;
		}

		// These classes will sort it automatically
		pClass->AddCompetitor( objArrival, m_exclude );

		if( pSprint && objArrival.m_points )
		{
			pSprint->AddCompetitor( objArrival, pClass, nFS, nHS );
		}
	}

	if( pPoints && m_pointspointsFinish.GetCount() )
	{
		POSITION nPos = pClass->m_classification.GetHeadPosition();
 		WORD i = 1;
		while( nPos && i<=m_pointspointsFinish.GetCount() )
		{
			CArrival aArr = pClass->m_classification.GetNext(nPos);
			m_pointspointsFinish.Lookup(i, aArr.m_points);
			pPoints->AddCompetitor( aArr, pClass, nFS, nHS );
			i++;
		}
		pPoints->FinishClassification();
	}

	if( pSprint )
		pSprint->FinishClassification();
	
	if( pTeam )
		pTeam->LoadClassification( pClass, m_oneForTeamsClass );
}

void CHalfStage::PublishTTArrivalList(CStageRaceDoc *pDoc, int nFS, int nHS)
{
	if( m_stageType==ST_TT_GROSS )
	{
		CArray<WORD, WORD> sorted;

		bool bBonus = false;
		bool bPenalty = false;

		DWORD champtime = 0;
		CArrival arr, arrtest;
		// First make a sorted list of staNos
		m_arrival.LockRead();
		POSITION pos = m_arrival.GetStartPosition();
		while( pos )
		{
			m_arrival.Iterate( pos, arr );
			for( int i=sorted.GetSize()-1; i>=0; i-- )
			{
				arrtest = m_arrival.GetAt(sorted.GetAt(i));
				if( arr.m_unitsAtArrival > arrtest.m_unitsAtArrival )
					break;
			}
			sorted.InsertAt(i+1, arr.m_staNo);
			// See if this is the winning time
			if(champtime==0)
				champtime = arr.m_units;
			else
				champtime = min( champtime, arr.m_units );

			// Keep track if there are any bonuses or penalties
			if( arr.m_bonus )
				bBonus = true;
			if( arr.m_penalty )
				bPenalty = true;
		}
		m_arrival.UnlockRead();

		if( sorted.GetSize() )
		{
			// Select the columns to print
			PUBLI_BODYCOLUMNS columns[PUBLI_BODYCOLUMNS_MAX];
			CEventItem::GetPublicationColumns( TI_TTARRIVALLIST, pDoc, columns, ST_TT_GROSS );

			if( !bBonus )
				CEventItem::RemovePublicationColumn( columns, PBC_BONUSES );
			if( !bPenalty )
				CEventItem::RemovePublicationColumn( columns, PBC_PENALTY );

			// Make the html document
			CHtmlDoc objHtml( CEventItem( pDoc, TI_TTARRIVALLIST, nFS, nHS ) );

			// Set the winning time
			champtime = (champtime/1000)*1000;
			objHtml.m_championTime = champtime;

			objHtml.Header(m_idTTArrival.GetNo());

			WORD nStaNo;
			// Use the sorted list of staNos
			for( int i=sorted.GetSize()-1; i>=0; i-- )
			{
				nStaNo = sorted.GetAt(i);
				arr = m_arrival.GetAt(nStaNo);
				objHtml.Competitor( columns, nStaNo, &arr, NULL, true );
			}

			objHtml.Footer(columns);
			objHtml.Finish();
		}
		else
			CHtmlDoc::MakeDummy(
				CEventItem( pDoc, TI_TTARRIVALLIST, nFS, nHS ),
				m_idTTArrival.GetNo() );
	}
}

bool CHalfStage::OrderInvolvesArrival()
{
	return (m_stageType!=ST_NORMAL) && m_allowLateChangesStartOrder;
}
