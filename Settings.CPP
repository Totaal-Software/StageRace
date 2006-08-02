// Settings.cpp: implementation of the CSettings class.
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

CSettings::CSettings()
{
}

CSettings::~CSettings()
{
	// Clear the values list, just to be sure
	for( int i=0; i<m_values.GetSize(); i++ )
		delete m_values.GetAt( i );
	m_values.RemoveAll();
}

CSettings::CSettings(CSettings *pSettings)
{
	*this = *pSettings;
}

void CSettings::ValueAdd(DWORD nID, CSettings::CSetting::SETTINGTYPE type, bool bInitial, int nGroupID/*=0*/, char icon/*=0*/)
{
	CSetting* pSet = new CSetting(bInitial, type, nID, nGroupID, icon);
	int i = m_values.Add( pSet );
	m_availableIDs.SetAt( nID, i );
}

bool CSettings::ValueGetAt( int nIndex, const CSetting** ppSet/*=NULL*/ ) const
{
	CSetting* pSet = (CSetting*)m_values.GetAt( nIndex );
	if( ppSet )
		*ppSet = pSet;
	return pSet->m_bValue;
}

bool CSettings::ValueGet(DWORD nID, const CSetting** ppSet/*=NULL*/) const
{
	int i;
	m_availableIDs.Lookup( nID, i );
	
	return ValueGetAt( i, ppSet );
}

void CSettings::ValueSet(DWORD nID, bool bVal)
{
	int i;
	if( m_availableIDs.Lookup( nID, i ) )
	{
		CSetting* pSet = (CSetting*)m_values.GetAt( i );
		pSet->m_bValue = bVal;
	}
#ifdef _DEBUG
	else
	{
		ASSERT(0);
	}
#endif 
}

void CSettings::Serialize(CArchive &objAr)
{
	// Storage spec here is as follows:
	// [(char)value1][(UINT)id1][(char)value2][(UINT)id2]...[(char)-1]
	CObject::Serialize(objAr);
	if( objAr.IsLoading() )
	{
		char c;
		UINT n;
		objAr>>c;
		while( c!=((char)-1) ) // while values keep coming...
		{
			objAr >> n; // ...we can also keep on getting id's
			ValueSet( n, c==1 );
			objAr>>c;
		}
	}
	else
	{
		for( int i=0; i<m_values.GetSize(); i++ )
		{
			CSetting* pSet = (CSetting*)m_values.GetAt( i );
			objAr << (char)(pSet->m_bValue?1:0);
			objAr << pSet->m_nID;
		}
		objAr << (char)-1;
	}
}

CSettings& CSettings::operator=( const CSettings& s )
{
	// First clear the values list, just to be sure
	for( int i=0; i<m_values.GetSize(); i++ )
		delete m_values.GetAt( i );
	m_values.RemoveAll();

	// Then fill the values list
	for( i=0; i<s.m_values.GetSize(); i++ )
	{
		CSetting* pSet = (CSetting*)s.m_values.GetAt( i );
		ValueAdd( pSet->m_nID, pSet->m_type, pSet->m_bValue, pSet->m_nGroupID, pSet->m_nIcon );
	}

	return *this;
}

char CSettings::IconGet(DWORD nGroup) const
{
	int i;
	m_availableIDs.Lookup( nGroup, i );
	
	const CSetting* pSet;
	ValueGetAt( i, &pSet );
	return pSet->m_nIcon;
}

bool CSettings::ValueExist(DWORD nID) const
{
	int i;
	return m_availableIDs.Lookup( nID, i )==TRUE;
}
