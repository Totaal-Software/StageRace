// FullStage.cpp: implementation of the CFullStage class.
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

CFullStage::CFullStage()
{

}

CFullStage::~CFullStage()
{

}

CFullStage& CFullStage::operator =(CFullStage & aFullStage)
{
	this->m_communique = aFullStage.m_communique;
	this->m_date = aFullStage.m_date;

	POSITION thePos = this->m_halfStages.GetHeadPosition();
	while ( thePos != NULL )
	{
		aFullStage.AddHalfStage( &(this->m_halfStages.GetNext( thePos )) );
	};

	return *this;
}

CFullStage& CFullStage::operator =(CFullStageTrialDat & aTrialDat)
{
	this->m_date = aTrialDat.m_date;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CFullStage::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);

	m_communique.Serialize(ar);
	if( ar.IsLoading() )
	{
		ar >> m_date;
		// Half stages
			int nCount;
			ar >> nCount;

			while( nCount-- )
			{
				CHalfStage aHalfStage;
				aHalfStage.Serialize(ar);
				this->AddHalfStage( &aHalfStage );
			}
	}
	else
	{
		ar << m_date;
		// Half stages
			ar << m_halfStages.GetCount();

			POSITION pos = m_halfStages.GetHeadPosition( );

			while ( pos!=NULL )
			{
				CHalfStage aHalfStage;
				aHalfStage = m_halfStages.GetNext( pos );
				aHalfStage.Serialize(ar);
			}
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

int CFullStage::CountHalfStages() const
{
	return m_halfStages.GetCount();
}

int CFullStage::Edit(HANDLE hSemaphore)
{
	CFullStageTrialDat aDlg;
	aDlg = (*this);
	if ( aDlg.DoModal() == IDOK )
	{
		if( hSemaphore )
			WaitForSingleObject(hSemaphore,INFINITE);

		(*this) = aDlg;

		if( hSemaphore )
			ReleaseSemaphore(hSemaphore,1,NULL);
		return IDOK;
	}
	return IDCANCEL;
}

void CFullStage::AddHalfStage(CHalfStage * aNewOne)
{
	m_halfStages.AddTail( *aNewOne );
}

