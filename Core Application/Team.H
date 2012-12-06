// Team.h: interface for the CTeam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEAM_H__03C584C0_BFAD_11D3_92DA_0040954019F4__INCLUDED_)
#define AFX_TEAM_H__03C584C0_BFAD_11D3_92DA_0040954019F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTeam : public CObject
{
	DECLARE_SERIAL(CTeam)
public:
	CString GetClipboardRow();
	CString m_code;		//Key
	CString m_name;		//Optional
	CString m_manager;	//Optional
	CString m_country;	//Optional

	CTeam();
	virtual ~CTeam();
	void Serialize(CArchive & ar);
	CTeam(const CTeam* pTeam);
	CTeam(const CTeam& aTeam);
	CTeam& operator=(const CEditTeam& aTeam);
	CTeam& operator=(const CTeam &aTeam);
	int Edit(const CStageRaceDoc* pDoc, HANDLE hSemaphore=NULL);
};

#endif // !defined(AFX_TEAM_H__03C584C0_BFAD_11D3_92DA_0040954019F4__INCLUDED_)
