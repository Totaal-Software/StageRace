// Team.cpp: implementation of the CTeam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "incl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL( CTeam, CObject, 1 );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTeam::CTeam()
{

}

CTeam::~CTeam()
{

}

CTeam::CTeam(const CTeam &aTeam)
{
	*this=aTeam;
}


CTeam::CTeam(const CTeam *pTeam)
{
	*this=*pTeam;
}

CTeam& CTeam::operator =(const CTeam &aTeam)
{
	this->m_code	= aTeam.m_code;
	this->m_name	= aTeam.m_name;
	this->m_country	= aTeam.m_country;
	this->m_manager	= aTeam.m_manager;
	return *this;
}

CTeam& CTeam::operator =(const CEditTeam& aTeam)
{
	this->m_code	= aTeam.m_szCode;
	this->m_name	= aTeam.m_szName;
	this->m_manager = aTeam.m_szManager;
	this->m_country = aTeam.m_szCountry;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CTeam::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsLoading())
	{
		ar >> m_country >> m_manager >> m_name >> m_code;
	}
	else
	{
		ar << m_country << m_manager << m_name << m_code;
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

int CTeam::Edit(const CStageRaceDoc *pDoc, HANDLE hSemaphore)
{
	CEditTeam aEditTeam;
	// Copy the data from the original to the editable object
	aEditTeam=*this;
	aEditTeam.m_pTeam = (const CTeam*)this;

	//Set the pointer to the document object
	aEditTeam.m_pStageRaceDoc = pDoc;

	int ret = aEditTeam.DoModal();
	if (ret == IDOK)
	{
		if( hSemaphore )
			WaitForSingleObject(hSemaphore,INFINITE);

		// If evaluated positive:
		
		// Copy the data from the editable object to the original object
		*this=aEditTeam;

		if( hSemaphore )
			ReleaseSemaphore(hSemaphore,1,NULL);
	}
	return ret;
}

CString CTeam::GetClipboardRow()
{
	return m_code + "\t"
		+ m_name + "\t"
		+ m_manager + "\t"
		+ m_country
		+ "\r\n";	
}
