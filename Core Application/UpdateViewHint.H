// UpdateViewHint.h: interface for the CUpdateViewHint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UPDATEVIEWHINT_H__87817B24_FA05_4E51_88CF_A0F2733FC7B5__INCLUDED_)
#define AFX_UPDATEVIEWHINT_H__87817B24_FA05_4E51_88CF_A0F2733FC7B5__INCLUDED_

#include "GeneralFunctions.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum UPDATEVIEWREASON
{
	UV_UNKNOWN,
	UV_CONFIGURED,
	UV_UPDATED,
	UV_ADDED,
	UV_DELETED,
	UV_SELECTIONCHANGED,
	UV_PUBLISHED,
	UV_INVALIDATEALL
};

class CUpdateViewHint  
{
public:
	UPDATEVIEWREASON	GetReason()		{ return m_reason; };
	const CObject*		GetConcerning()	{ return m_concerning; };
	int					GetHalfStage()	{ return m_nHalfStage; };
	int					GetFullStage()	{ return m_nFullStage; };
	CUpdateViewHint(UPDATEVIEWREASON r, CObject* c=NULL, int f=0, int h=0);
protected:
	UPDATEVIEWREASON	m_reason;
	const CObject*		m_concerning;
	int					m_nHalfStage;
	int					m_nFullStage;
};

#endif // !defined(AFX_UPDATEVIEWHINT_H__87817B24_FA05_4E51_88CF_A0F2733FC7B5__INCLUDED_)
