// StageDistance.h: interface for the CStageDistance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAGEDISTANCE_H__9D1513DC_3FB6_45E5_A4D3_53DCDDDDC7ED__INCLUDED_)
#define AFX_STAGEDISTANCE_H__9D1513DC_3FB6_45E5_A4D3_53DCDDDDC7ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MILESCONVERSION 1609.344

class CStageDistance : CStageCalc
{
public:
	static double ToMiles(int distance);
	static CString DistanceSingle( DWORD distance, bool bKM, bool bMile, TCHAR* cSplitter = TEXT("<BR>") );
	static CString DistanceFromTo( DWORD before, DWORD after, bool bKM, bool bMile, TCHAR* cSplitter = TEXT("<BR>") );
	static CString DistanceStage( int rounds, DWORD distance, bool bKM, bool bMile, TCHAR* cSplitter = TEXT("<BR>") );
};

#endif // !defined(AFX_STAGEDISTANCE_H__9D1513DC_3FB6_45E5_A4D3_53DCDDDDC7ED__INCLUDED_)
