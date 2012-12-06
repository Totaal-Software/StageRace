// StaNoObject.cpp: implementation of the CStaNoObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaNoObject::CStaNoObject()
{

}

CStaNoObject::~CStaNoObject()
{

}

CStaNoObject::CStaNoObject(const CStaNoObject &aStaNo)
{
	this->m_staNo = aStaNo.m_staNo;
}

CStaNoObject& CStaNoObject::operator =(const CStaNoObject & aStaNo)
{
	this->m_staNo = aStaNo.m_staNo;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CStaNoObject::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		ar << m_staNo;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			ar >> m_staNo;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			int i;
			ar >> i;
			m_staNo = (WORD) i;
		}
	}
}

