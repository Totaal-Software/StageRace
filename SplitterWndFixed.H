// SplitterWndFixed.h: interface for the CStageRaceSplitterWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSplitterWndFixed_H__87367237_86F5_44B4_BB18_92C138AD8706__INCLUDED_)
#define AFX_CSplitterWndFixed_H__87367237_86F5_44B4_BB18_92C138AD8706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSplitterWndFixed : public CSplitterWnd  
{
public:
	int HitTest(CPoint pt) const;
	CSplitterWndFixed();
	virtual ~CSplitterWndFixed();

};

#endif // !defined(AFX_CSplitterWndFixed_H__87367237_86F5_44B4_BB18_92C138AD8706__INCLUDED_)
