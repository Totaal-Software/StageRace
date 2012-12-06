// Communique.cpp: implementation of the CCommunique class.
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

CCommunique::CCommunique()
{

}

CCommunique::~CCommunique()
{

}

CCommunique& CCommunique::operator =(const CCommunique &aComm)
{
	this->m_title = aComm.m_title;
	this->m_contents = aComm.m_contents;
	this->m_date = aComm.m_date;
	this->m_id = aComm.m_id;
	return *this;
}

CCommunique& CCommunique::operator =(const CEditCommunique &aEdit)
{
	this->m_date = aEdit.m_date;
	this->m_title = aEdit.m_title;
	this->m_contents = aEdit.m_contents;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CCommunique::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	if ( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		ar << m_title << m_contents << m_date;
		m_id.Serialize(ar);
	}
	else
	{
	///////////
	//LOAD FILE
	///////////

		if( *(int*)(ar.m_pDocument) >= 1200 )
		{ // FILE STRUCTURE AVAILABLE SINCE 1.20
			ar >> m_title >> m_contents >> m_date;
			m_id.Serialize(ar);
		}
		else if( *(int*)(ar.m_pDocument) >= 1070 )
		{ // FILE STRUCTURE AVAILABLE SINCE 1.07
			ar >> m_title >> m_contents;
			m_id.Serialize(ar);
		}
		else
		{ // FILE STRUCTURE UP TO 1.06
			ar >> m_title >> m_contents;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CCommunique::Empty()
{
	this->m_title.Empty();
	this->m_contents.Empty();
}

bool CCommunique::IsEmpty()
{
	return !(m_contents.GetLength() && m_title.GetLength());
}
