// SplitterWndFixed.cpp: implementation of the CStageRaceSplitterWnd class.
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

CSplitterWndFixed::CSplitterWndFixed()
{
	m_cySplitter=0;
	m_cyBorderShare=0;
	m_cySplitterGap=2;
}

CSplitterWndFixed::~CSplitterWndFixed()
{

}

int CSplitterWndFixed::HitTest(CPoint pt) const
{
	// Do not allow caller to see mouse hits
	// in order to make the border fixed
	return 0;
}


