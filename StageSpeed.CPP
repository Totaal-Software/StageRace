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
	nUnits = nUnits / 1000 * 1000;
	if( nDistance && nUnits && (bMile||bKM) )
	{
		float kmh = (double)nDistance*((double)3600/nUnits);
		float mph = (double)nDistance*((double)2236.936/nUnits);
		CString result;
		if(bKM && bMile)
		{
			result.Format(_T("%0.3f km/h%s%0.3f mph"), kmh, CString(cSplitter), mph);
		}
		else if(bKM)
		{
			result.Format(_T("%0.3f km/h"), kmh);
		}
		else
		{
			result.Format(_T("%0.3f mph"), mph);
		}
		return result;
	}
	else
		return "n/a";
}
