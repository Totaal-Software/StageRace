// Time.cpp: implementation of the CTime class.
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

CStageTime::CStageTime( CString hours="0", CString minutes="0", CString seconds="0", CString thousandth="0" )
{
	m_hours = hours;
	m_minutes = minutes;
	m_seconds = seconds;
	m_thousandth = thousandth;

	m_units = 3600000 * _ttoi( hours ) +
		60000 * _ttoi( minutes ) +
		1000 * _ttoi( seconds ) +
		_ttoi( thousandth );
}

CStageTime::CStageTime( DWORD units )
{

	m_units = units;

	TCHAR   chrBuffer[10];
	CString strBuffer;

	_itot( units / 3600000, chrBuffer, 10 );
	strBuffer    = chrBuffer;
	strBuffer    = "    " + strBuffer;
	m_hours      = strBuffer.Right( 3 );
	for (int i=0; i<=1; i++ ) if ( m_hours.GetAt( i )==' ' ) m_hours.SetAt( i, '0' );
	units        = units % 3600000;

	_itot( units /   60000, chrBuffer, 10 );
	strBuffer    = chrBuffer;
	strBuffer    = " " + strBuffer;
	m_minutes    = strBuffer.Right( 2 );
	if ( m_minutes.GetAt( 0 )==' ' ) m_minutes.SetAt( 0, '0' );
	units        = units %   60000;

	_itot( units /    1000, chrBuffer, 10 );
	strBuffer    = chrBuffer;
	strBuffer    = " " + strBuffer;
	m_seconds    = strBuffer.Right( 2 );
	if ( m_seconds.GetAt( 0 )==' ' ) m_seconds.SetAt( 0, '0' );
	units        = units %    1000;

	_itot( units          , chrBuffer, 10 );
	strBuffer    = chrBuffer;
	strBuffer    = "  " + strBuffer;
	m_thousandth = strBuffer.Right( 3 );
	for (i=0; i<=1; i++ ) if ( m_thousandth.GetAt( i )==' ' ) m_thousandth.SetAt( i, '0' );
}

DWORD CStageTime::GetUnits( CString hours="0", CString minutes="0", CString seconds="0", CString thousandth="0" )
{
	CStageTime s( hours, minutes, seconds, thousandth );
	return s.m_units;
}


CString CStageTime::GetFormatted()
{
	CString res = m_hours;

	res.TrimLeft('0');
	if( !res.GetLength() )
		res = "0";
	res += "." + m_minutes + "'" + m_seconds + "\"";

	return res;
}

CString CStageTime::GetFormattedLefttrimmed()
{
	CString res = m_hours;

	res.TrimLeft('0');
	res += "." + m_minutes + "'" + m_seconds + "\"";

	return res;
}

CString CStageTime::GetFormattedAlllefttrimmed()
{
	if( m_units >= 1000 ) // Second or more
		if( m_units >= 60000 ) // Minute or more
			if( m_units >= 3600000 ) // Hour or more
				return GetFormattedLefttrimmed();
			else
			{
				CString t = m_minutes;
				t.TrimLeft('0');
				return t + "'" + m_seconds + "\"";
			}
		else
		{
			CString t = m_seconds;
			t.TrimLeft('0');
			return t + "\"";
		}
	else
		return "";
}

CString CStageTime::GetFormattedWide()
{
	CString res = m_hours;

	res.TrimLeft('0');
	if( !res.GetLength() )
		res = "0";
	res += ". " + m_minutes + "' " + m_seconds + "\" ";

	return res;
}

CString CStageTime::GetFormattedSemicolons()
{
	CString res = m_hours;

	res.TrimLeft('0');
	if( !res.GetLength() )
		res = "0";
	res += ":" + m_minutes + ":" + m_seconds;

	return res;
}
