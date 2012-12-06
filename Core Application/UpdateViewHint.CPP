// UpdateViewHint.cpp: implementation of the CUpdateViewHint class.
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

CUpdateViewHint::CUpdateViewHint(UPDATEVIEWREASON r, CObject *c, int f, int h)
{
	m_reason		= r;
	m_concerning	= c;
	m_nHalfStage	= h;
	m_nFullStage	= f;
}