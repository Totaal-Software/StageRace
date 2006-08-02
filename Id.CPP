// Id.cpp: implementation of the CId class.
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

CId::CId()
{
	m_nId			= 0;
	m_bPublished	= false;
}

CId& CId::operator =(const CId &aId)
{
	this->m_bPublished	= aId.m_bPublished;
	this->m_nId			= aId.m_nId;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CId::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		ar << m_bPublished << m_nId;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////

		if( *(int*)(ar.m_pDocument) >= 1070 )
		{ // FILE STRUCTURE AVAILABLE SINCE 1.07
			int nPublished;
			ar >> nPublished >> m_nId;
			m_bPublished = nPublished != 0;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

unsigned short CId::GetNo() const
{
	if( m_bPublished )
		return m_nId;
	else
		return 0;
}

BOOL CId::IsPublished() const
{
	return m_bPublished;
}

void CId::SetNo(unsigned short nId)
{
	m_nId = nId;
}
