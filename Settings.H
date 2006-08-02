// Settings.h: interface for the CSettings class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTINGS_H__0F5BFD19_CFA5_4F19_82CD_9B56FE66615F__INCLUDED_)
#define AFX_SETTINGS_H__0F5BFD19_CFA5_4F19_82CD_9B56FE66615F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSettings : public CObject  
{
public:
	class CSetting : public CObject
	{
		public:
			bool m_bValue;
			enum SETTINGTYPE
			{
				GROUP,
				SINGLEOPTION,	// results in check box
				MULTIOPTION		// results in radio button
			} m_type;
			DWORD m_nID;
			DWORD m_nGroupID;
			char m_nIcon;

			CSetting( bool v, SETTINGTYPE t, DWORD i, DWORD g, char icon )
			{
				m_bValue = v;
				m_type = t;
				m_nID = i;
				m_nGroupID = g;
				m_nIcon = icon;
			}
			operator CObject*() { return this; }
			CSetting(const CSetting &s)
			{
				*this = s;
			}
			CSetting& CSetting::operator=( const CSetting& s )
			{
				m_bValue = s.m_bValue;
				m_type = s.m_type;
				m_nID = s.m_nID;
				m_nGroupID = s.m_nGroupID;
				m_nIcon = s.m_nIcon;
				return *this;
			}
	};

	virtual void Serialize(CArchive& objAr);
	virtual CSettings& operator=( const CSettings& s );
	void ValueSet( DWORD nID, bool bVal );
	bool ValueGet( DWORD nID, const CSetting** ppSet=NULL ) const;
	void ValueAdd(DWORD nID, CSettings::CSetting::SETTINGTYPE type, bool bInitial, int nGroupID=0, char icon=0);
	int ValuesSize() const { return m_values.GetSize(); }
	bool ValueExist( DWORD nID ) const;
	bool ValueGetAt( int nIndex, const CSetting** ppSet=NULL ) const;
	char IconGet( DWORD nGroup ) const;
	CSettings();
	CSettings(CSettings*);
	virtual ~CSettings();
	virtual CPageSettings* GetPage() = 0;
protected:
	CMap<DWORD,DWORD&,int,int&> m_availableIDs;
	CObArray m_values;
};

#endif // !defined(AFX_SETTINGS_H__0F5BFD19_CFA5_4F19_82CD_9B56FE66615F__INCLUDED_)
