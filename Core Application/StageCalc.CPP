// StageCalc.cpp: implementation of the StageCalc class.
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

CString CStageCalc::CommaValue(double f)
{
	CString cBuffer;
	char* pcBuffer;
	int nDecimals, nSign;

	pcBuffer = _ecvt( f, 10, &nDecimals, &nSign );
	cBuffer = CString(pcBuffer);
	if( nDecimals<=0 )
	{
		cBuffer = "0,"+CString('0',abs(nDecimals))+cBuffer;
		cBuffer = cBuffer.Left( 6 );
	}
	else
	{
		cBuffer = cBuffer.Left( nDecimals ) + "," + cBuffer.Mid( nDecimals, max(0,5-nDecimals) );
	}
	cBuffer.TrimRight('0');
	if( cBuffer.Right(1)==',' ) cBuffer+="0";
	return cBuffer;
}
