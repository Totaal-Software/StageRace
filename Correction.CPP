// Correction.cpp: implementation of the CCorrection class.
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

CCorrection::CCorrection()
{
	m_bonus = m_penalty = 0;
}

CCorrection::CCorrection(const CCorrection &aCorr)
{
	*this = aCorr;
}

CCorrection& CCorrection::operator =(const CCorrection &aCorr)
{
	this->m_staNo = aCorr.m_staNo;
	this->m_bonus = aCorr.m_bonus;
	this->m_penalty = aCorr.m_penalty;
	return *this;
}

CCorrection& CCorrection::operator =(const CArrival &aArr)
{
	this->m_staNo = aArr.m_staNo;
	this->m_bonus = aArr.m_bonus;
	this->m_penalty = aArr.m_penalty;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CCorrection::Serialize(CArchive &ar)
{
	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		CStaNoObject::Serialize(ar);
		ar << m_bonus << m_penalty;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			CStaNoObject::Serialize(ar);
			ar >> m_bonus >> m_penalty;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CObject::Serialize(ar);
			int i;
			ar >> i;
			m_staNo = (WORD) i;
			ar >> m_bonus >> m_penalty;
		}
	}
}
