// StageSpeed.cpp: implementation of the CStageSpeed class.
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

CString CStageSpeed::GetSpeed(int nDistance, DWORD nUnits, bool bKM, bool bMile, char* cSplitter )
{
	if( nDistance && nUnits && (bMile||bKM) )
	{
		CString result;
		if( bKM )
			result = CommaValue( (double)nDistance*((double)3600/nUnits) ) + "km/h";
		if( bKM && bMile )
			result += CString(cSplitter);
		if( bMile )
			result += CommaValue( (double)nDistance*((double)2236.936/nUnits) ) + "mph";
		return result;
	}
	else
		return "n/a";
}
