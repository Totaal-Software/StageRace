// StageSpeed.h: interface for the CStageSpeed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAGESPEED_H__E231C191_BDB1_4675_ACAA_4DB0472572D3__INCLUDED_)
#define AFX_STAGESPEED_H__E231C191_BDB1_4675_ACAA_4DB0472572D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStageSpeed : CStageCalc
{
public:
	static CString GetSpeed( int nDistance, DWORD nUnits, bool bKM, bool bMile, char* cSplitter = "<BR>" );

};

#endif // !defined(AFX_STAGESPEED_H__E231C191_BDB1_4675_ACAA_4DB0472572D3__INCLUDED_)
