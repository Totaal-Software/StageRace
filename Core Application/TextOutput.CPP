// TextOutput.cpp: implementation of the CTextOutput class.
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

CTextOutput::CTextOutput(CString czPath, CString czDocTitle, int nType, CStageRaceDoc *pTheDoc)
{
	// Save for further use
	m_title = czDocTitle;
	m_type = nType;
	m_pDocument = pTheDoc;

	// First we set up the file name
	CString strFileName = m_pDocument->GetTitle();
	// If the title includes an extension, we get rid of that extension
	if( (m_pDocument->GetTitle().Right( 4 ) == ".str") ||
		(m_pDocument->GetTitle().Right( 4 ) == ".STR") ) strFileName = strFileName.Left( strFileName.GetLength()-4 );
	strFileName = strFileName + " - " + m_title;
	switch( m_type )
	{
		case 1: strFileName = strFileName + " (OPTIc).txt"; break;
		case 2: strFileName = strFileName + " (ChronX).txt"; break;
		case 3: strFileName = "LstConc.txt"; break;
		case 4: strFileName = strFileName + " (TTWare).csv"; break;
	}
	strFileName = czPath + strFileName;

	// We create a file with this new name

	CFileException objFileException;

	// We open the new file
	if ( !m_objTheFile.Open( strFileName, CFile::modeCreate |   
			CFile::typeText | CFile::modeReadWrite | CFile::shareDenyWrite, &objFileException ))
	{
		MessageBox( NULL, LoadStr( IDS_MBC_7 )+strFileName, LoadStr( IDS_MBT_7 ), MB_OK );
		m_openSuccess = false;
	}
	else
	{
		m_openSuccess = true;
		if( m_type==3 )
			m_objTheFile.WriteString( TEXT("\"idBib\";\"Bib\";\"Prénom\";\"Nom\";\"AbrevNat\";\"AbrevCat\";\"BirthDate\";\"Licence\"\n") );
	}
}

CTextOutput::~CTextOutput()
{

}

void CTextOutput::AlgeOpticFormat(CCompetitor *aComp)
{
	if( !m_openSuccess )
		return;

	TCHAR buffer[10];
	_itot( aComp->m_staNo, buffer, 10 );

	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  1	COL_RANK
	m_objTheFile.WriteString( CString(buffer) + TEXT("\t") );					// Spalte  2	COL_BIB
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  3	COL_LANE
	m_objTheFile.WriteString( aComp->m_competitor + TEXT("\t") );				// Spalte  4	COL_LASTNAME
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  5	COL_FIRSTNAME
	if( aComp->m_pTeam )
		m_objTheFile.WriteString( aComp->m_pTeam->m_code + "\t" );	// Spalte  6	COL_CLUB
	else
		m_objTheFile.WriteString( TEXT("\t") );
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  7	COL_AGE
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  8	COL_STRING_TIME
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte  9	COL_BMPPOS
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 10	COL_INT_TIME
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 11	COL_PICNUM
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 12	COL_INDEX
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 13	COL_DISTANCE
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 14	COL_T_KM
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 15	COL_KM_H
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 16	COL_DELTA_TIME
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 17	COL_INT_TIME_ROUNDED
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 18	COL_HORSE_UNITS
	m_objTheFile.WriteString( TEXT("\t") );									// Spalte 19	COL_MISSING_LAPS
	m_objTheFile.WriteString( TEXT("\n") );									// Spalte 20	COL_RESERVED1
}

void CTextOutput::AmbChronxFormat(CCompetitor *aComp)
{
	if( !m_openSuccess )
		return;

	CString cEvent = m_pDocument->GetTitle();
	if( (m_pDocument->GetTitle().Right( 4 ) == ".str") ||
		(m_pDocument->GetTitle().Right( 4 ) == ".STR") ) cEvent = cEvent.Left( cEvent.GetLength()-4 );
	
	TCHAR buffer[10];
	_itot( aComp->m_staNo, buffer, 10 );

	m_objTheFile.WriteString( CString(buffer) + TEXT(",") );										// UniqueID
	m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_competitor ) + TEXT("\",") );				// FirstName
	m_objTheFile.WriteString( TEXT("\"\",") );													// LastName
	m_objTheFile.WriteString( CString(buffer) + "," );										// TranNo
	m_objTheFile.WriteString( TEXT("\"") + CString(buffer) + TEXT("\",") );								// CarNo
	m_objTheFile.WriteString( TEXT("\"") + m_title + " (" + NoQuotes( cEvent ) + TEXT(")\",") );		// Class
	m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_countryCode ) + TEXT("\",") );			// Nat
	if( aComp->m_pTeam )
		m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_pTeam->m_name ) + TEXT("\",") );		// AddData2
	else
		m_objTheFile.WriteString( TEXT("\"\",") );												// AddData2
	m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_UCICode ) + TEXT("\"") );					// RegNo
	m_objTheFile.WriteString( TEXT("\n") );
}

void CTextOutput::Finish()
{
	if( !m_openSuccess )
		return;

	// We finish the document by writing it to disk
	m_objTheFile.Close();
}

void CTextOutput::Competitor(CCompetitor *aComp, CArrival* aArr/*=NULL*/ )
{
	switch( m_type )
	{
		case 1: AlgeOpticFormat( aComp ); break;
		case 2: AmbChronxFormat( aComp ); break;
		case 3: OmegaScanOVisionFormat( aComp ); break;
		case 4: SkunkwareTTWare( aComp, aArr ); break;
	}
}

void CTextOutput::OmegaScanOVisionFormat(CCompetitor *aComp)
{
	if( !m_openSuccess )
		return;

	TCHAR buffer[10];
	_itot( aComp->m_staNo, buffer, 10 );

	m_objTheFile.WriteString( CString(buffer) + TEXT(";") );								// idBib
	m_objTheFile.WriteString( TEXT("\"") + CString(buffer) + TEXT("\";") );						// Bib
	m_objTheFile.WriteString( TEXT(";") );												// Prénom
	m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_competitor ) + TEXT("\";") );		// Nom
	if( aComp->m_pTeam )
		m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_pTeam->m_code ) + TEXT("\";") );	// AbrevNat
	else
		m_objTheFile.WriteString( TEXT("\"\";") );
	m_objTheFile.WriteString( TEXT(";") );												// AbrevCat
	m_objTheFile.WriteString( TEXT(";") );												// BirthDate
	m_objTheFile.WriteString( TEXT("\"") + NoQuotes( aComp->m_UCICode ) + TEXT("\"") );			// Licence
	m_objTheFile.WriteString( TEXT("\n") );
}

void CTextOutput::SkunkwareTTWare(CCompetitor *pComp, CArrival *pArr)
{
	if( !m_openSuccess )
		return;

	// Start time
	if( pArr )
	{
		m_objTheFile.WriteString(
			CStageTime( pArr->m_unitsAtStart ).GetFormattedSemicolons() );
	}
	m_objTheFile.WriteString( TEXT(",") );

	// Competitor no.
	TCHAR buffer[10];
	_itot( pComp->m_staNo, buffer, 10 );
	m_objTheFile.WriteString( CString(buffer) + TEXT(",") );

	// Name
	m_objTheFile.WriteString( NoCommas( pComp->m_competitor ) + TEXT(",") );

	// Team
	if( pComp->m_pTeam )
	{
		m_objTheFile.WriteString( NoCommas( pComp->m_pTeam->m_code ) + TEXT(",") );
		m_objTheFile.WriteString( NoCommas( pComp->m_pTeam->m_name ) + TEXT(",") );
	}
	else
		m_objTheFile.WriteString( TEXT(",") );

	// Etc.
	m_objTheFile.WriteString( NoCommas( pComp->m_countryCode )+TEXT(",") );
	m_objTheFile.WriteString( NoCommas( pComp->m_category )+TEXT(",") );
	m_objTheFile.WriteString( NoCommas( pComp->m_license )+TEXT(",") );
	m_objTheFile.WriteString( NoCommas( pComp->m_UCICode ) );
	m_objTheFile.WriteString( TEXT("\n") );
}
