// SettingsGeneral.h: interface for the CSettingsGeneral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGSGENERAL_H__CAAD9755_C653_4D8F_9955_69B8B368ED0E__INCLUDED_)
#define AFX_SETTINGSGENERAL_H__CAAD9755_C653_4D8F_9955_69B8B368ED0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettingsGeneral : public CSettings  
{
public:
	CSettingsGeneral(CSettingsGeneral*);
	void Serialize(CArchive &objAr);
	CSettingsGeneral();
	virtual CPageSettings* GetPage();
	CSettings& operator=( const CSettings& s );

	CString m_eventName;
	CString m_eventSubTitle;
	CString m_organiser;
	CString m_dates;
	CString m_location;
	CString m_category;
	CString m_mask1;
	CString m_mask2;
	CString m_mask3;
	CString m_mask4;
	CString m_mask5;
	CString m_mask6;
	CString m_mask7;
	CString m_mask8;
	CString m_mask9;
	CString m_mask10;

	CString m_cl_sponsor_general;
	CString m_cl_sponsor_teams;
	CString m_cl_sponsor_sprint;
	CString m_cl_sponsor_climb;
	CString m_cl_sponsor_points;
	CString m_cl_sponsor_mostaggressive;
	CString m_cl_sponsor_mask1;
	CString m_cl_sponsor_mask2;
	CString m_cl_sponsor_mask3;
	CString m_cl_sponsor_mask4;
	CString m_cl_sponsor_mask5;
	CString m_cl_sponsor_mask6;
	CString m_cl_sponsor_mask7;
	CString m_cl_sponsor_mask8;
	CString m_cl_sponsor_mask9;
	CString m_cl_sponsor_mask10;
};

#endif // !defined(AFX_SETTINGSGENERAL_H__CAAD9755_C653_4D8F_9955_69B8B368ED0E__INCLUDED_)
