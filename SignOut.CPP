// SignOut.cpp: implementation of the CSignOut class.
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

CSignOut::CSignOut()
{

}

CSignOut::~CSignOut()
{

}

CSignOut& CSignOut::operator =(const CSignOut &aSignOut)
{
	this->m_reasonOfSignOut = aSignOut.m_reasonOfSignOut;
	this->m_staNo = aSignOut.m_staNo;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CSignOut::Serialize(CArchive & ar)
{
	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		CStaNoObject::Serialize(ar);
		ar << m_reasonOfSignOut;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 2000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 2.00
			CStaNoObject::Serialize(ar);
			ar >> m_reasonOfSignOut;
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			CObject::Serialize(ar);
			int i;
			ar >> i;
			m_staNo = (WORD) i;
			ar >> m_reasonOfSignOut;
		}
	}
}
