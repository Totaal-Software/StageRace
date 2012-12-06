// Arrival.cpp: implementation of the CArrival class.
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

CArrival::CArrival()
{
	this->m_pBunch = NULL;
	this->m_pTeam = NULL;
	this->m_units = 0;
	this->m_bonus = 0;
	this->m_penalty = 0;
	this->m_points = 0;
	this->m_thousandth = 0;
	this->m_unitsAtArrival = 0;
	this->m_unitsAtStart = 0;
	this->m_order = 0;
	this->m_sumRank = 0;
	this->m_rank = 0;
}

CArrival::~CArrival()
{
	if( this->m_pBunch )
	{
		delete this->m_pBunch;
		this->m_pBunch = NULL;
	}
}

CArrival::CArrival(const CArrival &aArrival)
{
	if( aArrival.m_pBunch )
		this->m_pBunch		= new CClassification( *aArrival.m_pBunch );
	else
		this->m_pBunch		= NULL;
	this->m_pTeam			= aArrival.m_pTeam;
	this->m_rank			= aArrival.m_rank;
	this->m_sumRank			= aArrival.m_sumRank;
	this->m_staNo			= aArrival.m_staNo;
	this->m_order			= aArrival.m_order;
	this->m_units			= aArrival.m_units;
	this->m_points			= aArrival.m_points;
	this->m_bonus			= aArrival.m_bonus;
	this->m_penalty			= aArrival.m_penalty;
	this->m_thousandth		= aArrival.m_thousandth;
	this->m_unitsAtStart	= aArrival.m_unitsAtStart;
	this->m_unitsAtArrival	= aArrival.m_unitsAtArrival;
}

CArrival& CArrival::operator =(const CArrival & aArriv)
{
	if( aArriv.m_pBunch )
	{
		if( m_pBunch )
			*m_pBunch = *aArriv.m_pBunch;
		else
			m_pBunch = new CClassification( *aArriv.m_pBunch );
	}
	else
	{
		if( m_pBunch )
		{
			delete m_pBunch;
			m_pBunch = NULL;
		}
	}
	this->m_pTeam			= aArriv.m_pTeam;
	this->m_rank			= aArriv.m_rank;
	this->m_sumRank			= aArriv.m_sumRank;
	this->m_staNo			= aArriv.m_staNo;
	this->m_order			= aArriv.m_order;
	this->m_units			= aArriv.m_units;
	this->m_bonus			= aArriv.m_bonus;
	this->m_penalty			= aArriv.m_penalty;
	this->m_points			= aArriv.m_points;
	this->m_thousandth		= aArriv.m_thousandth;
	this->m_unitsAtStart	= aArriv.m_unitsAtStart;
	this->m_unitsAtArrival	= aArriv.m_unitsAtArrival;
	return *this;
}

CArrival& CArrival::operator =(const CCorrection & aCorr)
{
	this->m_staNo			= aCorr.m_staNo;
	this->m_bonus			= aCorr.m_bonus;
	this->m_penalty			= aCorr.m_penalty;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CArrival::Serialize(CArchive & ar)
{
	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		CStaNoObject::Serialize(ar);
		ar << m_rank << m_units;
		ar << m_order << m_unitsAtStart << m_unitsAtArrival << m_bonus /*<< m_penalty*/ << m_points /*<< m_pTeam*/;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			CStaNoObject::Serialize(ar);
			ar >> m_rank >> m_units;
			ar >> m_order >> m_unitsAtStart >> m_unitsAtArrival >> m_bonus >> m_points;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CObject::Serialize(ar);
			int i;
			long l;
			ar >> i;
			m_rank = (WORD)i;
			ar >> i;
			m_staNo = (WORD)i;
			ar >> l;
			m_units = (DWORD)l;
			ar >> i;
			m_order = (WORD)i;
			ar >> l;
			m_unitsAtStart = (DWORD)l;
			ar >> l;
			m_unitsAtArrival = (DWORD)l;
			ar >> i;
			m_bonus = (unsigned short)i;
			ar >> i;
			m_points = (WORD)i;
			ar >> m_pTeam;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

CArrival& CArrival::operator+(const CArrival &aArrival)
{
	this->m_sumRank			+= aArrival.m_rank;
	this->m_units			+= aArrival.m_units;
	this->m_thousandth		+= aArrival.m_thousandth;
	this->m_points			+= aArrival.m_points;
	return *this;
}

DWORD CArrival::SetArrival(DWORD aArrivaltime, bool anticipateTime, DWORD anticipatedTime)
{
	// Save the absolute arrival time, in relation to the first rider
	m_unitsAtArrival = aArrivaltime;

	// If hour indication was forgotten, add it...
	while( aArrivaltime < m_unitsAtStart )
		aArrivaltime += 3600000;

	// Calculate the relative arrival time for this competitor
	m_units = aArrivaltime - m_unitsAtStart;

	if( anticipateTime )
	{
		// Make sure the time is close to the anticipated time
		while( (m_units > anticipatedTime+1800000) &&
				(m_units>3600000) ) // Prevent underflow of units
			m_units -= 3600000;
		while( (anticipatedTime>1800000) && // Prevent underflow of lower limit
				(m_units < anticipatedTime-1800000) )
			m_units += 3600000;
	}

	while( m_units < 0 )
		m_units += 3600000;

	return m_units;
}

void CArrival::SetStart(DWORD aStarttime)
{
	// Save the start time, in relation to the first rider
	m_unitsAtStart = aStarttime;
}

void CArrival::CorrectStartNet(const CArrival &order)
{
	SetStart(order.m_unitsAtStart);
}

void CArrival::CorrectStartGross(const CArrival &order)
{
	// Correct the arrival
	m_units += m_unitsAtStart - order.m_unitsAtStart;
	// Set the start time
	SetStart(order.m_unitsAtStart);
}