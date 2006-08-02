// Competitor.cpp: implementation of the CCompetitor class.
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

CCompetitor::CCompetitor()
{
	m_pTeam = NULL;
	m_staNo = 0;
	m_mask1 = FALSE;
	m_mask2 = FALSE;
	m_mask3 = FALSE;
	m_mask4 = FALSE;
	m_mask5 = FALSE;
	m_mask6 = FALSE;
	m_mask7 = FALSE;
	m_mask8 = FALSE;
	m_mask9 = FALSE;
	m_mask10 = FALSE;
}

CCompetitor::~CCompetitor()
{
}

CCompetitor::CCompetitor(const CCompetitor &aComp)
{
	*this = aComp;
}

CCompetitor& CCompetitor::operator =(const CCompetitor & aComp)
{
	m_staNo			= aComp.m_staNo;
	m_competitor	= aComp.m_competitor;
	m_pTeam			= aComp.m_pTeam;
	m_countryCode	= aComp.m_countryCode;
	m_UCICode		= aComp.m_UCICode;
	m_license		= aComp.m_license;
	m_category		= aComp.m_category;
	m_mask1			= aComp.m_mask1;
	m_mask2			= aComp.m_mask2;
	m_mask3			= aComp.m_mask3;
	m_mask4			= aComp.m_mask4;
	m_mask5			= aComp.m_mask5;
	m_mask6			= aComp.m_mask6;
	m_mask7			= aComp.m_mask7;
	m_mask8			= aComp.m_mask8;
	m_mask9			= aComp.m_mask9;
	m_mask10		= aComp.m_mask10;
	return *this;
}

CCompetitor& CCompetitor::operator =(const CEditCompetitor & aComp)
{
	m_staNo = aComp.m_staNo;
	m_competitor = aComp.m_competitor;
	m_pTeam = aComp.m_pTeam;
	m_countryCode = aComp.m_countryCode;
	m_UCICode = aComp.m_UCICode;
	m_license = aComp.m_license;
	m_category = aComp.m_category;
	m_mask1			= aComp.m_mask1;
	m_mask2			= aComp.m_mask2;
	m_mask3			= aComp.m_mask3;
	m_mask4			= aComp.m_mask4;
	m_mask5			= aComp.m_mask5;
	m_mask6			= aComp.m_mask6;
	m_mask7			= aComp.m_mask7;
	m_mask8			= aComp.m_mask8;
	m_mask9			= aComp.m_mask9;
	m_mask10		= aComp.m_mask10;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// Serialization
//////////////////////////////////////////////////////////////////////

void CCompetitor::Serialize(CArchive & ar)
{
	if( ar.IsStoring() )
	{
	////////////
	//STORE FILE
	////////////
		CStaNoObject::Serialize(ar);
		ar << m_competitor << m_pTeam
			<< m_countryCode << m_UCICode
			<< m_license << m_category << m_mask1
			<< m_mask2 << m_mask3 << m_mask4
			<< m_mask5 << m_mask6 << m_mask7
			<< m_mask8 << m_mask9 << m_mask10;
	}
	else
	{
	///////////
	//LOAD FILE
	///////////
		if( *(int*)(ar.m_pDocument) >= 3000 )
		{ // FILE STRUCTURE AVAILABLE SINCE 3.00
			CStaNoObject::Serialize(ar);
			ar >> m_competitor >> m_pTeam
				>> m_countryCode >> m_UCICode
				>> m_license >> m_category >> m_mask1
				>> m_mask2 >> m_mask3 >> m_mask4
				>> m_mask5 >> m_mask6 >> m_mask7
				>> m_mask8 >> m_mask9 >> m_mask10;
		}
		else
		{ // FILE STRUCTURE UP TO 2.00
			if( *(int*)(ar.m_pDocument) >= 2000 )
			{ // FILE STRUCTURE AVAILABLE SINCE 2.00
				CStaNoObject::Serialize(ar);
				ar >> m_competitor >> m_pTeam
					>> m_countryCode >> m_UCICode
					>> m_license >> m_category >> m_mask1
					>> m_mask2 >> m_mask3;
			}
			else
			{ // FILE STRUCTURE UP TO 1.06
				CObject::Serialize(ar);
				int i;
				ar >> i;
				m_staNo = (WORD) i;
				ar >> m_competitor >> m_pTeam
					>> m_countryCode >> m_UCICode
					>> m_license >> m_category >> m_mask1
					>> m_mask2 >> m_mask3;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void CCompetitor::SetMask(char nMask, bool bOn/* = TRUE*/)
{
	switch( nMask )
	{
		case 1:
			m_mask1 = bOn;
			break;
		case 2:
			m_mask2 = bOn;
			break;
		case 3:
			m_mask3 = bOn;
			break;
		case 4:
			m_mask4 = bOn;
			break;
		case 5:
			m_mask5 = bOn;
			break;
		case 6:
			m_mask6 = bOn;
			break;
		case 7:
			m_mask7 = bOn;
			break;
		case 8:
			m_mask8 = bOn;
			break;
		case 9:
			m_mask9 = bOn;
			break;
		case 10:
			m_mask10 = bOn;
			break;
	}
}

int CCompetitor::Edit(const CStageRaceDoc *pDoc)
{
	CEditCompetitor aEditCompetitor;
	// Copy the data from the original to the editable object
	aEditCompetitor=*this;
	//Set the pointer to the document object
	aEditCompetitor.m_pStageRaceDoc = pDoc;

	int ret = aEditCompetitor.DoModal();
	if (ret == IDOK)
	{
		// If evaluated positive:
		
		// Copy the data from the editable object to the original object
		*this=aEditCompetitor;
	}
	return ret;
}

CString CCompetitor::GetClipboardRow()
{
	TCHAR cBuffer[10];
	_itot( m_staNo, cBuffer, 10 );

	return CString(cBuffer) + "\t"
		+ m_competitor + "\t"
		+ (m_pTeam?m_pTeam->m_code:"") + "\t"
		+ m_countryCode + "\t"
		+ m_UCICode + "\t"
		+ m_license + "\t"
		+ m_category + "\t"
		+ (m_mask1?"X":"") + "\t"
		+ (m_mask2?"X":"") + "\t"
		+ (m_mask3?"X":"") + "\t"
		+ (m_mask4?"X":"") + "\t"
		+ (m_mask5?"X":"") + "\t"
		+ (m_mask6?"X":"") + "\t"
		+ (m_mask7?"X":"") + "\t"
		+ (m_mask8?"X":"") + "\t"
		+ (m_mask9?"X":"") + "\t"
		+ (m_mask10?"X":"")
		+ "\r\n";	
}

void CCompetitor::Swap(CCompetitor *pComp)
{
	// Note that the StaNo is not copied
	m_competitor	= pComp->m_competitor;
	m_pTeam			= pComp->m_pTeam;
	m_countryCode	= pComp->m_countryCode;
	m_UCICode		= pComp->m_UCICode;
	m_license		= pComp->m_license;
	m_category		= pComp->m_category;
	m_mask1			= pComp->m_mask1;
	m_mask2			= pComp->m_mask2;
	m_mask3			= pComp->m_mask3;
	m_mask4			= pComp->m_mask4;
	m_mask5			= pComp->m_mask5;
	m_mask6			= pComp->m_mask6;
	m_mask7			= pComp->m_mask7;
	m_mask8			= pComp->m_mask8;
	m_mask9			= pComp->m_mask9;
	m_mask10		= pComp->m_mask10;
}

