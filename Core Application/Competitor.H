// Competitor.h: interface for the CCompetitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Competitor_H__237FCCA4_BA25_11D2_B376_0040954019F4__INCLUDED_)
#define AFX_Competitor_H__237FCCA4_BA25_11D2_B376_0040954019F4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCompetitor

class CCompetitor : public CStaNoObject  
{
public:
	void Swap( CCompetitor* pComp );
	CString GetClipboardRow();
	CString	m_category;
	CString	m_competitor;
	CString	m_license;
	CTeam*	m_pTeam;
	CString	m_UCICode;
	CString	m_countryCode;
	BOOL	m_mask1;
	BOOL	m_mask2;
	BOOL	m_mask3;
	BOOL	m_mask4;
	BOOL	m_mask5;
	BOOL	m_mask6;
	BOOL	m_mask7;
	BOOL	m_mask8;
	BOOL	m_mask9;
	BOOL	m_mask10;

	CCompetitor();
	CCompetitor( const CCompetitor &aComp );
	virtual ~CCompetitor();
	CCompetitor& operator=(const CEditCompetitor& aComp);
	CCompetitor& operator=(const CCompetitor& aComp);

 	void Serialize(CArchive& ar);

	int Edit(const CStageRaceDoc* pDoc);
	void SetMask(char nMask, bool bOn = TRUE);
};

#endif // !defined(AFX_Competitor_H__237FCCA4_BA25_11D2_B376_0040954019F4__INCLUDED_)
