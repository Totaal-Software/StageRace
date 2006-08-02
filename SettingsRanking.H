// SettingsRanking.h: interface for the CSettingsRanking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSRANKING_H__C04C6F5D_67B7_4B7C_AED4_CEFA4171A5A3__INCLUDED_)
#define AFX_SETTINGSRANKING_H__C04C6F5D_67B7_4B7C_AED4_CEFA4171A5A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsRanking : public CSettings  
{
public:
	CSettingsRanking(CSettingsRanking*);
	WORD m_maxDepthSprint;
	WORD m_maxDepthFinish;
	void Serialize(CArchive &objAr);
	CSettingsRanking();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	char m_bunchSize;
};

#endif // !defined(AFX_SETTINGSRANKING_H__C04C6F5D_67B7_4B7C_AED4_CEFA4171A5A3__INCLUDED_)
