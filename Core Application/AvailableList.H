// AvailableList.h: interface for the CAvailableList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AVAILABLELIST_H__6F836636_51ED_460A_9A8F_CDC47DB4E364__INCLUDED_)
#define AFX_AVAILABLELIST_H__6F836636_51ED_460A_9A8F_CDC47DB4E364__INCLUDED_

#include "Arrival.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAvailableList
{
public:
	CArrival GetAt(WORD) const;
	bool Exist(WORD) const;
	virtual  ~CAvailableList();
	bool IterateSorted(DWORD &nState, CArrival &objArr) const;
	CAvailableList( const CSignOutList*		pListSignOuts,
					const CStaNoObjectList*	pListCompetitors,
					const CStaNoObjectList* pListMustBeOn=NULL);
protected:
	const CSignOutList*		m_pListSignOuts;
	const CStaNoObjectList*	m_pListCompetitors;
	const CStaNoObjectList*	m_pListMustBeOn;
};

#endif // !defined(AFX_AVAILABLELIST_H__6F836636_51ED_460A_9A8F_CDC47DB4E364__INCLUDED_)
