// StageDistance.cpp: implementation of the CStageDistance class.
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

CString CStageDistance::DistanceStage(int nRounds, DWORD nDistance, bool bKM, bool bMile, TCHAR* cSplitter)
{
	if( nDistance && (bMile||bKM) )
	{
		CString result;
		if( nRounds == 1 )
			result = DistanceSingle( nDistance, bKM, bMile, cSplitter );
		else
		{
			// We print the nDistance of this stage
			if( bKM )
			{
				TCHAR czBuffer[10];
				// We print the nDistance of this stage
				_itot( nRounds, czBuffer, 10 );
				result += CString(czBuffer) + "R × ";
				result += CommaValue( (double)nDistance/1000 ) + "km/R = ";
				result += CommaValue( (double)nDistance*nRounds/1000 ) + "km";
			}
			if( bKM && bMile )
			{
				result += CString(cSplitter);
			}
			if( bMile )
			{
				TCHAR czBuffer[10];
				// We print the nDistance of this stage
				_itot( nRounds, czBuffer, 10 );
				result += CString(czBuffer) + "R × ";
				result += CommaValue( (double)nDistance/MILESCONVERSION ) + "m/R = ";
				result += CommaValue( (double)nDistance*nRounds/MILESCONVERSION ) + "m";
			}
		}
		return result;
	}
	else
		return "0";
}

CString CStageDistance::DistanceFromTo(DWORD before, DWORD after, bool bKM, bool bMile, TCHAR* cSplitter)
{
	CString result;
	// We print the nDistance of this stage
	if( bKM )
	{
		result = "(" + CommaValue( (double)before/1000 ) + "km &#151; ";
		result += CommaValue( (double)after/1000 ) + "km)";
	}
	if( bKM && bMile )
	{
		result += CString(cSplitter);
	}
	if( bMile )
	{
		result += "(" + CommaValue( (double)before/MILESCONVERSION ) + "m &#151; ";
		result += CommaValue( (double)after/MILESCONVERSION ) + "m)";
	}
	return result;
}

CString CStageDistance::DistanceSingle(DWORD nDistance, bool bKM, bool bMile, TCHAR* cSplitter)
{
	if( nDistance && (bMile||bKM) )
	{
		CString result;
		// We print the nDistance of this stage
		if( bKM )
			result = CommaValue((double)nDistance/1000)+"km";			
		if( bKM && bMile )
			result += CString(cSplitter);
		if( bMile )
			result += CommaValue((double)nDistance/MILESCONVERSION) + "m";
		return result;
	}
	else
		return "0";
}

double CStageDistance::ToMiles(int nDistance)
{
	return (double)nDistance/MILESCONVERSION;
}
