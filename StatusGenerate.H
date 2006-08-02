// StatusGenerate.h: interface for the CStatusGenerate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSGENERATE_H__F5016A49_049B_46DF_890B_22B793CCE57C__INCLUDED_)
#define AFX_STATUSGENERATE_H__F5016A49_049B_46DF_890B_22B793CCE57C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStatusGenerate : public CStatusProgress  
{
public:
	void Finish();
	void Reposition();
	BOOL Create( CStatusBar * parent, UINT id, DWORD style );
	void Increment();
	BOOL PreTranslateMessage(MSG *pMsg);
	void Start(int);
	CStatusGenerate();
	virtual ~CStatusGenerate();

protected:
	int m_nProgressLength;
};

#endif // !defined(AFX_STATUSGENERATE_H__F5016A49_049B_46DF_890B_22B793CCE57C__INCLUDED_)
